#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "checkerHeader.h"

int cageCount = 0;
int N = 0;

int main(int argc, char** argv) {

  Cage* cages = loadFile(argv[1]);
  int** solution = loadSolution(argv[2]);

  bool squaresPartOfCage = checkCages(cages, cageCount, solution);
  bool problemCheck = checkProblemValid(cages, N, cageCount);
  bool uniqueCages = checkNoDuplicatesCages(cages, solution);
  bool checkedSudokuGrid = checkSudokuGrid(solution);
  bool checkedRowColSums = checkRowColSums(solution);
  bool validBox = validBoxes(solution);

  printf("%d\n",squaresPartOfCage);
  printf("%d\n",problemCheck);
  printf("%d\n",uniqueCages);
  printf("%d\n",checkedSudokuGrid);
  printf("%d\n",checkedRowColSums);
  printf("%d\n",validBox);

  if(!uniqueCages || !checkedSudokuGrid || !validBox){
    printf("INVALIDSOL\n");
  }

  else if(!squaresPartOfCage || !problemCheck){
    printf("INVALIDPROBLEM\n");
  }
  else if (!checkedRowColSums ){
    printf("INCOMPLETE\n");
  }
  else{
    printf("SOLVED\n");
  }
}
