#pragma once
#include "ListItem.h"

class OrderedItem : public ListItem {
public:
        virtual int compareTo(OrderedItem *other) = 0;
	virtual ~OrderedItem();
}; // class ListItem
