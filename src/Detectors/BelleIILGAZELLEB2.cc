#include "include/Detectors/BelleIILGAZELLEB2.h"
#include "include/DetectorGeometryUtils.h"

// Detector for Large Gazelle-B2 (LGB2) at SuperKEKB
// Dimensions: 26m x 16m x 3m cube.
// Position: x approx 19m, y approx 2.3m, z approx 10.5m.
// Integrated Luminosity: 50 ab^-1.


Detector BelleIILGAZELLEB2() {
    const auto layers = BuildRectangularTiledLayers(
         9.0, 12.0,   // z
         6.0, 32.0,   // x
        -5.7, 10.3,   // y
          5,    2);   // slicing
    return Detector("BelleIILGAZELLEB2", 50000.0, layers);
}

bool BelleIILGAZELLEB2Cuts(HepMC::GenEvent* evtin){
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
