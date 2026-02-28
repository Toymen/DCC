#include "include/Detectors/DELIGHTC.h"
#include "include/DetectorGeometryUtils.h"

//2306.11803  
//DELIGHT-C
//   25.0 m < x < 225.0 m
//    0.0 m < y < 50.0 m
//  -25.0 m < z < 25.0 m

Detector DELIGHTC() {
    const auto delightLayers = BuildRectangularTiledLayers(
        -25.0,  25.0,
         25.0, 225.0,
          0.0,  50.0,
           100,   25);
    return Detector("DELIGHTC", 30000.0, delightLayers);
}


bool DELIGHTCCuts(HepMC::GenEvent* evtin) {
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

