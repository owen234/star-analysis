#define dump_gen1_cxx
#include "dump_gen1.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void dump_gen1::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


      printf("\n\n Event %llu,  %d gen particles,  Event_ = %d\n", jentry, Particle_, Event_ ) ;
      printf("     Scale = %10.2f  AlphaQED = %10.6f  AlphaQCD = %9.3f  ID1 = %6d  ID2 = %6d  X1 = %7.5f  X2 = %7.5f\n",
         Event_Scale[0],
         Event_AlphaQED[0],
         Event_AlphaQCD[0],
         Event_ID1[0],
         Event_ID2[0],
         Event_X1[0],
         Event_X2[0] ) ;

      for ( int pi=0; pi<50; pi++ ) {
         printf("  %3d :  PID %7d  Status %6d  M1 %5d M2 %5d  D1 %5d D2 %5d  q %3d  m %8.3f  E %9.2f  Pt = %7.2f Eta = %9.3f\n",
            pi,
            Particle_PID[pi],
            Particle_Status[pi],
            Particle_M1[pi],
            Particle_M2[pi],
            Particle_D1[pi],
            Particle_D2[pi],
            Particle_Charge[pi],
            Particle_Mass[pi],
            Particle_E[pi],
            Particle_PT[pi],
            Particle_Eta[pi]
            ) ;
      }


      printf("  continue?  type q if no.   ") ;
      char answ = getchar() ;
      if ( answ == 'q' ) break ;

   } // jentry
   printf("\n\n Done.\n\n") ;
}











