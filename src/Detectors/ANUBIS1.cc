#include "include/Detectors/ANUBIS1.h"
#include "include/DetectorGeometryUtils.h"

    // Building ANUBIS from 1m-high, 1m-deep bricks
    
Detector ANUBIS1() {
 const auto bricks = BuildPolarBricksOverZ(
     4.0, 1.0, 20,
     1.0,
     24.0, 1.5, 44,
     1.5 * atan(1.0), 0.00392699, 200,
     [](double z, double x, double y) {
       const double dz = z - 14.0;
       const double dx = x - 0.0;
       const double dist = sqrt(dz * dz + dx * dx);
       return y >= 24.0 && y <= 80.0 && dist < 9.0;
     });
 return Detector("ANUBIS1", 3000.0, bricks);
}

bool ANUBIS1Cuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
