// File and Version Information:
// $Header: /nfs/slac/g/glast/ground/cvs/OverlayEvent/src/OverlayEventModel.cpp,v 1.3 2010/04/27 16:49:08 usher Exp $

#define _OverlayEventModel_CPP_

// Define this in order to export symbols
#define OEVT_DLL_EXPORTS

#include "OverlayEvent/OverlayEventModel.h"
#include "GaudiKernel/ClassID.h"

std::string OverlayEventModel::OverlayEventHeader = "/Overlay"; 

/** 
 *  @class Definitions of Overlay locations in transient data store
 *         **NOTE** that unlike the /Event section of the TDS, the definitions
 *         below are RELATIVE addresses! In order to facilitate the possibility
 *         of multiple overlay files there will be different sections in the 
 *         TDS for the overlay all prefixed by a section name defined in 
 *         OverlayDataSvc. 
 *
*/

// Digi Overlay 
std::string OverlayEventModel::Overlay::EventOverlay    = ""; //OverlayEventModel::OverlayEventHeader; //    + "/Overlay";
std::string OverlayEventModel::Overlay::SrcOverlay      = OverlayEventModel::Overlay::EventOverlay + "/Src";
std::string OverlayEventModel::Overlay::AcdOverlayCol   = OverlayEventModel::Overlay::EventOverlay + "/AcdOverlayCol";
std::string OverlayEventModel::Overlay::TkrOverlayCol   = OverlayEventModel::Overlay::EventOverlay + "/TkrOverlayCol";
std::string OverlayEventModel::Overlay::CalOverlayCol   = OverlayEventModel::Overlay::EventOverlay + "/CalOverlayCol";
std::string OverlayEventModel::Overlay::GemOverlay      = OverlayEventModel::Overlay::EventOverlay + "/GemOverlay";
std::string OverlayEventModel::Overlay::DiagDataOverlay = OverlayEventModel::Overlay::EventOverlay + "/DiagDataOverlay";
std::string OverlayEventModel::Overlay::PtOverlay       = OverlayEventModel::Overlay::EventOverlay + "/PtOverlay";

