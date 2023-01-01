#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<ctype.h>
#define size1 10
#define size2 100
#define n 3
#pragma warning(disable:4996)

char buffer;
int retSize(const char s[]) {
    int i = 0;
    for (; s[i]; ++i);
    return i;
}

struct guesses {
    char names[size2];
    char hint[size2];
};

const struct guesses games[size1] = { {"Grand Theft Auto", "Action, Open world Game"}, {"Valorant", "Online FPS Game"}, {"Outlast", "Horror FP game"},
                                      {"Half Life", "FPS game developed by valve"}, {"The Last of Us", "Action-Horror game developed by Naughty Dog"},
                                      {"Forza Horizon", "Racing video game developed by Playground Games"}, {"Resident Evil", "Japanese horror game series"},
                                      {"Uncharted", "Action-Adventure game developed by Naughty Dog"}, {"Tekken", "Arcade game developed by Bandai Namco Studios"},
                                      {"Call of Duty", "FPS video game franchise published by Activision"} };


const struct guesses countries[size1] = { {"Djibouti", "Home to one of the saltiest bodies of water in the world"}, {"Burkina Faso", "Bordered by Mali"}, {"Niger", "Bordered by Libya"},
                                          {"Zimbabwe", "Landlocked country in southern Africa"}, {"Uganda", "Landlocked country in East Africa"},
                                          {"Chad", "Landlocked country at the crossroads of North and Central Africa"}, {"Cameroon",
                                                       "Central African country of varied terrain and wildlife."},{"Mali", "Landlocked country in West Africa"},
        {"Belarus", "Landlocked country in Eastern Europe"}, {"Lesotho", "landlocked kingdom encircled by South Africa"} };


const struct guesses famousPeople[size1] = { {"Alan Turing", "English mathematician, computer scientist"}, {"Donald Knuth", "Winner of the 1974 ACM Turing Award"},
                                             {"Ada Lovelace", "Known for the work on Charles Babbage's proposed mechanical general-purpose computer"},
                                             {"Shakira", "Colombian singer"}, {"Brad Pitt", "American actor and film producer"},
                                             {"Leonardo da Vinci", "Italian Painter"}, {"Edsger Wybe Dijkstra", "Dutch computer scientist, known for his graph theory algorithm"},
                                             {"Cleopatra", "Queen of the Ptolemaic Kingdom of Egypt"}, {"Pablo Picasso", "Spanish painter"},
                                             {"Vladimir Putin", "Russian politician and former intelligence officer"} };

void printArt(int life) {
    switch (life) {
    case 0:
        printf(
            "\t\t\t\t+------+\n"
            "\t\t\t\t |     |\n"
            "\t\t\t\t O     |\n"
            "\t\t\t\t/|\\    |\n"
            "\t\t\t\t/ \\    |\n"
            "\t\t\t\t       |\n"
            "\t\t\t\t=========\n\n"
        );
        break;
    case 1:
        printf(
            "\t\t\t\t+------+\n"
            "\t\t\t\t |     |\n"
            "\t\t\t\t O     |\n"
            "\t\t\t\t/|\\    |\n"
            "\t\t\t\t/      |\n"
            "\t\t\t\t       |\n"
            "\t\t\t\t=========\n\n"
        );
        break;
    case 2:
        printf(
            "\t\t\t\t+------+\n"
            "\t\t\t\t |     |\n"
            "\t\t\t\t O     |\n"
            "\t\t\t\t/|\\    |\n"
            "\t\t\t\t       |\n"
            "\t\t\t\t       |\n"
            "\t\t\t\t=========\n\n"
        );
        break;
    case 3:
        printf(
            "\t\t\t\t+------+\n"
            "\t\t\t\t |     |\n"
            "\t\t\t\t O     |\n"
            "\t\t\t\t/|     |\n"
            "\t\t\t\t       |\n"
            "\t\t\t\t       |\n"
            "\t\t\t\t=========\n\n"
        );
        break;
    case 4:
        printf(
            "\t\t\t\t+------+\n"
            "\t\t\t\t|     |\n"
            "\t\t\t\tO     |\n"
            "\t\t\t\t|     |\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t========\n\n"
        );
        break;
    case 5:
        printf(
            "\t\t\t\t+------+\n"
            "\t\t\t\t|     |\n"
            "\t\t\t\tO     |\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t========\n\n"
        );
        break;
    case 6:
        printf(
            "\t\t\t\t+------+\n"
            "\t\t\t\t|     |\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t========\n\n"
        );
        break;
    case 7:
        printf(
            "\t\t\t\t+------+\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t      |\n"
            "\t\t\t\t========\n\n"
        );
    }
}

