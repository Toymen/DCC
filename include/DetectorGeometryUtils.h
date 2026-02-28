#ifndef _DETECTOR_GEOMETRY_UTILS_
#define _DETECTOR_GEOMETRY_UTILS_

#include <array>
#include <functional>
#include <vector>

#include "include/CCylDetLayer.h"

double NormalizePhi(double phi);
double SmallestAngularSpan(const std::array<double,4>& phis);
double LinearInterpolate(double z, double zMin, double length, double upstream, double downstream);

std::vector<CylDetLayer> BuildRectangularTiledLayers(
    double zMin, double zMax,
    double xMin, double xMax,
    double yMin, double yMax,
    int numXSlices, int numYSlices);

std::vector<CylDetLayer> BuildRectangularFrustumBricks(
    double zMin, double totalLength, double dz,
    double wxUpstream, double wxDownstream,
    double wyUpstream, double wyDownstream,
    double dh, int phiBins, double safetyFactor = 1.1);

// Row format: {zMin, zMax, hMin, hMax, weight}
std::vector<CylDetLayer> BuildZHRectLayers(const std::vector<std::array<double,5>>& rows);

std::vector<CylDetLayer> BuildPolarBricksAtFixedZ(
    double zCoord, double dl,
    double hStart, double dh, int hBins,
    double phiStart, double dphi, int phiBins,
    const std::function<bool(double x, double y)>& insideXY);

std::vector<CylDetLayer> BuildPolarBricksOverZ(
    double zStart, double dz, int zBins,
    double dl,
    double hStart, double dh, int hBins,
    double phiStart, double dphi, int phiBins,
    const std::function<bool(double z, double x, double y)>& insideXYZ);

#endif
