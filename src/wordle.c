#include "../inc/wordle.h"

bool guessWord(char** game, char correctWord[], int guesses, int wordLength, int counter) {

    char guess[wordLength+1];
    char input[MAX_INPUT];
    bool isValid = false;

    // continue taking input until it is valid
    while (isValid == false) {
        printf("\n\nPlease enter a %d-letter word: ", wordLength);
        scanf("%s", input);

        // if the input does not match the word length specified
        if ((strlen(input) != wordLength)) {
            printf("\nSorry, but you can only enter %d-letter words.", wordLength);

        // if the input matches the word length, validate that it is alphabetic characters only
        } else {
            bool isAlpha = true;

            for (int i = 0; i < strlen(input); i++) {
                if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) {
                    continue;

                } else {
                    isAlpha = false;
                }
            }

            if (isAlpha == true) {
                isValid = true;

            } else {
                printf("\nSorry, but you can only enter %d-letter words.", wordLength);
            }
        }
    }

    // copy the validated input to the 'guess' array
    strcpy(guess, input);

    // store the 'guess' array into the game fields
    for (int i = 0; i < wordLength; i++) {
        game[counter][i] = toupper(guess[i]);
    }

    // print the updated game field
    printGameState(game, correctWord, guesses, wordLength);

    // if the guess was correct, end the game
    if (strcmpi(guess, correctWord) == 0) {
        return true;

    } else {
        return false;
    }
}

void printGameState(char** game, char correctWord[], int guesses, int wordLength) {

    printf("\n\nCurrent game state:");

    for (int i = 0; i < guesses; i++) {
        printf("\n");

        for (int j = 0; j < wordLength; j++) {

            // if the letter is placed correctly
            if (game[i][j] == correctWord[j]) {
                green();
                printf("%c ", game[i][j]);
                reset();

            // if the letter is present, but not placed correctly
            } else if (strchr(correctWord, game[i][j]) != NULL) {
                yellow();
                printf("%c ", game[i][j]);
                reset();

            // if the letter is incorrect
            } else {
                printf("%c ", game[i][j]);
            }
        }
    }
}

void green() {
    printf("\033[1;32m");
}

void yellow() {
    printf("\033[1;33m");
}

void reset() {
    printf("\033[0m");
}