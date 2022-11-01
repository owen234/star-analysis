
#include "histio.c"
#include "utils.c"

   void pf_jet_pt( int sel = 0, const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;

      char hname[1000] ;
      sprintf( hname, "h_jet1pt_vs_jet0pt_sel%d", sel ) ;
      TH2F* hp2d = get_hist2d( hname ) ;

      hp2d -> SetXTitle( "Jet pT (GeV), higher pT jet" ) ;
      hp2d -> SetYTitle( "Jet pT (GeV), lower pT jet" ) ;


      hp2d -> GetXaxis() -> SetRangeUser( 2.2, 8. ) ;
      hp2d -> GetYaxis() -> SetRangeUser( 2.2, 8. ) ;



      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      hp2d -> Draw("colz") ;
      gPad->SetLogz(1) ;


      char fname[1000] ;

      sprintf( fname, "pf_jet1pt_vs_jet0pt_sel%d_2d.pdf", sel ) ;
      can1 -> SaveAs( fname ) ;

    //---------------


      TH1D* hp1da = hp2d -> ProjectionX() ;
      TH1D* hp1db = hp2d -> ProjectionY() ;

      hp1da -> SetLineWidth(3) ;
      hp1db -> SetLineWidth(3) ;

      hp1da -> SetLineColor(4) ;
      hp1db -> SetLineColor(2) ;

      hp1da -> SetXTitle( "Jet pT (GeV)" ) ;

      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      hp1db -> Draw("hist") ;
      hp1da -> Draw("hist same") ;
      gPad -> SetLogy(1) ;

      sprintf( fname, "pf_jet1pt_vs_jet0pt_sel%d_1d.pdf", sel ) ;
      can1 -> SaveAs( fname ) ;



   }









