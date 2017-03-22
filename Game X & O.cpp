/* COURSE : Topics Java 
   CIS403 
   Project1.
*/

#include <iostream>
#include <cstdlib>      //for rand
#include <ctime> // Needed for the true randomization

using namespace std;
const char NOWIN = '!';
char board[3][3];
int Xwins = 0;
int Owins = 0;
int tie = 0;
   
void copyBoard(const char original[3][3], char xerox[3][3]);
bool makeMove(char board[3][3], char move, char player);
char getXMoveAI(const char board[3][3]);

//prints the board with labels for options.
void print(const char board[3][3])    //function prototype
{  
   for(int row = 0 ; row < 3 ; row++)
   {
      for(int column=0 ; column<3 ; column++)
      {
         cout << board[row][column]; // print the array element
         if (column < 2) 
         {  
                  // print the separator between the element for 2 time beacuse for the last element doesnt need to print |
            cout << "|";
         }
      }
      if (row < 2)
         cout << "\n------ \n"; //after execution of inner loop print the line separator.
   }
   cout << " \n " << endl;
}

// returns 'X', 'O', or a non-winning character of your choosing
char winner(const char board[3][3])
{
   // Checks for horizontal win
   for (int i = 0; i < 3; ++i)
   {
      if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
         return board[i][0];
   }

    // Checks for vertical win
   for (int i = 0; i < 3; ++i)
   {
      if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
         return board[0][i];
   }
    
    // Check for diagonal win (upper left to bottom right)
   if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
   {
      return board[0][0];
   }
    
    // Check for diagonal win (upper right to bottom left)
   if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
   {
      return board[0][2];
   }
    
    //if no win, return;
   else
   {
      return NOWIN;
   } 
}

//move should be one of 9 characters 'A' to 'I', player should be 'X' or 'O', should return true if move was successfully made at move position, false otherwise.
bool makeMove(char board[3][3], char move, char player)
{
   int Col = 0;
   int Row = 0;
   if(move == 'X' || move == 'O')
   {
      return false;
   }
   for(Row = 0; Row < 3; ++Row)
   {
      for(Col = 0; Col < 3; ++Col)
      
         if(board[Row][Col] == move) 
         {
            // if row and col are in bounds
            board[Row][Col] = player;
            return true;
         }
   }
   return false;
}

// returns the char at the location that the AI chooses to move. You can have multiple versions of this function with varying complexity, one for X and one for O, or you could make one AI function that has options as second and third parameters for the player, and the complexity.
char getXMoveAI(const char board[3][3])
{
   //use random object to determine what game played.
   char randMove;	
   randMove=rand()%9+'A'; // Randomizing the number between 0-3.
   static char scratch[3][3];
   
   // check for winning move
   char players[2];
   players[0] = 'X';
   players[1] = 'O';
   
   // loop 9x
   for(int j = 0; j < 2; j++)
   { 
      for(int i = 0; i < 9; i++)
      {
         // copy board to scratch
         copyBoard(board,scratch);
         
         // make nextTry char.
         char nextTry = 'A' + i;
         
         //call makeMove.
         char turn = players[j];
      
         makeMove(scratch, nextTry, turn);
       
         // check for winner
         if(winner(scratch) == turn)
         {
            return nextTry;      // if winner, return try
         }
      }
   }
   return randMove;
}

//make a function called scratch;
void copyBoard(const char original[3][3], char xerox[3][3])
{  
   for(int row = 0; row < 9; row++)
   {
      for(int col = 0; col < 9; col++){
         xerox[row][col] = original[row][col]; 
      }
   }
}

// plays a full tic-tac-toe game, and returns the winner of the game.
char playGame()
{
   char move; 

   board[0][0]='A';
   board[0][1]='B';
   board[0][2]='C';
   board[1][0]='D';
   board[1][1]='E';
   board[1][2]='F';
   board[2][0]='G';
   board[2][1]='H';
   board[2][2]='I';
   
   //create an object to store user input
   char turn;

   //use random object to determine what player goes first.
   int randNum=rand()%2; // Randomizing the number between 0-1.
   cout << "\nGetting a random number between 0-1 to determine what player goes first: \n";
   
   if(randNum == 0 ) {
      turn='X';
      cout<<"Player X goes first \n";
   }
   else {
      turn ='O';
      cout<<"Player O goes first \n";
   }
   
   char wins = NOWIN;   
   
   // turns of the game
   for(int i = 0; i < 9 && wins == NOWIN; i++)
   {
      cout<<"\n";
      print(board);
      do {
         if(turn == 'X')
         {
            cout << "Player X, Enter move; ";
            move = getXMoveAI(board);
            cout << move;
            cout << " \n " << endl;
         } 
         else
         {
            cout << "Player O, Enter move; ";
            cin >> move;
            cout << " \n " << endl;
         }
      }  while(!makeMove(board,move,turn));
   
      wins = winner(board);
      
      // turn is over
      // switch players
      if(turn == 'O')
      {
         turn = 'X';              
      }
      else
      {
         turn = 'O';
      }
   }
 
   print(board);     //print board to display wininng game
         
   return winner(board);
}

int main()
{      
   char YourChoice;
  
   srand(time(0)); // This will ensure a really randomized number by help of time.

   cout << "Welcome to Harbioye's X & O game \n";
   cout << "\n\t\t Instructions \n";
   cout << "\n\t There are two players -- the AI and the player -- with tiles X & O \n";
   cout << "\t NOTE; Your input is case sensitive. So, please do activate capsLock. \n" << endl; 
   cout << "\t Press P to Play or another alphabeth to Quit:\n";
   cin >> YourChoice;
   
   while(YourChoice == 'P')
   {
      playGame();
      
      if(winner(board) == 'X')
      {
         cout << "The winner is player " << winner(board) << endl;
         Xwins++;
      }
      else if(winner(board) == 'O')
      {
         cout << "The winner is player " << winner(board) << endl;
         Owins++;
      }
      else if(winner(board) == NOWIN)
      {
         cout << "There is tie " << winner(board) << endl;
         tie++;
      }
    
      cout << endl;
      cout << "X | O | tie";
      cout << "\n------------ \n"; 
      cout << Xwins << " | " << Owins << " | " << tie << endl;
   
      cout << "\nEnter P to play again; ";  
      cin >> YourChoice;
   }
   cout << "Good Bye!!" << endl;
   return 0;     
}

