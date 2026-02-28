#include "include/Detectors/MATHUSLA40.h"
#include "include/DetectorGeometryUtils.h"

	//zmin = 70, zmax = 70 + 40 = 110    xmin=-20  xmax=20   ymin=81   ymax=81+11=92
    // Building MATHUSLA40 from dh-m-high bricks
    
Detector MATHUSLA40() {
 const auto bricks = BuildPolarBricksAtFixedZ(
     90.0, 40.0,
     40.0, 1.0, 75,
     atan(1.0), 0.00785398, 200,
     [](double x, double y) {
       return y >= 81.0 && y <= 92.0 && x >= -20.0 && x <= 20.0;
     });
 return Detector("MATHUSLA40", 3000.0, bricks);
}

bool MATHUSLA40Cuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
