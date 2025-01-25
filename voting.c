#include <stdio.h>
#include <string.h>

#define MAX_C 11
// defining max number of candidates

// Structure of candidate
typedef struct Candidate {
    char name[50];
    int votes;
    char symbol;
} Candidate;

// global array of candidate details
Candidate allCandidates[MAX_C];
// global variable to keep the count of candidates
int candidateCount = 0;
// global array to store all symbols
char symbols[10] = { '!', '@', '#', '$', '%', '^', '&', '*', '~', '+' };
// array to keep track of taken symbol
int symbolTaken[11];

// function declaration
void fillCandidate(int);
void displayAllCandidates();
void getVotes(int);
void getResults();

// driver code
int main()
{
    // initializing necessary data structures
    for (int i = 0; i < 11; i++) {
        symbolTaken[i] = 0;
    }

    // getting the number of candidates
    printf("Enter the number of candidates: ");
    if (scanf("%d", &candidateCount) != 1 || candidateCount >= MAX_C) {
        printf("Invalid input. Number of candidates cannot be greater than 10.\n");
        return 0;
    }

    // filling the details of the candidate
    for (int i = 0; i < candidateCount; i++) {
        fillCandidate(i);
    }

    // getting the number of voters
    int numVoters;
    printf("Enter the number of voters: ");
    if (scanf("%d", &numVoters) != 1) {
        printf("Invalid input.\n");
        return 0;
    }

    // Collecting votes
    for (int i = 0; i < numVoters; i++) {
        getVotes(i);
    }

    // printing results
    getResults();

    return 0;
}

// function to populate the allCandidates array using the
// details provided by user
void fillCandidate(int cNum)
{
    printf("Available Symbols: \n");
    for (int j = 0; j < 10; j++) {
        if (symbolTaken[j] == 1)
            continue;
        printf("%d  %c\n", j + 1, symbols[j]);
    }

    int num = 0;

    // Loop until a valid symbol is selected
    while (1) {
        printf("\nEnter the symbol number for candidate %d: ", cNum + 1);
        if (scanf("%d", &num) != 1) {
            while (getchar() != '\n'); // clear the input buffer
            printf("Invalid input. Please enter a number between 1 and 10: ");
            continue;
        }

        if (num <= 0 || num > 10 || symbolTaken[num - 1] == 1) {
            printf("This symbol is not available. Please choose from the available symbols.\n");
        } else {
            symbolTaken[num - 1] = 1;
            allCandidates[cNum].symbol = symbols[num - 1];
            break;
        }
    }

    // Input the candidate's name
    printf("Enter the name of candidate %d: ", cNum + 1);
    if (scanf("%s", allCandidates[cNum].name) != 1) {
        printf("Invalid name input.\n");
        return;
    }

    allCandidates[cNum].votes = 0;
}

// function to display all candidates' names with symbols
void displayAllCandidates()
{
    if (!allCandidates || !candidateCount) {
        printf("Invalid Candidate Array\n");
        return;
    }

    printf("\nCandidates and Symbols:\n");
    for (int j = 0; j < candidateCount; j++) {
        printf("%s\t\t", allCandidates[j].name);
    }
    printf("\n");
    for (int j = 0; j < candidateCount; j++) {
        printf("%3c\t\t", allCandidates[j].symbol);
    }
    printf("\n");
}

// function to get votes
void getVotes(int voterCount)
{
    displayAllCandidates();
    int choice;

    // Loop until a valid vote is entered
    while (1) {
        printf("Voter %d, please enter your choice (1-%d): ", voterCount + 1, candidateCount);
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // clear the input buffer
            printf("Invalid input. Please enter a valid number between 1 and %d: ", candidateCount);
            continue;
        }

        if (choice >= 1 && choice <= candidateCount) {
            allCandidates[choice - 1].votes++;
            break;
        } else {
            printf("Invalid choice! Please vote again.\n");
        }
    }
}

// function to get results
void getResults()
{
    int maxVotes = 0;
    int winnerIndex = -1;
    int winnerFrequency = 0;

    // Find the maximum votes and the winner(s)
    for (int i = 0; i < candidateCount; i++) {
        if (allCandidates[i].votes > maxVotes) {
            maxVotes = allCandidates[i].votes;
            winnerIndex = i;
        }
    }

    for (int i = 0; i < candidateCount; i++) {
        if (allCandidates[i].votes == maxVotes) {
            winnerFrequency++;
        }
    }

    printf("\n-----RESULT-----\n");

    if (winnerFrequency > 1) {
        printf("No candidate has majority votes.\n");
    } else if (winnerIndex != -1) {
        printf("The winner is: %s\nCandidate Symbol: %c\nwith %d votes!\n",
               allCandidates[winnerIndex].name,
               allCandidates[winnerIndex].symbol, maxVotes);
    } else {
        printf("No winner.\n");
    }
}
