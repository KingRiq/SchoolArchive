//
// Created by Eriq Hampton on 7/22/20.
//

#include "PartArrival.h"
#include "StartAssembly.h"
#include <iostream>

PartArrival::PartArrival(int theTime, Simulation* theSim, int partNum):Event(theTime, theSim){
    this->partNumber=partNum;
}

void PartArrival::processEvent() {
 std::cout << "part "<< this->getPart()<< " has arrived @"<< sim->getSimulationTime() <<endl;
 cout<< sim->partAvailable(partNumber);
 //check if main station is busy
 if(partNumber == 0 || partNumber == 1){
     cout<< "do stuff"<< endl;
     //check
     if(!sim->isMainBusy() && sim->partAvailable(partNumber))
     {
        cout << "trigger nxt event"<< endl;
        partNumber = 3; //I have designated a part number for partially assembled product
         StartAssembly* partialProduct = new StartAssembly(sim->getSimulationTime(), sim, partNumber);
         partialProduct->processEvent();
     }
     else{
         //add to queue
         sim->insertPart(partNumber);
     }

 }
 else{
     //its partnumber is 2 and assembling makes it a product so I kept the part number the same
     if(!sim->isFinishingBusy()&& sim->partAvailable(partNumber)){
         StartAssembly* partialProduct = new StartAssembly(sim->getSimulationTime(), sim, partNumber);
         partialProduct->processEvent();

         cout << sim->isFinishingBusy()<< endl;


     }
     else{
         sim->insertPart(partNumber);
     }

 }
}

int PartArrival::getPart() {
    return this->partNumber;
}
