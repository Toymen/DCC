#include "include/DetectorGeometryUtils.h"

#include <cmath>
#include <iostream>
#include <string>

namespace {

bool nearlyEqual(double a, double b, double eps = 1e-12) {
    return std::abs(a - b) <= eps;
}

bool check(const std::string& name, bool ok) {
    if (ok) {
        std::cout << "[PASS] " << name << '\n';
        return true;
    }
    std::cerr << "[FAIL] " << name << '\n';
    return false;
}

}  // namespace

int main() {
    bool allOk = true;
    const double pi = 4.0 * std::atan(1.0);

    allOk &= check("normalize negative phi", nearlyEqual(NormalizePhi(-0.1), 2.0 * pi - 0.1));
    allOk &= check("normalize positive phi unchanged", nearlyEqual(NormalizePhi(1.3), 1.3));

    allOk &= check(
        "small angular span with wrap-around",
        nearlyEqual(SmallestAngularSpan({6.20, 6.25, 0.02, 0.05}), 0.053185307179585806, 1e-9));

    allOk &= check(
        "small angular span without wrap-around",
        nearlyEqual(SmallestAngularSpan({0.10, 0.15, 0.18, 0.24}), 0.14, 1e-12));

    allOk &= check(
        "linear interpolation at upstream edge",
        nearlyEqual(LinearInterpolate(10.0, 10.0, 20.0, 2.0, 6.0), 2.0));
    allOk &= check(
        "linear interpolation at downstream edge",
        nearlyEqual(LinearInterpolate(30.0, 10.0, 20.0, 2.0, 6.0), 6.0));
    allOk &= check(
        "linear interpolation midpoint",
        nearlyEqual(LinearInterpolate(20.0, 10.0, 20.0, 2.0, 6.0), 4.0));

    const auto layers = BuildRectangularTiledLayers(
        -1.0, 1.0,   // z range
        1.0, 3.0,    // x range
        0.0, 2.0,    // y range
        2, 2);       // tiles
    allOk &= check("tile builder creates nx*ny layers", layers.size() == 4);

    const auto frustumBricks = BuildRectangularFrustumBricks(
        0.0, 2.0, 1.0,   // z min, total length, dz
        2.0, 2.0,        // wx upstream/downstream
        2.0, 2.0,        // wy upstream/downstream
        1.0, 4, 1.1);    // dh, phi bins, safety
    allOk &= check("frustum builder creates expected simple brick count", frustumBricks.size() == 2);

    const auto polarFixed = BuildPolarBricksAtFixedZ(
        0.0, 1.0,
        1.0, 1.0, 2,
        0.0, pi / 2.0, 4,
        [](double x, double) { return x >= 0.0; });
    allOk &= check("fixed-z polar builder count", polarFixed.size() == 2);

    const auto polarOverZ = BuildPolarBricksOverZ(
        0.0, 1.0, 2,
        1.0,
        1.0, 1.0, 1,
        0.0, pi / 2.0, 4,
        [](double z, double x, double) { return z < 1.0 && x >= 0.0; });
    allOk &= check("z-sweep polar builder count", polarOverZ.size() == 1);

    const auto zhLayers = BuildZHRectLayers({
        {0.0, 1.0, 2.0, 3.0, 0.5},
        {1.0, 2.0, 3.0, 4.0, 0.25}});
    allOk &= check("zh-rect table builder count", zhLayers.size() == 2);

    if (!allOk) return 1;
    return 0;
}
