all: atomic-lock condition-vars lock-really spin-lock pthread-lock

atomic-lock: atomic-lock.c
	clang -Wall -Wpedantic -Wextra -Werror -lpthread atomic-lock.c  -o atomic-lock

condition-vars: condition-vars.c
	clang -Wall -Wpedantic -Wextra -Werror -lpthread condition-vars.c  -o condition-vars

lock-really: lock-really.c
	clang -Wall -Wpedantic -Wextra -Werror -lpthread lock-really.c  -o lock-really

spin-lock: spin-lock.c
	clang -Wall -Wpedantic -Wextra -Werror -lpthread spin-lock.c  -o spin-lock

pthread-lock: pthread-lock.c
	clang -Wall -Wpedantic -Wextra -Werror -lpthread pthread-lock.c  -o pthread-lock

run:
	strace -o spin_lock.txt ./spin-lock
	strace -o atomic-lock.txt ./atomic-lock  
	strace -o lock-really.txt ./lock-really 
	strace -o pthread-lock.txt ./pthread-lock
	./condition-vars

time:	
	time ./spin-lock
	time ./atomic-lock
	time ./lock-really
	time ./pthread-lock
	

clean:
	-rm atomic-lock condition-vars lock-really spin-lock *.txt pthread-lock

