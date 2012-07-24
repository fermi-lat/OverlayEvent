/** @file TkrOverlay.h
*
* @author Leon Rochester
*
* $Header: /nfs/slac/g/glast/ground/cvs/OverlayEvent/OverlayEvent/TkrOverlay.h,v 1.2 2008/12/07 17:01:39 usher Exp $
*/

#ifndef Event_TkrOverlay_H
#define Event_TkrOverlay_H 1

//include files
#include "GaudiKernel/ContainedObject.h"
#include "GaudiKernel/ObjectVector.h"
#include "GaudiKernel/IInterface.h"

#include "idents/TowerId.h"
#include "idents/GlastAxis.h"

#include <vector>
#include <algorithm>

static const CLID& CLID_TkrOverlay = InterfaceID("TkrOverlay", 1, 0);

namespace Event {

/*!
* \class TkrOverlay
* \brief TDS version of the TKR digi
*
* Contains layer and tower identification, ToT and a list of hit strips
* The digis are produced either from MC hit output or from the actual data
*/

class TkrOverlay : public std::vector<int>, virtual public ContainedObject 
{
public:
    //! typedefs
    typedef std::vector<int> HitList;
    typedef HitList::const_iterator const_iterator;

    /// Status bit definitions
    enum DigiStatusBits {
         DIGI_NULL    = 0,
         DIGI_MC      = 1<<28,   // This digi is from Monte Carlo
         DIGI_DATA    = 1<<30,   // This digi is from data 
         DIGI_OVERLAY = 1<<31    // This digi contains overlay info
    };

    //! Constructors
    //! Null constructor
    TkrOverlay() {};

    //! constructor with layer, tower and ToT, but with an empty list of strips
    TkrOverlay(int l, idents::GlastAxis::axis v, idents::TowerId t, int* tot, DigiStatusBits status=DIGI_NULL) {
        m_bilayer = l;
        m_view = v;
        m_tower = t;
        m_tot[0] = *tot;
        m_tot[1] = *(++tot);
        m_status = status;

        m_lastController0Strip =  -1;
    };

    //! Destructor
    virtual ~TkrOverlay() 
    {
        clear();
    }

    //! Retrieve pointer to class defininition structure
    virtual const CLID& clID()    const { return TkrOverlay::classID(); }
    static  const CLID& classID()       { return CLID_TkrOverlay; }

    //! Retrieve tower info
    idents::TowerId getTower() const {return m_tower;}
    //! Retrieve layer info
    int getBilayer() const {return m_bilayer;} 
    //! Retrieve view info
    idents::GlastAxis::axis getView () const {return m_view;}
    //! Return the last strip associated with controller 0 
    int getLastController0Strip() const { return m_lastController0Strip; }
    //! Retrieve ToT info
    int getToT( int i) const {return m_tot[i];}
    //! Get ToT for a given strip
    int getToTForStrip(int strip){ return m_tot[(strip<=m_lastController0Strip ? 0 : 1 )]; }
    //! number of hits
    int getNumHits() const{ return size();} //m_hits.size(); }
    //! Get the pointer to the ith hit strip
    int getHit( int i ) const { return (*this)[i];}

    //! Add a controller 0 hit to the hit list (keeps track of highest strip)
    void addC0Hit( int strip, int ToT=0 ) 
    {
        //m_hits.push_back(strip);
        push_back(strip);
        m_lastController0Strip = std::max(strip, m_lastController0Strip);
        m_tot[0] = std::max(m_tot[0], ToT);
    }

    //! Add a controller 1 hit to the hit list
    void addC1Hit( int strip, int ToT=0 )
    {
        //m_hits.push_back(strip);
        push_back(strip);
        m_tot[1] = std::max(m_tot[1], ToT);
    }

    //! Set value of ToT
    void setToT(int i, int ToT) 
    {
        if (i == 0 || i == 1) m_tot[i] = ToT;
    }

    //! Set value of lastController0
    void setLastController0Strip(int stripId) 
    {
        m_lastController0Strip = stripId;
    }

    //! returns integer for sorting order
    operator int() const 
    {
        return m_view + 2*m_bilayer + 64*m_tower.id();
    }

    //! predicate for sort
    struct digiLess : public std::binary_function <TkrOverlay*, TkrOverlay*, bool> 
    {
        bool operator() (const TkrOverlay* left, const TkrOverlay* right) const 
        {
            return (*left)<(*right);
        } 
    };        

    //! Serialize the object for reading
    virtual StreamBuffer& serialize( StreamBuffer& s );
    //! Serialize the object for writing
    virtual StreamBuffer& serialize( StreamBuffer& s )  const;
    //! Fill the ASCII output stream
    virtual std::ostream& fillStream( std::ostream& s ) const;

    /// remove a hit from the digi, using the strip number
    void removeHit(int strip) 
    {
        // find the strip in the digi, remove if present
        HitList::iterator it = std::find(begin(), end(), strip);
        if (it!=end()) erase(it);
    }

    /// Retrieve the status word
    inline unsigned int getStatus() const {return m_status;}

    /// Allow status word to be modified
    inline void setStatus(unsigned int status)       {m_status  = status;}
    inline void addToStatus(DigiStatusBits bitToAdd) {m_status |= bitToAdd;}

private:

    idents::TowerId         m_tower;
    int                     m_bilayer;
    idents::GlastAxis::axis m_view;
    int                     m_tot[2];
    int                     m_lastController0Strip;
    unsigned int            m_status;
};


//! Serialize the object for writing
inline StreamBuffer& TkrOverlay::serialize( StreamBuffer& s ) const 
{
    ContainedObject::serialize(s);  
    s << m_bilayer
      << (int)m_view
      << m_tower.id()
      << m_tot[0]
      << m_tot[1]
      << m_lastController0Strip
      << size();
    const_iterator ih;
    for (ih = begin(); ih!=end(); ih++) {
        s << *ih;
    }

    return s;
}

//! Serialize the object for reading
inline StreamBuffer& TkrOverlay::serialize( StreamBuffer& s )       
{
    ContainedObject::serialize(s);
    int size;
    int view;
    long tower;
    s >> m_bilayer
      >> view
      >> tower
      >> m_tot[0]
      >> m_tot[1]
      >> m_lastController0Strip
      >> size;
    m_tower = idents::TowerId(tower);
    m_view  = (view==0 ? idents::GlastAxis::X : idents::GlastAxis::Y);

    resize( size, 0);
    std::vector<int>::iterator ih;
    for (ih = begin(); ih!=end(); ih++) {
        s >> *ih;
    }

    return s;
}

//! Fill the ASCII output stream

inline std::ostream& TkrOverlay::fillStream( std::ostream& s ) const 
{
    int j;
    int hitSize = size();
    s << "class TkrOverlay :" << std::endl
      << "Layer: " << m_bilayer 
      << " view: " << (int)m_view
      << " tower: " << m_tower.id()
      << " ToT: " << m_tot[0] << " " << m_tot[1]
      << " last controller 0 strip " << m_lastController0Strip
      << std::endl
      << " Number of hits strips: " << hitSize << std::endl;

    const_iterator ih;
    for(ih = begin(), j=0; ih != end();ih++,j++) {
        if (j==10) {j = 0; s << std::endl;}
        s << *ih << " ";
    }
    s << std::endl;
    return s;
}

//! Definition of all container type of TkrOverlay

typedef ObjectVector<TkrOverlay> TkrOverlayCol;

} //Namespace Event
#endif
