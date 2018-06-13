#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "queens.h"

int count_queens(Cell **table, int size) {
  int queens_count = 0;

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      if (table[i][j].figure == 'Q') queens_count++;

  return queens_count;
}

int check_rows_and_cols(Cell **table, int size) {
  int queens_in_row, queens_in_col;

  for (int i = 0; i < size; i++) {
    queens_in_col = 0;
    queens_in_row = 0;
    for (int j = 0; j < size; j++) {
      if (table[i][j].figure == 'Q') queens_in_row++;
      if (table[j][i].figure == 'Q') queens_in_col++;
    }
    assert(queens_in_row < 2);
    assert(queens_in_col < 2);
  }

  return 0;
}

int check_diags(Cell **table, int size) {
  int queens_on_diag1, queens_on_diag2;

  for (int i = 0; i < size; i++) {
    queens_on_diag1 = 0;
    queens_on_diag2 = 0;
    for (int j = 0 ; j < size - i; j++) {
      if (table[j][i + j].figure == 'Q') queens_on_diag1++;
      if (table[size - j - 1][i + j].figure == 'Q') queens_on_diag2++;
    }
    assert(queens_on_diag1 < 2);
    assert(queens_on_diag2 < 2);
  }

  for (int j = 1; j < size; j++) {
    queens_on_diag1 = 0;
    queens_on_diag2 = 0;
    for (int i = 0 ; i < size - j; i++) {
      if (table[j][i + j].figure == 'Q') queens_on_diag1++;
      if (table[size - j - 1][i + j].figure == 'Q') queens_on_diag2++;
    }
    assert(queens_on_diag1 < 2);
    assert(queens_on_diag2 < 2);
  }

  return 0;
}

int check_board(Cell **table, int size) {
  int queens_on_line = 0;

  assert(count_queens(table, size) == size);
  assert(check_rows_and_cols(table, size) == 0);
  assert(check_diags(table, size) == 0);

  return 0;
}

void test_n_queens(int n) {
  Cell **table;

  printf("Testing %dx%d table\n", n, n);

  table = malloc(n * sizeof(Cell*));
  for (int i = 0; i < n; i++)
    table[i] = malloc(n * sizeof(Cell));

  table[0][3].figure = 'Q';

  place_queens(table, n);

  check_board(table, n);

  printf("%dx%d table is OK\n", n ,n);

  for (int i = 0; i < n; i++)
    free(table[i]);
  free(table);
}

int main() {
  printf("N-Queens solution test\n");

  test_n_queens(8);
  test_n_queens(9);

  return 0;
}