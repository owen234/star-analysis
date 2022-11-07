
#include "histio.c"
#include "utils.c"

   void pf_x2_pt1slices( const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.10) ;

      gStyle -> SetStatX(0.83) ;
      gStyle -> SetStatY(0.85) ;
      gStyle -> SetStatW(0.30) ;
      gStyle -> SetStatH(0.20) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;

      TH2F* hp2d = get_hist2d( "h_log10x2_vs_pt1_sel2" ) ;
      TH2F* hp2dpm = get_hist2d( "h_log10x2_vs_pt1_sel2_pm" ) ;


      TH1D* hp1lx = hp2d -> ProjectionY("hp1lx",31,35) ;
      TH1D* hp2lx = hp2d -> ProjectionY("hp2lx",36,39) ;
      TH1D* hp3lx = hp2d -> ProjectionY("hp3lx",41,60) ;

      TH1D* hp1lxpm = hp2dpm -> ProjectionY("hp1lxpm",31,35) ;
      TH1D* hp2lxpm = hp2dpm -> ProjectionY("hp2lxpm",36,39) ;
      TH1D* hp3lxpm = hp2dpm -> ProjectionY("hp3lxpm",41,60) ;

      TH1F* hp1 = convert_log10_to_linear_1d( hp1lx ) ;
      TH1F* hp2 = convert_log10_to_linear_1d( hp2lx ) ;
      TH1F* hp3 = convert_log10_to_linear_1d( hp3lx ) ;
      TH1F* hp1pm = convert_log10_to_linear_1d( hp1lxpm ) ;
      TH1F* hp2pm = convert_log10_to_linear_1d( hp2lxpm ) ;
      TH1F* hp3pm = convert_log10_to_linear_1d( hp3lxpm ) ;

      hp1 -> SetLineWidth(3) ;
      hp2 -> SetLineWidth(3) ;
      hp3 -> SetLineWidth(3) ;
      hp1pm -> SetLineWidth(3) ;
      hp2pm -> SetLineWidth(3) ;
      hp3pm -> SetLineWidth(3) ;
      hp1pm -> SetLineStyle(2) ;
      hp2pm -> SetLineStyle(2) ;
      hp3pm -> SetLineStyle(2) ;

      hp1 -> SetXTitle( "x2" ) ;
      hp2 -> SetXTitle( "x2" ) ;
      hp3 -> SetXTitle( "x2" ) ;
      hp1 -> SetYTitle( "Events" ) ;
      hp2 -> SetYTitle( "Events" ) ;
      hp3 -> SetYTitle( "Events" ) ;

      hp1 -> SetTitleOffset( 1.5, "x" ) ;
      hp2 -> SetTitleOffset( 1.5, "x" ) ;
      hp3 -> SetTitleOffset( 1.5, "x" ) ;

      hp1 -> SetTitleOffset( 1.7, "y" ) ;
      hp2 -> SetTitleOffset( 1.7, "y" ) ;
      hp3 -> SetTitleOffset( 1.9, "y" ) ;

      TText* tt = new TText() ;
      tt -> SetTextFont( 42 ) ;
      tt -> SetTextSize( 0.04 ) ;
      tt -> SetTextAlign(31) ;

    //---------------

      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      hp1 -> Draw() ;
      hp1 -> Draw("same hist") ;
      hp1pm -> Draw("same hist") ;
      hp1pm -> Draw("same") ;
      gPad -> SetLogx(1) ;

      tt -> DrawTextNDC( 0.90, 0.92, "Lower pT jet pT from 3.0 to 3.5 GeV" ) ;

      can1 -> SaveAs( "plots/pf_x2_jet1pt_30to35.pdf" ) ;

    //---------------

      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      hp2 -> Draw() ;
      hp2 -> Draw("same hist") ;
      hp2pm -> Draw("same hist") ;
      hp2pm -> Draw("same") ;
      gPad -> SetLogx(1) ;

      tt -> DrawTextNDC( 0.90, 0.92, "Lower pT jet pT from 3.5 to 4.0 GeV" ) ;

      can2 -> SaveAs( "plots/pf_x2_jet1pt_35to40.pdf" ) ;

    //---------------

      TCanvas* can3 = get_canvas( "can3", "", 1150, 150, 900, 900 ) ;
      can3 -> cd() ;
      can3 -> Clear() ;

      hp3 -> Draw() ;
      hp3 -> Draw("same hist") ;
      hp3pm -> Draw("same hist") ;
      hp3pm -> Draw("same") ;
      gPad -> SetLogx(1) ;

      tt -> DrawTextNDC( 0.90, 0.92, "Lower pT jet pT greater than 4.0 GeV" ) ;

      can3 -> SaveAs( "plots/pf_x2_jet1pt_40.pdf" ) ;

    //---------------



   }









