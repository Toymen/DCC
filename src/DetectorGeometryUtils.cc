#include "include/DetectorGeometryUtils.h"
#include "include/CDetector.h"

#include <algorithm>
#include <cmath>

double NormalizePhi(double phi) {
  const double twoPi = 8.0 * atan(1.0);
  while (phi < 0.0) {
    phi += twoPi;
  }
  while (phi >= twoPi) {
    phi -= twoPi;
  }
  return phi;
}

double SmallestAngularSpan(const std::array<double,4>& phis) {
  std::array<double,4> nphi = {
      NormalizePhi(phis[0]),
      NormalizePhi(phis[1]),
      NormalizePhi(phis[2]),
      NormalizePhi(phis[3])};

  const double minPhi = std::min({nphi[0], nphi[1], nphi[2], nphi[3]});
  const double maxPhi = std::max({nphi[0], nphi[1], nphi[2], nphi[3]});
  const double directSpan = maxPhi - minPhi;
  const double twoPi = 8.0 * atan(1.0);
  const double wrapSpan = (minPhi + twoPi) - maxPhi;
  return std::min(directSpan, wrapSpan);
}

double LinearInterpolate(double z, double zMin, double length, double upstream, double downstream) {
  if (length == 0.0) return upstream;
  return upstream + (downstream - upstream) * (z - zMin) / length;
}

std::vector<CylDetLayer> BuildRectangularTiledLayers(
    double zMin, double zMax,
    double xMin, double xMax,
    double yMin, double yMax,
    int numXSlices, int numYSlices) {
  std::vector<CylDetLayer> layers;
  const double xDim = xMax - xMin;
  const double yDim = yMax - yMin;
  const double dx = xDim / static_cast<double>(numXSlices);
  const double dy = yDim / static_cast<double>(numYSlices);
  const double twoPi = 8.0 * atan(1.0);

  layers.reserve(static_cast<size_t>(numXSlices * numYSlices));

  for (int i = 0; i < numXSlices; ++i) {
    for (int j = 0; j < numYSlices; ++j) {
      const double cxMin = xMin + i * dx;
      const double cxMax = xMin + (i + 1) * dx;
      const double cyMin = yMin + j * dy;
      const double cyMax = yMin + (j + 1) * dy;

      const double h1 = std::hypot(cxMin, cyMin);
      const double h2 = std::hypot(cxMax, cyMin);
      const double h3 = std::hypot(cxMax, cyMax);
      const double h4 = std::hypot(cxMin, cyMax);
      const double hMin = std::min({h1, h2, h3, h4});
      const double hMax = std::max({h1, h2, h3, h4});

      const std::array<double,4> phis = {
          atan2(cyMin, cxMin),
          atan2(cyMin, cxMax),
          atan2(cyMax, cxMax),
          atan2(cyMax, cxMin)};
      const double angularWeight = SmallestAngularSpan(phis) / twoPi;

      std::vector<std::array<double,2>> points = {
          {zMin, hMin}, {zMax, hMin}, {zMax, hMax}, {zMin, hMax}};
      layers.push_back(CylDetLayer(points, angularWeight));
    }
  }
  return layers;
}

std::vector<CylDetLayer> BuildRectangularFrustumBricks(
    double zMin, double totalLength, double dz,
    double wxUpstream, double wxDownstream,
    double wyUpstream, double wyDownstream,
    double dh, int phiBins, double safetyFactor) {
  std::vector<CylDetLayer> bricks;
  if (dz <= 0.0 || dh <= 0.0 || totalLength <= 0.0 || phiBins <= 0) return bricks;

  const int zSlices = static_cast<int>(totalLength / dz);
  const double twoPi = 8.0 * atan(1.0);
  const double dphi = twoPi / phiBins;

  for (int iz = 0; iz < zSlices; ++iz) {
    const double zlow = zMin + iz * dz;
    const double zhigh = zlow + dz;
    const double zmid = 0.5 * (zlow + zhigh);
    const double wx = LinearInterpolate(zmid, zMin, totalLength, wxUpstream, wxDownstream);
    const double wy = LinearInterpolate(zmid, zMin, totalLength, wyUpstream, wyDownstream);
    const double rmax = std::hypot(wx / 2.0, wy / 2.0) * safetyFactor;
    const int hBins = static_cast<int>(rmax / dh) + 1;

    for (int ih = 0; ih < hBins; ++ih) {
      const double h = (ih + 0.5) * dh;
      int count = 0;
      for (int ip = 0; ip < phiBins; ++ip) {
        const double phi = ip * dphi;
        const double x = h * cos(phi);
        const double y = h * sin(phi);
        if (std::abs(x) <= wx / 2.0 && std::abs(y) <= wy / 2.0) {
          ++count;
        }
      }
      if (count > 0) {
        bricks.push_back(CylBrick({zmid, h}, dz, dh, count * dphi, 1.0));
      }
    }
  }
  return bricks;
}

std::vector<CylDetLayer> BuildZHRectLayers(const std::vector<std::array<double,5>>& rows) {
  std::vector<CylDetLayer> layers;
  layers.reserve(rows.size());
  for (const auto& r : rows) {
    const std::vector<std::array<double,2>> points = {
        {r[0], r[2]}, {r[1], r[2]}, {r[1], r[3]}, {r[0], r[3]}};
    layers.push_back(CylDetLayer(points, r[4]));
  }
  return layers;
}

std::vector<CylDetLayer> BuildPolarBricksAtFixedZ(
    double zCoord, double dl,
    double hStart, double dh, int hBins,
    double phiStart, double dphi, int phiBins,
    const std::function<bool(double, double)>& insideXY) {
  std::vector<CylDetLayer> bricks;
  if (dh <= 0.0 || dphi <= 0.0 || hBins <= 0 || phiBins <= 0) return bricks;

  for (int ih = 0; ih < hBins; ++ih) {
    const double h = hStart + ih * dh;
    int count = 0;
    for (int ip = 0; ip < phiBins; ++ip) {
      const double phi = phiStart + ip * dphi;
      const double x = -h * cos(phi);
      const double y =  h * sin(phi);
      if (insideXY(x, y)) ++count;
    }
    if (count > 0) bricks.push_back(CylBrick({zCoord, h}, dl, dh, count * dphi, 1.0));
  }
  return bricks;
}

std::vector<CylDetLayer> BuildPolarBricksOverZ(
    double zStart, double dz, int zBins,
    double dl,
    double hStart, double dh, int hBins,
    double phiStart, double dphi, int phiBins,
    const std::function<bool(double, double, double)>& insideXYZ) {
  std::vector<CylDetLayer> bricks;
  if (dz <= 0.0 || dh <= 0.0 || dphi <= 0.0 || zBins <= 0 || hBins <= 0 || phiBins <= 0) return bricks;

  for (int iz = 0; iz < zBins; ++iz) {
    const double z = zStart + iz * dz;
    auto zSlice = BuildPolarBricksAtFixedZ(
        z, dl, hStart, dh, hBins, phiStart, dphi, phiBins,
        [&](double x, double y) { return insideXYZ(z, x, y); });
    bricks.insert(bricks.end(), zSlice.begin(), zSlice.end());
  }
  return bricks;
}
