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
  pythia.readString("PhaseSpace:showViolation = off");
  pythia.readString("Check:event =off");
  pythia.readString("Beams:eCM =14000.");
  pythia.readString("WeakSingleBoson:ffbar2ffbar(s:gm)=on");
  pythia.readString("WeakSingleBoson:ffbar2ffbar(s:gmZ)=on");
  pythia.readString("WeakSingleBoson:ffbar2ffbar(s:W)=on");

  pythia.readString("HardQCD:hardbbbar=on");
  //pythia.readString("PhaseSpace:pTHatMin = 20.");
  pythia.readString("Next:numberShowEvent=10");


  
  pythia.readString("9900015:name = N2");
  pythia.readString("9900015:antiName = N3c");
  pythia.readString("9900015:chargeType = 0");
  pythia.readString("9900015:m0 = 3.");
  pythia.readString("9900015:tau0 = 3.e-11");
  pythia.readString("9900015:oneChannel = 1 1. 1521 13 211");      // HNL decay into mu+- pi-+
  pythia.readString("9900015:mayDecay = on");
  
  pythia.readString("HNLDecays:mode = 3");
  pythia.readString("HNLDecays:HNLPolarization = -1.");

  pythia.readString("521:oneChannel = 1 1. 22 9900015 -13");

	//pythia.readString("HNLDecays:HNLExt=2");	
	//pythia.readString("9013:oneChannel = 1 1. 22 111 -13");
  
  
	pythia.init();
  
  // Begin event loop. Generate event. Skip if error. List first one.
  for (int iEvent = 0; iEvent < 30000; ++iEvent) {
    if (!pythia.next()) continue;
    for(int i(0); i<pythia.event.size(); ++i){
      if(pythia.event[i].idAbs()==9900015){
        std::cout<<"HNL produced, status:"<<pythia.event[i].status()<<std::endl;
        Particle hnl = pythia.event[i];
        std::cout<<"HNL daughter 1 (muon), event no:"<<hnl.daughter1()<<", ID="<<pythia.event[hnl.daughter1()].id()<<std::endl;
        std::cout<<"HNL daughter 2 (pion), event no:"<<hnl.daughter2()<<", ID="<<pythia.event[hnl.daughter2()].id()<<std::endl;
        Particle muon = pythia.event[hnl.daughter1()];
        Particle pion = pythia.event[hnl.daughter2()];
        muon.bstback(hnl.p());
        pion.bstback(hnl.p());

        h->Fill(cos(muon.theta()));
        h2->Fill(muon.theta());
      }//end of if HNL
    }

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



