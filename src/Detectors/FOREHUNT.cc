#include "include/Detectors/FOREHUNT.h"
#include "include/DetectorGeometryUtils.h"
//2306.11803  
//we take FOREHUNT-C as an example which gives the max signal acceptance out of the six detector configuratons for all the benchmark points
//R = 5 m, Length Ld = 50 m,  distance of the near end from the IP = 50 m



Detector FOREHUNT() {
 const auto layers = BuildZHRectLayers({{50.0, 100.0, 0.0, 5.0, 1.0}});
 return Detector("FOREHUNT", 30000.0, layers);
}

bool FOREHUNTCuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};


