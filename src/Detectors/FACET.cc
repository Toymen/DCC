#include "include/Detectors/FACET.h"
#include "include/DetectorGeometryUtils.h"

Detector FACET() {
 const auto layers = BuildZHRectLayers({{101.0, 119.0, 0.1, 0.5, 1.0}});
 return Detector("FACET", 3000.0, layers);
}

bool FACETCuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
