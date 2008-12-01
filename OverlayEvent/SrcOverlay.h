#ifndef Event_SrcOverlay_H
#define Event_SrcOverlay_H 1

#include <iostream>
#include "GaudiKernel/Kernel.h"
#include "GaudiKernel/StreamBuffer.h"
#include "GaudiKernel/DataObject.h"
#include "Event/TopLevel/Definitions.h"

static const CLID& CLID_SrcOverlay = InterfaceID("SrcOverlay", 1, 0);

/** @class SrcOverlay
* @brief Defines the top level object for digitization data.
* It can be identified by "/Event/Digi" on the TDS
* 
* It contains:
* - m_fromMc, if coming from Monte Carlo
* 
* $Header: /nfs/slac/g/glast/ground/cvs/OverlayEvent/OverlayEvent/SrcOverlay.h,v 1.0 2005/02/02 05:19:09 heather Exp $
*/
namespace Event {  // NameSpace

class SrcOverlay : public DataObject {
    
public:
    
    SrcOverlay()
        : DataObject(), m_fromMc(true) { }
    
    virtual ~SrcOverlay() { }
    
    void initialize(bool fromMc) { m_fromMc = fromMc; };

    /// Retrieve reference to class definition structure
    virtual const CLID& clID() const  { return SrcOverlay::classID(); }
    static const CLID& classID() { return CLID_SrcOverlay; }
    
    ///  Retrieve flag of origin
    bool fromMc () const {
        return m_fromMc;
    }
    
    /// Serialize the object for writing
    virtual StreamBuffer& serialize( StreamBuffer& s ) const;
    /// Serialize the object for reading
    virtual StreamBuffer& serialize( StreamBuffer& s );
    
    /// Output operator (ASCII)
    friend std::ostream& operator<< ( std::ostream& s, const SrcOverlay& obj )     {
        return obj.fillStream(s);
    }
    /// Fill the output stream (ASCII)
    virtual std::ostream& fillStream( std::ostream& s ) const;
    
private: 
    /// Flag of origin
    bool m_fromMc;
};

}

//
// Inline code must be outside the class definition
//


/// Serialize the object for writing
inline StreamBuffer& Event::SrcOverlay::serialize( StreamBuffer& s ) const              {
    DataObject::serialize(s);
    unsigned char u = (m_fromMc) ? 1 : 0;
    return s << u;
}


/// Serialize the object for reading
inline StreamBuffer& Event::SrcOverlay::serialize( StreamBuffer& s )                    {
    DataObject::serialize(s);
    unsigned char u;
    s >> u;
    m_fromMc = (u) ? true : false;
    return s;
}


/// Fill the output stream (ASCII)
inline std::ostream& Event::SrcOverlay::fillStream( std::ostream& s ) const             {
    s << "class SrcOverlay :"
        << "\n    Flag of origin    = ";
    if( m_fromMc ) {
        s << " true";
    }
    else {
        s << "false";
    }
    return s;
}


#endif  // GLASTEVENT_SrcOverlay_H

