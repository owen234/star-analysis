
#include "ExRootTreeReader.cc"
#include "DelphesClasses.h"


   void test_tr1( const char* infile = "test-1M-00.root" ) {


      //TFile* tf = new TFile( infile, "read" ) ;
      //if ( tf == 0x0 ) { printf("\n\n *** bad input file: %s\n\n", infile ) ; return ; }

      TChain* tch = new TChain( "Delphes" ) ;
      tch -> Add( infile ) ;
      int nevents = tch -> GetEntries() ;
      printf("\n\n File %s has %d events.\n\n", infile, nevents ) ;

      ExRootTreeReader* treeReader = new ExRootTreeReader( tch ) ;

      TClonesArray *branchJet = treeReader->UseBranch("Jet05");
      TClonesArray *branchGenJet = treeReader->UseBranch("GenJet05");

      printf("  TClonesArray   branchJet = %p  branchGenJet %p  \n\n", branchJet, branchGenJet ) ;

      for ( int ei=0; ei<10; ei++ ) {
         treeReader -> ReadEntry(ei) ;
         printf("\n\n Event %d :  number of Jets:  %d   number of GenJets:  %d\n", ei, branchJet->GetEntries(), branchGenJet->GetEntries() ) ;
         for ( int gji=0; gji<branchGenJet->GetEntries(); gji++ ) {
            Jet* genjet ;
            //printf("  GenJet %2d :  Pt = %6.2f  Eta = %6.3f  Phi = %6.3f\n", gji, 
         }
      }



   }


