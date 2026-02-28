#include "include/Detectors/CODEXB0.h"
#include "include/DetectorGeometryUtils.h"

    // Uncle Simon's CODEXB
    
Detector CODEXB0() {
 const double w = 2.0 * atan(5.0 / 31.0) / (8.0 * atan(1.0));
 const auto layers = BuildZHRectLayers({{5.0, 15.0, 26.0, 36.0, w}});
 return Detector("CODEXB0", 300.0, layers);
}

bool CODEXB0Cuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
