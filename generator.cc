#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	//En parentesis va el numero de particulas por evento, cada run en Geant4 contiene varios eventos, y cada evento varias particulas, vamos a colocar una particula por evento y un run sera la combinacion de varios eventos
	fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	CLHEP::HepRandom::setTheSeed((unsigned)clock());
	//Aqui definimos el tipo de particula que deseamos utilizar, y esto es lo ultimo que tenemos que hacer
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	//Por ejemplo, deseamos muones negativos
	G4String particleName="mu+";
	//Obtenemos las propiedades de esa particula
	G4ParticleDefinition *particle = particleTable->FindParticle("mu+");
	
	
	//Generamos una particula en una posicion aleatoria
	G4double px = (G4UniformRand()-G4UniformRand());
	G4double pz = (G4UniformRand()-G4UniformRand());
	//G4ThreeVector pos(5.0*px*cm,7.0*cm,5.0*pz*cm);
	G4ThreeVector pos(-2.0*cm,7.0*cm,0);
	//Definimos que tiene una direccion de momento aleatoria
	G4double pxx = (G4UniformRand()-G4UniformRand());
	G4double pzz = (G4UniformRand()-G4UniformRand());
	//G4ThreeVector mom(1.*pxx,-1.,1.*pzz);
	G4ThreeVector mom(0.1,-0.9,0);
	//G4double EnergyRest = 105.7*MeV;
	
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(4.0*GeV);
	//fParticleGun->SetParticleEnergy(4.*GeV);
	fParticleGun->SetParticleDefinition(particle);
	
	fParticleGun->GeneratePrimaryVertex(anEvent);
}
