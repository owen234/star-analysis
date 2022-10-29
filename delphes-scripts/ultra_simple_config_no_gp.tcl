set ExecutionPath {
  ParticlePropagator

  NeutrinoFilter
  GenJetFinder

  TreeWriter
}


module ParticlePropagator ParticlePropagator {
    set InputArray Delphes/stableParticles
    set OutputArray stableParticles
    set ChargedHadronOutputArray chargedHadrons
    set ElectronOutputArray electrons

    # radius of the magnetic field coverage, in m                                                          
    set Radius 1.5
    # half-length of the magnetic field coverage, in m                                                     
    set HalfLength 1.20
    # magnetic field                                                                                       
    set Bz 1.16
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

module FastJetFinder GenJetFinder {
  set InputArray NeutrinoFilter/filteredParticles

  set OutputArray jets

  # algorithm: 1 CDFJetClu, 2 MidPoint, 3 SIScone, 4 kt, 5 Cambridge/Aachen, 6 antikt                      
  set JetAlgorithm 6
  set ParameterR 1.0

  set JetPTMin 3.0
}

module TreeWriter TreeWriter {

  # add Branch Delphes/allParticles Particle GenParticle


  add Branch GenJetFinder/jets GenJet Jet

}


