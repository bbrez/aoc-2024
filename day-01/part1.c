#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void readInput(FILE *f, int *len, int **vec1, int **vec2) {
  int vecSize = 100;
  *len = 0;
  *vec1 = malloc(sizeof(int) * vecSize);
  *vec2 = malloc(sizeof(int) * vecSize);

  bool shouldContinueReading = true;
  while (shouldContinueReading) {
    if (*len >= vecSize) {
      vecSize += 100;
      *vec1 = realloc(*vec1, sizeof(int) * vecSize);
      *vec2 = realloc(*vec2, sizeof(int) * vecSize);
    }

    if (fscanf(f, "%d   %d", &(*vec1)[*len], &(*vec2)[*len]) == 2) {
      (*len)++;
    } else {
      shouldContinueReading = false;
    }
  }
}

bool isSorted(int *vec, int len) {
  for (int i = 0; i < len - 1; i++) {
    if (vec[i] > vec[i + 1])
      return false;
  }

  return true;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void sort(int *vec, int len) {
  for (int i = 0; i < len - 1; ++i) {
    for (int j = i + 1; j < len; ++j) {
      if (vec[i] > vec[j]) {
        swap(&vec[i], &vec[j]);
      }
    }
  }
}

void printVec(int *vec, int len) {
  for (int i = 0; i < len; ++i) {
    printf("%d", vec[i]);
    if (i < len - 1)
      printf(" ");
  }
}

int absDiff(int a, int b) { return abs(a - b); }

void absDiffVec(int *vec1, int *vec2, int len, int *ans) {
  for (int i = 0; i < len; ++i) {
    ans[i] = absDiff(vec1[i], vec2[i]);
  }
}

int sumVec(int *vec, int len) {
  int sum = 0;
  for (int i = 0; i < len; ++i) {
    sum += vec[i];
  }
  return sum;
}

int sumAbsDiff(int *vec1, int *vec2, int len) {
  int* absDiffAns = malloc(sizeof(int) * len);
  absDiffVec(vec1, vec2, len, absDiffAns);
  return sumVec(absDiffAns, len);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Wrong argument count!\n");
    printf("Usage: %s <input>", argv[0]);
    return -1;
  }

  FILE *f = fopen(argv[1], "r");
  int *vec1, *vec2;
  int len;

  readInput(f, &len, &vec1, &vec2);
  sort(vec1, len);
  sort(vec2, len);
  printf("%d\n", sumAbsDiff(vec1, vec2, len));
  return 0;
}
