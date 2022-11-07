
#include "histio.c"
#include "utils.c"

   void pf_qperp_Pperp( const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;

      TH2F* hp2d = get_hist2d( "h_qperp_vs_Pperp_sel3" ) ;

      hp2d -> SetXTitle( "Average jet pT (P_{#perp}  )" ) ;
      hp2d -> SetYTitle( "Imbalance in jet pT (q_{#perp}  )" ) ;


      //hp2d -> GetXaxis() -> SetRangeUser( 2.2, 8. ) ;
      //hp2d -> GetYaxis() -> SetRangeUser( 2.2, 8. ) ;



      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      hp2d -> Draw("colz") ;
      //gPad->SetLogz(1) ;


      char fname[1000] ;

//    sprintf( fname, "pf_jet1pt_vs_jet0pt_sel%d_2d.pdf", sel ) ;
//    can1 -> SaveAs( fname ) ;

//  //---------------


      TH1D* h_pperp = hp2d -> ProjectionX() ;
      TH1D* h_qperp = hp2d -> ProjectionY() ;

      h_pperp -> SetLineWidth(3) ;
      h_qperp -> SetLineWidth(3) ;

      h_pperp -> SetLineColor(4) ;
      h_qperp -> SetLineColor(2) ;

      h_pperp -> SetYTitle( "Events" ) ;
      h_qperp -> SetYTitle( "Events" ) ;

      h_pperp -> SetTitleOffset( 1.4, "x" ) ;
      h_pperp -> SetTitleOffset( 1.7, "y" ) ;
      h_qperp -> SetTitleOffset( 1.4, "x" ) ;
      h_qperp -> SetTitleOffset( 1.9, "y" ) ;



      //hp1db -> SetLineColor(2) ;

//    hp1da -> SetXTitle( "Jet pT (GeV)" ) ;

      /////gStyle -> SetOptStat("mri") ;

      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      h_pperp -> Draw( ) ;
      h_pperp -> Draw( "same hist" ) ;
      gPad -> SetLogy(1) ;

      can2 -> SaveAs( "plots/pf_pperp.pdf" ) ;


      TCanvas* can3 = get_canvas( "can3", "", 1550, 150, 900, 900 ) ;
      can3 -> cd() ;
      can3 -> Clear() ;

      h_qperp -> Draw( ) ;
      h_qperp -> Draw( "same hist" ) ;

      can3 -> SaveAs( "plots/pf_qperp.pdf" ) ;



   }









