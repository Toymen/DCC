#include "include/Detectors/BelleIIBabyGAZELLE.h"
#include "include/DetectorGeometryUtils.h"

// Dimensions: 4m x 4m x 4m cube.
// Position: x approx 10m, y approx -3.7m, z approx 10m.
// Integrated Luminosity: 50 ab^-1.
Detector BelleIIBabyGAZELLE() {
    const auto layers = BuildRectangularTiledLayers(
        10.0, 14.0,   // z
         8.0, 12.0,   // x
        -5.7, -1.7,   // y
          1,    1);   // one layer
    return Detector("BelleIIBabyGAZELLE", 50000.0, layers);
}

bool BelleIIBabyGAZELLECuts(HepMC::GenEvent* evtin){
 bool cuts=true;
    // Example of a possible cut:
    // if (evtin->event_scale() < 100.0) { // Example: Cut on event scale
    //     cuts = false;
    // }
    // Loop through particles in the event to apply cuts based on LLP properties
    // for (HepMC::GenEvent::particle_const_iterator p = evtin->particles_begin(); p != evtin->particles_end(); ++p) {
    //     if ((*p)->pdg_id() == <LLP_PDG_ID>) { // Replace <LLP_PDG_ID> with the actual PDG ID of your LLP
    //         if ((*p)->momentum().e() < 50.0) { // Example: Cut on LLP energy
    //             cuts = false;
    //             break; 
    //         }
    //     }
    // }
 return cuts;
};
