all: threads processes pe

threads: threads.c
	clang -Wall -Wpedantic -Wextra -Werror threads.c -lpthread  -lcurl -o threads 
processes: processes.c
	clang -Wall -Wpedantic -Wextra -Werror processes.c -o processes  #run 1
pe: pe.c
	clang -Wall -Wpedantic -Wextra -Werror pe.c -o pe
run:
	./threads #run
	./pe putty.exe
	./processes 8
	strace -o strace_output.txt ./processes 3  #for convenience
clean:
	-rm pe processes threads your_internet_friend.jpg

