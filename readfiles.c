#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "checkerHeader.h"

Cage* loadFile(char* fileName){
  int coordCounter =0;
  //int count = 0;
  FILE* f = fopen(fileName, "r");
  int countRead = fscanf( f, "%d", &N);
  //printf("n was %d", N);
  Cage* cages = malloc(sizeof(Cage) * (N*N));

  if( countRead != 1 ){
    printf("%s", "error input right problem size");
  }
  int checkArray[N][N];

  while(1){
    int sum, size;
    int countRead = fscanf(f, "%d %d",&sum, &size);
    if(countRead != 2){
      break;
    }
    cages[cageCount].sum = sum;
    cages[cageCount].size = size;
    for(int i =0; i < size; i++){
      int x,y;
      countRead = fscanf(f, "%d,%d", &x, &y);
      assert(countRead == 2);
      if(checkArray[x][y] == -1){
        printf("INVALIDPROBLEM\n");
        exit(0);
      }
      else{
        checkArray[x][y] = -1;
        coordCounter++;
      }
      cages[cageCount].coord[i].x = x;
      cages[cageCount].coord[i].y = y;
    }
    cageCount++;
  }
  if(coordCounter == N*N){
    printf("Whole grid is filled\n");
  }
  else{
    printf("Error in input file\n");
  }
  fclose(f);
  return cages;
}

int** loadSolution(char* solutionFile){
  FILE* f = fopen(solutionFile, "r");
  int** solArray = malloc(sizeof(int*) * N);
  if (solArray){
    for (int i = 0; i < N; i++){
      solArray[i] = malloc(sizeof(int) * N);
    }
  }
  int i = 0;
  int j = 0;
  while(1){
    int element;
    int countRead = fscanf(f, "%d", &element);
    if(countRead != 1){
      break;
    }
    solArray[i][j] = element;
    j++;
    if(j == N){
      i++;
      j=0;
    }
  }
  for(int x =0; x< N; x++){
    for(int y =0; y<N;y++){
      printf(" %d", solArray[x][y]);
    }
    printf("\n");
  }
  fclose(f);
  return solArray;
}
