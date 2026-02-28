#include "include/Detectors/SHiPhsds.h"
#include "include/DetectorGeometryUtils.h"

// SHiPhsds: pyramidal frustum
//https://cds.cern.ch/record/2878604/files/SPSC-P-369.pdf
//SHiP Hidden Sector Decay Spectrometer
// zmin = 33.0 m, length = 50 m
// upstream: 1.0 × 2.7 m², downstream: 4.0 × 6.0 m²

Detector SHiPhsds() {
    const auto bricks = BuildRectangularFrustumBricks(
        33.0, 50.0, 1.0,
         1.0,  4.0,
         2.7,  6.0,
         0.1, 800, 1.1);

    std::string Dname = "SHiPhsds";
    double DLumi = 4.6e6;
    Detector mySHiPhsds(Dname, DLumi, bricks);
    return mySHiPhsds;
}

bool SHiPhsdsCuts(HepMC::GenEvent* evtin){
    bool cuts = true;
    return cuts;
};



/*estimation of Dlumi, the effective int lumi of SHiP

15 years with 6e20 POTs.

L = NPOT times   n_target.
n_target = NA  rho  L_target / A
NA = 6.022e23   #/mol, Avogadrgo's number
rho = 10.22g/cm^3, since the target consists of TZM alloy   (considering molybdenum)
L_target = 1.2 m = 120 cm.  this is becasue 12 nuclear interaction length for a 400 GeV proton beam is roughly 1.2 m
A = 95.95 g/mol.   (considering molybdenum)
So n_target = 7.697e3 nuclei/cm^2
So L = 4.6e45 cm^{-2} = 4.618e6 /fb
*/
