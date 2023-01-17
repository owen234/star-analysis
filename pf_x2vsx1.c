
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


      hp2dlin -> SetXTitle( "x_{1}" ) ;
      hp2dlin -> SetYTitle( "x_{2}" ) ;
      hp2dlin -> SetTitleSize( 0.060, "x" ) ;
      hp2dlin -> SetTitleSize( 0.060, "y" ) ;
      hp2dlin -> SetTitleOffset(1.0,"x") ;
      hp2dlin -> SetTitleOffset(0.8,"y") ;

      hp2dlin -> SetTitle(0) ;
      hp2dlin -> SetStats(0) ;


      hp2dlin -> Draw("colz") ;
      gPad->SetLogx(1) ;
      gPad->SetLogy(1) ;

      can -> SaveAs( "plots/pf_x2vsx1.pdf" ) ;

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
      h_x1 -> SetYTitle( "Events" ) ;
      h_x1 -> SetTitleOffset( 1.75, "y" ) ;

      h_x1 -> Draw( "hist" ) ;
      h_x1 -> Draw( "same" ) ;
      h_x2 -> Draw("hist same") ;
      h_x2 -> Draw("same") ;

      h_x1_pm -> Draw( "hist same" ) ;
      h_x1_pm -> Draw( "same" ) ;
      h_x2_pm -> Draw("hist same") ;
      h_x2_pm -> Draw("same") ;

      gPad -> SetLogx(1) ;

      float lx1 = 0.20 ;
      float ly1 = 0.84 ;
      float ldx = 0.08 ;
      float ldy = 0.07 ;
      TLine* tl = new TLine() ;
      tl -> SetLineWidth(4) ;

      tl -> SetLineColor(4) ;
      tl -> SetLineStyle(1) ;
      tl -> DrawLineNDC( lx1, ly1, lx1+ldx, ly1 ) ;
      tl -> SetLineStyle(2) ;
      tl -> DrawLineNDC( lx1, ly1-ldy, lx1+ldx, ly1-ldy ) ;

      tl -> SetLineColor(2) ;
      tl -> SetLineStyle(1) ;
      tl -> DrawLineNDC( lx1, ly1-2*ldy, lx1+ldx, ly1-2*ldy ) ;
      tl -> SetLineStyle(2) ;
      tl -> DrawLineNDC( lx1, ly1-3*ldy, lx1+ldx, ly1-3*ldy ) ;

      TLatex* text = new TLatex() ;
      text -> SetTextSize(0.040) ;
      text -> SetTextFont( 62 ) ;

      text -> DrawLatexNDC( lx1+1.1*ldx, ly1-0.2*ldy, "x_{1}" ) ;
      text -> DrawLatexNDC( lx1+1.1*ldx, ly1-1.2*ldy, "x_{1} , parton matched" ) ;
      text -> DrawLatexNDC( lx1+1.1*ldx, ly1-2.2*ldy, "x_{2}" ) ;
      text -> DrawLatexNDC( lx1+1.1*ldx, ly1-3.2*ldy, "x_{2} , parton matched" ) ;




      can2 -> SaveAs( "plots/pf_x2_and_x1.pdf" ) ;

   }









