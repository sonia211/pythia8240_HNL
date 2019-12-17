// Testing HNL "package"

// have to introduce new particle 9013

#include "Pythia8/Pythia.h"
#include "TH1.h"
#include "TCanvas.h"


using namespace Pythia8;

TH1D *h = new TH1D("h","", 40, -1, 1);
TH1D *h2 = new TH1D("h2","", 40, -1, 1);
TCanvas *c = new TCanvas("c","",800, 600);
TCanvas *c2 = new TCanvas("c2","",800, 600);

int main() {
	// Generator. Process selection. LHC initialization. Histogram.
	Pythia pythia("", 0);
  pythia.readString("ProcessLevel:all = off");
  pythia.readString("Check:event = off");

  pythia.readString("HNLDecays:mode = 3");
  pythia.readString("HNLDecays:HNLPolarization = 1.");

  
  pythia.readString("9900015:m0 = 3.5"); // in Gev
  pythia.readString("521:oneChannel = 1 1. 22 9900015 -13");


	pythia.init();
  
  // Begin event loop. Generate event. Skip if error. List first one.
  for (int iEvent = 0; iEvent < 5000; ++iEvent) {
	
    pythia.event.reset();
    pythia.event.append(521, 1, 0, 0, 0, 0, 0, 0, 0., 0., 1., sqrt(1+5.279*5.279), 5.279, 0, 9);
    //Synthax is: int Event::append(int id, int status, int mother1, int mother2, int daughter1, int daughter2, int col, int acol, double px, double py, double pz, double e, double m = 0., double scale = 0., double pol = 9.)  
    
    //pythia.event.append(9900015, 1, 0, 0, 0, 0, 0, 0, 0., 0., 0., 4., 4., 0, 9);
	  if (!pythia.next()) continue;
    
    
    Particle B = pythia.event[1];
    Particle hnl = pythia.event[2];
    Particle mu1 = pythia.event[3];
    Particle pi0 = pythia.event[4];
    Particle muon = pythia.event[5];
    Particle pion = pythia.event[6];
    
    
    /**
    Particle hnl = pythia.event[1];
    Particle muon = pythia.event[2];
    Particle pion = pythia.event[3];
    **/
    
    mu1.bstback(B.p());
    muon.bstback(hnl.p());
    pion.bstback(hnl.p());


    h->Fill(cos(muon.theta()));
    h2->Fill(cos(mu1.theta()));

    // End of event loop. Statistics. Histogram. Done.
  }
  pythia.stat();
  //cout << mult;

  c->cd();
  h->GetXaxis()->SetTitle("cos#theta_{#mu_{2}} in HNL restframe");
  h->Draw("hist");
  c->SaveAs("out_mu2.root");
  c->SaveAs("out_mu2.pdf");

  c2->cd();
  h2->GetXaxis()->SetTitle("cos#theta_{#mu_{1}} in HNL restframe");
  h2->Draw("hist");
  c2->SaveAs("out_mu1.root");
  c2->SaveAs("out_mu1.pdf");


  return 0;
}



