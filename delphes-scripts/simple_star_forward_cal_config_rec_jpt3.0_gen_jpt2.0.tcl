#######################################
# Order of execution of various modules
#######################################

set ExecutionPath {
  ParticlePropagator

  ChargedHadronTrackingEfficiency
  ElectronTrackingEfficiency
  ChargedHadronMomentumSmearing
  ElectronMomentumSmearing
  TrackMerger



  ECal
  HCal

  Calorimeter


  NeutrinoFilter

  GenJetFinder05
  GenJetFinder10

  FastJetFinder05
  FastJetFinder10

  TreeWriter
}

#################################
# Propagate particles in cylinder
#################################

module ParticlePropagator ParticlePropagator {
  set InputArray Delphes/stableParticles

  set OutputArray stableParticles
  set ChargedHadronOutputArray chargedHadrons
  set ElectronOutputArray electrons
  set MuonOutputArray muons

  # radius of the magnetic field coverage, in m
  set Radius 2.00
  # half-length of the magnetic field coverage, in m
  set HalfLength 3.00

  # magnetic field
  set Bz 0.5
}

##  A track list is required for the calorimeter parts, so make a central one that won't matter for forward    

set CommonTrackingEfficiency {
    (abs(eta) <= 1.0) * (pt > 0.100)                     * (1.0) +
    0.0
}

set CommonTrackingResolution {
    (abs(eta)<=1.0)  * (sqrt( (2.0e-2)^2 + (pt*cosh(eta)*5e-3)^2  ) ) +
    0.0
}

module Efficiency ChargedHadronTrackingEfficiency {
  set InputArray ParticlePropagator/chargedHadrons
  set OutputArray chargedHadrons
  set EfficiencyFormula $CommonTrackingEfficiency
}
module Efficiency ElectronTrackingEfficiency {
  set InputArray ParticlePropagator/electrons
  set OutputArray electrons
  set EfficiencyFormula $CommonTrackingEfficiency
}
module MomentumSmearing ChargedHadronMomentumSmearing {
  set InputArray ChargedHadronTrackingEfficiency/chargedHadrons
  set OutputArray chargedHadrons
  set ResolutionFormula  $CommonTrackingResolution
}
module MomentumSmearing ElectronMomentumSmearing {
  set InputArray ElectronTrackingEfficiency/electrons
  set OutputArray electrons
  set ResolutionFormula $CommonTrackingResolution
}
module Merger TrackMerger {
  add InputArray ChargedHadronMomentumSmearing/chargedHadrons
  add InputArray ElectronMomentumSmearing/electrons
  set OutputArray tracks
}




#############
#   ECAL
#############

module SimpleCalorimeter ECal {
  set ParticleInputArray ParticlePropagator/stableParticles
  set TrackInputArray TrackMerger/tracks

  set TowerOutputArray ecalTowers
  set EFlowTrackOutputArray eflowTracks
  set EFlowTowerOutputArray eflowPhotons

  set IsEcal true

  set EnergyMin 0.1
  set EnergySignificanceMin 1.0

  set SmearTowerCenter true
  #set SmearTowerCenter false

  set pi [expr {acos(-1)}]

  # lists of the edges of each tower in eta and phi
  # each list starts with the lower edge of the first tower
  # the list ends with the higher edged of the last tower

  # STAR forward ECAL is rectangulary array of 5.22 cm x 5.22 cm x 30 cm at z = 7 m  from about 2.5 < eta < 4.0
  # make the face area roughly 5.22 cm x 5.22 cm in that eta range


  #-- eta 2.417 has 152 phi cells
  set PhiBins {}
  for {set i -76} {$i <= 76} {incr i} {
    add PhiBins [expr {$i * $pi/76.0}]
  }
  add EtaPhiBins 2.417 $PhiBins


  #-- eta 2.460 has 145 phi cells
  set PhiBins {}
  for {set i -73} {$i <= 73} {incr i} {
    add PhiBins [expr {$i * $pi/73.0}]
  }
  add EtaPhiBins 2.460 $PhiBins


  #-- eta 2.505 has 139 phi cells
  set PhiBins {}
  for {set i -69} {$i <= 69} {incr i} {
    add PhiBins [expr {$i * $pi/69.0}]
  }
  add EtaPhiBins 2.505 $PhiBins


