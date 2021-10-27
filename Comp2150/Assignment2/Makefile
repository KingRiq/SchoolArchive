A2main: Simulation.h A2main.cpp Simulation.o PartArrival.o StartAssembly.o \
	Event.o EndAssembly.o Node.o PriorityQueue.o
	clang++ -Wall A2main.cpp Simulation.o PartArrival.o StartAssembly.o \
	Event.o EndAssembly.o Node.o PriorityQueue.o -o A2main
Simulation.o: Simulation.h Simulation.cpp PartArrival.o
	clang++ -Wall Simulation.cpp -o Simulation.o -c
PartArrival.o: PartArrival.h PartArrival.cpp StartAssembly.o
	clang++ -Wall PartArrival.cpp -o PartArrival.o -c
StartAssembly.o: StartAssembly.h StartAssembly.cpp
	clang++ -Wall StartAssembly.cpp -o StartAssembly.o -c
EndAssembly.o: EndAssembly.h EndAssembly.cpp
	clang++ -Wall EndAssembly.cpp -o EndAssembly.o -c
Event.o: Event.h Event.cpp
	clang++ -Wall Event.cpp -o Event.o -c
ListItem.o: ListItem.h ListItem.cpp
	clang++ -Wall ListItem.cpp -o ListItem.o -c
OrderedItem.o: OrderedItem.h OrderedItem.cpp
	clang++ -Wall OrderedItem.cpp -o SOrderedItem.o -c
Queue.o: Queue.h Queue.cpp
	clang++ -Wall Queue.cpp -o Queue.o -c
PriorityQueue.o: PriorityQueue.h PriorityQueue.cpp
	clang++ -Wall PriorityQueue.cpp -o PriorityQueue.o -c
Node.o: Node.h Node.cpp
	clang++ -Wall Node.cpp -o Node.o -c
ProductArrival.o: ProductArrival.h ProductArrival.cpp
	clang++ -Wall ProductArrival.cpp -o ProductArrival.o -c




clean: A2main Simulation.o Event.o ListItem.o OrderedItem.o Queue.o \
	PriorityQueue.o Node.o PartArrival.o EndAssembly.o ProductArrival.o \
	StartAssembly.o
	rm A2main Simulation.o Event.o ListItem.o OrderedItem.o \
		Queue.o PriorityQueue.o Node.o PartArrival.o EndAssembly.o \
		ProductArrival.o StartAssembly.o
