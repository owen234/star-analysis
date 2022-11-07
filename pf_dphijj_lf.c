
#include "histio.c"
#include "utils.c"

   void pf_dphijj_lf( const char* infile = "ca4-output/all.root" ) {


      //gStyle -> SetOptStat("mri") ;
      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;


      TH2F* hp2d = get_hist2d( "h_dphijj_rec_vs_gen" ) ;

      hp2d -> SetXTitle( "dphi(jj), gen jets" ) ;
      hp2d -> SetYTitle( "dphi(jj), reconstructed jets" ) ;

      hp2d -> SetTitleOffset( 1.4, "x" ) ;
      hp2d -> SetTitleOffset( 1.4, "y" ) ;



      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      hp2d -> Draw("colz") ;


      can1 -> SaveAs( "plots/pf_dphijj_rec_vs_gen.pdf" ) ;

    //---------------

      gStyle -> SetPadRightMargin(0.02) ;
      gStyle -> SetPadBottomMargin(0.18) ;
      gStyle -> SetPadLeftMargin(0.20) ;

      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      TH1D* hp = hp2d -> ProjectionY() ;

      hp -> SetLineWidth(3) ;
      hp -> SetLineWidth(3) ;

      hp -> SetLabelSize( 0.065, "x" ) ;
      hp -> SetLabelSize( 0.065, "y" ) ;
      hp -> SetTitleSize( 0.065, "x" ) ;
      hp -> SetTitleSize( 0.065, "y" ) ;


      hp -> SetXTitle( "dphi(jj), reconstructed jets" ) ;
      hp -> SetYTitle( "Events" ) ;

      hp -> SetTitleOffset( 1.4, "x" ) ;
      hp -> SetTitleOffset( 1.6, "y" ) ;

      hp -> Draw("hist") ;
      hp -> Draw("same") ;

      can2 -> SaveAs( "plots/pf_dphijj_rec.pdf" ) ;



   }









