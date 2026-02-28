#include "include/Detectors/CODEXB1.h"
#include "include/DetectorGeometryUtils.h"

    // Improved CODEXB
    
Detector CODEXB1() {
 const double norm = 8.0 * atan(1.0);
 const auto layers = BuildZHRectLayers({
     {5.0, 15.0, 26.051358, 36.0711111, 0.17766086 / norm},
     {5.0, 15.0, 26.118785, 31.56222,   0.0127311073 / norm},
     {5.0, 15.0, 26.146760, 28.3784804, 0.008702541 / norm},
     {5.0, 15.0, 26.2479356, 36.3432954, 0.084295998 / norm},
     {5.0, 15.0, 26.455781, 36.6310814, 0.024716089 / norm},
     {5.0, 15.0, 26.549617, 34.596021,  0.011806297 / norm},
     {5.0, 15.0, 26.618576, 32.674020,  0.012533236 / norm},
     {5.0, 15.0, 26.696529, 30.858797,  0.0133093 / norm},
     {5.0, 15.0, 26.784744, 29.144419,  0.01413877 / norm},
     {5.0, 15.0, 26.863778, 27.832842,  0.00920773 / norm}
 });
 return Detector("CODEXB1", 300.0, layers);
}

bool CODEXB1Cuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
