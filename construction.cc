#include "construction.hh"
#include "G4IonisParamMat.hh"
#include "G4MuIonisation.hh"
#include "G4MuBetheBlochModel.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "detector.hh"
#include "G4Scintillation.hh"

#include "G4AutoDelete.hh"
#include "G4RotationMatrix.hh"
#include "G4UserLimits.hh"
//Coseno y seno
#include <cmath>
#include <iostream>

using namespace std;



//Constructor
MyDetectorConstruction::MyDetectorConstruction() 
: tubeVisAtt(0),GasVis(0),GVisAtt(0),
  G4VUserDetectorConstruction(),
  logicGas(0),
 // Efield(0),
 // fEquation_1(0),
 // fStepper_1(0),
 // fFieldMgr_1(0),
 // fMinStep_1(0),
 // fChordFinder_1(0),
  fCheckOverlaps(true)
{}

//Destructor
MyDetectorConstruction::~MyDetectorConstruction()
{

delete tubeVisAtt;
delete GasVis;
delete GVisAtt;
}


G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
	
	//Parámetros
	G4double temperature = 293.15*kelvin;
	G4double pressure = 1.0*atmosphere;
	
	//Materiales en la simulación
	//Material del mundo
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	
	//Latón
	G4Material *Laton = new G4Material("Laton", 8.73*g/cm3, 2);
	Laton->AddElement(nist->FindOrBuildElement("Cu"), 60.0*perCent);
	Laton->AddElement(nist->FindOrBuildElement("Zn"), 40.0*perCent);
	
	//Metano
	G4Material *CH4 = new G4Material("CH4", 0.00067898*g/cm3, 2, kStateGas, temperature, pressure);
	CH4->AddElement(nist->FindOrBuildElement("C"), 1);
	CH4->AddElement(nist->FindOrBuildElement("H"), 4);
	
	//Gas compuesto de argón y metano
	G4Material *Gas = new G4Material("Gas", 0.0015895*g/cm3, 2, kStateGas, temperature, pressure);
	Gas->AddMaterial(CH4,10.0*perCent);
	Gas->AddElement(nist->FindOrBuildElement("Ar"),90.0*perCent);
	//Energía de ionización del Argón
	Gas->GetIonisation()->SetMeanExcitationEnergy(0.76*eV);
	
        //Aleacion oro tungsteno
	G4Material *Alambre = new G4Material("Alambre", 19.2*g/cm3, 2);
	Alambre->AddElement(nist->FindOrBuildElement("Au"),5.0*perCent);
	Alambre->AddElement(nist->FindOrBuildElement("W"),95.0*perCent);
	
	//Material nada
	G4Material *Nada = new G4Material("Nada", 0.001*g/cm3, 1);
	Nada->AddMaterial(Gas,100.0*perCent);
	
	//Materiales veto detectores
	//Aluminio
	G4Material *Aluminio = new G4Material("Aluminio", 2.7*g/cm3, 1,kStateSolid,temperature,pressure);
	Aluminio->AddElement(nist->FindOrBuildElement("Al"), 1);
	
	//Benzofenona
	G4Material *Benzofenona = new G4Material("Benzofenona", 1.1*g/cm3, 3,kStateSolid,temperature,pressure);
	Benzofenona->AddElement(nist->FindOrBuildElement("C"), 13);
	Benzofenona->AddElement(nist->FindOrBuildElement("H"), 10);
	Benzofenona->AddElement(nist->FindOrBuildElement("O"), 1);
	
	//Polímero, Polyvinyl toluene
	G4Material *Polyvinyl = new G4Material("Polyvinyl", 1.023*g/cm3, 2,kStateSolid,temperature,pressure);
	Polyvinyl->AddElement(nist->FindOrBuildElement("C"), 9);
	Polyvinyl->AddElement(nist->FindOrBuildElement("H"), 10);
	
	//Centellador
	G4Material *PlCent = new G4Material("PlCent", 1.023*g/cm3, 2,kStateSolid,temperature,pressure);
	PlCent->AddMaterial(Benzofenona,0.5*perCent);
	PlCent->AddMaterial(Polyvinyl,99.5*perCent);
      
        //Propiedades ópticas de los veto
        G4Scintillation* theScintProcess = new G4Scintillation("Scintillation");
	theScintProcess-> SetTrackSecondariesFirst(true);
	theScintProcess-> SetScintillationYieldFactor(7500.0/MeV);
	//theScintProcess-> SetResolutionScale(1.0);
	//theScintProcess-> SetScintillationTime(45 *ns);
        //Definimos la energía, con un factor de conversión, luz azul 0.2 y roja 0.9
        
        G4double energy[21] = {1.239841939*eV/0.34 ,1.239841939*eV/0.342,1.239841939*eV/0.345 ,1.239841939*eV/0.347,1.239841939*eV/0.352 ,1.239841939*eV/0.355,1.239841939*eV/0.36 ,1.239841939*eV/0.362,1.239841939*eV/0.365 ,1.239841939*eV/370,1.239841939*eV/0.375 ,1.239841939*eV/0.378,1.239841939*eV/0.385 ,1.239841939*eV/0.388,1.239841939*eV/0.392 ,1.239841939*eV/0.395,1.239841939*eV/0.4 ,1.239841939*eV/0.41,1.239841939*eV/0.42 ,1.239841939*eV/0.43,1.239841939*eV/0.44 };
        
        G4double scintarray[21]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,0.9,0.85,0.85,0.8,0.7,0.6,0.5,0.4,0.3,0.2,0.1};
        G4double rindexEJ232Q[21] = {1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58,1.58};
        G4double reflexAluminio[21]={0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.95};
	G4double rindexWorld[21] = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
	
	G4MaterialPropertiesTable *mptEJ232Q = new G4MaterialPropertiesTable();
	mptEJ232Q->AddProperty("RINDEX",energy,rindexEJ232Q,21);
	mptEJ232Q->AddProperty("SCINTILLATION",energy,scintarray,21);
	
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX",energy,rindexWorld,21);
	
	
	PlCent->SetMaterialPropertiesTable(mptEJ232Q);
	worldMat->SetMaterialPropertiesTable(mptWorld);
	
	
	//Definimos solidWorld en la mitad del tamaño del que queremos
	G4Box *solidWorld = new G4Box("solidWorld", 50.0, 80.0, 55);
	
	//Nuestro volumen logico
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	
	//Volumen fisico, el primer parametro es la rotacion, el segundo parametro es donde esta centrado, el 0 despues de "physWorld" es el volumen madre, por si estamos haciendo un volumen sobre otro
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	
	//Definimos el volumen de nuestra camarita, en este caso son los tubos acomodados en pirámide
	G4Tubs *solidTube = new G4Tubs( "solidTube",  //nombre
	                                 1.22/2*cm,   //radio interno
	                                 1.27/2*cm,   //radio externo
	                                 5.0*cm,      //largo entre 2 
	                                 0.0,         //ángulo de inicio
	                                 2.0*M_PI);   //angulo del segmento
	
	//Definimos el volumen logico
	logicTube = new G4LogicalVolume(solidTube, Laton, "logicTube");
	
	//Volumen fisico en bucle mas abajo
	
	//Volumen de gas compuesto
	G4Tubs *solidGas = new G4Tubs( "solidGas",   //nombre
	                                 0.00,       //radio interno
	                                 1.23/2*cm,  //radio externo
	                                 5.0*cm,     //largo entre 2 
	                                 0.0,        //ángulo de inicio
	                                 2.*M_PI);   //ángulo del segmento
	
	logicGas = new G4LogicalVolume(solidGas, Gas, "logicGas");
	
	//Volumen de fibras de tungsteno y oro
	G4Tubs *solidWire = new G4Tubs( "solidWire",  //nombre
	                                 0.0,         //radio interno
	                                 0.01,        //radio externo
	                                 50.0,        //largo entre 2 
	                                 0.0,         //ángulo de inicio
	                                 2.0*M_PI);   //angulo del segmento
	
	
	//Volumenes para gajos del campo
	paso=(2*M_PI) / n;
	
	for(G4int i=0;i<n2;i++)
	{
	solidGajo[i] = new G4Tubs( "solidGajo[]",  //nombre
	                                 (0.635/n2*i)*cm,         //radio interno
	                                 (0.635/n2*(i+1))*cm,   //radio externo
	                                 50.0,        //largo entre 2 
	                                 0.0,         //ángulo de inicio
	                                 paso);   //angulo del segmento
	}
	
	//Para no ver gajos
	GVisAtt = new G4VisAttributes(G4Colour(0.0,0.0, 0.0,0.0));
	               GVisAtt->SetVisibility(true);
	               
	//Voumen lógico para campos
	for(G4int k=0; k < n; k++)
	{ for(G4int l=0; l < n2; l++)
	  {
	   logicField[k][l]=new G4LogicalVolume(solidGajo[l],Gas, "logicField[][]");
	   logicField[k][l]->SetVisAttributes(GVisAtt);
	  }
	}
	
	//Bucle para posicionar todos los tubos
	
	for(G4int i=0; i < 3; i++)
	{     
		for(G4int j=0; j < 3; j++)
		{       
		        a=j+i*3;
		        if (a==6){a=5;};
		        
		        logicWire[a] = new G4LogicalVolume(solidWire, Alambre, "logicWire[]");
		        
		        G4VPhysicalVolume *physTube = new G4PVPlacement(0, G4ThreeVector((-1.27+j*1.27+i*1.27/2)*cm, (-5.0+i*2.15/2)*cm, 0.0), logicTube, "physTube", logicWorld, false, a, true);
		        G4VPhysicalVolume *physWire = new G4PVPlacement(0, G4ThreeVector((-1.27+j*1.27+i*1.27/2)*cm, (-5.0+i*2.15/2)*cm, 0.0), logicWire[a], "physWire[]", logicWorld, false, a, true);
		        G4VPhysicalVolume *physGas  = new G4PVPlacement(0, G4ThreeVector((-1.27+j*1.27+i*1.27/2)*cm, (-5.0+i*2.15/2)*cm, 0.0), logicGas,  "physGas",  logicWorld, false, a, true);
		        
		        for(G4int k=0; k < n; k++)
		        { 
		        G4RotationMatrix *GajoRotar = new G4RotationMatrix();
	 		GajoRotar->rotateZ(-k*(paso));
	 		
	 		for(G4int l=0; l < n2; l++)
	 		  {
			G4VPhysicalVolume *physGajo=new G4PVPlacement(GajoRotar,G4ThreeVector((-1.27+j*1.27+i*1.27/2)*cm,(-5.0+i*2.15/2)*cm, 0.0),logicField[k][l],"physGajo[]",logicWorld,false,0,true);
			
	              
	                 }
			}
			
			a=0;
			if (i==1)
			{
				if (j==1){break;}
			} 
			else if (i==2)
			{
				if (j==0){break;}
			}
		}	
	}
	
	
	
	//Veto y diodos multiplicadores detectores 
	G4Box *solidVeto = new G4Box("solidVeto", 25.0, 1.5, 50.0);
	G4Box *solidDiode = new G4Box("solidDiode", 1.0, 1.5, 1.5);
	
	logicVeto1 = new G4LogicalVolume(solidVeto, PlCent ,"logicVeto1");
        logicVeto2 = new G4LogicalVolume(solidVeto, PlCent ,"logicVeto2");
        logicDiode1 = new G4LogicalVolume(solidDiode, worldMat ,"logicDiode1");
        logicDiode2 = new G4LogicalVolume(solidDiode, worldMat ,"logicDiode2");
        
        //Recubrimiento de aluminio
        G4Box *solidTapa = new G4Box("solidTapa", 25.1, 0.1, 50.1);
        G4Box *solidParedCorta = new G4Box("solidParedCorta", 0.1, 1.5, 50.0);
        G4Box *solidParedLarga = new G4Box("solidParedLarga", 25.1, 1.5, 0.1);
        
        logicTapa = new G4LogicalVolume(solidTapa, Aluminio ,"LogicTapa");
        logicParedCorta = new G4LogicalVolume(solidParedCorta, Aluminio ,"logicParedCorta");
        logicParedLarga = new G4LogicalVolume(solidParedLarga, Aluminio ,"logicParedLarga");
        
        //Óptica del aluminio
        G4OpticalSurface* OpAluminiumSurface = new G4OpticalSurface("AluminiumSurface");
	
	G4LogicalSkinSurface* AluminiumSurface = new G4LogicalSkinSurface("AluminiumSurface",logicTapa,OpAluminiumSurface);
	G4LogicalSkinSurface* AluminiumSurface2 = new G4LogicalSkinSurface("AluminiumSurface2",logicParedCorta,OpAluminiumSurface);
	G4LogicalSkinSurface* AluminiumSurface3 = new G4LogicalSkinSurface("AluminiumSurface3",logicParedLarga,OpAluminiumSurface);
	
	OpAluminiumSurface -> SetFinish(polishedfrontpainted);
        G4MaterialPropertiesTable *mptAluminio= new G4MaterialPropertiesTable();
	mptAluminio->AddProperty("REFLECTIVITY",energy,reflexAluminio,21);
	
	OpAluminiumSurface->SetMaterialPropertiesTable(mptAluminio);
	
	
	//Posicionamiento de vetos
	G4VPhysicalVolume *physVeto1 = new G4PVPlacement(0, G4ThreeVector(0, (-6.635)*cm, 0.0*cm), logicVeto1, "physVeto1", logicWorld, false, 0, true);
	G4VPhysicalVolume *physDiode1 = new G4PVPlacement(0, G4ThreeVector(25, (-6.635)*cm, 0.0*cm), logicDiode1, "physDiode1", logicWorld, false, 0, true);
	G4VPhysicalVolume *physVeto2 = new G4PVPlacement(0, G4ThreeVector(0, (-6.635+5)*cm, 0.0*cm), logicVeto2, "physVeto2", logicWorld, false, 0, true);
	G4VPhysicalVolume *physDiode2 = new G4PVPlacement(0, G4ThreeVector(25, (-6.635+5)*cm, 0.0*cm), logicDiode2, "physDiode2", logicWorld, false, 0, true);
	for(G4int j=0 ; j<2 ; j++)
	{
	  for(G4int i=0 ; i<2 ; i++)
	  {
	    G4VPhysicalVolume *physTapa = new G4PVPlacement(0, G4ThreeVector(0, (-66.35-1.6+3.2*i+50*j), 0.0), logicTapa, "physTapa", logicWorld, false, i, true);
	    G4VPhysicalVolume *physParedCorta = new G4PVPlacement(0, G4ThreeVector(-25.1+50.2*i, (-66.35+50*j), 0.0), logicParedCorta, "physParedCorta", logicWorld, false, i, true);
	    G4VPhysicalVolume *physParedLarga = new G4PVPlacement(0, G4ThreeVector(0, (-66.35+50*j), -50.1+100.2*i), logicParedLarga, "physParedLarga", logicWorld, false, i, true);
	  }
	}
	
	//****************** User Limits... to see all the electrons with low energy********************************
	
	G4UserLimits* UserLimits =  new G4UserLimits( "e-",       //Particle type
	                                              0.00001*mm, //max step
                                                      10.0*m,     //Track lenght
                                                      10.0*s,     //Time
                                                      0.001 *eV,       //min kinetic energy
                                                      10.0     //Min remaining range
                                                       );     
	logicWorld -> SetUserLimits(UserLimits);

	
	
	
	//Para visualizacioes
	tubeVisAtt = new G4VisAttributes(G4Colour(0.8,0.64, 0.32));
	tubeVisAtt->SetForceSolid(true);
	tubeVisAtt->SetVisibility(true);
	logicTube->SetVisAttributes(tubeVisAtt);
	
	GasVis = new G4VisAttributes(G4Colour(0.51,2.55, 0.51,0.3));
	GasVis->SetForceSolid(true);
	GasVis->SetVisibility(true);
        logicGas->SetVisAttributes(GasVis);
        
        //Regresa el volúmen físico
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet1 = new MySensitiveDetector("SensitiveDetector");
	MySensitiveDetector *sensDet2 = new MySensitiveDetector("SensitiveDetector");
	logicDiode1 -> SetSensitiveDetector(sensDet1); 
	logicDiode2 -> SetSensitiveDetector(sensDet2);
	
	//Fibras detectoras
	for(G4int i=0 ; i<6 ; i++)
	{
	WireDet[i] = new WSensitiveDetector("WSensitiveDetector");
	logicWire[i] -> SetSensitiveDetector(WireDet[i]);
	}
	
	
	//CAMPO
	G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  	//---------------------------------------------------------
  	V=1800.0*volt;
  	paso2=(6.35/n2)*mm;
  	
	   for(G4int j=0; j < n; j++)
	     {
	        for(G4int k=0; k < n2; k++)
	        {
	        
	        r=(paso2*k+paso2/2);
	        Er=V/r;
	        
	        angle=paso*j+paso/2 ;
	        
	        Ex=Er*std::cos(angle);
	        Ey=Er*std::sin(angle);
	        
	  	Efield[j][k] = new G4UniformElectricField(G4ThreeVector(Ex, Ey, 0.0));
	  	// Create an equation of motion for this field
	  	fEquation_1[j][k] = new G4EqMagElectricField(Efield[j][k]);
	  	fStepper_1[j][k] = new G4ClassicalRK4(fEquation_1[j][k],12);

	  	fFieldMgr_1[j][k] = new G4FieldManager(Efield[j][k]);
	  	
	  	logicField[j][k]->SetFieldManager(fFieldMgr_1[j][k],true);
		
	  	fMinStep_1[j][k] = 0.00010*mm ; // minimal step of 10 microns
	  	
	  	fIntgrDriver_1[j][k] = new G4MagInt_Driver(fMinStep_1[j][k],fStepper_1[j][k],fStepper_1[j][k]->GetNumberOfVariables());

	  	fChordFinder_1[j][k] = new G4ChordFinder(fIntgrDriver_1[j][k]);
	  	fFieldMgr_1[j][k]->SetChordFinder(fChordFinder_1[j][k]);
	  	
	  	}
	    }
  	
  	
}




