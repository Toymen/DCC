#include "include/Detectors/BelleIILGAZELLEB1.h"
#include "include/DetectorGeometryUtils.h"

// Detector for Large Gazelle-B1 (LGB1) at SuperKEKB
// Dimensions: 6m x 16m x 24m cube.
// Position: x approx 35m, y approx 2.3m, z approx 0m.
// Integrated Luminosity: 50 ab^-1.
Detector BelleIILGAZELLEB1() {
    const auto layers = BuildRectangularTiledLayers(
        -12.0, 12.0,  // z
         32.0, 38.0,  // x
         -5.7, 10.3,  // y
           1,    1);  // one layer
    return Detector("BelleIILGAZELLEB1", 50000.0, layers);
}

bool BelleIILGAZELLEB1Cuts(HepMC::GenEvent* evtin){
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
