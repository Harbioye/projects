#include <iostream>
#include "PredatorPrey.h"

using namespace std;

const int ALIVE = 1;
const int DEAD  = 0;

//A function that makes clear N x N grid of characters.
char** makeClearGrid(int N) {
   char** grid = new char*[N];
   for(int i = 0; i < N; ++i) {
      grid[i] = new char[N];
      for(int j = 0; j < N; ++j) {
         grid[i][j] = ' ';
      }
   }
   return grid;
}

//A function that makes an N x N grid to keep track of the cell age initialized to 0
int** makeClearAgeGrid(int N) {
   int** grid = new int*[N];
   for(int i = 0; i < N; ++i) {
      grid[i] = new int[N];
      for(int j = 0; j < N; ++j) {
         grid[i][j] = 0;
      }
   }
   return grid;
}

/*A function that finds neighbors of the  current row and column.
*and counts the number of life forms of a specific type in the neighborhood of a given cell
*/

//using a reference to keep track of counts for each animals in the neighborhood.
void getNeighborhood(const char** grid, int N, int row, int col, int &countB , int &countF , int &countR, int &countG){
   
   //fields
   int currRow;
   int currCol;
   countB = 0;
   countF = 0;
   countR = 0;
   countG = 0;
   
   //begin int i and int j at -1 because it makes the code more efficient where currROW or currCol equals 0.
   for(int i = -1; i < 2; i++){
      for(int j = -1; j < 2; j++){
         currRow = row + i;               //current row.
         currCol = col + j;               //current column.
         
         //keeps current row and col in bounds
         if(currRow >= 0 && currRow < N && currCol >= 0 && currCol < N){
            if(grid[currRow][currCol] == 'B')
            {
               ++countB;
            }
            if(grid[currRow][currCol] == 'F')
            {
               ++countF;
            }
            if(grid[currRow][currCol] == 'R')
            {
               ++countR;
            }
            if(grid[currRow][currCol] == 'G')
            {
               ++countG;
            }
         }
      }
   }
}

//A function that increases the age of each cell on the grid once each cycle
int** ageUpdate(int gridSize, char** newGrid, int** ageGrid, char** grid)
{
   for(int i = 0; i < gridSize; ++i) {
      for(int j = 0; j < gridSize; ++j) {
         
         //check each predator age with regards to survival rules.
         if(newGrid[i][j] == grid[i][j]){
            ageGrid[i][j]++;
         }  
         else{
            ageGrid[i][j] = 0;
         }  
      }
   }
   return ageGrid;
}

//A function to update current cell after each cycle based on survival rules.
char update(const char** grid, int N, int currRow, int currCol, int age, int countB, int countF, int countR, int countG)
{
   age = 0;
  /*Empty if the Badger is currently at age 4;
  *otherwise Empty, if there is only one Badger but there are more than one Fox in the neighborhood;
  *otherwise, Empty, if Badgers and Foxes together outnumber Rabbits in the neighborhood;
  *otherwise, Badger (the Badger will live on).
  */
   
  //life form of a badger.
   if(grid[currRow][currCol] == 'B'){
      if(age == 4){
         return 'E';
      }
      else if((countB == 1 && countF > 1)){
         return  'E';
      }
      else if((countB + countF) > countR){
         return 'E';
      }
      return  'B';
   }
      
   /*Empty if the Fox is currently at age 5;
    *Empty, if there are at least as many Badgers as Foxes in the neighborhood;
    *Empty, if Badgers and Foxes together outnumber Rabbits in the neighborhood;
    *otherwise, Fox (the Fox will live on).
    */
   
   //life form of a fox.
   else if(grid[currRow][currCol] == 'F') {
      if(age == 5){
         return 'E';
      }
      else if(countB >= countF){
         return 'E';
      }
      else if((countB + countF) > countR){
         return 'E';
      }
      return 'F';
   }
      
     /*Empty if the Rabbit's current age is 3;
      *otherwise, Empty if there are at least as many Foxes and Badgers together as Rabbits in the neighborhood;
      *otherwise, Empty if there is no Grass in the neighborhood (the Rabbit needs food)
      *otherwise, Rabbit (the Rabbit will live on).
      */
   
   //life form of a rabbit.
   else if(grid[currRow][currCol] == 'R'){
      if(age == 3){
         return'E';
      }
      else if((countB + countF) >= countR){
         return 'E';
      }
      else if(countG == 0){
         return 'E';
      }
      return 'R';
   }
     
   /*Rabbit if more than one Rabbit and more than one Grass in the neighborhood;
    *otherwise, Grass if more Grasses than Rabbits in the neighborhood;
    *otherwise, Empty.
   */
   
   //life form on a Grass.
   else if(grid[currRow][currCol] == 'G'){
      if(countR > 1 && countG > 1){
         return 'R';
      }
      else if(countG > countR){
         return 'G';
      }
      return  'E';
   }
    
    /*Badger, if more than one Badger and no more Foxes than Badgers in the neighborhood;  
     *otherwise, Fox, if more than one Fox and more Foxes than Badgers in the neighborhood;
     *otherwise, Rabbit, if the number of Rabbits exceeds one in the neighborhood;
     *otherwise, Grass, if at least one neighboring Grass.
     *otherwise, Empty.
     */
      
   //life form on an Empty.
   else if (grid[currRow][currCol] == 'E'){
      if(countB > 1 && countB >= countF){
         return 'B';
      }
      else if(countF > 1 && countF > countB){
         return 'F';
      }
      else if(countR > 1){
         return 'R';
      }
      else if(countG > 0){
         return 'G';
      }
      return 'E';
   }
   cerr << grid[currRow][currCol] << " is an invalid character" << endl;
   return grid[currRow][currCol];
}
            
