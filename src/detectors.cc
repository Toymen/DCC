/*! \file
 * Definition of the CreateDetectors function, giving access to the selected detectors.
*/
#include "include/detectors.h"

namespace {
struct DetectorEntry {
  const char* name;
  Detector (*factory)();
};

const std::vector<DetectorEntry>& DetectorRegistry() {
  static const std::vector<DetectorEntry> registry = {
#define DETECTOR_ENTRY(NAME, FACTORY_FN, CUTS_FN) {NAME, &FACTORY_FN},
#include "include/DetectorRegistry.def"
#undef DETECTOR_ENTRY
  };
  return registry;
}
}  // namespace

/*! \fn CreateDetectors
 * The CreateDetectors function looks for the detectors from a list (vector) of
    identifiers (strings) and returns a vector of detectors that can be tested
    against MC events.
   It first declares all known detectors, adding them to the knownDet vector.
    Then it looks at the inputed 'wish-list', compares its elements to the identifiers
    of the known detectors and builds the desired list.
   A log file is copied to bin/Detectors/Detector_log.txt , 
    detailing the success or problems in establishing the list.
*/

//                   LIST OF DETECTORS

std::vector<Detector> CreateDetectors(std::vector<std::string> nameList) {
 std::vector<Detector> myList,knownDet;
 myList.clear();
 knownDet.clear();
 
//   KNOWN DETECTORS
 for (const auto& entry : DetectorRegistry()) {
  knownDet.push_back(entry.factory());
 }

// BUILDING THE LIST OF STUDIED DETECTORS
   std::vector<std::array<double,3>> TDcoord;
   TDcoord.clear(); 
   std::ofstream myfile;
  myfile.open ("Logs/Detector_log.txt");
  myfile << "***************************************************************" << "\n";
  myfile << "***************** WELCOME TO THE DETECTOR LOG *****************" << "\n";
  myfile << "***************************************************************" << "\n";
  myfile << "\n";
  myfile << "Checking the availability of detectors..." << "\n";
  myfile << "\n";
 
 for(int i=0;i<nameList.size();i++){
  std::string searchname=nameList[i];
  bool foundDet=false;
  myfile << "***************************************************************" << "\n";
  myfile << "	Requested detector:	" << searchname << "\n";
  myfile << "***************************************************************" << "\n";
  for(int j=0;j<knownDet.size();j++){
   std::string foundname=knownDet[j].readname();
   if(foundname==searchname){
    if(foundDet){
  myfile << "Warning! Detector " << searchname << " seems to be defined twice!" << "\n";
    }
    if(!foundDet){
     myList.push_back(knownDet[j]);
     foundDet=true;
    }
   }
  }
  if(foundDet){
  myfile << "Detector " << searchname << " was found." << "\n";
  }
  if(!foundDet){
  myfile << "Warning! Detector " << searchname << " does not seem to be declared!" << "\n";
  }
  myfile << "\n";
 }
  myfile << "***************************************************************" << "\n";
  myfile << "\n";
  myfile << "***************************************************************" << "\n";
  myfile << "******************* END OF THE DETECTOR LOG *******************" << "\n";
  myfile << "***************************************************************" << "\n";
  myfile.close();
 
 return myList;
}

