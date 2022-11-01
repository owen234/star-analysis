
#include "histio.c"
#include "utils.c"

   void pf_jet_dphi( const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;

      char hname[1000] ;
      sprintf( hname, "h_jj_dphi_precut" ) ;
      TH1F* hp = get_hist( hname ) ;

      hp -> SetXTitle( "di-jet Delta phi" ) ;

      hp -> SetTitleOffset( 1.5, "x" ) ;

      hp -> SetLineWidth(3) ;



      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      hp -> Draw("hist") ;
      hp -> Draw( "same" ) ;


      char fname[1000] ;

      sprintf( fname, "pf_jet_dphi.pdf" ) ;
      can1 -> SaveAs( fname ) ;




   }









