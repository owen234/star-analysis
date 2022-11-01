

   TH1F* make_cumulative_hist( TH1F* hp ) {

       char hname[1000] ;
       sprintf( hname, "%s_cumulative", hp -> GetName() ) ;

       TH1F* rp = (TH1F*) hp -> Clone( hname ) ;

       char htitle[1000] ;
       sprintf( htitle, "%s, cumulative dist.", hp -> GetTitle() ) ;

       int nbins = hp -> GetNbinsX() ;

       for ( int bi=1; bi<nbins; bi++ ) {
          double val ;
          double err ;
          val = hp -> IntegralAndError( bi, nbins+1, err ) ;
          rp -> SetBinContent( bi, val ) ;
          rp -> SetBinError( bi, err ) ;
       }

       return rp ;

   }


