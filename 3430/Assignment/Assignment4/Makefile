all: exfat

exfat: exfat.c
	clang -Wall -Wpedantic -Wextra -Werror exfat.c  -o exfat

run:
	./exfat a4image.exfat info
	./exfat a4image.exfat list
	./exfat a4image.exfat get text/numbers/300.txt

	
clean:
	-rm -f exfat *.img *.txt *.exfat
