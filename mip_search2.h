//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug  9 12:05:28 2023 by ROOT version 6.24/07
// from TChain mipanalysis/
//////////////////////////////////////////////////////////

#ifndef mip_search2_h
#define mip_search2_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "c++/v1/vector"
#include "c++/v1/vector"

class mip_search2 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           rcN;
   vector<float>   *rcPt;
   vector<float>   *rcEta;
   vector<float>   *rcPhi;
   vector<int>     *rcNumFST;
   vector<int>     *rcNumFTT;
   vector<float>   *rcProjEcalx;
   vector<float>   *rcProjEcaly;
   vector<float>   *rcProjEcalz;
   vector<float>   *rcProjHcalx;
   vector<float>   *rcProjHcaly;
   vector<float>   *rcProjHcalz;
   vector<float>   *rcProjEcalPx;
   vector<float>   *rcProjEcalPy;
   vector<float>   *rcProjEcalPz;
   vector<int>     *rcEcalClIndex;
   vector<int>     *rcHcalClIndex;
   vector<float>   *rcEcalClE;
   vector<float>   *rcHcalClE;
   vector<float>   *rcEcalClDx;
   vector<float>   *rcEcalClDy;
   vector<float>   *rcEcalClDr;
   vector<float>   *rcHcalClDx;
   vector<float>   *rcHcalClDy;
   vector<float>   *rcHcalClDr;
   Int_t           fcs_cl_ecalN;
   vector<float>   *fcs_cl_ecalE;
   vector<float>   *fcs_cl_ecalX;
   vector<float>   *fcs_cl_ecalY;
   vector<float>   *fcs_cl_ecalZ;
   vector<int>     *fcs_cl_ecalNhit;
   Int_t           fcs_cl_hcalN;
   vector<float>   *fcs_cl_hcalE;
   vector<float>   *fcs_cl_hcalX;
   vector<float>   *fcs_cl_hcalY;
   vector<float>   *fcs_cl_hcalZ;
   vector<int>     *fcs_cl_hcalNhit;
   Int_t           fcs_rec_ecalN;
   vector<float>   *fcs_rec_ecalX;
   vector<float>   *fcs_rec_ecalY;
   vector<float>   *fcs_rec_ecalZ;
   vector<float>   *fcs_rec_ecalLX;
   vector<float>   *fcs_rec_ecalLY;
   vector<float>   *fcs_rec_ecalE;
   vector<int>     *fcs_rec_ecalId;
   vector<int>     *fcs_rec_ecalDet;
   vector<int>     *fcs_rec_ecalClIndex;
   vector<int>     *fcs_rec_ecalTrkIndex;
   Int_t           fcs_rec_hcalN;
   vector<float>   *fcs_rec_hcalX;
   vector<float>   *fcs_rec_hcalY;
   vector<float>   *fcs_rec_hcalZ;
   vector<float>   *fcs_rec_hcalLX;
   vector<float>   *fcs_rec_hcalLY;
   vector<float>   *fcs_rec_hcalE;
   vector<int>     *fcs_rec_hcalId;
   vector<int>     *fcs_rec_hcalDet;
   vector<int>     *fcs_rec_hcalClIndex;
   vector<int>     *fcs_rec_hcalTrkIndex;

   // List of branches
   TBranch        *b_rcN;   //!
   TBranch        *b_rcPt;   //!
   TBranch        *b_rcEta;   //!
   TBranch        *b_rcPhi;   //!
   TBranch        *b_rcNumFST;   //!
   TBranch        *b_rcNumFTT;   //!
   TBranch        *b_rcProjEcalx;   //!
   TBranch        *b_rcProjEcaly;   //!
   TBranch        *b_rcProjEcalz;   //!
   TBranch        *b_rcProjHcalx;   //!
   TBranch        *b_rcProjHcaly;   //!
   TBranch        *b_rcProjHcalz;   //!
   TBranch        *b_rcProjEcalPx;   //!
   TBranch        *b_rcProjEcalPy;   //!
   TBranch        *b_rcProjEcalPz;   //!
   TBranch        *b_rcEcalClIndex;   //!
   TBranch        *b_rcHcalClIndex;   //!
   TBranch        *b_rcEcalClE;   //!
   TBranch        *b_rcHcalClE;   //!
   TBranch        *b_rcEcalClDx;   //!
   TBranch        *b_rcEcalClDy;   //!
   TBranch        *b_rcEcalClDr;   //!
   TBranch        *b_rcHcalClDx;   //!
   TBranch        *b_rcHcalClDy;   //!
   TBranch        *b_rcHcalClDr;   //!
   TBranch        *b_fcs_cl_ecalN;   //!
   TBranch        *b_fcs_cl_ecalE;   //!
   TBranch        *b_fcs_cl_ecalX;   //!
   TBranch        *b_fcs_cl_ecalY;   //!
   TBranch        *b_fcs_cl_ecalZ;   //!
   TBranch        *b_fcs_cl_ecalNhit;   //!
   TBranch        *b_fcs_cl_hcalN;   //!
   TBranch        *b_fcs_cl_hcalE;   //!
   TBranch        *b_fcs_cl_hcalX;   //!
   TBranch        *b_fcs_cl_hcalY;   //!
   TBranch        *b_fcs_cl_hcalZ;   //!
   TBranch        *b_fcs_cl_hcalNhit;   //!
   TBranch        *b_fcs_rec_ecalN;   //!
   TBranch        *b_fcs_rec_ecalX;   //!
   TBranch        *b_fcs_rec_ecalY;   //!
   TBranch        *b_fcs_rec_ecalZ;   //!
   TBranch        *b_fcs_rec_ecalLX;   //!
   TBranch        *b_fcs_rec_ecalLY;   //!
   TBranch        *b_fcs_rec_ecalE;   //!
   TBranch        *b_fcs_rec_ecalId;   //!
   TBranch        *b_fcs_rec_ecalDet;   //!
   TBranch        *b_fcs_rec_ecalClIndex;   //!
   TBranch        *b_fcs_rec_ecalTrkIndex;   //!
   TBranch        *b_fcs_rec_hcalN;   //!
   TBranch        *b_fcs_rec_hcalX;   //!
   TBranch        *b_fcs_rec_hcalY;   //!
   TBranch        *b_fcs_rec_hcalZ;   //!
   TBranch        *b_fcs_rec_hcalLX;   //!
   TBranch        *b_fcs_rec_hcalLY;   //!
   TBranch        *b_fcs_rec_hcalE;   //!
   TBranch        *b_fcs_rec_hcalId;   //!
   TBranch        *b_fcs_rec_hcalDet;   //!
   TBranch        *b_fcs_rec_hcalClIndex;   //!
   TBranch        *b_fcs_rec_hcalTrkIndex;   //!

   mip_search2(TTree *tree=0);
   virtual ~mip_search2();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop( int max_evts = -1, bool arg_verb = false );
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void  doTrackLoop( std::map<const char*,TH1F*> hist_map, std::map<const char*,TH2F*> hist_map2d, bool use_previous_event_tracks = false ) ;
   void  check_neighbors( int hit_index, vector<int> &all_neighbors ) ;
   void  check_neighbors_hcal( int hit_index, vector<int> &all_neighbors ) ;

   void calc_iso( float x, float y, vector<int> cluster_hits, float& iso20, float& iso30 ) ;
   int  match_track( float x, float y, float radius=20 ) ;
   int find_closest_hcal_hit( float x, float y ) ;

   vector<float>* previous_event_rcProjEcalx = new vector<float> ;
   vector<float>* previous_event_rcProjEcaly = new vector<float> ;
   vector<float>* previous_event_rcProjHcalx = new vector<float> ;
   vector<float>* previous_event_rcProjHcaly = new vector<float> ;
   vector<int>*   previous_event_rcNumFST    = new vector<int> ;

   bool verbose ;
   float radius ;
};

