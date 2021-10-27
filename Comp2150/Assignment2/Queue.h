#pragma once
#include "ListItem.h"
class Node;

class Queue : public ListItem{
private:
        Node *front; // front of queue.
        Node *back; // back of queue
        int size; // size of queue.
public:
        Queue(); 
        int getSize(); // how many elements are in queue?
        bool isEmpty(); // is queue empty?
        void enqueue(ListItem *item); // add item to queue.
        ListItem *getFront(); // look at first item in queue.
        ListItem *dequeue(); // remove first item from queue. 
	~Queue();
}; // class Queue
