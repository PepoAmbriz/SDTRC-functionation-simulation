#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"

#include "g4root.hh"
//#include "G4AnalysisManager.hh"

//Estoy agregando sensibilidad al detector
class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();
    
private:
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};


//Fibras detectoras
class WSensitiveDetector : public G4VSensitiveDetector
{
public:
    WSensitiveDetector(G4String);
    ~WSensitiveDetector();
    
private:
	virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};


#endif
