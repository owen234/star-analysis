
#include "histio.c"
#include "utils.c"


   void pf_pthat( const char* indir = "ca4-output" ) {

      gStyle -> SetPadLeftMargin(0.15) ;
      gStyle -> SetPadBottomMargin(0.15) ;
      gStyle -> SetPadTopMargin(0.05) ;

      TCanvas* can = get_canvas( "can", "", 50, 50, 700, 1100 ) ;
      can -> Clear() ;
      can -> cd() ;

      gStyle -> SetOptStat(0) ;
      gStyle -> SetOptTitle(0) ;

      gDirectory -> Delete( "h*" ) ;

      char infile[1000] ;

      sprintf( infile, "%s/all.root", indir ) ;
      printf("\n Loading %s\n", infile ) ;
      loadHist( infile ,"all", "h*" ) ;

      sprintf( infile, "%s/dset-pthat-1.0to1.8.root", indir ) ;
      printf("\n Loading %s\n", infile ) ;
      loadHist( infile ,"ds1", "h*" ) ;

      sprintf( infile, "%s/dset-pthat-1.8-cut-to-1.8to3.0.root", indir ) ;
      printf("\n Loading %s\n", infile ) ;
      loadHist( infile ,"ds2", "h*" ) ;

      sprintf( infile, "%s/dset-pthat-3.0to5.0.root", indir ) ;
      printf("\n Loading %s\n", infile ) ;
      loadHist( infile ,"ds3", "h*" ) ;

      sprintf( infile, "%s/dset-pthat-5.0.root", indir ) ;
      printf("\n Loading %s\n", infile ) ;
      loadHist( infile ,"ds4", "h*" ) ;

      loadHist( "hist_pthat_nofilter.root" ) ;

      gDirectory -> ls( "h_pthat_all*" ) ;

      TH1F* h_all = get_hist( "h_pthat_all_all" ) ;
      TH1F* h_pm = get_hist( "h_pthat_pm_all" ) ;
      TH1F* h_ds1 = get_hist( "h_pthat_all_ds1" ) ;
      TH1F* h_ds2 = get_hist( "h_pthat_all_ds2" ) ;
      TH1F* h_ds3 = get_hist( "h_pthat_all_ds3" ) ;
      TH1F* h_ds4 = get_hist( "h_pthat_all_ds4" ) ;
      TH1F* h_nofilter = get_hist( "h_pthat_nofilter" ) ;

      h_nofilter -> Scale( (113.7e9/1.e7) * 1.3 * 197 ) ;
      h_nofilter -> SetMinimum(1.) ;

      h_nofilter -> SetLineWidth(2) ;

      h_nofilter -> SetXTitle( "PYTHIA pTHat" ) ;
      h_nofilter -> SetYTitle( "p+A events in 1.3 1/pb" ) ;
      h_nofilter -> SetTitleOffset( 1.6, "y" ) ;

      h_ds1->SetFillColor(30) ;
      h_ds2->SetFillColor(31) ;
      h_ds3->SetFillColor(32) ;
      h_ds4->SetFillColor(33) ;

      h_nofilter -> Draw( ) ;
      h_nofilter -> Draw("same hist" ) ;
      //h_all -> Draw() ;
      h_ds1 -> Draw("same hist") ;
      h_ds2 -> Draw("same hist") ;
      h_ds3 -> Draw("same hist") ;
      h_ds4 -> Draw("same hist") ;
      h_all -> Draw("same") ;
      h_all -> Draw("axis same") ;

      h_pm -> SetLineWidth(3) ;
      h_pm -> SetLineColor(4) ;

      h_pm -> Draw("same") ;


      gPad -> SetLogy(1) ;


   }




