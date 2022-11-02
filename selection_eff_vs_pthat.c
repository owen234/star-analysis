


   void selection_eff_vs_pthat() {

      TChain* ch_nofilter = new TChain("Delphes") ;
      TChain* ch_filter = new TChain("Delphes") ;

      ch_nofilter -> Add( "/home/owen/delphes/temp-second-version/delphes/test-1M-2022-10-23a/chunk-00.root") ;
      int n_nofilter = ch_nofilter -> GetEntries() ;
      printf("\n\n Number of events in no-filter chain:  %d\n\n", n_nofilter ) ;

      ch_filter -> Add( "/home/owen/delphes/delphes/output-rjf-2jR-pthat0.0-jpt3-30x50M-2022-10-23a/*.root" ) ;
      int n_filter = ch_filter -> GetEntries() ;
      printf("\n\n Number of events in filter chain:  %d\n\n", n_filter ) ;

      int n_gen_filter = 27 * 50000000 ;

      int nbins = 24 ;
      float pthmin = 0. ;
      float pthmax = 8. ;

    //int nbins = 36 ;
    //float pthmin = 0. ;
    //float pthmax = 12. ;

      TH1F* h_nofilter = new TH1F( "h_nofilter", "pthat, no filter", nbins, pthmin, pthmax ) ;
      TH1F* h_filter = new TH1F( "h_filter", "pthat, filter", nbins, pthmin, pthmax ) ;
      h_nofilter -> Sumw2() ;
      h_filter -> Sumw2() ;

      ch_nofilter -> Draw( "Particle.PT[4] >> h_nofilter" ) ;

      ch_filter -> Draw( "Particle.PT[4] >> h_filter" ) ;

      h_nofilter -> SetLineWidth(2) ;
      h_nofilter -> SetLineColor(4) ;
      h_filter -> SetLineWidth(2) ;
      h_filter -> SetLineColor(2) ;

      TCanvas* can = new TCanvas( "can", "", 50, 50, 800, 1200 ) ;
      can -> Divide( 1, 2 ) ;


      h_nofilter -> Scale( (1.*n_gen_filter)/(1.*n_nofilter) ) ;

      h_nofilter -> SetMinimum(1.) ;

      can -> cd(1) ;
      h_nofilter -> Draw() ;
      h_filter -> Draw("same") ;
      gPad -> SetLogy(1) ;


      can -> cd(2) ;
      TH1F* h_sel_eff = (TH1F*) h_filter -> Clone( "h_sel_eff" ) ;
      h_sel_eff -> SetTitle("Selection efficiency" ) ;
      h_sel_eff -> Divide( h_nofilter ) ;
      h_sel_eff -> Draw() ;




   }


