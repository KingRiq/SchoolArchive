#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>

void handle(int arg) {
	char* insults [] = {
		"GO AWAY",
		"NO",
		"Ah ah ah, you didn't say the magic word..."
	};
	int r = rand() % (sizeof(insults)/sizeof(char*));
	printf("%s\n", insults[r]);
}
int main(int argc, char *argv[]) {
	srand(time(NULL));
	signal(SIGINT, handle);
	while (1);
	return 0;
}

