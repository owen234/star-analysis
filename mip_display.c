#define mip_display_cxx
#include "mip_display.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "histio.c"
#include "utils.c"

//---------------
void ecal_id_to_row_col( int id, int& row, int& col ) {
   row = id/22+1 ;
   col = id%22+1 ;
}
//---------------
vector<int> all_used_hits ;

   TPolyMarker* tpm_fcsc = new TPolyMarker() ;
   TPolyMarker* tpm_fcs_mc_ecal = new TPolyMarker() ;
   TPolyMarker* tpm_fcs_mc_hcal = new TPolyMarker() ;
   TPolyMarker* tpm_tp = new TPolyMarker() ;
   TPolyMarker* tpm_cl = new TPolyMarker() ;
   TPolyMarker* tpm_cl_ecal = new TPolyMarker() ;
   TPolyMarker* tpm_cl_hcal = new TPolyMarker() ;
   TBox* tb_ecal = new TBox() ;
   TBox* tb_ecal_line = new TBox() ;
   TBox* tb_ecal_line_red = new TBox() ;
   TBox* tb_ecal_line2 = new TBox() ;
   TBox* tb_hcal = new TBox() ;
   TBox* tb_hcal_line = new TBox() ;
   TArrow* ta_trk = new TArrow() ;
   TArrow* ta_cl = new TArrow() ;
   TEllipse* te_circle = new TEllipse() ;
   TCanvas* can_xy(0x0) ;
   TCanvas* can_xy_cluster(0x0) ;
   TH2F* h_display_xy(0x0) ;
   TH2F* h_display_xy_cluster(0x0) ;

//-----------------------------------------------------------------------------------------------------------

      void mip_display::draw_ecal_hits() {

         can_xy -> cd() ;
         h_display_xy -> Draw() ;

         double x[1] ;
         double y[1] ;

         for ( int i=0; i<fcs_rec_ecalE->size(); i++ ) {

            float energy = fcs_rec_ecalE->at(i) ;
            if ( energy < 0.0001 ) continue ;

            float x, y ;
            x = fcs_rec_ecalX->at(i) ;
            y = fcs_rec_ecalY->at(i) ;

            int id = fcs_rec_ecalId -> at(i) ;
            int row, col ;
            ecal_id_to_row_col( id, row, col ) ;
            int ns = fcs_rec_ecalDet->at(i) % 2 ;



            float alpha = energy  ;
            if ( alpha > 1 ) alpha = 1 ;
            if ( alpha < 0 ) alpha = 0 ;
            tb_ecal -> SetFillColorAlpha( kBlue, alpha ) ;
            tb_ecal -> DrawBox( x - 5.572/2.,  y - 5.572/2.,  x + 5.572/2, y + 5.572/2 ) ;
            tb_ecal_line -> DrawBox( x - 5.572/2.,  y - 5.572/2.,  x + 5.572/2, y + 5.572/2 ) ;
            //////printf( "  ECAL hit %3d,  id=%4d, row = %2d, col = %2d, ns = %d,  x = %7.2f  , y = %7.2f  ,  E = %7.3f\n",
            //////    i, id, row, col, ns, x, y, energy ) ;
         }

         for ( int ti=0; ti<rcN; ti++ ) {
            float tpx = rcProjEcalx->at(ti) ;
            float tpy = rcProjEcaly->at(ti) ;
            double x[10] ;
            double y[10] ;
            x[0] = tpx  ;
            y[0] = tpy  ;
            tpm_tp -> DrawPolyMarker( 1, x, y ) ;
         }
      } // draw_ecal_hits

//-----------------------------------------------------------------------------------------------------------
int mip_display::match_track( float x, float y, float radius ) {

   int trkind(-1) ;

   int nmatch(0) ;

   for ( int ti=0; ti<rcN; ti++ ) {

      float tpx = rcProjEcalx->at(ti) ;
      float tpy = rcProjEcaly->at(ti) ;
      float dx = x - tpx ;
      float dy = y - tpy ;
      float dr = sqrt( dx*dx + dy*dy ) ;

      if ( dr < radius ) {
         nmatch ++ ;
         trkind = ti ;
      }

   } // ti

   if ( nmatch > 1 ) trkind = -2 ;

   return trkind ;

} // match_track

