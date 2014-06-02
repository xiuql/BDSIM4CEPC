//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun  2 17:10:27 2014 by ROOT version 5.34/18
// from TChain Sampler_11278_DRIFT456_11277_phys_1/
//////////////////////////////////////////////////////////

#ifndef SamplerTest_h
#define SamplerTest_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class SamplerTest {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         E0;
   Float_t         x0;
   Float_t         y0;
   Float_t         z0;
   Float_t         xp0;
   Float_t         yp0;
   Float_t         zp0;
   Float_t         t0;
   Float_t         E;
   Float_t         x;
   Float_t         y;
   Float_t         z;
   Float_t         xp;
   Float_t         yp;
   Float_t         zp;
   Float_t         t;
   Float_t         X;
   Float_t         Y;
   Float_t         Z;
   Float_t         Xp;
   Float_t         Yp;
   Float_t         Zp;
   Float_t         s;
   Float_t         weight;
   Int_t           partID;
   Int_t           nEvent;
   Int_t           parentID;
   Int_t           trackID;
   Int_t           turnnumber;

   // List of branches
   TBranch        *b_E0 (GeV);   //!
   TBranch        *b_x0 (mum);   //!
   TBranch        *b_y0 (mum);   //!
   TBranch        *b_z0 (m);   //!
   TBranch        *b_xp0 (rad);   //!
   TBranch        *b_yp0 (rad);   //!
   TBranch        *b_zp0 (rad);   //!
   TBranch        *b_t0 (ns);   //!
   TBranch        *b_E (GeV);   //!
   TBranch        *b_x (mum);   //!
   TBranch        *b_y (mum);   //!
   TBranch        *b_z (m);   //!
   TBranch        *b_xp (rad);   //!
   TBranch        *b_yp (rad);   //!
   TBranch        *b_zp (rad);   //!
   TBranch        *b_t (ns);   //!
   TBranch        *b_X (mum);   //!
   TBranch        *b_Y (mum);   //!
   TBranch        *b_Z (m);   //!
   TBranch        *b_Xp (rad);   //!
   TBranch        *b_Yp (rad);   //!
   TBranch        *b_Zp (rad);   //!
   TBranch        *b_s (m);   //!
   TBranch        *b_weight;   //!
   TBranch        *b_partID;   //!
   TBranch        *b_nEvent;   //!
   TBranch        *b_parentID;   //!
   TBranch        *b_trackID;   //!
   TBranch        *b_turnnumber;   //!

   SamplerTest(TTree *tree=0);
   virtual ~SamplerTest();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef SamplerTest_cxx
SamplerTest::SamplerTest(TTree *tree) : fChain(0) 
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
      f->GetObject("Sampler_11278_DRIFT456_11277_phys_1",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("Sampler_11278_DRIFT456_11277_phys_1","");
      chain->Add("/Users/nevay/physics/reps/bdsim/utils/root-scripts/optics/st_100_0.root/Sampler_11278_DRIFT456_11277_phys_1");
      chain->Add("/Users/nevay/physics/reps/bdsim/utils/root-scripts/optics/st_64_0.root/Sampler_11278_DRIFT456_11277_phys_1");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

SamplerTest::~SamplerTest()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SamplerTest::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SamplerTest::LoadTree(Long64_t entry)
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

void SamplerTest::Init(TTree *tree)
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

   fChain->SetBranchAddress("E0", &E0, &b_E0 (GeV));
   fChain->SetBranchAddress("x0", &x0, &b_x0 (mum));
   fChain->SetBranchAddress("y0", &y0, &b_y0 (mum));
   fChain->SetBranchAddress("z0", &z0, &b_z0 (m));
   fChain->SetBranchAddress("xp0", &xp0, &b_xp0 (rad));
   fChain->SetBranchAddress("yp0", &yp0, &b_yp0 (rad));
   fChain->SetBranchAddress("zp0", &zp0, &b_zp0 (rad));
   fChain->SetBranchAddress("t0", &t0, &b_t0 (ns));
   fChain->SetBranchAddress("E", &E, &b_E (GeV));
   fChain->SetBranchAddress("x", &x, &b_x (mum));
   fChain->SetBranchAddress("y", &y, &b_y (mum));
   fChain->SetBranchAddress("z", &z, &b_z (m));
   fChain->SetBranchAddress("xp", &xp, &b_xp (rad));
   fChain->SetBranchAddress("yp", &yp, &b_yp (rad));
   fChain->SetBranchAddress("zp", &zp, &b_zp (rad));
   fChain->SetBranchAddress("t", &t, &b_t (ns));
   fChain->SetBranchAddress("X", &X, &b_X (mum));
   fChain->SetBranchAddress("Y", &Y, &b_Y (mum));
   fChain->SetBranchAddress("Z", &Z, &b_Z (m));
   fChain->SetBranchAddress("Xp", &Xp, &b_Xp (rad));
   fChain->SetBranchAddress("Yp", &Yp, &b_Yp (rad));
   fChain->SetBranchAddress("Zp", &Zp, &b_Zp (rad));
   fChain->SetBranchAddress("s", &s, &b_s (m));
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("partID", &partID, &b_partID);
   fChain->SetBranchAddress("nEvent", &nEvent, &b_nEvent);
   fChain->SetBranchAddress("parentID", &parentID, &b_parentID);
   fChain->SetBranchAddress("trackID", &trackID, &b_trackID);
   fChain->SetBranchAddress("turnnumber", &turnnumber, &b_turnnumber);
   Notify();
}

Bool_t SamplerTest::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SamplerTest::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SamplerTest::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SamplerTest_cxx
