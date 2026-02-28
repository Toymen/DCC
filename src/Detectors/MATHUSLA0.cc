#include "include/Detectors/MATHUSLA0.h"
#include "include/DetectorGeometryUtils.h"

    // Uncle Simon's MATHUSLA
    
Detector MATHUSLA0() {
 double w = 2.0 * atan(50.0 / 60.0) / (8.0 * atan(1.0));
 const auto layers = BuildZHRectLayers({{68.0, 168.0, 60.0, 85.0, w}});
 return Detector("MATHUSLA0", 3000.0, layers);
}

bool MATHUSLA0Cuts(HepMC::GenEvent* evtin){
 bool cuts=true;
   for (auto p  = evtin->particles_begin(); p != evtin->particles_end(); ++p ){

    /*
    //apply trivial cut
    if( (*p)->momentum().perp() > -10. ){
    std::cout << (*p)->pdg_id() << std::endl;
      return true;
    }

    */

   }

 return cuts;
};