//-----------------------------------------------------------------------------------------------------------

void mip_display::check_neighbors( int hit_index, vector<int>& all_neighbors ) {

   if ( all_neighbors.size() == 0 ) all_neighbors.push_back( hit_index ) ; // add the hit itself if necessary.

   int hit_id = fcs_rec_ecalId->at(hit_index) ;
   int hit_row = hit_id/22 + 1 ; // correlated with Y
   int hit_col = hit_id%22 + 1 ; // correlated with X
   int hit_det = fcs_rec_ecalDet->at(hit_index) ;

   for ( int hi=0; hi<fcs_rec_ecalE->size(); hi++ ) {

      if ( hi == hit_index ) continue ; // skip hit itself

      if ( std::find( all_neighbors.begin(), all_neighbors.end(), hi ) != all_neighbors.end() ) continue ; // already in neighbor list.

      int det = fcs_rec_ecalDet->at(hi) ;
      if ( det != hit_det ) continue ; // not in same side of FCS.



      float energy = fcs_rec_ecalE->at(hi) ;

      if ( energy < 0.001 ) continue ;

      int id = fcs_rec_ecalId->at(hi) ;
      int row = id/22 + 1 ; // correlated with Y
      int col = id%22 + 1 ; // correlated with X

      if ( abs( hit_row - row ) <=1   && abs( hit_col - col ) <= 1 ) {
         if ( verbose ) printf("  ECAL hit %3d (%3d,%3d) neighbors hit %3d (%3d,%3d)\n", hit_index, hit_row, hit_col, hi, row, col ) ;
         all_neighbors.push_back( hi ) ;
         check_neighbors( hi, all_neighbors ) ;
      }


   } // hi

} // check_neighbors

//-----------------------------------------------------------------------------------------------------------

void mip_display::check_neighbors_hcal( int hit_index, vector<int>& all_neighbors ) {

   if ( hit_index < 0 ) return ;

   if ( all_neighbors.size() == 0 ) all_neighbors.push_back( hit_index ) ; // add the hit itself if necessary.

   if ( all_neighbors.size() >= 9 ) return ; // cut off the size of the cluster.

   int hit_id = fcs_rec_hcalId->at(hit_index) ;
   int hit_row = hit_id/13 + 1 ; // correlated with Y
   int hit_col = hit_id%13 + 1 ; // correlated with X
   int hit_det = fcs_rec_hcalDet->at(hit_index) ;

   for ( int hi=0; hi<fcs_rec_hcalE->size(); hi++ ) {

      if ( hi == hit_index ) continue ; // skip hit itself

      if ( std::find( all_neighbors.begin(), all_neighbors.end(), hi ) != all_neighbors.end() ) continue ; // already in neighbor list.

      int det = fcs_rec_hcalDet->at(hi) ;
      if ( det != hit_det ) continue ; // not in same side of FCS.



      float energy = fcs_rec_hcalE->at(hi) ;

      if ( energy < 0.01 ) continue ;

      int id = fcs_rec_hcalId->at(hi) ;
      int row = id/13 + 1 ; // correlated with Y
      int col = id%13 + 1 ; // correlated with X

    //--- see if they share a side (no corner connections).
      if (  ( abs( hit_row - row ) == 1 && (hit_col == col) ) ||
            ( abs( hit_col - col ) == 1 && (hit_row == row) )      )  {
         if ( all_neighbors.size() >= 9 ) return ; // cut off the size of the cluster.
         if ( verbose ) printf("  HCAL hit %3d (%3d,%3d) neighbors hit %3d (%3d,%3d)\n", hit_index, hit_row, hit_col, hi, row, col ) ;
         all_neighbors.push_back( hi ) ;
         check_neighbors_hcal( hi, all_neighbors ) ;
      }

   } // hi

} // check_neighbors_hcal

//-----------------------------------------------------------------------------------------------------------

