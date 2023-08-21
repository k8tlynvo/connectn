#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "play_game.h"
#include "inputValidation.h"
#include "setup.h"

void play_game(int num_rows, int num_cols, int pieces_to_win, char** board, char* pieces, int cur_player) {
	/*
	@num_rows: the number of rows on the board
	@num_cols: the number of columns on the board
	@pieces_to_win: the number of pieces in a row needed to win
	@board: the board a 2d array
	@pieces: the array of character pieces
	@cur_player: the number corresponding to the current player
	*/
	int col_played;
	int row_played;

	do {
		print_board(board, num_rows, num_cols);
		get_valid_move(&col_played, board, num_rows, num_cols);
		do_move(pieces[cur_player - 1], col_played, &row_played, board, num_rows);
		change_turn(&cur_player);
	} while(!is_game_over(board, num_rows, num_cols, pieces_to_win, row_played, col_played));

	print_board(board, num_rows, num_cols);
	change_turn(&cur_player);
	announce_results(board, num_rows, num_cols, pieces_to_win, row_played, col_played, cur_player);
}

void get_valid_move(int *col, char** board, int num_rows, int num_cols){
	/*
	keep asking the user for a move until it's valid
	@*col: a pointer to the column played
	@board: the board, a 2d array
	@num_rows: the number of rows on the board
	@num_cols: the number of columns on the board
	*/
	int num_args_read;
	const int num_args_needed = 1;
	do{
		printf("Enter a column between 0 and %d to play in: ", num_cols-1);
		num_args_read = scanf("%d", col);
	}while(!(isValidFormat(num_args_read, num_args_needed) &&
					 is_valid_move(board, *col, num_rows, num_cols)));
}

bool is_valid_move(char** board, int col, int num_rows, int num_cols) {
	/*
	check if a move is valid
	@board: the board, a 2d array
	@col: the column the user chose to play
	@num_rows: the number of rows on the board
	@num_cols: the number of columns on the board
	@return: whether the move is valid
	*/
	return !is_col_full(board, col, num_rows) && is_col_on_board(col, num_cols);
}

void do_move(char piece, int col, int *row, char** board, int num_rows) {
	/*
	place the piece in the column the user chose
	@piece: the character to place
	@col: the column to place it in
	@*row: a pointer to the row the piece will be placed in
	@board: the board, a 2d array
	@num_rows: the number of rows on the board
	*/
	for (int i = 0; i < num_rows; i++) {
		if (board[i][col] == '*') {
			board[i][col] = piece;
			*row = i;
			break;
		}
	}
}

void change_turn(int *cur_player) {
	/*
	change who is the current player
	@*cur_player: a pointer to the number corrresponding to the current player
	*/
	if (*cur_player == 1) {
		*cur_player = 2;
	} else *cur_player = 1;
}

bool is_game_over(char** board, int num_rows, int num_cols, int pieces_to_win, int row_played,
									int col_played) {
	/*
	check if the game is over which is when either someone has won or there is a tie
	@board: the board, a 2d array
	@num_rows: the number of rows on the board
	@num_cols: the number of columns on the board
	@pieces_to_win: the number of pieces in a row needed to win
	@row_played: the row where the piece is on the board
	@col_played: the column where the piece is on the board
	@return: whether the game is over
	*/
	return has_someone_won(board, num_rows, num_cols, pieces_to_win, row_played, col_played) ||
				 is_tie(board, num_rows, num_cols);
}

bool has_someone_won(char** board, int num_rows, int num_cols, int pieces_to_win, int row_played, int col_played) {
	/*
	check if someone has won by a horizontal win, vertical win, or diagonal win
	@board: the board, a 2d array
	@num_rows: the number of rows on the board
	@num_cols: the number of columns on the board
	@pieces_to_win: the number of pieces in a row needed to win
	@row_played: the row where the piece is on the board
	@col_played: the column where the piece is on the board
	@return: whether someone has won
	*/
	return is_horizontal_win(board, row_played, num_cols, pieces_to_win) ||
				 is_vertical_win(board, col_played, num_rows, pieces_to_win) ||
				 is_diagonal_win(board, num_rows, num_cols, pieces_to_win);
}

