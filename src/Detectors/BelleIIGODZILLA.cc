#include "include/Detectors/BelleIIGODZILLA.h"
#include "include/DetectorGeometryUtils.h"

// Detector for GODZILLA at SuperKEKB
// Dimensions: 25m x 10m x 50m cube.
// Position: x approx -27m, y approx 18m, z approx 20m.
// Integrated Luminosity: 50 ab^-1.

Detector BelleIIGODZILLA() {
    const auto layers = BuildRectangularTiledLayers(
        -5.0, 45.0,    // z
       -39.5, -14.5,   // x
        13.0, 23.0,    // y
           5,    2);   // slicing
    return Detector("BelleIIGODZILLA", 50000.0, layers);
    // Example of a possible cut:
    // if (evtin->event_scale() < 100.0) { 
    //     cuts = false;
    // }
    // for (HepMC::GenEvent::particle_const_iterator p = evtin->particles_begin(); p != evtin->particles_end(); ++p) {
    //     if ((*p)->pdg_id() == <LLP_PDG_ID>) { 
    //         if ((*p)->momentum().e() < 50.0) { 
    //             cuts = false;
    //             break;
    //         }
    //     }
    // }
}

bool BelleIIGODZILLACuts(HepMC::GenEvent* evtin){
 bool cuts=true;
 return cuts;
};
