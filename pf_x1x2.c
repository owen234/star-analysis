
#include "histio.c"
#include "utils.c"

   void pf_x1x2( const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;

      TCanvas* can = get_canvas( "can", "", 50, 50, 900, 600 ) ;
      can -> cd() ;
      can -> Clear() ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;

      TH2F* hp2d = get_hist2d( "h_log10x2_vs_log10x1_pm" ) ;


      TH2F* hp2dlin = convert_log10_to_linear_2d( hp2d ) ;

    //hp2dlin -> Draw("colz") ;
    //gPad->SetLogx(1) ;
    //gPad->SetLogy(1) ;

      TH1D* hp_x1 = hp2dlin->ProjectionX("hp_x1") ;
      TH1D* hp_x2 = hp2dlin->ProjectionY("hp_x2") ;



      hp_x1 -> SetLabelSize(0.050,"x") ;
      hp_x1 -> SetLabelSize(0.050,"y") ;

      hp_x1 -> SetTitle(0) ;
      hp_x1 -> SetStats(0) ;

      hp_x1 -> SetXTitle("x") ;
      hp_x1 -> SetTitleOffset(1.2,"x") ;
      hp_x1 -> SetTitleSize(0.060) ;

      hp_x1 -> SetLineWidth(4) ;
      hp_x2 -> SetLineWidth(4) ;

      hp_x1 -> SetLineColor(1) ;
      hp_x2 -> SetLineColor(2) ;

      hp_x1 -> SetLineStyle(2) ;
      hp_x2 -> SetLineStyle(1) ;

      hp_x1 -> Draw("hist") ;
      hp_x2 -> Draw("hist same") ;
      gPad->SetLogx(1) ;

      float mean_x1 = hp_x1 -> GetMean() ;
      float mean_x2 = hp_x2 -> GetMean() ;
      printf("\n\n Means:  x1  %8.5f,   x2 %8.5f\n\n", mean_x1, mean_x2 ) ;

      TLatex* tl = new TLatex() ;
      tl -> SetTextSize( 0.06 ) ;
      tl -> SetTextFont( 42 ) ;
      char label[1000] ;

      float tx = 0.14 ;
      float ty = 0.81 ;
      float dy = 0.11 ;

      sprintf( label, "#LTx_{1}#GT = %6.4f", mean_x1 ) ;
      tl -> DrawLatexNDC( tx, ty, label ) ;

      sprintf( label, "#LTx_{2}#GT = %6.4f", mean_x2 ) ;
      tl -> SetTextColor(2) ;
      tl -> DrawLatexNDC( tx, ty-dy, label ) ;


  /// TText* tt = new TText() ;
  /// tt -> SetTextFont( 42 ) ;
  /// tt -> SetTextSize( 0.06 ) ;
  /// tt -> DrawTextNDC( 0.30, 0.93, "This work : NN -> jet jet" ) ;
      tl -> SetTextColor(1) ;
      tl -> DrawLatexNDC( 0.30, 0.93, "This work : NN #rightarrow jet jet X" ) ;




      can -> SaveAs( "pf_x1x2.pdf" ) ;


   }









