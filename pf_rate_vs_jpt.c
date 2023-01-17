
#include "histio.c"
#include "utils.c"
#include "make_cumulative_hist.c"

   void pf_rate_vs_jpt( const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;
      gStyle -> SetOptTitle(0) ;
      gStyle -> SetOptStat(0) ;

      TCanvas* can = get_canvas( "can", "", 50, 50, 900, 900 ) ;
      can -> cd() ;
      can -> Clear() ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;

      TH2F* hp2d = get_hist2d( "h_jet1pt_vs_jet0pt_sel3_v2" ) ;

      ////////TH1D* h_jpt1 = hp2d -> ProjectionY() ;
      TH1D* h_jpt0 = hp2d -> ProjectionX() ;


      //h_jpt1 -> Draw() ;
      //gPad -> SetLogy(1) ;

      TH1F* h_cumulative = make_cumulative_hist( (TH1F*) h_jpt0 ) ;

      h_cumulative->SetLineWidth(3) ;

      h_cumulative -> GetXaxis() -> SetRangeUser( 3.7, 10 ) ;

      h_cumulative-> SetXTitle( "Minimum leading jet pT (GeV)" ) ;
      h_cumulative-> SetYTitle( "Number of p+A events in 1.3 1/pb" ) ;

      h_cumulative-> SetTitleOffset( 1.4, "y" ) ;
      h_cumulative-> SetTitleOffset( 1.4, "x" ) ;

      h_cumulative -> Draw( "hist l" ) ;
      h_cumulative -> Draw( "same" ) ;
      gPad -> SetLogy(1) ;
      gPad -> SetGridx(1) ;
      gPad -> SetGridy(1) ;




      can -> SaveAs( "plots/pf_rate_vs_jpt.pdf" ) ;


   }









