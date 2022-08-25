//
// Created by Eriq Hampton on 7/22/20.
//
#include <iostream>
#include "StartAssembly.h"
#include "EndAssembly.h"
//Start Assembly: these events should cause an End Assembly event to be scheduled with a time equal
// to the current time plus the assembly time of the station.

void StartAssembly::processEvent() {
    cout << "Starting Assembly Event, started at time "<< sim->getSimulationTime() << endl;
    int endTime = this->getTime()+ sim->getAssemblyTime(this->getPart());
    cout << endTime << "END TIME"<< endl;
    EndAssembly* partAssembled = new EndAssembly(endTime, sim, this->getPart());
    partAssembled->processEvent();
   // cout << sim->isFinishingBusy()<< endl;
}

StartAssembly::StartAssembly(int theTime, Simulation *theSim, int partNum) : PartArrival(theTime, theSim, partNum) {

}


