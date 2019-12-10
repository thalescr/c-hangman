#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 256

// Clears the terminal screen in Windows or Linux
void clear() {
    #ifdef linux
    system("clear");
    #endif
    #ifdef _WIN32
    system("cls");
    #endif
}

// Prints hangman status and check if the game has ended
int printHangman(int tries[26], int n, char *current) {
    int i, count = 0;
    clear();

    // Check tries array and print all wrong tries
    for(i = 0; i < 26; i ++) {
        if(tries[i] == -1) {
            printf("%c ", i + 65);
            count++;
        }
    }

    // Print the hangman according to wrong tries count
    printf("\n|-----|");
    printf("\n|     |");
    if(count > 0)
        printf("\n|     O");
    else
        printf("\n|");
    if(count > 5)
        printf("\n|    /|\\");
    else if(count > 4)
        printf("\n|    /|");
    else if(count > 1)
        printf("\n|     |");
    else
        printf("\n|");
    if(count > 3)
        printf("\n|    / \\");
    else if(count > 2)
        printf("\n|    /");
    else
        printf("\n|");
    printf("\n|");
    printf("\n|");

    // Player loses
    if(count > 5)
        return -1;

    // Print the current status and count letters left
    count = 0;
    for(i = 0; i < n; i ++) {
        printf("%c ", current[i]);
        if(current[i] == '_')
            count++;
    }
    printf("\n");

    // If there's no more letters left, player wins
    if(count == 0)
        return 0;
    
    // Else, game keeps running
    return 1;

}


int main() {
    char answer[MAX], letter;
    int tries[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Please type a word
    printf("Hangman\n");
    printf("Please, type a word: ");
    scanf("%s", answer);
    int n = strlen(answer), i, count, notEnd = 1;

    // Put the answer string to uppercase and set current array to '_'
    char current[n];
    for(i = 0; i < n; i ++) {
        answer[i] = toupper(answer[i]);
        current[i] = '_';
    }

    // First print
    printHangman(tries, n, current);

    // Main loop
    while(notEnd == 1) {
        letter = 0;
        // Only reads if it's a char from 'A' to 'Z'
        while(letter < 65 || letter > 90) {
            getchar();
            printf("Type a letter: ");
            scanf("%c", &letter);
            letter = toupper(letter);
        }

        // If the player didn't tried this letter
        if(tries[letter - 65] == 0) {
            count = 0;
            // Check if the answer has this letter
            for(i = 0; i < n; i ++) {
                if(answer[i] == letter) {
                    count++;
                    current[i] = letter;
                    tries[letter - 65] = 1;
                }
            }

            // If not, print "Wrong!"
            if(count == 0) {
                tries[letter - 65] = -1;
                notEnd = printHangman(tries, n, current);
                printf("Wrong!\n");
            }

            // Else, print hangman and check if it ended
            else {
                notEnd = printHangman(tries, n, current);
                printf("Found out %d more\n", count);
            }
        
        }
        // If the player already tried this letter
        else {
            notEnd = printHangman(tries, n, current);
            printf("You've already wrote %c!\n", letter);
        }
    }

    // If it ended returning -1
    if(notEnd == -1)
        printf("\nYou lose!\n");

    // If it ended returning 0
    else
        printf("Congrats!\n");

    return 0;
}