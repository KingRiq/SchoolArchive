#include "Event.h"
#include "Simulation.h"


Event::Event(int theTime, Simulation *theSim) :eventTime(theTime), sim (theSim) {}
Event::~Event() {}
int Event::getTime(){ return eventTime; }
//void Event::setTime(int newTime) {eventTime = newTime; }

//I need this method to compare event times and add

int Event::compareTo(OrderedItem* other){
  /*  this->eventTime;
    Event* downCast = dynamic_cast<Event*>(other);
    downCast->eventTime;

*/
	return 0; // you must implement this.
}// compareTo