#endif

#ifdef mip_search2_cxx
mip_search2::mip_search2(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("mipanalysis",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("mipanalysis","");


      chain->Add("/Users/owen/work/bnl/star/mip-analysis-data-2023-08/mip-analysis-ttree-*.root/mipanalysis") ;


      //////////chain->Add("mip-analysis-ttree.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-001.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-002.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-003.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-004.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-005.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-006.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-007.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-008.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-009.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-010.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-011.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-012.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-013.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-014.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-015.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-016.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-017.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-018.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-019.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-020.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-021.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-022.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-023.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-024.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-025.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-026.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-027.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-028.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-029.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-030.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-031.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-032.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-033.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-034.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-035.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-036.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-037.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-038.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-039.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-040.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-041.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-042.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-043.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-044.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-045.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-046.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-047.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-048.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-049.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-050.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-051.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-052.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-053.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-054.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-055.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-056.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-057.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-058.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-059.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-060.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-061.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-062.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-063.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-064.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-065.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-066.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-067.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-068.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-069.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-070.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-071.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-072.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-073.root/mipanalysis");
///   chain->Add("output-files/mip-analysis-ttree-074.root/mipanalysis");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

mip_search2::~mip_search2()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t mip_search2::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t mip_search2::LoadTree(Long64_t entry)
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

void mip_search2::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   rcPt = 0;
   rcEta = 0;
   rcPhi = 0;
   rcNumFST = 0;
   rcNumFTT = 0;
   rcProjEcalx = 0;
   rcProjEcaly = 0;
   rcProjEcalz = 0;
   rcProjHcalx = 0;
   rcProjHcaly = 0;
   rcProjHcalz = 0;
   rcProjEcalPx = 0;
   rcProjEcalPy = 0;
   rcProjEcalPz = 0;
   rcEcalClIndex = 0;
   rcHcalClIndex = 0;
   rcEcalClE = 0;
   rcHcalClE = 0;
   rcEcalClDx = 0;
   rcEcalClDy = 0;
   rcEcalClDr = 0;
   rcHcalClDx = 0;
   rcHcalClDy = 0;
   rcHcalClDr = 0;
   fcs_cl_ecalE = 0;
   fcs_cl_ecalX = 0;
   fcs_cl_ecalY = 0;
   fcs_cl_ecalZ = 0;
   fcs_cl_ecalNhit = 0;
   fcs_cl_hcalE = 0;
   fcs_cl_hcalX = 0;
   fcs_cl_hcalY = 0;
   fcs_cl_hcalZ = 0;
   fcs_cl_hcalNhit = 0;
   fcs_rec_ecalX = 0;
   fcs_rec_ecalY = 0;
   fcs_rec_ecalZ = 0;
   fcs_rec_ecalLX = 0;
   fcs_rec_ecalLY = 0;
   fcs_rec_ecalE = 0;
   fcs_rec_ecalId = 0;
   fcs_rec_ecalDet = 0;
   fcs_rec_ecalClIndex = 0;
   fcs_rec_ecalTrkIndex = 0;
   fcs_rec_hcalX = 0;
   fcs_rec_hcalY = 0;
   fcs_rec_hcalZ = 0;
   fcs_rec_hcalLX = 0;
   fcs_rec_hcalLY = 0;
   fcs_rec_hcalE = 0;
   fcs_rec_hcalId = 0;
   fcs_rec_hcalDet = 0;
   fcs_rec_hcalClIndex = 0;
   fcs_rec_hcalTrkIndex = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("rcN", &rcN, &b_rcN);
   fChain->SetBranchAddress("rcPt", &rcPt, &b_rcPt);
   fChain->SetBranchAddress("rcEta", &rcEta, &b_rcEta);
   fChain->SetBranchAddress("rcPhi", &rcPhi, &b_rcPhi);
   fChain->SetBranchAddress("rcNumFST", &rcNumFST, &b_rcNumFST);
   fChain->SetBranchAddress("rcNumFTT", &rcNumFTT, &b_rcNumFTT);
   fChain->SetBranchAddress("rcProjEcalx", &rcProjEcalx, &b_rcProjEcalx);
   fChain->SetBranchAddress("rcProjEcaly", &rcProjEcaly, &b_rcProjEcaly);
   fChain->SetBranchAddress("rcProjEcalz", &rcProjEcalz, &b_rcProjEcalz);
   fChain->SetBranchAddress("rcProjHcalx", &rcProjHcalx, &b_rcProjHcalx);
   fChain->SetBranchAddress("rcProjHcaly", &rcProjHcaly, &b_rcProjHcaly);
   fChain->SetBranchAddress("rcProjHcalz", &rcProjHcalz, &b_rcProjHcalz);
   fChain->SetBranchAddress("rcProjEcalPx", &rcProjEcalPx, &b_rcProjEcalPx);
   fChain->SetBranchAddress("rcProjEcalPy", &rcProjEcalPy, &b_rcProjEcalPy);
   fChain->SetBranchAddress("rcProjEcalPz", &rcProjEcalPz, &b_rcProjEcalPz);
   fChain->SetBranchAddress("rcEcalClIndex", &rcEcalClIndex, &b_rcEcalClIndex);
   fChain->SetBranchAddress("rcHcalClIndex", &rcHcalClIndex, &b_rcHcalClIndex);
   fChain->SetBranchAddress("rcEcalClE", &rcEcalClE, &b_rcEcalClE);
   fChain->SetBranchAddress("rcHcalClE", &rcHcalClE, &b_rcHcalClE);
   fChain->SetBranchAddress("rcEcalClDx", &rcEcalClDx, &b_rcEcalClDx);
   fChain->SetBranchAddress("rcEcalClDy", &rcEcalClDy, &b_rcEcalClDy);
   fChain->SetBranchAddress("rcEcalClDr", &rcEcalClDr, &b_rcEcalClDr);
   fChain->SetBranchAddress("rcHcalClDx", &rcHcalClDx, &b_rcHcalClDx);
   fChain->SetBranchAddress("rcHcalClDy", &rcHcalClDy, &b_rcHcalClDy);
   fChain->SetBranchAddress("rcHcalClDr", &rcHcalClDr, &b_rcHcalClDr);
   fChain->SetBranchAddress("fcs_cl_ecalN", &fcs_cl_ecalN, &b_fcs_cl_ecalN);
   fChain->SetBranchAddress("fcs_cl_ecalE", &fcs_cl_ecalE, &b_fcs_cl_ecalE);
   fChain->SetBranchAddress("fcs_cl_ecalX", &fcs_cl_ecalX, &b_fcs_cl_ecalX);
   fChain->SetBranchAddress("fcs_cl_ecalY", &fcs_cl_ecalY, &b_fcs_cl_ecalY);
   fChain->SetBranchAddress("fcs_cl_ecalZ", &fcs_cl_ecalZ, &b_fcs_cl_ecalZ);
   fChain->SetBranchAddress("fcs_cl_ecalNhit", &fcs_cl_ecalNhit, &b_fcs_cl_ecalNhit);
   fChain->SetBranchAddress("fcs_cl_hcalN", &fcs_cl_hcalN, &b_fcs_cl_hcalN);
   fChain->SetBranchAddress("fcs_cl_hcalE", &fcs_cl_hcalE, &b_fcs_cl_hcalE);
   fChain->SetBranchAddress("fcs_cl_hcalX", &fcs_cl_hcalX, &b_fcs_cl_hcalX);
   fChain->SetBranchAddress("fcs_cl_hcalY", &fcs_cl_hcalY, &b_fcs_cl_hcalY);
   fChain->SetBranchAddress("fcs_cl_hcalZ", &fcs_cl_hcalZ, &b_fcs_cl_hcalZ);
   fChain->SetBranchAddress("fcs_cl_hcalNhit", &fcs_cl_hcalNhit, &b_fcs_cl_hcalNhit);
   fChain->SetBranchAddress("fcs_rec_ecalN", &fcs_rec_ecalN, &b_fcs_rec_ecalN);
   fChain->SetBranchAddress("fcs_rec_ecalX", &fcs_rec_ecalX, &b_fcs_rec_ecalX);
   fChain->SetBranchAddress("fcs_rec_ecalY", &fcs_rec_ecalY, &b_fcs_rec_ecalY);
   fChain->SetBranchAddress("fcs_rec_ecalZ", &fcs_rec_ecalZ, &b_fcs_rec_ecalZ);
   fChain->SetBranchAddress("fcs_rec_ecalLX", &fcs_rec_ecalLX, &b_fcs_rec_ecalLX);
   fChain->SetBranchAddress("fcs_rec_ecalLY", &fcs_rec_ecalLY, &b_fcs_rec_ecalLY);
   fChain->SetBranchAddress("fcs_rec_ecalE", &fcs_rec_ecalE, &b_fcs_rec_ecalE);
   fChain->SetBranchAddress("fcs_rec_ecalId", &fcs_rec_ecalId, &b_fcs_rec_ecalId);
   fChain->SetBranchAddress("fcs_rec_ecalDet", &fcs_rec_ecalDet, &b_fcs_rec_ecalDet);
   fChain->SetBranchAddress("fcs_rec_ecalClIndex", &fcs_rec_ecalClIndex, &b_fcs_rec_ecalClIndex);
   fChain->SetBranchAddress("fcs_rec_ecalTrkIndex", &fcs_rec_ecalTrkIndex, &b_fcs_rec_ecalTrkIndex);
   fChain->SetBranchAddress("fcs_rec_hcalN", &fcs_rec_hcalN, &b_fcs_rec_hcalN);
   fChain->SetBranchAddress("fcs_rec_hcalX", &fcs_rec_hcalX, &b_fcs_rec_hcalX);
   fChain->SetBranchAddress("fcs_rec_hcalY", &fcs_rec_hcalY, &b_fcs_rec_hcalY);
   fChain->SetBranchAddress("fcs_rec_hcalZ", &fcs_rec_hcalZ, &b_fcs_rec_hcalZ);
   fChain->SetBranchAddress("fcs_rec_hcalLX", &fcs_rec_hcalLX, &b_fcs_rec_hcalLX);
   fChain->SetBranchAddress("fcs_rec_hcalLY", &fcs_rec_hcalLY, &b_fcs_rec_hcalLY);
   fChain->SetBranchAddress("fcs_rec_hcalE", &fcs_rec_hcalE, &b_fcs_rec_hcalE);
   fChain->SetBranchAddress("fcs_rec_hcalId", &fcs_rec_hcalId, &b_fcs_rec_hcalId);
   fChain->SetBranchAddress("fcs_rec_hcalDet", &fcs_rec_hcalDet, &b_fcs_rec_hcalDet);
   fChain->SetBranchAddress("fcs_rec_hcalClIndex", &fcs_rec_hcalClIndex, &b_fcs_rec_hcalClIndex);
   fChain->SetBranchAddress("fcs_rec_hcalTrkIndex", &fcs_rec_hcalTrkIndex, &b_fcs_rec_hcalTrkIndex);
   Notify();
}

Bool_t mip_search2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void mip_search2::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t mip_search2::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef mip_search2_cxx
