#include "physics.hh" 
#include "G4MuIonisation.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4ios.hh"
#include <iomanip>

#include "A01MuonPhysics.hh"
#include "A01EMPhysics.hh"


//#include "PhysListEmStandard.hh"

//#include "LXeOpticalPhysics.hh"

MyPhysicsList::MyPhysicsList()
{
	//Mediciones electromagneticas
	RegisterPhysics(new G4EmStandardPhysics_option4());
	//Fenoemenos opticos
	RegisterPhysics(new G4OpticalPhysics());
	//RegisterPhysics(new LXeOpticalPhysics("optical"));
	// Muon Physics
	RegisterPhysics(new A01MuonPhysics("muon"));
	// EM Physics
	//RegisterPhysics(new A01EMPhysics("EM"));
	//RegisterPhysics(new PhysListEmStandard("standard"));
	
}

MyPhysicsList::~MyPhysicsList()
{}



