#define analysis2_cxx
#include "analysis2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "histio.c"

void analysis2::Loop( bool verbose )
{
   TStopwatch tsw ;
   tsw.Start() ;
   double total_time(0.) ;

   if (fChain == 0) return;

   gDirectory -> Delete( "h*" ) ;

   TH1F* h_njets = new TH1F( "h_njets", "N jets (gen)", 8, -0.5, 7.5 ) ;

   TH1F* h_dphi = new TH1F( "h_dphi", "Dijet, dphi", 100, -6.15, 6.15 ) ;
   TH1F* h_deta = new TH1F( "h_deta", "Dijet, deta", 100, -6.15, 6.15 ) ;

   TH2F* h_eta2vseta1 = new TH2F( "h_eta2vseta1", "Dijet, eta2 vs eta1", 60, -6., 6., 60, -6., 6. ) ;
   TH2F* h_pt2vspt1 = new TH2F( "h_pt2vspt1", "Dijet, pt2 vs pt1", 60, 0, 20., 60, 0, 20. ) ;

   TH2F* h_deta_vs_dphi = new TH2F( "h_deta_vs_dphi", "Deta vs Dphi", 60, -6., 6., 60, -6., 6. ) ;



   TH1F* h_dphi_pt1gt8 = new TH1F( "h_dphi_pt1gt8", "Dijet, dphi, Pt1>8", 100, -6.15, 6.15 ) ;
   TH1F* h_deta_pt1gt8 = new TH1F( "h_deta_pt1gt8", "Dijet, deta, Pt1>8", 100, -6.15, 6.15 ) ;

   TH1F* h_dphi_pt12gt8 = new TH1F( "h_dphi_pt12gt8", "Dijet, dphi, Pt12>8", 100, -6.15, 6.15 ) ;
   TH1F* h_deta_pt12gt8 = new TH1F( "h_deta_pt12gt8", "Dijet, deta, Pt12>8", 100, -6.15, 6.15 ) ;


   TH1F* h_dphi_both_eta_2to4 = new TH1F( "h_dphi_both_eta_2to4", "Dijet, dphi, both eta 2 to 4", 100, -6.15, 6.15 ) ;


   Long64_t nentries = fChain->GetEntries();

   TStopwatch tsw_loop ;
   double total_time_loop(0.) ;
   tsw_loop.Stop() ;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      int ei = jentry ;

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ( !verbose && ei%100 == 0 ) {
         tsw.Stop() ;
         tsw_loop.Stop() ;
         total_time += tsw.RealTime() ;
         total_time_loop += tsw_loop.RealTime() ;
         float rate_inverse = 1. ;
         if ( ei > 0 ) rate_inverse = total_time_loop / ei ;
                 float eta = (1.*nentries - 1.*ei) * rate_inverse ;
                 printf(" --- Event: %7d / %lld    %6.1f %% complete    %.1f seconds total,  %.1f seconds loop,  rate  %9.1f evt/s,  ETA %.1f seconds                 \r",
                   ei, nentries, 100*(1.*ei)/(1.*nentries), total_time, total_time_loop, 1./rate_inverse, eta ) ;
         fflush(stdout) ;
         tsw.Start() ;
         tsw_loop.Start() ;
      }

     if ( verbose ) {

         printf("\n\n Event %llu,  %d gen particles,  Event_ = %d\n", jentry, Particle_, Event_ ) ;
         printf("     Scale = %10.2f  AlphaQED = %10.6f  AlphaQCD = %9.3f  ID1 = %6d  ID2 = %6d  X1 = %7.5f  X2 = %7.5f\n",
            Event_Scale[0],
            Event_AlphaQED[0],
            Event_AlphaQCD[0],
            Event_ID1[0],
            Event_ID2[0],
            Event_X1[0],
            Event_X2[0] ) ;

         for ( int pi=0; pi<20; pi++ ) {
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

         printf("\n\n Gen Jets:  %d\n", GenJet_ ) ;
         for ( int ji=0; ji<GenJet_; ji++ ) {
            printf(" %3d:  Pt = %9.2f  Eta = %7.3f  Phi = %7.3f\n",
               ji,
               GenJet_PT[ji],
               GenJet_Eta[ji],
               GenJet_Phi[ji]
               ) ;
         } // ji



         printf("  continue?  type q if no.   ") ;
         char answ = getchar() ;
         if ( answ == 'q' ) break ;

      } // verbose?

      h_njets -> Fill( GenJet_ ) ;

      //////if ( GenJet_ < 2 ) continue ;
      if ( GenJet_ != 2 ) continue ;

      float dphi = GenJet_Phi[1] - GenJet_Phi[0] ;
      if ( dphi > 3.14159265 ) dphi = dphi - 2*3.14159265 ;
      if ( dphi <-3.14159265 ) dphi = dphi + 2*3.14159265 ;

      h_dphi -> Fill( dphi ) ;

      float deta = GenJet_Eta[1] - GenJet_Eta[0] ;
      h_deta -> Fill( deta ) ;

      h_eta2vseta1 -> Fill( GenJet_Eta[0], GenJet_Eta[1] ) ;
      h_pt2vspt1 -> Fill( GenJet_PT[0], GenJet_PT[1] ) ;

      h_deta_vs_dphi -> Fill( dphi, deta ) ;


      if ( GenJet_Eta[0] > 2 && GenJet_Eta[0] < 4 && GenJet_Eta[1] > 2 && GenJet_Eta[1] < 4 ) h_dphi_both_eta_2to4 -> Fill(dphi) ;



      if ( GenJet_PT[0]<8 ) continue ;

      h_dphi_pt1gt8 -> Fill( dphi ) ;
      h_deta_pt1gt8 -> Fill( deta ) ;



         printf("\n\n Event %llu,  %d gen particles,  Event_ = %d\n", jentry, Particle_, Event_ ) ;
         printf("     Scale = %10.2f  AlphaQED = %10.6f  AlphaQCD = %9.3f  ID1 = %6d  ID2 = %6d  X1 = %7.5f  X2 = %7.5f\n",
            Event_Scale[0],
            Event_AlphaQED[0],
            Event_AlphaQCD[0],
            Event_ID1[0],
            Event_ID2[0],
            Event_X1[0],
            Event_X2[0] ) ;

   ///   for ( int pi=0; pi<20; pi++ ) {
   ///      printf("  %3d :  PID %7d  Status %6d  M1 %5d M2 %5d  D1 %5d D2 %5d  q %3d  m %8.3f  E %9.2f  Pt = %7.2f Eta = %9.3f\n",
   ///         pi,
   ///         Particle_PID[pi],
   ///         Particle_Status[pi],
   ///         Particle_M1[pi],
   ///         Particle_M2[pi],
   ///         Particle_D1[pi],
   ///         Particle_D2[pi],
   ///         Particle_Charge[pi],
   ///         Particle_Mass[pi],
   ///         Particle_E[pi],
   ///         Particle_PT[pi],
   ///         Particle_Eta[pi]
   ///         ) ;
   ///   }

         printf("\n\n Gen Jets:  %d\n", GenJet_ ) ;
         for ( int ji=0; ji<GenJet_; ji++ ) {
            printf(" %3d:  Pt = %9.2f  Eta = %7.3f  Phi = %7.3f\n",
               ji,
               GenJet_PT[ji],
               GenJet_Eta[ji],
               GenJet_Phi[ji]
               ) ;
         } // ji






      if ( GenJet_PT[1]<8 ) continue ;

      h_dphi_pt12gt8 -> Fill( dphi ) ;
      h_deta_pt12gt8 -> Fill( deta ) ;




   } // jentry
   printf("\n\n Done.\n\n") ;

   saveHist( "a2.root", "h*" ) ;

   loadHist( "a2.root" ) ;

}











