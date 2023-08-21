#include <stdio.h>
#include <stdlib.h>
#include "setup.h"
#include "play_game.h"

int main(int argc, char** argv) {
	int num_rows, num_cols, pieces_to_win;

	if (argc < 4) {
		printf("Not enough arguments entered\n");
		printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
		exit(0);
	} else if (argc > 4) {
		printf("Too many arguments entered\n");
		printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
		exit(0);
	}

	sscanf(argv[1], "%d", &num_rows);
	sscanf(argv[2], "%d", &num_cols);
	sscanf(argv[3], "%d", &pieces_to_win);

	int cur_player;
	char** board;
	char* pieces;

	setup_game(num_rows, num_cols, &board, &pieces, &cur_player);
	play_game(num_rows, num_cols, pieces_to_win, board, pieces, cur_player);
	delete_board(&board, num_rows, num_cols);
	return 0;
}
