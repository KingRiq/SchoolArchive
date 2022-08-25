all: a3q1 a3q0

a3q1: a3q1.c
	clang -Wall -Wpedantic -Wextra -Werror -lpthread a3q1.c  -o a3q1

a3q0: a3q0.c
	clang -Wall -Wpedantic -Wextra -Werror -lpthread a3q0.c  -o a3q0

run:
	python3 taskmaker.py
	./a3q1 4 5000 tasks.txt # 4 "CPUs" With S set to 5000ms

clean:
	-rm  -f a3q1 a3q0 *.txt
