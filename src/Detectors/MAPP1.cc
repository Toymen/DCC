#include "include/Detectors/MAPP1.h"
#include "include/DetectorGeometryUtils.h"

Detector MAPP1() {
 const auto layers = BuildPolarBricksOverZ(
     -63.0, 0.2, 80,
     0.2,
     3.0, 0.2, 25,
     1.0, 0.00785398, 120,
     [](double z, double x, double y) {
       return -0.813502 * y - 0.0692948 * z <= 1.0 &&
               0.0351491 * y - 0.0167562 * z >= 1.0 &&
               0.922095  * y + 0.0827521 * z <= 1.0 &&
               0.029519  * y - 0.0143659 * z <= 1.0 &&
               x >= -2.0 && x <= 1.0;
     });
 return Detector("MAPP1", 30.0, layers);
}

bool MAPP1Cuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
