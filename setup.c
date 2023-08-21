#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "setup.h"

void setup_game(int num_rows, int num_cols, char** *out_board, char* *out_pieces, int* out_cur_player) {
	/*
	make the board, players pick their pieces, and who goes first is determined
	@num_rows: the number of rows on the board
	@num_cols: the number of cols on the board
	@*out_board: pointer to the 2d array, board
	@*out_pieces: pointer to the array of pieces
	@*out_cur_player: pointer to the current player
	*/
	const int num_players = 2;
	*out_board = make_board(num_rows, num_cols);
	*out_pieces = players_pick_pieces(num_players);
	*out_cur_player = pick_who_goes_first();
}

char** make_board(int num_rows, int num_cols) {
	/*
	make the board, a 2d array of blank characters '*'
	@num_rows: the number of rows on the board
	@num_cols: the number of cols on the board
	@return: the board
	*/
	char** board = (char**)calloc(num_rows, sizeof(char*));
	for (int row = 0; row < num_rows; row++) {
		board[row] = (char*)calloc(num_cols, sizeof(char));
		for (int col = 0; col < num_cols; col++) {
			board[row][col] = '*';
		}
	}
	return board;
}

char* players_pick_pieces(int num_players) {
	/*
	determine which player has which piece
	@num_players: the number of players in the game
	@return: array of player pieces
	*/
	char* pieces = (char*)calloc(num_players, sizeof(char));
	pieces[0] = 'X';
	pieces[1] = 'O';
	return pieces;
}

int pick_who_goes_first() {
	/*
	determine which player goes first
	@return: the player that goes first
	*/
	return 1;
}

void print_board(char** board, int num_rows, int num_cols) {
	/*
	print the board to the screen
	@board: the board
	@num_rows: the number of rows on the board
	@num_cols: the number of cols on the board
	*/
	for(int i = num_rows - 1; i >= 0; i--) {
		// label the row
		printf("%d ", i);
		// print the stars
		for(int j = 0; j < num_cols; j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	// bottom numbers
	printf("  ");
	for (int i = 0; i < num_cols; i++) {
		printf("%d ", i);
	}
	printf("\n");
}

void delete_board(char** *board, int num_rows, int num_cols) {
	/*
	delete the board at the end of the game
	@*board: a pointer to the board
	@num_rows: the number of rows on the board
	@num_cols: the number of cols on the board
	*/
	for(int i = 0; i < num_rows; i++) {
		free((*board)[i]);
	}
	free(*board);
	board = NULL;
}
