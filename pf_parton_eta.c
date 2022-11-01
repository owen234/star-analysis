
#include "histio.c"
#include "utils.c"

   void pf_parton_eta( int sel = 0, const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;

      char hname[1000] ;
      sprintf( hname, "h_genparton_etab_vs_etaa_sel%d", sel ) ;
      TH2F* hp2d = get_hist2d( hname ) ;

      hp2d -> SetXTitle( "eta, Final State parton A" ) ;
      hp2d -> SetYTitle( "eta, Final State parton B" ) ;





      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      hp2d -> Draw("colz") ;


      char fname[1000] ;

      sprintf( fname, "pf_parton_eta_sel%d.pdf", sel ) ;
      can1 -> SaveAs( fname ) ;

    //---------------


      TH1D* hp1da = hp2d -> ProjectionX() ;
      TH1D* hp1db = hp2d -> ProjectionY() ;

      hp1da -> SetLineWidth(3) ;
      hp1db -> SetLineWidth(3) ;

      hp1da -> SetLineColor(4) ;
      hp1db -> SetLineColor(2) ;

      hp1da -> SetXTitle( "eta, Final State parton" ) ;

      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      hp1da -> Draw("hist") ;
      hp1db -> Draw("hist same") ;








//    hp2d -> SetTitleOffset(1.2,"x") ;
//    hp2d -> SetTitleOffset(1.4,"y") ;

//    hp2dlin -> Draw("colz") ;
//    gPad->SetLogx(1) ;
//    gPad->SetLogy(1) ;

//    TLatex* tl = new TLatex() ;
//    tl -> SetTextSize( 0.05 ) ;
//    tl -> SetTextFont( 42 ) ;
//    char label[1000] ;

//    tl -> SetTextColor(1) ;
//    tl -> SetTextAlign( 22 ) ;
//    tl -> DrawLatexNDC( 0.50, 0.93, "This work : NN #rightarrow jet jet X" ) ;







   }









