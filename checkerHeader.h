#ifndef CHECKERHEADER_H
#define CHECKERHEADER_H

//structs to define the Cage data structure
typedef struct Coord {
    int x, y;
  } Coord;

  typedef struct Cage {
    int sum;
    int size;
    struct Coord coord[81];
  } Cage;

extern int cageCount;
extern int N;

Cage* loadFile(char* fileName);
int** loadSolution(char* solutionFile);
bool checkCages(Cage* cages, int numberOfCages, int** solution);
int sumCage(Cage* cage, int** solution);
bool checkProblemValid(Cage* cages, int n, int cageCount);
bool checkNoDuplicatesCages(Cage* cages, int** solution);
int compare(const void * a, const void * b);
bool duplicateCageCheck(Cage cage, int** solution);
bool checkSudokuGrid(int** solution);
bool checkRow(int** solution, int row);
bool checkCol(int** solution, int col);
bool checkRowColSums(int** solution);
bool checkRowSum(int** solution, int row);
bool checkColSum(int** solution, int col);
bool checkBoxes(int** solution, int row, int col);
bool validBoxes(int** solution);


#endif // CHECKERHEADER_H