#include "include/Detectors/FCChhCT.h"
#include "include/DetectorGeometryUtils.h"

Detector FCChhCT() {
    const auto layers = BuildZHRectLayers({{-5.0, 5.0, 20.0/1000.0, 1.7, 1.0}});
    return Detector("FCChhCT", 20000.0, layers);
}

bool FCChhCTCuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
