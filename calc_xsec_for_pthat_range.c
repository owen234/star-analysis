


   void calc_xsec_for_pthat_range( float pthatmin = 1.8, float pthatmax = -1. ) {

      float no_filter_xsec = 113.7 ; // mb

      TChain* ch_nofilter = new TChain("Delphes") ;

      ch_nofilter -> Add( "/home/owen/delphes/temp-second-version/delphes/test-1M-2022-10-23a/chunk-00.root") ;
      int n_nofilter = ch_nofilter -> GetEntries() ;
      printf("\n\n Number of events in no-filter chain:  %d\n\n", n_nofilter ) ;

      int nbins = 150 ;
      float pthmin = 0. ;
      float pthmax = 15. ;


      TH1F* h_nofilter = new TH1F( "h_nofilter", "pthat, no filter", nbins, pthmin, pthmax ) ;
      h_nofilter -> Sumw2() ;
      TH1F* h_window = new TH1F( "h_window", "pthat, window", nbins, pthmin, pthmax ) ;
      h_window -> Sumw2() ;

      ch_nofilter -> Draw( "Particle.PT[4] >> h_nofilter" ) ;
      char cuts[1000];
      if ( pthatmax > 0 ) {
         sprintf( cuts, "Particle.PT[4] >= %.2f && Particle.PT[4] <= %.2f", pthatmin, pthatmax ) ;
      }  else {
         sprintf( cuts, "Particle.PT[4] >= %.2f", pthatmin ) ;
      }
      ch_nofilter -> Draw( "Particle.PT[4] >> h_nofilter" ) ;
      ch_nofilter -> Draw( "Particle.PT[4] >> h_window", cuts ) ;

      h_nofilter -> SetLineWidth(2) ;
      h_nofilter -> SetLineColor(4) ;

      h_window -> SetLineWidth(2) ;
      h_window -> SetFillColor(30) ;

      TCanvas* can = new TCanvas( "can", "", 50, 50, 800, 700 ) ;

      h_nofilter -> Draw() ;
      h_window -> Draw("hist same") ;
      h_window -> Draw("same") ;
      h_window -> Draw("axis same") ;
      gPad -> SetLogy(1) ;


      float n0 = h_nofilter -> Integral() ;
      float nwindow = h_window -> Integral() ;

      float xsec_window = no_filter_xsec * (nwindow/n0) ;

      printf("\n\n   n0 = %.0f    nwindow = %.0f   xsec_window = %.3f mb \n\n", n0, nwindow, xsec_window ) ;



   }


