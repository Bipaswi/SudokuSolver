#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "checkerHeader.h"

//checks if there are any duplicate numbers in a cage
bool checkNoDuplicatesCages(Cage* cages, int** solution){
  //int check[N*N];
  int i = 0;
  while(i <= cageCount){
    if(duplicateCageCheck(cages[i], solution) == false){
      //printf("Invalid Problem in cages\n");
      return false;
    }
    i++;
  }
  return true;
}

//helper function to help check duplicates in cage
bool duplicateCageCheck(Cage cage, int** solution){
  int check[N*N];
  for(int i = 0; i < cage.size; i++){
    check[i] = solution[cage.coord[i].x][cage.coord[i].y];
  }
  qsort(check, cage.size, sizeof(int), compare);
  for(int x =1; x<cage.size; x++){
    if(check[x]){
      if(check[x-1] == check[x]){
        //printf("Duplicates in cage %d \n ", check[x]);
        return false;
      }
    }
  }
  return true;
}

int compare(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}

//checks if all cage sizes add upto numberofcells
bool checkProblemValid(Cage* cages, int n, int cageCount){
  bool correctProblem = false;
  int totalCells = 0;

  for(int i = 0; i < cageCount; i++){
    totalCells = totalCells + cages[i].size;
  }
  if(totalCells == (n*n)){
    correctProblem = true;
    //printf("valid problem: %d\n", correctProblem);
    return correctProblem;
  }
  //printf("invalid %d\n", correctProblem);
  return correctProblem;
}

//checks sum of all cages
bool checkCages(Cage* cages, int numberOfCages, int** solution){
  int i = 0;
  bool validCages = false;
  while(i <= numberOfCages){
    int sum = sumCage(&cages[i], solution);
    if(sum == cages[i].sum){
      //printf(" sum: %d\n ", sum);
      //printf(" valid %d\n", validCages);
      validCages = true;
      i++;
    }
    else if(sum < cages[i].sum){
      //printf(" sum: %d\n ", sum);
      //printf(" valid %d\n", validCages);
      validCages = true;
      //printf("Incomplete\n");
      i++;
    }
    else{
      //printf("%s\n", "invalid sum of cages");
      return false;
    }
  }
  //printf("all cages sum up to values: %d\n", validCages);
  return validCages;
}

//sums the cages up
int sumCage(Cage* cage, int** solution){
  int sum = 0;
  for(int i = 0; i < cage->size; i++){
    sum = sum + solution[cage->coord[i].x][cage->coord[i].y];
  }
  return sum;
}

//checks if incomplete adds up all sides and rows
bool checkRowColSums(int** solution){
  int j = 0;
  while(j < N){
    if (!checkRowSum(solution, j) || !checkColSum(solution, j)){
      //printf("InvalidSol sum\n");
      return false;
    }
    //printf("working sum check\n");
    j++;
    return true;
  }
  return false;
}

bool checkRowSum(int** solution, int row){
  int sum;
  for(int j = 0; j < N; j++){
    sum = sum + solution[row][j];
  }
  if(sum == (N*(N+1))/2){
    //printf("valid sum row\n");
    sum =0;
    return true;
  }
  else if(sum < (N*(N+1))/2){
    //printf(" sum: %d\n ", sum);
    //printf(" valid %d\n", validCages);
    return false;
    //printf("Incomplete\n");
  }
  //printf("INvalid sum row\n");
  sum=0;
  return false;
}

bool checkColSum(int** solution, int col){
  int sumCol;
  for(int j = 0; j < N; j++){
    sumCol = sumCol + solution[j][col];
  }
  if(sumCol == (N*(N+1))/2){
    //printf("valid sum col\n");
    sumCol=0;
    return true;
  } else if(sumCol < (N*(N+1))/2){
    //printf(" sum: %d\n ", sum);
    //printf(" valid %d\n", validCages);
    return false;
    //printf("Incomplete\n");
  }
  //printf("INvalid sum col\n");
  sumCol=0;
  return false;
}

//checks duplicates in sudoku grid
bool checkSudokuGrid(int** solution){
  int j = 0;
  while(j < N){
    if (!checkRow(solution, j) || !checkCol(solution, j)){
      //printf("INVALIDSOL\n");
      //printf("%d\n", checkRow(solution, j));
      //printf("%d\n", checkCol(solution, j));
      return false;
    }
    // printf("working sudoku\n");
    j++;
    return true;
  }
  return false;

}

bool checkRow(int** solution, int row){
  int store[N*N];
  for(int i = 0; i < N; i++){
    store[i] = solution[row][i];
  }
  qsort(store, N, sizeof(int), compare);
  for(int x =1; x<N; x++){
    if(store[x]){
      if(store[x-1] == store[x]){
        //printf("Duplicates in row\n");
        return false;
      }
    }
  }
  return true;
}

bool checkCol(int** solution, int col){
  int store[N*N];
  for(int i = 0; i < N; i++){
    store[i]=solution[i][col];
  }
  qsort(store, N, sizeof(int), compare);
  for(int x =1; x<N; x++){
    if(store[x]){
      if(store[x-1] == store[x]){
        // printf("Duplicates in col\n");
        return false;
      }
    }
  }
  return true;
}

//checks if valid boxes have unique numbers
bool validBoxes(int** solution){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if (!checkBoxes(solution, i, j)){
        // printf("not working\n");
        return false;
        break;
      }
    }
  }
  //printf("working\n");
  return true;
}

//what happens if it's zero

//need to check each box
bool checkBoxes(int** solution, int row, int col){
  int check[N*N];
  int root = (int) sqrt(N);
  int rowStart = (row/root) * root;
  int colStart = (col/root) * root;
  int i;
  for(i=0; i<N; i++){
    check[i] = solution[rowStart + (i%root)][colStart + (i/root)];
  }
  qsort(check, N, sizeof(int), compare);
  for(int x =1; x<N; x++){
    if(check[x]){
      if(check[x-1] == check[x]){
        //printf("Duplicates %d\n", check[x]);
        return false;
      }
    }
  }
  return true;
}
