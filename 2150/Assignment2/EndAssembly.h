//
// Created by Eriq Hampton on 7/22/20.
//

#ifndef ASSIGNMENT2_ENDASSEMBLY_H
#define ASSIGNMENT2_ENDASSEMBLY_H


#include "PartArrival.h"

class EndAssembly: PartArrival{
public:
    EndAssembly(int theTime, Simulation* theSim, int partNum);
    void processEvent();
};


#endif //ASSIGNMENT2_ENDASSEMBLY_H
