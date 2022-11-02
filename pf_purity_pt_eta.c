
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


      TH2F* hp_pt_all = get_hist2d( "h_jet1pt_vs_jet0pt_sel3" ) ;
      TH2F* hp_pt_pm  = get_hist2d( "h_jet1pt_vs_jet0pt_sel3_pm" ) ;

      TH1D* h_pt1_all = hp_pt_all -> ProjectionY("h_pt1_all") ;
      TH1D* h_pt1_pm  = hp_pt_pm  -> ProjectionY("h_pt1_pm") ;

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

      TH2F* hp_eta_all = get_hist2d( "h_jet1eta_vs_jet0eta_sel3" ) ;
      TH2F* hp_eta_pm  = get_hist2d( "h_jet1eta_vs_jet0eta_sel3_pm" ) ;

      TH1D* h_eta1_all = hp_eta_all -> ProjectionY("h_eta1_all") ;
      TH1D* h_eta1_pm  = hp_eta_pm  -> ProjectionY("h_eta1_pm") ;

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

      h_pt1_pm -> Divide( h_pt1_all ) ;


      TCanvas* can3 = get_canvas( "can3", "", 150, 150, 900, 900 ) ;
      can3 -> cd() ;
      can3 -> Clear() ;

      h_pt1_pm -> SetLineWidth(3) ;
      h_pt1_pm -> SetXTitle( "jet pT (GeV), lower pT jet" ) ;
      h_pt1_pm -> SetYTitle( "Fraction of events, parton matched" ) ;

      h_pt1_pm -> SetMinimum(0.) ;
      h_pt1_pm -> SetMaximum(1.1) ;

      h_pt1_pm -> SetTitleOffset( 1.5, "y" ) ;
      h_pt1_pm -> SetTitleOffset( 1.5, "x" ) ;

      h_pt1_pm -> GetXaxis() -> SetRangeUser( 2.2, 8. ) ;

      h_pt1_pm -> Draw() ;

    //---------------

      h_eta1_pm -> Divide( h_eta1_all ) ;


      TCanvas* can4 = get_canvas( "can4", "", 1050, 150, 900, 900 ) ;
      can4 -> cd() ;
      can4 -> Clear() ;

      h_eta1_pm -> SetLineWidth(3) ;
      h_eta1_pm -> SetXTitle( "jet eta, lower pT jet" ) ;
      h_eta1_pm -> SetYTitle( "Fraction of events, parton matched" ) ;

      h_eta1_pm -> SetMinimum(0.) ;
      h_eta1_pm -> SetMaximum(1.1) ;

      h_eta1_pm -> SetTitleOffset( 1.5, "y" ) ;
      h_eta1_pm -> SetTitleOffset( 1.5, "x" ) ;

      h_eta1_pm -> GetXaxis() -> SetRangeUser( 2.2, 8. ) ;

      h_eta1_pm -> Draw() ;


    //---------------


      TCanvas* can5 = get_canvas( "can5", "", 250, 250, 900, 900 ) ;
      can5 -> cd() ;
      can5 -> Clear() ;

      h_pt1_all -> SetLineWidth(3) ;
      h_pt1_all -> SetXTitle( "jet pT (GeV), lower pT jet" ) ;
      h_pt1_all -> SetYTitle( "Events" ) ;

      h_pt1_all -> SetTitleOffset( 1.5, "y" ) ;
      h_pt1_all -> SetTitleOffset( 1.5, "x" ) ;

      h_pt1_all -> GetXaxis() -> SetRangeUser( 2.2, 8. ) ;

      h_pt1_all -> Draw("hist") ;
      h_pt1_all -> Draw("same") ;
      gPad->SetLogy(1) ;


    //---------------


      TCanvas* can6 = get_canvas( "can6", "", 1250, 250, 900, 900 ) ;
      can6 -> cd() ;
      can6 -> Clear() ;

      h_eta1_all -> SetLineWidth(3) ;
      h_eta1_all -> SetXTitle( "jet eta, lower pT jet" ) ;
      h_eta1_all -> SetYTitle( "Events" ) ;

      h_eta1_all -> SetTitleOffset( 1.5, "y" ) ;
      h_eta1_all -> SetTitleOffset( 1.5, "x" ) ;

      h_eta1_all -> GetXaxis() -> SetRangeUser( 2.2, 8. ) ;

      h_eta1_all -> Draw("hist") ;
      h_eta1_all -> Draw("same") ;


   }









