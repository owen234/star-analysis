
#include "calo_analysis4.c"

void run_all() {

   calo_analysis4* c1 = new calo_analysis4("pthat-1.0to1.8" )  ;
   calo_analysis4* c2 = new calo_analysis4("pthat-1.8-cut-to-1.8to3.0" )  ;
   calo_analysis4* c3 = new calo_analysis4("pthat-3.0to5.0" )  ;
   calo_analysis4* c4 = new calo_analysis4("pthat-5.0" )  ;

   c1 -> Loop() ;
   c2 -> Loop() ;
   c3 -> Loop() ;
   c4 -> Loop() ;


}
