

   void draw_calo_eta_phi() {

      gStyle -> SetOptStat(0) ;

      TCanvas* can = new TCanvas( "can", "phi vs eta", 50, 50, 1200, 700 ) ;

      TH2F* hp = new TH2F( "hp", "",   500,    -6., 6.,  500, -3.14159265, 3.14159265   ) ;
      hp -> SetXTitle( "eta" ) ;
      hp -> SetYTitle( "phi" ) ;

      hp -> Draw() ;
      gPad -> SetGridx(1) ;
      gPad -> SetGridy(1) ;


      float inner_x = 0.25 ;
      float outer_x = 1.40 ;
      float top_y = 0.885 ;
      float front_z = 7.0 ;

      double x[1000], y[1000] ;

      int n_step(50) ;

      int np(0) ;

      x[0] = inner_x ;
      y[0] = 0. ;
      np ++ ;

      //   ^
      for ( int i=1; i<=n_step; i++ ) {
         x[np] = inner_x ;
         y[np] = ((1.*i)/(1.*n_step))*top_y ;
         np++ ;
      }

      //  >
      for ( int i=1; i<=n_step; i++ ) {
         y[np] = top_y ;
         x[np] = inner_x + (outer_x-inner_x)*((1.*i)/(1.*n_step)) ;
         np++ ;
      }

      //  \/
      for ( int i=1; i<=n_step; i++ ) {
         x[np] = outer_x ;
         y[np] = top_y - ((1.*i)/(1.*n_step))*2*top_y ;
         np++ ;
      }

      //  <
      for ( int i=1; i<=n_step; i++ ) {
         y[np] = -1 * top_y ;
         x[np] = outer_x - (outer_x-inner_x)*((1.*i)/(1.*n_step)) ;
         np++ ;
      }

      //  ^
      for ( int i=1; i<=n_step; i++ ) {
         x[np] = inner_x ;
         y[np] = -1*top_y + ((1.*i)/(1.*n_step))*top_y ;
         np++ ;
      }

      //TGraph* tg = new TGraph( np, x, y ) ;
      //tg -> SetLineWidth(3) ;
      //tg -> Draw("al") ;

      double eta[1000] ;
      double phi[1000] ;

      for ( int i=0; i<np; i++ ) {
         phi[i] = atan2( y[i], x[i] ) ;
         double rho = sqrt( x[i]*x[i] + y[i]*y[i] ) ;
         double theta = atan2( rho, front_z ) ;
         eta[i] = -1. * log( tan( theta/2. ) ) ;
      }

      TGraph* tg = new TGraph( np, eta, phi ) ;
      tg -> SetLineWidth(3) ;
      tg -> SetFillColor(30) ;

      tg -> Draw("same f") ;
      tg -> Draw("same") ;

    //--------------------------------------------------------------

      x[0] = -1. * inner_x ;
      y[0] = 0. ;
      np = 1 ;

      for ( int i=1; i<=n_step; i++ ) {
         x[np] = -1. * inner_x ;
         y[np] = ((1.*i)/(1.*n_step))*top_y ;
         np++ ;
      }

      for ( int i=1; i<=n_step; i++ ) {
         y[np] = top_y ;
         x[np] = -1. * inner_x - (outer_x-inner_x)*((1.*i)/(1.*n_step)) ;
         np++ ;
      }

      for ( int i=1; i<=n_step; i++ ) {
         x[np] = -1. * outer_x ;
         y[np] = top_y - ((1.*i)/(1.*n_step))*top_y ;
         np++ ;
      }




      for ( int i=0; i<np; i++ ) {
         phi[i] = atan2( y[i], x[i] ) ;
         double rho = sqrt( x[i]*x[i] + y[i]*y[i] ) ;
         double theta = atan2( rho, front_z ) ;
         eta[i] = -1. * log( tan( theta/2. ) ) ;
      }

      TGraph* tg2 = new TGraph( np, eta, phi ) ;
      tg2 -> SetLineWidth(3) ;
      tg2 -> SetFillColor(30) ;

      tg2 -> Draw("same f") ;
      tg2 -> Draw("same") ;



    //--------------------------------------------------------------

      x[0] = -1. * outer_x ;
      y[0] = -0.000000001 ;
      np = 1 ;

      for ( int i=1; i<=n_step; i++ ) {
         x[np] = -1. * outer_x ;
         y[np] = -0.0000001 - ((1.*i)/(1.*n_step))*top_y ;
         np++ ;
      }

      for ( int i=1; i<=n_step; i++ ) {
         y[np] = -1 * top_y ;
         x[np] = -1. * outer_x + (outer_x-inner_x)*((1.*i)/(1.*n_step)) ;
         np++ ;
      }

      for ( int i=1; i<=n_step; i++ ) {
         x[np] = -1. * inner_x ;
         y[np] = -1*top_y + ((1.*i)/(1.*n_step))*top_y - 0.0000000001 ;
         np++ ;
      }



      for ( int i=0; i<np; i++ ) {
         phi[i] = atan2( y[i], x[i] ) ;
         double rho = sqrt( x[i]*x[i] + y[i]*y[i] ) ;
         double theta = atan2( rho, front_z ) ;
         eta[i] = -1. * log( tan( theta/2. ) ) ;
         printf("  %4d :  x = %6.3f, y = %6.3f, eta = %6.3f, phi = %6.3f\n", i, x[i], y[i], eta[i], phi[i] ) ;
      }

      TGraph* tg3 = new TGraph( np, eta, phi ) ;
      tg3 -> SetLineWidth(3) ;
      tg3 -> SetFillColor(30) ;

      tg3 -> Draw("same f") ;
      tg3 -> Draw("same") ;

      hp -> Draw("axis same" ) ;
      hp -> Draw("axig same" ) ;


   }








