
#include "histio.c"


   void make_nofilter_pthat_hist( const char* infile = "/home/owen/delphes/temp-second-version/delphes/test-1M-2022-10-23a/chunk-00.root" ) {

      gDirectory -> Delete( "h*" ) ;

      TChain ch("Delphes") ;

      ch.Add( infile ) ;

      TH1F* h_pthat_nofilter = new TH1F( "h_pthat_nofilter", "pthat, all, no filter", 80, 0., 8. ) ;

      ch.Draw( "Particle.PT[4] >> h_pthat_nofilter", "" ) ;

      saveHist( "hist_pthat_nofilter.root", "h*" ) ;

   }

