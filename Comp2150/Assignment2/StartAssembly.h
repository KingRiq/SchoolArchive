//
// Created by Eriq Hampton on 7/22/20.
//

#ifndef ASSIGNMENT2_STARTASSEMBLY_H
#define ASSIGNMENT2_STARTASSEMBLY_H


#include "PartArrival.h"

class StartAssembly: public PartArrival{
public:
    StartAssembly(int theTime, Simulation* theSim, int partNum);
    void processEvent();

};


#endif //ASSIGNMENT2_STARTASSEMBLY_H
