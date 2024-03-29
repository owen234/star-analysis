#define calo_analysis4_cxx
#include "calo_analysis4.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "histio.c"


float pt_correction( float meas_pt ) {
   float x = meas_pt ;
   return 1.86233-0.667162*x+0.164494*x*x-0.0181387*x*x*x+0.000741937*x*x*x*x ;
}

float pt_shift( float meas_pt ) {
   float x = meas_pt ;
   return -0.990277+0.507769*x-0.0288964*x*x ;
}

void set_process_bin_labels( TH1F* hp ) {
   hp -> GetXaxis() -> SetBinLabel(1, "g g to g g : 111") ;
   hp -> GetXaxis() -> SetBinLabel(2, "g g to q qbar (uds) : 112") ;
   hp -> GetXaxis() -> SetBinLabel(3, "q g to q g : 113") ;
   hp -> GetXaxis() -> SetBinLabel(4, "g q to g q : 113") ;
   hp -> GetXaxis() -> SetBinLabel(5, "q q(bar)' to q q(bar)' : 114") ;
   hp -> GetXaxis() -> SetBinLabel(6, "qqbar to gg : 115") ;
   hp -> GetXaxis() -> SetBinLabel(7, "other") ;
}

bool is_quark( int pid ) {
   if ( pid > 0 && pid <= 6 ) return true ;
   return false ;
}
bool is_antiquark( int pid ) {
   if ( pid < 0 && pid >= -6 ) return true ;
   return false ;
}
bool is_gluon( int pid ) {
   if ( pid == 21 ) return true ;
   return false ;
}
bool is_q_or_qbar( int pid ) {
   if ( fabs(pid) > 0 && fabs(pid) <= 6 ) return true ;
   return false ;
}

int get_process( int pid2, int pid3, int pid4, int pid5 ) {

   if ( is_gluon(pid2) && is_gluon(pid3) && is_gluon(pid4) && is_gluon(pid5) ) return 1 ;

   if ( is_gluon(pid2) && is_gluon(pid3) && is_quark(pid4) && is_antiquark(pid5) ) return 2 ;
   if ( is_gluon(pid2) && is_gluon(pid3) && is_antiquark(pid4) && is_quark(pid5) ) return 2 ;

   if ( is_q_or_qbar(pid2) && is_gluon(pid3) && is_q_or_qbar(pid4) && is_gluon(pid5) && pid2 == pid4 && pid3 == pid5 ) return 3 ;
   if ( is_gluon(pid2) && is_q_or_qbar(pid3) && is_gluon(pid4) && is_q_or_qbar(pid5) && pid2 == pid4 && pid3 == pid5 ) return 4 ;

   if ( is_q_or_qbar(pid2) && is_q_or_qbar(pid3) && is_q_or_qbar(pid4) && is_q_or_qbar(pid5) && pid2 == pid4 && pid3 == pid5 ) return 5 ;

   if ( is_quark(pid2) && is_antiquark(pid3) && is_gluon(pid4) && is_gluon(pid5) ) return 6 ;
   if ( is_antiquark(pid2) && is_quark(pid3) && is_gluon(pid4) && is_gluon(pid5) ) return 6 ;

   //printf(" get_process : other : pid2 = %d, pid3 = %d, pid4 = %d, pid5 = %d\n", pid2, pid3, pid4, pid5 ) ;

   return 7 ;


}


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


bool inside_fiducial( float eta, float phi ) {

   if ( eta < 2.5 ) return false ;
   if ( eta > 4.0 ) return false ;

   float inner_x = 0.25 ;
   float outer_x = 1.40 ;
   float top_y = 0.885 ;
   float front_z = 7.0 ;

   float edge_buffer = 0.20 ;
   float edge_buffer_inner = 0.08 ;

   float theta = theta_from_eta( eta ) ;

   float rho = tan( theta ) * front_z ;
   float x = rho * cos(phi) ;
   float y = rho * sin(phi) ;

   if ( x > (inner_x + edge_buffer_inner) && x < (outer_x - edge_buffer)
     && y < (top_y - edge_buffer) && y > (-1*top_y + edge_buffer) ) {
      return true ;
   }

   if ( x > (-1*outer_x + edge_buffer) && x < (-1*inner_x - edge_buffer_inner)
     && y < (top_y - edge_buffer) && y > (-1*top_y + edge_buffer) ) {
      return true ;
   }

   return false ;

}


