#ifndef PLAY_GAME_H
	#define PLAY_GAME_H

	#include <stdbool.h>
	#include "setup.h"

	void play_game(int num_rows, int num_cols, int pieces_to_win, char** board, char* pieces,
								 int cur_player);
	void do_move(char piece, int col, int* row, char** board, int num_rows);
	void change_turn(int* cur_player);
	bool is_game_over(char** board, int num_rows, int num_cols, int pieces_to_win, int row_played,
										int col_played);
	bool has_someone_won(char** board, int num_rows, int num_cols, int pieces_to_win, int row_played, int col_played);
	bool is_horizontal_win(char** board, int row_played, int num_cols, int pieces_to_win);
	bool is_vertical_win(char** board, int col_played, int num_rows, int pieces_to_win);
	char* get_section_from_row(char** board, int starting_col, int row_played, int length);
	char* get_section_from_col(char** board, int starting_row, int col_played, int length);
	bool all_same(char* values, int length);
	bool is_diagonal_win(char** board, int num_rows, int num_cols, int pieces_to_win);
	bool left_diagonal_win(char** board, int num_rows, int num_cols, int pieces_to_win);
	char* get_possible_left_diagonal(char** board, int starting_row, int starting_col, int length);
	bool right_diagonal_win(char** board, int num_rows, int num_cols, int pieces_to_win);
	char* get_possible_right_diagonal(char** board, int starting_row, int starting_col, int length);
	bool is_tie(char** board, int num_rows, int num_cols);
	void get_valid_move(int *col, char** board, int num_rows, int num_cols);
	bool is_valid_move(char** board, int col, int num_rows, int num_cols);
	bool is_col_full(char** board, int col, int num_rows);
	bool is_col_on_board(int col, int num_cols);
	void announce_results(char** board, int num_rows, int num_cols, int pieces_to_win,
												int row_played, int col_played, int cur_player);

#endif
