#include "include/Detectors/FASER2.h"
#include "include/DetectorGeometryUtils.h"

    // FASER2
    
Detector FASER2() {
 const auto layers = BuildZHRectLayers({{475.0, 480.0, 0.0, 1.0, 1.0}});
 return Detector("FASER2", 3000.0, layers);
}

bool FASER2Cuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
