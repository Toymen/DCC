#include "include/Detectors/DELIGHTB.h"
#include "include/DetectorGeometryUtils.h"

//2306.11803  
//DELIGHT-B
//   25.0 m < x < 125.0 m
//    0.0 m < y < 100.0 m
//  -50.0 m < z < 50.0 m

Detector DELIGHTB() {
    const auto delightLayers = BuildRectangularTiledLayers(
        -50.0,  50.0,
         25.0, 125.0,
          0.0, 100.0,
            50,   50);
    return Detector("DELIGHTB", 30000.0, delightLayers);
}


bool DELIGHTBCuts(HepMC::GenEvent* evtin) {
    bool cuts = true;

    // Example: keep all events by default; user can add LLP-specific kinematic/decay-volume cuts here.
    // for (HepMC::GenEvent::particle_const_iterator p = evtin->particles_begin();
    //      p != evtin->particles_end(); ++p) {
    //     if ((*p)->pdg_id() == <LLP_PDG_ID>) {
    //         // Example kinematic cut: require LLP energy > 100 GeV
    //         if ((*p)->momentum().e() < 100.0) {
    //             cuts = false;
    //             break;
    //         }
    //     }
    // }
    return cuts;
}

