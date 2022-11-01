#ifndef utils_c
#define utils_c





//==========================================================================================

TH1F* convert_log10_to_linear_1d( TH1* hp_in ) {

   if ( hp_in == 0x0 ) {
      printf("\n\n *** null pointer!\n\n" ) ;
      return 0x0 ;
   }

   int nbins = hp_in -> GetNbinsX() ;

   double new_bins[1000] ;

   printf("\n\n Number of bins: %d\n", nbins ) ;
   for ( int bi=1; bi<=(nbins+1); bi++ ) {
      double bin_edge = hp_in -> GetBinLowEdge(bi) ;
      double new_edge = pow( 10., bin_edge ) ;
      int ai=bi-1;
      new_bins[ai] = new_edge ;
      printf("  bin %3d : %8.3f  %9.5f\n", bi, bin_edge, new_edge  ) ;
   }

   char hname[1000] ;
   char htitle[1000] ;
   sprintf( hname, "%s_linx", hp_in->GetName() ) ;
   sprintf( htitle, "%s", hp_in->GetTitle() ) ;

   TH1F* hp_out = new TH1F( hname, htitle, nbins, new_bins ) ;
   for ( int bi=1; bi<=nbins; bi++ ) {
      hp_out -> SetBinContent( bi, hp_in -> GetBinContent(bi) ) ;
      hp_out -> SetBinError( bi, hp_in -> GetBinError(bi) ) ;
   }

   return hp_out ;


}


//==========================================================================================

TH2F* convert_log10_to_linear_2d( TH2* hp_in ) {

   if ( hp_in == 0x0 ) {
      printf("\n\n *** null pointer!\n\n" ) ;
      return 0x0 ;
   }

   int nbinsx = hp_in -> GetNbinsX() ;
   int nbinsy = hp_in -> GetNbinsY() ;

   printf("\n\n Number of bins: x %d,  y%d\n", nbinsx, nbinsy ) ;

   double new_binsx[1000] ;
   double new_binsy[1000] ;

   for ( int bi=1; bi<=(nbinsx+1); bi++ ) {
      double bin_edge = hp_in -> GetXaxis() -> GetBinLowEdge(bi) ;
      double new_edge = pow( 10., bin_edge ) ;
      int ai=bi-1;
      new_binsx[ai] = new_edge ;
      printf(" x bin %3d : %8.3f  %9.5f\n", bi, bin_edge, new_edge  ) ;
   }

   for ( int bi=1; bi<=(nbinsy+1); bi++ ) {
      double bin_edge = hp_in -> GetYaxis() -> GetBinLowEdge(bi) ;
      double new_edge = pow( 10., bin_edge ) ;
      int ai=bi-1;
      new_binsy[ai] = new_edge ;
      printf(" y bin %3d : %8.3f  %9.5f\n", bi, bin_edge, new_edge  ) ;
   }

   char hname[1000] ;
   char htitle[1000] ;
   sprintf( hname, "%s_linxy", hp_in->GetName() ) ;
   sprintf( htitle, "%s", hp_in->GetTitle() ) ;

   TH2F* hp_out = new TH2F( hname, htitle, nbinsx, new_binsx, nbinsy, new_binsy ) ;
   for ( int xbi=1; xbi<=nbinsx; xbi++ ) {
      for ( int ybi=1; ybi<=nbinsy; ybi++ ) {
         hp_out -> SetBinContent( xbi, ybi, hp_in -> GetBinContent(xbi,ybi) ) ;
         hp_out -> SetBinError( xbi, ybi, hp_in -> GetBinError(xbi,ybi) ) ;
      } // ybi
   } // xbi

   return hp_out ;


}


//==========================================================================================







   TCanvas* get_canvas( const char* cname, const char* ctitle = "",
                        int px = 50, int py = 50,
                        int w = 900, int h = 900 ) {
       TCanvas* rp = (TCanvas*) gDirectory -> FindObject( cname ) ;
       if ( rp != 0 ) return rp ;
       return new TCanvas( cname, ctitle, px, py, w, h ) ;
   }

   TH1F* get_hist( const char* hname ) {
      TH1F* rp = (TH1F*) gDirectory -> FindObject( hname ) ;
      if ( rp == 0x0 ) { printf("\n\n *** Missing hist %s\n\n", hname ) ; gSystem -> Exit(-1) ; }
      return rp ;
   }

   TH2F* get_hist2d( const char* hname ) {
      TH2F* rp = (TH2F*) gDirectory -> FindObject( hname ) ;
      if ( rp == 0x0 ) { printf("\n\n *** Missing hist %s\n\n", hname ) ; gSystem -> Exit(-1) ; }
      return rp ;
   }

   TH1F* fget_hist( const char* hname, TFile* tfp ) {
      if ( tfp == 0x0 ) { printf("\n\n *** fget_hist : bad file pointer.\n\n") ; gSystem -> Exit(-1) ; }
      TH1F* rp = (TH1F*) tfp -> Get( hname ) ;
      if ( rp == 0x0 ) { printf("\n\n *** Missing hist %s\n\n", hname ) ; gSystem -> Exit(-1) ; }
      return rp ;
   }

   TH2F* fget_hist2d( const char* hname, TFile* tfp ) {
      if ( tfp == 0x0 ) { printf("\n\n *** fget_hist : bad file pointer.\n\n") ; gSystem -> Exit(-1) ; }
      TH2F* rp = (TH2F*) tfp -> Get( hname ) ;
      if ( rp == 0x0 ) { printf("\n\n *** Missing hist %s\n\n", hname ) ; gSystem -> Exit(-1) ; }
      return rp ;
   }

   TH2Poly* fget_hist2dp( const char* hname, TFile* tfp ) {
      if ( tfp == 0x0 ) { printf("\n\n *** fget_hist : bad file pointer.\n\n") ; gSystem -> Exit(-1) ; }
      TH2Poly* rp = (TH2Poly*) tfp -> Get( hname ) ;
      if ( rp == 0x0 ) { printf("\n\n *** Missing hist %s\n\n", hname ) ; gSystem -> Exit(-1) ; }
      return rp ;
   }

   TGraph* get_graph( const char* gname ) {
      TGraph* rp = (TGraph*) gDirectory -> FindObject( gname ) ;
      if ( rp == 0x0 ) { printf("\n\n *** Missing TGraph %s\n\n", gname ) ; gSystem -> Exit(-1) ; }
      return rp ;
   }

   void grid_on() {
      gPad -> SetGridx(1) ;
      gPad -> SetGridy(1) ;
   }

   void logxy_on() {
      gPad -> SetLogx(1) ;
      gPad -> SetLogy(1) ;
   }

   void stats_off() {
      gStyle -> SetOptStat(0) ;
   }

   void set_tf( const char* tf="5.3f" ) {
      gStyle -> SetPaintTextFormat( tf ) ;
   }




#endif
