#define event_display1_cxx
#include "event_display1.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

char pname[100] ;

const char* mcname( int pdgid ) ;

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

void event_display1::Loop( bool big_canvas )
{
   if (fChain == 0) return;

   gStyle -> SetOptStat(0) ;

   TCanvas* can(0x0) ;
   if ( big_canvas ) {
      can = new TCanvas( "can", "phi vs eta", 50, 50, 2000, 2000 ) ;
   } else {
      can = new TCanvas( "can", "phi vs eta", 50, 50, 1200, 1200 ) ;
   }


   TPad* pad1 = new TPad("pad1","", 0.02, 0.52,  0.98, 0.98 ) ;
   pad1->Draw() ;
   pad1->cd() ;

   TH2F* hp = new TH2F( "hp", "",   500,    -6., 6.,  500, -3.14159265, 3.14159265   ) ;
   hp -> SetXTitle( "eta" ) ;
   hp -> SetYTitle( "phi" ) ;

   hp -> Draw() ;
   gPad -> SetGridx(1) ;
   gPad -> SetGridy(1) ;



   TH2F* hp2 = new TH2F( "hp2", "",   500,  -8., 8.,  500, -8., 8.  ) ;
   hp2 -> SetXTitle( "Px (GeV)" ) ;
   hp2 -> SetYTitle( "Py (GeV)" ) ;


   char label[100] ;
   TText* text = new TText() ;
   text -> SetTextSize(0.03) ;
   text -> SetTextFont( 82 ) ;

   TMarker* marker_gp = new TMarker() ;
   marker_gp -> SetMarkerStyle( 22 ) ;
   marker_gp -> SetMarkerSize( 2.5 ) ;
   marker_gp -> SetMarkerColor( 4 ) ;

   TMarker* marker_fsp = new TMarker() ;
   marker_fsp -> SetMarkerStyle( 20 ) ;
   marker_fsp -> SetMarkerSize( 1.0 ) ;
   marker_fsp -> SetMarkerColor( 1 ) ;

   TMarker* marker_rj = new TMarker() ;
   marker_rj -> SetMarkerStyle(24) ;
   marker_rj -> SetMarkerSize( 2.5 ) ;
   marker_rj -> SetMarkerColor(2) ;

   TMarker* marker_gj = new TMarker() ;
   marker_gj -> SetMarkerStyle(24) ;
   marker_gj -> SetMarkerSize( 4.5 ) ;
   marker_gj -> SetMarkerColor(3) ;

   TEllipse* circle_rj = new TEllipse() ;
   circle_rj -> SetLineColor(2) ;
   circle_rj -> SetLineWidth(2) ;
   circle_rj -> SetFillColor(0) ;
   circle_rj -> SetFillStyle(0) ;
   float circle_rj_radius = 0.5 ;

   TEllipse* circle_gj = new TEllipse() ;
   circle_gj -> SetLineColor(3) ;
   circle_gj -> SetLineWidth(2) ;
   circle_gj -> SetFillColor(0) ;
   circle_gj -> SetFillStyle(0) ;
   float circle_gj_radius = 0.5 ;

   TArrow* arrow = new TArrow() ;
   arrow -> SetLineWidth(3) ;
   arrow -> SetFillStyle(0) ;

   TLine* jet_pt_bar = new TLine() ;
   jet_pt_bar -> SetLineWidth(3) ;
   jet_pt_bar -> SetLineColor(2) ;
   double jet_pt_bar_scale = 0.8/2. ; // deta/pt
   double jet_pt_bar_deta = 0.1 ;
   double jet_pt_bar_dphi = -0.20 ;

   TLine* genjet_pt_bar = new TLine() ;
   genjet_pt_bar -> SetLineWidth(3) ;
   genjet_pt_bar -> SetLineColor(3) ;
   double genjet_pt_bar_scale = 0.8/2. ; // deta/pt
   double genjet_pt_bar_deta = 0.2 ;
   double genjet_pt_bar_dphi = -0.20 ;


   TText* textp3 = new TText() ;
   textp3 -> SetTextSize(0.035) ;
   textp3 -> SetTextFont( 42 ) ;

   TEllipse* circle_border = new TEllipse() ;
   circle_border -> SetLineWidth(1) ;
   circle_border -> SetFillColor(0) ;
   circle_border -> SetFillStyle(0) ;

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


    //--- begin event selection / reconstruction
    //
    //

      if ( Particle_PT[4] < 1.8 ) continue ; //--- simulate pthat > 1.8

      if ( Jet05_ < 2 ) continue ;
      if ( Jet05_Eta[0] < 2.6 ) continue ;
      if ( Jet05_Eta[1] < 2.6 ) continue ;

      if ( Jet05_PT[0] < 4.0 ) continue ;
      if ( Jet05_PT[1] < 4.0 ) continue ;

      float rec_dphi = calc_dphi( Jet05_Phi[0], Jet05_Phi[1] ) ;

      if ( rec_dphi < 3.14159265/2. ) continue ;

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


      //if ( genjetht > 0.1 ) continue ;
      //if ( genjetht < 5 ) continue ;




    //
    //
    //--- end event selection / reconstruction



      printf("\n\n Event %llu,  %d gen particles,  Event_ = %d\n", jentry, Particle_, Event_ ) ;
      printf("     Scale = %10.2f  AlphaQED = %10.6f  AlphaQCD = %9.3f  ID1 = %6d  ID2 = %6d  X1 = %7.5f  X2 = %7.5f\n",
         Event_Scale[0],
         Event_AlphaQED[0],
         Event_AlphaQCD[0],
         Event_ID1[0],
         Event_ID2[0],
         Event_X1[0],
         Event_X2[0] ) ;

      for ( int pi=0; pi<Particle_; pi++ ) {

         sprintf( pname, "%s", mcname( Particle_PID[pi] ) ) ;
         if ( Particle_Status[pi] > 30 || Particle_Status[pi] == 2 ) continue ;
         printf("  %3d :  PID %7d  %8s  Status %6d  M1 %5d M2 %5d  D1 %5d D2 %5d  q %3d  m %8.3f  E %9.2f  Pt = %7.2f Eta = %9.3f",
            pi,
            Particle_PID[pi],
            pname,
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
         if ( Particle_Status[pi] == 1 && Particle_Eta[pi] > -1.0 && Particle_Eta[pi] < 2.0 ) { printf(" *") ; }
         printf("\n") ;

      } // pi

      printf("\n\n  Gen jet HT = %.2f   Gen particle HT = %.2f\n\n", genjetht, genparticleht ) ;

      pad1 -> cd() ;

      hp -> Draw() ;

      for ( int pi=0; pi<Particle_; pi++ ) {
         float eta = Particle_Eta[pi] ;
         float phi = Particle_Phi[pi] ;
         float pt = Particle_PT[pi] ;
         if ( Particle_Status[pi] == 1 && pt>0.100   ) {
            float sf = 2*log( 1. + pt ) ;
            marker_fsp -> SetMarkerSize( sf ) ;
            marker_fsp -> DrawMarker( eta, phi ) ;
         }
         if ( Particle_Status[pi] == 23 ) {
            marker_gp -> DrawMarker( eta, phi ) ;
            sprintf( pname, "%s Pt=%4.2f", mcname( Particle_PID[pi] ), Particle_PT[pi] ) ;
            text -> DrawText( eta+0.1, phi+0.1, pname ) ;
         }
      } // pi

      printf("\n") ;
      for ( int pi=0; pi<Particle_; pi++ ) {
         float eta = Particle_Eta[pi] ;
         float phi = Particle_Phi[pi] ;
         float pt = Particle_PT[pi] ;
         if ( Particle_Status[pi] == 23 ) {
            marker_gp -> DrawMarker( eta, phi ) ;
            sprintf( pname, "%s Pt=%4.2f", mcname( Particle_PID[pi] ), Particle_PT[pi] ) ;
            text -> DrawText( eta+0.1, phi+0.1, pname ) ;
            printf("  parton %2d :  Pt = %6.2f   Eta = %7.2f  Phi = %7.2f\n", pi, pt, eta, phi ) ;
         }
      } // pi

      printf("\n") ;
      for ( int ji=0; ji<GenJet05_; ji++ ) {
         float eta = GenJet05_Eta[ji] ;
         float phi = GenJet05_Phi[ji] ;
         float pt  = GenJet05_PT[ji] ;
         circle_gj -> DrawEllipse( eta, phi, circle_gj_radius, circle_gj_radius, 0., 360., 0. ) ;
         genjet_pt_bar -> DrawLine( eta+genjet_pt_bar_deta, phi+genjet_pt_bar_dphi,
                         eta+genjet_pt_bar_deta + genjet_pt_bar_scale*pt, phi+genjet_pt_bar_dphi ) ;
         printf("  GenJet05 %2d :  Pt = %6.2f   Eta = %7.2f  Phi = %7.2f\n", ji, pt, eta, phi ) ;
      } // ji

////  printf("\n") ;
////  for ( int ji=0; ji<GenJet10_; ji++ ) {
////     float eta = GenJet10_Eta[ji] ;
////     float phi = GenJet10_Phi[ji] ;
////     float pt  = GenJet10_PT[ji] ;
////     printf("  GenJet10 %2d :  Pt = %6.2f   Eta = %7.2f  Phi = %7.2f\n", ji, pt, eta, phi ) ;
////  } // ji

      printf("\n") ;
      for ( int ji=0; ji<Jet05_; ji++ ) {
         float eta = Jet05_Eta[ji] ;
         float phi = Jet05_Phi[ji] ;
         float pt  = Jet05_PT[ji] ;
         circle_rj -> DrawEllipse( eta, phi, circle_rj_radius, circle_rj_radius, 0., 360., 0. ) ;
         jet_pt_bar -> DrawLine( eta+jet_pt_bar_deta, phi+jet_pt_bar_dphi,
                         eta+jet_pt_bar_deta + jet_pt_bar_scale*pt, phi+jet_pt_bar_dphi ) ;
         printf("  RecJet05 %2d :  Pt = %6.2f   Eta = %7.2f  Phi = %7.2f\n", ji, pt, eta, phi ) ;
      } // ji

////  printf("\n") ;
////  for ( int ji=0; ji<Jet10_; ji++ ) {
////     float eta = Jet10_Eta[ji] ;
////     float phi = Jet10_Phi[ji] ;
////     float pt  = Jet10_PT[ji] ;
////     printf("  RecJet10 %2d :  Pt = %6.2f   Eta = %7.2f  Phi = %7.2f\n", ji, pt, eta, phi ) ;
////  } // ji

      pad1 -> Update() ;
      pad1 -> Draw() ;



    //------------


      can -> cd() ;
      TPad* pad2 = new TPad("pad2","", 0.02, 0.02,  0.48, 0.48 ) ;
      pad2->Draw() ;
      pad2->cd() ;

      hp2 -> Draw() ;
      gPad -> SetGridx(1) ;
      gPad -> SetGridy(1) ;

      circle_border -> DrawEllipse( 0, 0, 8., 8., 0., 360., 0. ) ;

      for ( int pi=0; pi<Particle_; pi++ ) {
         if ( Particle_Status[pi] != 23 ) continue ;
         float eta = Particle_Eta[pi] ;
         float phi = Particle_Phi[pi] ;
         float pt = Particle_PT[pi] ;
         float px = pt * cos( phi ) ;
         float py = pt * sin( phi ) ;
     //  arrow -> SetLineWidth(3) ;
     //  arrow -> SetLineColor( 4 ) ;
     //  arrow -> DrawArrow( 0., 0., px, py, 0.02 ) ;
      } // pi

      for ( int ji=0; ji<GenJet05_; ji++ ) {
         float eta = GenJet05_Eta[ji] ;
         float phi = GenJet05_Phi[ji] ;
         float pt  = GenJet05_PT[ji] ;
         float px = pt * cos( phi ) ;
         float py = pt * sin( phi ) ;
         if ( eta > 2.4 ) {
            arrow -> SetLineWidth(3) ;
            arrow -> SetLineColor( 3 ) ;
            arrow -> DrawArrow( 0., 0., px, py, 0.02 ) ;
         }
      } // ji

      for ( int ji=0; ji<Jet05_; ji++ ) {
         float eta = Jet05_Eta[ji] ;
         float phi = Jet05_Phi[ji] ;
         float pt  = Jet05_PT[ji] ;
         float px = pt * cos( phi ) ;
         float py = pt * sin( phi ) ;
         arrow -> SetLineWidth(6) ;
         arrow -> SetLineColor( 2 ) ;
         arrow -> DrawArrow( 0., 0., px, py, 0.02 ) ;
      } // ji



      float Pperp_random_sign = 1. ;
      if ( gRandom -> Integer(2) == 1 ) Pperp_random_sign = -1. ;

      float jet0px = Jet05_PT[0]*cos(Jet05_Phi[0]) ;
      float jet0py = Jet05_PT[0]*sin(Jet05_Phi[0]) ;

      float jet1px = Jet05_PT[1]*cos(Jet05_Phi[1]) ;
      float jet1py = Jet05_PT[1]*sin(Jet05_Phi[1]) ;

      float Pperpx = 0.5 * ( jet0px - jet1px ) * Pperp_random_sign ;
      float Pperpy = 0.5 * ( jet0py - jet1py ) * Pperp_random_sign ;
      float Pperp = sqrt( Pperpx*Pperpx + Pperpy*Pperpy ) ;

      float qperpx =       ( jet0px + jet1px ) ;
      float qperpy =       ( jet0py + jet1py ) ;
      float qperp = sqrt( qperpx*qperpx + qperpy*qperpy ) ;

      float phi_Pperp = atan2( Pperpy, Pperpx ) ;
      float phi_qperp = atan2( qperpy, qperpx ) ;

      float dphi_Pperp_qperp = calc_dphi( phi_Pperp, phi_qperp ) ;

      arrow -> SetLineWidth(6) ;
      arrow -> SetLineColor( 1 ) ;
      arrow -> DrawArrow( 0., 0.,  Pperpx, Pperpy, 0.02 ) ;

      arrow -> SetLineWidth(6) ;
      arrow -> SetLineColor( 6 ) ;
      arrow -> DrawArrow( 0., 0.,  qperpx, qperpy, 0.02 ) ;

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

         bool has_2gjm(false) ;
         if ( ind_gj0>=0 && ind_gj1>=0 && ind_gj0!=ind_gj1 && gj0dr<0.3 && gj1dr<0.3 ) has_2gjm = true ;

         if ( has_2gjm ) {
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

      arrow -> SetLineStyle( 3 ) ;

      arrow -> SetLineWidth(6) ;
      arrow -> SetLineColor( 1 ) ;
      arrow -> DrawArrow( 0., 0.,  genPperpx, genPperpy, 0.02, ">" ) ;

      arrow -> SetLineWidth(6) ;
      arrow -> SetLineColor( 6 ) ;
      arrow -> DrawArrow( 0., 0.,  genqperpx, genqperpy, 0.02, ">" ) ;

      arrow -> SetLineStyle( 1 ) ;
         }

      pad2 -> Update() ;
      pad2 -> Draw() ;


    //------------


      can -> cd() ;
      TPad* pad3 = new TPad("pad3","", 0.52, 0.02,  0.98, 0.48 ) ;
      pad3->Draw() ;
      pad3->cd() ;

      float ty = 0.9 ;
      float dty = 0.05 ;

      char line_text[100] ;

      sprintf( line_text, "Event %lld", jentry ) ;
      textp3 -> DrawTextNDC( 0.1, ty, line_text ) ;
      ty = ty - dty ;

      sprintf( line_text, "x1 = %6.4f, %s", Event_X1[0], mcname( Particle_PID[4] ) ) ;
      textp3 -> DrawTextNDC( 0.1, ty, line_text ) ;
      ty = ty - dty ;

      sprintf( line_text, "x2 = %6.4f, %s", Event_X2[0], mcname( Particle_PID[5] ) ) ;
      textp3 -> DrawTextNDC( 0.1, ty, line_text ) ;
      ty = ty - dty ;

      sprintf( line_text, "Pperp = %6.2f    qperp = %6.2f", Pperp, qperp ) ;
      textp3 -> DrawTextNDC( 0.1, ty, line_text ) ;
      ty = ty - dty ;


      pad3 -> Update() ;
      pad3 -> Draw() ;

      //printf("\n\n Jet05_Constituents length for first jet:  %d\n\n", Jet05_Constituents[0].GetEntries() ) ;
      //printf("\n\n Jet05_Constituents pointer to first constituent:  %p\n\n", Jet05_Constituents[0].At(0) ) ;



      printf("  continue?  type q if no.  type b to go back one event. ") ;
      char answ = getchar() ;
      if ( answ == 'q' ) break ;
      if ( answ == 'b' ) jentry = jentry -3 ;

   } // jentry

}


