
#include "histio.c"
#include "utils.c"

   void pf_genjetht( const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;

      char hname[1000] ;
      sprintf( hname, "h_r2j_genjetht_vs_log10x2_sel0" ) ;
      TH2F* hp2d = get_hist2d( hname ) ;

      TH1D* h_ht = hp2d -> ProjectionY( "hp2d" ) ;
      h_ht -> GetXaxis() -> SetRangeUser( 0.5, 20 ) ;

      h_ht -> SetLineWidth(3) ;

      h_ht -> SetTitleOffset( 1.3, "x" ) ;



      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      h_ht -> SetXTitle( "Scalar sum, gen Jet pT, -1<eta<2, (GeV)" ) ;

      h_ht -> Draw( "hist" ) ;
      h_ht -> Draw( "same" ) ;



      char fname[1000] ;

      sprintf( fname, "pf_genjetht.pdf" ) ;
      can1 -> SaveAs( fname ) ;

    //---------------


      TH1D* h_x2_ht0  = hp2d -> ProjectionX( "h_x2_ht0", 1, 1 ) ;
      TH1D* h_x2_htn0  = hp2d -> ProjectionX( "h_x2_htn0", 2, -1 ) ;

      h_x2_ht0 -> SetLineWidth(3) ;
      h_x2_htn0 -> SetLineWidth(3) ;

      h_x2_ht0 -> SetLineColor(4) ;
      h_x2_htn0 -> SetLineColor(2) ;

      h_x2_ht0 -> SetXTitle( "x" ) ;

      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      h_x2_ht0 -> Draw("hist") ;
      h_x2_htn0 -> Draw("hist same") ;

      sprintf( fname, "pf_x2_htcut.pdf" ) ;
      can1 -> SaveAs( fname ) ;



   }









