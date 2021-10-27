//
// Created by Eriq Hampton on 7/22/20.
//

#ifndef ASSIGNMENT2_PARTARRIVAL_H
#define ASSIGNMENT2_PARTARRIVAL_H


#include "Event.h"

class PartArrival: public Event {
private:
    int partNumber;
public:
    PartArrival(int theTime, Simulation* theSim, int partNum);
    void processEvent();
    int getPart();
};


#endif //ASSIGNMENT2_PARTARRIVAL_H