void calo_analysis4::Loop( bool verbose ) {

   TStopwatch tsw ;
   tsw.Start() ;
   double total_time(0.) ;

   if (fChain == 0) return;

   gDirectory -> Delete( "h*" ) ;

   TH1F* h_njets = new TH1F( "h_njets", "N jets (gen)", 8, -0.5, 7.5 ) ;

   TH2F* h_njets_rec_vs_gen = new TH2F( "h_njets_rec_vs_gen", "N jets, rec vs gen ", 8, -0.5, 7.5,  8, -0.5, 7.5 ) ;
   TH2F* h_njets_pt3_rec_vs_gen = new TH2F( "h_njets_pt3_rec_vs_gen", "N jets, Pt>3, rec vs gen ", 8, -0.5, 7.5,  8, -0.5, 7.5 ) ;
   TH2F* h_njets_pt4_rec_vs_gen = new TH2F( "h_njets_pt4_rec_vs_gen", "N jets, Pt>4, rec vs gen ", 8, -0.5, 7.5,  8, -0.5, 7.5 ) ;
   TH2F* h_njets_pt5_rec_vs_gen = new TH2F( "h_njets_pt5_rec_vs_gen", "N jets, Pt>5, rec vs gen ", 8, -0.5, 7.5,  8, -0.5, 7.5 ) ;
   TH2F* h_njets_pt6_rec_vs_gen = new TH2F( "h_njets_pt6_rec_vs_gen", "N jets, Pt>6, rec vs gen ", 8, -0.5, 7.5,  8, -0.5, 7.5 ) ;

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

   TH1F* h_r2j_dphijj_recmgen = new TH1F( "h_r2j_dphijj_recmgen", "phijj, rec - true", 100, -1., 1. ) ;

   TH1F* h_r2j_eta0_recmgen = new TH1F( "h_r2j_eta0_recmgen", "jet0, eta, rec - true", 100, -1., 1. ) ;
   TH1F* h_r2j_eta1_recmgen = new TH1F( "h_r2j_eta1_recmgen", "jet1, eta, rec - true", 100, -1., 1. ) ;

   TH1F* h_r2j_Pperp = new TH1F( "h_r2j_Pperp", "Rec 2 jets, Pperp rec", 100, 0., 8. ) ;
   TH1F* h_r2j_qperp = new TH1F( "h_r2j_qperp", "Rec 2 jets, qperp rec", 100, 0., 8. ) ;

   TH2F* h_r2j_qperp_vs_Pperp = new TH2F( "h_r2j_qperp_vs_Pperp", "Rec 2 jets, qperp vs Pperp", 60, 0., 8.,  60, 0., 8. ) ;
   TH2F* h_r2j_2gj_qperp_vs_Pperp = new TH2F( "h_r2j_2gj_qperp_vs_Pperp", "Rec 2 jets, 2 gen jets, qperp vs Pperp", 60, 0., 8.,  60, 0., 8. ) ;
   TH2F* h_r2j_3gj_qperp_vs_Pperp = new TH2F( "h_r2j_3gj_qperp_vs_Pperp", "Rec 2 jets, 3 gen jets, qperp vs Pperp", 60, 0., 8.,  60, 0., 8. ) ;

   TH1F* h_r2j_Pperp_recmgen = new TH1F( "h_r2j_Pperp_recmgen", "Rec 2 jets, Pperp, rec - true", 100, -2., 2. ) ;
   TH1F* h_r2j_qperp_recmgen = new TH1F( "h_r2j_qperp_recmgen", "Rec 2 jets, qperp, rec - true", 100, -2., 2. ) ;


   TH2F* h_r2j_Pperp_gen_vs_rec = new TH2F( "h_r2j_Pperp_gen_vs_rec", "Rec 2 jets, Pperp, gen vs rec", 60, 0., 8.,  60, 0., 8. ) ;
   TH2F* h_r2j_qperp_gen_vs_rec = new TH2F( "h_r2j_qperp_gen_vs_rec", "Rec 2 jets, qperp, gen vs rec", 60, 0., 8.,  60, 0., 8. ) ;

   TH2F* h_r2j_qperp_over_Pperp_rec_vs_gen = new TH2F( "h_r2j_qperp_over_Pperp_rec_vs_gen", "qperp/Pperp, rec vs gen", 60, 0., 2., 60, 0., 2. ) ;


   TH1F* h_r2j_qperp_over_Pperp = new TH1F( "h_r2j_qperp_over_Pperp", "Rec 2 jets, qperp/Pperp", 60, 0., 4. ) ;
   TH1F* h_r2j_2gj_qperp_over_Pperp = new TH1F( "h_r2j_2gj_qperp_over_Pperp", "Rec 2 jets, 2 gen jets, qperp/Pperp", 60, 0., 4. ) ;
   TH1F* h_r2j_3gj_qperp_over_Pperp = new TH1F( "h_r2j_3gj_qperp_over_Pperp", "Rec 2 jets, 3 gen jets, qperp/Pperp", 60, 0., 4. ) ;

   TH2F* h_r2j_j1_vs_j0_pt = new TH2F( "h_r2j_j1_vs_j0_pt", "Rec 2 jets, Jet 1 pt vs jet0 pt", 60, 0., 8.,  60, 0., 8. ) ;
   TH2F* h_r2j_2gj_j1_vs_j0_pt = new TH2F( "h_r2j_2gj_j1_vs_j0_pt", "Rec 2 jets, 2 gen jets, Jet 1 pt vs jet0 pt", 60, 0., 8.,  60, 0., 8. ) ;
   TH2F* h_r2j_3gj_j1_vs_j0_pt = new TH2F( "h_r2j_3gj_j1_vs_j0_pt", "Rec 2 jets, 3 gen jets, Jet 1 pt vs jet0 pt", 60, 0., 8.,  60, 0., 8. ) ;

   TH2F* h_r2j_j1_vs_j0_eta = new TH2F( "h_r2j_j1_vs_j0_eta", "Rec 2 jets, Jet 1 pt vs jet0 eta", 60, 2., 5.,  60, 2., 5. ) ;
   TH2F* h_r2j_j1_vs_j0_pz = new TH2F( "h_r2j_j1_vs_j0_pz", "Rec 2 jets, Jet 1 pt vs jet0 pz", 60, 0., 100.,  60, 0., 100. ) ;

   TH2F* h_r2j_j1_vs_j0_phi = new TH2F( "h_r2j_j1_vs_j0_phi", "Rec 2 jets, Jet 1 pt vs jet0 phi", 60, -3.2, 3.2,  60, -3.2, 3.2 ) ;
   TH2F* h_r2j_2gj_j1_vs_j0_phi = new TH2F( "h_r2j_2gj_j1_vs_j0_phi", "Rec 2 jets, 2 gen jets, Jet 1 pt vs jet0 phi", 60, -3.2, 3.2,  60, -3.2, 3.2 ) ;
   TH2F* h_r2j_3gj_j1_vs_j0_phi = new TH2F( "h_r2j_3gj_j1_vs_j0_phi", "Rec 2 jets, 3 gen jets, Jet 1 pt vs jet0 phi", 60, -3.2, 3.2,  60, -3.2, 3.2 ) ;


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

   TH2F* h_r2j_gpm_dphi_Pq_vs_dphi_jj = new TH2F( "h_r2j_gpm_dphi_Pq_vs_dphi_jj", "Rec 2 jets, delta phi P q vs delta phi jet jet, gen partons match", 60, -3.2, 3.2,  60, -3.2, 3.2 ) ;

   TH2F* h_r2j_dphicut_dphi_Pq_vs_dphi_jj = new TH2F( "h_r2j_dphicut_dphi_Pq_vs_dphi_jj", "Rec 2 jets, dphijj>pi/2, delta phi P q vs delta phi jet jet", 60, -3.2, 3.2,  60, -3.2, 3.2 ) ;
   TH2F* h_r2j_2gj_dphicut_dphi_Pq_vs_dphi_jj = new TH2F( "h_r2j_2gj_dphicut_dphi_Pq_vs_dphi_jj", "Rec 2 jets, dphijj>pi/2, 2 gen jets, delta phi P q vs delta phi jet jet", 60, -3.2, 3.2,  60, -3.2, 3.2 ) ;
   TH2F* h_r2j_3gj_dphicut_dphi_Pq_vs_dphi_jj = new TH2F( "h_r2j_3gj_dphicut_dphi_Pq_vs_dphi_jj", "Rec 2 jets, dphijj>pi/2, 3 gen jets, delta phi P q vs delta phi jet jet", 60, -3.2, 3.2,  60, -3.2, 3.2 ) ;



   TH1F* h_r2j_genjetht = new TH1F( "h_r2j_genjetht", "Rec 2 jets, gen jet HT for -1<eta<2", 60, 0., 20. ) ;
   TH1F* h_r2j_2gj_genjetht = new TH1F( "h_r2j_2gj_genjetht", "Rec 2 jets, 2 gen jets, gen jet HT for -1<eta<2", 60, 0., 20. ) ;
   TH1F* h_r2j_3gj_genjetht = new TH1F( "h_r2j_3gj_genjetht", "Rec 2 jets, 3 gen jets, gen jet HT for -1<eta<2", 60, 0., 20. ) ;


   TH2F* h_r2j_ptrec_over_ptgen_vs_eta = new TH2F( "h_r2j_ptrec_over_ptgen_vs_eta", "Pt(rec)/Pt(gen) vs eta", 40, 2.2, 4.2,  40, 0., 2.5 ) ;


   TH1F* h_r2j_qperpxory_recmgen = new TH1F( "h_r2j_qperpxory_recmgen", "qperp x or y component, rec-gen", 60, -3., 3. ) ;
   TH1F* h_r2j_2gj_qperpxory_recmgen = new TH1F( "h_r2j_2gj_qperpxory_recmgen", "qperp x or y component, rec-gen, 2 gen jets", 60, -3., 3. ) ;
   TH1F* h_r2j_3gj_qperpxory_recmgen = new TH1F( "h_r2j_3gj_qperpxory_recmgen", "qperp x or y component, rec-gen, 3 gen jets", 60, -3., 3. ) ;

   TH2F* h_r2j_dphijj_recmgen_vs_Pperp = new TH2F( "h_r2j_dphijj_recmgen_vs_Pperp", "dphijj, rec-gen, vs Pperp", 20, 0., 6., 20, -0.4, 0.4 ) ;
   TH2F* h_r2j_2gj_dphijj_recmgen_vs_Pperp = new TH2F( "h_r2j_2gj_dphijj_recmgen_vs_Pperp", "dphijj, rec-gen, vs Pperp, 2 gen jets", 20, 0., 6., 20, -0.4, 0.4 ) ;
   TH2F* h_r2j_3gj_dphijj_recmgen_vs_Pperp = new TH2F( "h_r2j_3gj_dphijj_recmgen_vs_Pperp", "dphijj, rec-gen, vs Pperp, 3 gen jets", 20, 0., 6., 20, -0.4, 0.4 ) ;

   TH2F* h_log10x2_vs_log10x1_sel = new TH2F( "h_log10x2_vs_log10x1_sel", "log10x1 vs log10x2, selected events", 60, -4., 1., 60, -4., 1. ) ;


   TH1F* h_parton0_dr = new TH1F( "h_parton0_dr", "Parton 0, dR", 100, 0., 5. ) ;
   TH1F* h_parton1_dr = new TH1F( "h_parton1_dr", "Parton 1, dR", 100, 0., 5. ) ;

   TH1F* h_2gj_parton0_dr = new TH1F( "h_2gj_parton0_dr", "Parton 0, dR, 2 gen jets", 100, 0., 5. ) ;
   TH1F* h_2gj_parton1_dr = new TH1F( "h_2gj_parton1_dr", "Parton 1, dR, 2 gen jets", 100, 0., 5. ) ;

   TH1F* h_3gj_parton0_dr = new TH1F( "h_3gj_parton0_dr", "Parton 0, dR, 3 gen jets", 100, 0., 5. ) ;
   TH1F* h_3gj_parton1_dr = new TH1F( "h_3gj_parton1_dr", "Parton 1, dR, 3 gen jets", 100, 0., 5. ) ;


   TH1F* h_parton_pt_all = new TH1F( "h_parton_pt_all", "Parton Pt, all", 40, 0., 8. ) ;
   TH1F* h_parton_pt_sel = new TH1F( "h_parton_pt_sel", "Parton Pt, sel", 40, 0., 8. ) ;

   TH1F* h_parton_pt_jpt30_all = new TH1F( "h_parton_pt_jpt30_all", "Parton Pt, jet Pt>3.0, all", 40, 0., 8. ) ;
   TH1F* h_parton_pt_jpt35_all = new TH1F( "h_parton_pt_jpt35_all", "Parton Pt, jet Pt>3.5, all", 40, 0., 8. ) ;
   TH1F* h_parton_pt_jpt40_all = new TH1F( "h_parton_pt_jpt40_all", "Parton Pt, jet Pt>4.0, all", 40, 0., 8. ) ;
   TH1F* h_parton_pt_jpt45_all = new TH1F( "h_parton_pt_jpt45_all", "Parton Pt, jet Pt>4.5, all", 40, 0., 8. ) ;
   TH1F* h_parton_pt_jpt50_all = new TH1F( "h_parton_pt_jpt50_all", "Parton Pt, jet Pt>5.0, all", 40, 0., 8. ) ;

   TH1F* h_parton_pt_jpt30_sel = new TH1F( "h_parton_pt_jpt30_sel", "Parton Pt, jet Pt>3.0, sel", 40, 0., 8. ) ;
   TH1F* h_parton_pt_jpt35_sel = new TH1F( "h_parton_pt_jpt35_sel", "Parton Pt, jet Pt>3.5, sel", 40, 0., 8. ) ;
   TH1F* h_parton_pt_jpt40_sel = new TH1F( "h_parton_pt_jpt40_sel", "Parton Pt, jet Pt>4.0, sel", 40, 0., 8. ) ;
   TH1F* h_parton_pt_jpt45_sel = new TH1F( "h_parton_pt_jpt45_sel", "Parton Pt, jet Pt>4.5, sel", 40, 0., 8. ) ;
   TH1F* h_parton_pt_jpt50_sel = new TH1F( "h_parton_pt_jpt50_sel", "Parton Pt, jet Pt>5.0, sel", 40, 0., 8. ) ;


   TH2F* h_log10x2_vs_log10x1_sel0 = new TH2F( "h_log10x2_vs_log10x1_sel0", "log10x1 vs log10x2, sel0: 2 jets", 60, -4., 1., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_log10x1_sel1 = new TH2F( "h_log10x2_vs_log10x1_sel1", "log10x1 vs log10x2, sel1: 2 jets, jet eta>2.6", 60, -4., 1., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_log10x1_sel2 = new TH2F( "h_log10x2_vs_log10x1_sel2", "log10x1 vs log10x2, sel2: 2 jets, jet eta>2.6, dphijj>pi/2", 60, -4., 1., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_log10x1_sel3 = new TH2F( "h_log10x2_vs_log10x1_sel3", "log10x1 vs log10x2, sel3: 2 jets, jet eta>2.6, dphijj>pi/2, no central Ht", 60, -4., 1., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_log10x1_sel3_pm = new TH2F( "h_log10x2_vs_log10x1_sel3_pm", "log10x1 vs log10x2, sel3: 2 jets, jet eta>2.6, dphijj>pi/2, no central Ht, parton matched", 60, -4., 1., 60, -4., 1. ) ;

   TH2F* h_genparton_etab_vs_etaa_sel0 = new TH2F( "h_genparton_etab_vs_etaa_sel0", "Gen parton, etab vs etaa, etaa > etab, sel0: 2 jets", 40, -6., 6.,  40, -6., 6. ) ;
   TH2F* h_genparton_etab_vs_etaa_sel1 = new TH2F( "h_genparton_etab_vs_etaa_sel1", "Gen parton, etab vs etaa, etaa > etab, sel1: 2 jets, jet eta>2.6", 40, -6., 6.,  40, -6., 6. ) ;
   TH2F* h_genparton_etab_vs_etaa_sel2 = new TH2F( "h_genparton_etab_vs_etaa_sel2", "Gen parton, etab vs etaa, etaa > etab, sel2: 2 jets, jet eta>2.6, dphijj>pi/2", 40, -6., 6.,  40, -6., 6. ) ;
   TH2F* h_genparton_etab_vs_etaa_sel3 = new TH2F( "h_genparton_etab_vs_etaa_sel3", "Gen parton, etab vs etaa, etaa > etab, sel3: 2 jets, jet eta>2.6, dphijj>pi/2, no central Ht", 40, -6., 6.,  40, -6., 6. ) ;

   TH2F* h_genparton_drb_vs_dra_sel0 = new TH2F( "h_genparton_drb_vs_dra_sel0", "Gen parton, DeltaR match with forward jet, sel0: 2 jets", 40, -1., 7., 40, -1., 7. ) ;
   TH2F* h_genparton_drb_vs_dra_sel1 = new TH2F( "h_genparton_drb_vs_dra_sel1", "Gen parton, DeltaR match with forward jet, sel1: 2 jets, jet eta>2.6", 40, -1., 7., 40, -1., 7. ) ;
   TH2F* h_genparton_drb_vs_dra_sel2 = new TH2F( "h_genparton_drb_vs_dra_sel2", "Gen parton, DeltaR match with forward jet, sel2: 2 jets, jet eta>2.6, dphijj>pi/2", 40, -1., 7., 40, -1., 7. ) ;
   TH2F* h_genparton_drb_vs_dra_sel3 = new TH2F( "h_genparton_drb_vs_dra_sel3", "Gen parton, DeltaR match with forward jet, sel3: 2 jets, jet eta>2.6, dphijj>pi/2, no central Ht", 40, -1., 7., 40, -1., 7. ) ;

   TH2F* h_myq2_vs_scale2 = new TH2F( "h_myq2_vs_scale2", "My q2 calc vs Pythia scale^2", 200, 0., 150.,  200, 0., 150. ) ;
   TH2F* h_myq2_vs_scale2_q_g = new TH2F( "h_myq2_vs_scale2_q_g", "My q2 calc vs Pythia scale^2, quark gluon", 200, 0., 150.,  200, 0., 150. ) ;
   TH2F* h_myq2_vs_scale2_g_g = new TH2F( "h_myq2_vs_scale2_g_g", "My q2 calc vs Pythia scale^2, gluon gluon", 200, 0., 150.,  200, 0., 150. ) ;
   TH2F* h_myq2_vs_scale2_q_q = new TH2F( "h_myq2_vs_scale2_q_q", "My q2 calc vs Pythia scale^2, quark quark", 200, 0., 150.,  200, 0., 150. ) ;
   TH2F* h_myq2_vs_scale2_q_qbar = new TH2F( "h_myq2_vs_scale2_q_qbar", "My q2 calc vs Pythia scale^2, quark antiquark, same flavor", 200, 0., 150.,  200, 0., 150. ) ;

   TH2F* h_myq2_vs_scale2_zoom = new TH2F( "h_myq2_vs_scale2_zoom", "My q2 calc vs Pythia scale^2", 100, 0., 20.,  100, 0., 20. ) ;


   TH2F* h_log10x2_vs_Pperp = new TH2F( "h_log10x2_vs_Pperp", "log10(x2) vs Pperp", 40, 0., 6.,  40, -4., 1. ) ;

   TH2F* h_jet0_eta_vs_pt_all = new TH2F( "h_jet0_eta_vs_pt_all", "jet0, eta vs pt, all", 40, 1.5, 8.,  40, 2.2, 4.3 ) ;
   TH2F* h_jet0_eta_vs_pt_gm = new TH2F( "h_jet0_eta_vs_pt_gm", "jet0, eta vs pt, gen matched", 40, 1.5, 8.,  40, 2.2, 4.3 ) ;
   TH2F* h_jet0_eta_vs_pt_pm = new TH2F( "h_jet0_eta_vs_pt_pm", "jet0, eta vs pt, parton matched", 40, 1.5, 8.,  40, 2.2, 4.3 ) ;
   TH2F* h_jet0_eta_vs_pt_gm_pm = new TH2F( "h_jet0_eta_vs_pt_gm_pm", "jet0, eta vs pt, gen matched and parton matched", 40, 1.5, 8.,  40, 2.2, 4.3 ) ;

   TH2F* h_jet1_eta_vs_pt_all = new TH2F( "h_jet1_eta_vs_pt_all", "jet1, eta vs pt, all", 40, 1.5, 8.,  40, 2.2, 4.3 ) ;
   TH2F* h_jet1_eta_vs_pt_gm = new TH2F( "h_jet1_eta_vs_pt_gm", "jet1, eta vs pt, gen matched", 40, 1.5, 8.,  40, 2.2, 4.3 ) ;
   TH2F* h_jet1_eta_vs_pt_pm = new TH2F( "h_jet1_eta_vs_pt_pm", "jet1, eta vs pt, parton matched", 40, 1.5, 8.,  40, 2.2, 4.3 ) ;
   TH2F* h_jet1_eta_vs_pt_gm_pm = new TH2F( "h_jet1_eta_vs_pt_gm_pm", "jet1, eta vs pt, gen matched and parton matched", 40, 1.5, 8.,  40, 2.2, 4.3 ) ;


   //TH2F* h_q2_vs_log10x2 = new TH2F( "h_log10q2_vs_log10x2", "Q2 vs x2", 40, -4., 1., 40, -1, 4 ) ;
   //TH2F* h_q2_vs_log10x2_gm = new TH2F( "h_log10q2_vs_log10x2_gm", "Q2 vs x2, jets gen matched", 40, -4., 1., 40, -1, 4 ) ;
   //TH2F* h_q2_vs_log10x2_gm_pm = new TH2F( "h_log10q2_vs_log10x2_gm_pm", "Q2 vs x2, jets gen matched, parton matched", 40, -4., 1., 40, -1, 4 ) ;
   //TH2F* h_q2_vs_log10x2_pm = new TH2F( "h_log10q2_vs_log10x2_pm", "Q2 vs x2, jets parton matched", 40, -4., 1., 40, -1, 4 ) ;

   TH2F* h_log10q2_vs_log10x2 = new TH2F( "h_log10q2_vs_log10x2", "Q2 vs x2", 40, -6., 0.001, 40, -1.5, 4.2 ) ;
   TH2F* h_log10q2_vs_log10x2_gm = new TH2F( "h_log10q2_vs_log10x2_gm", "Q2 vs x2, jets gen matched", 40, -6., 0.001, 40, -1.5, 4.2 ) ;
   TH2F* h_log10q2_vs_log10x2_gm_pm = new TH2F( "h_log10q2_vs_log10x2_gm_pm", "Q2 vs x2, jets gen matched, parton matched", 40, -6., 0.001, 40, -1.5, 4.2 ) ;
   TH2F* h_log10q2_vs_log10x2_pm = new TH2F( "h_log10q2_vs_log10x2_pm", "Q2 vs x2, jets parton matched", 40, -6., 0.001, 40, -1.5, 4.2 ) ;



   //TH2F* h_log10x2_vs_log10x1 = new TH2F( "h_log10x2_vs_log10x1", "log10x2 vs x2", 40, -4., 1., 40, -4, 1 ) ;
   //TH2F* h_log10x2_vs_log10x1_gm = new TH2F( "h_log10x2_vs_log10x1_gm", "log10x2 vs x2, jets gen matched", 40, -4., 1., 40, -4, 1 ) ;
   //TH2F* h_log10x2_vs_log10x1_gm_pm = new TH2F( "h_log10x2_vs_log10x1_gm_pm", "log10x2 vs x2, jets gen matched, parton matched", 40, -4., 1., 40, -4, 1 ) ;
   //TH2F* h_log10x2_vs_log10x1_pm = new TH2F( "h_log10x2_vs_log10x1_pm", "log10x2 vs x2, jets parton matched", 40, -4., 1., 40, -4, 1 ) ;

   TH2F* h_log10x2_vs_log10x1 = new TH2F( "h_log10x2_vs_log10x1", "log10x2 vs x2", 40, -5., 0.001, 40, -5, 0.001 ) ;
   TH2F* h_log10x2_vs_log10x1_gm = new TH2F( "h_log10x2_vs_log10x1_gm", "log10x2 vs x2, jets gen matched", 40, -5., 0.001, 40, -5, 0.001 ) ;
   TH2F* h_log10x2_vs_log10x1_gm_pm = new TH2F( "h_log10x2_vs_log10x1_gm_pm", "log10x2 vs x2, jets gen matched, parton matched", 40, -5., 0.001, 40, -5, 0.001 ) ;
   TH2F* h_log10x2_vs_log10x1_pm = new TH2F( "h_log10x2_vs_log10x1_pm", "log10x2 vs x2, jets parton matched", 40, -5., 0.001, 40, -5, 0.001 ) ;


   TH2F* h_j0_pzrec_vs_pzgen = new TH2F( "h_j0_pzrec_vs_pzgen", "jet0, pz rec vs pz gen", 40, 0., 80., 40, 0., 80. ) ;
   TH2F* h_j0_etagt3_pzrec_vs_pzgen = new TH2F( "h_j0_etagt3_pzrec_vs_pzgen", "jet0, eta>3, pz rec vs pz gen", 40, 0., 80., 40, 0., 80. ) ;


   TH2F* h_j_phi_vs_eta_all = new TH2F( "h_j_phi_vs_eta_all", "jet, phi vs eta, all", 100, 2.4, 4.1,  100, -3.14159265, 3.14159265 ) ;
   TH2F* h_j_phi_vs_eta_fid = new TH2F( "h_j_phi_vs_eta_fid", "jet, phi vs eta, fiducial", 100, 2.4, 4.1,  100, -3.14159265, 3.14159265 ) ;

   TH1F* h_n_fiducial = new TH1F( "h_n_fiducial", "Number of jets in FCS fiducial", 3, -0.5, 2.5 ) ;

   TH1F* h_jj_dphi_rec_all = new TH1F( "h_jj_dphi_rec_all", "jet jet dphi, rec, all", 40, 3.14159265/2., 3*3.14159265/2. ) ;
   TH1F* h_jj_dphi_rec_fid = new TH1F( "h_jj_dphi_rec_fid", "jet jet dphi, rec, fiducial", 40, 3.14159265/2., 3*3.14159265/2. ) ;

   TH1F* h_jj_dphi_rec_bothjgm_all = new TH1F( "h_jj_dphi_rec_bothjgm_all", "jet jet dphi, rec, both jets gen matched, all", 40, 3.14159265/2., 3*3.14159265/2. ) ;
   TH1F* h_jj_dphi_rec_bothjgm_fid = new TH1F( "h_jj_dphi_rec_bothjgm_fid", "jet jet dphi, rec, both jets gen matched, fiducial", 40, 3.14159265/2., 3*3.14159265/2. ) ;

   TH1F* h_jj_dphi_gen_all = new TH1F( "h_jj_dphi_gen_all", "jet jet dphi, gen, all", 40, 3.14159265/2., 3*3.14159265/2. ) ;
   TH1F* h_jj_dphi_gen_fid = new TH1F( "h_jj_dphi_gen_fid", "jet jet dphi, gen, fiducial", 40, 3.14159265/2., 3*3.14159265/2. ) ;


   TH2F* h_q2_vs_jet0pt_all = new TH2F( "h_q2_vs_jet0pt_all", "Q2 vs jet0pt, all", 20, 0., 8., 240, 0., 40. ) ;
   TH2F* h_q2_vs_jet0pt_gm = new TH2F( "h_q2_vs_jet0pt_gm", "Q2 vs jet0pt, jets gen matched", 20, 0., 8., 240, 0., 40. ) ;
   TH2F* h_q2_vs_jet0pt_pm = new TH2F( "h_q2_vs_jet0pt_pm", "Q2 vs jet0pt, jets parton matched", 20, 0., 8., 240, 0., 40. ) ;
   TH2F* h_q2_vs_jet0pt_gm_pm = new TH2F( "h_q2_vs_jet0pt_gm_pm", "Q2 vs jet0pt, jets gen matched and parton matched", 20, 0., 8., 240, 0., 40. ) ;

   TH2F* h_q2_vs_jet1pt_all = new TH2F( "h_q2_vs_jet1pt_all", "Q2 vs jet1pt, all", 20, 0., 8., 240, 0., 40. ) ;
   TH2F* h_q2_vs_jet1pt_gm = new TH2F( "h_q2_vs_jet1pt_gm", "Q2 vs jet1pt, jets gen matched", 20, 0., 8., 240, 0., 40. ) ;
   TH2F* h_q2_vs_jet1pt_pm = new TH2F( "h_q2_vs_jet1pt_pm", "Q2 vs jet1pt, jets parton matched", 20, 0., 8., 240, 0., 40. ) ;
   TH2F* h_q2_vs_jet1pt_gm_pm = new TH2F( "h_q2_vs_jet1pt_gm_pm", "Q2 vs jet1pt, jets gen matched and parton matched", 20, 0., 8., 240, 0., 40. ) ;

   TH2F* h_log10x2_vs_jet0pt_all = new TH2F( "h_log10x2_vs_jet0pt_all", "log10(x2) vs jet0pt, all", 20, 0., 8., 20, -4., 1. ) ;
   TH2F* h_log10x2_vs_jet0pt_gm = new TH2F( "h_log10x2_vs_jet0pt_gm", "log10(x2) vs jet0pt, jets gen matched", 20, 0., 8., 20, -4., 1. ) ;
   TH2F* h_log10x2_vs_jet0pt_pm = new TH2F( "h_log10x2_vs_jet0pt_pm", "log10(x2) vs jet0pt, jets parton matched", 20, 0., 8., 20, -4., 1. ) ;
   TH2F* h_log10x2_vs_jet0pt_gm_pm = new TH2F( "h_log10x2_vs_jet0pt_gm_pm", "log10(x2) vs jet0pt, jets gen matched and parton matched", 20, 0., 8., 20, -4., 1. ) ;

   TH2F* h_log10x2_vs_jet1pt_all = new TH2F( "h_log10x2_vs_jet1pt_all", "log10(x2) vs jet1pt, all", 20, 0., 8., 20, -4., 1. ) ;
   TH2F* h_log10x2_vs_jet1pt_gm = new TH2F( "h_log10x2_vs_jet1pt_gm", "log10(x2) vs jet1pt, jets gen matched", 20, 0., 8., 20, -4., 1. ) ;
   TH2F* h_log10x2_vs_jet1pt_pm = new TH2F( "h_log10x2_vs_jet1pt_pm", "log10(x2) vs jet1pt, jets parton matched", 20, 0., 8., 20, -4., 1. ) ;
   TH2F* h_log10x2_vs_jet1pt_gm_pm = new TH2F( "h_log10x2_vs_jet1pt_gm_pm", "log10(x2) vs jet1pt, jets gen matched and parton matched", 20, 0., 8., 20, -4., 1. ) ;

   TH2F* h_q2_vs_jet0eta_all = new TH2F( "h_q2_vs_jet0eta_all", "Q2 vs jet0eta, all", 20, 2.4, 4.2, 240, 0., 40. ) ;
   TH2F* h_q2_vs_jet0eta_gm = new TH2F( "h_q2_vs_jet0eta_gm", "Q2 vs jet0eta, jets gen matched", 20, 2.4, 4.2, 240, 0., 40. ) ;
   TH2F* h_q2_vs_jet0eta_pm = new TH2F( "h_q2_vs_jet0eta_pm", "Q2 vs jet0eta, jets parton matched", 20, 2.4, 4.2, 240, 0., 40. ) ;
   TH2F* h_q2_vs_jet0eta_gm_pm = new TH2F( "h_q2_vs_jet0eta_gm_pm", "Q2 vs jet0eta, jets gen matched and parton matched", 20, 2.4, 4.2, 240, 0., 40. ) ;

   TH2F* h_q2_vs_jet1eta_all = new TH2F( "h_q2_vs_jet1eta_all", "Q2 vs jet1eta, all", 20, 2.4, 4.2, 240, 0., 40. ) ;
   TH2F* h_q2_vs_jet1eta_gm = new TH2F( "h_q2_vs_jet1eta_gm", "Q2 vs jet1eta, jets gen matched", 20, 2.4, 4.2, 240, 0., 40. ) ;
   TH2F* h_q2_vs_jet1eta_pm = new TH2F( "h_q2_vs_jet1eta_pm", "Q2 vs jet1eta, jets parton matched", 20, 2.4, 4.2, 240, 0., 40. ) ;
   TH2F* h_q2_vs_jet1eta_gm_pm = new TH2F( "h_q2_vs_jet1eta_gm_pm", "Q2 vs jet1eta, jets gen matched and parton matched", 20, 2.4, 4.2, 240, 0., 40. ) ;

   TH1F* h_j0pt_all = new TH1F( "h_j0pt_all", "jet0 pt, all", 20, 0., 8. ) ;
   TH1F* h_j0pt_gm = new TH1F( "h_j0pt_gm", "jet0 pt, gen matched", 20, 0., 8. ) ;
   TH1F* h_j0pt_pm = new TH1F( "h_j0pt_pm", "jet0 pt, parton matched", 20, 0., 8. ) ;
   TH1F* h_j0pt_gm_pm = new TH1F( "h_j0pt_gm_pm", "jet0 pt, gen matched and parton matched", 20, 0., 8. ) ;

   TH1F* h_j1pt_all = new TH1F( "h_j1pt_all", "jet1 pt, all", 20, 0., 8. ) ;
   TH1F* h_j1pt_gm = new TH1F( "h_j1pt_gm", "jet1 pt, gen matched", 20, 0., 8. ) ;
   TH1F* h_j1pt_pm = new TH1F( "h_j1pt_pm", "jet1 pt, parton matched", 20, 0., 8. ) ;
   TH1F* h_j1pt_gm_pm = new TH1F( "h_j1pt_gm_pm", "jet1 pt, gen matched and parton matched", 20, 0., 8. ) ;
   TH1F* h_j1pt_bothpm = new TH1F( "h_j1pt_bothpm", "jet1 pt, both partons matched", 20, 0., 8. ) ;

   TH1F* h_javept_all = new TH1F( "h_javept_all", "jet ave pt, all", 20, 0., 8. ) ;
   TH1F* h_javept_gm = new TH1F( "h_javept_gm", "jet ave pt, both gen matched", 20, 0., 8. ) ;
   TH1F* h_javept_pm = new TH1F( "h_javept_pm", "jet ave pt, both partons matched", 20, 0., 8. ) ;
   TH1F* h_javept_gm_pm = new TH1F( "h_javept_gm_pm", "jet ave pt, both gen matched and parton matched", 20, 0., 8. ) ;

   TH2F* h_j1pt_vs_j0pt_all = new TH2F( "h_j1pt_vs_j0pt_all", "jet1 pt vs jet0 pt, all", 20, 0., 8., 20, 0., 8. ) ;
   TH2F* h_j1pt_vs_j0pt_gm = new TH2F( "h_j1pt_vs_j0pt_gm", "jet1 pt vs jet0 pt, both gen matched", 20, 0., 8., 20, 0., 8. ) ;
   TH2F* h_j1pt_vs_j0pt_pm = new TH2F( "h_j1pt_vs_j0pt_pm", "jet1 pt vs jet0 pt, both parton matched", 20, 0., 8., 20, 0., 8. ) ;
   TH2F* h_j1pt_vs_j0pt_gm_pm = new TH2F( "h_j1pt_vs_j0pt_gm_pm", "jet1 pt vs jet0 pt, both gen and parton matched", 20, 0., 8., 20, 0., 8. ) ;

   TH2F* h_j1eta_vs_j0eta_all = new TH2F( "h_j1eta_vs_j0eta_all", "jet1 eta vs jet0 eta, all", 20, 2.4, 4.2, 20, 2.4, 4.2 ) ;
   TH2F* h_j1eta_vs_j0eta_gm = new TH2F( "h_j1eta_vs_j0eta_gm", "jet1 eta vs jet0 eta, both gen matched", 20, 2.4, 4.2, 20, 2.4, 4.2 ) ;
   TH2F* h_j1eta_vs_j0eta_pm = new TH2F( "h_j1eta_vs_j0eta_pm", "jet1 eta vs jet0 eta, both parton matched", 20, 2.4, 4.2, 20, 2.4, 4.2 ) ;
   TH2F* h_j1eta_vs_j0eta_gm_pm = new TH2F( "h_j1eta_vs_j0eta_gm_pm", "jet1 eta vs jet0 eta, both gen and parton matched", 20, 2.4, 4.2, 20, 2.4, 4.2 ) ;

   TH1F* h_process_all = new TH1F( "h_process_all", "Process, all", 7, 0.5, 7.5 ) ;
   TH1F* h_process_gm = new TH1F( "h_process_gm", "Process, jets gen matched", 7, 0.5, 7.5 ) ;
   TH1F* h_process_pm = new TH1F( "h_process_pm", "Process, jets parton matched", 7, 0.5, 7.5 ) ;
   TH1F* h_process_gm_pm = new TH1F( "h_process_gm_pm", "Process, jets gen and parton matched", 7, 0.5, 7.5 ) ;
   set_process_bin_labels( h_process_all ) ;
   set_process_bin_labels( h_process_gm ) ;
   set_process_bin_labels( h_process_pm ) ;
   set_process_bin_labels( h_process_gm_pm ) ;


   TH1F* h_pthat_all = new TH1F( "h_pthat_all", "pthat, all", 80, 0., 8. ) ;
   TH1F* h_pthat_gm = new TH1F( "h_pthat_gm", "pthat, jets gen matched", 80, 0., 8. ) ;
   TH1F* h_pthat_pm = new TH1F( "h_pthat_pm", "pthat, jets parton matched", 80, 0., 8. ) ;
   TH1F* h_pthat_gm_pm = new TH1F( "h_pthat_gm_pm", "pthat, jets gen and parton matched", 80, 0., 8. ) ;


   TH1F* h_pthat_pt30_all = new TH1F( "h_pthat_pt30_all", "pthat, jet pt > 3.0, all", 80, 0., 8. ) ;
   TH1F* h_pthat_pt35_all = new TH1F( "h_pthat_pt35_all", "pthat, jet pt > 3.5, all", 80, 0., 8. ) ;
   TH1F* h_pthat_pt40_all = new TH1F( "h_pthat_pt40_all", "pthat, jet pt > 4.0, all", 80, 0., 8. ) ;
   TH1F* h_pthat_pt45_all = new TH1F( "h_pthat_pt45_all", "pthat, jet pt > 4.5, all", 80, 0., 8. ) ;
   TH1F* h_pthat_pt50_all = new TH1F( "h_pthat_pt50_all", "pthat, jet pt > 5.0, all", 80, 0., 8. ) ;
   TH1F* h_pthat_pt55_all = new TH1F( "h_pthat_pt55_all", "pthat, jet pt > 5.5, all", 80, 0., 8. ) ;

   TH1F* h_pthat_pt30_pm = new TH1F( "h_pthat_pt30_pm", "pthat, jet pt > 3.0, parton matched", 80, 0., 8. ) ;
   TH1F* h_pthat_pt35_pm = new TH1F( "h_pthat_pt35_pm", "pthat, jet pt > 3.5, parton matched", 80, 0., 8. ) ;
   TH1F* h_pthat_pt40_pm = new TH1F( "h_pthat_pt40_pm", "pthat, jet pt > 4.0, parton matched", 80, 0., 8. ) ;
   TH1F* h_pthat_pt45_pm = new TH1F( "h_pthat_pt45_pm", "pthat, jet pt > 4.5, parton matched", 80, 0., 8. ) ;
   TH1F* h_pthat_pt50_pm = new TH1F( "h_pthat_pt50_pm", "pthat, jet pt > 5.0, parton matched", 80, 0., 8. ) ;
   TH1F* h_pthat_pt55_pm = new TH1F( "h_pthat_pt55_pm", "pthat, jet pt > 5.5, parton matched", 80, 0., 8. ) ;


   TH1F* h_jj_dphi_precut = new TH1F( "h_jj_dphi_precut", "jet jet dphi, pre cut", 80, 0., 2*3.14159265 ) ;
   TH1F* h_jj_dphi_precut_pm = new TH1F( "h_jj_dphi_precut_pm", "jet jet dphi, pre cut, both jets parton matched", 80, 0., 2*3.14159265 ) ;


   TH2F* h_gp1dr_vs_gp0dr_sel0 = new TH2F( "h_gp1dr_vs_gp0dr_sel0", "Parton match dR, jet1 vs jet0, sel0", 40, 0., 8., 40, 0., 8. ) ;
   TH2F* h_gp1dr_vs_gp0dr_sel1 = new TH2F( "h_gp1dr_vs_gp0dr_sel1", "Parton match dR, jet1 vs jet0, sel1", 40, 0., 8., 40, 0., 8. ) ;
   TH2F* h_gp1dr_vs_gp0dr_sel2 = new TH2F( "h_gp1dr_vs_gp0dr_sel2", "Parton match dR, jet1 vs jet0, sel2", 40, 0., 8., 40, 0., 8. ) ;
   TH2F* h_gp1dr_vs_gp0dr_sel3 = new TH2F( "h_gp1dr_vs_gp0dr_sel3", "Parton match dR, jet1 vs jet0, sel3", 40, 0., 8., 40, 0., 8. ) ;

   TH2F* h_jet1pt_vs_jet0pt_sel0 = new TH2F( "h_jet1pt_vs_jet0pt_sel0", "jet1pt vs jet0pt, sel0", 40, 0., 8., 40, 0., 8. ) ;
   TH2F* h_jet1pt_vs_jet0pt_sel1 = new TH2F( "h_jet1pt_vs_jet0pt_sel1", "jet1pt vs jet0pt, sel1", 40, 0., 8., 40, 0., 8. ) ;
   TH2F* h_jet1pt_vs_jet0pt_sel2 = new TH2F( "h_jet1pt_vs_jet0pt_sel2", "jet1pt vs jet0pt, sel2", 40, 0., 8., 40, 0., 8. ) ;
   TH2F* h_jet1pt_vs_jet0pt_sel3 = new TH2F( "h_jet1pt_vs_jet0pt_sel3", "jet1pt vs jet0pt, sel3", 40, 0., 8., 40, 0., 8. ) ;
   TH2F* h_jet1pt_vs_jet0pt_sel3_pm = new TH2F( "h_jet1pt_vs_jet0pt_sel3_pm", "jet1pt vs jet0pt, sel3, parton matched", 40, 0., 8., 40, 0., 8. ) ;

   TH2F* h_jet1pt_vs_jet0pt_sel3_v2 = new TH2F( "h_jet1pt_vs_jet0pt_sel3_v2", "jet1pt vs jet0pt, sel3", 50, 0., 10., 50, 0., 10. ) ;


   TH2F* h_jet1eta_vs_jet0eta_sel0 = new TH2F( "h_jet1eta_vs_jet0eta_sel0", "jet1eta vs jet0eta, sel0",   36, 2.4, 4.2, 36, 2.4, 4.2  ) ;
   TH2F* h_jet1eta_vs_jet0eta_sel1 = new TH2F( "h_jet1eta_vs_jet0eta_sel1", "jet1eta vs jet0eta, sel1",   36, 2.4, 4.2, 36, 2.4, 4.2  ) ;
   TH2F* h_jet1eta_vs_jet0eta_sel2 = new TH2F( "h_jet1eta_vs_jet0eta_sel2", "jet1eta vs jet0eta, sel2",   36, 2.4, 4.2, 36, 2.4, 4.2  ) ;
   TH2F* h_jet1eta_vs_jet0eta_sel3 = new TH2F( "h_jet1eta_vs_jet0eta_sel3", "jet1eta vs jet0eta, sel3",   36, 2.4, 4.2, 36, 2.4, 4.2  ) ;
   TH2F* h_jet1eta_vs_jet0eta_sel3_pm = new TH2F( "h_jet1eta_vs_jet0eta_sel3_pm", "jet1eta vs jet0eta, sel3, parton matched",   36, 2.4, 4.2, 36, 2.4, 4.2  ) ;

   TH1F* h_r2j_genjetht_sel0 = new TH1F( "h_r2j_genjetht_sel0", "gen jet HT for -1<eta<2, sel0", 60, 0., 20. ) ;
   TH1F* h_r2j_genjetht_sel1 = new TH1F( "h_r2j_genjetht_sel1", "gen jet HT for -1<eta<2, sel1", 60, 0., 20. ) ;
   TH1F* h_r2j_genjetht_sel2 = new TH1F( "h_r2j_genjetht_sel2", "gen jet HT for -1<eta<2, sel2", 60, 0., 20. ) ;
   TH1F* h_r2j_genjetht_sel3 = new TH1F( "h_r2j_genjetht_sel3", "gen jet HT for -1<eta<2, sel3", 60, 0., 20. ) ;

   TH1F* h_r2j_genjetht_sel0_pm = new TH1F( "h_r2j_genjetht_sel0_pm", "gen jet HT for -1<eta<2, sel0, parton matched", 60, 0., 20. ) ;
   TH1F* h_r2j_genjetht_sel1_pm = new TH1F( "h_r2j_genjetht_sel1_pm", "gen jet HT for -1<eta<2, sel1, parton matched", 60, 0., 20. ) ;
   TH1F* h_r2j_genjetht_sel2_pm = new TH1F( "h_r2j_genjetht_sel2_pm", "gen jet HT for -1<eta<2, sel2, parton matched", 60, 0., 20. ) ;
   TH1F* h_r2j_genjetht_sel3_pm = new TH1F( "h_r2j_genjetht_sel3_pm", "gen jet HT for -1<eta<2, sel3, parton matched", 60, 0., 20. ) ;

   TH1F* h_r2j_genjetht_sel0_npm = new TH1F( "h_r2j_genjetht_sel0_npm", "gen jet HT for -1<eta<2, sel0, not parton matched", 60, 0., 20. ) ;
   TH1F* h_r2j_genjetht_sel1_npm = new TH1F( "h_r2j_genjetht_sel1_npm", "gen jet HT for -1<eta<2, sel1, not parton matched", 60, 0., 20. ) ;
   TH1F* h_r2j_genjetht_sel2_npm = new TH1F( "h_r2j_genjetht_sel2_npm", "gen jet HT for -1<eta<2, sel2, not parton matched", 60, 0., 20. ) ;
   TH1F* h_r2j_genjetht_sel3_npm = new TH1F( "h_r2j_genjetht_sel3_npm", "gen jet HT for -1<eta<2, sel3, not parton matched", 60, 0., 20. ) ;

   TH2F* h_r2j_genjetht_vs_log10x2_sel0 = new TH2F( "h_r2j_genjetht_vs_log10x2_sel0", "gen jet HT for -1<eta<2 vs x2, sel0", 60, -4., 1., 60, 0., 20. ) ;
   TH2F* h_r2j_genjetht_vs_log10x2_sel0_pm = new TH2F( "h_r2j_genjetht_vs_log10x2_sel0_pm", "gen jet HT for -1<eta<2 vs x2, sel0, parton matched", 60, -4., 1., 60, 0., 20. ) ;

   TH1F* h_qperp_sel3 = new TH1F( "h_qperp_sel3", "qperp", 40, 0., 10. ) ;
   TH1F* h_qperp_sel3_pm = new TH1F( "h_qperp_sel3_pm", "qperp, parton matched", 40, 0., 10. ) ;

   TH1F* h_qperp_over_pperp_sel3 = new TH1F( "h_qperp_over_pperp_sel3", "qperp/Pperp", 42, 0., 2.1 ) ;
   TH1F* h_qperp_over_pperp_sel3_pm = new TH1F( "h_qperp_over_pperp_sel3_pm", "qperp/Pperp, parton matched", 42, 0., 2.1 ) ;

   TH2F* h_qperp_vs_Pperp_sel3 = new TH2F( "h_qperp_vs_Pperp_sel3", "qperp vs Pperp", 40, 0., 8.,  40, 0., 8. ) ;
   TH2F* h_qperp_vs_Pperp_sel3_pm = new TH2F( "h_qperp_vs_Pperp_sel3_pm", "qperp vs Pperp, parton matched", 40, 0., 8.,  40, 0., 8. ) ;

   TH2F* h_log10x2_vs_log10x1_sel4 = new TH2F( "h_log10x2_vs_log10x1_sel4", "log10x2 vs x2, sel4", 60, -4., 1., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_log10x1_sel4_pm = new TH2F( "h_log10x2_vs_log10x1_sel4_pm", "log10x2 vs x2, sel4, parton matched", 60, -4., 1., 60, -4., 1. ) ;


   TH1F* h_genparticleht_sel2 = new TH1F( "h_genparticleht_sel2", "gen particle HT, sel2", 60, 0., 60. ) ;
   TH1F* h_genparticleht_sel3 = new TH1F( "h_genparticleht_sel3", "gen particle HT, sel3", 60, 0., 60. ) ;
   TH1F* h_genparticleht_sel2_pm = new TH1F( "h_genparticleht_sel2_pm", "gen particle HT, sel2, parton matched", 60, 0., 60. ) ;
   TH1F* h_genparticleht_sel3_pm = new TH1F( "h_genparticleht_sel3_pm", "gen particle HT, sel3, parton matched", 60, 0., 60. ) ;


   TH2F* h_dphiqp_rec_vs_gen_qoplt03 = new TH2F( "h_dphiqp_rec_vs_gen_qoplt03", "delta phi(qperp, Pperp), rec vs gen, for q/P<0.3", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;
   TH2F* h_dphiqp_rec_vs_gen_qoplt03_pm = new TH2F( "h_dphiqp_rec_vs_gen_qoplt03_pm", "delta phi(qperp, Pperp), rec vs gen, for q/P<0.3, parton matched", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;

   TH2F* h_dphiqp_rec_vs_gen_qoplt03_gjeta26 = new TH2F( "h_dphiqp_rec_vs_gen_qoplt03_gjeta26", "delta phi(qperp, Pperp), rec vs gen, for q/P<0.3, gen jet eta>2.6", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;
   TH2F* h_dphiqp_rec_vs_gen_qoplt03_gjeta26_pm = new TH2F( "h_dphiqp_rec_vs_gen_qoplt03_gjeta26_pm", "delta phi(qperp, Pperp), rec vs gen, for q/P<0.3, parton matched, gen jet eta>2.6", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;

   TH2F* h_dphiqp_rec_vs_gen_qoplt03_gjeta30 = new TH2F( "h_dphiqp_rec_vs_gen_qoplt03_gjeta30", "delta phi(qperp, Pperp), rec vs gen, for q/P<0.3, gen jet eta>3.0", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;
   TH2F* h_dphiqp_rec_vs_gen_qoplt03_gjeta30_pm = new TH2F( "h_dphiqp_rec_vs_gen_qoplt03_gjeta30_pm", "delta phi(qperp, Pperp), rec vs gen, for q/P<0.3, parton matched, gen jet eta>3.0", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;

   TH2F* h_dphiqp_rec_vs_gen_qoplt10 = new TH2F( "h_dphiqp_rec_vs_gen_qoplt10", "delta phi(qperp, Pperp), rec vs gen, for q/P<1.0", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;
   TH2F* h_dphiqp_rec_vs_gen_qoplt10_pm = new TH2F( "h_dphiqp_rec_vs_gen_qoplt10_pm", "delta phi(qperp, Pperp), rec vs gen, for q/P<1.0, parton matched", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;

   TH2F* h_dphijj_rec_vs_gen = new TH2F( "h_dphijj_rec_vs_gen", "delta phi(jj), rec vs gen", 60, 3.14159265/2., 3*3.14159265/2.,  60, 3.14159265/2., 3*3.14159265/2. ) ;

   TH2F* h_dphiqp_rec_vs_gen_tightdphi = new TH2F( "h_dphiqp_rec_vs_gen_tightdphi", "delta phi(qperp, Pperp), rec vs gen, tight dphijj cut", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;
   TH2F* h_dphiqp_rec_vs_gen_tightdphi_pm = new TH2F( "h_dphiqp_rec_vs_gen_tightdphi_pm", "delta phi(qperp, Pperp), rec vs gen, tight dphijj cut, parton matched", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;

   TH2F* h_dphiqp_rec_vs_gen_tightdphi_rec_rewrap = new TH2F( "h_dphiqp_rec_vs_gen_tightdphi_rec_rewrap", "delta phi(qperp, Pperp), rec vs gen, tight dphijj cut", 60, -3.2, 3.2, 120, -2*3.2, 2*3.2 ) ;
   TH2F* h_dphiqp_rec_vs_gen_tightdphi_rec_rewrap_pm = new TH2F( "h_dphiqp_rec_vs_gen_tightdphi_rec_rewrap_pm", "delta phi(qperp, Pperp), rec vs gen, tight dphijj cut, parton matched", 60, -3.2, 3.2, 120, -2*3.2, 2*3.2 ) ;

   TH2F* h_dphiqp_rec_vs_gen_tightdphi_qoplt05 = new TH2F( "h_dphiqp_rec_vs_gen_tightdphi_qoplt05", "delta phi(qperp, Pperp), rec vs gen, tight dphijj cut, q/P<0.5", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;


   TH2F* h_log10x2_vs_qperp_sel2 = new TH2F( "h_log10x2_vs_qperp_sel2", "log10 x2 vs qperp, sel2", 60, 0., 6., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_qperp_sel3 = new TH2F( "h_log10x2_vs_qperp_sel3", "log10 x2 vs qperp, sel3", 60, 0., 6., 60, -4., 1. ) ;

   TH2F* h_log10x2_vs_qperp_Pperp4_sel2 = new TH2F( "h_log10x2_vs_qperp_Pperp4_sel2", "log10 x2 vs qperp, Pperp>4, sel2", 60, 0., 6., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_qperp_Pperp4_sel3 = new TH2F( "h_log10x2_vs_qperp_Pperp4_sel3", "log10 x2 vs qperp, Pperp>4, sel3", 60, 0., 6., 60, -4., 1. ) ;

   TH2F* h_log10x2_vs_qperp_Pperp30to35_sel2 = new TH2F( "h_log10x2_vs_qperp_Pperp30to35_sel2", "log10 x2 vs qperp, 3.0<Pperp<3.5, sel2", 60, 0., 6., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_qperp_Pperp30to35_sel3 = new TH2F( "h_log10x2_vs_qperp_Pperp30to35_sel3", "log10 x2 vs qperp, 3.0<Pperp<3.5, sel3", 60, 0., 6., 60, -4., 1. ) ;

   TH2F* h_log10x2_vs_qperp_Pperp35to40_sel2 = new TH2F( "h_log10x2_vs_qperp_Pperp35to40_sel2", "log10 x2 vs qperp, 3.5<Pperp<4.0, sel2", 60, 0., 6., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_qperp_Pperp35to40_sel3 = new TH2F( "h_log10x2_vs_qperp_Pperp35to40_sel3", "log10 x2 vs qperp, 3.5<Pperp<4.0, sel3", 60, 0., 6., 60, -4., 1. ) ;

   TH2F* h_log10x2_vs_qperp_Pperp40to45_sel2 = new TH2F( "h_log10x2_vs_qperp_Pperp40to45_sel2", "log10 x2 vs qperp, 4.0<Pperp<4.5, sel2", 60, 0., 6., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_qperp_Pperp40to45_sel3 = new TH2F( "h_log10x2_vs_qperp_Pperp40to45_sel3", "log10 x2 vs qperp, 4.0<Pperp<4.5, sel3", 60, 0., 6., 60, -4., 1. ) ;

   TH2F* h_log10x2_vs_qperp_Pperp45_sel2 = new TH2F( "h_log10x2_vs_qperp_Pperp45_sel2", "log10 x2 vs qperp, 4.5<Pperp, sel2", 60, 0., 6., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_qperp_Pperp45_sel3 = new TH2F( "h_log10x2_vs_qperp_Pperp45_sel3", "log10 x2 vs qperp, 4.5<Pperp, sel3", 60, 0., 6., 60, -4., 1. ) ;

   TH2F* h_log10x2_vs_qoverp_sel2 = new TH2F( "h_log10x2_vs_qoverp_sel2", "log10 x2 vs qperp/Pperp, sel2", 60, 0., 3., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_qoverp_sel2_pm = new TH2F( "h_log10x2_vs_qoverp_sel2_pm", "log10 x2 vs qperp/Pperp, sel2, parton matched", 60, 0., 3., 60, -4., 1. ) ;

   TH2F* h_log10x2_vs_pt1_sel2 = new TH2F( "h_log10x2_vs_pt1_sel2", "log10 x2 vs jet1 pt, sel2", 60, 0., 6., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_pt1_sel2_pm = new TH2F( "h_log10x2_vs_pt1_sel2_pm", "log10 x2 vs jet1 pt, sel2, parton matched", 60, 0., 6., 60, -4., 1. ) ;

   TH2F* h_log10x2_vs_pt0_sel2 = new TH2F( "h_log10x2_vs_pt0_sel2", "log10 x2 vs jet0 pt, sel2", 100, 0., 10., 60, -4., 1. ) ;
   TH2F* h_log10x2_vs_pt0_sel2_pm = new TH2F( "h_log10x2_vs_pt0_sel2_pm", "log10 x2 vs jet0 pt, sel2, parton matched", 100, 0., 10., 60, -4., 1. ) ;

   TH2F* h_log10x2_vs_qperp_pt1gt4_sel2 = new TH2F( "h_log10x2_vs_qperp_pt1gt4_sel2", "log10 x2 vs qperp, jet pt1 > 4 sel2", 60, 0., 6., 60, -4., 1. ) ;


   TH1F* h_log10x2_Pperp_30to35 = new TH1F( "h_log10x2_Pperp_30to35", "log10 x2, 3.0 < Pperp < 3.5", 60, -4., 1. ) ;
   TH1F* h_log10x2_Pperp_35to40 = new TH1F( "h_log10x2_Pperp_35to40", "log10 x2, 3.5 < Pperp < 4.0", 60, -4., 1. ) ;
   TH1F* h_log10x2_Pperp_40     = new TH1F( "h_log10x2_Pperp_40",     "log10 x2, Pperp > 4.0"      , 60, -4., 1. ) ;
   TH1F* h_log10x2_Pperp_40to45 = new TH1F( "h_log10x2_Pperp_40to45", "log10 x2, 4.0 < Pperp < 4.5", 60, -4., 1. ) ;
   TH1F* h_log10x2_Pperp_45     = new TH1F( "h_log10x2_Pperp_45",     "log10 x2, Pperp > 4.5"      , 60, -4., 1. ) ;

   TH1F* h_log10x2_Pperp_30to35_pm = new TH1F( "h_log10x2_Pperp_30to35_pm", "log10 x2, 3.0 < Pperp < 3.5, parton matched", 60, -4., 1. ) ;
   TH1F* h_log10x2_Pperp_35to40_pm = new TH1F( "h_log10x2_Pperp_35to40_pm", "log10 x2, 3.5 < Pperp < 4.0, parton matched", 60, -4., 1. ) ;
   TH1F* h_log10x2_Pperp_40_pm     = new TH1F( "h_log10x2_Pperp_40_pm",     "log10 x2, Pperp > 4.0, parton matched"      , 60, -4., 1. ) ;
   TH1F* h_log10x2_Pperp_40to45_pm = new TH1F( "h_log10x2_Pperp_40to45_pm", "log10 x2, 4.0 < Pperp < 4.5, parton matched", 60, -4., 1. ) ;
   TH1F* h_log10x2_Pperp_45_pm     = new TH1F( "h_log10x2_Pperp_45_pm",     "log10 x2, Pperp > 4.5, parton matched"      , 60, -4., 1. ) ;


   TH2F* h_cos2phiqp_vs_qperp_tightdphi = new TH2F( "h_cos2phiqp_vs_qperp_tightdphi", "cos(2phiqp) vs qperp, tightdphi", 60, 0., 3., 60, -1.1, 1.1 ) ;
   TH2F* h_cos2phiqp_vs_qperp_tightdphi_gen = new TH2F( "h_cos2phiqp_vs_qperp_tightdphi_gen", "cos(2phiqp) vs qperp, tightdphi, gen", 60, 0., 3., 60, -1.1, 1.1 ) ;

   TH2F* h_dphiqp_rec_vs_gen_qoplt03_tightgmdr = new TH2F( "h_dphiqp_rec_vs_gen_qoplt03_tightgmdr", "delta phi(qperp, Pperp), rec vs gen, q/P<0.3, tight jet dR matching", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;

   TH2F* h_jet0_ptrec_over_ptgen_vs_ptgen = new TH2F( "h_jet0_ptrec_over_ptgen_vs_ptgen", "jet0, ptrec/ptgen vs ptgen", 60, 0., 8., 60, 0., 2. ) ;
   TH2F* h_jet1_ptrec_over_ptgen_vs_ptgen = new TH2F( "h_jet1_ptrec_over_ptgen_vs_ptgen", "jet1, ptrec/ptgen vs ptgen", 60, 0., 8., 60, 0., 2. ) ;

   TH2F* h_jet0_ptrec_over_ptgen_vs_ptrec = new TH2F( "h_jet0_ptrec_over_ptgen_vs_ptrec", "jet0, ptrec/ptgen vs ptrec", 60, 0., 8., 60, 0., 2. ) ;
   TH2F* h_jet1_ptrec_over_ptgen_vs_ptrec = new TH2F( "h_jet1_ptrec_over_ptgen_vs_ptrec", "jet1, ptrec/ptgen vs ptrec", 60, 0., 8., 60, 0., 2. ) ;

   TH2F* h_dphiqp_rec_vs_gen_qoplt03_tightde = new TH2F( "h_dphiqp_rec_vs_gen_qoplt03_tightde", "delta phi(qperp, Pperp), rec vs gen, q/P<0.3, tight jet energy matching", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;

   TH2F* h_jet0_ptgen_over_ptrec_vs_ptrec = new TH2F( "h_jet0_ptgen_over_ptrec_vs_ptrec", "jet0, ptgen/ptrec vs ptrec", 60, 0., 8., 60, 0., 2. ) ;
   TH2F* h_jet1_ptgen_over_ptrec_vs_ptrec = new TH2F( "h_jet1_ptgen_over_ptrec_vs_ptrec", "jet1, ptgen/ptrec vs ptrec", 60, 0., 8., 60, 0., 2. ) ;


   TH2F* h_jet0_ptrec_vs_ptgen_raw = new TH2F( "h_jet0_ptrec_vs_ptgen_raw", "jet0 ptrec vs ptgen, raw", 60, 0., 8., 60, 0., 8. ) ;
   TH2F* h_jet0_ptgen_vs_ptrec_raw = new TH2F( "h_jet0_ptgen_vs_ptrec_raw", "jet0 ptgen vs ptrec, raw", 60, 0., 8., 60, 0., 8. ) ;
   TH2F* h_jet0_ptrec_vs_ptgen_corrected = new TH2F( "h_jet0_ptrec_vs_ptgen_corrected", "jet0 ptrec vs ptgen, corrected", 60, 0., 8., 60, 0., 8. ) ;
   TH2F* h_jet0_ptgen_vs_ptrec_corrected = new TH2F( "h_jet0_ptgen_vs_ptrec_corrected", "jet0 ptgen vs ptrec, corrected", 60, 0., 8., 60, 0., 8. ) ;


   TH2F* h_jet0_pt_rec_minus_true_vs_rec = new TH2F( "h_jet0_pt_rec_minus_true_vs_rec", "jet0 pt, rec-true vs rec", 60, 0., 8., 60, -3., 3. ) ;
   TH2F* h_jet0_ptrec_vs_ptgen_shifted = new TH2F( "h_jet0_ptrec_vs_ptgen_shifted", "jet0 ptrec vs ptgen, shifted", 60, 0., 8., 60, 0., 8. ) ;
   TH2F* h_jet0_ptgen_vs_ptrec_shifted = new TH2F( "h_jet0_ptgen_vs_ptrec_shifted", "jet0 ptgen vs ptrec, shifted", 60, 0., 8., 60, 0., 8. ) ;

   TH2F* h_dphiqp_rec_vs_gen_qoplt03_cor = new TH2F( "h_dphiqp_rec_vs_gen_qoplt03_cor", "delta phi(qperp, Pperp), rec vs gen, q/P<0.3, with energy correction", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;


   TH2F* h_dphiqp_rec_vs_gen_jpt040 = new TH2F( "h_dphiqp_rec_vs_gen_jpt040", "delta phi(qperp, Pperp), rec vs gen, jet0pt>4", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;
   TH2F* h_dphiqp_rec_vs_gen_qoplt03_jpt040 = new TH2F( "h_dphiqp_rec_vs_gen_qoplt03_jpt040", "delta phi(qperp, Pperp), rec vs gen, q/P<0.3, jet0pt>4", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;
   TH2F* h_dphiqp_rec_vs_gen_qoplt06_jpt040 = new TH2F( "h_dphiqp_rec_vs_gen_qoplt06_jpt040", "delta phi(qperp, Pperp), rec vs gen, q/P<0.6, jet0pt>4", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;

   TH2F* h_dphiqp_rec_vs_gen_qoplt03_jpt045 = new TH2F( "h_dphiqp_rec_vs_gen_qoplt03_jpt045", "delta phi(qperp, Pperp), rec vs gen, q/P<0.3, jet0pt>4.5", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;

   TH2F* h_dphiqp_rec_vs_gen_qoplt03_jpt040_rec_rewrap = new TH2F( "h_dphiqp_rec_vs_gen_qoplt03_jpt040_rec_rewrap", "delta phi(qperp, Pperp), rec vs gen, q/P<0.3, jet0pt>4", 60, -3.2, 3.2, 120, -2*3.2, 2*3.2 ) ;
   TH2F* h_dphiqp_rec_vs_gen_qoplt03_jpt045_rec_rewrap = new TH2F( "h_dphiqp_rec_vs_gen_qoplt03_jpt045_rec_rewrap", "delta phi(qperp, Pperp), rec vs gen, q/P<0.3, jet0pt>4.5", 60, -3.2, 3.2, 120, -2*3.2, 2*3.2 ) ;


   TH1F* h_dphiqp_rec_minus_true_qoplt03_jpt040_rewrap = new TH1F( "h_dphiqp_rec_minus_true_qoplt03_jpt040_rewrap", "delta phi(qperp, Pperp), q/P<0.3, jet0pt>4",
               60, -3.2, 3.2 ) ;


   TH2F* h_dphiqp_vs_qperp = new TH2F( "h_dphiqp_vs_qperp", "delta phi(qperp, Pperp) vs qperp", 60, 0., 8., 60, -3.2, 3.2 ) ;
   TH2F* h_dphiqp_vs_qoverp = new TH2F( "h_dphiqp_vs_qoverp", "delta phi(qperp, Pperp) vs qoverp", 60, 0., 2., 60, -3.2, 3.2 ) ;
   TH2F* h_dphiqp_vs_qoverp_pm = new TH2F( "h_dphiqp_vs_qoverp_pm", "delta phi(qperp, Pperp) vs qoverp, parton matched", 60, 0., 2., 60, -3.2, 3.2 ) ;

   TH2F* h_dphiqp_vs_qperp_gen = new TH2F( "h_dphiqp_vs_qperp_gen", "delta phi(qperp, Pperp) vs qperp, gen vars", 60, 0., 8., 60, -3.2, 3.2 ) ;
   TH2F* h_dphiqp_vs_qoverp_gen = new TH2F( "h_dphiqp_vs_qoverp_gen", "delta phi(qperp, Pperp) vs qoverp, gen vars", 60, 0., 2., 60, -3.2, 3.2 ) ;
   TH2F* h_dphiqp_vs_qoverp_gen_pm = new TH2F( "h_dphiqp_vs_qoverp_gen_pm", "delta phi(qperp, Pperp) vs qoverp, gen vars, parton matched", 60, 0., 2., 60, -3.2, 3.2 ) ;

   TH2F* h_dphiqp_rec_vs_gen = new TH2F( "h_dphiqp_rec_vs_gen", "delta phi(qperp, Pperp), rec vs gen, all", 60, -3.2, 3.2, 60, -3.2, 3.2 ) ;


   TH1F* h_dphijj_rec = new TH1F( "h_dphijj_rec", "delta phi(jj), rec", 16, 3.14159265/2., 3*3.14159265/2. ) ;




   //--- set up output mini tree

   char output_minitree_file[1000] ;
   sprintf( output_minitree_file, "ca4-output/mini-tree-%s.root", dset_name ) ;
   printf("\n\n Creating output minitree file:  %s\n\n", output_minitree_file ) ;
   TFile* tf_mt_out = new TFile( output_minitree_file, "recreate" ) ;

   TTree* tt_out = new TTree( "minitree", "Mini tree" ) ;

   float evt_weight ;
   float pthat_min ;
   float pthat_max ;
   float evt_x1 ;
   float evt_x2 ;
   float evt_xsec ;
   float evt_pthat ;

   float recj1_pt ;
   float recj1_eta ;
   float recj2_pt ;
   float recj2_eta ;
   float recjj_dphi ;

   float genj1_pt ;
   float genj1_eta ;
   float genj2_pt ;
   float genj2_eta ;
   float genjj_dphi ;

   float recPt ;
   float recqt ;
   float recphiPq ;

   float genPt ;
   float genqt ;
   float genphiPq ;

   tt_out -> Branch( "evt_weight", &evt_weight, "evt_weight/F" ) ;
   tt_out -> Branch( "pthat_min", &pthat_min, "pthat_min/F" ) ;
   tt_out -> Branch( "pthat_max", &pthat_max, "pthat_max/F" ) ;
   tt_out -> Branch( "evt_x1", &evt_x1, "evt_x1/F" ) ;
   tt_out -> Branch( "evt_x2", &evt_x2, "evt_x2/F" ) ;
   tt_out -> Branch( "evt_xsec", &evt_xsec, "evt_xsec/F" ) ;
   tt_out -> Branch( "evt_pthat", &evt_pthat, "evt_pthat/F" ) ;

   tt_out -> Branch( "recj1_pt", &recj1_pt, "recj1_pt/F" ) ;
   tt_out -> Branch( "recj1_eta", &recj1_eta, "recj1_eta/F" ) ;
   tt_out -> Branch( "recj2_pt", &recj2_pt, "recj2_pt/F" ) ;
   tt_out -> Branch( "recj2_eta", &recj2_eta, "recj2_eta/F" ) ;
   tt_out -> Branch( "recjj_dphi", &recjj_dphi, "recjj_dphi/F" ) ;

   tt_out -> Branch( "genj1_pt", &genj1_pt, "genj1_pt/F" ) ;
   tt_out -> Branch( "genj1_eta", &genj1_eta, "genj1_eta/F" ) ;
   tt_out -> Branch( "genj2_pt", &genj2_pt, "genj2_pt/F" ) ;
   tt_out -> Branch( "genj2_eta", &genj2_eta, "genj2_eta/F" ) ;
   tt_out -> Branch( "genjj_dphi", &genjj_dphi, "genjj_dphi/F" ) ;

   tt_out -> Branch( "recPt", &recPt, "recPt/F" ) ;
   tt_out -> Branch( "recqt", &recqt, "recqt/F" ) ;
   tt_out -> Branch( "recphiPq", &recphiPq, "recphiPq/F" ) ;

   tt_out -> Branch( "genPt", &genPt, "genPt/F" ) ;
   tt_out -> Branch( "genqt", &genqt, "genqt/F" ) ;
   tt_out -> Branch( "genphiPq", &genphiPq, "genphiPq/F" ) ;



   Long64_t nentries = fChain->GetEntries();

   TStopwatch tsw_loop ;
   double total_time_loop(0.) ;
   tsw_loop.Stop() ;


   //nentries = 10000 ;

   //nentries = 1000000 ;







   float weight = dset_pp_weight_per_ipb * 1.3 * 197 * 0.40 ; // 1.3 1/pb of pA, mass number of gold is 197
                                                              //  The factor of 0.4 is for the fraction that's fiducial in the FCS.

   evt_weight = weight ;

   pthat_min = dset_pthatmin ;
   pthat_max = dset_pthatmax ;

   evt_xsec = dset_total_pp_xsec_mb ;


   printf("\n\n  Pthat range:  %.1f to %.1f\n\n\n", dset_pthatmin, dset_pthatmax ) ;
   printf("  Dataset pp weight per ipb:  %.3f\n\n", dset_pp_weight_per_ipb ) ;

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


    //********** cut on pthat for this dataset
      if ( Particle_PT[4] < dset_pthatmin ) continue ;
      if ( Particle_PT[4] > dset_pthatmax ) continue ;
    //********** cut on pthat for this dataset


     evt_x1 = Event_X1[0] ;
     evt_x2 = Event_X2[0] ;
     evt_pthat = Particle_PT[4] ;


     if ( verbose ) {

         if ( Jet05_ != 2 ) continue ;

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

         printf("\n\n Gen Jets:  %d\n", GenJet05_ ) ;
         for ( int ji=0; ji<GenJet05_; ji++ ) {
            printf(" %3d:  Pt = %9.2f  Eta = %7.3f  Phi = %7.3f\n",
               ji,
               GenJet05_PT[ji],
               GenJet05_Eta[ji],
               GenJet05_Phi[ji]
               ) ;
         } // ji

         printf("\n\n Jets:  %d\n", Jet05_ ) ;
         for ( int ji=0; ji<Jet05_; ji++ ) {
            printf(" %3d:  Pt = %9.2f  Eta = %7.3f  Phi = %7.3f\n",
               ji,
               Jet05_PT[ji],
               Jet05_Eta[ji],
               Jet05_Phi[ji]
               ) ;
         } // ji



         printf("  continue?  type q if no.   ") ;
         char answ = getchar() ;
         if ( answ == 'q' ) break ;

      } // verbose?



      int n_genjet_central(0) ;
      int n_genjet_forward(0) ;

      for ( int ji=0; ji<GenJet05_; ji++ ) {
         if ( fabs( GenJet05_Eta[ji] ) < 1.0 ) n_genjet_central ++ ;
         if ( GenJet05_Eta[ji] > 2.5 && GenJet05_Eta[ji] < 4.0 ) n_genjet_forward ++ ;
      }









   //----------------------------------------------------------------------------------------------------------
   //
   //

      if ( Jet05_ >= 2 ) {

         int ind_gj0(-1) ;
         int ind_gj1(-1) ;
         float gj0dr = 9999999. ;
         float gj1dr = 9999999. ;
         for ( int ji=0; ji<GenJet05_; ji++ ) {
            float dr0 = calc_dR( Jet05_Phi[0], GenJet05_Phi[ji], Jet05_Eta[0], GenJet05_Eta[ji] ) ;
            if ( dr0 < gj0dr ) {
               ind_gj0 = ji ;
               gj0dr = dr0 ;
            }
            float dr1 = calc_dR( Jet05_Phi[1], GenJet05_Phi[ji], Jet05_Eta[1], GenJet05_Eta[ji] ) ;
            if ( dr1 < gj1dr ) {
               ind_gj1 = ji ;
               gj1dr = dr1 ;
            }
         } // ji


         int ind_gpa(-1) ;
         int ind_gpb(-1) ;
         float gpa_eta(-9.) ;
         float gpb_eta(-9.) ;
         float gpa_dr(-1.) ;
         float gpb_dr(-1.) ;

         if ( Particle_Eta[4] > Particle_Eta[5] ) {
            float dr0, dr1 ;
            ind_gpa = 4 ;
            gpa_eta = Particle_Eta[4] ;
            dr0 = calc_dR( Jet05_Phi[0], Particle_Phi[4], Jet05_Eta[0], Particle_Eta[4] ) ;
            dr1 = calc_dR( Jet05_Phi[1], Particle_Phi[4], Jet05_Eta[1], Particle_Eta[4] ) ;
            if ( dr0 < dr1 ) { gpa_dr = dr0 ; } else { gpa_dr = dr1 ; }
            ind_gpb = 5 ;
            gpb_eta = Particle_Eta[5] ;
            dr0 = calc_dR( Jet05_Phi[0], Particle_Phi[5], Jet05_Eta[0], Particle_Eta[5] ) ;
            dr1 = calc_dR( Jet05_Phi[1], Particle_Phi[5], Jet05_Eta[1], Particle_Eta[5] ) ;
            if ( dr0 < dr1 ) { gpb_dr = dr0 ; } else { gpb_dr = dr1 ; }
         } else {
            float dr0, dr1 ;
            ind_gpa = 5 ;
            gpa_eta = Particle_Eta[5] ;
            dr0 = calc_dR( Jet05_Phi[0], Particle_Phi[5], Jet05_Eta[0], Particle_Eta[5] ) ;
            dr1 = calc_dR( Jet05_Phi[1], Particle_Phi[5], Jet05_Eta[1], Particle_Eta[5] ) ;
            if ( dr0 < dr1 ) { gpa_dr = dr0 ; } else { gpa_dr = dr1 ; }
            ind_gpb = 4 ;
            gpb_eta = Particle_Eta[4] ;
            dr0 = calc_dR( Jet05_Phi[0], Particle_Phi[4], Jet05_Eta[0], Particle_Eta[4] ) ;
            dr1 = calc_dR( Jet05_Phi[1], Particle_Phi[4], Jet05_Eta[1], Particle_Eta[4] ) ;
            if ( dr0 < dr1 ) { gpb_dr = dr0 ; } else { gpb_dr = dr1 ; }
         }
         bool has_2gpm(false) ;
         if ( gpa_dr < 1.0 && gpb_dr < 1.0 ) has_2gpm = true ;


         int ind_gp0(0) ;
         int ind_gp1(0) ;
         float gp0dr = 999999999. ;
         float gp1dr = 999999999. ;
         float gp4j0dr = calc_dR( Jet05_Phi[0], Particle_Phi[4], Jet05_Eta[0], Particle_Eta[4] ) ;
         float gp5j0dr = calc_dR( Jet05_Phi[0], Particle_Phi[5], Jet05_Eta[0], Particle_Eta[5] ) ;
         float gp4j1dr = calc_dR( Jet05_Phi[1], Particle_Phi[4], Jet05_Eta[1], Particle_Eta[4] ) ;
         float gp5j1dr = calc_dR( Jet05_Phi[1], Particle_Phi[5], Jet05_Eta[1], Particle_Eta[5] ) ;
         if ( ( gp4j0dr + gp5j1dr) < (gp5j0dr + gp4j1dr) ) {
            gp0dr = gp4j0dr ;
            ind_gp0 = 4 ;
            gp1dr = gp5j1dr ;
            ind_gp1 = 5 ;
         } else {
            gp0dr = gp5j0dr ;
            ind_gp0 = 5 ;
            gp1dr = gp4j1dr ;
            ind_gp1 = 4 ;
         }

         bool gen_partons_match(false) ;
         if ( gp0dr<1.0 && gp1dr<1.0 ) gen_partons_match = true ;



         float j0ptcf = pt_correction( Jet05_PT[0] ) ;
         float j1ptcf = pt_correction( Jet05_PT[1] ) ;

         float j0pt_shift = pt_shift( Jet05_PT[0] ) ;
         float j1pt_shift = pt_shift( Jet05_PT[1] ) ;



         int njets_rec_pt3(0) ;
         int njets_rec_pt4(0) ;
         int njets_rec_pt5(0) ;
         int njets_rec_pt6(0) ;
         int njets_gen_pt3(0) ;
         int njets_gen_pt4(0) ;
         int njets_gen_pt5(0) ;
         int njets_gen_pt6(0) ;
         for ( int ji=0; ji<GenJet05_; ji++ ) {
            if ( GenJet05_PT[ji] > 3.0 ) njets_gen_pt3++ ;
            if ( GenJet05_PT[ji] > 4.0 ) njets_gen_pt4++ ;
            if ( GenJet05_PT[ji] > 5.0 ) njets_gen_pt5++ ;
            if ( GenJet05_PT[ji] > 6.0 ) njets_gen_pt6++ ;
         } // ji
         for ( int ji=0; ji<Jet05_; ji++ ) {
            if ( Jet05_PT[ji] > 3.0 ) njets_rec_pt3++ ;
            if ( Jet05_PT[ji] > 4.0 ) njets_rec_pt4++ ;
            if ( Jet05_PT[ji] > 5.0 ) njets_rec_pt5++ ;
            if ( Jet05_PT[ji] > 6.0 ) njets_rec_pt6++ ;
         } // ji

         h_njets_rec_vs_gen -> Fill( GenJet05_, Jet05_, weight ) ;
         h_njets_pt3_rec_vs_gen -> Fill( njets_gen_pt3, njets_rec_pt3, weight ) ;
         h_njets_pt4_rec_vs_gen -> Fill( njets_gen_pt4, njets_rec_pt4, weight ) ;
         h_njets_pt5_rec_vs_gen -> Fill( njets_gen_pt5, njets_rec_pt5, weight ) ;
         h_njets_pt6_rec_vs_gen -> Fill( njets_gen_pt6, njets_rec_pt6, weight ) ;

         bool has_2gjm(false) ;
         if ( ind_gj0>=0 && ind_gj1>=0 && ind_gj0!=ind_gj1 && gj0dr<0.3 && gj1dr<0.3 ) has_2gjm = true ;

         float rec_dphi = calc_dphi( Jet05_Phi[0], Jet05_Phi[1] ) ;

         float rec_dphi_0to2pi = rec_dphi ;
         if ( rec_dphi < 0 ) rec_dphi_0to2pi = rec_dphi_0to2pi + 2*3.14159265 ;

         float genjetht = 0. ;
         //--- include forward endcap from 1 to 2.
         for ( int ji=0; ji<GenJet05_; ji++ ) {
            if ( GenJet05_Eta[ji] < 2.0 && GenJet05_Eta[ji] > -1.0 ) genjetht += GenJet05_PT[ji] ;
         } // ji

         float genparticleht = 0. ;
         for ( int gpi=0; gpi<Particle_; gpi++ ) {
            if ( Particle_Status[gpi] != 1 ) continue ;
            if ( Particle_Eta[gpi] < 2.0 && Particle_Eta[gpi] > -1.0 ) genparticleht += Particle_PT[gpi] ;
         } // gpi


         TLorentzVector tlv_parton1_in ;
         TLorentzVector tlv_parton1_out ;
         TLorentzVector tlv_parton2_in ;
         TLorentzVector tlv_parton2_out ;
         tlv_parton1_in.SetPxPyPzE( Particle_Px[2], Particle_Py[2], Particle_Pz[2], Particle_E[2] ) ;
         tlv_parton1_out.SetPxPyPzE( Particle_Px[4], Particle_Py[4], Particle_Pz[4], Particle_E[4] ) ;
         tlv_parton2_in.SetPxPyPzE( Particle_Px[3], Particle_Py[3], Particle_Pz[3], Particle_E[3] ) ;
         tlv_parton2_out.SetPxPyPzE( Particle_Px[5], Particle_Py[5], Particle_Pz[5], Particle_E[5] ) ;
         TLorentzVector tlv1_Q = tlv_parton1_in - tlv_parton1_out ;
         TLorentzVector tlv2_Q = tlv_parton2_in - tlv_parton2_out ;
         double Q2_1 = tlv1_Q.Dot( tlv1_Q ) ;
         double Q2_2 = tlv2_Q.Dot( tlv2_Q ) ;
      // if ( jentry < 1000 ) {
      //    printf("\n\n Event %lld\n", jentry ) ;
      //    printf("  parton1 in  : " ) ;
      //    tlv_parton1_in.Print() ;
      //    printf("  parton1 out : " ) ;
      //    tlv_parton1_out.Print() ;
      //    printf("  parton2 in  : " ) ;
      //    tlv_parton2_in.Print() ;
      //    printf("  parton2 out : " ) ;
      //    tlv_parton2_out.Print() ;
      //    printf("  Q from 1    : " ) ;
      //    tlv1_Q.Print() ;
      //    printf("  Q from 2    : " ) ;
      //    tlv1_Q.Print() ;
      //    printf("   ID1 = %d   ID2 = %d   x1 = %7.4f  x2 = %7.4f\n", Particle_PID[4], Particle_PID[5], Event_X1[0], Event_X2[0] ) ;
      //    printf("   Q2 = %8.3f,  Q = %8.3f   Event.Scale = %8.3f   Event.ScalePDF = %8.3f  alphaQCD = %9.5f\n", Q2_1, sqrt(fabs(Q2_1)), Event_Scale[0], Event_ScalePDF[0], Event_AlphaQCD[0] ) ;
      // }

         h_myq2_vs_scale2 -> Fill( Event_Scale[0]*Event_Scale[0], fabs(Q2_1), weight ) ;
         h_myq2_vs_scale2_zoom -> Fill( Event_Scale[0]*Event_Scale[0], fabs(Q2_1), weight ) ;

         if ( (abs(Event_ID1[0]) < 7 && abs(Event_ID2[0]) > 20) || (abs(Event_ID2[0]) < 7 && abs(Event_ID1[0]) > 20) ) h_myq2_vs_scale2_q_g -> Fill( Event_Scale[0]*Event_Scale[0], (fabs(Q2_1)), weight ) ;
         if ( (abs(Event_ID1[0]) > 20 && abs(Event_ID2[0]) > 20) ) h_myq2_vs_scale2_g_g -> Fill( Event_Scale[0]*Event_Scale[0], (fabs(Q2_1)), weight ) ;
         if ( Event_ID1[0] < 7 && Event_ID2[0] < 7 && Event_ID1[0] > 0 && Event_ID2[0] > 0  ) h_myq2_vs_scale2_q_q -> Fill( Event_Scale[0]*Event_Scale[0], (fabs(Q2_1)), weight ) ;
         if ( abs(Event_ID1[0]) == abs(Event_ID2[0]) && abs(Event_ID1[0]) < 7 && Event_ID1[0] * Event_ID2[0] < 0 ) h_myq2_vs_scale2_q_qbar -> Fill( Event_Scale[0]*Event_Scale[0], (fabs(Q2_1)), weight ) ;


            float Pperp_random_sign = 1. ;
            if ( gRandom -> Integer(2) == 1 ) Pperp_random_sign = -1. ;




            float jet0px = Jet05_PT[0]*cos(Jet05_Phi[0]) ;
            float jet0py = Jet05_PT[0]*sin(Jet05_Phi[0]) ;
            float jet0theta = theta_from_eta( Jet05_Eta[0] ) ;
            float jet0pz = Jet05_PT[0] / tan(jet0theta) ;

            bool j0_fid = inside_fiducial( Jet05_Eta[0], Jet05_Phi[0] ) ;

            float jet1px = Jet05_PT[1]*cos(Jet05_Phi[1]) ;
            float jet1py = Jet05_PT[1]*sin(Jet05_Phi[1]) ;
            float jet1theta = theta_from_eta( Jet05_Eta[1] ) ;
            float jet1pz = Jet05_PT[1] / tan(jet1theta) ;

            bool j1_fid = inside_fiducial( Jet05_Eta[1], Jet05_Phi[1] ) ;

            float Pperpx = 0.5 * ( jet0px - jet1px ) * Pperp_random_sign ;
            float Pperpy = 0.5 * ( jet0py - jet1py ) * Pperp_random_sign ;
            float Pperp = sqrt( Pperpx*Pperpx + Pperpy*Pperpy ) ;

            float qperpx =       ( jet0px + jet1px ) ;
            float qperpy =       ( jet0py + jet1py ) ;
            float qperp = sqrt( qperpx*qperpx + qperpy*qperpy ) ;

            float phi_Pperp = atan2( Pperpy, Pperpx ) ;
            float phi_qperp = atan2( qperpy, qperpx ) ;

            float dphi_Pperp_qperp = calc_dphi( phi_Pperp, phi_qperp ) ;



         //--- with energy correction

            float jet0px_c = j0ptcf*Jet05_PT[0]*cos(Jet05_Phi[0]) ;
            float jet0py_c = j0ptcf*Jet05_PT[0]*sin(Jet05_Phi[0]) ;

            float jet1px_c = j1ptcf*Jet05_PT[1]*cos(Jet05_Phi[1]) ;
            float jet1py_c = j1ptcf*Jet05_PT[1]*sin(Jet05_Phi[1]) ;

            float Pperpx_c = 0.5 * ( jet0px_c - jet1px_c ) * Pperp_random_sign ;
            float Pperpy_c = 0.5 * ( jet0py_c - jet1py_c ) * Pperp_random_sign ;
            float Pperp_c = sqrt( Pperpx_c*Pperpx_c + Pperpy_c*Pperpy_c ) ;

            float qperpx_c =       ( jet0px_c + jet1px_c ) ;
            float qperpy_c =       ( jet0py_c + jet1py_c ) ;
            float qperp_c = sqrt( qperpx_c*qperpx_c + qperpy_c*qperpy_c ) ;

            float phi_Pperp_c = atan2( Pperpy_c, Pperpx_c ) ;
            float phi_qperp_c = atan2( qperpy_c, qperpx_c ) ;

            float dphi_Pperp_qperp_c = calc_dphi( phi_Pperp_c, phi_qperp_c ) ;





       //-- 2022-11-07 : increase higher pt jet cut to 4.0 while keeping lower one at 3.0.
       //
         if ( Jet05_PT[0] > 4.0 && Jet05_PT[1] > 3.0 ) {

            h_log10x2_vs_log10x1_sel0 -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;
            h_genparton_etab_vs_etaa_sel0 -> Fill( gpa_eta, gpb_eta, weight ) ;
            h_genparton_drb_vs_dra_sel0 -> Fill( gpa_dr, gpb_dr, weight ) ;
            h_jet1pt_vs_jet0pt_sel0 -> Fill( Jet05_PT[0], Jet05_PT[1], weight ) ;
            h_jet1eta_vs_jet0eta_sel0 -> Fill( Jet05_Eta[0], Jet05_Eta[1], weight ) ;
            h_r2j_genjetht_sel0 -> Fill( genjetht, weight ) ;

            h_r2j_genjetht_vs_log10x2_sel0 -> Fill( log10(Event_X2[0]), genjetht, weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_r2j_genjetht_vs_log10x2_sel0_pm -> Fill( log10(Event_X2[0]), genjetht, weight ) ;

            if ( gp0dr < 1.0 && gp1dr < 1.0 ) { h_r2j_genjetht_sel0_pm -> Fill( genjetht, weight ) ; } else { h_r2j_genjetht_sel0_npm -> Fill( genjetht, weight ) ; }


            h_gp1dr_vs_gp0dr_sel0 -> Fill( gp0dr, gp1dr, weight ) ;

            if ( Jet05_Eta[0]>2.6 && Jet05_Eta[1]>2.6 ) {

               h_log10x2_vs_log10x1_sel1 -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;
               h_genparton_etab_vs_etaa_sel1 -> Fill( gpa_eta, gpb_eta, weight ) ;
               h_genparton_drb_vs_dra_sel1 -> Fill( gpa_dr, gpb_dr, weight ) ;
               h_jet1pt_vs_jet0pt_sel1 -> Fill( Jet05_PT[0], Jet05_PT[1], weight ) ;
               h_jet1eta_vs_jet0eta_sel1 -> Fill( Jet05_Eta[0], Jet05_Eta[1], weight ) ;
               h_r2j_genjetht_sel1 -> Fill( genjetht, weight ) ;

               h_gp1dr_vs_gp0dr_sel1 -> Fill( gp0dr, gp1dr, weight ) ;

               h_jj_dphi_precut -> Fill( rec_dphi_0to2pi, weight ) ;
               if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_jj_dphi_precut_pm -> Fill( rec_dphi_0to2pi, weight ) ;

               if ( gp0dr < 1.0 && gp1dr < 1.0 ) { h_r2j_genjetht_sel1_pm -> Fill( genjetht, weight ) ; } else { h_r2j_genjetht_sel1_npm -> Fill( genjetht, weight ) ; }

               if ( fabs(rec_dphi)>3.14159265/2. ) {

                  h_log10x2_vs_log10x1_sel2 -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;
                  h_genparton_etab_vs_etaa_sel2 -> Fill( gpa_eta, gpb_eta, weight ) ;
                  h_genparton_drb_vs_dra_sel2 -> Fill( gpa_dr, gpb_dr, weight ) ;
                  h_jet1pt_vs_jet0pt_sel2 -> Fill( Jet05_PT[0], Jet05_PT[1], weight ) ;
                  h_jet1eta_vs_jet0eta_sel2 -> Fill( Jet05_Eta[0], Jet05_Eta[1], weight ) ;
                  h_r2j_genjetht_sel2 -> Fill( genjetht, weight ) ;

                  h_gp1dr_vs_gp0dr_sel2 -> Fill( gp0dr, gp1dr, weight ) ;

                  if ( gp0dr < 1.0 && gp1dr < 1.0 ) { h_r2j_genjetht_sel2_pm -> Fill( genjetht, weight ) ; } else { h_r2j_genjetht_sel2_npm -> Fill( genjetht, weight ) ; }

                  h_genparticleht_sel2 -> Fill( genparticleht, weight ) ;
                  if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_genparticleht_sel2_pm -> Fill( genparticleht, weight ) ;

                  h_log10x2_vs_qperp_sel2 -> Fill( qperp, log10(Event_X2[0]), weight ) ;

                  h_log10x2_vs_qoverp_sel2 -> Fill( qperp/Pperp, log10(Event_X2[0]), weight ) ;
                  if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_log10x2_vs_qoverp_sel2_pm -> Fill( qperp/Pperp, log10(Event_X2[0]), weight ) ;

                  h_log10x2_vs_pt1_sel2 -> Fill( Jet05_PT[1], log10(Event_X2[0]), weight ) ;
                  if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_log10x2_vs_pt1_sel2_pm -> Fill( Jet05_PT[1], log10(Event_X2[0]), weight ) ;

                  h_log10x2_vs_pt0_sel2 -> Fill( Jet05_PT[0], log10(Event_X2[0]), weight ) ;
                  if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_log10x2_vs_pt0_sel2_pm -> Fill( Jet05_PT[0], log10(Event_X2[0]), weight ) ;

                  if ( Jet05_PT[1] > 4.0 ) h_log10x2_vs_qperp_pt1gt4_sel2 ->  Fill( qperp, log10(Event_X2[0]), weight ) ;

                  if ( Pperp>4.0 ) h_log10x2_vs_qperp_Pperp4_sel2 -> Fill( qperp, log10(Event_X2[0]), weight ) ;
                  if ( Pperp>3.0 && Pperp<3.5 ) h_log10x2_vs_qperp_Pperp30to35_sel2 -> Fill( qperp, log10(Event_X2[0]), weight ) ;
                  if ( Pperp>3.5 && Pperp<4.0 ) h_log10x2_vs_qperp_Pperp35to40_sel2 -> Fill( qperp, log10(Event_X2[0]), weight ) ;
                  if ( Pperp>4.0 && Pperp<4.5 ) h_log10x2_vs_qperp_Pperp40to45_sel2 -> Fill( qperp, log10(Event_X2[0]), weight ) ;
                  if ( Pperp>4.5              ) h_log10x2_vs_qperp_Pperp45_sel2 -> Fill( qperp, log10(Event_X2[0]), weight ) ;


                  if ( Pperp>3.0 && Pperp<3.5 ) h_log10x2_Pperp_30to35 -> Fill( log10(Event_X2[0]), weight ) ;
                  if ( Pperp>3.5 && Pperp<4.0 ) h_log10x2_Pperp_35to40 -> Fill( log10(Event_X2[0]), weight ) ;
                  if ( Pperp>4.0 ) h_log10x2_Pperp_40 -> Fill( log10(Event_X2[0]), weight ) ;
                  if ( Pperp>4.0 && Pperp<4.5 ) h_log10x2_Pperp_40to45 -> Fill( log10(Event_X2[0]), weight ) ;
                  if ( Pperp>4.5 ) h_log10x2_Pperp_45 -> Fill( log10(Event_X2[0]), weight ) ;

                  if ( gp0dr < 1.0 && gp1dr < 1.0 ) {
                     if ( Pperp>3.0 && Pperp<3.5 ) h_log10x2_Pperp_30to35_pm -> Fill( log10(Event_X2[0]), weight ) ;
                     if ( Pperp>3.5 && Pperp<4.0 ) h_log10x2_Pperp_35to40_pm -> Fill( log10(Event_X2[0]), weight ) ;
                     if ( Pperp>4.0 ) h_log10x2_Pperp_40_pm -> Fill( log10(Event_X2[0]), weight ) ;
                     if ( Pperp>4.0 && Pperp<4.5 ) h_log10x2_Pperp_40to45_pm -> Fill( log10(Event_X2[0]), weight ) ;
                     if ( Pperp>4.5 ) h_log10x2_Pperp_45_pm -> Fill( log10(Event_X2[0]), weight ) ;
                  }

                  if ( genjetht < 999999. ) { // 2022-11-04 : drop the activity veto.

                     h_log10x2_vs_log10x1_sel3 -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;
                     h_genparton_etab_vs_etaa_sel3 -> Fill( gpa_eta, gpb_eta, weight ) ;
                     h_genparton_drb_vs_dra_sel3 -> Fill( gpa_dr, gpb_dr, weight ) ;
                     h_jet1pt_vs_jet0pt_sel3 -> Fill( Jet05_PT[0], Jet05_PT[1], weight ) ;
                     h_jet1pt_vs_jet0pt_sel3_v2 -> Fill( Jet05_PT[0], Jet05_PT[1], weight ) ;
                     h_jet1eta_vs_jet0eta_sel3 -> Fill( Jet05_Eta[0], Jet05_Eta[1], weight ) ;
                     h_r2j_genjetht_sel3 -> Fill( genjetht, weight ) ;

                     h_genparticleht_sel3 -> Fill( genparticleht, weight ) ;
                     if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_genparticleht_sel3_pm -> Fill( genparticleht, weight ) ;

                     h_gp1dr_vs_gp0dr_sel3 -> Fill( gp0dr, gp1dr, weight ) ;

                     if ( gp0dr < 1.0 && gp1dr < 1.0 ) { h_r2j_genjetht_sel3_pm -> Fill( genjetht, weight ) ; } else { h_r2j_genjetht_sel3_npm -> Fill( genjetht, weight ) ; }

                     if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_log10x2_vs_log10x1_sel3_pm -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;

                     if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_jet1pt_vs_jet0pt_sel3_pm -> Fill( Jet05_PT[0], Jet05_PT[1], weight ) ;
                     if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_jet1eta_vs_jet0eta_sel3_pm -> Fill( Jet05_Eta[0], Jet05_Eta[1], weight ) ;



            h_qperp_sel3 -> Fill( qperp, weight ) ;
            h_qperp_over_pperp_sel3 -> Fill( qperp/Pperp, weight ) ;
            h_qperp_vs_Pperp_sel3 -> Fill( Pperp, qperp, weight ) ;

            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_qperp_sel3_pm -> Fill( qperp, weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_qperp_over_pperp_sel3_pm -> Fill( qperp/Pperp, weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_qperp_vs_Pperp_sel3_pm -> Fill( Pperp, qperp, weight ) ;


            int n_fid(0) ;
            if ( j0_fid ) n_fid ++ ;
            if ( j1_fid ) n_fid ++ ;

            h_n_fiducial -> Fill( n_fid, weight ) ;


                     ////////if ( qperp/Pperp < 0.3 ) 
                     if ( genparticleht<4.0 ) {
                                                          h_log10x2_vs_log10x1_sel4    -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;
                        if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_log10x2_vs_log10x1_sel4_pm -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;
                     }

            float rec_dphi_0to2pi = rec_dphi ;
            if ( rec_dphi < 0 ) rec_dphi_0to2pi = rec_dphi_0to2pi + 2*3.14159265 ;

            h_jj_dphi_rec_all -> Fill( rec_dphi_0to2pi, weight ) ;
            if ( n_fid == 2 ) h_jj_dphi_rec_fid -> Fill( rec_dphi_0to2pi, weight ) ;




            h_log10x2_vs_Pperp -> Fill( Pperp, log10(Event_X2[0]), weight ) ;


            h_dphijj_rec -> Fill( rec_dphi_0to2pi, weight ) ;


            h_jet0_eta_vs_pt_all -> Fill( Jet05_PT[0], Jet05_Eta[0], weight ) ;
            if ( gj0dr < 0.3 ) h_jet0_eta_vs_pt_gm -> Fill( Jet05_PT[0], Jet05_Eta[0], weight ) ;
            if ( gp0dr < 1.0 ) h_jet0_eta_vs_pt_pm -> Fill( Jet05_PT[0], Jet05_Eta[0], weight ) ;
            if ( gp0dr < 1.0 && gj0dr < 0.3 ) h_jet0_eta_vs_pt_gm_pm -> Fill( Jet05_PT[0], Jet05_Eta[0], weight ) ;

            h_jet1_eta_vs_pt_all -> Fill( Jet05_PT[1], Jet05_Eta[1], weight ) ;
            if ( gj1dr < 0.3 ) h_jet1_eta_vs_pt_gm -> Fill( Jet05_PT[1], Jet05_Eta[1], weight ) ;
            if ( gp1dr < 1.0 ) h_jet1_eta_vs_pt_pm -> Fill( Jet05_PT[1], Jet05_Eta[1], weight ) ;
            if ( gp1dr < 1.0 && gj1dr < 0.3 ) h_jet1_eta_vs_pt_gm_pm -> Fill( Jet05_PT[1], Jet05_Eta[1], weight ) ;

            h_log10q2_vs_log10x2 -> Fill( log10(Event_X2[0]), log10( Event_Scale[0]*Event_Scale[0] ), weight ) ;
            if ( has_2gjm ) h_log10q2_vs_log10x2_gm -> Fill( log10(Event_X2[0]), log10( Event_Scale[0]*Event_Scale[0] ), weight ) ;
            if ( has_2gjm && has_2gpm ) h_log10q2_vs_log10x2_gm_pm -> Fill( log10(Event_X2[0]), log10( Event_Scale[0]*Event_Scale[0] ), weight ) ;
            if ( has_2gpm ) h_log10q2_vs_log10x2_pm -> Fill( log10(Event_X2[0]), log10( Event_Scale[0]*Event_Scale[0] ), weight ) ;

            h_log10x2_vs_log10x1 -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;
            if ( has_2gjm ) h_log10x2_vs_log10x1_gm -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;
            if ( has_2gjm && has_2gpm ) h_log10x2_vs_log10x1_gm_pm -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;
            if ( has_2gpm ) h_log10x2_vs_log10x1_pm -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;

            h_j_phi_vs_eta_all -> Fill( Jet05_Eta[0], Jet05_Phi[0], weight ) ;
            if ( j0_fid ) h_j_phi_vs_eta_fid -> Fill( Jet05_Eta[0], Jet05_Phi[0], weight ) ;
            h_j_phi_vs_eta_all -> Fill( Jet05_Eta[1], Jet05_Phi[1], weight ) ;
            if ( j1_fid ) h_j_phi_vs_eta_fid -> Fill( Jet05_Eta[1], Jet05_Phi[1], weight ) ;





            h_q2_vs_jet0pt_all -> Fill( Jet05_PT[0], Event_Scale[0]*Event_Scale[0], weight ) ;
            if ( gj0dr < 0.3 && gj1dr < 0.3 ) h_q2_vs_jet0pt_gm -> Fill( Jet05_PT[0], Event_Scale[0]*Event_Scale[0], weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_q2_vs_jet0pt_pm -> Fill( Jet05_PT[0], Event_Scale[0]*Event_Scale[0], weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 && gj0dr < 0.3 && gj1dr < 0.3 ) h_q2_vs_jet0pt_gm_pm -> Fill( Jet05_PT[0], Event_Scale[0]*Event_Scale[0], weight ) ;

            h_q2_vs_jet1pt_all -> Fill( Jet05_PT[1], Event_Scale[0]*Event_Scale[0], weight ) ;
            if ( gj0dr < 0.3 && gj1dr < 0.3 ) h_q2_vs_jet1pt_gm -> Fill( Jet05_PT[1], Event_Scale[0]*Event_Scale[0], weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_q2_vs_jet1pt_pm -> Fill( Jet05_PT[1], Event_Scale[0]*Event_Scale[0], weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 && gj0dr < 0.3 && gj1dr < 0.3 ) h_q2_vs_jet1pt_gm_pm -> Fill( Jet05_PT[1], Event_Scale[0]*Event_Scale[0], weight ) ;


            h_log10x2_vs_jet0pt_all -> Fill( Jet05_PT[0], log10(Event_X2[0]), weight ) ;
            if ( gj0dr < 0.3 && gj1dr < 0.3 ) h_log10x2_vs_jet0pt_gm -> Fill( Jet05_PT[0], log10(Event_X2[0]), weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_log10x2_vs_jet0pt_pm -> Fill( Jet05_PT[0], log10(Event_X2[0]), weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 && gj0dr < 0.3 && gj1dr < 0.3 ) h_log10x2_vs_jet0pt_gm_pm -> Fill( Jet05_PT[0], log10(Event_X2[0]), weight ) ;

            h_log10x2_vs_jet1pt_all -> Fill( Jet05_PT[1], log10(Event_X2[0]), weight ) ;
            if ( gj0dr < 0.3 && gj1dr < 0.3 ) h_log10x2_vs_jet1pt_gm -> Fill( Jet05_PT[1], log10(Event_X2[0]), weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_log10x2_vs_jet1pt_pm -> Fill( Jet05_PT[1], log10(Event_X2[0]), weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 && gj0dr < 0.3 && gj1dr < 0.3 ) h_log10x2_vs_jet1pt_gm_pm -> Fill( Jet05_PT[1], log10(Event_X2[0]), weight ) ;


            h_q2_vs_jet0eta_all -> Fill( Jet05_Eta[0], Event_Scale[0]*Event_Scale[0], weight ) ;
            if ( gj0dr < 0.3 && gj1dr < 0.3 ) h_q2_vs_jet0eta_gm -> Fill( Jet05_Eta[0], Event_Scale[0]*Event_Scale[0], weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_q2_vs_jet0eta_pm -> Fill( Jet05_Eta[0], Event_Scale[0]*Event_Scale[0], weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 && gj0dr < 0.3 && gj1dr < 0.3 ) h_q2_vs_jet0eta_gm_pm -> Fill( Jet05_Eta[0], Event_Scale[0]*Event_Scale[0], weight ) ;

            h_q2_vs_jet1eta_all -> Fill( Jet05_Eta[1], Event_Scale[0]*Event_Scale[0], weight ) ;
            if ( gj0dr < 0.3 && gj1dr < 0.3 ) h_q2_vs_jet1eta_gm -> Fill( Jet05_Eta[1], Event_Scale[0]*Event_Scale[0], weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_q2_vs_jet1eta_pm -> Fill( Jet05_Eta[1], Event_Scale[0]*Event_Scale[0], weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 && gj0dr < 0.3 && gj1dr < 0.3 ) h_q2_vs_jet1eta_gm_pm -> Fill( Jet05_Eta[1], Event_Scale[0]*Event_Scale[0], weight ) ;





            h_j0pt_all -> Fill( Jet05_PT[0], weight ) ;
            if ( gj0dr < 0.3 ) h_j0pt_gm -> Fill( Jet05_PT[0], weight ) ;
            if ( gp0dr < 1.0 ) h_j0pt_pm -> Fill( Jet05_PT[0], weight ) ;
            if ( gj0dr < 0.3 && gp0dr < 1.0 ) h_j0pt_gm_pm -> Fill( Jet05_PT[0], weight ) ;

            h_j1pt_all -> Fill( Jet05_PT[1], weight ) ;
            if ( gj1dr < 0.3 ) h_j1pt_gm -> Fill( Jet05_PT[1], weight ) ;
            if ( gp1dr < 1.0 ) h_j1pt_pm -> Fill( Jet05_PT[1], weight ) ;
            if ( gj1dr < 0.3 && gp1dr < 1.0 ) h_j1pt_gm_pm -> Fill( Jet05_PT[1], weight ) ;
            if ( gp1dr < 1.0 && gp0dr < 1.0 ) h_j1pt_bothpm -> Fill( Jet05_PT[1], weight ) ;

            float jet_ave_pt = 0.5 * ( Jet05_PT[0] + Jet05_PT[1] ) ;
            h_javept_all -> Fill( jet_ave_pt, weight ) ;
            if ( gj0dr < 0.3 && gj1dr < 0.3 ) h_javept_gm -> Fill( jet_ave_pt, weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0) h_javept_pm -> Fill( jet_ave_pt, weight ) ;
            if ( gj0dr < 0.3 && gp0dr < 1.0 && gj1dr < 0.3 && gp1dr < 1.0 ) h_javept_gm_pm -> Fill( jet_ave_pt, weight ) ;


            h_j1pt_vs_j0pt_all -> Fill( Jet05_PT[0], Jet05_PT[1], weight ) ;
            if ( gj0dr < 0.3 && gj1dr < 0.3 ) h_j1pt_vs_j0pt_gm -> Fill( Jet05_PT[0], Jet05_PT[1], weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_j1pt_vs_j0pt_pm -> Fill( Jet05_PT[0], Jet05_PT[1], weight ) ;
            if ( gj0dr < 0.3 && gp0dr < 1.0 && gj1dr < 0.3 && gp1dr < 1.0 ) h_j1pt_vs_j0pt_gm_pm -> Fill( Jet05_PT[0], Jet05_PT[1], weight ) ;


            h_j1eta_vs_j0eta_all -> Fill( Jet05_Eta[0], Jet05_Eta[1], weight ) ;
            if ( gj0dr < 0.3 && gj1dr < 0.3 ) h_j1eta_vs_j0eta_gm -> Fill( Jet05_Eta[0], Jet05_Eta[1], weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_j1eta_vs_j0eta_pm -> Fill( Jet05_Eta[0], Jet05_Eta[1], weight ) ;
            if ( gj0dr < 0.3 && gp0dr < 1.0 && gj1dr < 0.3 && gp1dr < 1.0 ) h_j1eta_vs_j0eta_gm_pm -> Fill( Jet05_Eta[0], Jet05_Eta[1], weight ) ;





            int process_code = get_process( Particle_PID[2], Particle_PID[3], Particle_PID[4], Particle_PID[5] ) ;

            h_process_all -> Fill( process_code, weight ) ;
            if ( gj0dr < 0.3 && gj1dr < 0.3 ) h_process_gm -> Fill( process_code, weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_process_pm -> Fill( process_code, weight ) ;
            if ( gj0dr < 0.3 && gp0dr < 1.0 && gj1dr < 0.3 && gp1dr < 1.0 ) h_process_gm_pm -> Fill( process_code, weight ) ;


            h_pthat_all -> Fill( Particle_PT[4], weight ) ;
            if ( gj0dr < 0.3 && gj1dr < 0.3 ) h_pthat_gm -> Fill( Particle_PT[4], weight ) ;
            if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_pthat_pm -> Fill( Particle_PT[4], weight ) ;
            if ( gj0dr < 0.3 && gp0dr < 1.0 && gj1dr < 0.3 && gp1dr < 1.0 ) h_pthat_gm_pm -> Fill( Particle_PT[4], weight ) ;

            if ( Jet05_PT[0] > 3.0 && Jet05_PT[1] > 3.0 ) h_pthat_pt30_all -> Fill( Particle_PT[4], weight ) ;
            if ( Jet05_PT[0] > 3.5 && Jet05_PT[1] > 3.5 ) h_pthat_pt35_all -> Fill( Particle_PT[4], weight ) ;
            if ( Jet05_PT[0] > 4.0 && Jet05_PT[1] > 4.0 ) h_pthat_pt40_all -> Fill( Particle_PT[4], weight ) ;
            if ( Jet05_PT[0] > 4.5 && Jet05_PT[1] > 4.5 ) h_pthat_pt45_all -> Fill( Particle_PT[4], weight ) ;
            if ( Jet05_PT[0] > 5.0 && Jet05_PT[1] > 5.0 ) h_pthat_pt50_all -> Fill( Particle_PT[4], weight ) ;
            if ( Jet05_PT[0] > 5.5 && Jet05_PT[1] > 5.5 ) h_pthat_pt55_all -> Fill( Particle_PT[4], weight ) ;

            if ( gp0dr < 1.0 && gp1dr < 1.0 ) {
               if ( Jet05_PT[0] > 3.0 && Jet05_PT[1] > 3.0 ) h_pthat_pt30_pm -> Fill( Particle_PT[4], weight ) ;
               if ( Jet05_PT[0] > 3.5 && Jet05_PT[1] > 3.5 ) h_pthat_pt35_pm -> Fill( Particle_PT[4], weight ) ;
               if ( Jet05_PT[0] > 4.0 && Jet05_PT[1] > 4.0 ) h_pthat_pt40_pm -> Fill( Particle_PT[4], weight ) ;
               if ( Jet05_PT[0] > 4.5 && Jet05_PT[1] > 4.5 ) h_pthat_pt45_pm -> Fill( Particle_PT[4], weight ) ;
               if ( Jet05_PT[0] > 5.0 && Jet05_PT[1] > 5.0 ) h_pthat_pt50_pm -> Fill( Particle_PT[4], weight ) ;
               if ( Jet05_PT[0] > 5.5 && Jet05_PT[1] > 5.5 ) h_pthat_pt55_pm -> Fill( Particle_PT[4], weight ) ;
            }


            h_log10x2_vs_qperp_sel3 -> Fill( qperp, log10(Event_X2[0]), weight ) ;
            if ( Pperp>4.0 ) h_log10x2_vs_qperp_Pperp4_sel3 -> Fill( qperp, log10(Event_X2[0]), weight ) ;
            if ( Pperp>3.0 && Pperp<3.5 ) h_log10x2_vs_qperp_Pperp30to35_sel3 -> Fill( qperp, log10(Event_X2[0]), weight ) ;
            if ( Pperp>3.5 && Pperp<4.0 ) h_log10x2_vs_qperp_Pperp35to40_sel3 -> Fill( qperp, log10(Event_X2[0]), weight ) ;
            if ( Pperp>4.0 && Pperp<4.5 ) h_log10x2_vs_qperp_Pperp40to45_sel3 -> Fill( qperp, log10(Event_X2[0]), weight ) ;
            if ( Pperp>4.5              ) h_log10x2_vs_qperp_Pperp45_sel3 -> Fill( qperp, log10(Event_X2[0]), weight ) ;



            if ( qperp / Pperp < 1000000000000000 ) {

               h_r2j_rec_dphi_all -> Fill( rec_dphi, weight ) ;
               h_r2j_gm0dr -> Fill( gj0dr, weight ) ;
               h_r2j_gm1dr -> Fill( gj1dr, weight ) ;

               if ( has_2gjm ) {


                  h_r2j_rec_dphi_2gjm -> Fill( rec_dphi, weight ) ;
                  float phi0_recmgen = calc_dphi( Jet05_Phi[0], GenJet05_Phi[ind_gj0] ) ;
                  float phi1_recmgen = calc_dphi( Jet05_Phi[1], GenJet05_Phi[ind_gj1] ) ;
                  h_r2j_phi0_recmgen -> Fill( phi0_recmgen, weight ) ;
                  h_r2j_phi1_recmgen -> Fill( phi1_recmgen, weight ) ;
                  float eta0_recmgen = Jet05_Eta[0] - GenJet05_Eta[ind_gj0] ;
                  float eta1_recmgen = Jet05_Eta[1] - GenJet05_Eta[ind_gj1] ;
                  h_r2j_eta0_recmgen -> Fill( eta0_recmgen, weight ) ;
                  h_r2j_eta1_recmgen -> Fill( eta1_recmgen, weight ) ;

                  float gen_dphi = calc_dphi( GenJet05_Phi[ind_gj0], GenJet05_Phi[ind_gj1] ) ;

                  h_r2j_dphijj_recmgen_vs_Pperp -> Fill( Pperp, rec_dphi - gen_dphi, weight ) ;


                  h_r2j_dphijj_recmgen -> Fill( rec_dphi - gen_dphi, weight ) ;

                  float genjet0px = GenJet05_PT[ind_gj0]*cos(GenJet05_Phi[ind_gj0]) ;
                  float genjet0py = GenJet05_PT[ind_gj0]*sin(GenJet05_Phi[ind_gj0]) ;
                  float genjet0theta = theta_from_eta( GenJet05_Eta[ind_gj0] ) ;
                  float genjet0pz = GenJet05_PT[ind_gj0] / tan(genjet0theta) ;

                  float genjet1px = GenJet05_PT[ind_gj1]*cos(GenJet05_Phi[ind_gj1]) ;
                  float genjet1py = GenJet05_PT[ind_gj1]*sin(GenJet05_Phi[ind_gj1]) ;
                  float genjet1theta = theta_from_eta( GenJet05_Eta[ind_gj1] ) ;
                  float genjet1pz = GenJet05_PT[ind_gj1] / tan(genjet0theta) ;

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

                  if ( qperp/Pperp < 0.3 ) h_dphiqp_rec_vs_gen_qoplt03 -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;
                  if ( qperp/Pperp < 0.3 && gp0dr < 1.0 && gp1dr < 1.0 ) h_dphiqp_rec_vs_gen_qoplt03_pm -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;

                  if ( GenJet05_Eta[ind_gj0]>2.6 && GenJet05_Eta[ind_gj1]>2.6 ) {
                     if ( qperp/Pperp < 0.3 ) h_dphiqp_rec_vs_gen_qoplt03_gjeta26 -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;
                     if ( qperp/Pperp < 0.3 && gp0dr < 1.0 && gp1dr < 1.0 ) h_dphiqp_rec_vs_gen_qoplt03_gjeta26_pm -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;
                  }
                  if ( GenJet05_Eta[ind_gj0]>3.0 && GenJet05_Eta[ind_gj1]>3.0 ) {
                     if ( qperp/Pperp < 0.3 ) h_dphiqp_rec_vs_gen_qoplt03_gjeta30 -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;
                     if ( qperp/Pperp < 0.3 && gp0dr < 1.0 && gp1dr < 1.0 ) h_dphiqp_rec_vs_gen_qoplt03_gjeta30_pm -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;
                  }

                  if ( qperp/Pperp < 0.3 && gj0dr<0.05 && gj1dr<0.05 ) h_dphiqp_rec_vs_gen_qoplt03_tightgmdr -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;

                  if ( qperp/Pperp < 1.0 ) h_dphiqp_rec_vs_gen_qoplt10 -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;
                  if ( qperp/Pperp < 1.0 && gp0dr < 1.0 && gp1dr < 1.0 ) h_dphiqp_rec_vs_gen_qoplt10_pm -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;

                  if ( fabs( rec_dphi_0to2pi - 3.14159265 ) < 0.2 ) {
                     h_dphiqp_rec_vs_gen_tightdphi -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;
                     if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_dphiqp_rec_vs_gen_tightdphi_pm -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;
                     if ( qperp/Pperp < 0.5 ) h_dphiqp_rec_vs_gen_tightdphi_qoplt05 -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;
                     h_cos2phiqp_vs_qperp_tightdphi -> Fill( qperp, cos( 2 * dphi_Pperp_qperp ), weight ) ;
                     h_cos2phiqp_vs_qperp_tightdphi_gen -> Fill( genqperp, cos( 2 * dphi_genPperp_genqperp ), weight ) ;
                  }

                  float dphi_Pperp_qperp_rewrap = dphi_Pperp_qperp ;
                  if ( dphi_Pperp_qperp > dphi_genPperp_genqperp + 3.14159265 ) dphi_Pperp_qperp_rewrap = dphi_Pperp_qperp_rewrap - 2*3.14159265 ;
                  if ( dphi_Pperp_qperp < dphi_genPperp_genqperp - 3.14159265 ) dphi_Pperp_qperp_rewrap = dphi_Pperp_qperp_rewrap + 2*3.14159265 ;

                  if ( fabs( rec_dphi_0to2pi - 3.14159265 ) < 0.2 ) {
                     h_dphiqp_rec_vs_gen_tightdphi_rec_rewrap -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp_rewrap, weight ) ;
                     if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_dphiqp_rec_vs_gen_tightdphi_rec_rewrap_pm -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp_rewrap, weight ) ;
                  }



                  h_j0_pzrec_vs_pzgen -> Fill( jet0pz, genjet0pz, weight ) ;
                  if ( Jet05_Eta[0] > 3.0 ) h_j0_etagt3_pzrec_vs_pzgen -> Fill( jet0pz, genjet0pz, weight ) ;

                  h_r2j_Pperp -> Fill( Pperp, weight ) ;
                  h_r2j_qperp -> Fill( qperp, weight ) ;

                  h_r2j_qperp_vs_Pperp -> Fill( Pperp, qperp, weight ) ;

                  h_r2j_Pperp_recmgen -> Fill( Pperp - genPperp, weight ) ;
                  h_r2j_qperp_recmgen -> Fill( qperp - genqperp, weight ) ;

                  h_r2j_Pperp_gen_vs_rec -> Fill( Pperp, genPperp, weight ) ;
                  h_r2j_qperp_gen_vs_rec -> Fill( qperp, genqperp, weight ) ;

                  h_r2j_qperp_over_Pperp_rec_vs_gen -> Fill( genqperp/genPperp, qperp/Pperp, weight ) ;


                  h_r2j_qperp_over_Pperp -> Fill( qperp / Pperp, weight ) ;


                  float gen_dphi_0to2pi = gen_dphi ;
                  if ( gen_dphi < 0 ) gen_dphi_0to2pi = gen_dphi_0to2pi + 2*3.14159265 ;

                  h_jj_dphi_rec_bothjgm_all -> Fill( rec_dphi_0to2pi, weight ) ;
                  if ( n_fid == 2 ) h_jj_dphi_rec_bothjgm_fid -> Fill( rec_dphi_0to2pi, weight ) ;

                  h_jj_dphi_gen_all -> Fill( gen_dphi_0to2pi, weight ) ;
                  if ( n_fid == 2 ) h_jj_dphi_gen_fid -> Fill( gen_dphi_0to2pi, weight ) ;


                  h_dphijj_rec_vs_gen -> Fill( gen_dphi_0to2pi, rec_dphi_0to2pi, weight ) ;





                  h_r2j_j1_vs_j0_pt -> Fill( Jet05_PT[0], Jet05_PT[1], weight ) ;
                  h_r2j_j1_vs_j0_eta -> Fill( Jet05_Eta[0], Jet05_Eta[1], weight ) ;
                  h_r2j_j1_vs_j0_pz -> Fill( jet0pz, jet1pz, weight ) ;
                  h_r2j_j1_vs_j0_phi -> Fill( Jet05_Phi[0], Jet05_Phi[1], weight ) ;

                  h_r2j_dphi_Pperp_qperp -> Fill( dphi_Pperp_qperp, weight ) ;
                  h_r2j_dphi_Pperp_qperp_gen -> Fill( dphi_genPperp_genqperp, weight ) ;
                  h_r2j_dphi_Pperp_qperp_recmgen -> Fill( dphi_Pperp_qperp_recmgen, weight ) ;

                  h_r2j_dphi_Pq_vs_dphi_jj -> Fill( rec_dphi, dphi_Pperp_qperp, weight ) ;

                  if ( fabs(rec_dphi)>3.14159265/2. ) h_r2j_dphicut_dphi_Pq_vs_dphi_jj -> Fill( rec_dphi, dphi_Pperp_qperp, weight ) ;

                  if ( gen_partons_match ) h_r2j_gpm_dphi_Pq_vs_dphi_jj -> Fill( rec_dphi, dphi_Pperp_qperp, weight ) ;


                  float jet0_ptrec_over_ptgen = ( Jet05_PT[0] )/( GenJet05_PT[ind_gj0] ) ;
                  float jet1_ptrec_over_ptgen = ( Jet05_PT[1] )/( GenJet05_PT[ind_gj1] ) ;


                  h_jet0_ptrec_over_ptgen_vs_ptgen -> Fill( GenJet05_PT[ind_gj0], jet0_ptrec_over_ptgen, weight ) ;
                  h_jet1_ptrec_over_ptgen_vs_ptgen -> Fill( GenJet05_PT[ind_gj1], jet1_ptrec_over_ptgen, weight ) ;

                  h_jet0_ptrec_over_ptgen_vs_ptrec -> Fill( Jet05_PT[0], jet0_ptrec_over_ptgen, weight ) ;
                  h_jet1_ptrec_over_ptgen_vs_ptrec -> Fill( Jet05_PT[1], jet1_ptrec_over_ptgen, weight ) ;

                  h_jet0_ptgen_over_ptrec_vs_ptrec -> Fill( Jet05_PT[0], 1./jet0_ptrec_over_ptgen, weight ) ;
                  h_jet1_ptgen_over_ptrec_vs_ptrec -> Fill( Jet05_PT[1], 1./jet1_ptrec_over_ptgen, weight ) ;


                  if ( qperp/Pperp < 0.3 && fabs(jet0_ptrec_over_ptgen-1)<0.05 && fabs(jet1_ptrec_over_ptgen-1)<0.05  ) h_dphiqp_rec_vs_gen_qoplt03_tightde -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;

                  if ( qperp/Pperp < 0.3 ) h_dphiqp_rec_vs_gen_qoplt03_cor -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp_c, weight ) ;

                  if ( Jet05_PT[0]>4.0 ) h_dphiqp_rec_vs_gen_jpt040 -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;



               //---- new on 11/7

                  if ( qperp/Pperp < 0.6 && Jet05_PT[0]>4.0 ) h_dphiqp_rec_vs_gen_qoplt06_jpt040 -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;

                  if ( qperp/Pperp < 0.3 && Jet05_PT[0]>4.0 ) h_dphiqp_rec_vs_gen_qoplt03_jpt040 -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;
                  if ( qperp/Pperp < 0.3 && Jet05_PT[0]>4.5 ) h_dphiqp_rec_vs_gen_qoplt03_jpt045 -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;

                  if ( qperp/Pperp < 0.3 && Jet05_PT[0]>4.0 ) h_dphiqp_rec_vs_gen_qoplt03_jpt040_rec_rewrap -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp_rewrap, weight ) ;
                  if ( qperp/Pperp < 0.3 && Jet05_PT[0]>4.5 ) h_dphiqp_rec_vs_gen_qoplt03_jpt045_rec_rewrap -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp_rewrap, weight ) ;

                  if ( qperp/Pperp < 0.3 && Jet05_PT[0]>4.0 ) h_dphiqp_rec_minus_true_qoplt03_jpt040_rewrap -> Fill( dphi_Pperp_qperp_rewrap - dphi_genPperp_genqperp, weight ) ;

                  h_dphiqp_rec_vs_gen -> Fill( dphi_genPperp_genqperp, dphi_Pperp_qperp, weight ) ;

                  h_dphiqp_vs_qperp -> Fill( qperp, dphi_Pperp_qperp, weight ) ;
                  h_dphiqp_vs_qoverp -> Fill( qperp/Pperp, dphi_Pperp_qperp, weight ) ;
                  if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_dphiqp_vs_qoverp_pm -> Fill( qperp/Pperp, dphi_Pperp_qperp, weight ) ;


                  h_dphiqp_vs_qperp_gen -> Fill( genqperp, dphi_genPperp_genqperp, weight ) ;
                  h_dphiqp_vs_qoverp_gen -> Fill( genqperp/genPperp, dphi_genPperp_genqperp, weight ) ;
                  if ( gp0dr < 1.0 && gp1dr < 1.0 ) h_dphiqp_vs_qoverp_gen_pm -> Fill( genqperp/genPperp, dphi_genPperp_genqperp, weight ) ;



                  h_r2j_ptrec_over_ptgen_vs_eta -> Fill( Jet05_Eta[0], jet0_ptrec_over_ptgen, weight ) ;
                  h_r2j_ptrec_over_ptgen_vs_eta -> Fill( Jet05_Eta[1], jet1_ptrec_over_ptgen, weight ) ;




                  h_jet0_ptrec_vs_ptgen_raw -> Fill( GenJet05_PT[ind_gj0], Jet05_PT[0], weight ) ;
                  h_jet0_ptgen_vs_ptrec_raw -> Fill( Jet05_PT[0], GenJet05_PT[ind_gj0], weight ) ;
                  h_jet0_ptrec_vs_ptgen_corrected -> Fill( GenJet05_PT[ind_gj0], j0ptcf * Jet05_PT[0], weight ) ;
                  h_jet0_ptgen_vs_ptrec_corrected -> Fill( j0ptcf * Jet05_PT[0], GenJet05_PT[ind_gj0], weight ) ;
                  h_jet0_ptrec_vs_ptgen_shifted -> Fill( GenJet05_PT[ind_gj0], Jet05_PT[0] - j0pt_shift, weight ) ;
                  h_jet0_ptgen_vs_ptrec_shifted -> Fill( Jet05_PT[0] - j0pt_shift, GenJet05_PT[ind_gj0], weight ) ;

                  h_jet0_pt_rec_minus_true_vs_rec -> Fill( Jet05_PT[0], Jet05_PT[0]-GenJet05_PT[ind_gj0], weight ) ;


                  h_r2j_genjetht -> Fill ( genjetht, weight ) ;

                  h_r2j_qperpxory_recmgen -> Fill( qperpx - genqperpx, weight ) ;
                  h_r2j_qperpxory_recmgen -> Fill( qperpy - genqperpy, weight ) ;

                  h_log10x2_vs_log10x1_sel -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;

                  h_parton0_dr -> Fill( gp0dr, weight ) ;
                  h_parton1_dr -> Fill( gp1dr, weight ) ;

                  h_parton_pt_sel -> Fill( Particle_PT[4], weight ) ;

                  if ( Jet05_PT[0] > 3.0 && Jet05_PT[1] > 3.0 ) h_parton_pt_jpt30_sel -> Fill( Particle_PT[4], weight ) ;
                  if ( Jet05_PT[0] > 3.5 && Jet05_PT[1] > 3.5 ) h_parton_pt_jpt35_sel -> Fill( Particle_PT[4], weight ) ;
                  if ( Jet05_PT[0] > 4.0 && Jet05_PT[1] > 4.0 ) h_parton_pt_jpt40_sel -> Fill( Particle_PT[4], weight ) ;
                  if ( Jet05_PT[0] > 4.5 && Jet05_PT[1] > 4.5 ) h_parton_pt_jpt45_sel -> Fill( Particle_PT[4], weight ) ;
                  if ( Jet05_PT[0] > 5.0 && Jet05_PT[1] > 5.0 ) h_parton_pt_jpt50_sel -> Fill( Particle_PT[4], weight ) ;

                  if ( GenJet05_ == 2 ) {
                     h_r2j_2gj_dphi_Pperp_qperp -> Fill( dphi_Pperp_qperp, weight ) ;
                     h_r2j_2gj_dphi_Pperp_qperp_gen -> Fill( dphi_genPperp_genqperp, weight ) ;
                     h_r2j_2gj_dphi_Pperp_qperp_recmgen -> Fill( dphi_Pperp_qperp_recmgen, weight ) ;
                     h_r2j_2gj_dphi_Pq_vs_dphi_jj -> Fill( rec_dphi, dphi_Pperp_qperp, weight ) ;
                     h_r2j_2gj_qperp_over_Pperp -> Fill( qperp / Pperp, weight ) ;
                     h_r2j_2gj_qperp_vs_Pperp -> Fill( Pperp, qperp, weight ) ;
                     h_r2j_2gj_j1_vs_j0_pt -> Fill( Jet05_PT[0], Jet05_PT[1], weight ) ;
                     h_r2j_2gj_genjetht -> Fill ( genjetht, weight ) ;
                     h_r2j_2gj_j1_vs_j0_phi -> Fill( Jet05_Phi[0], Jet05_Phi[1], weight ) ;
                     if ( fabs(rec_dphi)>3.14159265/2. ) h_r2j_2gj_dphicut_dphi_Pq_vs_dphi_jj -> Fill( rec_dphi, dphi_Pperp_qperp, weight ) ;
                     h_r2j_2gj_qperpxory_recmgen -> Fill( qperpx - genqperpx, weight ) ;
                     h_r2j_2gj_qperpxory_recmgen -> Fill( qperpy - genqperpy, weight ) ;
                     h_r2j_2gj_dphijj_recmgen_vs_Pperp -> Fill( Pperp, rec_dphi - gen_dphi, weight ) ;
                     h_2gj_parton0_dr -> Fill( gp0dr, weight ) ;
                     h_2gj_parton1_dr -> Fill( gp1dr, weight ) ;

                  }
                  if ( GenJet05_ == 3 ) {
                     h_r2j_3gj_dphi_Pperp_qperp -> Fill( dphi_Pperp_qperp, weight ) ;
                     h_r2j_3gj_dphi_Pperp_qperp_gen -> Fill( dphi_genPperp_genqperp, weight ) ;
                     h_r2j_3gj_dphi_Pperp_qperp_recmgen -> Fill( dphi_Pperp_qperp_recmgen, weight ) ;
                     h_r2j_3gj_dphi_Pq_vs_dphi_jj -> Fill( rec_dphi, dphi_Pperp_qperp, weight ) ;
                     h_r2j_3gj_qperp_over_Pperp -> Fill( qperp / Pperp, weight ) ;
                     h_r2j_3gj_qperp_vs_Pperp -> Fill( Pperp, qperp, weight ) ;
                     h_r2j_3gj_j1_vs_j0_pt -> Fill( Jet05_PT[0], Jet05_PT[1], weight ) ;
                     h_r2j_3gj_genjetht -> Fill ( genjetht, weight ) ;
                     h_r2j_3gj_j1_vs_j0_phi -> Fill( Jet05_Phi[0], Jet05_Phi[1], weight ) ;
                     if ( fabs(rec_dphi)>3.14159265/2. ) h_r2j_3gj_dphicut_dphi_Pq_vs_dphi_jj -> Fill( rec_dphi, dphi_Pperp_qperp, weight ) ;
                     h_r2j_3gj_qperpxory_recmgen -> Fill( qperpx - genqperpx, weight ) ;
                     h_r2j_3gj_qperpxory_recmgen -> Fill( qperpy - genqperpy, weight ) ;
                     h_r2j_3gj_dphijj_recmgen_vs_Pperp -> Fill( Pperp, rec_dphi - gen_dphi, weight ) ;
                     h_3gj_parton0_dr -> Fill( gp0dr, weight ) ;
                     h_3gj_parton1_dr -> Fill( gp1dr, weight ) ;
                  }


                  recj1_pt = Jet05_PT[0] ;
                  recj1_eta = Jet05_Eta[0] ;
                  recj2_pt = Jet05_PT[1] ;
                  recj2_eta = Jet05_Eta[1] ;
                  recjj_dphi = rec_dphi ;

                  genj1_pt = GenJet05_PT[ind_gj0] ;
                  genj1_eta = GenJet05_Eta[ind_gj0] ;
                  genj2_pt = GenJet05_PT[ind_gj1] ;
                  genj2_eta = GenJet05_Eta[ind_gj1] ;
                  genjj_dphi = gen_dphi ;

                  recPt = Pperp ;
                  recqt = qperp ;
                  recphiPq = dphi_Pperp_qperp ;

                  genPt = genPperp ;
                  genqt = genqperp ;
                  genphiPq = dphi_genPperp_genqperp ;



                  tt_out -> Fill() ;



             ///  printf("\n\n Gen Jets:  %d\n", GenJet05_ ) ;
             ///  for ( int ji=0; ji<GenJet05_; ji++ ) {
             ///     printf(" %3d:  Pt = %9.2f  Eta = %7.3f  Phi = %7.3f\n",
             ///        ji,
             ///        GenJet05_PT[ji],
             ///        GenJet05_Eta[ji],
             ///        GenJet05_Phi[ji]
             ///        ) ;
             ///  } // ji

             ///  printf("\n\n Jets:  %d\n", Jet05_ ) ;
             ///  for ( int ji=0; ji<Jet05_; ji++ ) {
             ///     printf(" %3d:  Pt = %9.2f  Eta = %7.3f  Phi = %7.3f  ",
             ///        ji,
             ///        Jet05_PT[ji],
             ///        Jet05_Eta[ji],
             ///        Jet05_Phi[ji]
             ///        ) ;
             ///     if ( ji==0 && ind_gj0>=0 ) {
             ///        printf(" | gen jet match  %d  dR = %7.3f   Pt = (%9.2f) %9.2f  Eta = (%7.3f) %7.3f  Phi = (%7.3f) %7.3f",
             ///            ind_gj0, gj0dr,
             ///            Jet05_PT[0], GenJet05_PT[ind_gj0],
             ///            Jet05_Eta[0], GenJet05_Eta[ind_gj0],
             ///            Jet05_Phi[0], GenJet05_Phi[ind_gj0] ) ;
             ///     }
             ///     if ( ji==1 && ind_gj1>=0 ) {
             ///        printf(" | gen jet match  %d  dR = %7.3f   Pt = (%9.2f) %9.2f  Eta = (%7.3f) %7.3f  Phi = (%7.3f) %7.3f",
             ///            ind_gj1, gj1dr,
             ///            Jet05_PT[1], GenJet05_PT[ind_gj1],
             ///            Jet05_Eta[1], GenJet05_Eta[ind_gj1],
             ///            Jet05_Phi[1], GenJet05_Phi[ind_gj1] ) ;
             ///     }
             ///     printf("\n") ;
             ///  } // ji
             ///  printf("   Pperp = %6.2f (gen %6.2f)   phi %7.3f (gen %7.3f)\n", Pperp, genPperp, phi_Pperp, phi_genPperp ) ;
             ///  printf("   qperp = %6.2f (gen %6.2f)   phi %7.3f (gen %7.3f)\n", qperp, genqperp, phi_qperp, phi_genqperp ) ;
             ///  printf("\n\n") ;



               } // both jets gen matched?

            } // cut on p/P

                  } // central Ht cut
               } // jet dphi cut
            } // jet eta cut
         } // jet pt cut


      } // at least two jets


   //
   //
   //----------------------------------------------------------------------------------------------------------







      int gen_pid1 = Particle_PID[4] ;
      int gen_pid2 = Particle_PID[5] ;

      h_gen_parton_eta2_vs_eta1_all -> Fill( Particle_Eta[4], Particle_Eta[5], weight ) ;
      if ( n_genjet_central==2 ) h_gen_parton_eta2_vs_eta1_2gen_central -> Fill( Particle_Eta[4], Particle_Eta[5], weight ) ;
      if ( n_genjet_forward==2 ) h_gen_parton_eta2_vs_eta1_2gen_forward -> Fill( Particle_Eta[4], Particle_Eta[5], weight ) ;


      h_njets -> Fill( GenJet05_, weight ) ;

      h_log10x2_vs_log10x1_all -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;

      h_parton_pt_all -> Fill( Particle_PT[4], weight ) ;

      if ( Jet05_PT[0] > 3.0 && Jet05_PT[1] > 3.0 ) h_parton_pt_jpt30_all -> Fill( Particle_PT[4], weight ) ;
      if ( Jet05_PT[0] > 3.5 && Jet05_PT[1] > 3.5 ) h_parton_pt_jpt35_all -> Fill( Particle_PT[4], weight ) ;
      if ( Jet05_PT[0] > 4.0 && Jet05_PT[1] > 4.0 ) h_parton_pt_jpt40_all -> Fill( Particle_PT[4], weight ) ;
      if ( Jet05_PT[0] > 4.5 && Jet05_PT[1] > 4.5 ) h_parton_pt_jpt45_all -> Fill( Particle_PT[4], weight ) ;
      if ( Jet05_PT[0] > 5.0 && Jet05_PT[1] > 5.0 ) h_parton_pt_jpt50_all -> Fill( Particle_PT[4], weight ) ;

      if ( n_genjet_central==2 ) h_log10x2_vs_log10x1_2gen_central -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;
      if ( n_genjet_forward==2 ) h_log10x2_vs_log10x1_2gen_forward -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;
      if ( n_genjet_forward==1 && n_genjet_central==1 ) h_log10x2_vs_log10x1_1gen_central_1gen_forward -> Fill( log10(Event_X1[0]), log10(Event_X2[0]), weight ) ;
      h_ngenjet_forward_vs_central -> Fill( n_genjet_central, n_genjet_forward, weight ) ;


      h_id2_vs_id1_all -> Fill( gen_pid1, gen_pid2, weight ) ;
      if ( n_genjet_central==2 ) h_id2_vs_id1_2gen_central -> Fill( gen_pid1, gen_pid2, weight ) ;
      if ( n_genjet_forward==2 ) h_id2_vs_id1_2gen_forward -> Fill( gen_pid1, gen_pid2, weight ) ;
      if ( n_genjet_forward==1 && n_genjet_central==1 ) h_id2_vs_id1_1gen_central_1gen_forward -> Fill( gen_pid1, gen_pid2, weight ) ;

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


      //////if ( GenJet05_ < 2 ) continue ;
      if ( GenJet05_ != 2 ) continue ;

      float dphi = GenJet05_Phi[1] - GenJet05_Phi[0] ;
      if ( dphi > 3.14159265 ) dphi = dphi - 2*3.14159265 ;
      if ( dphi <-3.14159265 ) dphi = dphi + 2*3.14159265 ;

      h_dphi -> Fill( dphi, weight ) ;

      float deta = GenJet05_Eta[1] - GenJet05_Eta[0] ;
      h_deta -> Fill( deta, weight ) ;

      h_eta2vseta1 -> Fill( GenJet05_Eta[0], GenJet05_Eta[1], weight ) ;
      h_pt2vspt1 -> Fill( GenJet05_PT[0], GenJet05_PT[1], weight ) ;

      h_deta_vs_dphi -> Fill( dphi, deta, weight ) ;


      if ( GenJet05_Eta[0] > 2 && GenJet05_Eta[0] < 4 && GenJet05_Eta[1] > 2 && GenJet05_Eta[1] < 4 ) h_dphi_both_eta_2to4 -> Fill(dphi, weight) ;



      if ( GenJet05_PT[0]<8 ) continue ;

      h_dphi_pt1gt8 -> Fill( dphi, weight ) ;
      h_deta_pt1gt8 -> Fill( deta, weight ) ;








      if ( GenJet05_PT[1]<8 ) continue ;

      h_dphi_pt12gt8 -> Fill( dphi, weight ) ;
      h_deta_pt12gt8 -> Fill( deta, weight ) ;




   } // jentry
   printf("\n\n Done.\n\n") ;

   tt_out -> Write() ;
   printf("\n\n Closing output minitree file:  %s\n\n", output_minitree_file ) ;
   tf_mt_out -> Close() ;


   gSystem -> Exec("mkdir -p ca4-output") ;

   char outfilename[1000] ;
   sprintf( outfilename, "ca4-output/dset-%s.root", dset_name ) ;

   saveHist( outfilename, "h*" ) ;


}











