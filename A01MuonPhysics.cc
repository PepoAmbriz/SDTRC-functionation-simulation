#include "A01MuonPhysics.hh"

#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>


A01MuonPhysics::A01MuonPhysics(const G4String& name)
                   :  G4VPhysicsConstructor(name)
{
}

A01MuonPhysics::~A01MuonPhysics()
{
}

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4TauMinus.hh"
#include "G4TauPlus.hh"
#include "G4NeutrinoTau.hh"
#include "G4AntiNeutrinoTau.hh"
#include "G4NeutrinoMu.hh"
#include "G4AntiNeutrinoMu.hh"

#include "G4VEmProcess.hh"
#include "G4BraggModel.hh"

void A01MuonPhysics::ConstructParticle()
{
  // Mu
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();

  // Tau
  G4TauMinus::TauMinusDefinition();
  G4TauPlus::TauPlusDefinition();
  G4NeutrinoTau::NeutrinoTauDefinition();
  G4AntiNeutrinoTau::AntiNeutrinoTauDefinition();

}

/*void A01MuonPhysics::ConstructModel()
{
    G4MuIonisation::InitialiseEnergyLossProcess("mu-", "e-");
} */


#include "G4ProcessManager.hh"

void A01MuonPhysics::ConstructProcess()
{
   G4ProcessManager * pManager = 0;

   //Muon+
   pManager = G4MuonPlus::MuonPlus()->GetProcessManager();
   G4VProcess* thempMultipleScattering = new G4MuMultipleScattering();
   G4VProcess* thempBremsstrahlung     = new G4MuBremsstrahlung();
   G4VProcess* thempPairProduction     = new G4MuPairProduction();
   G4VProcess* thempIonisation        = new G4MuIonisation();
   //G4VEmProcess* thempIonisationModel = new void SetEmModel(new G4BraggModel(),1);
   //Este no
   //pManager->SetEmModel(thempIonisation, new G4MuBetheBlochModel());
   //
   // add processes
   pManager->AddProcess(thempIonisation);
   pManager->AddProcess(thempMultipleScattering);
   pManager->AddProcess(thempBremsstrahlung);
   pManager->AddProcess(thempPairProduction);
   //
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thempMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thempIonisation,        idxAlongStep,2);
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thempMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thempIonisation,        idxPostStep,2);
   pManager->SetProcessOrdering(thempBremsstrahlung,     idxPostStep,3);
   pManager->SetProcessOrdering(thempPairProduction,     idxPostStep,4);

   //Muon-
   G4VProcess* themmMultipleScattering = new G4MuMultipleScattering();
   G4VProcess* themmBremsstrahlung     = new G4MuBremsstrahlung();
   G4VProcess* themmPairProduction     = new G4MuPairProduction();
   G4VProcess* themmIonisation        = new G4MuIonisation();
   //
   // add processes
   pManager->AddProcess(themmIonisation);
   pManager->AddProcess(themmMultipleScattering);
   pManager->AddProcess(themmBremsstrahlung);
   pManager->AddProcess(themmPairProduction);
   //
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(themmMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(themmIonisation,        idxAlongStep,2);
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(themmMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(themmIonisation,        idxPostStep,2);
   pManager->SetProcessOrdering(themmBremsstrahlung,     idxPostStep,3);
   pManager->SetProcessOrdering(themmPairProduction,     idxPostStep,4);
 
   // Tau+ Physics
   //pManager = G4TauPlus::TauPlus()->GetProcessManager();
   //G4VProcess* thetpMultipleScattering = new G4hMultipleScattering();
   //G4VProcess* thetpIonisation        = new G4hIonisation();
   //
   // add processes
   //pManager->AddProcess(thetpIonisation);
   //pManager->AddProcess(thetpMultipleScattering);
   //
   // set ordering for AlongStepDoIt
   //pManager->SetProcessOrdering(thetpMultipleScattering, idxAlongStep,1);
   //pManager->SetProcessOrdering(thetpIonisation,        idxAlongStep,2);
   //
   // set ordering for PostStepDoIt
   //pManager->SetProcessOrdering(thetpMultipleScattering, idxPostStep,1);
   //pManager->SetProcessOrdering(thetpIonisation,        idxPostStep,2);

   // Tau- Physics
   //pManager = G4TauMinus::TauMinus()->GetProcessManager();
   //G4VProcess* thetmMultipleScattering = new G4hMultipleScattering();
   //G4VProcess* thetmIonisation        = new G4hIonisation();
   //
   // add processes
   //pManager->AddProcess(thetmIonisation);
   //pManager->AddProcess(thetmMultipleScattering);
   //
   // set ordering for AlongStepDoIt
   //pManager->SetProcessOrdering(thetmMultipleScattering, idxAlongStep,1);
   //pManager->SetProcessOrdering(thetmIonisation,        idxAlongStep,2);
   //
   // set ordering for PostStepDoIt
   //pManager->SetProcessOrdering(thetmMultipleScattering, idxPostStep,1);
   //pManager->SetProcessOrdering(thetmIonisation,        idxPostStep,2);

}
