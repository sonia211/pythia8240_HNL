#include "Pythia8/Pythia.h"
#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TGraph2D.h"
#include "TGraph.h"
#include "TPad.h"
#include "TAxis.h"
#include "TMath.h"
#include <algorithm>
using namespace Pythia8;

// Function declarations
std::vector<std::vector<double>> file_to_vec(string filename);
double U2_to_tau0(double mN, double U2);



int main() {

	int HNL_id = 15;
	int mu2_id=-13; 
	
	int tauMode = 3, tauPol = -1;	 		//pol = +/-1 <=> OS/SS channels
	TString tauMode_s, tauPol_s;
	string tauMode_s2, tauPol_s2;
	
	tauMode_s = std::to_string(tauMode);
	tauMode_s2 = std::to_string(tauMode);
	
	tauPol_s = "polp1";
	tauPol_s2 = std::to_string(tauPol);

	TString HNL_id_s = std::to_string(HNL_id);
	string HNL_id_s2 = std::to_string(HNL_id);
	
	int nEvent = 50000;
	//int nEvent = 200;
	bool scanflag = 0;

	bool cBflag = 1;
	TString cBflag_s = std::to_string(cBflag);
	string cBflag_s2 = std::to_string(cBflag);
	
	
	bool no3mesonflag = 1;
	TString no3mesonflag_s = std::to_string(no3mesonflag);
	
	vector<double> tau0vec, U2vec, mNvec;	

	
	double hbar=6.582119514e-10; //in MeV/s
	
	if (!scanflag){
			tau0vec = {50}; 	// in ps, logarithmique
			mNvec = {3.5};  // in GeV, linear
	}
	else {
		tau0vec = {1., 2., 4., 6., 10., 20., 40., 60., 100., 200., 400., 600.}; 	// in ps, logarithmique
		mNvec = {0.244, 0.50, 0.75, 1.00, 1.25, 1.50, 1.75, 2.00, 2.25, 2.50, 2.75, 3.00, 
				 3.25,  3.50, 3.75, 4.00, 4.25, 4.50, 4.75, 5.00, 5.25, 5.50, 5.75, 6.00};  // in GeV, linear
		
	}

	vector<Double_t> tau0powervec = {0., 3.};
	
	// Histograms or TGraph to fill
	
	TCanvas *cnNP = new TCanvas("cnNP","cnNP",800,600);
	TCanvas *cnND = new TCanvas("cnND","cnND",800,600);
	TCanvas *cnBP = new TCanvas("cnBP","cnBP",800,600);
	TCanvas *crN1 = new TCanvas("crN1","crN1",800,600);
	TCanvas *crN2 = new TCanvas("crN2","crN2",800,600);
	TCanvas *crN1f = new TCanvas("crN1f","crN1f",800,600);
	TCanvas *crN2f = new TCanvas("crN2f","crN2f",800,600);
	

	TH2D *hscan_nNP = new TH2D("hscan_nNP", "hscan_nNP", mNvec.size(), mNvec[0], mNvec.back(), tau0vec.size(), tau0vec[0], tau0vec.back());
	TH2D *hscan_nND1 = new TH2D("hscan_nND1", "hscan_nND1", mNvec.size(), mNvec[0], mNvec.back(), tau0vec.size(), tau0vec[0], tau0vec.back());
	
	TH1D *hscan_nBP = new TH1D("nNB", "Produced B-mesons (scaled)", 50, 510., 544.);
	
	TGraph2D *g1 = new TGraph2D();
	TGraph2D *g2 = new TGraph2D();
	TGraph2D *g1f = new TGraph2D();
	TGraph2D *g2f = new TGraph2D();
	
	// Projections
	TGraph *g1fprojx = new TGraph();
	TGraph *g1fprojy = new TGraph();
	
	TGraph *g2fprojx = new TGraph();
	TGraph *g2fprojy = new TGraph();
	
	// Tools variables 
	int nNP(0), nND1(0), nND2(0);
	double rN1(0.), rN2(0.);
	Double_t mN(0.);
	Double_t tau0(0.);
	int cnt(0);
	
	// Store branching ratio values in vectors
	vector<vector<double> > br_dec_pi_mu =	file_to_vec("../dat_files_tmp/br_dec_pi_mu.dat.dat");
	
	vector<vector<double> > br_prod_B02pimuN =	file_to_vec("../dat_files_tmp/br_prod_B02pimuN.dat");
	vector<vector<double> > br_prod_B02rhomuN = file_to_vec("../dat_files_tmp/br_prod_B02rhomuN.dat");
	vector<vector<double> > br_prod_B02DmuN =	file_to_vec("../dat_files_tmp/br_prod_B02DmuN.dat");
	vector<vector<double> > br_prod_B02DstarmuN= file_to_vec("../dat_files_tmp/br_prod_B02DstarmuN.dat");
	
	
	vector<vector<double> > br_prod_B2D0barmuN =	file_to_vec("../dat_files_tmp/br_prod_B2D0barmuN.dat");
	vector<vector<double> > br_prod_B2D0stbarmuN=	file_to_vec("../dat_files_tmp/br_prod_B2D0stbarmuN.dat");
	vector<vector<double> > br_prod_B2pi0muN =	file_to_vec("../dat_files_tmp/br_prod_B2pi0muN.dat");
	vector<vector<double> > br_prod_B2rho0muN =	file_to_vec("../dat_files_tmp/br_prod_B2rho0muN.dat");
	vector<vector<double> > br_prod_B2muN =		file_to_vec("../dat_files_tmp/br_prod_B2muN.dat");
	
	
	vector<vector<double> > br_prod_Bs2DsmuN= 	file_to_vec("../dat_files_tmp/br_prod_Bs2DsmuN.dat");
	vector<vector<double> > br_prod_Bs2DsstmuN=	file_to_vec("../dat_files_tmp/br_prod_Bs2DsstmuN.dat");
	vector<vector<double> > br_prod_Bs2KmuN=	file_to_vec("../dat_files_tmp/br_prod_Bs2KmuN.dat");
	vector<vector<double> > br_prod_Bs2KstmuN=	file_to_vec("../dat_files_tmp/br_prod_Bs2KstmuN.dat");
	
	vector<vector<double> > br_prod_Bc2muN= 	file_to_vec("../dat_files_tmp/br_prod_Bc2muN.dat");
	
	
	// List of B mesons
	vector<TString> Bids={	"B^{0}", "B^{+} / B^{-}", "B_{s}", "B_{c}" }; 
	
	
	// Mains scan loop
	for (int a(0); a<mNvec.size(); ++a){ // loop on masses
		mN=mNvec[a];
		cout << "mN: " << mN << endl;
		
		for (int b(0); b<tau0vec.size(); ++b){ // loop on lifetimes
			tau0=tau0vec[b];
	
			Pythia pythia; // = Pythia("", false);
		  
			// Shorthand for the event record in pythia. LHC settings.
			Event& event = pythia.event;
			
			ParticleData& particleData = pythia.particleData;
			
			nNP=0; nND1=0; nND2=0;
			
			//List of processes
			
			//pythia.readString("PhaseSpace:showViolation = off");
			pythia.readString("ProcessLevel:all = off");
			//pythia.readString("HadronLevel:Decay=on");
			pythia.readString("Check:event = off");
			
			
			int nAbort = pythia.mode("Main:timesAllowErrors");
			
			
			// HNL properties
			if(HNL_id == 15){
				
				cout << "std::to_string(mN) " << std::to_string(mN) << endl;
				cout << "std::to_string(3e-01*tau0)" << std::to_string(3e-01*tau0) << endl;

				pythia.readString("15:name = N2");
				pythia.readString("15:antiName = N3c");
				pythia.readString("15:chargeType = 0");
				pythia.readString("15:m0 = "+std::to_string(mN));
				pythia.readString("15:tau0 = "+std::to_string(3e-01*tau0));
				pythia.readString("15:oneChannel = 1 1. 1521 13 211");			// HNL decay into mu+- pi-+
				pythia.readString("15:mayDecay=on");
				
				pythia.readString("TauDecays:tauPolarization="+tauPol_s2);
				pythia.readString("TauDecays:mode="+tauMode_s2);
				
				pythia.readString("521:oneChannel = 1 1. 22 "+HNL_id_s2+" -13");	// 2 body decay of the B
				
			}
			if(HNL_id == 25){
				cout << "HIGGS" << endl;
				pythia.readString("TauDecays:mode=0");
				//string HNLstr_m0 = "25:m0 = "+std::to_string(mN); 
				//string HNLstr_tau0 = "25:tau0 = "+std::to_string(3e-01*tau0);
				string HNLstr = "25:new = myHiggs myHiggs 1 0 0 "+std::to_string(mN)+" 0. 0. 0. "+std::to_string(3e-01*tau0);
				
				pythia.readString(HNLstr);
				pythia.readString("25:mayDecay=on");
				pythia.readString("25:oneChannel 1 1. 1 13 211");
				
				//pythia.readString("24:oneChannel = 1 1. 23 -13 15");
				pythia.readString("24:oneChannel = 1 1. 23 -13 15");
				pythia.readString("24:addChannel = 1 1. 23 1 -2");
				pythia.readString("521:oneChannel = 1 1. 22 "+HNL_id_s2+" -13");
			}
				
			

			// Interesting amounts

			
			std::vector<int> B_d_id;		//softer of the two B
			std::vector<int> hB_d_id = {111, 113, 221, 223, 331, -421, -423, -425,-10421,-10423,-20423};	//heavier of the two B
			
			if(cBflag and !no3mesonflag){
				B_d_id = {111, 113, 221, 223, 331, -421, -423, -425};	//B+
				hB_d_id = {421, 423, 441, 443, 511, 513, 533};			//h(heavy) Bc+
			}
			else if(!cBflag and !no3mesonflag){
				B_d_id = {-211, -213, -411, -413, -415};				//B0
				hB_d_id = {-321, -323, -431, -433, -435};				//Bs0
			}
			
			
			//if(!scanflag){
				Double_t B_P2(0),  B_PX(0), B_PY(0), B_PZ(0), B_PT(0), B_E(0);
				Double_t B_M(0),	B_tau(0);
				Double_t B_Xp(0),  B_Yp(0),  B_Zp(0),  B_Tp(0), B_Vp(0);
				Double_t B_Xd(0),  B_Yd(0),  B_Zd(0),  B_Td(0), B_Vd(0);
				Double_t B_Xdiff(0),	B_Ydiff(0),	B_Zdiff(0),  	B_Tdiff(0);
				Double_t B_POL(0),	B_SCALE(0);
				
				Double_t mu1_P2(0),  mu1_PX(0), mu1_PY(0), mu1_PZ(0), mu1_PT(0), mu1_E(0);
				Double_t mu1_M(0),	mu1_tau(0);
				Double_t mu1_Xp(0),  mu1_Yp(0),  mu1_Zp(0),  mu1_Tp(0), mu1_Vp(0);
				Double_t mu1_POL(0), mu1_SCALE(0);
				
				Double_t meson_P2(0),  meson_PX(0), meson_PY(0), meson_PZ(0), meson_PT(0), meson_E(0);
				Double_t meson_M(0),	meson_tau(0);
				Double_t meson_Xp(0),  meson_Yp(0),  meson_Zp(0),  meson_Tp(0), meson_Vp(0);
				Double_t meson_POL(0), meson_SCALE(0);
				
				Double_t mu2_P2(0), mu2_PX(0), mu2_PY(0), mu2_PZ(0), mu2_PT(0), mu2_E(0);
				Double_t mu2_M(0),	mu2_MT(0),	mu2_tau(0);
				Double_t mu2_Xp(0),  mu2_Yp(0),  mu2_Zp(0),  mu2_Tp(0), mu2_Vp(0);
				Double_t mu2_POL(0), mu2_SCALE(0);
			  
				Double_t pi_P2(0),  pi_PX(0), 	pi_PY(0), pi_PZ(0), pi_PT(0), pi_E(0);
				Double_t pi_M(0),	pi_MT(0),	pi_tau(0);
				Double_t pi_Xp(0),  pi_Yp(0),	pi_Zp(0),  pi_Tp(0), pi_Vp(0);
				Double_t pi_Xd(0),  pi_Yd(0),	pi_Zd(0),  pi_Td(0), pi_Vd(0);
				Double_t pi_POL(0),	pi_SCALE(0);
				
				
				Double_t N_P2(0),	N_PX(0), 	N_PY(0),	N_PZ(0), N_PT(0), N_E(0);
				Double_t N_M(0),	N_MT(0),	N_tau(0);
				Double_t N_Xp(0),	N_Yp(0),	N_Zp(0),  	N_Tp(0), N_Vp(0);
				Double_t N_Xd(0),	N_Yd(0),	N_Zd(0),  	N_Td(0), N_Vd(0);
				Double_t N_Xdiff(0),	N_Ydiff(0),	N_Zdiff(0),  	N_Tdiff(0);
				Double_t N_POL(0),	N_SCALE(0);
				
				Double_t nNP(0), nND(0), rN(0);
				
			  
				

				/** Set up the ROOT TFile and TTree, TBranch.  **/
				
				TFile *file;
				if (!scanflag) file = TFile::Open("./tree_Bgun.root","recreate");
				//Event *event = &pythia.event;
				TTree *Tgmo = new TTree("Tgrandmother","mytree");
				TTree *Tmo = new TTree("Tmother","mytree");
				TTree *Tda = new TTree("Tdaughters","mytree");
			  
			
				
				TBranch *b_mu2_PX = Tda->Branch("mu2_PX",&mu2_PX, "mu2_PX/D");
				TBranch *b_mu2_PY = Tda->Branch("mu2_PY",&mu2_PY, "mu2_PY/D");
				TBranch *b_mu2_PZ = Tda->Branch("mu2_PZ",&mu2_PZ, "mu2_PZ/D");
				TBranch *b_mu2_PT = Tda->Branch("mu2_PT",&mu2_PT, "mu2_PT/D");
				TBranch *b_mu2_E  = Tda->Branch("mu2_E",&mu2_E,   "mu2_E/D");
				TBranch *b_mu2_M= Tda->Branch("mu2_M",&mu2_M, "mu2_M/D");

				TBranch *b_mu2_tau= Tda->Branch("mu2_tau",&mu2_tau, "mu2_tau/D");
				TBranch *b_mu2_Xp = Tda->Branch("mu2_Xp",&mu2_Xp, "mu2_Xp/D");
				TBranch *b_mu2_Yp = Tda->Branch("mu2_Yp",&mu2_Yp, "mu2_Yp/D");
				TBranch *b_mu2_Zp = Tda->Branch("mu2_Zp",&mu2_Zp, "mu2_Zp/D");
				TBranch *b_mu2_Tp = Tda->Branch("mu2_Tp",&mu2_Tp, "mu2_Tp/D");
				
				TBranch *b_mu2_POL= Tda->Branch("mu2_POL",&mu2_POL, "mu2_POL/D");
				TBranch *b_mu2_SCALE= Tda->Branch("mu2_SCALE",&mu2_SCALE, "mu2_SCALE/D");
				
				TBranch *b_pi_PX = Tda->Branch("pi_PX",&pi_PX, "pi_PX/D");
				TBranch *b_pi_PY = Tda->Branch("pi_PY",&pi_PY, "pi_PY/D");
				TBranch *b_pi_PZ = Tda->Branch("pi_PZ",&pi_PZ, "pi_PZ/D");
				TBranch *b_pi_PT = Tda->Branch("pi_PT",&pi_PT, "pi_PT/D");
				TBranch *b_pi_E= Tda->Branch("pi_E",&pi_E, "pi_E/D");
				TBranch *b_pi_M= Tda->Branch("pi_M",&pi_M, "pi_M/D");

				TBranch *b_pi_tau= Tda->Branch("pi_tau",&pi_tau, "pi_tau/D");
				TBranch *b_pi_Xp = Tda->Branch("pi_Xp",&pi_Xp, "pi_Xp/D");
				TBranch *b_pi_Yp = Tda->Branch("pi_Yp",&pi_Yp, "pi_Yp/D");
				TBranch *b_pi_Zp = Tda->Branch("pi_Zp",&pi_Zp, "pi_Zp/D");
				TBranch *b_pi_Tp = Tda->Branch("pi_Tp",&pi_Tp, "pi_Tp/D");

				TBranch *b_pi_POL= Tda->Branch("pi_POL",&pi_POL, "pi_POL/D");
				TBranch *b_pi_SCALE= Tda->Branch("pi_SCALE",&pi_SCALE, "pi_SCALE/D");
			
				
				TBranch *b_N_PX = Tmo->Branch("N_PX",&N_PX, "N_PX/D");
				TBranch *b_N_PY = Tmo->Branch("N_PY",&N_PY, "N_PY/D");
				TBranch *b_N_PZ = Tmo->Branch("N_PZ",&N_PZ, "N_PZ/D");
				TBranch *b_N_PT = Tmo->Branch("N_PT",&N_PT, "N_PT/D");
				TBranch *b_N_E= Tmo->Branch("N_E",&N_E, "N_E/D");
				TBranch *b_N_M= Tmo->Branch("N_M",&N_M, "N_M/D");
				TBranch *b_N_MT= Tmo->Branch("N_MT",&N_MT, "N_MT/D");
				TBranch *b_N_POL= Tmo->Branch("N_POL",&N_POL, "N_POL/D");
				TBranch *b_N_SCALE= Tmo->Branch("N_SCALE",&N_SCALE, "N_SCALE/D");
				
				TBranch *b_mu1_PX = Tmo->Branch("mu1_PX",&mu1_PX, "mu1_PX/D");
				TBranch *b_mu1_PY = Tmo->Branch("mu1_PY",&mu1_PY, "mu1_PY/D");
				TBranch *b_mu1_PZ = Tmo->Branch("mu1_PZ",&mu1_PZ, "mu1_PZ/D");
				TBranch *b_mu1_PT = Tmo->Branch("mu1_PT",&mu1_PT, "mu1_PT/D");
				TBranch *b_mu1_E= Tmo->Branch("mu1_E",&mu1_E, "mu1_E/D");
				TBranch *b_mu1_M= Tmo->Branch("mu1_M",&mu1_M, "mu1_M/D");

				TBranch *b_mu1_POL= Tmo->Branch("mu1_POL",&mu1_POL, "mu1_POL/D");
				TBranch *b_mu1_SCALE= Tmo->Branch("mu1_SCALE",&mu1_SCALE, "mu1_SCALE/D");
				
				TBranch *b_B_PX = Tgmo->Branch("B_PX",&B_PX, "B_PX/D");
				TBranch *b_B_PY = Tgmo->Branch("B_PY",&B_PY, "B_PY/D");
				TBranch *b_B_PZ = Tgmo->Branch("B_PZ",&B_PZ, "B_PZ/D");
				TBranch *b_B_PT = Tgmo->Branch("B_PT",&B_PT, "B_PT/D");
				TBranch *b_B_E  = Tgmo->Branch("B_E",&B_E,   "B_E/D");
				TBranch *b_B_M= Tgmo->Branch("B_M",&B_M, "B_M/D");
				
				TBranch *b_B_tau= Tgmo->Branch("B_tau",&B_tau, "B_tau/D");
				TBranch *b_B_Xp = Tgmo->Branch("B_Xp",&B_Xp, "B_Xp/D");
				TBranch *b_B_Yp = Tgmo->Branch("B_Yp",&B_Yp, "B_Yp/D");
				TBranch *b_B_Zp = Tgmo->Branch("B_Zp",&B_Zp, "B_Zp/D");
				TBranch *b_B_Tp = Tgmo->Branch("B_Tp",&B_Tp, "B_Tp/D");

				TBranch *b_B_Xd = Tgmo->Branch("B_Xd",&B_Xd, "B_Xd/D");
				TBranch *b_B_Yd = Tgmo->Branch("B_Yd",&B_Yd, "B_Yd/D");
				TBranch *b_B_Zd = Tgmo->Branch("B_Zd",&B_Zd, "B_Zd/D");
				TBranch *b_B_Td = Tgmo->Branch("B_Td",&B_Td, "B_Td s/D");
				
				TBranch *b_B_POL= Tgmo->Branch("B_POL",&B_POL, "B_POL/D");
				TBranch *b_B_SCALE= Tgmo->Branch("B_SCALE",&B_SCALE, "B_SCALE/D");
		 
			int iAbort = 0;
			int d1, d2;
			//int cnt=0;
			std::vector<int> daughters{};
			std::vector<double> evt_vec;
			
			
			pythia.init(); 					//take its values from the beam specification stored in the Settings database
			for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
				
	
				// Generate events. Quit if many failures.
				if (!pythia.next()) {
					if (++iAbort < nAbort) continue;
					cout << " Event generation aborted prematurely, owing to error!\n";
					break;
				}
		
				//pythia.next();
				pythia.event.reset();
				pythia.event.append(521, 1, 0, 0, 0, 0, 0, 0, 0., 0., 0., 5.279, 5.279, 0, 9);

								
				std::vector<vector<int>> Bdaughters{};
				std::vector<vector<int>> Ndaughters{};
				
				
				// Branch filling
				B_E = pythia.event[1].e();
				B_M = pythia.event[1].m();
				//B_MT = pythia.event[1].mT();
				//B_P2 = pythia.event[1].p2(
				B_PX = pythia.event[1].px();
				B_PY = pythia.event[1].py();
				B_PZ = pythia.event[1].pz();
				B_PT = pythia.event[1].pT();
				B_tau = pythia.event[1].tau();
				Tgmo->Fill();
				

				N_E = pythia.event[2].e();
				N_M = pythia.event[2].m();
				N_MT = pythia.event[2].mT();
				//N_P2 = pythia.event[2].p2(
				N_PX = pythia.event[2].px();
				N_PY = pythia.event[2].py();
				N_PZ = pythia.event[2].pz();
				N_PT = pythia.event[2].pT();
				N_tau = pythia.event[2].tau();
				
				
				mu1_E = pythia.event[3].e();
				mu1_M = pythia.event[3].m();
				//mu1_MT = pythia.event[3].mT();
				//mu1_P2 = pythia.event[3].p2(
				mu1_PX = pythia.event[3].px();
				mu1_PY = pythia.event[3].py();
				mu1_PZ = pythia.event[3].pz();
				mu1_PT = pythia.event[3].pT();
				mu1_tau = pythia.event[3].tau();
				
				
				Tmo->Fill();
					
			//	std::cout << "HNL Status: " << pythia.event[2].status();
				
				// Interesting quantities for N
				mu2_E = pythia.event[4].e();
				mu2_M = pythia.event[4].m();
				mu2_MT = pythia.event[4].mT();
				//mu2_P2 = pythia.event[d1].p2(
				mu2_PX = pythia.event[4].px();
				mu2_PY = pythia.event[4].py();
				mu2_PZ = pythia.event[4].pz();
				mu2_PT = pythia.event[4].pT();
				
				pi_E = pythia.event[5].e();
				pi_M = pythia.event[5].m();
				pi_MT = pythia.event[5].mT();
				//pi_P2 = pythia.event[d1].p2(
				pi_PX = pythia.event[5].px();
				pi_PY = pythia.event[5].py();
				pi_PZ = pythia.event[5].pz();
				pi_PT = pythia.event[5].pT();
				
				Tda->Fill();
				
			}//loop on all events
			
			// Statistics on event generation.
			pythia.stat();

			if(!scanflag){
				//  Write tree.
				Tda->Print();  Tmo->Print(); Tgmo->Print();
				Tda->Write();  Tmo->Write();  Tgmo->Write();
				
				cout << "Tree written !" << endl;
			}
			
			
			else if(scanflag){
				//cout << "\n\n\nrN\ :" << rN1 << endl;
				cout << "\n\ncnt :" << cnt << endl;
				rN1 = (double)nND1/(double)nNP;	
				rN2 = (double)nND2/(double)nNP;	
				
				cout << "\n\nmN :" << mN << endl;
				cout << "\n\ntau0 :" << tau0 << endl;
				g1->SetPoint(cnt, mN, tau0, nND1);
				g1f->SetPoint(cnt, mN, tau0, nND1);
				g1fprojx->SetPoint(cnt, mN, nND1);
				g1fprojy->SetPoint(cnt, tau0, nND1);
				
				/**
				g2->SetPoint(cnt, mN, tau0, rN2);
				g2f->SetPoint(cnt, mN, tau0, rN2);
				g2fprojx->SetPoint(cnt, mN, rN2);
				g2fprojy->SetPoint(cnt, tau0, rN2);
				**/
				
			}
			cout << "cnt avant :" << cnt << endl;
			cnt++;
			cout << "cnt apres :" << cnt << endl;
			
			
			
		}//loop on tau
	}//loop of mN	
	

	
	
	//delete cnNP; delete cnND; delete crN1; delete crN2; delete crN1f; delete crN2f;

	// Done.
	return 0;
}

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

std::vector<std::vector<double> > file_to_vec(std::string filename){
	std::vector<std::vector<double> > br_vec(24,std::vector<double>(9, 0));
	std::ifstream file_br(filename);
	std::string line;
	int i1(0);
	while (std::getline(file_br, line)){

        std::vector<std::string> row_values;
        split(line, ' ', row_values);
        for (int i2(0); i2<row_values.size(); i2++){
			std::string v=row_values[i2];
			br_vec[i1][i2]=atof(v.c_str());
		}
		i1++;
	}

	return br_vec;
}