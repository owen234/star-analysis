
#include "histio.c"
#include "utils.c"

   void pf_qoverp( const char* infile = "ca4-output/all.root" ) {


      //gStyle -> SetOptStat("mri") ;
      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.17) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;


      TH2F* hp2d = get_hist2d( "h_r2j_qperp_over_Pperp_rec_vs_gen" ) ;

      hp2d -> SetXTitle( "q_{#perp}   /P_{#perp}   , gen jets" ) ;
      hp2d -> SetYTitle( "q_{#perp}   /P_{#perp}   , reconstructed jets" ) ;

      hp2d -> SetTitleOffset( 1.2, "x" ) ;
      hp2d -> SetTitleOffset( 1.4, "y" ) ;

      hp2d -> SetTitleSize( 0.055, "x" ) ;
      hp2d -> SetTitleSize( 0.055, "y" ) ;
      hp2d -> SetLabelSize( 0.050, "x" ) ;
      hp2d -> SetLabelSize( 0.050, "y" ) ;




      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      hp2d -> Draw("colz") ;


      can1 -> SaveAs( "plots/pf_qperp_over_pperp_rec_vs_gen.pdf" ) ;

    //---------------

      TH1D* hp = hp2d -> ProjectionY() ;

      hp -> SetLineWidth(3) ;
      hp -> SetLineWidth(3) ;


      hp -> SetXTitle( "q_{#perp}   /P_{#perp}   , reconstructed jets" ) ;
      hp -> SetYTitle( "Events" ) ;

      hp -> SetTitleSize( 0.055, "x" ) ;
      hp -> SetTitleSize( 0.055, "y" ) ;
      hp -> SetTitleOffset( 1.2, "x" ) ;
      hp -> SetTitleOffset( 1.3, "y" ) ;

      TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
      can2 -> cd() ;
      can2 -> Clear() ;

      hp -> Draw("hist") ;
      hp -> Draw("same") ;

      can2 -> SaveAs( "plots/pf_qoverp_rec.pdf" ) ;



   }









