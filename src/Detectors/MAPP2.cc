#include "include/Detectors/MAPP2.h"
#include "include/DetectorGeometryUtils.h"

Detector MAPP2() {
 const auto layers = BuildPolarBricksOverZ(
     -63.0, 0.5, 60,
     0.5,
     3.0, 0.2, 70,
     1.0, 0.00785398, 120,
     [](double z, double x, double y) {
       return -0.809479  * y - 0.0690327 * z <= 1.0 &&
               0.0357762 * y - 0.0167142 * z >= 1.0 &&
              -0.0149185 * y - 0.0351651 * z >= 1.0 &&
               0.0297144 * y - 0.0143532 * z <= 1.0 &&
               x >= -2.0 && x <= 1.0;
     });
 return Detector("MAPP2", 300.0, layers);
}

bool MAPP2Cuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
