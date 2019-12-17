# Updated version of Pythia8: Heavy Neutral Lepton's polarized decay


This is a modified version of Pythia8.240. It incorporates the production of a new type of particle (ID: 9900015), that can be produced. The xml file can be further fulfilled by different production channels. The decay channels of the HNL are let to be defined for the user. The main production and decay channels, as well as their decay width formulas, can be found in [arXiv:]. The implementation in a cxx environment can be found for example in [fabian’s repo]. A branch from sonia211, adding other features such as production channels from B hadrons, is currently WIP.



## Applied changes compared to version

The exhaustive list of addings is the following:

### File `src/HNLDecays.cc`
The HNLDecays class is public TauDecays class and contains basically the same functions. Since tau and HNL are both leptons, most of the handling is similar. In the following there is a quick physics explanation.

Assuming a B+ creates an HNL particle produced together with a positive muon. In the B rest frame, \vec{p(\l+)} = -\vec{p(HNL)}. More over chirality is conserved, so 1=chirality(l+)=-chirality(N). Thus, the polarisations are the same (say pol = +1). Then, if this HNL keeps its negative chirality, it decays into a negatively charged lepton l2- and some positively charged hadron (e.g. pi+). Now due to their pseudo-Dirac nature, they can flip in chirality state (leptonic number violation) and thus changes polarisation as well (pol = -1). In this case it will decays into a positively charred lepton l2+ and some negative hadron (e.g. pi-). In summary, the LNC/LNV nature of HNLs and their possibility to chsage their chirality can be complete driven, in most of cases, by the only polarisation. This was hopefully already coded for tau particles. 

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
*l. Added new data entry for HNL `<particle id="9900015" name="HNL" spinType="2" chargeType="0" colType="0" 
          m0="4.00000" tau0="4e-12">`. The chosen ID 9900015 is the same used as SHiP. The IDs 9900012(14,16) are already used for "resonnances HNL" inside Pythia, that come from a different model. For now only one decay channel is set: `<channel onMode="1" meMode="1521" bRatio="0.5200000" products="13 211"/>`. Obviously this can be further changed in the script by the user. The project would also be to add the list given in Table 5 of [arXiv:1805.08567]
          
### File `share/Pythia8/xmldoc/ParticleDecays.xml`
*l.257: Added some manual lines about the new usable options. This needs to be edited better.

