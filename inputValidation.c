#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
	/*
	check if the format of the user input is valid
	@numArgsRead: the number of arguments that was read from the user
	@numArgsNeed: the number of arguments that was needed
	@return: whether the format is valid 
	*/
  bool formatIsGood = numArgsRead == numArgsNeed;
  char character;
  do{
    scanf("%c", &character); //45  bob  \n
		if(!isspace(character)){ //found a non whitespace character on the way to the end of the line
			formatIsGood = false;
		}
	}while(character != '\n'); //read characters until the end of the line
  return formatIsGood;
}