//=================================================================================


const char* mcname( int pdgid ) {

   sprintf( pname, "" ) ;

   if ( pdgid == 1 ) sprintf( pname, "d" ) ;
   if ( pdgid == 2 ) sprintf( pname, "u" ) ;
   if ( pdgid == 3 ) sprintf( pname, "s" ) ;
   if ( pdgid == 4 ) sprintf( pname, "c" ) ;
   if ( pdgid == 5 ) sprintf( pname, "b" ) ;
   if ( pdgid == 6 ) sprintf( pname, "t" ) ;

   if ( pdgid == -1 ) sprintf( pname, "d-bar" ) ;
   if ( pdgid == -2 ) sprintf( pname, "u-bar" ) ;
   if ( pdgid == -3 ) sprintf( pname, "s-bar" ) ;
   if ( pdgid == -4 ) sprintf( pname, "c-bar" ) ;
   if ( pdgid == -5 ) sprintf( pname, "b-bar" ) ;
   if ( pdgid == -6 ) sprintf( pname, "t-bar" ) ;

   if ( pdgid == 11 ) sprintf( pname, "e-" ) ;
   if ( pdgid == 12 ) sprintf( pname, "nu_e" ) ;
   if ( pdgid == 13 ) sprintf( pname, "mu-" ) ;
   if ( pdgid == 14 ) sprintf( pname, "nu_mu" ) ;
   if ( pdgid == 15 ) sprintf( pname, "tau-" ) ;
   if ( pdgid == 16 ) sprintf( pname, "nu_tau" ) ;

   if ( pdgid == -11 ) sprintf( pname, "e+" ) ;
   if ( pdgid == -12 ) sprintf( pname, "nu_e-bar" ) ;
   if ( pdgid == -13 ) sprintf( pname, "mu+" ) ;
   if ( pdgid == -14 ) sprintf( pname, "nu_mu-bar" ) ;
   if ( pdgid == -15 ) sprintf( pname, "tau+" ) ;
   if ( pdgid == -16 ) sprintf( pname, "nu_tau-bar" ) ;

   if ( pdgid == 21 ) sprintf( pname, "gluon" ) ;
   if ( pdgid == 22 ) sprintf( pname, "photon" ) ;
   if ( pdgid == 23 ) sprintf( pname, "Z0" ) ;
   if ( pdgid == 24 ) sprintf( pname, "W+" ) ;
   if ( pdgid ==-24 ) sprintf( pname, "W-" ) ;
   if ( pdgid == 25 ) sprintf( pname, "h" ) ;
   if ( pdgid == 35 ) sprintf( pname, "H" ) ;
   if ( pdgid == 36 ) sprintf( pname, "a" ) ;

   if ( pdgid ==  2212 ) sprintf( pname, "proton" ) ;
   if ( pdgid == -2212 ) sprintf( pname, "pbar" ) ;
   if ( pdgid ==  2112 ) sprintf( pname, "neutron" ) ;
   if ( pdgid == -2112 ) sprintf( pname, "nbar" ) ;

   if ( pdgid ==  211 ) sprintf( pname, "pi+" ) ;
   if ( pdgid == -211 ) sprintf( pname, "pi-" ) ;
   if ( pdgid ==  111 ) sprintf( pname, "pi0" ) ;

   if ( pdgid ==  221 ) sprintf( pname, "eta" ) ;

   if ( pdgid ==  130 ) sprintf( pname, "K0L" ) ;
   if ( pdgid ==  310 ) sprintf( pname, "K0S" ) ;
   if ( pdgid ==  321 ) sprintf( pname, "K+" ) ;
   if ( pdgid == -321 ) sprintf( pname, "K-" ) ;
   if ( pdgid ==  313 ) sprintf( pname, "K*(892)0" ) ;
   if ( pdgid ==  323 ) sprintf( pname, "K*(892)+" ) ;
   if ( pdgid == -323 ) sprintf( pname, "K*(892)-" ) ;
   if ( pdgid ==  311 ) sprintf( pname, "K0" ) ;
   if ( pdgid == -311 ) sprintf( pname, "K0bar" ) ;

   if ( pdgid ==  2101 ) sprintf( pname, "(ud)0" ) ;
   if ( pdgid ==  2103 ) sprintf( pname, "(ud)1" ) ;

   if ( pdgid ==  2114 ) sprintf( pname, "Delta0" ) ;
   if ( pdgid == -2114 ) sprintf( pname, "Delta0b" ) ;
   if ( pdgid ==  1114 ) sprintf( pname, "Delta-" ) ;
   if ( pdgid ==  2214 ) sprintf( pname, "Delta+" ) ;

   if ( pdgid ==  3122 ) sprintf( pname, "Lambda" ) ;

   if ( pdgid ==  3212 ) sprintf( pname, "Sigma0" ) ;
   if ( pdgid ==  3222 ) sprintf( pname, "Sigma+" ) ;
   if ( pdgid == -3222 ) sprintf( pname, "Sigma+b" ) ;
   if ( pdgid ==  3112 ) sprintf( pname, "Sigma-" ) ;
   if ( pdgid == -3112 ) sprintf( pname, "Sigma-b" ) ;

   return pname ;


} // mcname




