#include "include/Detectors/ANUBIS0.h"
#include "include/DetectorGeometryUtils.h"

    // Uncle Simon's ANUBIS
    
Detector ANUBIS0() {
 const auto layers = BuildZHRectLayers({
     {5.0, 23.0, 24.0, 42.667, 2.0 * atan(9.0 / 33.333) / (8.0 * atan(1.0))},
     {5.0, 23.0, 42.667, 61.333, 2.0 * atan(9.0 / 52.0) / (8.0 * atan(1.0))},
     {5.0, 23.0, 61.333, 80.0, 2.0 * atan(9.0 / 70.667) / (8.0 * atan(1.0))}
 });
 return Detector("ANUBIS0", 3000.0, layers);
}

bool ANUBIS0Cuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
