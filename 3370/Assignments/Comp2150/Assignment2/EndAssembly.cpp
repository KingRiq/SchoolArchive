//
// Created by Eriq Hampton on 7/22/20.
//
#include <iostream>
#include "EndAssembly.h"

//End Assembly: for the main station, this event should cause a Product Arrival event to be
// scheduled immediately for the Finishing station (transportation time is assumed to be zero). If
// both parts P0 and P1 are waiting at the Main station, and the Main station is available,
// another Start Assembly event should be scheduled for the current time (at the Main station).
// For the Finishing station, the End Assembly event should calculate statistics for the
// assembly of this product (see the Output section below for more details on the statistics).

void EndAssembly::processEvent() {
    cout << "Ending Assembly Event, started at time "<< sim->getSimulationTime()<< endl;
}

EndAssembly::EndAssembly(int theTime, Simulation *theSim, int partNum) : PartArrival(theTime, theSim, partNum) {

}
//this event is tasked with printing the statistics when ending assembly for the finishing station

//void printStats()