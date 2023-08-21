#ifndef SETUP_H
	#define SETUP_H

		#include <stdbool.h>

		void setup_game(int num_rows, int num_cols, char** *out_board, char* *out_pieces,
										int* out_cur_player);
		char** make_board(int num_rows, int num_cols);
		char* players_pick_pieces(int num_players);
		int pick_who_goes_first();
		void print_board(char** board, int num_rows, int num_cols);
		void delete_board(char** *board, int num_rows, int num_cols);

#endif
