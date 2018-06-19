#include "queens.h"
#include <stdio.h>
#include <stdlib.h>

// display chess board
void print_table(Cell **table, int size) {
  printf("\n");
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      printf("%c\t", table[i][j].figure);
    }
    printf("\n\n");
  }
}

// init chess board
void init_board(Cell **table, int size)
{
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      if(table[i][j].figure != 'Q') table[i][j].figure = 'E';
    }
  }
}

// check if all queens are placed
int is_all_queens_placed(Cell **table, int size) {
  int count = 0;
  for(int rows = 0; rows < size; rows++) {
    for(int cols = 0; cols < size; cols++) {
      if(table[rows][cols].figure == 'Q') {
        count++;
        break;
      }
    }
  }
  if(count == size) return 1;
  return 0;
}

// checkout validation of move
int is_valid_move(Cell **table,int size,int rows, int cols) {
  int rows_count, cols_count;
  // check for queen in row
  rows_count = rows;
  for (cols_count = 0; cols_count < size; cols_count++) {
    if(table[rows_count][cols_count].figure == 'Q') {
      return 0;
    }
  }
  //check for queen in col
  cols_count = cols;
  for (rows_count = 0; rows_count < size; rows_count++) {
    if(table[rows_count][cols_count].figure == 'Q') {
      return 0;
    }
  }

  rows_count = rows - 1; cols_count = cols - 1;
  while( rows_count >= 0 && cols_count >= 0) {
    if(table[rows_count][cols_count].figure == 'Q') return 0;
    else { rows_count--; cols_count--; }
  }

  rows_count = rows - 1; cols_count = cols + 1;
  while( rows_count >= 0 && cols_count < size) {
    if(table[rows_count][cols_count].figure == 'Q') return 0;
    else { rows_count--; cols_count++; }
  }

  rows_count = rows + 1; cols_count = cols - 1;
  while( rows_count < size && cols_count >= 0) {
    if(table[rows_count][cols_count].figure == 'Q') return 0;
    else { rows_count++; cols_count--; }
  }

  rows_count = rows + 1; cols_count = cols + 1;
  while( rows_count < size && cols_count < size) {
    if(table[rows_count][cols_count].figure == 'Q') return 0;
    else { rows_count++; cols_count++; }
  }
  return 1;
}

// place new queen on the board
void place_queen(Cell **table, int rows, int cols) {
  table[rows][cols].figure = 'Q';
}

// backtrack function
int backtrack(Cell **table, int size, int rows) {
  int cols_count;
  for( cols_count = 0; cols_count < size; cols_count++) {
    if(table[rows - 1][cols_count].figure == 'Q') {
      table[rows - 1][cols_count].figure = 'E';
      break;
    }
  }
  return cols_count + 1;
}

// place queens on the table
void place_queens(Cell **table, int size)
{
  init_board(table, size);
  int rows = 1, cols = 1;
  while(!is_all_queens_placed(table, size)) {
    if(is_valid_move(table, size, rows, cols)) {
      place_queen(table, rows, cols);
      rows++;
      cols = 0;
    }
    else {
      cols++;
      while(cols == size) {
        cols = backtrack(table, size, rows);
        rows--;
      }
    }
  }
  print_table(table, size);
}
