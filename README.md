# Updated version of Pythia8: Heavy Neutral Lepton's polarized decay


This is a modified version of Pythia v8r240, developped by T. Sjöstrand et. al. 
It incorporates a new type of particle: a Heavy Neutral Lepton (HNL) of mass 1-10 GeV. The chosen ID is 9900015. This HNL was orginally purposed to be produced from beauty hadrons, though the user can add any production or decay channels in its Pythia script. The main production and decay channels, as well as their decay width formulas, can be found in [https://arxiv.org/abs/1805.08567]. Their implementation in a cxx environment, further customed by us for this project, and can be found on [https://github.com/f-thiele/cHNLdecay].



## Applied changes compared to original Pythia 8.240

The list of addings compared to the original version (http://home.thep.lu.se/~torbjorn/pythia8/pythia8240.tgz) is the following:

### File `src/HNLDecays.cc`
The HNLDecays class is public TauDecays class and contains basically the same functions. Since tau and HNL are both massive leptons, most of the handling is similar. In the following there is a quick physics explanation.

Assuming a B+ creates an HNL particle produced together with a positive muon. In the B rest frame, $\vec{p(\l+)} = -\vec{p(HNL)}$. Moreover, chirality is conserved by weak interaction, so 1=chirality(l+)=-chirality(N). Thus, the polarizations are the same (say pol = +1). Then, if this HNL keeps its negative chirality, it decays into a negatively charged lepton l2- and some positively charged hadron (e.g. pi+). Now due to their pseudo-Dirac nature, they can flip in chirality state (leptonic number violation) and thus changes polarisation as well (pol = -1). In this case it will decays into a positively charged lepton l2+ and some negative hadron (e.g. pi-). In summary, the LNC/LNV nature of HNLs and their possibility to change their chirality can be complete driven, in most of cases, by the only polarization. This was hopefully already coded for tau particles, and then reused for HNLs.

The redefined mode are the following (l.80):
* `mode("HNLDecays:externalMode”)`
* `mode(“HNLDecays:mode")`
* `mode("HNLDecays:HNLMother")`
* `parm("HNLDecays:HNLPolarization")`

In the case of one than more sister, the handling for the tau is kept, but with following preferred sisters:
* Mu (ID 13)
* HNL (ID 9900015)
* Charged lepton (ID: 11, 15)
* Neutrino (ID: 12, 14, 16)

### File `src/HNLDecays.h`
Header added with corresponding functions.

### File `share/Pythia8/xmldoc/ParticleData.xml`
* (l.9641): Added new data entry for HNL `<particle id="9900015" name="HNL" spinType="2" chargeType="0" colType="0" 
          m0="4.00000" tau0="4e-12">`. The chosen ID 9900015 is the same used as SHiP. The IDs 9900012(14,16) are already used for "resonnances HNL" inside Pythia, that come from a different model. For now only one decay channel is set: `<channel onMode="1" meMode="1521" bRatio="0.5200000" products="13 211"/>`. Obviously this can be further changed in the script by the user. The project would also be to add the list given in Table 5 of [arXiv:1805.08567].
          
### File `share/Pythia8/xmldoc/ParticleDecays.xml`
* (l.257): Added some manual lines about the new usable options. This needs to be edited better.

## How to use this repository 

Here are the steps to use this code:
* `git clone git@github.com:sonia211/pythia8240_HNL.git` 
* configure Pythi8 with shared libraries and ROOT6 usage (you can use more.): `./configure --enable-shared --with-root=$ROOTSYS` (I use ROOT 6.16.00_2 - a different but close version should be fine)
* to build in clean way in installation directory: `make clean`, then `make -j8`. The variable `ROOTSYS` must be defined to ROOT6 installation directory.
* The folder `$HOME/pythia8240_HNL/examples/` contains a lot of pre-coded main examples that teach the different Pythia functionnalities (some of them with external generators). User's examples files can also be created with the sythax `mymainXX.cc` (XX = numbers 00 to 99), and they are built by `make mymainXX`, and executed with `./mymainXX`

### Minimal working example 

`mymain01.cc` is a minimal working example of use of the new piece of code. 
* It uses the particle `9900015 ` (new HNL) and set HNLPolarization to 1 (can be 1,0,-1) and the HNLmode to 3. The definitions are the same than for TauDecays. The default HNLMode that should be used is the 3. It just means all the HNL should decay with 
* It defines a B particle gun (the line `pythia.event.append(...)`). You should properly define the initial energy and momentum (always give at least one momentum component not zero, otherwise it doesn't work). in your case you shall replace the 521 with bbar ID and proper mass and energy
* In the example of B -> mu1 N(->mu2 pi), the Event vector, containing Particle object, is : [some info, B (or whatever parent particle), mu1, N, mu2, pi].
* It collects the HNL daughters (here there are only 2) and boosts them back in HNL restframe
* It produces two histogram
* If other HNL decay channels are needed, the user should add them following the Pythia8 synthax. In the other hand, HNL is currently only produced from B so the user should precise by hand your production channels as well
* For exemple with eta_b (551): `pythia.readString("551:oneChannel = 1 1. 22 9900015 -13")` for the production)and `pythia.readString("9900015:oneChannel = 1 1. 1521 9900015 -13")` for the decay (22 and 1521 are the decay modes, check http://home.thep.lu.se/~torbjorn/pythia82html/ParticleDecays.html)
* The histograms collect, for each event, the angle between m1 and mu2 for the reaction B+ -> mu_1+ N(->mu_2-/+ pi+/-) in HNL restframe. 

