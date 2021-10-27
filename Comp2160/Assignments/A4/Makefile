main: ObjectManager.h main0.c ObjectManager.o
	clang -Wall main0.c ObjectManager.o -o main
ObjectManager.o: ObjectManager.h ObjectManager.c
	clang -Wall ObjectManager.c -o ObjectManager.o -c
clean: ObjectManager.o main
	rm ObjectManager.o main
