#include "include/Detectors/ANUBISceiling.h"
#include "include/DetectorGeometryUtils.h"
//anubis ceiling, l=53, rin=11.3 and rout=19.9, dx=28.7
Detector ANUBISceiling() {
 const auto layers = BuildZHRectLayers({{-53.0 / 2.0, 53.0 / 2.0, 11.3, 19.9, 0.198864}});
 return Detector("ANUBISceiling", 3000.0, layers);
}

bool ANUBISceilingCuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
