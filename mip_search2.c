#define mip_search2_cxx
#include "mip_search2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "histio.c"

//---------------
void ecal_id_to_row_col( int id, int& row, int& col ) {
   row = id/22+1 ;
   col = id%22+1 ;
}
//---------------
vector<int> all_used_hits ;

//-----------------------------------------------------------------------------------------------------------

int mip_search2::match_track( float x, float y, float radius ) {

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

void mip_search2::check_neighbors( int hit_index, vector<int>& all_neighbors ) {

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
         if ( verbose ) printf("  hit %3d (%3d,%3d) neighbors hit %3d (%3d,%3d)\n", hit_index, hit_row, hit_col, hi, row, col ) ;
         all_neighbors.push_back( hi ) ;
         check_neighbors( hi, all_neighbors ) ;
      }


   } // hi

} // check_neighbors

//-----------------------------------------------------------------------------------------------------------

void mip_search2::check_neighbors_hcal( int hit_index, vector<int>& all_neighbors ) {

   if ( hit_index < 0 ) return ;

   if ( all_neighbors.size() == 0 ) all_neighbors.push_back( hit_index ) ; // add the hit itself if necessary.

   if ( all_neighbors.size() >= 15 ) return ; // cut off the size of the cluster.

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
         if ( verbose ) printf("  HCAL hit %3d (%3d,%3d) neighbors hit %3d (%3d,%3d)\n", hit_index, hit_row, hit_col, hi, row, col ) ;
         if ( all_neighbors.size() >= 15 ) return ; // cut off the size of the cluster.
         all_neighbors.push_back( hi ) ;
         check_neighbors_hcal( hi, all_neighbors ) ;
      }

   } // hi

} // check_neighbors_hcal

//-----------------------------------------------------------------------------------------------------------

