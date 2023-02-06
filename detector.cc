#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();
    
    //Para que misma particula no se propague una vez sea detectada en la superficie
    //track->SetTrackStatus(fStopAndKill);
    
    //Cuando la particula entra, tiene un punto inicial y un punto final
    //Se supone que es mas complicado 
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posParticle = preStepPoint->GetPosition();

    G4String particleType = aStep->GetTrack()->GetDefinition()->GetParticleName();
    //Imprimimos el nombre de la particula
    //G4cout << "Particula: "<< particleType << G4endl;
    //if(particleType == "mu-" || particleType == "mu+") return true;
    if(particleType == "opticalPhoton") return true;

    
    //Imprimimos el resultado
    //G4cout << "Posicion de la particula: "<< posParticle << G4endl;
    //G4cout << "z: "<< posParticle[2] << G4endl;

    //Para saber la energia de la particula
    G4double edep = aStep->GetTotalEnergyDeposit();
    
    
   //Queremos saber en que celda se detecto.

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4int copyNo = touchable->GetCopyNumber();

    //G4cout << "Copy number: "<< copyNo << G4endl;    

    //Posicion del detector
    
    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    //G4cout << "Detector position: " << posDetector << G4endl;
    //Siempre que se añada otra columna en run.cc se debe declarar aqui
    
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0, evt);
    man->FillNtupleDColumn(1, posDetector[0]);
    man->FillNtupleDColumn(2, posDetector[1]);
    man->FillNtupleDColumn(3, posDetector[2]);
    man->FillNtupleDColumn(4, edep/MeV);
    man->AddNtupleRow(0); 
 
    return true;  
}
//#########################FIBRAS DETECTORAS#####################################
WSensitiveDetector::WSensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

WSensitiveDetector::~WSensitiveDetector()
{}

G4bool WSensitiveDetector::ProcessHits(G4Step *aStep2, G4TouchableHistory *ROhist2)
{
    G4Track *track2 = aStep2->GetTrack();
    
    //Para que misma particula no se propague una vez sea detectada en la superficie
    track2->SetTrackStatus(fStopAndKill);
    
    //Cuando la particula entra, tiene un punto inicial y un punto final
    //Se supone que es mas complicado 
    G4StepPoint *preStepPoint2 = aStep2->GetPreStepPoint();
    G4StepPoint *postStepPoint2 = aStep2->GetPostStepPoint();

    G4ThreeVector posParticle2 = preStepPoint2->GetPosition();

    G4String particleType2 = aStep2->GetTrack()->GetDefinition()->GetParticleName();
    //Imprimimos el nombre de la particula
    G4cout << "Particula: "<< particleType2 << G4endl;
    if(particleType2 == "e-") return true;

    
    //Imprimimos el resultado
    //G4cout << "Posicion de la particula: "<< posParticle << G4endl;
    //G4cout << "z: "<< posParticle[2] << G4endl;

    //Queremos saber la energia de la particula
    //G4double edep = aStep->GetTotalEnergyDeposit();
    //G4cout << "Energia: "<< edep/MeV << G4endl;
    
   //Queremos saber en que celda se detecto.

    const G4VTouchable *touchable2 = aStep2->GetPreStepPoint()->GetTouchable();

    G4int copyNo2 = touchable2->GetCopyNumber();

    G4cout << "Copy number: "<< copyNo2 << G4endl;    

    //Posicion del detector
    
    G4VPhysicalVolume *physVol2 = touchable2->GetVolume();
    G4ThreeVector posDetector2 = physVol2->GetTranslation();

    //G4cout << "Detector position: " << posDetector << G4endl;
    //Siempre que sevañada otra columna en run.cc semdebe declarar aqui
    
    G4int evt2 = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    
    G4AnalysisManager *man2 = G4AnalysisManager::Instance();
    man2->FillNtupleIColumn(0, evt2);
    man2->FillNtupleDColumn(1, posDetector2[0]);
    man2->FillNtupleDColumn(2, posDetector2[1]);
    man2->FillNtupleDColumn(3, posDetector2[2]);
    //man->FillNtupleDColumn(4, edep/MeV);
    man2->AddNtupleRow(0); 
 
    return true;  
}



