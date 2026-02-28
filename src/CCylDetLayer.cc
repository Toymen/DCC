/*! \file
 * Definition of the member functions of the CylDetLayer class.
*/
#include "include/CCylDetLayer.h"
#include "include/CCylSeg.h"
#include <algorithm>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/multi_point.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <cmath>

namespace bg = boost::geometry;

namespace {
using BoostPoint = bg::model::d2::point_xy<double>;
using BoostMultiPoint = bg::model::multi_point<BoostPoint>;
using BoostPolygon = bg::model::polygon<BoostPoint>;
constexpr double kEps = 1e-10;
bool samePoint(const std::array<double,2>& a, const std::array<double,2>& b) {
  return std::abs(a[0] - b[0]) <= kEps && std::abs(a[1] - b[1]) <= kEps;
}
} // namespace

/*! \brief
 * Simple constructor pf the CylDetLayer class.

 * The straightforward constructor of the CylDetLayer class directly takes a vector of oriented cylindrical segments and a weight as input. We do not encourage its use. 
*/

CylDetLayer::CylDetLayer(std::vector<CylSeg> Seglist,double wgh) { 
  CylSegList=Seglist;
  weight=wgh;
}

/*! \brief
 * Advanced constructor of the CylDetLayer class.

 * The 'advanced' constructor reads a list of coordinates (a vector of 2-dim. arrays) in the cylindrical plane {z,h}, together with the weighing factor. It then builds the convex polygonal envelope associated with the coordinates, automatically detecting the orientation of segments with respect to the IP.
*/
 
CylDetLayer::CylDetLayer(std::vector<std::array<double,2>> ptlist,double wgh) { 
  weight=wgh;
  CylSegList.clear();
  auto warn = []() {
    std::cout << "Warning! Something is wrong with the CylDetLayer constructor." << std::endl;
  };

  // Normalize y >= 0 and de-duplicate points.
  std::vector<std::array<double,2>> cleanPts;
  cleanPts.reserve(ptlist.size());
  for (auto p : ptlist) {
    if (p[1] < 0.) p[1] = -p[1];
    bool duplicate = false;
    for (const auto& q : cleanPts) {
      if (samePoint(q, p)) { duplicate = true; break; }
    }
    if (!duplicate) cleanPts.push_back(p);
  }
  if (cleanPts.size() < 3) {
    warn();
    return;
  }

  BoostMultiPoint mpts;
  for (const auto& p : cleanPts) {
    bg::append(mpts, BoostPoint(p[0], p[1]));
  }
  BoostPolygon hull;
  bg::convex_hull(mpts, hull);
  bg::correct(hull);

  const auto& ring = hull.outer();
  std::vector<std::array<double,2>> hullPts;
  hullPts.reserve(ring.size() > 0 ? ring.size() - 1 : 0);
  for (size_t i=0; i + 1 < ring.size(); ++i) {
    hullPts.push_back({bg::get<0>(ring[i]), bg::get<1>(ring[i])});
  } // ring closes by repeating first point
  if (hullPts.size() < 3) {
    warn();
    return;
  }

  // Find indices with max/min theta aperture.
  double thmax = -1.0;
  double thmin = 4. * atan(1.);
  int imax = -1;
  int imin = -1;
  auto theta = [](const std::array<double,2>& p) {
    const double r2 = p[0]*p[0] + p[1]*p[1];
    if (r2 <= kEps) return 0.0;
    return acos(std::clamp(p[0] / sqrt(r2), -1.0, 1.0));
  };
  auto r2 = [](const std::array<double,2>& p) { return p[0]*p[0] + p[1]*p[1]; };
  for (int i=0; i<(int)hullPts.size(); ++i) {
    const double th = theta(hullPts[i]);
    if (th > thmax + kEps || (std::abs(th-thmax) <= kEps && (imax < 0 || r2(hullPts[i]) > r2(hullPts[imax])))) {
      thmax = th;
      imax = i;
    }
    if (th < thmin - kEps || (std::abs(th-thmin) <= kEps && (imin < 0 || r2(hullPts[i]) < r2(hullPts[imin])))) {
      thmin = th;
      imin = i;
    }
  }
  if (imax < 0 || imin < 0 || imax == imin) {
    warn();
    return;
  }

  auto addPath = [&](int start, int end, int sign) {
    int idx = start;
    int guard = 0, n = (int)hullPts.size();
    while (idx != end && guard <= n + 1) {
      int next = (idx + 1) % n;
      CylSegList.push_back(CylSeg(hullPts[idx], hullPts[next], sign));
      idx = next;
      ++guard;
    }
    if (idx != end) warn();
  };
  addPath(imax, imin, -1);
  addPath(imin, imax, 1);
}

/*! \brief
 * Decay probability function for the CylDetLayer class.

 * The inDetDec class function computes the weighed decay probability within the detector layer. 
   It simply sums decay probabilities from the listed cyl. segments and applies an overall weight.
*/
 
double CylDetLayer::inDetDec(double th,double leff) {
  double Pdec=0.;
  if(CylSegList.size()>0 && th>=0 && th<=4.*atan(1.) && leff>0){
   for(int i=0; i<CylSegList.size(); i++) {
    Pdec=Pdec+CylSegList[i].DecProb(th,leff);
   }
   Pdec=weight*Pdec;
  }
  return Pdec;
}
