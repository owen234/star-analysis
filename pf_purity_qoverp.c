
#include "histio.c"
#include "utils.c"

   void pf_purity_qoverp( const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;



    //---------------


      TH1F* h_all = get_hist( "h_qperp_over_pperp_sel3" ) ;
      TH1F* h_pm = get_hist( "h_qperp_over_pperp_sel3_pm" ) ;

      h_pm -> Divide( h_all ) ;


      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      h_pm -> SetLineWidth(3) ;
      h_pm -> SetXTitle( "qperp / Pperp" ) ;
      h_pm -> SetYTitle( "Fraction of events, parton matched" ) ;

      h_pm -> SetMinimum(0.) ;
      h_pm -> SetMaximum(1.1) ;

      h_pm -> SetTitleOffset( 1.5, "y" ) ;
      h_pm -> SetTitleOffset( 1.5, "x" ) ;

      //h_pm -> GetXaxis() -> SetRangeUser( 2.2, 8. ) ;

      h_pm -> Draw() ;


    //---------------

      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      h_all -> SetLineWidth(3) ;
      h_all -> SetXTitle( "qperp / Pperp" ) ;
      h_all -> SetYTitle( "Events" ) ;
      h_all -> SetTitleOffset( 1.5, "y" ) ;
      h_all -> SetTitleOffset( 1.5, "x" ) ;

      h_all -> Draw("hist") ;
      h_all -> Draw("same") ;


   }









