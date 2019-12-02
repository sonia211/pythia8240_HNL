// Testing HNL "package"

// have to introduce new particle 9013

#include "Pythia8/Pythia.h"
#include "TH1.h"
#include "TCanvas.h"


using namespace Pythia8;

TH1D *h = new TH1D("H","", 100, -1, 1);
TCanvas *c = new TCanvas("c","",800, 600);

int main() {
	// Generator. Process selection. LHC initialization. Histogram.
	Pythia pythia;
    pythia.readString("ProcessLevel:all = off");
    pythia.readString("Check:event = off");


	/*pythia.readString("Beams:eCM = 14000.");
	pythia.readString("HardQCD:all = on");
	pythia.readString("HardQCD:hardbbbar=on");
	pythia.readString("PhaseSpace:pTHatMin = 20.");
	pythia.readString("Next:numberShowEvent=10");
	*/
//	pythia.readString("9013:name = HNL");
//	pythia.readString("9013:antiName = None");
//	pythia.readString("9013:chargeType = 0");
//	pythia.readString("9013:m0 = 3.5");
//	pythia.readString("9013:tau0 = 20.");
//	pythia.readString("9013:oneChannel = 1 1. 1 13 211");
//	pythia.readString("9013:mayDecay=on");
	
	pythia.readString("521:oneChannel = 1 1. 22 9900015 -13");
				
	//pythia.readString("HNLDecays:HNLPolarization="+tauPol_s2);
	pythia.readString("HNLDecays:mode=3");
	pythia.readString("HNLDecays:HNLPolarization=1.");
	//pythia.readString("HNLDecays:HNLExt=2");	
	//pythia.readString("9013:oneChannel = 1 1. 22 111 -13");
  
  
	pythia.init();
  
// Begin event loop. Generate event. Skip if error. List first one.
for (int iEvent = 0; iEvent < 10000; ++iEvent) {
	pythia.event.reset();
    pythia.event.append(521, 1, 0, 0, 0, 0, 0, 0, 0., 0., 0., 5.279, 5.279, 0, 9);
	if (!pythia.next()) continue;
	//std::cout<<"pythia.event.size()"<<pythia.event.size()<<std::endl;
    for (int i = 0; i < pythia.event.size(); ++i){
		if (pythia.event[i].idAbs() == 521){
			//std::cout << "there is a B" << std::endl;
			//std::cout << "status: " << pythia.event[i].status() << std::endl;
		}

		//if (pythia.event[i].idAbs() == 9000014){
             //std::cout << "there is an HNL" << std::endl;
             //std::cout << "status: " << pythia.event[i].status() << std::endl;
             Particle hnl = pythia.event[2];
             Particle muon = pythia.event[4];
             Particle pion = pythia.event[5];

             //std::cout<<"hnl.id(): "<<hnl.id()<<std::endl;
             //std::cout<<"muon.id(): "<<muon.id()<<std::endl;
             //std::cout<<"pion.id(): "<<pion.id()<<std::endl;

             //std::cout<<"muon.theta(): "<<muon.theta()<<std::endl;

             muon.bstback(hnl.p());
             pion.bstback(hnl.p());

             //std::cout<<"muon.theta(): "<<muon.theta()<<std::endl;
             //std::cout<<"cos(muon.theta()): "<<cos(muon.theta())<<std::endl;

             h->Fill(cos(muon.theta()));
         //}
	}


   
  // End of event loop. Statistics. Histogram. Done.
  }
  pythia.stat();
  //cout << mult;

  c->cd();
  h->Draw("hist");
  c->SaveAs("out.root");
  c->SaveAs("out.pdf");


  return 0;
}



