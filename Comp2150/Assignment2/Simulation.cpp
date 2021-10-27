
#include "Simulation.h"
#include "PartArrival.h"
#include <iostream>
Simulation::Simulation() {}

// you need methods to manipulate product and part queues.
// [add them here.]

int Simulation::getSimulationTime() {return simulationTime;}
void Simulation::setSimulationTime(int time) { this->simulationTime = time;}

void Simulation::runSimulation(char *fileName) {
    int time;
    int part;

    //open file
    ifile.open(fileName);
    //initialize all queues (stations are on by default
    this->startQueue();


    //pull the line from input file
    string line;
    getline(ifile,line);
    //cout << line;
    //store times into variables
    mainAssemblyTime = token1(line);
    finishingAssemblyTime = token2(line);
   // cout << finishingAssemblyTime;
    while(getline(ifile, line)) {
        time = token1(line);
        part = token2(line);

        //set simulation time
        this->setSimulationTime(time);
       // cout << time<< endl;
        //trigger an event
        //add it to the priority queue
        getNextArrival(part);
        while(!eventList->isEmpty())
        {
            Event* p = dynamic_cast<Event *>(eventList->dequeue());
            p->processEvent();
        }
      //  cout<< mainBusy;



      // partQueues[part]->enqueue(new ListItem());

        //cout <<line.length()-1<< endl;
    }
    /*for(int i = 0; i <3; i++)
        cout<< partQueues[i]->getSize()<< endl;
    //both stations are not busy by default so set them to true
    setMainStatus(mainBusy);
    setFinishingStatus(finishingBusy);
    int o= 5000;
    cout << mainBusy;
   // Simulation* t = new Simulation();
    Event* p = new PartArrival(time, this, part);
    addEvent(p);
    p= new PartArrival(10, this, o);
    int i;
    this->setSimulationTime(1699);

    eventList->enqueue(p);
    Event* t = new PartArrival(1006969, this, part);
    t->compareTo(p);*/
}

// add an event to event queue.
void Simulation::addEvent(Event * theEvent) {
   // cout << theEvent->getSimTime() << endl;
    //theEvent->processEvent();
    eventList->enqueue(theEvent);
}

void Simulation::getNextArrival(int partNum) {
    PartArrival* arrival = new PartArrival(simulationTime, this, partNum);
    addEvent(arrival);
}

// getters and setters for station statuses.
bool Simulation::isMainBusy() {return this->mainBusy;}
bool Simulation::isFinishingBusy() {return this->finishingBusy;}
void Simulation::setMainStatus(bool status) { mainBusy = status;}
void Simulation::setFinishingStatus(bool status) {finishingBusy = status;}

void Simulation::startQueue() {
    int products = 3;
    eventList = new PriorityQueue();
    productQueue = new Queue();
    partQueues = new Queue*[products];
    for(int i=0; i<products; i++)
        partQueues[i] = new Queue;
    cout<< "all queues init" <<endl;
}

int Simulation::token1(string line) {
    int time = stoi(line.substr(0, line.length()-2));

    return time;
}

int Simulation::token2(string line) {
    int part =stoi(line.substr(line.length()-1, line.length()-1));
    return part;
}

PriorityQueue* Simulation::getEventList() {
    return eventList;
}

void Simulation::insertPart(int part) {
this->partQueues[part]->enqueue(new ListItem);
}

bool Simulation::partAvailable(int part) {
    bool checkAvail = false;
    int partNeeded= 0;
    if(part == 0 || part == 1)
    {
        if(part == 0) {
            //we are searching for part 1
            partNeeded = 1;
        }

        else {
            //searching for part 0
            partNeeded = 0;
        }
        checkAvail = !partQueues[partNeeded]->isEmpty();

    }
    else if(part == 2)
    {
        //check if partially assembled is empty
        checkAvail = !productQueue[0].isEmpty();
    }
    return checkAvail;
}

int Simulation::getAssemblyTime(int part) {
    int time = 0;
    if(part == 3)
        //get main station time
        time = mainAssemblyTime;
    else if(part == 2)
    {
        time = finishingAssemblyTime;
    }
    return time;
}



