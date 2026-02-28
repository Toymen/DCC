/*! \file
 * Definition of the member function passCuts of the analyseEvent class, distributing the cut function to each detector.
*/
#include "include/CAnalyseEvent.h"
#include <iostream>
#include <unordered_map>

/*! \brief
 * The passCuts function looks for the cuts relevant for each detector and applies it to the tested event.
 
 * The individual cut functions are defined in the files describing the corresponding detectors in src/Detectors/ .
*/

bool analyseEvent::passCuts(std::string dettest){
  using CutFn = bool (*)(HepMC::GenEvent*);
  static const std::unordered_map<std::string, CutFn> cutMap = {
#define DETECTOR_ENTRY(NAME, FACTORY_FN, CUTS_FN) {NAME, &CUTS_FN},
#include "include/DetectorRegistry.def"
#undef DETECTOR_ENTRY
  };

  auto it = cutMap.find(dettest);
  if (it == cutMap.end()) {
    return true;
  }
  return it->second(evt);
}
