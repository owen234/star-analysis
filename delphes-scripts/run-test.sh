
export LD_LIBRARY_PATH=/home/owen/root-build-6.24/root_install/lib:/home/owen/pythia/pythia8307/lib/

   export delphes_config=simple_star_forward_cal_config_jpt2.0.tcl
   export pythia_config=pythia_RHIC_test_10Mevts.cmnd

   mkdir test-output

   echo $delphes_config  $pythia_config

   nohup ./DelphesPythia8  $delphes_config  $pythia_config  test-output/foo.root >& test-output/foo.log &



