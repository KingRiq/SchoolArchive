all: octopipe

octopipe: octopipe.c
	clang -Wall -Wpedantic -Wextra -Werror octopipe.c  -o octopipe
run:
	./octopipe "tr A-Z a-z" "tr a-z A-Z" "grep hello"
clean:
	-rm octopipe

