
#include "histio.c"
#include "utils.c"

   void pf_jet_qperp( const char* infile = "ca4-output/all.root" ) {


      //gStyle -> SetOptStat("mri") ;
      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadRightMargin(0.15) ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;


      TH2F* hp2d = get_hist2d( "h_r2j_qperp_gen_vs_rec" ) ;



      hp2d -> SetXTitle( "q_{#perp}  (GeV), from gen jets" ) ;
      hp2d -> SetYTitle( "q_{#perp}  (GeV), from reconstructed jets" ) ;

      hp2d -> SetTitleOffset( 1.4, "x" ) ;
      hp2d -> SetTitleOffset( 1.4, "y" ) ;



      TCanvas* can1 = get_canvas( "can1", "", 50, 50, 900, 900 ) ;
      can1 -> cd() ;
      can1 -> Clear() ;

      hp2d -> Draw("colz") ;


      can1 -> SaveAs( "plots/pf_qperp_rec_vs_gen.pdf" ) ;

    //---------------

//    TH1D* h_pz0 = h_pz1_vs_pz0 -> ProjectionX() ;
//    TH1D* h_pz1 = h_pz1_vs_pz0 -> ProjectionY() ;

//    h_pz0 -> SetLineWidth(3) ;
//    h_pz0 -> SetLineWidth(3) ;

//    h_pz0 -> SetXTitle( "Jet pz (GeV), higher pT jet" ) ;
//    h_pz0 -> SetYTitle( "Events" ) ;

//    h_pz0 -> SetTitleOffset( 1.4, "x" ) ;
//    h_pz0 -> SetTitleOffset( 1.6, "y" ) ;

//    TCanvas* can2 = get_canvas( "can2", "", 950, 50, 900, 900 ) ;
//    can2 -> cd() ;
//    can2 -> Clear() ;

//    h_pz0 -> Draw("hist") ;
//    h_pz0 -> Draw("same") ;

//    can1 -> SaveAs( "plots/pf_jet0pz.pdf" ) ;



   }









