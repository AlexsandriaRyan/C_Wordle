// Alexsandria Ryan
// Assignment #5
// December 14, 2022

#include "../inc/wordle.h"

int main(int argc, char *argv[]) {

    setbuf(stdout, 0);

// -------------------- VALIDATING ARGUMENTS ----------------------------------------

    if (argc != ARGUMENTS) {
        fprintf(stderr, "Invalid number of command line arguments.");
        return 1;
    }

    char inputFileName[MAX_INPUT];
    char outputFileName[MAX_INPUT];

    if ((strcmpi(argv[1], "-i") == 0) && (strcmpi(argv[3], "-o") == 0)) {
        strcpy(inputFileName, argv[2]);
        strcpy(outputFileName, argv[4]);

    } else if ((strcmpi(argv[3], "-i") == 0) && (strcmpi(argv[1], "-o") == 0)) {
        strcpy(inputFileName, argv[4]);
        strcpy(outputFileName, argv[2]);

    } else {
        fprintf(stderr, "Invalid command line argument usage.");
        return 1;
    }

    FILE *inputFile;
    char inputMode[] = "r";
    inputFile = fopen(inputFileName, inputMode);

    FILE *outputFile;
    char outputMode[] = "a+";
    outputFile = fopen(outputFileName, outputMode);

    if (inputFile == NULL) {
        fprintf(stderr, "Cannot open %s for reading.", argv[2]);
        return 1;

    } else if (outputFile == NULL) {
        fprintf(stderr, "Cannot open %s for writing.", argv [4]);
        return 1;

    }

// -------------------- READING INFO & ALLOCATING ----------------------------------------

    // reading from file and storing information
    int guesses;
    int wordLength;
    char tempWord[MAX_INPUT];
    fscanf(inputFile, "%d %d %s", &wordLength, &guesses, tempWord);
    fclose(inputFile);
    char correctWord[wordLength+1];
    strcpy(correctWord, tempWord);

    // allocating memory
    char** game = (char**) calloc(guesses, sizeof(char*));
    for (int i = 0; i < guesses; i++) {
        game[i] = (char*) calloc(wordLength, sizeof(char));
    }

    // storing all places in 'game' with an underscore
    for (int i = 0; i < guesses; i++) {
        for (int j = 0; j < wordLength; j++) {
           game[i][j] = '_';
        }
    }

// -------------------- BEGIN GAME ----------------------------------------

    printf("Welcome to C-Wordle!!");
    // printing blank game
    printGameState(game, correctWord, guesses, wordLength);

    int counter = 0;
    bool win = false;

    // while the game hasn't been won / the game hasn't exceeded the permitted amount of guesses
    while ((win == false) && (counter < guesses)) {
        win = guessWord(game, correctWord, guesses, wordLength, counter);
        counter ++;
    }

// -------------------- WRITE TO FILE ----------------------------------------

    // if the game is won
    if (win == true) {
        printf("\n\nYou WIN!!!");
        fprintf(outputFile, "The solution was found.");

    // if the game is lost
    } else {
        printf("\n\nYou LOSE!!!");
        fprintf(outputFile, "The solution was not found.");
    }

    for (int i = 0; i < guesses; i++) {
        fprintf(outputFile, "\n");

        for (int j = 0; j < wordLength; j++) {
            fprintf(outputFile, "%c ", game[i][j]);
        }
    }

    fprintf(outputFile, "\n\n");
    fclose(outputFile);
    free(game);

    printf("\nThe game result was written to the %s file", outputFileName);

    return 0;
}