//A function for 3x3 grid
char** gridA(int gridSize)
{
   char** grid = makeClearGrid(gridSize);

   //3x3 grid and 1 cycle.
   grid[0][0] = 'R';
   grid[0][1] = 'R';
   grid[0][2] = 'F';
   
   grid[1][0] = 'G';
   grid[1][1] = 'F';
   grid[1][2] = 'R';
   
   grid[2][0] = 'G';
   grid[2][1] = 'R';
   grid[2][2] = 'B';
   
   return grid;
}   

//A function for 6x6 grid
char** gridB(int gridSize){
   //create a clear char array grid before assigning it elements.  
   char** grid = makeClearGrid(gridSize);

   //6x6 grid and 10 cycles. 
   grid[0][0] = 'R';
   grid[0][1] = 'E';
   grid[0][2] = 'F';
   grid[0][3] = 'G';
   grid[0][4] = 'G';
   grid[0][5] = 'R';
   
   grid[1][0] = 'E';
   grid[1][1] = 'F';
   grid[1][2] = 'R';
   grid[1][3] = 'E';
   grid[1][4] = 'G';
   grid[1][5] = 'R';
   
   grid[2][0] = 'B';
   grid[2][1] = 'E';
   grid[2][2] = 'F';
   grid[2][3] = 'G';
   grid[2][4] = 'B';
   grid[2][5] = 'F';
   
   grid[3][0] = 'F';
   grid[3][1] = 'G';
   grid[3][2] = 'G';
   grid[3][3] = 'F';
   grid[3][4] = 'F';
   grid[3][5] = 'E';
   
   grid[4][0] = 'R';
   grid[4][1] = 'B';
   grid[4][2] = 'B';
   grid[4][3] = 'B';
   grid[4][4] = 'E';
   grid[4][5] = 'F';
   
   grid[5][0] = 'G';
   grid[5][1] = 'F';
   grid[5][2] = 'E';
   grid[5][3] = 'E';
   grid[5][4] = 'R';
   grid[5][5] = 'R';
   
   return grid;  
}

