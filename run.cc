#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    //Vamos a crear un archivo nuevo siempre que se ejecute
    //Esta funcion se incluye en root
    G4AnalysisManager *man = G4AnalysisManager::Instance();
   
    
    man->OpenFile("outputVetos.root"); //nombre del archivo de salida
   
    //Que tipo de informacion nos gustaria guardar
    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvent");//la I de IColumn es de integer, D de double
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->CreateNtupleDColumn("E");
    man->FinishNtuple(0);

}



void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    man->Write();
    man->CloseFile();
    
}

MyRunAction1::MyRunAction1()
{}

MyRunAction1::~MyRunAction1()
{}

void MyRunAction1::BeginOfRunAction(const G4Run*)
{
    G4AnalysisManager *man2 = G4AnalysisManager::Instance();
    man2->OpenFile("outputWires.root"); //nombre del archivo de salida
    
    //Que tipo de informacion nos gustaria guardar
    man2->CreateNtuple("Hits1", "Hits1");
    man2->CreateNtupleIColumn("fEvent1");//la I de IColumn es de integer, D de double
    man2->CreateNtupleDColumn("fX1");
    man2->CreateNtupleDColumn("fY1");
    man2->CreateNtupleDColumn("fZ1");
    //man2->CreateNtupleDColumn("E");
    man2->FinishNtuple(0);
}



void MyRunAction1::EndOfRunAction(const G4Run*)
{
    
    G4AnalysisManager *man2 = G4AnalysisManager::Instance();
    
    man2->Write();
    man2->CloseFile();
}


