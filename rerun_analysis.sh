#!/usr/bin/bash

  root -b -q run_all.c

  cd ca4-output
  mv all.root all.root-old
  hadd   all.root   dset-pthat-1.0to1.8.root  dset-pthat-1.8-cut-to-1.8to3.0.root  dset-pthat-3.0to5.0.root  dset-pthat-5.0.root
  cd ..
  ls -lrt ca4-output