//A function for 10x10 grid
char** gridC(int gridSize)
{
   char** grid = makeClearGrid(gridSize); 
     
   //10x10 grid and 7 cycles.
   grid[0][0] = 'B';
   grid[0][1] = 'E';
   grid[0][2] = 'E';
   grid[0][3] = 'E';
   grid[0][4] = 'E';
   grid[0][5] = 'E';
   grid[0][6] = 'G';
   grid[0][7] = 'G';
   grid[0][8] = 'G';
   grid[0][9] = 'G';
   
   grid[1][0] = 'E';
   grid[1][1] = 'E';
   grid[1][2] = 'E';
   grid[1][3] = 'F';
   grid[1][4] = 'F';
   grid[1][5] = 'F';
   grid[1][6] = 'G';
   grid[1][7] = 'G';
   grid[1][8] = 'E';
   grid[1][9] = 'G';
   
   grid[2][0] = 'E';
   grid[2][1] = 'E';
   grid[2][2] = 'E';
   grid[2][3] = 'E';
   grid[2][4] = 'E';
   grid[2][5] = 'E';
   grid[2][6] = 'G';
   grid[2][7] = 'B';
   grid[2][8] = 'G';
   grid[2][9] = 'G';
   
   grid[3][0] = 'E';
   grid[3][1] = 'G';
   grid[3][2] = 'B';
   grid[3][3] = 'E';
   grid[3][4] = 'E';
   grid[3][5] = 'E';
   grid[3][6] = 'E';
   grid[3][7] = 'E';
   grid[3][8] = 'B';
   grid[3][9] = 'E';

   grid[4][0] = 'E';
   grid[4][1] = 'E';
   grid[4][2] = 'F';
   grid[4][3] = 'G';
   grid[4][4] = 'E';
   grid[4][5] = 'G';
   grid[4][6] = 'E';
   grid[4][7] = 'B';
   grid[4][8] = 'B';
   grid[4][9] = 'B';
   
   grid[5][0] = 'E';
   grid[5][1] = 'R';
   grid[5][2] = 'E';
   grid[5][3] = 'R';
   grid[5][4] = 'E';
   grid[5][5] = 'F';
   grid[5][6] = 'E';
   grid[5][7] = 'R';
   grid[5][8] = 'E';
   grid[5][9] = 'G';
   
   grid[6][0] = 'R';
   grid[6][1] = 'R';
   grid[6][2] = 'R';
   grid[6][3] = 'E';
   grid[6][4] = 'E';
   grid[6][5] = 'G';
   grid[6][6] = 'F';
   grid[6][7] = 'E';
   grid[6][8] = 'R';
   grid[6][9] = 'E';
   
   grid[7][0] = 'R';
   grid[7][1] = 'R';
   grid[7][2] = 'R';
   grid[7][3] = 'R';
   grid[7][4] = 'B';
   grid[7][5] = 'E';
   grid[7][6] = 'E';
   grid[7][7] = 'F';
   grid[7][8] = 'R';
   grid[7][9] = 'E';
   
   grid[8][0] = 'B';
   grid[8][1] = 'R';
   grid[8][2] = 'F';
   grid[8][3] = 'R';
   grid[8][4] = 'R';
   grid[8][5] = 'F';
   grid[8][6] = 'F';
   grid[8][7] = 'E';
   grid[8][8] = 'E';
   grid[8][9] = 'E';
   
   grid[9][0] = 'E';
   grid[9][1] = 'E';
   grid[9][2] = 'R';
   grid[9][3] = 'R';
   grid[9][4] = 'R';
   grid[9][5] = 'E';
   grid[9][6] = 'F';
   grid[9][7] = 'F';
   grid[9][8] = 'E';
   grid[9][9] = 'E';
   
   return grid;
}

//A function that prints a grid with labels.
void printGrid(const char** grid, int N){
   cout << endl;
   for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){
         cout << grid[i][j] <<" ";
      }
      cout<<endl;
   }
   cout<<endl;
}

/*A function that accepts input for specifying which test cases to run.
* return the each relevant grid
*/
char** userInput(int &gridSize, int &cycles, char cases)
{
   char** grid = NULL;
   
   if(cases == 'A'){
      gridSize = 3;
      cycles = 1;
      grid = gridA(gridSize);
   }
   else if(cases == 'B'){
      gridSize = 6;
      cycles = 10;
      grid = gridB(gridSize);
   }
   else if(cases == 'C'){
      gridSize = 10;
      cycles = 7;
      grid = gridC(gridSize);
   }
   else{
      cout << "Try either A, B, or C...!!!" << endl;
   }
   return grid;
}


int main()
{  
   //fields
   int gridSize, cycles;
   int countB, countF, countR, countG;
   char cases, userResponse;
   
   //set userResponse to Y for the first simulation.
   userResponse = 'Y';
   
   //if grid equals NULL ask for user input.
   while(userResponse == 'Y'){
   
      //set grid to NULL to avoid unrequired items in the grid.
      char** grid = NULL;
      
      while (grid == NULL) {
         cout << "Which test case would you like to run? ";
         cout << "\n\tTest Cases -- A,B,C :";
         cin >> cases ;
      
      //creates a grid of a size based on user input.
         grid = userInput(gridSize,cycles,cases);
      } 
   
      char** newGrid = makeClearGrid(gridSize);
      int** ageGrid = makeClearAgeGrid(gridSize);
   
      for (int l = 0; l < cycles; ++l) {
         printGrid((const char**)grid, gridSize);
         for(int i = 0; i < gridSize; ++i) {
            for(int j = 0; j < gridSize; ++j){ 
               getNeighborhood((const char**) grid,gridSize,i,j,countB,countF,countR,countG);
                              ageUpdate(gridSize,newGrid,ageGrid,grid);

               newGrid[i][j] = update((const char**)grid,gridSize,i,j,ageGrid[i][j],countB,countF,countR,countG);
            }
         }
      // swap grid with newgrid.
         char** temp = grid;
         grid = newGrid;
         newGrid = temp;
      }
      printGrid((const char**)grid, gridSize);
   
   //everytime there is a new GRID there has to be a corresponding delete because there is no garbage collector in C++.
      for(int i = 0; i < gridSize; ++i){
         delete[] grid[i];
         delete[] newGrid[i];
      }
      delete [] grid;
      
      delete [] newGrid;
   
      cout << "Would you like to run another Test case? (Y/N); ";  
      cin >> userResponse;
   } 
   cout << "Good Bye" << endl;   
   return 0;
}