  #-- eta 2.551 has 132 phi cells
  set PhiBins {}
  for {set i -66} {$i <= 66} {incr i} {
    add PhiBins [expr {$i * $pi/66}]
  }
  add EtaPhiBins 2.551 $PhiBins


  set PhiBins {}
  for {set i -63} {$i <= 63} {incr i} {
    add PhiBins [expr {$i * $pi/63}]
  }
  add EtaPhiBins 2.600 $PhiBins


  set PhiBins {}
  for {set i -60} {$i <= 60} {incr i} {
    add PhiBins [expr {$i * $pi/60}]
  }
  add EtaPhiBins 2.652 $PhiBins


  set PhiBins {}
  for {set i -57} {$i <= 57} {incr i} {
    add PhiBins [expr {$i * $pi/57}]
  }
  add EtaPhiBins 2.706 $PhiBins


  set PhiBins {}
  for {set i -53} {$i <= 53} {incr i} {
    add PhiBins [expr {$i * $pi/53}]
  }
  add EtaPhiBins 2.764 $PhiBins


  set PhiBins {}
  for {set i -50} {$i <= 50} {incr i} {
    add PhiBins [expr {$i * $pi/50}]
  }
  add EtaPhiBins 2.825 $PhiBins


  set PhiBins {}
  for {set i -47} {$i <= 47} {incr i} {
    add PhiBins [expr {$i * $pi/47}]
  }
  add EtaPhiBins 2.890 $PhiBins


  set PhiBins {}
  for {set i -44} {$i <= 44} {incr i} {
    add PhiBins [expr {$i * $pi/44}]
  }
  add EtaPhiBins 2.959 $PhiBins


  set PhiBins {}
  for {set i -41} {$i <= 41} {incr i} {
    add PhiBins [expr {$i * $pi/41}]
  }
  add EtaPhiBins 3.034 $PhiBins


  set PhiBins {}
  for {set i -38} {$i <= 38} {incr i} {
    add PhiBins [expr {$i * $pi/38}]
  }
  add EtaPhiBins 3.114 $PhiBins


  set PhiBins {}
  for {set i -34} {$i <= 34} {incr i} {
    add PhiBins [expr {$i * $pi/34}]
  }
  add EtaPhiBins 3.202 $PhiBins


  set PhiBins {}
  for {set i -31} {$i <= 31} {incr i} {
    add PhiBins [expr {$i * $pi/31}]
  }
  add EtaPhiBins 3.298 $PhiBins


  set PhiBins {}
  for {set i -28} {$i <= 28} {incr i} {
    add PhiBins [expr {$i * $pi/28}]
  }
  add EtaPhiBins 3.404 $PhiBins


  set PhiBins {}
  for {set i -25} {$i <= 25} {incr i} {
    add PhiBins [expr {$i * $pi/25}]
  }
  add EtaPhiBins 3.524 $PhiBins


  set PhiBins {}
  for {set i -22} {$i <= 22} {incr i} {
    add PhiBins [expr {$i * $pi/22}]
  }
  add EtaPhiBins 3.659 $PhiBins


  set PhiBins {}
  for {set i -19} {$i <= 19} {incr i} {
    add PhiBins [expr {$i * $pi/19}]
  }
  add EtaPhiBins 3.815 $PhiBins


  set PhiBins {}
  for {set i -15} {$i <= 15} {incr i} {
    add PhiBins [expr {$i * $pi/15}]
  }
  add EtaPhiBins 4.000 $PhiBins


  set PhiBins {}
  for {set i -12} {$i <= 12} {incr i} {
    add PhiBins [expr {$i * $pi/12}]
  }
  add EtaPhiBins 4.228 $PhiBins