int mip_display::find_closest_hcal_hit( float ecalx, float ecaly ) {

    float min_dr = 999. ;
    int   closest_hcal_index(-1) ;
    for ( int hi=0; hi<fcs_rec_hcalE->size(); hi++ ) {
       float energy_hcal = fcs_rec_hcalE->at(hi) ;
       if ( energy_hcal < 0.1 ) continue ;
       float x = fcs_rec_hcalX->at(hi) ;
       float y = fcs_rec_hcalY->at(hi) ;
       float rx = x - ecalx  ;
       float ry = y - ecaly  ;
       float dr = sqrt( rx*rx + ry*ry ) ;
       if ( dr > 20 ) continue ;
       if ( dr < min_dr ) {
          min_dr = dr ;
          closest_hcal_index = hi ;
       }
    } // hi

    return closest_hcal_index ;

} // find_closest_hcal_hit


//-----------------------------------------------------------------------------------------------------------

void mip_display::calc_iso( float x, float y, vector<int> cluster_hits, float& iso20, float& iso30 ) {

   iso20 = 0. ;
   iso30 = 0. ;

   for ( int hi=0; hi<fcs_rec_ecalE->size(); hi++ ) {

      if ( std::find( cluster_hits.begin(), cluster_hits.end(), hi ) != cluster_hits.end() ) continue ; // skip hits that are in the cluster.

      float energy = fcs_rec_ecalE->at(hi) ;

      if ( energy < 0.001 ) continue ;

      float hitx = fcs_rec_ecalX->at(hi) ;
      float hity = fcs_rec_ecalY->at(hi) ;

      float dx = x - hitx ;
      float dy = y - hity ;

      float dr = sqrt( dx*dx + dy*dy ) ;
      if ( dr < 20. ) iso20 += energy ;
      if ( dr < 30. ) iso30 += energy ;


   } // hi

} // calc_iso

//-----------------------------------------------------------------------------------------------------------

