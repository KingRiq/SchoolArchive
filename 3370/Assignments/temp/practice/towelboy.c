#include <stdio.h>
#include <ctype.h>

int main(void) {
	int letter;
	letter = getchar();
	letter = tolower(letter);
	while (letter != EOF) {
		putchar(letter);
		letter = getchar();
		letter = tolower(letter);
	}
}
