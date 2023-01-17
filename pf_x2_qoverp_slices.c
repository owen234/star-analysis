
#include "histio.c"
#include "utils.c"

   void pf_x2_qoverp_slices( const char* infile = "ca4-output/all.root" ) {

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

      TH2F* hp2d = get_hist2d( "h_log10x2_vs_qoverp_sel2" ) ;
      TH2F* hp2dpm = get_hist2d( "h_log10x2_vs_qoverp_sel2_pm" ) ;


      TH1D* hp1lx = hp2d -> ProjectionY("hp1lx",1,6) ;
      TH1D* hp2lx = hp2d -> ProjectionY("hp2lx",7,16) ;
      TH1D* hp3lx = hp2d -> ProjectionY("hp3lx",17,60) ;

      TH1D* hp1lxpm = hp2dpm -> ProjectionY("hp1lxpm",1,6) ;
      TH1D* hp2lxpm = hp2dpm -> ProjectionY("hp2lxpm",7,16) ;
      TH1D* hp3lxpm = hp2dpm -> ProjectionY("hp3lxpm",17,60) ;

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

      hp1 -> SetXTitle( "x_{2}" ) ;
      hp2 -> SetXTitle( "x_{2}" ) ;
      hp3 -> SetXTitle( "x_{2}" ) ;
      hp1 -> SetYTitle( "Events" ) ;
      hp2 -> SetYTitle( "Events" ) ;
      hp3 -> SetYTitle( "Events" ) ;

      hp1 -> SetTitleSize( 0.06, "x" ) ;
      hp2 -> SetTitleSize( 0.06, "x" ) ;
      hp3 -> SetTitleSize( 0.06, "x" ) ;
      hp1 -> SetTitleSize( 0.06, "y" ) ;
      hp2 -> SetTitleSize( 0.06, "y" ) ;
      hp3 -> SetTitleSize( 0.06, "y" ) ;

      hp1 -> SetTitleOffset( 1.1, "x" ) ;
      hp2 -> SetTitleOffset( 1.1, "x" ) ;
      hp3 -> SetTitleOffset( 1.1, "x" ) ;

      hp1 -> SetTitleOffset( 1.2, "y" ) ;
      hp2 -> SetTitleOffset( 1.2, "y" ) ;
      hp3 -> SetTitleOffset( 1.2, "y" ) ;

      hp1 -> SetLabelSize( 0.05, "x" ) ;
      hp2 -> SetLabelSize( 0.05, "x" ) ;
      hp3 -> SetLabelSize( 0.05, "x" ) ;
      hp1 -> SetLabelSize( 0.05, "y" ) ;
      hp2 -> SetLabelSize( 0.05, "y" ) ;
      hp3 -> SetLabelSize( 0.05, "y" ) ;

      TLatex* tt = new TLatex() ;
      tt -> SetTextFont( 42 ) ;
      tt -> SetTextSize( 0.06 ) ;
      tt -> SetTextAlign(31) ;

      float lx = 0.90 ;
      float ly = 0.94 ;

    //---------------

      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      hp1 -> Draw() ;
      hp1 -> Draw("same hist") ;
      hp1pm -> Draw("same hist") ;
      hp1pm -> Draw("same") ;
      gPad -> SetLogx(1) ;

      tt -> DrawLatexNDC( lx, ly, "q_{#perp}   /P_{#perp}    less than 0.3" ) ;

      can1 -> SaveAs( "plots/pf_x2_qoverp_lt_03.pdf" ) ;

    //---------------

      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      hp2 -> Draw() ;
      hp2 -> Draw("same hist") ;
      hp2pm -> Draw("same hist") ;
      hp2pm -> Draw("same") ;
      gPad -> SetLogx(1) ;

      tt -> DrawLatexNDC( lx, ly, "q_{#perp}   /P_{#perp}    from 0.3 to 0.8" ) ;

      can2 -> SaveAs( "plots/pf_x2_qoverp_03to08.pdf" ) ;

    //---------------

      TCanvas* can3 = get_canvas( "can3", "", 1150, 150, 900, 900 ) ;
      can3 -> cd() ;
      can3 -> Clear() ;

      hp3 -> Draw() ;
      hp3 -> Draw("same hist") ;
      hp3pm -> Draw("same hist") ;
      hp3pm -> Draw("same") ;
      gPad -> SetLogx(1) ;

      tt -> DrawLatexNDC( lx, ly, "q_{#perp}   /P_{#perp}    greater than 0.8" ) ;

      can3 -> SaveAs( "plots/pf_x2_qoverp_gt_08.pdf" ) ;

    //---------------



   }









