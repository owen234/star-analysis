
#include "histio.c"
#include "utils.c"

   void pf_q2vsx( bool do_zoom = true, const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;

      TCanvas* can = get_canvas( "can", "", 50, 50, 900, 900 ) ;
      can -> cd() ;
      can -> Clear() ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;

      TH2F* hp2d = get_hist2d( "h_log10q2_vs_log10x2_pm" ) ;


      TH2F* hp2dlin = convert_log10_to_linear_2d( hp2d ) ;

      if ( do_zoom ) {
         hp2dlin -> GetXaxis() -> SetRangeUser( 1e-4, 1. ) ;
         hp2dlin -> GetYaxis() -> SetRangeUser( 0.2, 700 ) ;
      }


      hp2dlin -> SetXTitle( "x" ) ;
      hp2dlin -> SetYTitle( "Q^{2} (GeV^{2})" ) ;

      hp2dlin -> SetTitle(0) ;
      hp2dlin -> SetStats(0) ;

      hp2dlin -> SetTitleOffset(1.2,"x") ;
      hp2dlin -> SetTitleOffset(1.4,"y") ;

      hp2dlin -> Draw("colz") ;
      gPad->SetLogx(1) ;
      gPad->SetLogy(1) ;

      TLatex* tl = new TLatex() ;
      tl -> SetTextSize( 0.05 ) ;
      tl -> SetTextFont( 42 ) ;
      char label[1000] ;

      tl -> SetTextColor(1) ;
      tl -> SetTextAlign( 22 ) ;
      tl -> DrawLatexNDC( 0.50, 0.93, "This work : NN #rightarrow jet jet X" ) ;





      can -> SaveAs( "pf_q2vsx.pdf" ) ;


   }