bool is_horizontal_win(char** board, int row_played, int num_cols, int pieces_to_win) {
	/*
	check if there's a horizontal win in the row that the piece was placed in
	@board: the board, a 2d array
	@row_played: the row where the piece is on the board
	@num_cols: the number of columns on the board
	@pieces_to_win: the number of pieces in a row needed to win
	@return: whether there's a horizontal win in the row
	*/
	if (num_cols - pieces_to_win < 0) return false;
	// loop for how many times we're doing this check
	for (int i = 0; i <= num_cols - pieces_to_win; i++) {
		// make the array that we're checking
		char* checked_array = get_section_from_row(board, i, row_played, pieces_to_win);
		// if all the chars in the mini array are the same:
		if (all_same(checked_array, pieces_to_win) && board[row_played][i] != '*') {
			free(checked_array);
			return true;
		} else {
			// if the mini array is not all the same, free it and go to next iteration of loop
			free(checked_array);
		}
	}
	// if we get through all checks and never return true, return false
	return false;

}

bool is_vertical_win(char** board, int col_played, int num_rows, int pieces_to_win) {
	/*
	check if there's a vertical win in the column the piece was placed in
	@board: the board, a 2d array
	@col_played: the column where the piece is on the board
	@num_rows: the number of rows on the board
	@num_cols: the number of columns on the board
	@pieces_to_win: the number of pieces in a row needed to win
	@return: whether there's a vertical win in the column
	*/
	if (num_rows - pieces_to_win < 0) return false;
	for (int i = 0; i <= num_rows - pieces_to_win; i++) {
		// make the array that we're checking
		char* checked_array = get_section_from_col(board, i, col_played, pieces_to_win);
		// if all the chars in the mini array are the same and they're not the blank char:
		if (all_same(checked_array, pieces_to_win) && board[i][col_played] != '*') {
			free(checked_array);
			return true;
		} else {
			// if the array is not all the same, free it and go to next iteration of loop
			free(checked_array);
		}
	}
	// if we get through all checks and never return true, return false
	return false;

}

char* get_section_from_row(char** board, int starting_col, int row_played, int length) {
	/*
	get a section from a horizontal row on the board
	@board: the board, a 2d array
	@starting_col: the column on the board that the section will start at
	@row_played: the row where the piece was placed
	@length: the length of the section
	@return: the section, an array of characters
	*/
	char* out_array = (char*)calloc(length, sizeof(char));
	int array_index = 0;
	for (int i = starting_col; i < starting_col + length; i++) {
		out_array[array_index] = board[row_played][i];
		array_index++;
	}
	return out_array;
}

char* get_section_from_col(char** board, int starting_row, int col_played, int length) {
	/*
	get a section from a column on the board
	@board: the board, a 2d array
	@starting_row: the row on the board that the section will start at
	@col_played: the column where the piece was placed
	@length: the length of the section
	@return: the section, an array of characters
	*/
	char* out_array = (char*)calloc(length, sizeof(char));
	int array_index = 0;
	for (int i = starting_row; i < starting_row + length; i++) {
		out_array[array_index] = board[i][col_played];
		array_index++;
	}
	return out_array;
}

bool all_same(char* values, int length){
	/*
	check if all characters in an array are the same
	@values: the array of characters
	@length: the length of the array
	@return: whether all the characters are the same
	*/
	for(int i = 1; i < length; ++i){
		if(values[i] != values[0]){
			return false;
		}
	}
	return true;
}

bool is_diagonal_win(char** board, int num_rows, int num_cols, int pieces_to_win) {
	/*
	check if there's a diagonal win
	@board: the board, a 2d array
	@num_rows: the number of rows on the board
	@num_cols: the number of columns on the board
	@pieces_to_win: the number of pieces in a row needed to win
	@return: whether there's a diagonal win
	*/
	return left_diagonal_win(board, num_rows, num_cols, pieces_to_win) ||
				 right_diagonal_win(board, num_rows, num_cols, pieces_to_win);
}

bool left_diagonal_win(char** board, int num_rows, int num_cols, int pieces_to_win) {
	/*
	check if there's a left diagonal win, the diagonal starts from the bottom left
	@board: the board, a 2d array
	@num_rows: the number of rows on the board
	@num_cols: the number of columns on the board
	@pieces_to_win: the number of pieces in a row needed to win
	@return: whether there's a left diagonal win
	*/
	if (num_rows - pieces_to_win < 0 || num_cols - pieces_to_win < 0) return false;
	// the number of checks we do
	for (int i = 0; i <= num_rows - pieces_to_win; i++) {
		for (int j = 0; j <= num_cols - pieces_to_win; j++) {
			char* checked_array = get_possible_left_diagonal(board, i , j, pieces_to_win);
			if (board[i][j] != '*' && all_same(checked_array, pieces_to_win)) {
				free(checked_array);
				return true;
			} else {
				free(checked_array);
			}
		}
	}
	return false;
}

