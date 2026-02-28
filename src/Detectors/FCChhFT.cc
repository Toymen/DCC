#include "include/Detectors/FCChhFT.h"
#include "include/DetectorGeometryUtils.h"

Detector FCChhFT() { 
 const auto layers = BuildZHRectLayers({{10.0, 16.0, 20.0/1000.0, 1.6, 1.0}});
 return Detector("FCChhFT", 20000.0, layers);
}

bool FCChhFTCuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
