#include "ObjectManager.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  char *ptr;
  int i;
  int id1,id2,id3,id4,id5;
  initPool();
  
  id1= insertObject(100);
  id2 = insertObject(4000);
  id3 = insertObject(20200);
//	id4 = insertObject(499989);
	id4 = insertObject(499988);
	
	 id5 = insertObject(1);
//dumpPool();
//destroyPool();
dumpPool();

  ptr = (char*)retrieveObject(id1);
  for (i = 0; i < 100; i++)
    ptr[i] = (char)(i%26 + 'A');
    for (i = 0; i < 100; i++)
    fprintf(stderr,"%c",ptr[i]);
printf("\n");

/* ptr=(char*) retrieveObject(id3);
 for(i=0; i < 20200; i++)
	ptr[i] = (char)(i%26 + 'A');
for (i = 0; i < 20200; i++)
    fprintf(stderr,"%c",ptr[i]);
 ptr = (char*)retrieveObject(id1);
printf("\n");
for (i = 0; i < 100; i++)
    fprintf(stderr,"%c",ptr[i]);*/
dropReference(id4);
id5 = insertObject(1);
id1 = insertObject(50000);
id2 = insertObject(449986);
id5 = insertObject(1);
id3 = insertObject(1);
dumpPool();
/*dumpPool();
destroyPool();
dumpPool();*/
/*  id2 = insertObject(4000);
  id3 = insertObject(20200);
  dropReference(id3);
  id3 = insertObject(10);
  
  ptr = (char*)retrieveObject(id1);
  for (i = 0; i < 100; i++)
    fprintf(stderr,"%c",ptr[i]);
  fprintf(stderr,"\n");
  
  dumpPool();
  destroyPool();
  fprintf(stderr,"---\n");*/
  return 0;
}

