// Testing HNL "package"

// have to introduce new particle 9013

#include "Pythia8/Pythia.h"
using namespace Pythia8;
int main() {
	// Generator. Process selection. LHC initialization. Histogram.
	Pythia pythia;
	pythia.readString("Beams:eCM = 14000.");
	pythia.readString("HardQCD:all = on");
	pythia.readString("HardQCD:hardbbbar=on");
	pythia.readString("PhaseSpace:pTHatMin = 20.");
	pythia.readString("Next:numberShowEvent=10");
	
	pythia.readString("9013:name = HNL");
	pythia.readString("9013:antiName = None");
	pythia.readString("9013:chargeType = 0");
	pythia.readString("9013:m0 = 3.5");
	pythia.readString("9013:tau0 = 20.");
	pythia.readString("9013:oneChannel = 1 1. 1 13 211");
	pythia.readString("9013:mayDecay=on");
	
	pythia.readString("521:oneChannel = 1 1. 22 9013 -13");
				
	//pythia.readString("HNLDecays:HNLPolarization="+tauPol_s2);
	pythia.readString("HNLDecays:mode=3");
	pythia.readString("HNLDecays:HNLPolarization=1.");
	//pythia.readString("HNLDecays:HNLExt=2");	
	//pythia.readString("9013:oneChannel = 1 1. 22 111 -13");
  
  
	pythia.init();
  
// Begin event loop. Generate event. Skip if error. List first one.
for (int iEvent = 0; iEvent < 100; ++iEvent) {
	if (!pythia.next()) continue;
    for (int i = 0; i < pythia.event.size(); ++i){
		if (pythia.event[i].idAbs() == 521){
			std::cout << "there is a B" << std::endl;
			std::cout << "status: " << pythia.event[i].status() << std::endl;
		}
	}
   
  // End of event loop. Statistics. Histogram. Done.
  }
  pythia.stat();
  //cout << mult;
  return 0;
}



