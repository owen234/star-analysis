//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Oct 18 10:32:25 2022 by ROOT version 6.24/07
// from TTree Delphes/Analysis tree
// found on file: test-1M-00.root
//////////////////////////////////////////////////////////

#ifndef event_display1_h
#define event_display1_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"
#include "TObject.h"

class event_display1 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxEvent = 1;
   static constexpr Int_t kMaxParticle = 700;
   static constexpr Int_t kMaxECal = 12;
   static constexpr Int_t kMaxHCal = 13;
   static constexpr Int_t kMaxTower = 19;
   static constexpr Int_t kMaxGenJet05 = 8;
   static constexpr Int_t kMaxGenJet10 = 11;
   static constexpr Int_t kMaxJet05 = 2;
   static constexpr Int_t kMaxJet10 = 2;

   // Declaration of leaf types
   Int_t           Event_;
   UInt_t          Event_fUniqueID[kMaxEvent];   //[Event_]
   UInt_t          Event_fBits[kMaxEvent];   //[Event_]
   Long64_t        Event_Number[kMaxEvent];   //[Event_]
   Float_t         Event_ReadTime[kMaxEvent];   //[Event_]
   Float_t         Event_ProcTime[kMaxEvent];   //[Event_]
   Int_t           Event_ProcessID[kMaxEvent];   //[Event_]
   Int_t           Event_MPI[kMaxEvent];   //[Event_]
   Float_t         Event_Weight[kMaxEvent];   //[Event_]
   Float_t         Event_CrossSection[kMaxEvent];   //[Event_]
   Float_t         Event_CrossSectionError[kMaxEvent];   //[Event_]
   Float_t         Event_Scale[kMaxEvent];   //[Event_]
   Float_t         Event_AlphaQED[kMaxEvent];   //[Event_]
   Float_t         Event_AlphaQCD[kMaxEvent];   //[Event_]
   Int_t           Event_ID1[kMaxEvent];   //[Event_]
   Int_t           Event_ID2[kMaxEvent];   //[Event_]
   Float_t         Event_X1[kMaxEvent];   //[Event_]
   Float_t         Event_X2[kMaxEvent];   //[Event_]
   Float_t         Event_ScalePDF[kMaxEvent];   //[Event_]
   Float_t         Event_PDF1[kMaxEvent];   //[Event_]
   Float_t         Event_PDF2[kMaxEvent];   //[Event_]
   Int_t           Event_size;
   Int_t           Particle_;
   UInt_t          Particle_fUniqueID[kMaxParticle];   //[Particle_]
   UInt_t          Particle_fBits[kMaxParticle];   //[Particle_]
   Int_t           Particle_PID[kMaxParticle];   //[Particle_]
   Int_t           Particle_Status[kMaxParticle];   //[Particle_]
   Int_t           Particle_IsPU[kMaxParticle];   //[Particle_]
   Int_t           Particle_M1[kMaxParticle];   //[Particle_]
   Int_t           Particle_M2[kMaxParticle];   //[Particle_]
   Int_t           Particle_D1[kMaxParticle];   //[Particle_]
   Int_t           Particle_D2[kMaxParticle];   //[Particle_]
   Int_t           Particle_Charge[kMaxParticle];   //[Particle_]
   Float_t         Particle_Mass[kMaxParticle];   //[Particle_]
   Float_t         Particle_E[kMaxParticle];   //[Particle_]
   Float_t         Particle_Px[kMaxParticle];   //[Particle_]
   Float_t         Particle_Py[kMaxParticle];   //[Particle_]
   Float_t         Particle_Pz[kMaxParticle];   //[Particle_]
   Float_t         Particle_P[kMaxParticle];   //[Particle_]
   Float_t         Particle_PT[kMaxParticle];   //[Particle_]
   Float_t         Particle_Eta[kMaxParticle];   //[Particle_]
   Float_t         Particle_Phi[kMaxParticle];   //[Particle_]
   Float_t         Particle_Rapidity[kMaxParticle];   //[Particle_]
   Float_t         Particle_T[kMaxParticle];   //[Particle_]
   Float_t         Particle_X[kMaxParticle];   //[Particle_]
   Float_t         Particle_Y[kMaxParticle];   //[Particle_]
   Float_t         Particle_Z[kMaxParticle];   //[Particle_]
   Int_t           Particle_size;
   Int_t           ECal_;
   UInt_t          ECal_fUniqueID[kMaxECal];   //[ECal_]
   UInt_t          ECal_fBits[kMaxECal];   //[ECal_]
   Float_t         ECal_ET[kMaxECal];   //[ECal_]
   Float_t         ECal_Eta[kMaxECal];   //[ECal_]
   Float_t         ECal_Phi[kMaxECal];   //[ECal_]
   Float_t         ECal_E[kMaxECal];   //[ECal_]
   Float_t         ECal_T[kMaxECal];   //[ECal_]
   Int_t           ECal_NTimeHits[kMaxECal];   //[ECal_]
   Float_t         ECal_Eem[kMaxECal];   //[ECal_]
   Float_t         ECal_Ehad[kMaxECal];   //[ECal_]
   Float_t         ECal_Etrk[kMaxECal];   //[ECal_]
   Float_t         ECal_Edges[kMaxECal][4];   //[ECal_]
   TRefArray       ECal_Particles[kMaxECal];
   Int_t           ECal_size;
   Int_t           HCal_;
   UInt_t          HCal_fUniqueID[kMaxHCal];   //[HCal_]
   UInt_t          HCal_fBits[kMaxHCal];   //[HCal_]
   Float_t         HCal_ET[kMaxHCal];   //[HCal_]
   Float_t         HCal_Eta[kMaxHCal];   //[HCal_]
   Float_t         HCal_Phi[kMaxHCal];   //[HCal_]
   Float_t         HCal_E[kMaxHCal];   //[HCal_]
   Float_t         HCal_T[kMaxHCal];   //[HCal_]
   Int_t           HCal_NTimeHits[kMaxHCal];   //[HCal_]
   Float_t         HCal_Eem[kMaxHCal];   //[HCal_]
   Float_t         HCal_Ehad[kMaxHCal];   //[HCal_]
   Float_t         HCal_Etrk[kMaxHCal];   //[HCal_]
   Float_t         HCal_Edges[kMaxHCal][4];   //[HCal_]
   TRefArray       HCal_Particles[kMaxHCal];
   Int_t           HCal_size;
   Int_t           Tower_;
   UInt_t          Tower_fUniqueID[kMaxTower];   //[Tower_]
   UInt_t          Tower_fBits[kMaxTower];   //[Tower_]
   Float_t         Tower_ET[kMaxTower];   //[Tower_]
   Float_t         Tower_Eta[kMaxTower];   //[Tower_]
   Float_t         Tower_Phi[kMaxTower];   //[Tower_]
   Float_t         Tower_E[kMaxTower];   //[Tower_]
   Float_t         Tower_T[kMaxTower];   //[Tower_]
   Int_t           Tower_NTimeHits[kMaxTower];   //[Tower_]
   Float_t         Tower_Eem[kMaxTower];   //[Tower_]
   Float_t         Tower_Ehad[kMaxTower];   //[Tower_]
   Float_t         Tower_Etrk[kMaxTower];   //[Tower_]
   Float_t         Tower_Edges[kMaxTower][4];   //[Tower_]
   TRefArray       Tower_Particles[kMaxTower];
   Int_t           Tower_size;
   Int_t           GenJet05_;
   UInt_t          GenJet05_fUniqueID[kMaxGenJet05];   //[GenJet05_]
   UInt_t          GenJet05_fBits[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_PT[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_Eta[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_Phi[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_T[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_Mass[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_DeltaEta[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_DeltaPhi[kMaxGenJet05];   //[GenJet05_]
   UInt_t          GenJet05_Flavor[kMaxGenJet05];   //[GenJet05_]
   UInt_t          GenJet05_FlavorAlgo[kMaxGenJet05];   //[GenJet05_]
   UInt_t          GenJet05_FlavorPhys[kMaxGenJet05];   //[GenJet05_]
   UInt_t          GenJet05_BTag[kMaxGenJet05];   //[GenJet05_]
   UInt_t          GenJet05_BTagAlgo[kMaxGenJet05];   //[GenJet05_]
   UInt_t          GenJet05_BTagPhys[kMaxGenJet05];   //[GenJet05_]
   UInt_t          GenJet05_TauTag[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_TauWeight[kMaxGenJet05];   //[GenJet05_]
   Int_t           GenJet05_Charge[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_EhadOverEem[kMaxGenJet05];   //[GenJet05_]
   Int_t           GenJet05_NCharged[kMaxGenJet05];   //[GenJet05_]
   Int_t           GenJet05_NNeutrals[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_NeutralEnergyFraction[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_ChargedEnergyFraction[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_Beta[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_BetaStar[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_MeanSqDeltaR[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_PTD[kMaxGenJet05];   //[GenJet05_]
   Float_t         GenJet05_FracPt[kMaxGenJet05][5];   //[GenJet05_]
   Float_t         GenJet05_Tau[kMaxGenJet05][5];   //[GenJet05_]
   TLorentzVector  GenJet05_SoftDroppedJet[kMaxGenJet05];
   TLorentzVector  GenJet05_SoftDroppedSubJet1[kMaxGenJet05];
   TLorentzVector  GenJet05_SoftDroppedSubJet2[kMaxGenJet05];
   TLorentzVector  GenJet05_TrimmedP4[5][kMaxGenJet05];
   TLorentzVector  GenJet05_PrunedP4[5][kMaxGenJet05];
   TLorentzVector  GenJet05_SoftDroppedP4[5][kMaxGenJet05];
   Int_t           GenJet05_NSubJetsTrimmed[kMaxGenJet05];   //[GenJet05_]
   Int_t           GenJet05_NSubJetsPruned[kMaxGenJet05];   //[GenJet05_]
   Int_t           GenJet05_NSubJetsSoftDropped[kMaxGenJet05];   //[GenJet05_]
   Double_t        GenJet05_ExclYmerge12[kMaxGenJet05];   //[GenJet05_]
   Double_t        GenJet05_ExclYmerge23[kMaxGenJet05];   //[GenJet05_]
   Double_t        GenJet05_ExclYmerge34[kMaxGenJet05];   //[GenJet05_]
   Double_t        GenJet05_ExclYmerge45[kMaxGenJet05];   //[GenJet05_]
   Double_t        GenJet05_ExclYmerge56[kMaxGenJet05];   //[GenJet05_]
   TRefArray       GenJet05_Constituents[kMaxGenJet05];
   TRefArray       GenJet05_Particles[kMaxGenJet05];
   TLorentzVector  GenJet05_Area[kMaxGenJet05];
   Int_t           GenJet05_size;
   Int_t           GenJet10_;
   UInt_t          GenJet10_fUniqueID[kMaxGenJet10];   //[GenJet10_]
   UInt_t          GenJet10_fBits[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_PT[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_Eta[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_Phi[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_T[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_Mass[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_DeltaEta[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_DeltaPhi[kMaxGenJet10];   //[GenJet10_]
   UInt_t          GenJet10_Flavor[kMaxGenJet10];   //[GenJet10_]
   UInt_t          GenJet10_FlavorAlgo[kMaxGenJet10];   //[GenJet10_]
   UInt_t          GenJet10_FlavorPhys[kMaxGenJet10];   //[GenJet10_]
   UInt_t          GenJet10_BTag[kMaxGenJet10];   //[GenJet10_]
   UInt_t          GenJet10_BTagAlgo[kMaxGenJet10];   //[GenJet10_]
   UInt_t          GenJet10_BTagPhys[kMaxGenJet10];   //[GenJet10_]
   UInt_t          GenJet10_TauTag[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_TauWeight[kMaxGenJet10];   //[GenJet10_]
   Int_t           GenJet10_Charge[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_EhadOverEem[kMaxGenJet10];   //[GenJet10_]
   Int_t           GenJet10_NCharged[kMaxGenJet10];   //[GenJet10_]
   Int_t           GenJet10_NNeutrals[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_NeutralEnergyFraction[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_ChargedEnergyFraction[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_Beta[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_BetaStar[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_MeanSqDeltaR[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_PTD[kMaxGenJet10];   //[GenJet10_]
   Float_t         GenJet10_FracPt[kMaxGenJet10][5];   //[GenJet10_]
   Float_t         GenJet10_Tau[kMaxGenJet10][5];   //[GenJet10_]
   TLorentzVector  GenJet10_SoftDroppedJet[kMaxGenJet10];
   TLorentzVector  GenJet10_SoftDroppedSubJet1[kMaxGenJet10];
   TLorentzVector  GenJet10_SoftDroppedSubJet2[kMaxGenJet10];
   TLorentzVector  GenJet10_TrimmedP4[5][kMaxGenJet10];
   TLorentzVector  GenJet10_PrunedP4[5][kMaxGenJet10];
   TLorentzVector  GenJet10_SoftDroppedP4[5][kMaxGenJet10];
   Int_t           GenJet10_NSubJetsTrimmed[kMaxGenJet10];   //[GenJet10_]
   Int_t           GenJet10_NSubJetsPruned[kMaxGenJet10];   //[GenJet10_]
   Int_t           GenJet10_NSubJetsSoftDropped[kMaxGenJet10];   //[GenJet10_]
   Double_t        GenJet10_ExclYmerge12[kMaxGenJet10];   //[GenJet10_]
   Double_t        GenJet10_ExclYmerge23[kMaxGenJet10];   //[GenJet10_]
   Double_t        GenJet10_ExclYmerge34[kMaxGenJet10];   //[GenJet10_]
   Double_t        GenJet10_ExclYmerge45[kMaxGenJet10];   //[GenJet10_]
   Double_t        GenJet10_ExclYmerge56[kMaxGenJet10];   //[GenJet10_]
   TRefArray       GenJet10_Constituents[kMaxGenJet10];
   TRefArray       GenJet10_Particles[kMaxGenJet10];
   TLorentzVector  GenJet10_Area[kMaxGenJet10];
   Int_t           GenJet10_size;
   Int_t           Jet05_;
   UInt_t          Jet05_fUniqueID[kMaxJet05];   //[Jet05_]
   UInt_t          Jet05_fBits[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_PT[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_Eta[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_Phi[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_T[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_Mass[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_DeltaEta[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_DeltaPhi[kMaxJet05];   //[Jet05_]
   UInt_t          Jet05_Flavor[kMaxJet05];   //[Jet05_]
   UInt_t          Jet05_FlavorAlgo[kMaxJet05];   //[Jet05_]
   UInt_t          Jet05_FlavorPhys[kMaxJet05];   //[Jet05_]
   UInt_t          Jet05_BTag[kMaxJet05];   //[Jet05_]
   UInt_t          Jet05_BTagAlgo[kMaxJet05];   //[Jet05_]
   UInt_t          Jet05_BTagPhys[kMaxJet05];   //[Jet05_]
   UInt_t          Jet05_TauTag[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_TauWeight[kMaxJet05];   //[Jet05_]
   Int_t           Jet05_Charge[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_EhadOverEem[kMaxJet05];   //[Jet05_]
   Int_t           Jet05_NCharged[kMaxJet05];   //[Jet05_]
   Int_t           Jet05_NNeutrals[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_NeutralEnergyFraction[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_ChargedEnergyFraction[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_Beta[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_BetaStar[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_MeanSqDeltaR[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_PTD[kMaxJet05];   //[Jet05_]
   Float_t         Jet05_FracPt[kMaxJet05][5];   //[Jet05_]
   Float_t         Jet05_Tau[kMaxJet05][5];   //[Jet05_]
   TLorentzVector  Jet05_SoftDroppedJet[kMaxJet05];
   TLorentzVector  Jet05_SoftDroppedSubJet1[kMaxJet05];
   TLorentzVector  Jet05_SoftDroppedSubJet2[kMaxJet05];
   TLorentzVector  Jet05_TrimmedP4[5][kMaxJet05];
   TLorentzVector  Jet05_PrunedP4[5][kMaxJet05];
   TLorentzVector  Jet05_SoftDroppedP4[5][kMaxJet05];
   Int_t           Jet05_NSubJetsTrimmed[kMaxJet05];   //[Jet05_]
   Int_t           Jet05_NSubJetsPruned[kMaxJet05];   //[Jet05_]
   Int_t           Jet05_NSubJetsSoftDropped[kMaxJet05];   //[Jet05_]
   Double_t        Jet05_ExclYmerge12[kMaxJet05];   //[Jet05_]
   Double_t        Jet05_ExclYmerge23[kMaxJet05];   //[Jet05_]
   Double_t        Jet05_ExclYmerge34[kMaxJet05];   //[Jet05_]
   Double_t        Jet05_ExclYmerge45[kMaxJet05];   //[Jet05_]
   Double_t        Jet05_ExclYmerge56[kMaxJet05];   //[Jet05_]
   TRefArray       Jet05_Constituents[kMaxJet05];
   TRefArray       Jet05_Particles[kMaxJet05];
   TLorentzVector  Jet05_Area[kMaxJet05];
   Int_t           Jet05_size;
   Int_t           Jet10_;
   UInt_t          Jet10_fUniqueID[kMaxJet10];   //[Jet10_]
   UInt_t          Jet10_fBits[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_PT[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_Eta[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_Phi[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_T[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_Mass[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_DeltaEta[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_DeltaPhi[kMaxJet10];   //[Jet10_]
   UInt_t          Jet10_Flavor[kMaxJet10];   //[Jet10_]
   UInt_t          Jet10_FlavorAlgo[kMaxJet10];   //[Jet10_]
   UInt_t          Jet10_FlavorPhys[kMaxJet10];   //[Jet10_]
   UInt_t          Jet10_BTag[kMaxJet10];   //[Jet10_]
   UInt_t          Jet10_BTagAlgo[kMaxJet10];   //[Jet10_]
   UInt_t          Jet10_BTagPhys[kMaxJet10];   //[Jet10_]
   UInt_t          Jet10_TauTag[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_TauWeight[kMaxJet10];   //[Jet10_]
   Int_t           Jet10_Charge[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_EhadOverEem[kMaxJet10];   //[Jet10_]
   Int_t           Jet10_NCharged[kMaxJet10];   //[Jet10_]
   Int_t           Jet10_NNeutrals[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_NeutralEnergyFraction[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_ChargedEnergyFraction[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_Beta[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_BetaStar[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_MeanSqDeltaR[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_PTD[kMaxJet10];   //[Jet10_]
   Float_t         Jet10_FracPt[kMaxJet10][5];   //[Jet10_]
   Float_t         Jet10_Tau[kMaxJet10][5];   //[Jet10_]
   TLorentzVector  Jet10_SoftDroppedJet[kMaxJet10];
   TLorentzVector  Jet10_SoftDroppedSubJet1[kMaxJet10];
   TLorentzVector  Jet10_SoftDroppedSubJet2[kMaxJet10];
   TLorentzVector  Jet10_TrimmedP4[5][kMaxJet10];
   TLorentzVector  Jet10_PrunedP4[5][kMaxJet10];
   TLorentzVector  Jet10_SoftDroppedP4[5][kMaxJet10];
   Int_t           Jet10_NSubJetsTrimmed[kMaxJet10];   //[Jet10_]
   Int_t           Jet10_NSubJetsPruned[kMaxJet10];   //[Jet10_]
   Int_t           Jet10_NSubJetsSoftDropped[kMaxJet10];   //[Jet10_]
   Double_t        Jet10_ExclYmerge12[kMaxJet10];   //[Jet10_]
   Double_t        Jet10_ExclYmerge23[kMaxJet10];   //[Jet10_]
   Double_t        Jet10_ExclYmerge34[kMaxJet10];   //[Jet10_]
   Double_t        Jet10_ExclYmerge45[kMaxJet10];   //[Jet10_]
   Double_t        Jet10_ExclYmerge56[kMaxJet10];   //[Jet10_]
   TRefArray       Jet10_Constituents[kMaxJet10];
   TRefArray       Jet10_Particles[kMaxJet10];
   TLorentzVector  Jet10_Area[kMaxJet10];
   Int_t           Jet10_size;

   // List of branches
   TBranch        *b_Event_;   //!
   TBranch        *b_Event_fUniqueID;   //!
   TBranch        *b_Event_fBits;   //!
   TBranch        *b_Event_Number;   //!
   TBranch        *b_Event_ReadTime;   //!
   TBranch        *b_Event_ProcTime;   //!
   TBranch        *b_Event_ProcessID;   //!
   TBranch        *b_Event_MPI;   //!
   TBranch        *b_Event_Weight;   //!
   TBranch        *b_Event_CrossSection;   //!
   TBranch        *b_Event_CrossSectionError;   //!
   TBranch        *b_Event_Scale;   //!
   TBranch        *b_Event_AlphaQED;   //!
   TBranch        *b_Event_AlphaQCD;   //!
   TBranch        *b_Event_ID1;   //!
   TBranch        *b_Event_ID2;   //!
   TBranch        *b_Event_X1;   //!
   TBranch        *b_Event_X2;   //!
   TBranch        *b_Event_ScalePDF;   //!
   TBranch        *b_Event_PDF1;   //!
   TBranch        *b_Event_PDF2;   //!
   TBranch        *b_Event_size;   //!
   TBranch        *b_Particle_;   //!
   TBranch        *b_Particle_fUniqueID;   //!
   TBranch        *b_Particle_fBits;   //!
   TBranch        *b_Particle_PID;   //!
   TBranch        *b_Particle_Status;   //!
   TBranch        *b_Particle_IsPU;   //!
   TBranch        *b_Particle_M1;   //!
   TBranch        *b_Particle_M2;   //!
   TBranch        *b_Particle_D1;   //!
   TBranch        *b_Particle_D2;   //!
   TBranch        *b_Particle_Charge;   //!
   TBranch        *b_Particle_Mass;   //!
   TBranch        *b_Particle_E;   //!
   TBranch        *b_Particle_Px;   //!
   TBranch        *b_Particle_Py;   //!
   TBranch        *b_Particle_Pz;   //!
   TBranch        *b_Particle_P;   //!
   TBranch        *b_Particle_PT;   //!
   TBranch        *b_Particle_Eta;   //!
   TBranch        *b_Particle_Phi;   //!
   TBranch        *b_Particle_Rapidity;   //!
   TBranch        *b_Particle_T;   //!
   TBranch        *b_Particle_X;   //!
   TBranch        *b_Particle_Y;   //!
   TBranch        *b_Particle_Z;   //!
   TBranch        *b_Particle_size;   //!
   TBranch        *b_ECal_;   //!
   TBranch        *b_ECal_fUniqueID;   //!
   TBranch        *b_ECal_fBits;   //!
   TBranch        *b_ECal_ET;   //!
   TBranch        *b_ECal_Eta;   //!
   TBranch        *b_ECal_Phi;   //!
   TBranch        *b_ECal_E;   //!
   TBranch        *b_ECal_T;   //!
   TBranch        *b_ECal_NTimeHits;   //!
   TBranch        *b_ECal_Eem;   //!
   TBranch        *b_ECal_Ehad;   //!
   TBranch        *b_ECal_Etrk;   //!
   TBranch        *b_ECal_Edges;   //!
   TBranch        *b_ECal_Particles;   //!
   TBranch        *b_ECal_size;   //!
   TBranch        *b_HCal_;   //!
   TBranch        *b_HCal_fUniqueID;   //!
   TBranch        *b_HCal_fBits;   //!
   TBranch        *b_HCal_ET;   //!
   TBranch        *b_HCal_Eta;   //!
   TBranch        *b_HCal_Phi;   //!
   TBranch        *b_HCal_E;   //!
   TBranch        *b_HCal_T;   //!
   TBranch        *b_HCal_NTimeHits;   //!
   TBranch        *b_HCal_Eem;   //!
   TBranch        *b_HCal_Ehad;   //!
   TBranch        *b_HCal_Etrk;   //!
   TBranch        *b_HCal_Edges;   //!
   TBranch        *b_HCal_Particles;   //!
   TBranch        *b_HCal_size;   //!
   TBranch        *b_Tower_;   //!
   TBranch        *b_Tower_fUniqueID;   //!
   TBranch        *b_Tower_fBits;   //!
   TBranch        *b_Tower_ET;   //!
   TBranch        *b_Tower_Eta;   //!
   TBranch        *b_Tower_Phi;   //!
   TBranch        *b_Tower_E;   //!
   TBranch        *b_Tower_T;   //!
   TBranch        *b_Tower_NTimeHits;   //!
   TBranch        *b_Tower_Eem;   //!
   TBranch        *b_Tower_Ehad;   //!
   TBranch        *b_Tower_Etrk;   //!
   TBranch        *b_Tower_Edges;   //!
   TBranch        *b_Tower_Particles;   //!
   TBranch        *b_Tower_size;   //!
   TBranch        *b_GenJet05_;   //!
   TBranch        *b_GenJet05_fUniqueID;   //!
   TBranch        *b_GenJet05_fBits;   //!
   TBranch        *b_GenJet05_PT;   //!
   TBranch        *b_GenJet05_Eta;   //!
   TBranch        *b_GenJet05_Phi;   //!
   TBranch        *b_GenJet05_T;   //!
   TBranch        *b_GenJet05_Mass;   //!
   TBranch        *b_GenJet05_DeltaEta;   //!
   TBranch        *b_GenJet05_DeltaPhi;   //!
   TBranch        *b_GenJet05_Flavor;   //!
   TBranch        *b_GenJet05_FlavorAlgo;   //!
   TBranch        *b_GenJet05_FlavorPhys;   //!
   TBranch        *b_GenJet05_BTag;   //!
   TBranch        *b_GenJet05_BTagAlgo;   //!
   TBranch        *b_GenJet05_BTagPhys;   //!
   TBranch        *b_GenJet05_TauTag;   //!
   TBranch        *b_GenJet05_TauWeight;   //!
   TBranch        *b_GenJet05_Charge;   //!
   TBranch        *b_GenJet05_EhadOverEem;   //!
   TBranch        *b_GenJet05_NCharged;   //!
   TBranch        *b_GenJet05_NNeutrals;   //!
   TBranch        *b_GenJet05_NeutralEnergyFraction;   //!
   TBranch        *b_GenJet05_ChargedEnergyFraction;   //!
   TBranch        *b_GenJet05_Beta;   //!
   TBranch        *b_GenJet05_BetaStar;   //!
   TBranch        *b_GenJet05_MeanSqDeltaR;   //!
   TBranch        *b_GenJet05_PTD;   //!
   TBranch        *b_GenJet05_FracPt;   //!
   TBranch        *b_GenJet05_Tau;   //!
   TBranch        *b_GenJet05_SoftDroppedJet;   //!
   TBranch        *b_GenJet05_SoftDroppedSubJet1;   //!
   TBranch        *b_GenJet05_SoftDroppedSubJet2;   //!
   TBranch        *b_GenJet05_TrimmedP4;   //!
   TBranch        *b_GenJet05_PrunedP4;   //!
   TBranch        *b_GenJet05_SoftDroppedP4;   //!
   TBranch        *b_GenJet05_NSubJetsTrimmed;   //!
   TBranch        *b_GenJet05_NSubJetsPruned;   //!
   TBranch        *b_GenJet05_NSubJetsSoftDropped;   //!
   TBranch        *b_GenJet05_ExclYmerge12;   //!
   TBranch        *b_GenJet05_ExclYmerge23;   //!
   TBranch        *b_GenJet05_ExclYmerge34;   //!
   TBranch        *b_GenJet05_ExclYmerge45;   //!
   TBranch        *b_GenJet05_ExclYmerge56;   //!
   TBranch        *b_GenJet05_Constituents;   //!
   TBranch        *b_GenJet05_Particles;   //!
   TBranch        *b_GenJet05_Area;   //!
   TBranch        *b_GenJet05_size;   //!
   TBranch        *b_GenJet10_;   //!
   TBranch        *b_GenJet10_fUniqueID;   //!
   TBranch        *b_GenJet10_fBits;   //!
   TBranch        *b_GenJet10_PT;   //!
   TBranch        *b_GenJet10_Eta;   //!
   TBranch        *b_GenJet10_Phi;   //!
   TBranch        *b_GenJet10_T;   //!
   TBranch        *b_GenJet10_Mass;   //!
   TBranch        *b_GenJet10_DeltaEta;   //!
   TBranch        *b_GenJet10_DeltaPhi;   //!
   TBranch        *b_GenJet10_Flavor;   //!
   TBranch        *b_GenJet10_FlavorAlgo;   //!
   TBranch        *b_GenJet10_FlavorPhys;   //!
   TBranch        *b_GenJet10_BTag;   //!
   TBranch        *b_GenJet10_BTagAlgo;   //!
   TBranch        *b_GenJet10_BTagPhys;   //!
   TBranch        *b_GenJet10_TauTag;   //!
   TBranch        *b_GenJet10_TauWeight;   //!
   TBranch        *b_GenJet10_Charge;   //!
   TBranch        *b_GenJet10_EhadOverEem;   //!
   TBranch        *b_GenJet10_NCharged;   //!
   TBranch        *b_GenJet10_NNeutrals;   //!
   TBranch        *b_GenJet10_NeutralEnergyFraction;   //!
   TBranch        *b_GenJet10_ChargedEnergyFraction;   //!
   TBranch        *b_GenJet10_Beta;   //!
   TBranch        *b_GenJet10_BetaStar;   //!
   TBranch        *b_GenJet10_MeanSqDeltaR;   //!
   TBranch        *b_GenJet10_PTD;   //!
   TBranch        *b_GenJet10_FracPt;   //!
   TBranch        *b_GenJet10_Tau;   //!
   TBranch        *b_GenJet10_SoftDroppedJet;   //!
   TBranch        *b_GenJet10_SoftDroppedSubJet1;   //!
   TBranch        *b_GenJet10_SoftDroppedSubJet2;   //!
   TBranch        *b_GenJet10_TrimmedP4;   //!
   TBranch        *b_GenJet10_PrunedP4;   //!
   TBranch        *b_GenJet10_SoftDroppedP4;   //!
   TBranch        *b_GenJet10_NSubJetsTrimmed;   //!
   TBranch        *b_GenJet10_NSubJetsPruned;   //!
   TBranch        *b_GenJet10_NSubJetsSoftDropped;   //!
   TBranch        *b_GenJet10_ExclYmerge12;   //!
   TBranch        *b_GenJet10_ExclYmerge23;   //!
   TBranch        *b_GenJet10_ExclYmerge34;   //!
   TBranch        *b_GenJet10_ExclYmerge45;   //!
   TBranch        *b_GenJet10_ExclYmerge56;   //!
   TBranch        *b_GenJet10_Constituents;   //!
   TBranch        *b_GenJet10_Particles;   //!
   TBranch        *b_GenJet10_Area;   //!
   TBranch        *b_GenJet10_size;   //!
   TBranch        *b_Jet05_;   //!
   TBranch        *b_Jet05_fUniqueID;   //!
   TBranch        *b_Jet05_fBits;   //!
   TBranch        *b_Jet05_PT;   //!
   TBranch        *b_Jet05_Eta;   //!
   TBranch        *b_Jet05_Phi;   //!
   TBranch        *b_Jet05_T;   //!
   TBranch        *b_Jet05_Mass;   //!
   TBranch        *b_Jet05_DeltaEta;   //!
   TBranch        *b_Jet05_DeltaPhi;   //!
   TBranch        *b_Jet05_Flavor;   //!
   TBranch        *b_Jet05_FlavorAlgo;   //!
   TBranch        *b_Jet05_FlavorPhys;   //!
   TBranch        *b_Jet05_BTag;   //!
   TBranch        *b_Jet05_BTagAlgo;   //!
   TBranch        *b_Jet05_BTagPhys;   //!
   TBranch        *b_Jet05_TauTag;   //!
   TBranch        *b_Jet05_TauWeight;   //!
   TBranch        *b_Jet05_Charge;   //!
   TBranch        *b_Jet05_EhadOverEem;   //!
   TBranch        *b_Jet05_NCharged;   //!
   TBranch        *b_Jet05_NNeutrals;   //!
   TBranch        *b_Jet05_NeutralEnergyFraction;   //!
   TBranch        *b_Jet05_ChargedEnergyFraction;   //!
   TBranch        *b_Jet05_Beta;   //!
   TBranch        *b_Jet05_BetaStar;   //!
   TBranch        *b_Jet05_MeanSqDeltaR;   //!
   TBranch        *b_Jet05_PTD;   //!
   TBranch        *b_Jet05_FracPt;   //!
   TBranch        *b_Jet05_Tau;   //!
   TBranch        *b_Jet05_SoftDroppedJet;   //!
   TBranch        *b_Jet05_SoftDroppedSubJet1;   //!
   TBranch        *b_Jet05_SoftDroppedSubJet2;   //!
   TBranch        *b_Jet05_TrimmedP4;   //!
   TBranch        *b_Jet05_PrunedP4;   //!
   TBranch        *b_Jet05_SoftDroppedP4;   //!
   TBranch        *b_Jet05_NSubJetsTrimmed;   //!
   TBranch        *b_Jet05_NSubJetsPruned;   //!
   TBranch        *b_Jet05_NSubJetsSoftDropped;   //!
   TBranch        *b_Jet05_ExclYmerge12;   //!
   TBranch        *b_Jet05_ExclYmerge23;   //!
   TBranch        *b_Jet05_ExclYmerge34;   //!
   TBranch        *b_Jet05_ExclYmerge45;   //!
   TBranch        *b_Jet05_ExclYmerge56;   //!
   TBranch        *b_Jet05_Constituents;   //!
   TBranch        *b_Jet05_Particles;   //!
   TBranch        *b_Jet05_Area;   //!
   TBranch        *b_Jet05_size;   //!
   TBranch        *b_Jet10_;   //!
   TBranch        *b_Jet10_fUniqueID;   //!
   TBranch        *b_Jet10_fBits;   //!
   TBranch        *b_Jet10_PT;   //!
   TBranch        *b_Jet10_Eta;   //!
   TBranch        *b_Jet10_Phi;   //!
   TBranch        *b_Jet10_T;   //!
   TBranch        *b_Jet10_Mass;   //!
   TBranch        *b_Jet10_DeltaEta;   //!
   TBranch        *b_Jet10_DeltaPhi;   //!
   TBranch        *b_Jet10_Flavor;   //!
   TBranch        *b_Jet10_FlavorAlgo;   //!
   TBranch        *b_Jet10_FlavorPhys;   //!
   TBranch        *b_Jet10_BTag;   //!
   TBranch        *b_Jet10_BTagAlgo;   //!
   TBranch        *b_Jet10_BTagPhys;   //!
   TBranch        *b_Jet10_TauTag;   //!
   TBranch        *b_Jet10_TauWeight;   //!
   TBranch        *b_Jet10_Charge;   //!
   TBranch        *b_Jet10_EhadOverEem;   //!
   TBranch        *b_Jet10_NCharged;   //!
   TBranch        *b_Jet10_NNeutrals;   //!
   TBranch        *b_Jet10_NeutralEnergyFraction;   //!
   TBranch        *b_Jet10_ChargedEnergyFraction;   //!
   TBranch        *b_Jet10_Beta;   //!
   TBranch        *b_Jet10_BetaStar;   //!
   TBranch        *b_Jet10_MeanSqDeltaR;   //!
   TBranch        *b_Jet10_PTD;   //!
   TBranch        *b_Jet10_FracPt;   //!
   TBranch        *b_Jet10_Tau;   //!
   TBranch        *b_Jet10_SoftDroppedJet;   //!
   TBranch        *b_Jet10_SoftDroppedSubJet1;   //!
   TBranch        *b_Jet10_SoftDroppedSubJet2;   //!
   TBranch        *b_Jet10_TrimmedP4;   //!
   TBranch        *b_Jet10_PrunedP4;   //!
   TBranch        *b_Jet10_SoftDroppedP4;   //!
   TBranch        *b_Jet10_NSubJetsTrimmed;   //!
   TBranch        *b_Jet10_NSubJetsPruned;   //!
   TBranch        *b_Jet10_NSubJetsSoftDropped;   //!
   TBranch        *b_Jet10_ExclYmerge12;   //!
   TBranch        *b_Jet10_ExclYmerge23;   //!
   TBranch        *b_Jet10_ExclYmerge34;   //!
   TBranch        *b_Jet10_ExclYmerge45;   //!
   TBranch        *b_Jet10_ExclYmerge56;   //!
   TBranch        *b_Jet10_Constituents;   //!
   TBranch        *b_Jet10_Particles;   //!
   TBranch        *b_Jet10_Area;   //!
   TBranch        *b_Jet10_size;   //!

   event_display1(TTree *tree=0);
   virtual ~event_display1();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef event_display1_cxx
event_display1::event_display1(TTree *tree) : fChain(0) 
{
   TChain* ch = new TChain("Delphes") ;
 //---------
   //ch->Add("../../delphes/delphes/output-rjf-2jR-pthat5.0-jpt2-allgp-30x10M-2022-10-21a/*.root") ;
   //ch->Add("../../delphes/delphes/output-rjf-2jR-pthat5.0-jpt3-allgp-30x10M-2022-10-21a/*.root") ;
   //ch->Add("../../delphes/delphes/output-rjf-pthat0.0-jpt2.0-allgp-30x10M-2022-10-22a/*.root") ;
   //ch->Add("../../delphes/delphes/output-rjf-2jR-pthat0.0-jpt3-30x50M-2022-10-23a/*.root") ;
   //ch->Add("../../delphes/delphes/output-rjf-2jR-pthat0.0-jpt3-allgp-30x50M-2022-10-18a/*.root") ;
   ch->Add("../../delphes/delphes/output-rjf-2jR-pthat5.0-jpt3-allgp-30x10M-2022-10-21a/*.root") ;

   tree = ch ;

   Init(tree);
}

event_display1::~event_display1()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t event_display1::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t event_display1::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void event_display1::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Event", &Event_, &b_Event_);
   fChain->SetBranchAddress("Event.fUniqueID", Event_fUniqueID, &b_Event_fUniqueID);
   fChain->SetBranchAddress("Event.fBits", Event_fBits, &b_Event_fBits);
   fChain->SetBranchAddress("Event.Number", Event_Number, &b_Event_Number);
   fChain->SetBranchAddress("Event.ReadTime", Event_ReadTime, &b_Event_ReadTime);
   fChain->SetBranchAddress("Event.ProcTime", Event_ProcTime, &b_Event_ProcTime);
   fChain->SetBranchAddress("Event.ProcessID", Event_ProcessID, &b_Event_ProcessID);
   fChain->SetBranchAddress("Event.MPI", Event_MPI, &b_Event_MPI);
   fChain->SetBranchAddress("Event.Weight", Event_Weight, &b_Event_Weight);
   fChain->SetBranchAddress("Event.CrossSection", Event_CrossSection, &b_Event_CrossSection);
   fChain->SetBranchAddress("Event.CrossSectionError", Event_CrossSectionError, &b_Event_CrossSectionError);
   fChain->SetBranchAddress("Event.Scale", Event_Scale, &b_Event_Scale);
   fChain->SetBranchAddress("Event.AlphaQED", Event_AlphaQED, &b_Event_AlphaQED);
   fChain->SetBranchAddress("Event.AlphaQCD", Event_AlphaQCD, &b_Event_AlphaQCD);
   fChain->SetBranchAddress("Event.ID1", Event_ID1, &b_Event_ID1);
   fChain->SetBranchAddress("Event.ID2", Event_ID2, &b_Event_ID2);
   fChain->SetBranchAddress("Event.X1", Event_X1, &b_Event_X1);
   fChain->SetBranchAddress("Event.X2", Event_X2, &b_Event_X2);
   fChain->SetBranchAddress("Event.ScalePDF", Event_ScalePDF, &b_Event_ScalePDF);
   fChain->SetBranchAddress("Event.PDF1", Event_PDF1, &b_Event_PDF1);
   fChain->SetBranchAddress("Event.PDF2", Event_PDF2, &b_Event_PDF2);
   fChain->SetBranchAddress("Event_size", &Event_size, &b_Event_size);
   fChain->SetBranchAddress("Particle", &Particle_, &b_Particle_);
   fChain->SetBranchAddress("Particle.fUniqueID", Particle_fUniqueID, &b_Particle_fUniqueID);
   fChain->SetBranchAddress("Particle.fBits", Particle_fBits, &b_Particle_fBits);
   fChain->SetBranchAddress("Particle.PID", Particle_PID, &b_Particle_PID);
   fChain->SetBranchAddress("Particle.Status", Particle_Status, &b_Particle_Status);
   fChain->SetBranchAddress("Particle.IsPU", Particle_IsPU, &b_Particle_IsPU);
   fChain->SetBranchAddress("Particle.M1", Particle_M1, &b_Particle_M1);
   fChain->SetBranchAddress("Particle.M2", Particle_M2, &b_Particle_M2);
   fChain->SetBranchAddress("Particle.D1", Particle_D1, &b_Particle_D1);
   fChain->SetBranchAddress("Particle.D2", Particle_D2, &b_Particle_D2);
   fChain->SetBranchAddress("Particle.Charge", Particle_Charge, &b_Particle_Charge);
   fChain->SetBranchAddress("Particle.Mass", Particle_Mass, &b_Particle_Mass);
   fChain->SetBranchAddress("Particle.E", Particle_E, &b_Particle_E);
   fChain->SetBranchAddress("Particle.Px", Particle_Px, &b_Particle_Px);
   fChain->SetBranchAddress("Particle.Py", Particle_Py, &b_Particle_Py);
   fChain->SetBranchAddress("Particle.Pz", Particle_Pz, &b_Particle_Pz);
   fChain->SetBranchAddress("Particle.P", Particle_P, &b_Particle_P);
   fChain->SetBranchAddress("Particle.PT", Particle_PT, &b_Particle_PT);
   fChain->SetBranchAddress("Particle.Eta", Particle_Eta, &b_Particle_Eta);
   fChain->SetBranchAddress("Particle.Phi", Particle_Phi, &b_Particle_Phi);
   fChain->SetBranchAddress("Particle.Rapidity", Particle_Rapidity, &b_Particle_Rapidity);
   fChain->SetBranchAddress("Particle.T", Particle_T, &b_Particle_T);
   fChain->SetBranchAddress("Particle.X", Particle_X, &b_Particle_X);
   fChain->SetBranchAddress("Particle.Y", Particle_Y, &b_Particle_Y);
   fChain->SetBranchAddress("Particle.Z", Particle_Z, &b_Particle_Z);
   fChain->SetBranchAddress("Particle_size", &Particle_size, &b_Particle_size);
   fChain->SetBranchAddress("ECal", &ECal_, &b_ECal_);
   fChain->SetBranchAddress("ECal.fUniqueID", ECal_fUniqueID, &b_ECal_fUniqueID);
   fChain->SetBranchAddress("ECal.fBits", ECal_fBits, &b_ECal_fBits);
   fChain->SetBranchAddress("ECal.ET", ECal_ET, &b_ECal_ET);
   fChain->SetBranchAddress("ECal.Eta", ECal_Eta, &b_ECal_Eta);
   fChain->SetBranchAddress("ECal.Phi", ECal_Phi, &b_ECal_Phi);
   fChain->SetBranchAddress("ECal.E", ECal_E, &b_ECal_E);
   fChain->SetBranchAddress("ECal.T", ECal_T, &b_ECal_T);
   fChain->SetBranchAddress("ECal.NTimeHits", ECal_NTimeHits, &b_ECal_NTimeHits);
   fChain->SetBranchAddress("ECal.Eem", ECal_Eem, &b_ECal_Eem);
   fChain->SetBranchAddress("ECal.Ehad", ECal_Ehad, &b_ECal_Ehad);
   fChain->SetBranchAddress("ECal.Etrk", ECal_Etrk, &b_ECal_Etrk);
   fChain->SetBranchAddress("ECal.Edges[4]", ECal_Edges, &b_ECal_Edges);
   fChain->SetBranchAddress("ECal.Particles", ECal_Particles, &b_ECal_Particles);
   fChain->SetBranchAddress("ECal_size", &ECal_size, &b_ECal_size);
   fChain->SetBranchAddress("HCal", &HCal_, &b_HCal_);
   fChain->SetBranchAddress("HCal.fUniqueID", HCal_fUniqueID, &b_HCal_fUniqueID);
   fChain->SetBranchAddress("HCal.fBits", HCal_fBits, &b_HCal_fBits);
   fChain->SetBranchAddress("HCal.ET", HCal_ET, &b_HCal_ET);
   fChain->SetBranchAddress("HCal.Eta", HCal_Eta, &b_HCal_Eta);
   fChain->SetBranchAddress("HCal.Phi", HCal_Phi, &b_HCal_Phi);
   fChain->SetBranchAddress("HCal.E", HCal_E, &b_HCal_E);
   fChain->SetBranchAddress("HCal.T", HCal_T, &b_HCal_T);
   fChain->SetBranchAddress("HCal.NTimeHits", HCal_NTimeHits, &b_HCal_NTimeHits);
   fChain->SetBranchAddress("HCal.Eem", HCal_Eem, &b_HCal_Eem);
   fChain->SetBranchAddress("HCal.Ehad", HCal_Ehad, &b_HCal_Ehad);
   fChain->SetBranchAddress("HCal.Etrk", HCal_Etrk, &b_HCal_Etrk);
   fChain->SetBranchAddress("HCal.Edges[4]", HCal_Edges, &b_HCal_Edges);
   fChain->SetBranchAddress("HCal.Particles", HCal_Particles, &b_HCal_Particles);
   fChain->SetBranchAddress("HCal_size", &HCal_size, &b_HCal_size);
   fChain->SetBranchAddress("Tower", &Tower_, &b_Tower_);
   fChain->SetBranchAddress("Tower.fUniqueID", Tower_fUniqueID, &b_Tower_fUniqueID);
   fChain->SetBranchAddress("Tower.fBits", Tower_fBits, &b_Tower_fBits);
   fChain->SetBranchAddress("Tower.ET", Tower_ET, &b_Tower_ET);
   fChain->SetBranchAddress("Tower.Eta", Tower_Eta, &b_Tower_Eta);
   fChain->SetBranchAddress("Tower.Phi", Tower_Phi, &b_Tower_Phi);
   fChain->SetBranchAddress("Tower.E", Tower_E, &b_Tower_E);
   fChain->SetBranchAddress("Tower.T", Tower_T, &b_Tower_T);
   fChain->SetBranchAddress("Tower.NTimeHits", Tower_NTimeHits, &b_Tower_NTimeHits);
   fChain->SetBranchAddress("Tower.Eem", Tower_Eem, &b_Tower_Eem);
   fChain->SetBranchAddress("Tower.Ehad", Tower_Ehad, &b_Tower_Ehad);
   fChain->SetBranchAddress("Tower.Etrk", Tower_Etrk, &b_Tower_Etrk);
   fChain->SetBranchAddress("Tower.Edges[4]", Tower_Edges, &b_Tower_Edges);
   fChain->SetBranchAddress("Tower.Particles", Tower_Particles, &b_Tower_Particles);
   fChain->SetBranchAddress("Tower_size", &Tower_size, &b_Tower_size);
   fChain->SetBranchAddress("GenJet05", &GenJet05_, &b_GenJet05_);
   fChain->SetBranchAddress("GenJet05.fUniqueID", GenJet05_fUniqueID, &b_GenJet05_fUniqueID);
   fChain->SetBranchAddress("GenJet05.fBits", GenJet05_fBits, &b_GenJet05_fBits);
   fChain->SetBranchAddress("GenJet05.PT", GenJet05_PT, &b_GenJet05_PT);
   fChain->SetBranchAddress("GenJet05.Eta", GenJet05_Eta, &b_GenJet05_Eta);
   fChain->SetBranchAddress("GenJet05.Phi", GenJet05_Phi, &b_GenJet05_Phi);
   fChain->SetBranchAddress("GenJet05.T", GenJet05_T, &b_GenJet05_T);
   fChain->SetBranchAddress("GenJet05.Mass", GenJet05_Mass, &b_GenJet05_Mass);
   fChain->SetBranchAddress("GenJet05.DeltaEta", GenJet05_DeltaEta, &b_GenJet05_DeltaEta);
   fChain->SetBranchAddress("GenJet05.DeltaPhi", GenJet05_DeltaPhi, &b_GenJet05_DeltaPhi);
   fChain->SetBranchAddress("GenJet05.Flavor", GenJet05_Flavor, &b_GenJet05_Flavor);
   fChain->SetBranchAddress("GenJet05.FlavorAlgo", GenJet05_FlavorAlgo, &b_GenJet05_FlavorAlgo);
   fChain->SetBranchAddress("GenJet05.FlavorPhys", GenJet05_FlavorPhys, &b_GenJet05_FlavorPhys);
   fChain->SetBranchAddress("GenJet05.BTag", GenJet05_BTag, &b_GenJet05_BTag);
   fChain->SetBranchAddress("GenJet05.BTagAlgo", GenJet05_BTagAlgo, &b_GenJet05_BTagAlgo);
   fChain->SetBranchAddress("GenJet05.BTagPhys", GenJet05_BTagPhys, &b_GenJet05_BTagPhys);
   fChain->SetBranchAddress("GenJet05.TauTag", GenJet05_TauTag, &b_GenJet05_TauTag);
   fChain->SetBranchAddress("GenJet05.TauWeight", GenJet05_TauWeight, &b_GenJet05_TauWeight);
   fChain->SetBranchAddress("GenJet05.Charge", GenJet05_Charge, &b_GenJet05_Charge);
   fChain->SetBranchAddress("GenJet05.EhadOverEem", GenJet05_EhadOverEem, &b_GenJet05_EhadOverEem);
   fChain->SetBranchAddress("GenJet05.NCharged", GenJet05_NCharged, &b_GenJet05_NCharged);
   fChain->SetBranchAddress("GenJet05.NNeutrals", GenJet05_NNeutrals, &b_GenJet05_NNeutrals);
   fChain->SetBranchAddress("GenJet05.NeutralEnergyFraction", GenJet05_NeutralEnergyFraction, &b_GenJet05_NeutralEnergyFraction);
   fChain->SetBranchAddress("GenJet05.ChargedEnergyFraction", GenJet05_ChargedEnergyFraction, &b_GenJet05_ChargedEnergyFraction);
   fChain->SetBranchAddress("GenJet05.Beta", GenJet05_Beta, &b_GenJet05_Beta);
   fChain->SetBranchAddress("GenJet05.BetaStar", GenJet05_BetaStar, &b_GenJet05_BetaStar);
   fChain->SetBranchAddress("GenJet05.MeanSqDeltaR", GenJet05_MeanSqDeltaR, &b_GenJet05_MeanSqDeltaR);
   fChain->SetBranchAddress("GenJet05.PTD", GenJet05_PTD, &b_GenJet05_PTD);
   fChain->SetBranchAddress("GenJet05.FracPt[5]", GenJet05_FracPt, &b_GenJet05_FracPt);
   fChain->SetBranchAddress("GenJet05.Tau[5]", GenJet05_Tau, &b_GenJet05_Tau);
   fChain->SetBranchAddress("GenJet05.SoftDroppedJet", GenJet05_SoftDroppedJet, &b_GenJet05_SoftDroppedJet);
   fChain->SetBranchAddress("GenJet05.SoftDroppedSubJet1", GenJet05_SoftDroppedSubJet1, &b_GenJet05_SoftDroppedSubJet1);
   fChain->SetBranchAddress("GenJet05.SoftDroppedSubJet2", GenJet05_SoftDroppedSubJet2, &b_GenJet05_SoftDroppedSubJet2);
   fChain->SetBranchAddress("GenJet05.TrimmedP4[5]", GenJet05_TrimmedP4, &b_GenJet05_TrimmedP4);
   fChain->SetBranchAddress("GenJet05.PrunedP4[5]", GenJet05_PrunedP4, &b_GenJet05_PrunedP4);
   fChain->SetBranchAddress("GenJet05.SoftDroppedP4[5]", GenJet05_SoftDroppedP4, &b_GenJet05_SoftDroppedP4);
   fChain->SetBranchAddress("GenJet05.NSubJetsTrimmed", GenJet05_NSubJetsTrimmed, &b_GenJet05_NSubJetsTrimmed);
   fChain->SetBranchAddress("GenJet05.NSubJetsPruned", GenJet05_NSubJetsPruned, &b_GenJet05_NSubJetsPruned);
   fChain->SetBranchAddress("GenJet05.NSubJetsSoftDropped", GenJet05_NSubJetsSoftDropped, &b_GenJet05_NSubJetsSoftDropped);
   fChain->SetBranchAddress("GenJet05.ExclYmerge12", GenJet05_ExclYmerge12, &b_GenJet05_ExclYmerge12);
   fChain->SetBranchAddress("GenJet05.ExclYmerge23", GenJet05_ExclYmerge23, &b_GenJet05_ExclYmerge23);
   fChain->SetBranchAddress("GenJet05.ExclYmerge34", GenJet05_ExclYmerge34, &b_GenJet05_ExclYmerge34);
   fChain->SetBranchAddress("GenJet05.ExclYmerge45", GenJet05_ExclYmerge45, &b_GenJet05_ExclYmerge45);
   fChain->SetBranchAddress("GenJet05.ExclYmerge56", GenJet05_ExclYmerge56, &b_GenJet05_ExclYmerge56);
   fChain->SetBranchAddress("GenJet05.Constituents", GenJet05_Constituents, &b_GenJet05_Constituents);
   fChain->SetBranchAddress("GenJet05.Particles", GenJet05_Particles, &b_GenJet05_Particles);
   fChain->SetBranchAddress("GenJet05.Area", GenJet05_Area, &b_GenJet05_Area);
   fChain->SetBranchAddress("GenJet05_size", &GenJet05_size, &b_GenJet05_size);
   fChain->SetBranchAddress("GenJet10", &GenJet10_, &b_GenJet10_);
   fChain->SetBranchAddress("GenJet10.fUniqueID", GenJet10_fUniqueID, &b_GenJet10_fUniqueID);
   fChain->SetBranchAddress("GenJet10.fBits", GenJet10_fBits, &b_GenJet10_fBits);
   fChain->SetBranchAddress("GenJet10.PT", GenJet10_PT, &b_GenJet10_PT);
   fChain->SetBranchAddress("GenJet10.Eta", GenJet10_Eta, &b_GenJet10_Eta);
   fChain->SetBranchAddress("GenJet10.Phi", GenJet10_Phi, &b_GenJet10_Phi);
   fChain->SetBranchAddress("GenJet10.T", GenJet10_T, &b_GenJet10_T);
   fChain->SetBranchAddress("GenJet10.Mass", GenJet10_Mass, &b_GenJet10_Mass);
   fChain->SetBranchAddress("GenJet10.DeltaEta", GenJet10_DeltaEta, &b_GenJet10_DeltaEta);
   fChain->SetBranchAddress("GenJet10.DeltaPhi", GenJet10_DeltaPhi, &b_GenJet10_DeltaPhi);
   fChain->SetBranchAddress("GenJet10.Flavor", GenJet10_Flavor, &b_GenJet10_Flavor);
   fChain->SetBranchAddress("GenJet10.FlavorAlgo", GenJet10_FlavorAlgo, &b_GenJet10_FlavorAlgo);
   fChain->SetBranchAddress("GenJet10.FlavorPhys", GenJet10_FlavorPhys, &b_GenJet10_FlavorPhys);
   fChain->SetBranchAddress("GenJet10.BTag", GenJet10_BTag, &b_GenJet10_BTag);
   fChain->SetBranchAddress("GenJet10.BTagAlgo", GenJet10_BTagAlgo, &b_GenJet10_BTagAlgo);
   fChain->SetBranchAddress("GenJet10.BTagPhys", GenJet10_BTagPhys, &b_GenJet10_BTagPhys);
   fChain->SetBranchAddress("GenJet10.TauTag", GenJet10_TauTag, &b_GenJet10_TauTag);
   fChain->SetBranchAddress("GenJet10.TauWeight", GenJet10_TauWeight, &b_GenJet10_TauWeight);
   fChain->SetBranchAddress("GenJet10.Charge", GenJet10_Charge, &b_GenJet10_Charge);
   fChain->SetBranchAddress("GenJet10.EhadOverEem", GenJet10_EhadOverEem, &b_GenJet10_EhadOverEem);
   fChain->SetBranchAddress("GenJet10.NCharged", GenJet10_NCharged, &b_GenJet10_NCharged);
   fChain->SetBranchAddress("GenJet10.NNeutrals", GenJet10_NNeutrals, &b_GenJet10_NNeutrals);
   fChain->SetBranchAddress("GenJet10.NeutralEnergyFraction", GenJet10_NeutralEnergyFraction, &b_GenJet10_NeutralEnergyFraction);
   fChain->SetBranchAddress("GenJet10.ChargedEnergyFraction", GenJet10_ChargedEnergyFraction, &b_GenJet10_ChargedEnergyFraction);
   fChain->SetBranchAddress("GenJet10.Beta", GenJet10_Beta, &b_GenJet10_Beta);
   fChain->SetBranchAddress("GenJet10.BetaStar", GenJet10_BetaStar, &b_GenJet10_BetaStar);
   fChain->SetBranchAddress("GenJet10.MeanSqDeltaR", GenJet10_MeanSqDeltaR, &b_GenJet10_MeanSqDeltaR);
   fChain->SetBranchAddress("GenJet10.PTD", GenJet10_PTD, &b_GenJet10_PTD);
   fChain->SetBranchAddress("GenJet10.FracPt[5]", GenJet10_FracPt, &b_GenJet10_FracPt);
   fChain->SetBranchAddress("GenJet10.Tau[5]", GenJet10_Tau, &b_GenJet10_Tau);
   fChain->SetBranchAddress("GenJet10.SoftDroppedJet", GenJet10_SoftDroppedJet, &b_GenJet10_SoftDroppedJet);
   fChain->SetBranchAddress("GenJet10.SoftDroppedSubJet1", GenJet10_SoftDroppedSubJet1, &b_GenJet10_SoftDroppedSubJet1);
   fChain->SetBranchAddress("GenJet10.SoftDroppedSubJet2", GenJet10_SoftDroppedSubJet2, &b_GenJet10_SoftDroppedSubJet2);
   fChain->SetBranchAddress("GenJet10.TrimmedP4[5]", GenJet10_TrimmedP4, &b_GenJet10_TrimmedP4);
   fChain->SetBranchAddress("GenJet10.PrunedP4[5]", GenJet10_PrunedP4, &b_GenJet10_PrunedP4);
   fChain->SetBranchAddress("GenJet10.SoftDroppedP4[5]", GenJet10_SoftDroppedP4, &b_GenJet10_SoftDroppedP4);
   fChain->SetBranchAddress("GenJet10.NSubJetsTrimmed", GenJet10_NSubJetsTrimmed, &b_GenJet10_NSubJetsTrimmed);
   fChain->SetBranchAddress("GenJet10.NSubJetsPruned", GenJet10_NSubJetsPruned, &b_GenJet10_NSubJetsPruned);
   fChain->SetBranchAddress("GenJet10.NSubJetsSoftDropped", GenJet10_NSubJetsSoftDropped, &b_GenJet10_NSubJetsSoftDropped);
   fChain->SetBranchAddress("GenJet10.ExclYmerge12", GenJet10_ExclYmerge12, &b_GenJet10_ExclYmerge12);
   fChain->SetBranchAddress("GenJet10.ExclYmerge23", GenJet10_ExclYmerge23, &b_GenJet10_ExclYmerge23);
   fChain->SetBranchAddress("GenJet10.ExclYmerge34", GenJet10_ExclYmerge34, &b_GenJet10_ExclYmerge34);
   fChain->SetBranchAddress("GenJet10.ExclYmerge45", GenJet10_ExclYmerge45, &b_GenJet10_ExclYmerge45);
   fChain->SetBranchAddress("GenJet10.ExclYmerge56", GenJet10_ExclYmerge56, &b_GenJet10_ExclYmerge56);
   fChain->SetBranchAddress("GenJet10.Constituents", GenJet10_Constituents, &b_GenJet10_Constituents);
   fChain->SetBranchAddress("GenJet10.Particles", GenJet10_Particles, &b_GenJet10_Particles);
   fChain->SetBranchAddress("GenJet10.Area", GenJet10_Area, &b_GenJet10_Area);
   fChain->SetBranchAddress("GenJet10_size", &GenJet10_size, &b_GenJet10_size);
   fChain->SetBranchAddress("Jet05", &Jet05_, &b_Jet05_);
   fChain->SetBranchAddress("Jet05.fUniqueID", Jet05_fUniqueID, &b_Jet05_fUniqueID);
   fChain->SetBranchAddress("Jet05.fBits", Jet05_fBits, &b_Jet05_fBits);
   fChain->SetBranchAddress("Jet05.PT", Jet05_PT, &b_Jet05_PT);
   fChain->SetBranchAddress("Jet05.Eta", Jet05_Eta, &b_Jet05_Eta);
   fChain->SetBranchAddress("Jet05.Phi", Jet05_Phi, &b_Jet05_Phi);
   fChain->SetBranchAddress("Jet05.T", Jet05_T, &b_Jet05_T);
   fChain->SetBranchAddress("Jet05.Mass", Jet05_Mass, &b_Jet05_Mass);
   fChain->SetBranchAddress("Jet05.DeltaEta", Jet05_DeltaEta, &b_Jet05_DeltaEta);
   fChain->SetBranchAddress("Jet05.DeltaPhi", Jet05_DeltaPhi, &b_Jet05_DeltaPhi);
   fChain->SetBranchAddress("Jet05.Flavor", Jet05_Flavor, &b_Jet05_Flavor);
   fChain->SetBranchAddress("Jet05.FlavorAlgo", Jet05_FlavorAlgo, &b_Jet05_FlavorAlgo);
   fChain->SetBranchAddress("Jet05.FlavorPhys", Jet05_FlavorPhys, &b_Jet05_FlavorPhys);
   fChain->SetBranchAddress("Jet05.BTag", Jet05_BTag, &b_Jet05_BTag);
   fChain->SetBranchAddress("Jet05.BTagAlgo", Jet05_BTagAlgo, &b_Jet05_BTagAlgo);
   fChain->SetBranchAddress("Jet05.BTagPhys", Jet05_BTagPhys, &b_Jet05_BTagPhys);
   fChain->SetBranchAddress("Jet05.TauTag", Jet05_TauTag, &b_Jet05_TauTag);
   fChain->SetBranchAddress("Jet05.TauWeight", Jet05_TauWeight, &b_Jet05_TauWeight);
   fChain->SetBranchAddress("Jet05.Charge", Jet05_Charge, &b_Jet05_Charge);
   fChain->SetBranchAddress("Jet05.EhadOverEem", Jet05_EhadOverEem, &b_Jet05_EhadOverEem);
   fChain->SetBranchAddress("Jet05.NCharged", Jet05_NCharged, &b_Jet05_NCharged);
   fChain->SetBranchAddress("Jet05.NNeutrals", Jet05_NNeutrals, &b_Jet05_NNeutrals);
   fChain->SetBranchAddress("Jet05.NeutralEnergyFraction", Jet05_NeutralEnergyFraction, &b_Jet05_NeutralEnergyFraction);
   fChain->SetBranchAddress("Jet05.ChargedEnergyFraction", Jet05_ChargedEnergyFraction, &b_Jet05_ChargedEnergyFraction);
   fChain->SetBranchAddress("Jet05.Beta", Jet05_Beta, &b_Jet05_Beta);
   fChain->SetBranchAddress("Jet05.BetaStar", Jet05_BetaStar, &b_Jet05_BetaStar);
   fChain->SetBranchAddress("Jet05.MeanSqDeltaR", Jet05_MeanSqDeltaR, &b_Jet05_MeanSqDeltaR);
   fChain->SetBranchAddress("Jet05.PTD", Jet05_PTD, &b_Jet05_PTD);
   fChain->SetBranchAddress("Jet05.FracPt[5]", Jet05_FracPt, &b_Jet05_FracPt);
   fChain->SetBranchAddress("Jet05.Tau[5]", Jet05_Tau, &b_Jet05_Tau);
   fChain->SetBranchAddress("Jet05.SoftDroppedJet", Jet05_SoftDroppedJet, &b_Jet05_SoftDroppedJet);
   fChain->SetBranchAddress("Jet05.SoftDroppedSubJet1", Jet05_SoftDroppedSubJet1, &b_Jet05_SoftDroppedSubJet1);
   fChain->SetBranchAddress("Jet05.SoftDroppedSubJet2", Jet05_SoftDroppedSubJet2, &b_Jet05_SoftDroppedSubJet2);
   fChain->SetBranchAddress("Jet05.TrimmedP4[5]", Jet05_TrimmedP4, &b_Jet05_TrimmedP4);
   fChain->SetBranchAddress("Jet05.PrunedP4[5]", Jet05_PrunedP4, &b_Jet05_PrunedP4);
   fChain->SetBranchAddress("Jet05.SoftDroppedP4[5]", Jet05_SoftDroppedP4, &b_Jet05_SoftDroppedP4);
   fChain->SetBranchAddress("Jet05.NSubJetsTrimmed", Jet05_NSubJetsTrimmed, &b_Jet05_NSubJetsTrimmed);
   fChain->SetBranchAddress("Jet05.NSubJetsPruned", Jet05_NSubJetsPruned, &b_Jet05_NSubJetsPruned);
   fChain->SetBranchAddress("Jet05.NSubJetsSoftDropped", Jet05_NSubJetsSoftDropped, &b_Jet05_NSubJetsSoftDropped);
   fChain->SetBranchAddress("Jet05.ExclYmerge12", Jet05_ExclYmerge12, &b_Jet05_ExclYmerge12);
   fChain->SetBranchAddress("Jet05.ExclYmerge23", Jet05_ExclYmerge23, &b_Jet05_ExclYmerge23);
   fChain->SetBranchAddress("Jet05.ExclYmerge34", Jet05_ExclYmerge34, &b_Jet05_ExclYmerge34);
   fChain->SetBranchAddress("Jet05.ExclYmerge45", Jet05_ExclYmerge45, &b_Jet05_ExclYmerge45);
   fChain->SetBranchAddress("Jet05.ExclYmerge56", Jet05_ExclYmerge56, &b_Jet05_ExclYmerge56);
   fChain->SetBranchAddress("Jet05.Constituents", Jet05_Constituents, &b_Jet05_Constituents);
   fChain->SetBranchAddress("Jet05.Particles", Jet05_Particles, &b_Jet05_Particles);
   fChain->SetBranchAddress("Jet05.Area", Jet05_Area, &b_Jet05_Area);
   fChain->SetBranchAddress("Jet05_size", &Jet05_size, &b_Jet05_size);
   fChain->SetBranchAddress("Jet10", &Jet10_, &b_Jet10_);
   fChain->SetBranchAddress("Jet10.fUniqueID", Jet10_fUniqueID, &b_Jet10_fUniqueID);
   fChain->SetBranchAddress("Jet10.fBits", Jet10_fBits, &b_Jet10_fBits);
   fChain->SetBranchAddress("Jet10.PT", Jet10_PT, &b_Jet10_PT);
   fChain->SetBranchAddress("Jet10.Eta", Jet10_Eta, &b_Jet10_Eta);
   fChain->SetBranchAddress("Jet10.Phi", Jet10_Phi, &b_Jet10_Phi);
   fChain->SetBranchAddress("Jet10.T", Jet10_T, &b_Jet10_T);
   fChain->SetBranchAddress("Jet10.Mass", Jet10_Mass, &b_Jet10_Mass);
   fChain->SetBranchAddress("Jet10.DeltaEta", Jet10_DeltaEta, &b_Jet10_DeltaEta);
   fChain->SetBranchAddress("Jet10.DeltaPhi", Jet10_DeltaPhi, &b_Jet10_DeltaPhi);
   fChain->SetBranchAddress("Jet10.Flavor", Jet10_Flavor, &b_Jet10_Flavor);
   fChain->SetBranchAddress("Jet10.FlavorAlgo", Jet10_FlavorAlgo, &b_Jet10_FlavorAlgo);
   fChain->SetBranchAddress("Jet10.FlavorPhys", Jet10_FlavorPhys, &b_Jet10_FlavorPhys);
   fChain->SetBranchAddress("Jet10.BTag", Jet10_BTag, &b_Jet10_BTag);
   fChain->SetBranchAddress("Jet10.BTagAlgo", Jet10_BTagAlgo, &b_Jet10_BTagAlgo);
   fChain->SetBranchAddress("Jet10.BTagPhys", Jet10_BTagPhys, &b_Jet10_BTagPhys);
   fChain->SetBranchAddress("Jet10.TauTag", Jet10_TauTag, &b_Jet10_TauTag);
   fChain->SetBranchAddress("Jet10.TauWeight", Jet10_TauWeight, &b_Jet10_TauWeight);
   fChain->SetBranchAddress("Jet10.Charge", Jet10_Charge, &b_Jet10_Charge);
   fChain->SetBranchAddress("Jet10.EhadOverEem", Jet10_EhadOverEem, &b_Jet10_EhadOverEem);
   fChain->SetBranchAddress("Jet10.NCharged", Jet10_NCharged, &b_Jet10_NCharged);
   fChain->SetBranchAddress("Jet10.NNeutrals", Jet10_NNeutrals, &b_Jet10_NNeutrals);
   fChain->SetBranchAddress("Jet10.NeutralEnergyFraction", Jet10_NeutralEnergyFraction, &b_Jet10_NeutralEnergyFraction);
   fChain->SetBranchAddress("Jet10.ChargedEnergyFraction", Jet10_ChargedEnergyFraction, &b_Jet10_ChargedEnergyFraction);
   fChain->SetBranchAddress("Jet10.Beta", Jet10_Beta, &b_Jet10_Beta);
   fChain->SetBranchAddress("Jet10.BetaStar", Jet10_BetaStar, &b_Jet10_BetaStar);
   fChain->SetBranchAddress("Jet10.MeanSqDeltaR", Jet10_MeanSqDeltaR, &b_Jet10_MeanSqDeltaR);
   fChain->SetBranchAddress("Jet10.PTD", Jet10_PTD, &b_Jet10_PTD);
   fChain->SetBranchAddress("Jet10.FracPt[5]", Jet10_FracPt, &b_Jet10_FracPt);
   fChain->SetBranchAddress("Jet10.Tau[5]", Jet10_Tau, &b_Jet10_Tau);
   fChain->SetBranchAddress("Jet10.SoftDroppedJet", Jet10_SoftDroppedJet, &b_Jet10_SoftDroppedJet);
   fChain->SetBranchAddress("Jet10.SoftDroppedSubJet1", Jet10_SoftDroppedSubJet1, &b_Jet10_SoftDroppedSubJet1);
   fChain->SetBranchAddress("Jet10.SoftDroppedSubJet2", Jet10_SoftDroppedSubJet2, &b_Jet10_SoftDroppedSubJet2);
   fChain->SetBranchAddress("Jet10.TrimmedP4[5]", Jet10_TrimmedP4, &b_Jet10_TrimmedP4);
   fChain->SetBranchAddress("Jet10.PrunedP4[5]", Jet10_PrunedP4, &b_Jet10_PrunedP4);
   fChain->SetBranchAddress("Jet10.SoftDroppedP4[5]", Jet10_SoftDroppedP4, &b_Jet10_SoftDroppedP4);
   fChain->SetBranchAddress("Jet10.NSubJetsTrimmed", Jet10_NSubJetsTrimmed, &b_Jet10_NSubJetsTrimmed);
   fChain->SetBranchAddress("Jet10.NSubJetsPruned", Jet10_NSubJetsPruned, &b_Jet10_NSubJetsPruned);
   fChain->SetBranchAddress("Jet10.NSubJetsSoftDropped", Jet10_NSubJetsSoftDropped, &b_Jet10_NSubJetsSoftDropped);
   fChain->SetBranchAddress("Jet10.ExclYmerge12", Jet10_ExclYmerge12, &b_Jet10_ExclYmerge12);
   fChain->SetBranchAddress("Jet10.ExclYmerge23", Jet10_ExclYmerge23, &b_Jet10_ExclYmerge23);
   fChain->SetBranchAddress("Jet10.ExclYmerge34", Jet10_ExclYmerge34, &b_Jet10_ExclYmerge34);
   fChain->SetBranchAddress("Jet10.ExclYmerge45", Jet10_ExclYmerge45, &b_Jet10_ExclYmerge45);
   fChain->SetBranchAddress("Jet10.ExclYmerge56", Jet10_ExclYmerge56, &b_Jet10_ExclYmerge56);
   fChain->SetBranchAddress("Jet10.Constituents", Jet10_Constituents, &b_Jet10_Constituents);
   fChain->SetBranchAddress("Jet10.Particles", Jet10_Particles, &b_Jet10_Particles);
   fChain->SetBranchAddress("Jet10.Area", Jet10_Area, &b_Jet10_Area);
   fChain->SetBranchAddress("Jet10_size", &Jet10_size, &b_Jet10_size);
   Notify();
}

Bool_t event_display1::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void event_display1::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t event_display1::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef event_display1_cxx
