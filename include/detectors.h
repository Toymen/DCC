#ifndef _DETECTORS_
#define _DETECTORS_

#include <string>
#include <vector>

#include "include/CDetector.h"

namespace HepMC {
class GenEvent;
}

// Centralized declarations generated from DetectorRegistry.def
#define DETECTOR_ENTRY(NAME, FACTORY_FN, CUTS_FN) \
  Detector FACTORY_FN(); \
  bool CUTS_FN(HepMC::GenEvent*);
#include "include/DetectorRegistry.def"
#undef DETECTOR_ENTRY

inline std::vector<std::string> RegisteredDetectorNames() {
  std::vector<std::string> names;
  names.reserve(64);
#define DETECTOR_ENTRY(NAME, FACTORY_FN, CUTS_FN) names.push_back(NAME);
#include "include/DetectorRegistry.def"
#undef DETECTOR_ENTRY
  return names;
}

/*! \brief
 * The CreateDetectors function looks for the detectors from a list (vector) of identifiers
    (strings) and returns a vector of detectors that can be tested against MC events.
 */

std::vector<Detector> CreateDetectors(std::vector<std::string>);

#endif
