
#include "histio.c"
#include "utils.c"

   void pf_x2vsx1( const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;

      gStyle -> SetOptStat(0) ;

      TCanvas* can = get_canvas( "can", "", 50, 50, 900, 900 ) ;
      can -> cd() ;
      can -> Clear() ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;

      TH2F* hp2d = get_hist2d( "h_log10x2_vs_log10x1_sel3" ) ;


      TH2F* hp2dlin = convert_log10_to_linear_2d( hp2d ) ;

       hp2dlin -> GetXaxis() -> SetRangeUser( 1e-4, 2. ) ;
       hp2dlin -> GetYaxis() -> SetRangeUser( 1e-4, 2. ) ;


      hp2dlin -> SetXTitle( "x1" ) ;
      hp2dlin -> SetYTitle( "x2" ) ;

      hp2dlin -> SetTitle(0) ;
      hp2dlin -> SetStats(0) ;

      hp2dlin -> SetTitleOffset(1.2,"x") ;
      hp2dlin -> SetTitleOffset(1.4,"y") ;

      hp2dlin -> Draw("colz") ;
      gPad->SetLogx(1) ;
      gPad->SetLogy(1) ;

      can -> SaveAs( "pf_x2vsx1.pdf" ) ;

    //-------------------


      TH2F* hp2d_pm = get_hist2d( "h_log10x2_vs_log10x1_sel3_pm" ) ;

      TH2F* hp2dlin_pm = convert_log10_to_linear_2d( hp2d_pm ) ;

       hp2dlin_pm -> GetXaxis() -> SetRangeUser( 1e-4, 2. ) ;
       hp2dlin_pm -> GetYaxis() -> SetRangeUser( 1e-4, 2. ) ;

      TH1D* h_x1 = hp2dlin -> ProjectionX() ;
      TH1D* h_x2 = hp2dlin -> ProjectionY() ;

      TH1D* h_x1_pm = hp2dlin_pm -> ProjectionX() ;
      TH1D* h_x2_pm = hp2dlin_pm -> ProjectionY() ;

      h_x1 -> SetLineWidth(3) ;
      h_x2 -> SetLineWidth(3) ;

      h_x1 -> SetLineColor(4) ;
      h_x2 -> SetLineColor(2) ;

      h_x1_pm -> SetLineWidth(3) ;
      h_x2_pm -> SetLineWidth(3) ;

      h_x1_pm -> SetLineStyle(2) ;
      h_x2_pm -> SetLineStyle(2) ;

      h_x1_pm -> SetLineColor(4) ;
      h_x2_pm -> SetLineColor(2) ;

      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      h_x1 -> SetXTitle( "x" ) ;

      h_x1 -> Draw( "hist" ) ;
      h_x1 -> Draw( "same" ) ;
      h_x2 -> Draw("hist same") ;
      h_x2 -> Draw("same") ;

      h_x1_pm -> Draw( "hist same" ) ;
      h_x1_pm -> Draw( "same" ) ;
      h_x2_pm -> Draw("hist same") ;
      h_x2_pm -> Draw("same") ;

      gPad -> SetLogx(1) ;



   }









