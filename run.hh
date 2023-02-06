#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4UserRunAction.hh"

#include "g4root.hh"
//#include "G4AnalysisManager.hh"

class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction();
    ~MyRunAction();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

class MyRunAction1 : public G4UserRunAction
{
public:
    MyRunAction1();
    ~MyRunAction1();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif
