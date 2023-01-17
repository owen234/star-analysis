
#include "histio.c"
#include "utils.c"

   void pf_dphijj2( const char* infile = "ca4-output/all.root" ) {


      //gStyle -> SetOptStat("mri") ;
      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.10) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;


      TH1F* hp = get_hist( "h_dphijj_rec" ) ;

     //-- reset error bars to sqrt(N) (probably very tiny).
      for ( int bi=1; bi<=16; bi++ ) {
         float val = hp -> GetBinContent( bi ) ;
         hp -> SetBinError( bi, sqrt(val) ) ;
      } // bi




      hp -> SetXTitle( "#Delta#phi_{jj}" ) ;
      hp -> SetYTitle( "Events" ) ;

      hp -> SetTitleOffset( 1.0, "x" ) ;
      hp -> SetTitleOffset( 1.2, "y" ) ;

      hp -> SetTitleSize( 0.065, "x" ) ;
      hp -> SetTitleSize( 0.065, "y" ) ;
      hp -> SetLabelSize( 0.050, "x" ) ;
      hp -> SetLabelSize( 0.050, "y" ) ;

      hp -> SetMarkerStyle(20) ;
      hp -> SetMarkerSize(2) ;

      hp -> SetNdivisions(804) ;



      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 700 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      hp -> SetMaximum( 1.5 * hp -> GetMaximum() ) ;

      hp -> Draw( "p" ) ;

      TLatex* tl = new TLatex() ;
      tl -> SetTextSize( 0.06 ) ;
      tl -> SetTextFont( 42 ) ;

      tl -> DrawLatexNDC( 0.30, 0.80, "This work : NN #rightarrow jet jet X" ) ;


      can1 -> SaveAs( "plots/pf_dphijj_16bins.pdf" ) ;




   }









