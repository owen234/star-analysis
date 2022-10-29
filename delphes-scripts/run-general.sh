

 mkdir current-output

export LD_LIBRARY_PATH=/home/owen/root-build-6.24/root_install/lib:/home/owen/pythia/pythia8307/lib/



  #----------------

  #export delphes_config=simple_star_forward_cal_config_jpt2.0.tcl
  #export delphes_config=simple_star_forward_cal_config_jpt3.0.tcl

   export delphes_config=simple_star_forward_cal_config_rec_jpt3.0_gen_jpt2.0.tcl

  #----------------

  #export pythia_config=pythia_RHIC_test_50Mevts.cmnd

  #export pythia_config=pythia_RHIC_test_pthat1.8_40Mevts.cmnd
  #export pythia_config=pythia_RHIC_test_pthat1.8_30Mevts.cmnd
   export pythia_config=pythia_RHIC_test_pthat1.8_10Mevts.cmnd

  #export pythia_config=pythia_RHIC_test_pthat5.0_10Mevts.cmnd
  #export pythia_config=pythia_RHIC_test_pthat5.0_5Mevts.cmnd
  #export pythia_config=pythia_RHIC_test_pthat5.0_40Mevts.cmnd

  #----------------



  cp $delphes_config current-output
  cp $pythia_config current-output

  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-00.root     >&     current-output/chunk-00.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-01.root     >&     current-output/chunk-01.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-02.root     >&     current-output/chunk-02.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-03.root     >&     current-output/chunk-03.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-04.root     >&     current-output/chunk-04.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-05.root     >&     current-output/chunk-05.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-06.root     >&     current-output/chunk-06.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-07.root     >&     current-output/chunk-07.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-08.root     >&     current-output/chunk-08.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-09.root     >&     current-output/chunk-09.log &
  sleep 2

  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-10.root     >&     current-output/chunk-10.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-11.root     >&     current-output/chunk-11.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-12.root     >&     current-output/chunk-12.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-13.root     >&     current-output/chunk-13.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-14.root     >&     current-output/chunk-14.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-15.root     >&     current-output/chunk-15.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-16.root     >&     current-output/chunk-16.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-17.root     >&     current-output/chunk-17.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-18.root     >&     current-output/chunk-18.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-19.root     >&     current-output/chunk-19.log &
  sleep 2

  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-20.root     >&     current-output/chunk-20.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-21.root     >&     current-output/chunk-21.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-22.root     >&     current-output/chunk-22.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-23.root     >&     current-output/chunk-23.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-24.root     >&     current-output/chunk-24.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-25.root     >&     current-output/chunk-25.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-26.root     >&     current-output/chunk-26.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-27.root     >&     current-output/chunk-27.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-28.root     >&     current-output/chunk-28.log &
  sleep 2
  nohup   ./DelphesPythia8        $delphes_config        $pythia_config   current-output/chunk-29.root     >&     current-output/chunk-29.log &