  add EnergyFraction {0} {0.0}
  # energy fractions for e, gamma and pi0
  add EnergyFraction {11} {1.0}
  add EnergyFraction {22} {1.0}
  add EnergyFraction {111} {1.0}
  # energy fractions for muon, neutrinos and neutralinos
  add EnergyFraction {12} {0.0}
  add EnergyFraction {13} {0.0}
  add EnergyFraction {14} {0.0}
  add EnergyFraction {16} {0.0}
  add EnergyFraction {1000022} {0.0}
  add EnergyFraction {1000023} {0.0}
  add EnergyFraction {1000025} {0.0}
  add EnergyFraction {1000035} {0.0}
  add EnergyFraction {1000045} {0.0}
  # energy fractions for K0short and Lambda
  add EnergyFraction {310} {0.3}
  add EnergyFraction {3122} {0.3}

  # from "Results of the 2019 STAR FCS Test Beam at FNAL" note, Figure 16
  #    sigma / E = 0.11/sqrt(E) + 0.011

  set ResolutionFormula {  ( eta>2.417 && eta<=4.228 ) * sqrt(energy^2*0.011^2 + energy*0.11^2 )  }

}


#############
#   HCAL
#############

module SimpleCalorimeter HCal {
  set ParticleInputArray ParticlePropagator/stableParticles
  set TrackInputArray ECal/eflowTracks

  set TowerOutputArray hcalTowers
  #set EFlowTrackOutputArray eflowTracks
  #set EFlowTowerOutputArray eflowNeutralHadrons

  set IsEcal false

  set EnergyMin 0.5
  set EnergySignificanceMin 1.0

  set SmearTowerCenter true
  #set SmearTowerCenter false

  set pi [expr {acos(-1)}]

  # lists of the edges of each tower in eta and phi
  # each list starts with the lower edge of the first tower
  # the list ends with the higher edged of the last tower

  # STAR forward HCAL is rectangulary array of 10 cm x 10 cm at z = 7.33 m  from about 2.5 < eta < 4.0
  # make the face area roughly 10 cm x 10 cm in that eta range


  set PhiBins {}
  for {set i -40} {$i <= 40} {incr i} {
    add PhiBins [expr {$i * $pi/40}]
  }
  add EtaPhiBins 2.412 $PhiBins


  set PhiBins {}
  for {set i -37} {$i <= 37} {incr i} {
    add PhiBins [expr {$i * $pi/37}]
  }
  add EtaPhiBins 2.491 $PhiBins


  set PhiBins {}
  for {set i -34} {$i <= 34} {incr i} {
    add PhiBins [expr {$i * $pi/34}]
  }
  add EtaPhiBins 2.577 $PhiBins


  set PhiBins {}
  for {set i -31} {$i <= 31} {incr i} {
    add PhiBins [expr {$i * $pi/31}]
  }
  add EtaPhiBins 2.671 $PhiBins


  set PhiBins {}
  for {set i -28} {$i <= 28} {incr i} {
    add PhiBins [expr {$i * $pi/28}]
  }
  add EtaPhiBins 2.775 $PhiBins


  set PhiBins {}
  for {set i -25} {$i <= 25} {incr i} {
    add PhiBins [expr {$i * $pi/25}]
  }
  add EtaPhiBins 2.891 $PhiBins


  set PhiBins {}
  for {set i -21} {$i <= 21} {incr i} {
    add PhiBins [expr {$i * $pi/21}]
  }
  add EtaPhiBins 3.022 $PhiBins


  set PhiBins {}
  for {set i -18} {$i <= 18} {incr i} {
    add PhiBins [expr {$i * $pi/18}]
  }
  add EtaPhiBins 3.173 $PhiBins


  set PhiBins {}
  for {set i -15} {$i <= 15} {incr i} {
    add PhiBins [expr {$i * $pi/15}]
  }
  add EtaPhiBins 3.351 $PhiBins


  set PhiBins {}
  for {set i -12} {$i <= 12} {incr i} {
    add PhiBins [expr {$i * $pi/12}]
  }
  add EtaPhiBins 3.568 $PhiBins


  set PhiBins {}
  for {set i -9} {$i <= 9} {incr i} {
    add PhiBins [expr {$i * $pi/9}]
  }
  add EtaPhiBins 3.844 $PhiBins


  set PhiBins {}
  for {set i -6} {$i <= 6} {incr i} {
    add PhiBins [expr {$i * $pi/6}]
  }
  add EtaPhiBins 4.228 $PhiBins




