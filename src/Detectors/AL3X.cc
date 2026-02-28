#include "include/Detectors/AL3X.h"
#include "include/DetectorGeometryUtils.h"

    // AL3X
    
Detector AL3X() {
 const auto layers = BuildZHRectLayers({{5.25, 17.25, 0.85, 5.0, 1.0}});
 return Detector("AL3X", 250.0, layers);
}

bool AL3XCuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
