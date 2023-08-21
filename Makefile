connectn.out: main.o setup.o play_game.o inputValidation.o
	gcc -g -Wall -Werror -o connectn.out main.o setup.o play_game.o inputValidation.o

main.o: main.c setup.h play_game.h
	gcc -g -Wall -Werror -c main.c

setup.o: setup.c setup.h
	gcc -g -Wall -Werror -c setup.c

play_game.o: play_game.c play_game.h setup.h
	gcc -g -Wall -Werror -c play_game.c

inputValidation.o: inputValidation.c
	gcc -g -Wall -Werror -c inputValidation.c

clean:
	rm -fr*.o*.out