  # default energy fractions {abs(PDG code)} {Fecal Fhcal}
  add EnergyFraction {0} {1.0}
  # energy fractions for e, gamma and pi0
  add EnergyFraction {11} {0.0}
  add EnergyFraction {22} {0.0}
  add EnergyFraction {111} {0.0}
  # energy fractions for muon, neutrinos and neutralinos
  add EnergyFraction {12} {0.0}
  add EnergyFraction {13} {0.0}
  add EnergyFraction {14} {0.0}
  add EnergyFraction {16} {0.0}
  add EnergyFraction {1000022} {0.0}
  add EnergyFraction {1000023} {0.0}
  add EnergyFraction {1000025} {0.0}
  add EnergyFraction {1000035} {0.0}
  add EnergyFraction {1000045} {0.0}
  # energy fractions for K0short and Lambda
  add EnergyFraction {310} {0.7}
  add EnergyFraction {3122} {0.7}

  # from "Results of the 2019 STAR FCS Test Beam at FNAL" note, Figure 23
  #    sigma / E = 0.80/sqrt(E) + 0.072

  # set HCalResolutionFormula {resolution formula as a function of eta and energy}
  set ResolutionFormula { (eta > 2.412 && eta <= 4.228) * sqrt(energy^2*0.072^2 + energy*0.80^2)}

}



###################################################
# Tower Merger (in case not using e-flow algorithm)
###################################################

module Merger Calorimeter {
# add InputArray InputArray
  add InputArray ECal/ecalTowers
  add InputArray HCal/hcalTowers
  set OutputArray towers
}




#####################
# Neutrino Filter
#####################

module PdgCodeFilter NeutrinoFilter {

  set InputArray Delphes/stableParticles
  set OutputArray filteredParticles

  set PTMin 0.0

  add PdgCode {12}
  add PdgCode {14}
  add PdgCode {16}
  add PdgCode {-12}
  add PdgCode {-14}
  add PdgCode {-16}

}


#####################
# MC truth jet finder
#####################

module FastJetFinder GenJetFinder05 {
  set InputArray NeutrinoFilter/filteredParticles

  set OutputArray jets

  # algorithm: 1 CDFJetClu, 2 MidPoint, 3 SIScone, 4 kt, 5 Cambridge/Aachen, 6 antikt
  set JetAlgorithm 6
  set ParameterR 0.5

  set JetPTMin 2.0
}


module FastJetFinder GenJetFinder10 {
  set InputArray NeutrinoFilter/filteredParticles

  set OutputArray jets

  # algorithm: 1 CDFJetClu, 2 MidPoint, 3 SIScone, 4 kt, 5 Cambridge/Aachen, 6 antikt
  set JetAlgorithm 6
  set ParameterR 1.0

  set JetPTMin 2.0
}



############
# Jet finder
############

module FastJetFinder FastJetFinder05 {
  set InputArray Calorimeter/towers

  set OutputArray jets

  # algorithm: 1 CDFJetClu, 2 MidPoint, 3 SIScone, 4 kt, 5 Cambridge/Aachen, 6 antikt
  set JetAlgorithm 6
  set ParameterR 0.5

  set JetPTMin 3.0
}


module FastJetFinder FastJetFinder10 {
  set InputArray Calorimeter/towers

  set OutputArray jets

  # algorithm: 1 CDFJetClu, 2 MidPoint, 3 SIScone, 4 kt, 5 Cambridge/Aachen, 6 antikt
  set JetAlgorithm 6
  set ParameterR 1.0

  set JetPTMin 3.0
}





##################
# ROOT tree writer
##################

module TreeWriter TreeWriter {

# add Branch InputArray BranchName BranchClass

  add Branch Delphes/allParticles Particle GenParticle

  add Branch ECal/ecalTowers ECal Tower
  add Branch HCal/hcalTowers HCal Tower

  add Branch Calorimeter/towers Tower Tower

  add Branch GenJetFinder05/jets GenJet05 Jet
  add Branch GenJetFinder10/jets GenJet10 Jet

  add Branch FastJetFinder05/jets Jet05 Jet
  add Branch FastJetFinder10/jets Jet10 Jet

}


#set RandomSeed 2