int mip_search2::find_closest_hcal_hit( float ecalx, float ecaly ) {

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

void mip_search2::calc_iso( float x, float y, vector<int> cluster_hits, float& iso20, float& iso30 ) {

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

void mip_search2::Loop( int max_evts, bool arg_verb )
{

   verbose = arg_verb ;

   if (fChain == 0) return;

   radius = 20. ;

   gDirectory -> Delete( "h*" ) ;


   TH1F* h_ecal_cluster_energy = new TH1F( "h_ecal_cluster_energy", "h_ecal_cluster_energy", 100, 0., 2. ) ;
   TH1F* h_ecal_cluster_energy_1hit = new TH1F( "h_ecal_cluster_energy_1hit", "h_ecal_cluster_energy_1hit", 100, 0., 2. ) ;
   TH1F* h_ecal_cluster_energy_2hit = new TH1F( "h_ecal_cluster_energy_2hit", "h_ecal_cluster_energy_2hit", 100, 0., 2. ) ;
   TH1F* h_ecal_cluster_energy_12hit = new TH1F( "h_ecal_cluster_energy_12hit", "h_ecal_cluster_energy_12hit", 100, 0., 2. ) ;
   TH1F* h_ecal_cluster_energy_iso20 = new TH1F( "h_ecal_cluster_energy_iso20", "h_ecal_cluster_energy_iso20", 100, 0., 2. ) ;
   TH1F* h_ecal_cluster_energy_trk = new TH1F( "h_ecal_cluster_energy_trk", "h_ecal_cluster_energy_trk", 100, 0., 2. ) ;
   TH1F* h_ecal_cluster_energy_trk_12hit_iso20 = new TH1F( "h_ecal_cluster_energy_trk_12hit_iso20", "h_ecal_cluster_energy_trk_12hit_iso20", 100, 0., 2. ) ;


   TH1F* h_hcal_energy = new TH1F( "h_hcal_energy", "h_hcal_energy", 100, 0., 4. ) ;
   TH1F* h_hcal_energy_1hit = new TH1F( "h_hcal_energy_1hit", "h_hcal_energy_1hit", 100, 0., 4. ) ;
   TH1F* h_hcal_energy_2hit = new TH1F( "h_hcal_energy_2hit", "h_hcal_energy_2hit", 100, 0., 4. ) ;
   TH1F* h_hcal_energy_12hit = new TH1F( "h_hcal_energy_12hit", "h_hcal_energy_12hit", 100, 0., 4. ) ;
   TH1F* h_hcal_nhits = new TH1F( "h_hcal_nhits", "h_hcal_nhits", 11, -0.5, 10.5 ) ;

   TH1F* h_hcal_energy_trk_ecalmip = new TH1F( "h_hcal_energy_trk_ecalmip", "h_hcal_energy_trk_ecalmip", 100, 0., 4. ) ;
   TH1F* h_hcal_energy_12hit_trk_ecalmip = new TH1F( "h_hcal_energy_12hit_trk_ecalmip", "h_hcal_energy_12hit_trk_ecalmip", 100, 0., 4. ) ;

   Long64_t nentries = fChain->GetEntries();
   printf("\n\n Chain has %llu entries\n\n", nentries ) ;








  //-------- display stuff

   gStyle -> SetPadRightMargin(0.05) ;
   gStyle -> SetPadLeftMargin(0.15) ;
   gStyle -> SetPadTopMargin(0.05) ;
   gStyle -> SetPadBottomMargin(0.15) ;
   gStyle -> SetOptTitle(0) ;
   if (fChain == 0) return;


   TPolyMarker* tpm_fcsc = new TPolyMarker() ;
   tpm_fcsc -> SetMarkerStyle(20) ;
   tpm_fcsc -> SetMarkerColor(3) ;
   tpm_fcsc -> SetMarkerSize(0.7) ;

   TPolyMarker* tpm_fcs_mc_ecal = new TPolyMarker() ;
   tpm_fcs_mc_ecal -> SetMarkerStyle(25) ;
   tpm_fcs_mc_ecal -> SetMarkerColor(4) ;
   tpm_fcs_mc_ecal -> SetMarkerSize(2.0) ;

   TPolyMarker* tpm_fcs_mc_hcal = new TPolyMarker() ;
   tpm_fcs_mc_hcal -> SetMarkerStyle(25) ;
   tpm_fcs_mc_hcal -> SetMarkerColor(2) ;
   tpm_fcs_mc_hcal -> SetMarkerSize(4.0) ;

   TPolyMarker* tpm_tp = new TPolyMarker() ;
   //tpm_tp -> SetMarkerStyle(24) ;
   tpm_tp -> SetMarkerStyle(20) ;
   tpm_tp -> SetMarkerColor(1) ;
   tpm_tp -> SetMarkerSize(1.0) ;

   TPolyMarker* tpm_cl = new TPolyMarker() ;
   tpm_cl -> SetMarkerStyle(22) ;
   tpm_cl -> SetMarkerColor(2) ;
   tpm_cl -> SetMarkerSize(1.5) ;


   TBox* tb_ecal = new TBox() ;
   tb_ecal -> SetFillColor(4) ;
   tb_ecal -> SetFillStyle(1001) ;
   tb_ecal -> SetLineColor(4) ;
   TBox* tb_ecal_line = new TBox() ;
   tb_ecal_line -> SetFillStyle(0) ;
   tb_ecal_line -> SetLineColor(4) ;
   TBox* tb_ecal_line_red = new TBox() ;
   tb_ecal_line_red -> SetFillStyle(0) ;
   tb_ecal_line_red -> SetLineColor(2) ;
   tb_ecal_line_red -> SetLineWidth(4) ;

   TBox* tb_ecal_line2 = new TBox() ;
   tb_ecal_line2 -> SetFillStyle(0) ;
   tb_ecal_line2 -> SetLineColor(17) ;

   TBox* tb_hcal = new TBox() ;
   tb_hcal -> SetFillColor(2) ;
   tb_hcal -> SetFillStyle(1001) ;
   tb_hcal -> SetLineColor(2) ;
   TBox* tb_hcal_line = new TBox() ;
   tb_hcal_line -> SetFillStyle(0) ;
   tb_hcal_line -> SetLineColor(2) ;

   TEllipse* te_circle = new TEllipse() ;
   te_circle -> SetLineWidth(2) ;
   te_circle -> SetLineColor(2) ;
   te_circle -> SetFillStyle(0) ;


   TCanvas* can_xy(0x0) ;
      gStyle -> SetOptStat(0) ;
      can_xy = new TCanvas( "can_xy", "xy", 50, 50, 800, 800 ) ;
      can_xy -> Draw() ;
      gSystem -> ProcessEvents() ;

   TH2F* h_display_xy = new TH2F( "h_display_xy", "Display, xy", 800, -200., 200., 800, -200., 200. ) ;


  //-------- display stuff





   int tt_n_ecal_cl ;
   vector<float> tt_ecal_E ;
   vector<int>   tt_ecal_nhit ;
   vector<float> tt_ecal_x ;
   vector<float> tt_ecal_y ;
   vector<float> tt_ecal_iso20 ;
   vector<float> tt_ecal_iso30 ;
   vector<int>   tt_trk_nsys ;
   vector<float> tt_trk_x ;
   vector<float> tt_trk_y ;
   vector<float> tt_hcal_E ;
   vector<int>   tt_hcal_nhit ;
   vector<float> tt_hcal_x ;
   vector<float> tt_hcal_y ;
   vector<float> tt_hcal_ecal_cos_angle ;
   vector<float> tt_hcal_iso20 ;
   vector<float> tt_hcal_iso30 ;


   //--- storing a vector of vectors in a TTree requires extra crap that doesn't work.  Do it the dumb way.

   ////////std::vector<vector<int>> tt_ecal_hit_index ; // NFG
   ////////std::vector<vector<int>> tt_hcal_hit_index ; // NFG

   vector<int> tt_ecal_hit0ind ;
   vector<int> tt_ecal_hit1ind ;

   vector<int> tt_hcal_hit0ind ;
   vector<int> tt_hcal_hit1ind ;
   vector<int> tt_hcal_hit2ind ;
   vector<int> tt_hcal_hit3ind ;
   vector<int> tt_hcal_hit4ind ;

   vector<int> tt_trk_index ;


   TTree* tt_out = new TTree( "mipsearch2", "mipsearch2" ) ;

   tt_out -> Branch( "n_ecal_cl", &tt_n_ecal_cl ) ;
   tt_out -> Branch( "ecal_E", &tt_ecal_E ) ;
   tt_out -> Branch( "ecal_nhit", &tt_ecal_nhit ) ;
   tt_out -> Branch( "ecal_x", &tt_ecal_x ) ;
   tt_out -> Branch( "ecal_y", &tt_ecal_y ) ;
   tt_out -> Branch( "ecal_iso20", &tt_ecal_iso20 ) ;
   tt_out -> Branch( "ecal_iso30", &tt_ecal_iso30 ) ;
   tt_out -> Branch( "trk_nsys", &tt_trk_nsys ) ;
   tt_out -> Branch( "trk_x", &tt_trk_x ) ;
   tt_out -> Branch( "trk_y", &tt_trk_y ) ;
   tt_out -> Branch( "hcal_E", &tt_hcal_E ) ;
   tt_out -> Branch( "hcal_nhit", &tt_hcal_nhit ) ;
   tt_out -> Branch( "hcal_x", &tt_hcal_x ) ;
   tt_out -> Branch( "hcal_y", &tt_hcal_y ) ;
   tt_out -> Branch( "hcal_ecal_cos_angle", &tt_hcal_ecal_cos_angle ) ;
   ///////tt_out -> Branch( "hcal_iso20", &tt_ecal_iso20 ) ; // bug found 2023-10-09
   ///////tt_out -> Branch( "hcal_iso30", &tt_ecal_iso30 ) ; // bug found 2023-10-09
   tt_out -> Branch( "hcal_iso20", &tt_hcal_iso20 ) ;
   tt_out -> Branch( "hcal_iso30", &tt_hcal_iso30 ) ;

   tt_out -> Branch( "ecal_hit0ind", &tt_ecal_hit0ind ) ;
   tt_out -> Branch( "ecal_hit1ind", &tt_ecal_hit1ind ) ;

   tt_out -> Branch( "hcal_hit0ind", &tt_hcal_hit0ind ) ;
   tt_out -> Branch( "hcal_hit1ind", &tt_hcal_hit1ind ) ;
   tt_out -> Branch( "hcal_hit2ind", &tt_hcal_hit2ind ) ;
   tt_out -> Branch( "hcal_hit3ind", &tt_hcal_hit3ind ) ;
   tt_out -> Branch( "hcal_hit4ind", &tt_hcal_hit4ind ) ;

   tt_out -> Branch( "trk_index", &tt_trk_index ) ;




   if ( max_evts < nentries && max_evts > 0 ) nentries = max_evts ;


   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

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



      if ( verbose ) {

         can_xy -> cd() ;
         h_display_xy -> SetXTitle( "x position (cm)" ) ;
         h_display_xy -> SetYTitle( "y position (cm)" ) ;
         h_display_xy -> SetTitleOffset( 1.4, "y") ;
         h_display_xy -> SetTitleOffset( 1.2, "x") ;
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

      } // verbose?






      if (verbose) printf("\n\n All clusters:\n") ;

      for ( int ci=0; ci<all_clusters.size(); ci++ ) {


         vector<int>& cluster = all_clusters.at(ci) ;
         if (verbose) printf("\n cluster %3d:  nhits = %3lu\n", ci, cluster.size() ) ;
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
            if (verbose ) tb_ecal_line_red -> DrawBox( x - 5.572/2.,  y - 5.572/2.,  x + 5.572/2, y + 5.572/2 ) ;
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



         if (verbose) printf(" cluster %3d:  (%6.1f, %6.1f)  sum E = %7.3f   iso20 %7.3f  iso30 %7.3f\n", ci, clusterx, clustery, sumE, iso20, iso30 ) ;
         if (verbose) printf("      HCAL     (%6.1f, %6.1f)  sum E = %7.3f  Nhits = %d\n", clusterx_hcal, clustery_hcal, sumE_hcal, nhits_hcal ) ;

         h_ecal_cluster_energy -> Fill( sumE ) ;
         if ( nhits == 1 ) h_ecal_cluster_energy_1hit -> Fill( sumE ) ;
         if ( nhits == 2 ) h_ecal_cluster_energy_2hit -> Fill( sumE ) ;
         if ( nhits <= 2 ) h_ecal_cluster_energy_12hit -> Fill( sumE ) ;
         if ( iso20 < 0.010 ) h_ecal_cluster_energy_iso20 -> Fill( sumE ) ;
         if ( trk_ind >= 0 ) h_ecal_cluster_energy_trk -> Fill( sumE ) ;
         if ( trk_ind >= 0 && nhits <= 2 && iso20 < 0.010 ) h_ecal_cluster_energy_trk_12hit_iso20 -> Fill( sumE ) ;

         h_hcal_energy -> Fill( sumE_hcal ) ;
         h_hcal_nhits -> Fill( nhits_hcal ) ;
         if ( nhits_hcal == 1 ) h_hcal_energy_1hit -> Fill( sumE_hcal ) ;
         if ( nhits_hcal == 2 ) h_hcal_energy_2hit -> Fill( sumE_hcal ) ;
         if ( nhits_hcal == 1 || nhits_hcal == 2 ) h_hcal_energy_12hit -> Fill( sumE_hcal ) ;

         if ( trk_ind >= 0 && nhits <= 2 && iso20 < 0.010 && sumE>0.15 && sumE<0.30 ) h_hcal_energy_trk_ecalmip -> Fill( sumE_hcal ) ;
         if ( ( nhits_hcal == 1 || nhits_hcal == 2 ) && trk_ind >= 0 && nhits <= 2 && iso20 < 0.010 && sumE>0.15 && sumE<0.30 ) h_hcal_energy_12hit_trk_ecalmip -> Fill( sumE_hcal ) ;

         int trk_nsys(0) ;
         float trk_x(-999.) ;
         float trk_y(-999.) ;
         if ( trk_ind >= 0 ) {
            if ( rcNumFST->at(trk_ind) > 0 ) trk_nsys++ ;
            if ( rcNumFTT->at(trk_ind) > 0 ) trk_nsys++ ;
            trk_x = rcProjEcalx->at(trk_ind) ;
            trk_y = rcProjEcaly->at(trk_ind) ;
         }

         if ( verbose ) {
            can_xy -> Update() ;
            can_xy -> Draw() ;
            gSystem -> ProcessEvents() ;
            char answ = getchar() ;
            if ( answ == 'q' ) return ;
         }

         float hcal_ecal_cos_angle(-2) ;
         if ( nhits_hcal > 0 && nhits > 0 ) {
            float cluster_dir_dx = clusterx_hcal - clusterx ;
            float cluster_dir_dy = clustery_hcal - clustery ;
            float cluster_dir_Lxy = sqrt( cluster_dir_dx*cluster_dir_dx + cluster_dir_dy*cluster_dir_dy  ) ;
            float cluster_ecal_Lxy = sqrt( clusterx*clusterx + clustery*clustery ) ;
            hcal_ecal_cos_angle = ( clusterx * cluster_dir_dx + clustery * cluster_dir_dy ) / ( cluster_ecal_Lxy * cluster_dir_Lxy ) ;
         }

         int tmp_ecal_hit0ind(-1) ;
         int tmp_ecal_hit1ind(-1) ;

         int tmp_hcal_hit0ind(-1) ;
         int tmp_hcal_hit1ind(-1) ;
         int tmp_hcal_hit2ind(-1) ;
         int tmp_hcal_hit3ind(-1) ;
         int tmp_hcal_hit4ind(-1) ;

         if ( cluster.size() > 0 ) tmp_ecal_hit0ind = cluster.at(0) ;
         if ( cluster.size() > 1 ) tmp_ecal_hit1ind = cluster.at(1) ;

         if ( all_neighbors_hcal.size() > 0 ) tmp_hcal_hit0ind = all_neighbors_hcal.at(0) ;
         if ( all_neighbors_hcal.size() > 1 ) tmp_hcal_hit1ind = all_neighbors_hcal.at(1) ;
         if ( all_neighbors_hcal.size() > 2 ) tmp_hcal_hit2ind = all_neighbors_hcal.at(2) ;
         if ( all_neighbors_hcal.size() > 3 ) tmp_hcal_hit3ind = all_neighbors_hcal.at(3) ;
         if ( all_neighbors_hcal.size() > 4 ) tmp_hcal_hit4ind = all_neighbors_hcal.at(4) ;


         tt_ecal_E.push_back( sumE ) ;
         tt_ecal_nhit.push_back( nhits ) ;
         tt_ecal_x.push_back( clusterx ) ;
         tt_ecal_y.push_back( clustery ) ;
         tt_ecal_iso20.push_back( iso20 ) ;
         tt_ecal_iso30.push_back( iso30 ) ;
         tt_trk_nsys.push_back( trk_nsys ) ;
         tt_trk_x.push_back( trk_x ) ;
         tt_trk_y.push_back( trk_y ) ;
         tt_hcal_E.push_back( sumE_hcal ) ;
         tt_hcal_nhit.push_back( nhits_hcal ) ;
         tt_hcal_x.push_back( clusterx_hcal ) ;
         tt_hcal_y.push_back( clustery_hcal ) ;
         tt_hcal_ecal_cos_angle.push_back( hcal_ecal_cos_angle ) ;
         tt_hcal_iso20.push_back( hcal_iso20 ) ;
         tt_hcal_iso30.push_back( hcal_iso30 ) ;

         tt_ecal_hit0ind.push_back( tmp_ecal_hit0ind ) ;
         tt_ecal_hit1ind.push_back( tmp_ecal_hit1ind ) ;

         tt_hcal_hit0ind.push_back( tmp_hcal_hit0ind ) ;
         tt_hcal_hit1ind.push_back( tmp_hcal_hit1ind ) ;
         tt_hcal_hit2ind.push_back( tmp_hcal_hit2ind ) ;
         tt_hcal_hit3ind.push_back( tmp_hcal_hit3ind ) ;
         tt_hcal_hit4ind.push_back( tmp_hcal_hit4ind ) ;

         tt_trk_index.push_back( trk_ind ) ;



      } // ci

      tt_n_ecal_cl = all_clusters.size() ;

      tt_out -> Fill() ;

      tt_ecal_E.clear() ;
      tt_ecal_nhit.clear() ;
      tt_ecal_x.clear() ;
      tt_ecal_y.clear() ;
      tt_ecal_iso20.clear() ;
      tt_ecal_iso30.clear() ;
      tt_trk_nsys.clear() ;
      tt_trk_x.clear() ;
      tt_trk_y.clear() ;
      tt_hcal_E.clear() ;
      tt_hcal_nhit.clear() ;
      tt_hcal_x.clear() ;
      tt_hcal_y.clear() ;
      tt_hcal_ecal_cos_angle.clear() ;
      tt_hcal_iso20.clear() ;
      tt_hcal_iso30.clear() ;

      tt_ecal_hit0ind.clear() ;
      tt_ecal_hit1ind.clear() ;

      tt_hcal_hit0ind.clear() ;
      tt_hcal_hit1ind.clear() ;
      tt_hcal_hit2ind.clear() ;
      tt_hcal_hit3ind.clear() ;
      tt_hcal_hit4ind.clear() ;

      tt_trk_index.clear() ;


   } // jentry

   gDirectory -> ls() ;


   TFile* tf_out = new TFile( "ms2-out.root", "recreate" ) ;
   tt_out -> Write() ;
   tf_out -> Close() ;


} // Loop







