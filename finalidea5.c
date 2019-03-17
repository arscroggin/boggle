/*
CS 201 Portfolio Project
Allison Price

Uses an array of structs and an adjacency maxtrix to represent the boggle board
runs a DFS on the boggle board to find all possible letter combinations
dictionary file is stored into a trie

step 1. find out how to find all words efficiently
      - figure out trie
      - figure out finding all letter combinations

step 2. figure out game play... make a gameplay function and put it all in the timer loop

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


struct Letter {
  char letter; // letter value in the board
  int number; // defines which node in the graph it is
  int visited; // 0 if unvisited and 1 if visited
};


struct Edge {  // stores the graph's edges
   int source, dest;

};

struct TrieNode
{
    struct TrieNode *children[27];
    char letter;
    int end; // 1 if the end of a word and 2 if not
};

struct Trie
{
   struct TrieNode *roots[27]; // trying to make one trie that I can search

};



struct Edge *findEdges (int boardSize, int numEdges, struct Letter array[][boardSize + 1]) { // finds the edges in the 2d array


   struct Edge *boardEdges = malloc(sizeof(struct Edge) * numEdges); // allocates memory
   int a = 0;

      for (int i = 0; i < boardSize; i++) {
         for (int j = 0; j < boardSize - 1; j++ ) {

             boardEdges[a].source = array[i][j].number; // the horizontal edges
             boardEdges[a].dest = array[i][j + 1].number;
             a++;
         }
       }

    int b = a;

     for (int i = 0; i < boardSize -1; i++) {
        for (int j = 0; j < boardSize; j++ ) {

           boardEdges[b].source = array[i][j].number;   // the vertical edges
           boardEdges[b].dest = array[i + 1][j].number;
           b++;
    }
  }

   int c = b;

   for (int i = 0; i < boardSize - 1; i ++) {
     for (int j = 0; j < boardSize - 1; j++) {

       boardEdges[c].source = array[i][j].number; // diagonal right edges
       boardEdges[c].dest = array[i + 1][j + 1].number;
       c++;
     }
   }


   int d = c;

   for (int i = 0; i < boardSize - 1; i ++) {
     for (int j = 1; j < boardSize; j++) {

       boardEdges[d].source = array[i][j].number; // diagonal left edges
       boardEdges[d].dest = array[i + 1][j - 1].number;
       d++;

     }
   }

  return boardEdges;
}



void printAllCombos(int start, int dest, int boardSize, int diceNum, int pathIndex, int visited[], int path[], int **adj, struct Letter boggle[][boardSize + 1]) {

  visited[start] = 1; // true
  path[pathIndex] = start;
  pathIndex++;

  if (start == dest) {

    for (int i = 0; i < pathIndex; i++) {
      printf("%d -> ", path[i]);                     // this should be printing the current path (by vertex number)

    }
   printf("\n");
  }

 else {
   for (int j = 0; j < diceNum; j++) {
     if(!visited[j] && adj[start][j] == 1) {
       printAllCombos(j, dest, boardSize, diceNum, pathIndex, visited, path, adj, boggle);
     }
   }
 }

 pathIndex--;
 visited[start] = 0;

}


void findCombos(int diceNum, int start, int dest, int boardSize, int **adj, int *visited, struct Letter boggle[][boardSize + 1])
{                  // GOAL: perform dfs on each node and return
  char **comboList;//  a list of all possible letter combinations
  int pathIndex = 0;
  int path[boardSize * boardSize];

 printAllCombos(start, dest, boardSize, diceNum, pathIndex, visited, path, adj, boggle);

}


void setTimeout(int milliseconds)
{

    int milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;    // this will hopefully be the timer for game play
    int end = milliseconds_since + milliseconds;
    do {
        milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
    } while (milliseconds_since <= end);
}


// Returns new trie node (initialized to NULL)
struct TrieNode *getNode(void)
{
    struct TrieNode * new = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (new)
    {
        new -> end = 2;
        for (int i = 0; i < 27; i++) {
            new -> children[i] = NULL;
        }
    }

    return new;
}


// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *branch, char *str)
{
  struct TrieNode * newNode;

  while (*str) {
    if (branch->children[*str - 'a'] == NULL) {
       newNode = getNode();
       branch->children[*str - 'a'] = newNode;
       newNode->letter = *str;
    }

    str++;

    if (str != NULL) {
      newNode->end = 2;
    }
    else {
      newNode->end = 1;
    }
  }
}


// Returns 1 if key presents in trie, else 2
int search(struct Trie* trie, char *str)
{
    printf("Entered the search function\n");
    struct TrieNode *temp = trie -> roots[0];

    while(*str) {
      printf("Entered the while loop of the search function\n");
      temp = temp -> children[*str - 'a'];
      if (temp == NULL) {
        return 2;
      }
     str++;
     printf("Incremented str\n");
    }
    printf("Returning from the search function\n");
    return temp -> end;
  }



/*
char **checkTrie(trie, dfsList) { // compares the words found in the DFS to the trie to see if they exist
                                  // should return a list of all possible words in the board


return wordList;
}

int userWord(char **wordList, char *userWord) {   // see if the word entered by the user is valid

  for (int a = 0; a < sizeof(wordList); a ++) {
     if (strcmp (word, wordList[a]) == 0) {
        return 1; // it IS in the list
     }

     else {
       return 2; // word is NOT in list
     }
   }
}

void twoPlayer() {}
void onePlayer() {}
void gamePlay() {   // this is gonna be so that the game
                   //  can keep score for the multiple games

// literally everything in main goes here pretty much. main should end up being like 3 lines

}

*/