void mip_display::Loop( int first_event, int max_evts, bool arg_verb )
{

   verbose = arg_verb ;

   if (fChain == 0) return;

   radius = 20. ;

   gDirectory -> Delete( "h*" ) ;



   Long64_t nentries = fChain->GetEntries();
   printf("\n\n Chain has %llu entries\n\n", nentries ) ;


  //-------- display stuff

   gStyle -> SetPadRightMargin(0.05) ;
   gStyle -> SetPadLeftMargin(0.15) ;
   gStyle -> SetPadTopMargin(0.05) ;
   gStyle -> SetPadBottomMargin(0.15) ;
   gStyle -> SetOptTitle(0) ;
   if (fChain == 0) return;



   tpm_fcsc -> SetMarkerStyle(20) ;
   tpm_fcsc -> SetMarkerColor(3) ;
   tpm_fcsc -> SetMarkerSize(0.7) ;

   tpm_fcs_mc_ecal -> SetMarkerStyle(25) ;
   tpm_fcs_mc_ecal -> SetMarkerColor(4) ;
   tpm_fcs_mc_ecal -> SetMarkerSize(2.0) ;

   tpm_fcs_mc_hcal -> SetMarkerStyle(25) ;
   tpm_fcs_mc_hcal -> SetMarkerColor(2) ;
   tpm_fcs_mc_hcal -> SetMarkerSize(4.0) ;

   ta_trk -> SetLineWidth(2) ;
   ta_cl -> SetLineStyle(2) ;

   //tpm_tp -> SetMarkerStyle(24) ;
   tpm_tp -> SetMarkerStyle(20) ;
   tpm_tp -> SetMarkerColor(1) ;
   tpm_tp -> SetMarkerSize(1.0) ;

   tpm_cl -> SetMarkerStyle(22) ;
   tpm_cl -> SetMarkerColor(2) ;
   tpm_cl -> SetMarkerSize(1.5) ;

   tpm_cl_ecal -> SetMarkerStyle(22) ;
   tpm_cl_ecal -> SetMarkerColor(4) ;
   tpm_cl_ecal -> SetMarkerSize(1.5) ;
   tpm_cl_hcal -> SetMarkerStyle(22) ;
   tpm_cl_hcal -> SetMarkerColor(2) ;
   tpm_cl_hcal -> SetMarkerSize(1.5) ;


   tb_ecal -> SetFillColor(4) ;
   tb_ecal -> SetFillStyle(1001) ;
   tb_ecal -> SetLineColor(4) ;
   tb_ecal_line -> SetFillStyle(0) ;
   tb_ecal_line -> SetLineColor(4) ;
   tb_ecal_line_red -> SetFillStyle(0) ;
   tb_ecal_line_red -> SetLineColor(2) ;
   tb_ecal_line_red -> SetLineWidth(4) ;

   tb_ecal_line2 -> SetFillStyle(0) ;
   tb_ecal_line2 -> SetLineColor(17) ;

   tb_hcal -> SetFillColor(2) ;
   tb_hcal -> SetFillStyle(1001) ;
   tb_hcal -> SetLineColor(2) ;
   tb_hcal_line -> SetFillStyle(0) ;
   tb_hcal_line -> SetLineColor(2) ;

   te_circle -> SetLineWidth(2) ;
   te_circle -> SetLineColor(2) ;
   te_circle -> SetFillStyle(0) ;


      gStyle -> SetOptStat(0) ;
      can_xy = get_canvas( "can_xy", "xy", 50, 50, 800, 800 ) ;
      can_xy -> Draw() ;
      can_xy_cluster = get_canvas( "can_xy_cluster", "xy", 850, 50, 800, 800 ) ;
      can_xy_cluster -> Draw() ;
      gSystem -> ProcessEvents() ;


         h_display_xy = new TH2F( "h_display_xy", "Display, xy", 800, -200., 200., 800, -200., 200. ) ;
         h_display_xy -> SetXTitle( "x position (cm)" ) ;
         h_display_xy -> SetYTitle( "y position (cm)" ) ;
         h_display_xy -> SetTitleOffset( 1.4, "y") ;
         h_display_xy -> SetTitleOffset( 1.2, "x") ;
         h_display_xy_cluster = new TH2F( "h_display_xy_cluster", "Display, xy, cluster", 800, -30., 30., 800, -30., 30. ) ;
         h_display_xy_cluster -> SetXTitle( "relative x position (cm)" ) ;
         h_display_xy_cluster -> SetYTitle( "relative y position (cm)" ) ;
         h_display_xy_cluster -> SetTitleOffset( 1.4, "y") ;
         h_display_xy_cluster -> SetTitleOffset( 1.2, "x") ;


  //-------- display stuff













   if ( max_evts < nentries && max_evts > 0 ) nentries = max_evts ;

   int start_event = 0 ;
   if ( first_event > 0 ) start_event = first_event ;


   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=start_event; jentry<nentries;jentry++) {

      all_used_hits.clear() ;

      vector< vector<int> > all_clusters ;

      if ( jentry % 1000 == 0 ) printf("  %9llu / %9llu\n", jentry, nentries ) ;

      if ( verbose ) printf("\n\n ========= Event %llu\n", jentry ) ;

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


      for ( int hi=0; hi<fcs_rec_ecalE->size(); hi++ ) {

         if ( std::find( all_used_hits.begin(), all_used_hits.end(), hi ) != all_used_hits.end() ) continue ; // already in list.  Skip

         all_used_hits.push_back( hi ) ; // add to all used hits list.

         float energy = fcs_rec_ecalE->at(hi) ;

         if ( energy < 0.001 ) continue ;

         int id = fcs_rec_ecalId->at(hi) ;
         int row = id/22 + 1 ; // correlated with Y
         int col = id%22 + 1 ; // correlated with X
         if ( verbose ) { printf("   ECAL hit %3d : id = %7d,  (%3d, %3d)   E = %7.3f\n", hi, id, row, col, energy ) ; }
         vector<int> all_neighbors ;
         check_neighbors( hi, all_neighbors ) ;

         for ( int nhi=0; nhi<all_neighbors.size(); nhi++ ) { all_used_hits.push_back( all_neighbors.at( nhi ) ) ; }

         all_clusters.push_back( all_neighbors ) ;


      } // hi








      if (verbose) printf("\n\n All clusters:\n") ;

      for ( int ci=0; ci<all_clusters.size(); ci++ ) {


         vector<int>& cluster = all_clusters.at(ci) ;
         if (verbose) printf("\n event %7llu :  cluster %3d:  nhits = %3lu\n", jentry, ci, cluster.size() ) ;
         float sumE = 0. ;
         float sumEx = 0. ;
         float sumEy = 0. ;
         for ( int hii=0; hii<cluster.size(); hii++ ) {
            int hi = cluster.at(hii) ;
            int id = fcs_rec_ecalId->at(hi) ;
            int row = id/22 + 1 ; // correlated with Y
            int col = id%22 + 1 ; // correlated with X
            float x = fcs_rec_ecalX->at(hi) ;
            float y = fcs_rec_ecalY->at(hi) ;
            int det = fcs_rec_ecalDet->at(hi) ;
            float energy = fcs_rec_ecalE->at(hi) ;
            if (verbose) printf("  ci %3d :  hii %3d  hi %3d   (%3d, %3d) det %d   (%6.1f, %6.1f)   E = %6.3f\n", ci, hii, hi, row, col, det, x, y, energy  ) ;
            sumE += energy ;
            sumEx += energy * x ;
            sumEy += energy * y ;
            //////if (verbose ) tb_ecal_line_red -> DrawBox( x - 5.572/2.,  y - 5.572/2.,  x + 5.572/2, y + 5.572/2 ) ;
         } // hi
         float clusterx = sumEx / sumE ;
         float clustery = sumEy / sumE ;
         int nhits = cluster.size() ;

         float iso20(0.), iso30(0.) ;
         calc_iso( clusterx, clustery, cluster, iso20, iso30 ) ;

         int trk_ind = match_track( clusterx, clustery ) ;



         int closest_hcal_hit_index = find_closest_hcal_hit( clusterx, clustery ) ;

         vector<int> all_neighbors_hcal ;
         check_neighbors_hcal( closest_hcal_hit_index, all_neighbors_hcal ) ;


         int nhits_hcal(0) ;
         float sumE_hcal(0.00000000001) ;
         float sumEx_hcal(0.) ;
         float sumEy_hcal(0.) ;
   ////  for ( int hi=0; hi<fcs_rec_hcalE->size(); hi++ ) {
   ////     float energy_hcal = fcs_rec_hcalE->at(hi) ;
   ////     if ( energy_hcal < 0.01 ) continue ;
   ////     float x = fcs_rec_hcalX->at(hi) ;
   ////     float y = fcs_rec_hcalY->at(hi) ;
   ////     float dx = clusterx - x ;
   ////     float dy = clustery - y ;
   ////     float dr = sqrt( dx*dx + dy*dy ) ;
   ////     if ( dr > 20 ) continue ;
   ////     nhits_hcal ++ ;
   ////     sumE_hcal += energy_hcal ;
   ////     sumEx_hcal += energy_hcal * x ;
   ////     sumEy_hcal += energy_hcal * y ;
   ////  } // hi
         for ( int ni=0; ni<all_neighbors_hcal.size(); ni++ ) {
            int hi = all_neighbors_hcal.at(ni) ;
            float energy_hcal = fcs_rec_hcalE->at(hi) ;
            if ( energy_hcal < 0.01 ) continue ;
            float x = fcs_rec_hcalX->at(hi) ;
            float y = fcs_rec_hcalY->at(hi) ;
            float dx = clusterx - x ;
            float dy = clustery - y ;
            nhits_hcal ++ ;
            sumE_hcal += energy_hcal ;
            sumEx_hcal += energy_hcal * x ;
            sumEy_hcal += energy_hcal * y ;
         } // hi
         float clusterx_hcal = sumEx_hcal / sumE_hcal ;
         float clustery_hcal = sumEy_hcal / sumE_hcal ;

         float hcal_iso20(0.) ;
         float hcal_iso30(0.) ;
         for ( int hi=0; hi<fcs_rec_hcalE->size(); hi++ ) {
            if ( std::find( all_neighbors_hcal.begin(), all_neighbors_hcal.end(), hi ) != all_neighbors_hcal.end() ) continue ; // don't include hcal cluster hits.
            float energy_hcal = fcs_rec_hcalE->at(hi) ;
            if ( energy_hcal < 0.01 ) continue ;
            float x = fcs_rec_hcalX->at(hi) ;
            float y = fcs_rec_hcalY->at(hi) ;
            float dx = clusterx - x ;
            float dy = clustery - y ;
            float dr = sqrt( dx*dx + dy*dy ) ;
            if ( dr > 30 ) continue ;
            hcal_iso30 += energy_hcal ;
            if ( dr > 20 ) continue ;
            hcal_iso20 += energy_hcal ;
         } // hi



         if (verbose) printf(" event %7llu :  cluster %3d:  (%6.1f, %6.1f)  sum E = %7.3f   iso20 %7.3f  iso30 %7.3f\n", jentry, ci, clusterx, clustery, sumE, iso20, iso30 ) ;
         if (verbose) printf("      HCAL     (%6.1f, %6.1f)  sum E = %7.3f  Nhits = %d  iso20 = %7.3f  iso30 = %7.3f\n", clusterx_hcal, clustery_hcal, sumE_hcal, nhits_hcal, hcal_iso20, hcal_iso30 ) ;


         int trk_nsys(0) ;
         float trk_x(-999.) ;
         float trk_y(-999.) ;
         if ( trk_ind >= 0 ) {
            if ( rcNumFST->at(trk_ind) > 0 ) trk_nsys++ ;
            if ( rcNumFTT->at(trk_ind) > 0 ) trk_nsys++ ;
            trk_x = rcProjEcalx->at(trk_ind) ;
            trk_y = rcProjEcaly->at(trk_ind) ;
         }


         float trk_pmag(1.) ;
         float trk_pmag_xy(1.) ;
         float trk_projL(1.) ;
         float trk_proj_pos_cosine(0.) ;
         if ( trk_ind >= 0 ) {
            float px = rcProjEcalPx->at(trk_ind) ;
            float py = rcProjEcalPy->at(trk_ind) ;
            float pz = rcProjEcalPz->at(trk_ind) ;
            trk_pmag = sqrt( px*px + py*py + pz*pz ) ;
            trk_pmag_xy = sqrt( px*px + py*py ) ;
            float x = rcProjEcalx->at(trk_ind) ;
            float y = rcProjEcaly->at(trk_ind) ;
            float z = rcProjEcalz->at(trk_ind) ;
            trk_projL = sqrt( x*x + y*y + z*z ) ;
            trk_proj_pos_cosine = ( px*x + py*y + pz*z ) / (trk_pmag*trk_projL) ;
            printf("   track projection    x,y,z  (%6.1f, %6.1f, %6.1f)  %7.1f\n", x, y, z, trk_projL ) ;
            printf("   track projection px,py,pz  (%6.3f, %6.3f, %6.3f)  %7.3f\n", px, py, pz, trk_pmag ) ;
            printf("   cos angle between track projection point and track momentum at projection point:  %9.6f\n", trk_proj_pos_cosine ) ;

            float clusterz = 745. ;
            float clusterz_hcal = 827. ;
            float cluster_dir_dx = clusterx_hcal - clusterx ;
            float cluster_dir_dy = clustery_hcal - clustery ;
            float cluster_dir_dz = clusterz_hcal - clusterz ;
            float cluster_dir_Lxy = sqrt( cluster_dir_dx*cluster_dir_dx + cluster_dir_dy*cluster_dir_dy  ) ;
            float cluster_dir_track_p_cos_xy = ( cluster_dir_dx * px + cluster_dir_dy * py ) / ( trk_pmag_xy * cluster_dir_Lxy ) ;
            printf("   cos angle between cluster xy direction and track momentum:    %9.6f\n", cluster_dir_track_p_cos_xy ) ;

            float cluster_ecal_lxy = sqrt( clusterx*clusterx + clustery*clustery ) ;
            float cluster_dir_ecal_hcal_xy = ( clusterx * cluster_dir_dx + clustery * cluster_dir_dy ) / ( cluster_ecal_lxy * cluster_dir_Lxy ) ;
            printf("   cos angle between cluster xy direction and ecal xy position:  %9.6f\n", cluster_dir_ecal_hcal_xy ) ;
         }

         float hcal_ecal_cos_angle(-2) ;
         if ( nhits_hcal > 0 && nhits > 0 ) {
            float cluster_dir_dx = clusterx_hcal - clusterx ;
            float cluster_dir_dy = clustery_hcal - clustery ;
            float cluster_dir_Lxy = sqrt( cluster_dir_dx*cluster_dir_dx + cluster_dir_dy*cluster_dir_dy  ) ;
            float cluster_ecal_Lxy = sqrt( clusterx*clusterx + clustery*clustery ) ;
            hcal_ecal_cos_angle = ( clusterx * cluster_dir_dx + clustery * cluster_dir_dy ) / ( cluster_ecal_Lxy * cluster_dir_Lxy ) ;
         }




         bool display_cluster = true ;
         if ( nhits_hcal > 5 ) display_cluster = false ;
         if ( nhits > 2 ) display_cluster = false ;
         if ( sumE < 0.15 ) display_cluster = false ;
         if ( sumE > 0.30 ) display_cluster = false ;
         if ( trk_nsys == 0 ) display_cluster = false ;
         if ( iso20 > 0.1 ) display_cluster = false ;
         if ( ( trk_x - clusterx ) > 4 ) display_cluster = false ;
         if ( ( trk_x - clusterx ) < -5 ) display_cluster = false ;
         if ( ( trk_y - clustery ) > 6 ) display_cluster = false ;
         if ( ( trk_y - clustery ) < -3 ) display_cluster = false ;
     //  if ( hcal_iso30 > 0.50 ) display_cluster = false ;
         ///if ( hcal_ecal_cos_angle < 0.80 ) display_cluster = false ;
         ///if ( sumE_hcal<1 ) display_cluster = false ;
         ///if ( sumE_hcal>2 ) display_cluster = false ;




         if ( display_cluster ) {

            draw_ecal_hits() ;
            can_xy_cluster -> cd() ;
            h_display_xy_cluster -> Draw() ;



            for ( int hi=0; hi<fcs_rec_hcalE->size(); hi++ ) {
               float energy_hcal = fcs_rec_hcalE->at(hi) ;
               if ( energy_hcal < 0.01 ) continue ;
               float x = fcs_rec_hcalX->at(hi) ;
               float y = fcs_rec_hcalY->at(hi) ;
               float dx = x - clusterx ;
               float dy = y - clustery ;
               float dr = sqrt( dx*dx + dy*dy ) ;
               if ( dr > 20 ) continue ;
               int hcal_hit_id = fcs_rec_hcalId->at(hi) ;
               int hcal_hit_row = hcal_hit_id/13 + 1 ; // correlated with Y
               int hcal_hit_col = hcal_hit_id%13 + 1 ; // correlated with X
               int hcal_hit_det = fcs_rec_hcalDet->at(hi) ;
               printf("  HCAL hit  %4d (%3d,%3d) %d:  dx,dy = (%6.1f,%6.1f)   E = %7.3f", hi, hcal_hit_row, hcal_hit_col, hcal_hit_det, dx, dy, energy_hcal ) ;
               if ( std::find( all_neighbors_hcal.begin(), all_neighbors_hcal.end(), hi ) != all_neighbors_hcal.end() ) printf(" neighbor" ) ;
               if ( hi == closest_hcal_hit_index ) printf(" closest") ;
               printf("\n") ;
            } // hi

            for ( int hii=0; hii<cluster.size(); hii++ ) {

               int hi = cluster.at(hii) ;

               float x = fcs_rec_ecalX->at(hi) ;
               float y = fcs_rec_ecalY->at(hi) ;
               can_xy -> cd() ;
               //tb_ecal_line_red -> DrawBox( x - 5.572/2.,  y - 5.572/2.,  x + 5.572/2, y + 5.572/2 ) ;


               float rx = x - clusterx ;
               float ry = y - clustery ;
               float energy = fcs_rec_ecalE->at(hi) ;
               can_xy_cluster -> cd() ;
               float alpha = energy  ;
               if ( alpha > 1 ) alpha = 1 ;
               if ( alpha < 0 ) alpha = 0 ;
               tb_ecal -> SetFillColorAlpha( kBlue, alpha ) ;
               tb_ecal -> DrawBox( rx - 5.572/2.,  ry - 5.572/2.,  rx + 5.572/2, ry + 5.572/2 ) ;
               tb_ecal_line -> DrawBox( rx - 5.572/2.,  ry - 5.572/2.,  rx + 5.572/2, ry + 5.572/2 ) ;

            } // hi

            {
               double x[1] ;
               double y[1] ;
               x[0] = clusterx ;
               y[0] = clustery ;
               float radius = 20. ;
               can_xy -> cd() ;
               te_circle -> DrawEllipse( x[0], y[0], radius, radius, 0., 360., 0. ) ;
               can_xy_cluster -> cd() ;
            }

            for ( int hi=0; hi<fcs_rec_hcalE->size(); hi++ ) {
               float energy_hcal = fcs_rec_hcalE->at(hi) ;
               if ( energy_hcal < 0.01 ) continue ;
               float x = fcs_rec_hcalX->at(hi) ;
               float y = fcs_rec_hcalY->at(hi) ;
               float rx = x - clusterx  ;
               float ry = y - clustery  ;
               float alpha = energy_hcal / 2. ;
               if ( alpha > 1 ) alpha = 1 ;
               if ( alpha < 0 ) alpha = 0 ;
               float dr = sqrt( rx*rx + ry*ry ) ;
               //if ( dr > 20 ) continue ;
               if ( dr > 30 ) continue ;
               tb_hcal -> SetFillColorAlpha( kRed, alpha ) ;
               tb_hcal -> DrawBox( rx - 9.99/2.,  ry - 9.99/2.,  rx + 9.99/2, ry + 9.99/2 ) ;
               tb_hcal_line -> DrawBox( rx - 9.99/2.,  ry - 9.99/2.,  rx + 9.99/2, ry + 9.99/2 ) ;
            } // hi

            for ( int ti=0; ti<rcN; ti++ ) {
               float tpx = rcProjEcalx->at(ti) ;
               float tpy = rcProjEcaly->at(ti) ;
               double x[10] ;
               double y[10] ;
               x[0] = tpx - clusterx ;
               y[0] = tpy - clustery ;
               tpm_tp -> DrawPolyMarker( 1, x, y ) ;
               float px = rcProjEcalPx->at(ti) ;
               float py = rcProjEcalPy->at(ti) ;
               float pz = rcProjEcalPz->at(ti) ;
               float dz = 150 ;
               float dx = (px/pz)*dz ;
               float dy = (py/pz)*dz ;
               float rx = tpx - clusterx ;
               float ry = tpy - clustery ;
               ta_trk -> DrawArrow( rx, ry, rx+dx, ry+dy, 0.05, ">" ) ;
            }

            if ( nhits > 0 && nhits_hcal > 0 ) {
               double x[10] ;
               double y[10] ;
               x[0] = 0. ;
               y[0] = 0. ;
               tpm_cl_ecal -> DrawPolyMarker( 1, x, y ) ;
               x[0] = clusterx_hcal - clusterx ;
               y[0] = clustery_hcal - clustery ;
               tpm_cl_hcal -> DrawPolyMarker( 1, x, y ) ;
               ta_cl -> DrawArrow( 0., 0., clusterx_hcal - clusterx, clustery_hcal - clustery, 0.03, ">" ) ;
            }

            if ( verbose ) {
               can_xy -> Update() ;
               can_xy -> Draw() ;
               can_xy_cluster -> Update() ;
               can_xy_cluster -> Draw() ;
               gSystem -> ProcessEvents() ;
               char answ = getchar() ;
               if ( answ == 'q' ) return ;
            }

         } // display_cluster?



      } // ci



   } // jentry



} // Loop







