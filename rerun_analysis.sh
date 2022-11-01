#!/usr/bin/bash

  root -b -q run_all.c

  cd ca4-output
  mv all.root all.root-old
  hadd all.root d*.root
  cd ..
  ls -lrt ca4-output


