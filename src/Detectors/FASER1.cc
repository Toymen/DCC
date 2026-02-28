#include "include/Detectors/FASER1.h"
#include "include/DetectorGeometryUtils.h"

    // FASER
    
Detector FASER1() {
 const auto layers = BuildZHRectLayers({{478.5, 480.0, 0.0, 0.1, 1.0}});
 return Detector("FASER", 150.0, layers);
}

bool FASER1Cuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