char* get_possible_left_diagonal(char** board, int starting_row, int starting_col, int length) {
	/*
	get a possible left diagonal
	@board: the board, a 2d array
	@starting_row: the row where the diagonal starts
	@starting_col: the column where the diagonal starts
	@length: the length of the possible diagonal
	@return: the array of the characters from the possible diagonal
	*/
	char* out_array = (char*)calloc(length, sizeof(char));
	int row = starting_row;
	int col = starting_col;
	for (int i = 0; i < length; i++) {
		out_array[i] = board[row][col];
		row++;
		col++;
	}
	return out_array;
}

bool right_diagonal_win(char** board, int num_rows, int num_cols, int pieces_to_win) {
	/*
	check if there's a right diagonal win, the diagonal starts from the bottom right
	@board: the board, a 2d array
	@num_rows: the number of rows on the board
	@num_cols: the number of columns on the board
	@pieces_to_win: the number of pieces in a row needed to win
	@return: whether there's a right diagonal win
	*/
	// the number of checks we need to do
	if (num_rows - pieces_to_win < 0 || pieces_to_win > num_cols + 1) return false;
	for (int i = 0; i <= num_rows - pieces_to_win; i++) {
		for (int j = num_cols - 1; j >= pieces_to_win - 1; j--) {
			char* checked_array = get_possible_right_diagonal(board, i , j, pieces_to_win);
			if (board[i][j] != '*' && all_same(checked_array, pieces_to_win)) {
				free(checked_array);
				return true;
			} else {
				free(checked_array);
			}
		}
	}
	return false;
}

char* get_possible_right_diagonal(char** board, int starting_row, int starting_col, int length) {
	/*
	get a possible right diagonal
	@board: the board, a 2d array
	@starting_row: the row where the diagonal starts
	@starting_col: the column where the diagonal starts
	@length: the length of the possible diagonal
	@return: the array of the characters from the possible diagonal
	*/
	char* out_array = (char*)calloc(length, sizeof(char));
	int row = starting_row;
	int col = starting_col;
	for (int i = 0; i < length; i++) {
		out_array[i] = board[row][col];
		row++;
		col--;
	}
	return out_array;
}

bool is_tie(char** board, int num_rows, int num_cols) {
	// check if there's a tie but must check is someone won first before calling this function or else
	// the last winning piece will be considered a tie
	/*
	check if there's a tie
	@board: the board, a 2d array
	@num_rows: the number of rows in the board
	@num_cols: the number of columns in the board
	@return: whether there's a tie
	*/
	for(int i = 0; i < num_rows; i++) {
		for(int j = 0; j < num_cols; j++) {
			if(board[i][j] == '*') {
				return false;
			}
		}
	}
	return true;
}

bool is_col_full(char** board, int col, int num_rows) {
	/*
	check if a column is full of played characters
	@board: the board, a 2d array
	@col: the column that's being checked
	@num_rows: the number of rows in the board
	@return: whether the column is full
	*/
	char* whole_col = get_section_from_col(board, 0, col, num_rows);
	for(int i = 0; i < num_rows; i++) {
		if (whole_col[i] == '*') {
			free(whole_col);
			return false;
		}
	}
	free(whole_col);
	return true;
}

bool is_col_on_board(int col, int num_cols) {
	/*
	checks whether the column chosen by the user is on the board
	@col: the column chosen
	@num_cols: the number of columns in the board
	@return: whether the column is on the board
	*/
	return col >= 0 && col < num_cols;
}

void announce_results(char** board, int num_rows, int num_cols, int pieces_to_win,
											int row_played, int col_played, int cur_player) {
	/*
	announce the results of the game, whether if someone won or there's a tie
	@board: the board, a 2d array
	@num_rows: the number of rows in the board
	@num_cols: the number of columns in the board
	@pieces_to_win: the number of pieces in a row needed to win
	@row_played: the row where the piece that was played is in
	@col_played: the column where the piece that was played is in
	@cur_player: the current player
	*/
	if (has_someone_won(board, num_rows, num_cols, pieces_to_win, row_played, col_played) ) {
		printf("Player %d Won!\n", cur_player);
	} else {
		printf("Tie game!\n");
	}
}
