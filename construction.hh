#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
//#include "G4VSolid.hh"
//#include "G4CSGSolid.hh"
#include "G4NistManager.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"

#include "globals.hh"
#include <sstream>
#include "G4SDManager.hh"
#include "G4UniformElectricField.hh"
#include "G4UniformMagField.hh"
#include "G4MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4EquationOfMotion.hh"
#include "G4EqMagElectricField.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4ChordFinder.hh"

#include "G4ExplicitEuler.hh"
#include "G4ImplicitEuler.hh"
#include "G4SimpleRunge.hh"
#include "G4SimpleHeum.hh"
#include "G4ClassicalRK4.hh"
#include "G4HelixExplicitEuler.hh"
#include "G4HelixImplicitEuler.hh"
#include "G4HelixSimpleRunge.hh"
#include "G4CashKarpRKF45.hh"
#include "G4RKG3_Stepper.hh"

#include "G4EqMagElectricField.hh"
#include "G4UniformElectricField.hh"

//Aquí se pone el sistema de unidades, importante para usar los *cm o *m, *eV. etc.
#include "G4SystemOfUnits.hh"
 // Clases para el campo
class G4FieldManager;
class G4ChordFinder;
class G4EquationOfMotion;
class G4Mag_EqRhs;
class G4EqMagElectricField;
class G4MagIntegratorStepper;
class G4MagInt_Driver;

class G4VPhysicalVolume;
class G4LogicalVolume;

class G4VisAttributes;
//Definimos la clase del objeto detector

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction(); //Creador
    ~MyDetectorConstruction(); //Destructor

    virtual G4VPhysicalVolume* Construct();

    
    //Definimos los objetos necesarios para el campo
    G4ElectricField*         Efield[500][50];
    G4EqMagElectricField*    fEquation_1[500][50];
    G4MagIntegratorStepper*  fStepper_1[500][50];
    G4FieldManager*          fFieldMgr_1[500][50];
    G4double                 fMinStep_1[500][50];
    G4ChordFinder*           fChordFinder_1[500][50];
    G4MagInt_Driver*         fIntgrDriver_1[500][50];
    G4VSensitiveDetector*    WireDet[6];

private:
        //Volúmenes lógicos 
        int a;
        G4double V,r,Er,Ey,Ex,angle,paso,paso2,n=360,n2=5.0;
        
        G4LogicalVolume *logicTube;
        G4LogicalVolume *logicGas;
        G4LogicalVolume *logicField[500][50];
        G4LogicalVolume *logicWire[6];
        G4Tubs          *solidGajo[10];
        G4LogicalVolume *logicVeto1;
        G4LogicalVolume *logicVeto2;
        G4LogicalVolume *logicDiode2;
        G4LogicalVolume *logicDiode1;
	G4VisAttributes *tubeVisAtt;
	G4VisAttributes *GVisAtt;
	G4VisAttributes *GasVis;
	G4LogicalVolume *logicTapa;
	G4LogicalVolume *logicParedCorta;
	G4LogicalVolume *logicParedLarga;
    	G4bool fCheckOverlaps;
    	//Field and sensitive detectors
        virtual void ConstructSDandField();
};

#endif
