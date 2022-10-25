#define calo_analysis2_cxx
#include "calo_analysis2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "histio.c"

float calc_dphi( float phi1, float phi2 ) {
   float rv = phi1 - phi2 ;
   if ( rv > 3.14159265 ) rv = rv - 2*3.14159265 ;
   if ( rv <-3.14159265 ) rv = rv + 2*3.14159265 ;
   return rv ;
}

float calc_dR( float phi1, float phi2, float eta1, float eta2 ) {
   float dphi = calc_dphi( phi1, phi2 ) ;
   float deta = eta1 - eta2 ;
   return sqrt( dphi*dphi + deta*deta ) ;
}

float calc_y( float E, float pz ) {
   if ( E == pz ) return 9999. ;
   return 0.5 * log( (E + pz)/(E - pz) ) ;
}

float theta_from_eta( float eta ) {
   return 2. * atan( exp( -1. * eta ) ) ;
}

void calo_analysis2::Loop( bool verbose ) {

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



   TH2F* h_gen_parton_eta2_vs_eta1_all = new TH2F( "h_gen_parton_eta2_vs_eta1_all", "Gen partons, eta2 vs eta1, all events", 60, -5., 5.,  60, -5., 5. ) ;

   TH2F* h_gen_parton_eta2_vs_eta1_2gen_central = new TH2F( "h_gen_parton_eta2_vs_eta1_2gen_central", "Gen partons, eta2 vs eta1, 2 central gen jets", 60, -5., 5.,  60, -5., 5. ) ;
   TH2F* h_gen_parton_eta2_vs_eta1_2gen_forward = new TH2F( "h_gen_parton_eta2_vs_eta1_2gen_forward", "Gen partons, eta2 vs eta1, 2 forward gen jets", 60, -5., 5.,  60, -5., 5. ) ;





   TH1F* h_dphi_pt1gt8 = new TH1F( "h_dphi_pt1gt8", "Dijet, dphi, Pt1>8", 100, -6.15, 6.15 ) ;
   TH1F* h_deta_pt1gt8 = new TH1F( "h_deta_pt1gt8", "Dijet, deta, Pt1>8", 100, -6.15, 6.15 ) ;

   TH1F* h_dphi_pt12gt8 = new TH1F( "h_dphi_pt12gt8", "Dijet, dphi, Pt12>8", 100, -6.15, 6.15 ) ;
   TH1F* h_deta_pt12gt8 = new TH1F( "h_deta_pt12gt8", "Dijet, deta, Pt12>8", 100, -6.15, 6.15 ) ;


   TH1F* h_dphi_both_eta_2to4 = new TH1F( "h_dphi_both_eta_2to4", "Dijet, dphi, both eta 2 to 4", 100, -6.15, 6.15 ) ;



   TH2F* h_log10x2_vs_log10x1_all = new TH2F( "h_log10x2_vs_log10x1_all", "log10x1 vs log10x2, all generated events", 60, -4., 1., 60, -4., 1. ) ;

   TH2F* h_log10x2_vs_log10x1_2gen_central = new TH2F( "h_log10x2_vs_log10x1_2gen_central", "log10x1 vs log10x2, 2 central gen jets", 60, -4., 1., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_log10x1_2gen_forward = new TH2F( "h_log10x2_vs_log10x1_2gen_forward", "log10x1 vs log10x2, 2 forward gen jets", 60, -4., 1., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_log10x1_1gen_central_1gen_forward = new TH2F( "h_log10x2_vs_log10x1_1gen_central_1gen_forward", "log10x1 vs log10x2, 1 central, 1 forward gen jets", 60, -4., 1., 60, -4., 1. ) ;
   TH2F* h_ngenjet_forward_vs_central = new TH2F( "h_ngenjet_forward_vs_central", "N genjets, forward vs central", 4, -0.5, 3.5,  4, -0.5, 3.5 ) ;



   TH2F* h_id2_vs_id1_all = new TH2F( "h_id2_vs_id1_all", "PDG ID2 vs ID2, all",   51, -25.5, 25.5,  51, -25.5, 25.5  ) ;
   TH2F* h_id2_vs_id1_2gen_central = new TH2F( "h_id2_vs_id1_2gen_central", "PDG ID2 vs ID2, 2 central gen jets",   51, -25.5, 25.5,  51, -25.5, 25.5  ) ;
   TH2F* h_id2_vs_id1_2gen_forward = new TH2F( "h_id2_vs_id1_2gen_forward", "PDG ID2 vs ID2, 2 forward gen jets",   51, -25.5, 25.5,  51, -25.5, 25.5  ) ;
   TH2F* h_id2_vs_id1_1gen_central_1gen_forward = new TH2F( "h_id2_vs_id1_1gen_central_1gen_forward", "PDG ID2 vs ID2, 1 central, 1 forward gen jet",   51, -25.5, 25.5,  51, -25.5, 25.5  ) ;


   TH2F* h_log10x2_vs_log10x1_2rec = new TH2F( "h_log10x2_vs_log10x1_2rec", "log10x1 vs log10x2, 2 rec jets", 60, -4., 1., 60, -4., 1. ) ;







   TH1F* h_r2j_rec_dphi_all = new TH1F( "h_r2j_rec_dphi_all", "Rec 2 jets, dphi, all", 100, -3.2, 3.2 ) ;
   TH1F* h_r2j_rec_dphi_2gjm = new TH1F( "h_r2j_rec_dphi_2gjm", "Rec 2 jets, dphi, 2 gen jet match", 100, -3.2, 3.2 ) ;

   TH1F* h_r2j_gm0dr = new TH1F("h_r2j_gm0dr", "Jet 0 best gen match dR", 100, 0., 2. ) ;
   TH1F* h_r2j_gm1dr = new TH1F("h_r2j_gm1dr", "Jet 1 best gen match dR", 100, 0., 2. ) ;

   TH1F* h_r2j_phi0_recmgen = new TH1F( "h_r2j_phi0_recmgen", "jet0, phi, rec - true", 100, -1., 1. ) ;
   TH1F* h_r2j_phi1_recmgen = new TH1F( "h_r2j_phi1_recmgen", "jet1, phi, rec - true", 100, -1., 1. ) ;

   TH1F* h_r2j_eta0_recmgen = new TH1F( "h_r2j_eta0_recmgen", "jet0, eta, rec - true", 100, -1., 1. ) ;
   TH1F* h_r2j_eta1_recmgen = new TH1F( "h_r2j_eta1_recmgen", "jet1, eta, rec - true", 100, -1., 1. ) ;

   TH1F* h_r2j_Pperp = new TH1F( "h_r2j_Pperp", "Rec 2 jets, Pperp rec", 100, 0., 8. ) ;
   TH1F* h_r2j_qperp = new TH1F( "h_r2j_qperp", "Rec 2 jets, qperp rec", 100, 0., 8. ) ;

   TH2F* h_r2j_qperp_vs_Pperp = new TH2F( "h_r2j_qperp_vs_Pperp", "Rec 2 jets, qperp vs Pperp", 60, 0., 8.,  60, 0., 8. ) ;

   TH1F* h_r2j_Pperp_recmgen = new TH1F( "h_r2j_Pperp_recmgen", "Rec 2 jets, Pperp, rec - true", 100, -2., 2. ) ;
   TH1F* h_r2j_qperp_recmgen = new TH1F( "h_r2j_qperp_recmgen", "Rec 2 jets, qperp, rec - true", 100, -2., 2. ) ;


   TH2F* h_r2j_Pperp_gen_vs_rec = new TH2F( "h_r2j_Pperp_gen_vs_rec", "Rec 2 jets, Pperp, gen vs rec", 60, 0., 8.,  60, 0., 8. ) ;
   TH2F* h_r2j_qperp_gen_vs_rec = new TH2F( "h_r2j_qperp_gen_vs_rec", "Rec 2 jets, qperp, gen vs rec", 60, 0., 8.,  60, 0., 8. ) ;


   TH1F* h_r2j_qperp_over_Pperp = new TH1F( "h_r2j_qperp_over_Pperp", "Rec 2 jets, qperp/Pperp", 60, 0., 4. ) ;

   TH2F* h_r2j_j1_vs_j0_pt = new TH2F( "h_r2j_j1_vs_j0_pt", "Rec 2 jets, Jet 1 pt vs jet0 pt", 60, 0., 8.,  60, 0., 8. ) ;
   TH2F* h_r2j_j1_vs_j0_eta = new TH2F( "h_r2j_j1_vs_j0_eta", "Rec 2 jets, Jet 1 pt vs jet0 eta", 60, 2., 5.,  60, 2., 5. ) ;
   TH2F* h_r2j_j1_vs_j0_pz = new TH2F( "h_r2j_j1_vs_j0_pz", "Rec 2 jets, Jet 1 pt vs jet0 pz", 60, 0., 100.,  60, 0., 100. ) ;

   TH1F* h_r2j_dphi_Pperp_qperp = new TH1F( "h_r2j_dphi_Pperp_qperp", "Rec 2 jets, phi(Pperp)-phi(qperp)", 100, -3.2, 3.2 ) ;
   TH1F* h_r2j_dphi_Pperp_qperp_gen = new TH1F( "h_r2j_dphi_Pperp_qperp_gen", "Rec 2 jets, gen phi(Pperp)-phi(qperp)", 100, -3.2, 3.2 ) ;
   TH1F* h_r2j_dphi_Pperp_qperp_recmgen = new TH1F( "h_r2j_dphi_Pperp_qperp_recmgen", "Rec 2 jets, phi(Pperp)-phi(qperp), rec-gen", 100, -3.2, 3.2 ) ;

   TH1F* h_r2j_2gj_dphi_Pperp_qperp = new TH1F( "h_r2j_2gj_dphi_Pperp_qperp", "Rec 2 jets, 2 gen jets, phi(Pperp)-phi(qperp)", 100, -3.2, 3.2 ) ;
   TH1F* h_r2j_2gj_dphi_Pperp_qperp_gen = new TH1F( "h_r2j_2gj_dphi_Pperp_qperp_gen", "Rec 2 jets,  2 gen jets,gen phi(Pperp)-phi(qperp)", 100, -3.2, 3.2 ) ;
   TH1F* h_r2j_2gj_dphi_Pperp_qperp_recmgen = new TH1F( "h_r2j_2gj_dphi_Pperp_qperp_recmgen", "Rec 2 jets,  2 gen jets,phi(Pperp)-phi(qperp), rec-gen", 100, -3.2, 3.2 ) ;

   TH1F* h_r2j_3gj_dphi_Pperp_qperp = new TH1F( "h_r2j_3gj_dphi_Pperp_qperp", "Rec 2 jets, 3 gen jets, phi(Pperp)-phi(qperp)", 100, -3.2, 3.2 ) ;
   TH1F* h_r2j_3gj_dphi_Pperp_qperp_gen = new TH1F( "h_r2j_3gj_dphi_Pperp_qperp_gen", "Rec 2 jets,  3 gen jets,gen phi(Pperp)-phi(qperp)", 100, -3.2, 3.2 ) ;
   TH1F* h_r2j_3gj_dphi_Pperp_qperp_recmgen = new TH1F( "h_r2j_3gj_dphi_Pperp_qperp_recmgen", "Rec 2 jets,  3 gen jets,phi(Pperp)-phi(qperp), rec-gen", 100, -3.2, 3.2 ) ;



   TH2F* h_r2j_dphi_Pq_vs_dphi_jj = new TH2F( "h_r2j_dphi_Pq_vs_dphi_jj", "Rec 2 jets, delta phi P q vs delta phi jet jet", 60, -3.2, 3.2,  60, -3.2, 3.2 ) ;
   TH2F* h_r2j_2gj_dphi_Pq_vs_dphi_jj = new TH2F( "h_r2j_2gj_dphi_Pq_vs_dphi_jj", "Rec 2 jets, 2 gen jets, delta phi P q vs delta phi jet jet", 60, -3.2, 3.2,  60, -3.2, 3.2 ) ;
   TH2F* h_r2j_3gj_dphi_Pq_vs_dphi_jj = new TH2F( "h_r2j_3gj_dphi_Pq_vs_dphi_jj", "Rec 2 jets, 3 gen jets, delta phi P q vs delta phi jet jet", 60, -3.2, 3.2,  60, -3.2, 3.2 ) ;


   Long64_t nentries = fChain->GetEntries();

   TStopwatch tsw_loop ;
   double total_time_loop(0.) ;
   tsw_loop.Stop() ;


   //nentries = 10000 ;

   //nentries = 1000000 ;

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

         if ( Jet_ != 2 ) continue ;

         printf("\n\n Event %llu,   Event_ = %d\n", jentry, Event_ ) ;
         printf("     Scale = %10.2f  AlphaQED = %10.6f  AlphaQCD = %9.3f  ID1 = %6d  ID2 = %6d  X1 = %7.5f  X2 = %7.5f\n",
            Event_Scale[0],
            Event_AlphaQED[0],
            Event_AlphaQCD[0],
            Event_ID1[0],
            Event_ID2[0],
            Event_X1[0],
            Event_X2[0] ) ;

     //  for ( int pi=0; pi<20; pi++ ) {
     //     printf("  %3d :  PID %7d  Status %6d  M1 %5d M2 %5d  D1 %5d D2 %5d  q %3d  m %8.3f  E %9.2f  Pt = %7.2f Eta = %9.3f\n",
     //        pi,
     //        Particle_PID[pi],
     //        Particle_Status[pi],
     //        Particle_M1[pi],
     //        Particle_M2[pi],
     //        Particle_D1[pi],
     //        Particle_D2[pi],
     //        Particle_Charge[pi],
     //        Particle_Mass[pi],
     //        Particle_E[pi],
     //        Particle_PT[pi],
     //        Particle_Eta[pi]
     //        ) ;
     //  }

         printf("\n\n Gen Jets:  %d\n", GenJet_ ) ;
         for ( int ji=0; ji<GenJet_; ji++ ) {
            printf(" %3d:  Pt = %9.2f  Eta = %7.3f  Phi = %7.3f\n",
               ji,
               GenJet_PT[ji],
               GenJet_Eta[ji],
               GenJet_Phi[ji]
               ) ;
         } // ji

         printf("\n\n Jets:  %d\n", Jet_ ) ;
         for ( int ji=0; ji<Jet_; ji++ ) {
            printf(" %3d:  Pt = %9.2f  Eta = %7.3f  Phi = %7.3f\n",
               ji,
               Jet_PT[ji],
               Jet_Eta[ji],
               Jet_Phi[ji]
               ) ;
         } // ji



         printf("  continue?  type q if no.   ") ;
         char answ = getchar() ;
         if ( answ == 'q' ) break ;

      } // verbose?



      int n_genjet_central(0) ;
      int n_genjet_forward(0) ;

      for ( int ji=0; ji<GenJet_; ji++ ) {
         if ( fabs( GenJet_Eta[ji] ) < 1.0 ) n_genjet_central ++ ;
         if ( GenJet_Eta[ji] > 2.5 && GenJet_Eta[ji] < 4.0 ) n_genjet_forward ++ ;
      }









   //----------------------------------------------------------------------------------------------------------
   //
   //

      if ( Jet_ >= 2 ) {

         int ind_gj0(-1) ;
         int ind_gj1(-1) ;
         float gj0dr = 9999999. ;
         float gj1dr = 9999999. ;
         for ( int ji=0; ji<GenJet_; ji++ ) {
            float dr0 = calc_dR( Jet_Phi[0], GenJet_Phi[ji], Jet_Eta[0], GenJet_Eta[ji] ) ;
            if ( dr0 < gj0dr ) {
               ind_gj0 = ji ;
               gj0dr = dr0 ;
            }
            float dr1 = calc_dR( Jet_Phi[1], GenJet_Phi[ji], Jet_Eta[1], GenJet_Eta[ji] ) ;
            if ( dr1 < gj1dr ) {
               ind_gj1 = ji ;
               gj1dr = dr1 ;
            }
         } // ji


         bool has_2gjm(false) ;
         if ( ind_gj0>=0 && ind_gj1>=0 && ind_gj0!=ind_gj1 && gj0dr<0.3 && gj1dr<0.3 ) has_2gjm = true ;

         float rec_dphi = calc_dphi( Jet_Phi[0], Jet_Phi[1] ) ;


         if ( Jet_PT[0] > 3.0 && Jet_PT[1] > 3.0 ) {

            float Pperp_random_sign = 1. ;
            if ( gRandom -> Integer(2) == 1 ) Pperp_random_sign = -1. ;

            float jet0px = Jet_PT[0]*cos(Jet_Phi[0]) ;
            float jet0py = Jet_PT[0]*sin(Jet_Phi[0]) ;
            float jet0theta = theta_from_eta( Jet_Eta[0] ) ;
            float jet0pz = Jet_PT[0] / tan(jet0theta) ;

            float jet1px = Jet_PT[1]*cos(Jet_Phi[1]) ;
            float jet1py = Jet_PT[1]*sin(Jet_Phi[1]) ;
            float jet1theta = theta_from_eta( Jet_Eta[1] ) ;
            float jet1pz = Jet_PT[1] / tan(jet1theta) ;

            float Pperpx = 0.5 * ( jet0px - jet1px ) * Pperp_random_sign ;
            float Pperpy = 0.5 * ( jet0py - jet1py ) * Pperp_random_sign ;
            float Pperp = sqrt( Pperpx*Pperpx + Pperpy*Pperpy ) ;

            float qperpx =       ( jet0px + jet1px ) ;
            float qperpy =       ( jet0py + jet1py ) ;
            float qperp = sqrt( qperpx*qperpx + qperpy*qperpy ) ;

            float phi_Pperp = atan2( Pperpy, Pperpx ) ;
            float phi_qperp = atan2( qperpy, qperpx ) ;

            float dphi_Pperp_qperp = calc_dphi( phi_Pperp, phi_qperp ) ;

            if ( qperp / Pperp < 222222222222 ) {

               h_r2j_rec_dphi_all -> Fill( rec_dphi ) ;
               h_r2j_gm0dr -> Fill( gj0dr ) ;
               h_r2j_gm1dr -> Fill( gj1dr ) ;
               if ( has_2gjm ) {

                  h_r2j_rec_dphi_2gjm -> Fill( rec_dphi ) ;
                  float phi0_recmgen = calc_dphi( Jet_Phi[0], GenJet_Phi[ind_gj0] ) ;
                  float phi1_recmgen = calc_dphi( Jet_Phi[1], GenJet_Phi[ind_gj1] ) ;
                  h_r2j_phi0_recmgen -> Fill( phi0_recmgen ) ;
                  h_r2j_phi1_recmgen -> Fill( phi1_recmgen ) ;
                  float eta0_recmgen = Jet_Eta[0] - GenJet_Eta[ind_gj0] ;
                  float eta1_recmgen = Jet_Eta[1] - GenJet_Eta[ind_gj1] ;
                  h_r2j_eta0_recmgen -> Fill( eta0_recmgen ) ;
                  h_r2j_eta1_recmgen -> Fill( eta1_recmgen ) ;





                  float genjet0px = GenJet_PT[ind_gj0]*cos(GenJet_Phi[ind_gj0]) ;
                  float genjet0py = GenJet_PT[ind_gj0]*sin(GenJet_Phi[ind_gj0]) ;

                  float genjet1px = GenJet_PT[ind_gj1]*cos(GenJet_Phi[ind_gj1]) ;
                  float genjet1py = GenJet_PT[ind_gj1]*sin(GenJet_Phi[ind_gj1]) ;

                  float genPperpx = 0.5 * ( genjet0px - genjet1px ) * Pperp_random_sign ;
                  float genPperpy = 0.5 * ( genjet0py - genjet1py ) * Pperp_random_sign ;
                  float genPperp = sqrt( genPperpx*genPperpx + genPperpy*genPperpy ) ;

                  float genqperpx =       ( genjet0px + genjet1px ) ;
                  float genqperpy =       ( genjet0py + genjet1py ) ;
                  float genqperp = sqrt( genqperpx*genqperpx + genqperpy*genqperpy ) ;

                  float phi_genPperp = atan2( genPperpy, genPperpx ) ;
                  float phi_genqperp = atan2( genqperpy, genqperpx ) ;

                  float dphi_genPperp_genqperp = calc_dphi( phi_genPperp, phi_genqperp ) ;

                  float dphi_Pperp_qperp_recmgen = calc_dphi( dphi_Pperp_qperp, dphi_genPperp_genqperp ) ;



                  h_r2j_Pperp -> Fill( Pperp ) ;
                  h_r2j_qperp -> Fill( qperp ) ;

                  h_r2j_qperp_vs_Pperp -> Fill( Pperp, qperp ) ;

                  h_r2j_Pperp_recmgen -> Fill( Pperp - genPperp ) ;
                  h_r2j_qperp_recmgen -> Fill( qperp - genqperp ) ;

                  h_r2j_Pperp_gen_vs_rec -> Fill( Pperp, genPperp ) ;
                  h_r2j_qperp_gen_vs_rec -> Fill( qperp, genqperp ) ;


                  h_r2j_qperp_over_Pperp -> Fill( qperp / Pperp ) ;


                  h_r2j_j1_vs_j0_pt -> Fill( Jet_PT[0], Jet_PT[1] ) ;
                  h_r2j_j1_vs_j0_eta -> Fill( Jet_Eta[0], Jet_Eta[1] ) ;
                  h_r2j_j1_vs_j0_pz -> Fill( jet0pz, jet1pz ) ;

                  h_r2j_dphi_Pperp_qperp -> Fill( dphi_Pperp_qperp ) ;
                  h_r2j_dphi_Pperp_qperp_gen -> Fill( dphi_genPperp_genqperp ) ;
                  h_r2j_dphi_Pperp_qperp_recmgen -> Fill( dphi_Pperp_qperp_recmgen ) ;

                  h_r2j_dphi_Pq_vs_dphi_jj -> Fill( rec_dphi, dphi_Pperp_qperp ) ;

                  if ( GenJet_ == 2 ) {
                     h_r2j_2gj_dphi_Pperp_qperp -> Fill( dphi_Pperp_qperp ) ;
                     h_r2j_2gj_dphi_Pperp_qperp_gen -> Fill( dphi_genPperp_genqperp ) ;
                     h_r2j_2gj_dphi_Pperp_qperp_recmgen -> Fill( dphi_Pperp_qperp_recmgen ) ;
                     h_r2j_2gj_dphi_Pq_vs_dphi_jj -> Fill( rec_dphi, dphi_Pperp_qperp ) ;
                  }
                  if ( GenJet_ == 3 ) {
                     h_r2j_3gj_dphi_Pperp_qperp -> Fill( dphi_Pperp_qperp ) ;
                     h_r2j_3gj_dphi_Pperp_qperp_gen -> Fill( dphi_genPperp_genqperp ) ;
                     h_r2j_3gj_dphi_Pperp_qperp_recmgen -> Fill( dphi_Pperp_qperp_recmgen ) ;
                     h_r2j_3gj_dphi_Pq_vs_dphi_jj -> Fill( rec_dphi, dphi_Pperp_qperp ) ;
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

                  printf("\n\n Jets:  %d\n", Jet_ ) ;
                  for ( int ji=0; ji<Jet_; ji++ ) {
                     printf(" %3d:  Pt = %9.2f  Eta = %7.3f  Phi = %7.3f  ",
                        ji,
                        Jet_PT[ji],
                        Jet_Eta[ji],
                        Jet_Phi[ji]
                        ) ;
                     if ( ji==0 && ind_gj0>=0 ) {
                        printf(" | gen jet match  %d  dR = %7.3f   Pt = (%9.2f) %9.2f  Eta = (%7.3f) %7.3f  Phi = (%7.3f) %7.3f",
                            ind_gj0, gj0dr,
                            Jet_PT[0], GenJet_PT[ind_gj0],
                            Jet_Eta[0], GenJet_Eta[ind_gj0],
                            Jet_Phi[0], GenJet_Phi[ind_gj0] ) ;
                     }
                     if ( ji==1 && ind_gj1>=0 ) {
                        printf(" | gen jet match  %d  dR = %7.3f   Pt = (%9.2f) %9.2f  Eta = (%7.3f) %7.3f  Phi = (%7.3f) %7.3f",
                            ind_gj1, gj1dr,
                            Jet_PT[1], GenJet_PT[ind_gj1],
                            Jet_Eta[1], GenJet_Eta[ind_gj1],
                            Jet_Phi[1], GenJet_Phi[ind_gj1] ) ;
                     }
                     printf("\n") ;
                  } // ji
                  printf("   Pperp = %6.2f (gen %6.2f)   phi %7.3f (gen %7.3f)\n", Pperp, genPperp, phi_Pperp, phi_genPperp ) ;
                  printf("   qperp = %6.2f (gen %6.2f)   phi %7.3f (gen %7.3f)\n", qperp, genqperp, phi_qperp, phi_genqperp ) ;
                  printf("\n\n") ;



               } // both jets gen matched?

            } // cut on p/P

         }


      }


   //
   //
   //----------------------------------------------------------------------------------------------------------







      int gen_pid1 = Particle_PID[4] ;
      int gen_pid2 = Particle_PID[5] ;

      h_gen_parton_eta2_vs_eta1_all -> Fill( Particle_Eta[4], Particle_Eta[5] ) ;
      if ( n_genjet_central==2 ) h_gen_parton_eta2_vs_eta1_2gen_central -> Fill( Particle_Eta[4], Particle_Eta[5] ) ;
      if ( n_genjet_forward==2 ) h_gen_parton_eta2_vs_eta1_2gen_forward -> Fill( Particle_Eta[4], Particle_Eta[5] ) ;


      h_njets -> Fill( GenJet_ ) ;

      h_log10x2_vs_log10x1_all -> Fill( log10(Event_X1[0]), log10(Event_X2[0]) ) ;

      if ( n_genjet_central==2 ) h_log10x2_vs_log10x1_2gen_central -> Fill( log10(Event_X1[0]), log10(Event_X2[0]) ) ;
      if ( n_genjet_forward==2 ) h_log10x2_vs_log10x1_2gen_forward -> Fill( log10(Event_X1[0]), log10(Event_X2[0]) ) ;
      if ( n_genjet_forward==1 && n_genjet_central==1 ) h_log10x2_vs_log10x1_1gen_central_1gen_forward -> Fill( log10(Event_X1[0]), log10(Event_X2[0]) ) ;
      h_ngenjet_forward_vs_central -> Fill( n_genjet_central, n_genjet_forward ) ;


      h_id2_vs_id1_all -> Fill( gen_pid1, gen_pid2 ) ;
      if ( n_genjet_central==2 ) h_id2_vs_id1_2gen_central -> Fill( gen_pid1, gen_pid2 ) ;
      if ( n_genjet_forward==2 ) h_id2_vs_id1_2gen_forward -> Fill( gen_pid1, gen_pid2 ) ;
      if ( n_genjet_forward==1 && n_genjet_central==1 ) h_id2_vs_id1_1gen_central_1gen_forward -> Fill( gen_pid1, gen_pid2 ) ;

      if ( n_genjet_forward==2 ) {

///      printf("\n\n Event %llu,  Event_ = %d\n", jentry, Event_ ) ;
///      printf("     Scale = %10.2f  AlphaQED = %10.6f  AlphaQCD = %9.3f  ID1 = %6d  ID2 = %6d  X1 = %7.5f  X2 = %7.5f\n",
///         Event_Scale[0],
///         Event_AlphaQED[0],
///         Event_AlphaQCD[0],
///         Event_ID1[0],
///         Event_ID2[0],
///         Event_X1[0],
///         Event_X2[0] ) ;

///      printf("     PID1 = %3d, PID2 = %3d\n", gen_pid1, gen_pid2 ) ;

///      for ( int pi=0; pi<Particle_; pi++ ) {
///         printf("  %3d :  PID %7d  Status %6d  M1 %5d M2 %5d  D1 %5d D2 %5d  q %3d  m %8.3f  E %9.2f  Pt = %7.2f Eta = %9.3f  Phi = %7.3f\n",
///            pi,
///            Particle_PID[pi],
///            Particle_Status[pi],
///            Particle_M1[pi],
///            Particle_M2[pi],
///            Particle_D1[pi],
///            Particle_D2[pi],
///            Particle_Charge[pi],
///            Particle_Mass[pi],
///            Particle_E[pi],
///            Particle_PT[pi],
///            Particle_Eta[pi],
///            Particle_Phi[pi]
///            ) ;
///      }

///      printf("\n\n Gen Jets:  %d\n", GenJet_ ) ;
///      for ( int ji=0; ji<GenJet_; ji++ ) {
///         printf(" %3d:  Pt = %9.2f  Eta = %7.3f  Phi = %7.3f\n",
///            ji,
///            GenJet_PT[ji],
///            GenJet_Eta[ji],
///            GenJet_Phi[ji]
///            ) ;
///      } // ji

///      printf("\n\n Jets:  %d\n", Jet_ ) ;
///      for ( int ji=0; ji<Jet_; ji++ ) {
///         printf(" %3d:  Pt = %9.2f  Eta = %7.3f  Phi = %7.3f\n",
///            ji,
///            Jet_PT[ji],
///            Jet_Eta[ji],
///            Jet_Phi[ji]
///            ) ;
///      } // ji
///      fflush(stdout) ;

      }


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








      if ( GenJet_PT[1]<8 ) continue ;

      h_dphi_pt12gt8 -> Fill( dphi ) ;
      h_deta_pt12gt8 -> Fill( deta ) ;




   } // jentry
   printf("\n\n Done.\n\n") ;

   saveHist( "ca2.root", "h*" ) ;

   loadHist( "ca2.root" ) ;

}











