all: a1_process_herder a1_thread_herder elf_reader 

a1_process_herder: a1_process_herder.c	
	clang -Wall -Wpedantic -Wextra -Werror a1_process_herder.c -o a1_process_herder
a1_thread_herder: a1_thread_herder.c
	clang -Wall -Wpedantic -Wextra -Werror -pthread a1_thread_herder.c -o a1_thread_herder
elf_reader: elf_reader.c
	clang -Wall -Wpedantic -Wextra -Werror  elf_reader.c -o elf_reader
	
clean:
	-rm elf_reader a1_thread_herder a1_process_herder
