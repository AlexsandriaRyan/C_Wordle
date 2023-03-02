#ifndef ASSIGN5_WORDLE_H
#define ASSIGN5_WORDLE_H

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define ARGUMENTS 5
#define MAX_INPUT 256

bool guessWord(char** game, char correctWord[], int guesses, int wordLength, int counter);
void printGameState(char** game, char correctWord[], int guesses, int wordLength);
void yellow();
void green();
void reset();

#endif //ASSIGN5_WORDLE_H
