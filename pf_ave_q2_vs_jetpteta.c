
#include "histio.c"
#include "utils.c"

   void pf_ave_q2_vs_jetpteta( const char* infile = "ca4-output/all.root" ) {

      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.10) ;
      gStyle -> SetPadLeftMargin(0.15) ;

      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      TCanvas* can = get_canvas( "can", "", 50, 50, 900, 600 ) ;
      can -> cd() ;
      can -> Clear() ;

      gDirectory -> Delete( "h*" ) ;

      loadHist( infile ) ;

      TH2F* hp2d_vsj1pt = get_hist2d( "h_q2_vs_jet1pt_pm" ) ;
      TH2F* hp2d_vsj1eta = get_hist2d( "h_q2_vs_jet1eta_pm" ) ;

      TH1D* hp_aveq2vspt = hp2d_vsj1pt -> ProfileX() ;
      TH1D* hp_aveq2vseta = hp2d_vsj1eta -> ProfileX() ;

      hp_aveq2vspt->SetLineWidth(3) ;
      hp_aveq2vseta->SetLineWidth(3) ;

      hp_aveq2vspt->SetXTitle( "higher pT jet pT (GeV)" ) ;
      hp_aveq2vspt->SetYTitle( "Average Q^{2} (GeV^{2})" ) ;
      hp_aveq2vspt->SetTitleSize( 0.055, "x") ;
      hp_aveq2vspt->SetTitleSize( 0.065, "y") ;

      hp_aveq2vseta->SetXTitle( "higher pT jet eta" ) ;
      hp_aveq2vseta->SetYTitle( "Average Q^{2} (GeV^{2})" ) ;
      hp_aveq2vseta->SetTitleSize( 0.055, "x") ;
      hp_aveq2vseta->SetTitleSize( 0.065, "y") ;


      can -> Divide(2,1) ;

      can -> cd(1) ;
      hp_aveq2vspt -> Draw() ;

      can -> cd(2) ;
      hp_aveq2vseta -> Draw() ;




      can -> SaveAs( "pf_ave_q2_vs_jetpteta.pdf" ) ;


   }









