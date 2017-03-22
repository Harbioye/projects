char** makeClearGrid(int N);

int** makeClearAgeGrid(int N);

void getNeighborhood(const char** grid, int N, int row, int col, int& countB, int& countF, int& countR, int& countG);

char update(const char** grid, int N, int currRow, int currCol, int age, int countB, int countF, int countR, int countG);

int** ageUpdate(int gridSize, char** newGrid, int** ageGrid, char** grid);

char** gridA(int gridSize);

char** gridB(int gridSize);

char** gridC(int gridSize);

void printGrid(const char** grid, int N);

char** userInput(int& gridSize, int& cycles, char cases);