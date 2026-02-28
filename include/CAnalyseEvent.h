/*! \file
 * Definition of the analyseEvent class, giving access to the cut functions applying to the detectors.
*/
#ifndef _CANALYSEEVENT_
#define _CANALYSEEVENT_

#include <string>
#include "include/detectors.h"

/*! \brief
 * The class analyseEvent allows to apply detector cuts to events.
 
 * It is created from an HepMC event and gives access to the passCuts function, checking the cuts that are relevant for a given detector.
*/

class analyseEvent{

 public:
  analyseEvent(HepMC::GenEvent* evtInput){evt=evtInput;};
  ~analyseEvent(){}
  bool passCuts(std::string dettest);

 private:
  HepMC::GenEvent* evt;
};

#endif
