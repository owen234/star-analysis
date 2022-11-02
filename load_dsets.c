
#include "histio.c"

   void load_dsets() {

      loadHist( "ca4-output/dset-pthat-1.0to1.8.root", "ds1" ) ;
      loadHist( "ca4-output/dset-pthat-1.8-cut-to-1.8to3.0.root", "ds2" ) ;
      loadHist( "ca4-output/dset-pthat-3.0to5.0.root", "ds3" ) ;
      loadHist( "ca4-output/dset-pthat-5.0.root", "ds4" ) ;
      loadHist( "ca4-output/all.root", "all" ) ;


   }
