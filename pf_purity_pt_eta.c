
#include "histio.c"
#include "utils.c"

   void pf_purity_pt_eta( const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;


      TH2F* hp_pt_all = get_hist2d( "h_j1pt_vs_j0pt_all" ) ;
      TH2F* hp_pt_pm  = get_hist2d( "h_j1pt_vs_j0pt_pm" ) ;

      hp_pt_pm->Divide( hp_pt_all ) ;

      hp_pt_pm -> SetXTitle( "Jet pT (GeV), higher pT jet" ) ;
      hp_pt_pm -> SetYTitle( "Jet pT (GeV), lower pT jet" ) ;

      hp_pt_pm -> SetTitleOffset( 1.5, "y" ) ;
      hp_pt_pm -> SetTitleOffset( 1.5, "x" ) ;


      hp_pt_pm -> GetXaxis() -> SetRangeUser( 2.2, 8. ) ;
      hp_pt_pm -> GetYaxis() -> SetRangeUser( 2.2, 8. ) ;



      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      hp_pt_pm -> Draw("colz") ;


      can1 -> SaveAs( "pf_purity_pt.pdf"  ) ;

    //---------------

      TH2F* hp_eta_all = get_hist2d( "h_j1eta_vs_j0eta_all" ) ;
      TH2F* hp_eta_pm  = get_hist2d( "h_j1eta_vs_j0eta_pm" ) ;

      hp_eta_pm->Divide( hp_eta_all ) ;

      hp_eta_pm -> SetXTitle( "Jet eta, higher pT jet" ) ;
      hp_eta_pm -> SetYTitle( "Jet eta, lower pT jet" ) ;

      hp_eta_pm -> SetTitleOffset( 1.5, "y" ) ;
      hp_eta_pm -> SetTitleOffset( 1.5, "x" ) ;


      hp_eta_pm -> GetXaxis() -> SetRangeUser( 2.2, 8. ) ;
      hp_eta_pm -> GetYaxis() -> SetRangeUser( 2.2, 8. ) ;



      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      hp_eta_pm -> Draw("colz") ;


      can2 -> SaveAs( "pf_purity_eta.pdf"  ) ;

    //---------------





   }