int main(void) {

  printf("\n\nBB BB           OOOO            GGG                GGG           LL            EEEEEEEE         \n");
  printf("BB    BB      OO    OO        GG   GG            GG   GG         LL            EE               \n");
  printf("BB     BB    OO      OO      GG     GG          GG     GG        LL            EE               \n");
  printf("BB    BB    OO        OO    GG                 GG                LL            EE               \n");
  printf("BB BB       OO        OO    GG                 GG                LL            EEEEEE           \n");
  printf("BB   BB     OO        OO    GG      GGGGGG     GG      GGGGGG    LL            EE               \n");
  printf("BB     BB   OO        OO    GG        GG       GG        GG      LL            EE               \n");
  printf("BB      BB   OO      OO      GG      GG         GG      GG       LL            EE               \n");
  printf("BB     BB     OO    OO        GG    GG           GG    GG        LL            EE               \n");
  printf("BB BBBB         OOOO            GGGG               GGGG          LLLLLLLLLLL   EEEEEEEE         \n");


  char die0[6] = {'R', 'I', 'F', 'O', 'B', 'X'};
  char die1[6] = {'I', 'F', 'E', 'H', 'E', 'Y'};
  char die2[6] = {'D', 'E', 'N', 'O', 'W', 'S'};
  char die3[6] = {'U', 'T', 'O', 'K', 'N', 'D'};
  char die4[6] = {'H', 'M', 'S', 'R', 'A', 'O'};
  char die5[6] = {'L', 'U', 'P', 'E', 'T', 'S'};
  char die6[6] = {'A', 'C', 'I', 'T', 'O', 'A'};
  char die7[6] = {'Y', 'L', 'G', 'K', 'U', 'E'};
  char die8[6] = {'Q', 'B', 'M', 'J', 'O', 'A'};
  char die9[6] = {'E', 'H', 'I', 'S', 'P', 'N'};
  char die10[6] = {'V', 'E', 'T', 'I', 'G', 'N'};
  char die11[6] = {'B', 'A', 'L', 'I', 'Y', 'T'};
  char die12[6] = {'E', 'Z', 'A', 'V', 'N', 'D'};
  char die13[6] = {'R', 'A', 'L', 'E', 'S', 'C'};
  char die14[6] = {'U', 'W', 'I', 'L', 'R', 'G'};
  char die15[6] = {'P', 'A', 'C', 'E', 'M', 'D'};

  char *diceArray[17];

  diceArray[0] = die0; // look here to POTENTIALLY add qu
  diceArray[1] = die1;
  diceArray[2] = die2;
  diceArray[3] = die3;
  diceArray[4] = die4;
  diceArray[5] = die5;
  diceArray[6] = die6;
  diceArray[7] = die7;
  diceArray[8] = die8;
  diceArray[9] = die9;
  diceArray[10] = die10;
  diceArray[11] = die11;
  diceArray[12] = die12;
  diceArray[13] = die13;
  diceArray[14] = die14;
  diceArray[15] = die15;

   int bsize = 0;
   char gameMode;
   char dictionaryFile[50];

   printf("\n\nChoose Game Mode: \nS - Single Player \nT - Two Player \n");
   scanf("%c", &gameMode);

   if (gameMode != 'S' && gameMode != 's' && gameMode != 'T' && gameMode != 't') { // if not s or t, then it exits the game
     printf("Not a valid game mode! Try again!");
     return 0;
   }

   printf("\n\nBoard Size (in form NxN)? Enter a number: ");
   scanf("%d", &bsize);
   printf("\n\n");

   //printf("What is the name of the dictionary file? Put it in quotation marks!\n");
   //scanf("%s", dictionaryFile);

   if ((gameMode == 'S') || (gameMode == 's')) { // for single player
      printf("The timer starts now!\n\n");
      int pscore, cscore, p, c;

  /*    int delay = 180;
      time_t start,end;
      time (&start);

      // counter downtime for game play while the delay with more 0           // this is the timer
      do {                                                                    // but i havent figured out how to make the
          // erase the previous line and display remain of the delay          // game run within the time? when this
          printf("\033[ASeconds left: %d\n", delay);                          // displays it just displays the countdown
          setTimeout(1000);
          delay--;

      } while (delay >= 0);

      time (&end);
*/

/*
      if (pscore > cscore) {
        printf("You win! The computer only scored %d points!\n", cscore);
        p++;
      }

      else if (cscore > pscore) {
        printf("You lose! The computer scored %d points!\n", cscore);
        c++;
      }

      else {
        printf("It's a tie!");
        p++;
        c++;
      }

    //  printf("The computer found the following words: %s ", wordList);
*/

   }

   else  { // two player option
      printf("Player 1 goes first! The timer starts now!\n\n");
      int p1, p2, p1score, p2score;

/*
      int delay = 180;
      time_t start,end;
      time (&start);

      // counter downtime for game play while the delay with more 0
      do {
          // erase the previous line and display remain of the delay
          printf("\033[ASeconds left: %d\n", delay);
          setTimeout(1000);
          delay--;

      } while (delay >= 0);

      time (&end);
*/
/*
      printf("Player 2's Turn! The timer starts now!\n\n");

      if (p1score > p2score) {
        printf("Player 1 Wins!\n");
        p1++;
      }

      else if(p2score > p1score) {
        printf("Player 2 Wins!\n");
        p2++;
      }

      else {
        printf("It's a tie!");
        p1++;
        p2++;
      }
*/
   }

   int numDice = bsize * bsize;
   int a = numDice - 1;
   int score = 0;
   int numEdges = (2 * ((bsize - 1)*(bsize - 1))) + 2 * ((bsize) * (bsize - 1));
   char board[bsize + 1][bsize + 1];
   char word[100];

   struct Letter boggle[bsize + 1][bsize + 1];

   srand(time(0));
   int k = 0;
   for (int i = 0; i < bsize; i++) {
     for (int j = 0; j < bsize; j++) {
       int whichDice = (rand() % 15); // chooses 1-16 dice
       int diceSide = (rand() % 6 ); // chooses 1-6 sides of dice

         if (a % bsize != 0) {
            printf("%c  ", diceArray[whichDice][diceSide]);// generates the board
            board[i][j] = diceArray[whichDice][diceSide];// store the generated letters in the array
            boggle[i][j].letter = diceArray[whichDice][diceSide];
            boggle[i][j].visited = 0;
            boggle[i][j].number = k;
            k ++;

         }

         else {
           printf("%c \n", diceArray[whichDice][diceSide]);
           board[i][j] = diceArray[whichDice][diceSide];
           boggle[i][j].letter = diceArray[whichDice][diceSide];
           boggle[i][j].visited = 0;
           boggle[i][j].number = k;
           k ++;

         }
       }

         printf("\n\n");
   }



   for (int m = 0; m < bsize; m++) {
     for(int n = 0; n < bsize; n++) {
       printf("Letter = %c, Visited = %d, Number = %d\n", boggle[m][n].letter, boggle[m][n].visited, boggle[m][n].number);
     }
   }

   struct Edge *edges = {findEdges(bsize, numEdges, boggle)};
   int **adjMatrix = (int **)malloc(numDice * sizeof(int *));

   for (int a = 0; a < numDice; a++){
     adjMatrix[a] = (int *)malloc(numDice * sizeof(int));
   }

   for (int q = 0; q < numDice; q++) {
     for (int r = 0; r < numDice; r++) {
       adjMatrix[q][r] = 0;
     }
   }

   for (int a = 0; a < numEdges; a ++) {
      adjMatrix[edges[a].source][edges[a].dest] = 1; // adds the connections to the matrix
      adjMatrix[edges[a].dest][edges[a].source] = 1;
   }

for (int o = 0; o < numDice; o++) {
  for(int p = 0; p < numDice; p++) {
    printf("%d ", adjMatrix[o][p]);  // prints the adjacency matrix
  }

  printf("\n");
}

int visited[numDice];
char **letterCombos;


for (int dest = 1; dest < numDice; dest ++) {
  for (int r = 0; r < numDice; r++) {
    visited[r] = 0;
  }

    findCombos(numDice, 0, dest, bsize, adjMatrix, visited, boggle) ;  // generates possible words in one direction

}



/*
if(userWord(wordList, word) == 1) {  // if the word exists in the board then determine the point value of the word
  int size = sizeof(word);

  if (size >= 8) {
    score += 11;
  }
  else if (size == 7) {
    score += 4;
  }
  else if (size == 6) {
    score += 3;
  }
  else if (size == 5) {
    score += 2;
  }
  else if ((size == 4) || (size == 3)) {
    score += 1;
  }
  else {
    score = score;
  }
}

else if (userWord(wordList, word) == 2) { // give a notice if the word doesn't exist in the board
  printf("Word doesn't exist!\n");
}*/


FILE *dictionary;
char str[20];
char alphabet[27];
int w = 0;
int insertedWords = 0;


struct Trie* trie = (struct Trie*)malloc(sizeof(struct Trie));

for (int i = 0; i < 27; i++) {
  trie -> roots[i] = NULL;
}

// dictionary = fopen("C:\\cygwin64\\home\\ally price\\cs201projectidea\\words.txt", "r"); 
dictionary = fopen("words.txt", "r");
if (dictionary == NULL) {
  printf("Error! Can't find the dictionary file!\n");
}
else {
    // this is seg faulting after opening the file
    printf("\n\nOpened file successfully!\n");
    struct TrieNode *root = getNode();// need to call this for each new first letter!

    while(fgets(str, sizeof(str), dictionary) != NULL) {
       
       if ((strlen(str) > 2) && (!(str[0] >= 'A' && str[0] <= 'Z'))) {

           int firstLetterIndex = str[0] - 'a';

           if (trie->roots[firstLetterIndex] == NULL) { // if the first letter isnt in the array of first letters
              trie->roots[firstLetterIndex] = getNode();
              trie->roots[firstLetterIndex]->letter = str[0];
              insert(trie->roots[firstLetterIndex], &str[1]);
           }
           else {
              int stringIndex = 1;
              int nextCharIndex = str[stringIndex] - 'a';
              struct TrieNode *nodePtr = trie->roots[firstLetterIndex]->children[nextCharIndex];

              while (str[stringIndex] != '\0') {
                 if (nodePtr == NULL) {
                    nodePtr = getNode();
                    insert(nodePtr, &str[stringIndex]);
                 }
                 
                 stringIndex++;
                 nodePtr = nodePtr->children[str[stringIndex] - 'a'];
              }
            }
        }

        insertedWords++;
        printf("Inserted %s", str);
      }
    }


 printf("\n\n%d Words were inserted into the trie\n", insertedWords);
/*
for(int a = 0; a < 4; a ++) {
   printf("\nEnter Word (one by one): ");
   scanf("%s", word);

   if (strlen(word) > bsize*bsize) {  // if the word has more letters than there are dice on the board
      printf("Not a valid word!");
   }

   else {
     int there = search(trie, word);
     if (there == 1) {
       printf("Nice!\n");
     }

     else if (there == 2) {
        printf("Word not in dictionary! :( \n");

     }
  }
}
*/

fclose(dictionary);
free(adjMatrix); // free the allocated space
//free(root);

  return 0;
}
