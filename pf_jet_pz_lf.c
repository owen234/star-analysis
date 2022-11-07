
#include "histio.c"
#include "utils.c"

   void pf_jet_pt_lf( const char* infile = "ca4-output/all.root" ) {


      gStyle -> SetOptStat("mr") ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;

      gStyle -> SetStatX(0.83) ;
      gStyle -> SetStatY(0.85) ;
      gStyle -> SetStatW(0.30) ;
      gStyle -> SetStatH(0.20) ;


      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;


      TH2F* h_pz1_vs_pz0 = get_hist2d( "h_r2j_j1_vs_j0_pz" ) ;

      TH2F* h_pz_rec_vs_gen = get_hist2d( "h_j0_pzrec_vs_pzgen" ) ;


      h_pz_rec_vs_gen -> SetXTitle( "Jet pz (GeV), gen jet" ) ;
      h_pz_rec_vs_gen -> SetYTitle( "Jet pz (GeV), reconstructed jet" ) ;

      h_pz_rec_vs_gen -> SetTitleOffset( 1.4, "x" ) ;
      h_pz_rec_vs_gen -> SetTitleOffset( 1.4, "y" ) ;



      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      h_pz_rec_vs_gen -> SetStats(0) ;

      h_pz_rec_vs_gen -> Draw("colz") ;


      can1 -> SaveAs( "plots/pf_pz_rec_vs_gen.pdf" ) ;

    //---------------

      TH1D* hp1da = h_pz1_vs_pz0 -> ProjectionX() ;
      TH1D* hp1db = h_pz1_vs_pz0 -> ProjectionY() ;

      hp1da -> SetLineWidth(3) ;
      hp1db -> SetLineWidth(3) ;

      hp1da -> SetLineColor(4) ;
      hp1db -> SetLineColor(2) ;

      hp1db -> SetXTitle( "Jet pz (GeV)" ) ;
      hp1db -> SetYTitle( "Events" ) ;

      gStyle -> SetPadRightMargin(0.05) ;
      gStyle -> SetPadBottomMargin(0.18) ;
      gStyle -> SetPadLeftMargin(0.20) ;

      gStyle -> SetStatX(0.89) ;
      gStyle -> SetStatY(0.85) ;
      gStyle -> SetStatW(0.40) ;
      gStyle -> SetStatH(0.25) ;

      hp1da -> SetLabelSize( 0.065, "x" ) ;
      hp1da -> SetLabelSize( 0.065, "y" ) ;
      hp1da -> SetTitleSize( 0.065, "x" ) ;
      hp1da -> SetTitleSize( 0.065, "y" ) ;

      hp1db -> SetLabelSize( 0.065, "x" ) ;
      hp1db -> SetLabelSize( 0.065, "y" ) ;
      hp1db -> SetTitleSize( 0.065, "x" ) ;
      hp1db -> SetTitleSize( 0.065, "y" ) ;

      hp1db -> SetTitleOffset( 1.6, "y" ) ;
      hp1db -> SetTitleOffset( 1.3, "x" ) ;
      hp1da -> SetTitleOffset( 1.6, "y" ) ;
      hp1da -> SetTitleOffset( 1.3, "x" ) ;

      hp1da -> SetNdivisions(505) ;
      hp1db -> SetNdivisions(505) ;


      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      hp1da -> Draw("hist") ;
      gPad->Update() ;
      hp1db -> Draw("hist") ;
      gPad->Update() ;

      hp1db -> Draw("hist") ;
      hp1da -> Draw("hist same") ;
      hp1db -> Draw("same") ;
      hp1da -> Draw("same") ;


      TPaveStats* tpsa = (TPaveStats*) hp1da -> GetListOfFunctions()->FindObject("stats") ;
      if ( tpsa != 0x0 ) {
         tpsa -> SetLineColor(2) ;
         tpsa -> SetTextColor(2) ;
         tpsa -> SetY1NDC(0.65) ;
         tpsa -> SetY2NDC(0.75) ;
      } else {
         printf("No stats???\n") ;
      }

      TPaveStats* tpsb = (TPaveStats*) hp1db -> GetListOfFunctions()->FindObject("stats") ;
      if ( tpsb != 0x0 ) {
         tpsb -> SetLineColor(4) ;
         tpsb -> SetTextColor(4) ;
         tpsb -> SetY1NDC(0.78) ;
         tpsb -> SetY2NDC(0.88) ;
      } else {
         printf("No stats???\n") ;
      }

      char fname[1000] ;
      sprintf( fname, "plots/pf_jet_pz_sel%d_1d.pdf", 1 ) ;
      can2 -> SaveAs( fname ) ;



   }









