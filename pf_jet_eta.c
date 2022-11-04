
#include "histio.c"
#include "utils.c"

   void pf_jet_eta( int sel = 1, const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetOptStat("mr") ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;

      gStyle -> SetStatX(0.83) ;
      gStyle -> SetStatY(0.85) ;
      gStyle -> SetStatW(0.30) ;
      gStyle -> SetStatH(0.20) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;

      char hname[1000] ;
      sprintf( hname, "h_jet1eta_vs_jet0eta_sel%d", sel ) ;
      TH2F* hp2d = get_hist2d( hname ) ;

      hp2d -> SetXTitle( "Jet eta, higher pT jet" ) ;
      hp2d -> SetYTitle( "Jet eta, lower pT jet" ) ;

      hp2d -> SetTitleOffset( 1.5, "y" ) ;
      hp2d -> SetTitleOffset( 1.5, "x" ) ;


      hp2d -> GetXaxis() -> SetRangeUser( 2.2, 8. ) ;
      hp2d -> GetYaxis() -> SetRangeUser( 2.2, 8. ) ;



      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      hp2d -> SetStats(0) ;

      hp2d -> Draw("colz") ;
      //gPad->SetLogz(1) ;


      char fname[1000] ;

      sprintf( fname, "plots/pf_jet1eta_vs_jet0eta_sel%d_2d.pdf", sel ) ;
      can1 -> SaveAs( fname ) ;

    //---------------


      TH1D* hp1da = hp2d -> ProjectionX() ;
      TH1D* hp1db = hp2d -> ProjectionY() ;

      hp1da -> SetLineWidth(3) ;
      hp1db -> SetLineWidth(3) ;

      hp1da -> SetLineColor(4) ;
      hp1db -> SetLineColor(2) ;

      hp1da -> SetXTitle( "Jet eta" ) ;
      hp1da -> SetYTitle( "Events" ) ;

      hp1db -> SetTitleOffset( 1.5, "y" ) ;
      hp1db -> SetTitleOffset( 1.5, "x" ) ;

      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      hp1db -> Draw() ;
      gPad->Update() ;


      hp1da -> Draw("hist") ;
      gPad->Update() ;
      hp1db -> Draw("hist same") ;
      hp1da -> Draw("same") ;
      hp1db -> Draw("same") ;

      TPaveStats* tpsa = (TPaveStats*) hp1da -> GetListOfFunctions()->FindObject("stats") ;
      if ( tpsa != 0x0 ) {
         tpsa -> SetLineColor(4) ;
         tpsa -> SetTextColor(4) ;
         tpsa -> SetY1NDC(0.78) ;
         tpsa -> SetY2NDC(0.88) ;
      } else {
         printf("No stats???\n") ;
      }

      TPaveStats* tpsb = (TPaveStats*) hp1db -> GetListOfFunctions()->FindObject("stats") ;
      if ( tpsb != 0x0 ) {
         tpsb -> SetLineColor(2) ;
         tpsb -> SetTextColor(2) ;
         tpsb -> SetY1NDC(0.65) ;
         tpsb -> SetY2NDC(0.75) ;
      } else {
         printf("No stats???\n") ;
      }

      sprintf( fname, "plots/pf_jet_eta_sel%d_1d.pdf", sel ) ;
      can2 -> SaveAs( fname ) ;



   }









