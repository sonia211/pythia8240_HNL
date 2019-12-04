// Testing HNL "package"

// have to introduce new particle 9013

#include "Pythia8/Pythia.h"
#include "TH1.h"
#include "TCanvas.h"


using namespace Pythia8;

TH1D *h = new TH1D("h","", 40, -1, 1);
TH1D *h2 = new TH1D("h2","", 100, 0, 3.2);
TCanvas *c = new TCanvas("c","",800, 600);
TCanvas *c2 = new TCanvas("c2","",800, 600);

int main() {
	// Generator. Process selection. LHC initialization. Histogram.
	Pythia pythia("", 0);
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
	
	
  //pythia.readString("521:oneChannel = 1 1. 22 15 -13");
				
	//pythia.readString("HNLDecays:HNLPolarization="+tauPol_s2);
  /**
  pythia.readString("15:name = N2");
  pythia.readString("15:antiName = N3c");
  pythia.readString("15:chargeType = 0");
  pythia.readString("15:m0 = 4.");
  pythia.readString("15:tau0 = 3.e-13");
  pythia.readString("15:oneChannel = 1 1. 1521 13 211");      // HNL decay into mu+- pi-+
  pythia.readString("15:mayDecay = on");
  **/
  //pythia.readString("TauDecays:mode = 3");
  //pythia.readString("TauDecays:tauPolarization = 1.");

  
  pythia.readString("9900015:name = N2");
  pythia.readString("9900015:antiName = N3c");
  pythia.readString("9900015:chargeType = 0");
  pythia.readString("9900015:m0 = 3.");
  pythia.readString("9900015:tau0 = 3.e-11");
  pythia.readString("9900015:oneChannel = 1 1. 1521 13 211");      // HNL decay into mu+- pi-+
  pythia.readString("9900015:mayDecay = on");
  
  pythia.readString("HNLDecays:mode = 3");
  pythia.readString("HNLDecays:HNLPolarization = 1.");

  pythia.readString("521:oneChannel = 1 1. 22 9900015 -13");

	//pythia.readString("HNLDecays:HNLExt=2");	
	//pythia.readString("9013:oneChannel = 1 1. 22 111 -13");
  
  
	pythia.init();
  
  // Begin event loop. Generate event. Skip if error. List first one.
  for (int iEvent = 0; iEvent < 30000; ++iEvent) {
	
    pythia.event.reset();
    //pythia.event.append(521, 1, 0, 0, 0, 0, 0, 0, 0., 0., 0., 5.279, 5.279, 0, 9);
    //int Event::append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, double px, double py, double pz, double e, double m = 0., double scale = 0., double pol = 9.)  
    pythia.event.append(9900015, 1, 0, 0, 0, 0, 0, 0, 0., 0., 0., 4., 4., 0, 9);
	  if (!pythia.next()) continue;
    
    /**
    Particle B = pythia.event[1];
    Particle hnl = pythia.event[2];
    Particle muon = pythia.event[4];
    Particle pion = pythia.event[5];
    **/
    
    
    Particle hnl = pythia.event[1];
    Particle muon = pythia.event[2];
    Particle pion = pythia.event[3];
    
    
    //std::cout<<"B.id(): "<<B.id()<<std::endl;
    std::cout<<"hnl.status(): "<<hnl.status()<<std::endl;
    std::cout<<"hnl.id(): "<<hnl.id()<<std::endl;
    std::cout<<"muon.id(): "<<muon.id()<<std::endl;
    std::cout<<"pion.id(): "<<pion.id()<<std::endl;
  

    //std::cout<<"muon.theta(): "<<muon.theta()<<std::endl;
    //muon.bstback(hnl.p());
    pion.bstback(hnl.p());

    //std::cout<<"muon.theta(): "<<muon.theta()<<std::endl;
    //std::cout<<"cos(muon.theta()): "<<cos(muon.theta())<<std::endl;

    h->Fill(cos(muon.theta()));
    h2->Fill(muon.theta());

    // End of event loop. Statistics. Histogram. Done.
  }
  pythia.stat();
  //cout << mult;

  c->cd();
  h->Draw("hist");
  c->SaveAs("out.root");
  c->SaveAs("out.pdf");

  c2->cd();
  h2->Draw("hist");
  c2->SaveAs("out2.root");
  c2->SaveAs("out2.pdf");


  return 0;
}



