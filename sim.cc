//This is for creating main file
//COMANDO SH
// . geant4/geant4.10.07.p02-install/share/Geant4-10.7.2/geant4make/geant4make.sh
// echo ". ~/Documentos/root/root_src/buildroot/bin/thisroot.sh" >> ~/.bashrc

/*ROOT
new TBrowser
Hits->Draw("fX:fY","","colz")

*/


#include <iostream> 

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
    G4RunManager *runManager = new G4RunManager();
    
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    
    runManager->Initialize();
    
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    
    //Muestra el volumen vacio
    UImanager->ApplyCommand("/vis/open OGL");
    //La posicion incial del detector
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    //Muestra el volumen madre
    UImanager->ApplyCommand("/vis/drawVolume");
    //Se refresca cada vez que lo ejecutamos
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    //Nos dibuja las trayectorias
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    //Nos dibuja trayectorias acumuladas de varios eventos
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    //Muestra las líneas de campo eléctrico
    //UImanager->ApplyCommand("/vis/scene/add/electricField 50 lightArrow");
    //Tratando de activar cascada de iones
    UImanager->ApplyCommand("/process/em/auger true");
    UImanager->ApplyCommand(" /process/em/augerCascade true");
    
    
    ui->SessionStart();
 
    return 0;
}
