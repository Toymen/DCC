#include "include/Detectors/BelleII.h"
#include "include/DetectorGeometryUtils.h"

//Belle II main detector
//We take the fiducial volume to be -40cm < z < 120 cm and 10 cm < r < 80 cm
//The user can freely adjust these numbers according to their need

Detector BelleII() {
    const auto layers = BuildZHRectLayers({{-0.4, 1.2, 0.1, 0.8, 1.0}});
    return Detector("BelleII", 50.0e3, layers);
}

bool BelleIICuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
