
#include "histio.c"
#include "utils.c"

   void pf_jet_pt( const char* infile = "ca4-output/all.root" ) {


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

      TH1D* h_pz0 = h_pz1_vs_pz0 -> ProjectionX() ;
      TH1D* h_pz1 = h_pz1_vs_pz0 -> ProjectionY() ;

      h_pz0 -> SetLineWidth(3) ;
      h_pz1 -> SetLineWidth(3) ;

      h_pz0 -> SetLineColor(4) ;
      h_pz1 -> SetLineColor(2) ;

      h_pz1 -> SetXTitle( "Jet pz (GeV)" ) ;
      h_pz1 -> SetYTitle( "Events" ) ;

      h_pz1 -> SetTitleOffset( 1.4, "x" ) ;
      h_pz1 -> SetTitleOffset( 1.6, "y" ) ;

      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      h_pz0 -> Draw("hist") ;
      gPad->Update() ;
      h_pz1 -> Draw("hist") ;
      gPad->Update() ;

      h_pz1 -> Draw("hist") ;
      h_pz0 -> Draw("hist same") ;
      h_pz1 -> Draw("same") ;
      h_pz0 -> Draw("same") ;

      TH1D* hp1da = h_pz1 ;
      TH1D* hp1db = h_pz0 ;

      TPaveStats* tpsa = (TPaveStats*) hp1da -> GetListOfFunctions()->FindObject("stats") ;
      if ( tpsa != 0x0 ) {
         tpsa -> SetLineColor(2) ;
         tpsa -> SetTextColor(2) ;
         tpsa -> SetY1NDC(0.78) ;
         tpsa -> SetY2NDC(0.88) ;
      } else {
         printf("No stats???\n") ;
      }

      TPaveStats* tpsb = (TPaveStats*) hp1db -> GetListOfFunctions()->FindObject("stats") ;
      if ( tpsb != 0x0 ) {
         tpsb -> SetLineColor(4) ;
         tpsb -> SetTextColor(4) ;
         tpsb -> SetY1NDC(0.65) ;
         tpsb -> SetY2NDC(0.75) ;
      } else {
         printf("No stats???\n") ;
      }

      char fname[1000] ;
      sprintf( fname, "plots/pf_jet_pz_sel%d_1d.pdf", 1 ) ;
      can2 -> SaveAs( fname ) ;



   }