// function to return a character in lower case
char lower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}


int guess(const struct guesses* g) {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // retSize will return length of the word to guess... toGuess variable is to count the alphabets of the word to be guessedd
    int wordSize = retSize(g->names), toGuess = 0;
    // alt array is to display the dashes according to the word to guess.
    char alt[size2] = { '\0' };
    for (int i = 0; i < wordSize; ++i) {
        if (isalnum(g->names[i])) {
            alt[i] = '-';
            ++toGuess;
        }
        else
            alt[i] = ' ';
    }
    // guessedWords is to count the number of alphabets of the word that have been guessed.
    int guessedWords = 0, lives = 7;
    int hint;
    int hintTaken = 0;

    while (lives && guessedWords != toGuess) {
        system("cls");
        printArt(lives);
        printf("YOU HAVE %d lives LEFT\n\n", lives);
        printf("%s\n\n", alt);
        if (!hintTaken) { // will display hint for one time only
            printf("Enter 1 to get a hint\n");
            scanf("%d", &hint);
            scanf("%c", &buffer);
            if (hint == 1) {
                printf("\nhint: %s\n\n", g->hint);
                ++hintTaken;
            }
        }
        char c = '-';
        while (!isalnum(c)) {
            printf("Guess an alphabet:\n");
            scanf("%c", &c);
        }
        scanf("%c", &buffer);
        // prevGuess is used here to know if the user guessed an alphabet that is in the word.
        int prevGuess = guessedWords, t = 1;
        for (int i = 0; i < wordSize && t; ++i) {
            if (lower(alt[i]) == lower(c))
                t = 0; // user already guessed the same aplhabet so we will break the loop
            else if (lower(g->names[i]) == lower(c)) {
                alt[i] = g->names[i];
                ++guessedWords;
            }
        }
        if (prevGuess == guessedWords) {
            if (!t)
                printf("You already guess this alphabet\n\n");
            else {
                printf("YOU LOST A LIFE\n\n");
                --lives;
            }
            Sleep(550);
        }
    }
    system("cls");
    if (!lives) {
        SetConsoleTextAttribute(hConsole, 4);
        printf("YOU LOST\n\n");
    }
    else {
        SetConsoleTextAttribute(hConsole, 2);
        printf("YOU WON\n\n");
    }
    printArt(lives);
    Sleep(550);
    system("cls");
    SetConsoleTextAttribute(hConsole, 7);
    return lives;
}


void hangMan() {
    srand(time(NULL));
    int noOfGames = -1, noOfWins = 0, noOfLosses = 0;
    while (noOfGames < 1) {
        printf("Enter number of games you want to play:\n");
        scanf("%d", &noOfGames);
    }
    while (noOfGames--) {
        int choice = 0;
        while (choice < 1 || choice > 4) {
            printf("Enter 1 if you want to guess video game's name:\n"
                "Enter 2 if you want to guess country's name:\n"
                "Enter 3 if you want to guess famous people's name:\n"
                "Enter 4 if you want to guess words from above all:\n");
            scanf("%d", &choice);
        }
        int randChoice = rand() % 11, alt;
        if (choice == 4)
            choice = 1 + rand() % 3;
        switch (choice) {
        case 1:
            alt = guess(&games[randChoice]);
            break;
        case 2:
            alt = guess(&countries[randChoice]);
            break;
        case 3:
            alt = guess(&famousPeople[randChoice]);
            break;
        }
        if (alt)
            ++noOfWins;
        else
            ++noOfLosses;
    }
    printf("\nGAMES WON: %d\n\nGAMES LOST: %d\n\n", noOfWins, noOfLosses);
}


int main() {
    printf(
        "\t\t\t\t\t\t _\n"
        "\t\t\t\t\t\t| |\n"
        "\t\t\t\t\t\t| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __\n"
        "\t\t\t\t\t\t| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\\n"
        "\t\t\t\t\t\t| | | | (_| | | | | (_| | | | | | | (_| | | | |\n"
        "\t\t\t\t\t\t|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n"
        "\t\t\t\t\t\t                   __/ |\n"
        "\t\t\t\t\t\t                   |___/\n\n"
    );
    hangMan();
    return 0;
}