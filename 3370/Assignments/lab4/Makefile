all: fsck-exfat

fsck-exfat: fsck-exfat.c
	clang -Wall -Wpedantic -Wextra -Werror -std=c11 fsck-exfat.c  -o fsck-exfat

run:
	./fsck-exfat exfat-empty-consistent.img
	
clean:
	-rm -f fsck-exfat *.img

