#include "include/Detectors/MATHUSLA2.h"
#include "include/DetectorGeometryUtils.h"

    // Building MATHUSLA from 3m-high bricks
    
Detector MATHUSLA2() {
 const auto bricks = BuildPolarBricksAtFixedZ(
     118.0, 100.0,
     40.0, 3.0, 25,
     atan(1.0), 0.00785398, 200,
     [](double x, double y) {
       return y >= 60.0 && y <= 85.0 && x >= -50.0 && x <= 50.0;
     });
 return Detector("MATHUSLA2", 3000.0, bricks);
}

bool MATHUSLA2Cuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
