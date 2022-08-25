#pragma once
#include "Simulation.h"
#include "OrderedItem.h"

/**** Event abstract interface */
class Event: public OrderedItem {
private:
        int eventTime; // time of the event.
protected: 
        Simulation* sim; // simulation event is a part of.
public:
        Event(int theTime, Simulation* sim);
        virtual void processEvent() = 0; // polymorphic method for events. 
        virtual ~Event();
        int getTime();
        int getSimTime() {return sim->getSimulationTime();}
        int compareTo(OrderedItem *other); // you must implement this.
}; // class Event
