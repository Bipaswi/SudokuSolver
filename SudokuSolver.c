#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

typedef struct Coord {
  int x, y;
} Coord;

typedef struct Cage {
  int sum;
  int size;
  struct Coord coord[81];
} Cage;

int cageCount;
int N;
int coordCounter =0;

Cage* loadFile(char* fileName);
int solver(int puzzle[N][N], Cage* cages, int row, int col);
bool validRow(int row, int attempt, int puzzle[N][N]);
bool validCol(int col, int attempt, int puzzle[N][N]);
bool cageValid(int row, int col, int attempt, int puzzle[N][N], Cage* cages);
bool boxValid(int row, int col, int attempt, int puzzle[N][N]);
Cage* getCage(int row, int col, Cage* cages);
int sumCage(Cage* cage, int puzzle[N][N]);

int main(int argc, char** argv) {
  Cage* cages = loadFile(argv[1]);
  int puzzle[N][N];

  for(int i = 0; i < N; ++i)
  for(int j = 0; j < N; ++j)
  puzzle[i][j] = 0;

  //print puzzle
  solver(puzzle, cages, 0, 0);
  for(int x =0; x< N; x++){
    for(int y =0; y<N;y++){
      printf(" %d", puzzle[x][y]);
    }
    printf("\n");
  }
}

Cage* loadFile(char* fileName){

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
      if(checkArray[x][y] == -1){
        printf("INVALIDPROBLEM\n");
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
    printf("INCOMPLETE\n");
  }
  fclose(f);
  return cages;
}

int solver(int puzzle[N][N], Cage* cages, int row, int col){
  //printf("%d,%d\n",row,col);
  if (N == row) {
    return 1;
  }
  for (int nextNum = 1; nextNum<N+1; nextNum++) {
    if(validRow(row, nextNum, puzzle)
    && validCol(col, nextNum, puzzle)
    && cageValid(row, col, nextNum, puzzle, cages)
    && boxValid(row, col, nextNum, puzzle)) {
      puzzle[row][col] = nextNum;
      // printf("******************\n");
      // for(int x =0; x< N; x++){
      //   for(int y =0; y<N;y++){
      //       printf(" %d", puzzle[x][y]);
      //      }
      //          printf("\n");
      //       }
      if (col == N-1) {
        if (solver(puzzle, cages, row+1, 0))
        return 1;
      } else {
        if (solver(puzzle, cages, row, col+1))
        return 1;
      }
      puzzle[row][col] = 0;
    }
  }
  return 0;
}

bool validRow(int row, int attempt, int puzzle[N][N]){
  for (int i=0; i<N; i++) {
    if (puzzle[row][i] == attempt){
      //printf(" puzzle[][]: %d attempt %d row %d col %d\n", puzzle[col][i], attempt, col, i);
      return false;
    }
  }
  return true;
}

bool validCol(int col, int attempt, int puzzle[N][N]){
  for (int i=0; i<N; i++) {
    if (puzzle[i][col] == attempt){
      //printf(" puzzle[][]: %d attempt %d col %d row %d\n", puzzle[i][row], attempt, i, row);
      return false;
    }
  }
  return true;
}

bool cageValid(int row, int col, int attempt, int puzzle[N][N], Cage* cages){
  int elementCounter = 1;
  Cage* temp = getCage(row, col, cages);
  //access right cage
  //need to check if adds to sum
  int i =0;
  for(; i < temp->size; i++){

    if(puzzle[temp->coord[i].x][temp->coord[i].y] == attempt){
      return false;
    }
    if(puzzle[temp->coord[i].x][temp->coord[i].y] != 0){
      elementCounter++;
    }
  }
  int sum = sumCage(temp, puzzle) + attempt;
  // printf("(%d, %d) sum %d attempt %d\n", row, col, sum, attempt);
  // printf("cage sum: %d\n", temp->sum);
  // printf("elementCounter %d\n", elementCounter);

  if(sum == temp->sum && elementCounter != temp->size){
    //printf("sum is: %d reached sum too early\n", sum);
    return false;
  }
  if(sum > temp->sum){
    //printf("sum is: %d sum is too big:\n", sum);
    return false;
  }
  //printf("returning true");
  return true;
}

Cage* getCage(int row, int col, Cage* cages){
  for(int i = 0; i < cageCount; i++){
    for(int j =0; j < coordCounter; j++){
      if(cages[i].coord[j].x == row && cages[i].coord[j].y == col){
        //printf("( %d, %d)", row, col);
        //printf("( cage size: %d, cage Sum %d)", cages[i].size, cages[i].sum);
        return &cages[i];
      }
    }
  }
  return NULL;
}

int sumCage(Cage* cage, int puzzle[N][N]){
  int sum = 0;
  for(int i = 0; i < cage->size; i++){
    sum = sum + puzzle[cage->coord[i].x][cage->coord[i].y];
  }
  return sum;
}

bool boxValid(int row, int col, int attempt, int puzzle[N][N]){
  int root = (int) sqrt(N);
  int rowStart = (row/root) * root;
  int colStart = (col/root) * root;

  for(int i=0; i<N; i++){
    if (attempt == puzzle[rowStart + (i%root)][colStart + (i/root)]){
      return false;
    }
  }
  return true;
}
