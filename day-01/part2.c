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

int max(int *vec, int len) {
  int current = vec[0];
  for (int i = 0; i < len; ++i) {
    if (vec[i] > current)
      current = vec[i];
  }

  return current;
}

int countOcurrences(int target, int *vec, int len) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    if (vec[i] == target)
      count++;
  }

  return count;
}

int hasElement(int target, int *vec, int len) {
  for (int i = 0; i < len; i++) {
    if (vec[i] == target)
      return true;
  }

  return false;
}

void distinctElements(int *vec, int len, int **out, int *outLen) {
  *out = malloc(sizeof(int) * len);
  *outLen = 0;
  for (int i = 0; i < len; ++i) {
    if (!hasElement(vec[i], *out, *outLen))
      (*out)[(*outLen)++] = vec[i];
  }
  *out = realloc(*out, sizeof(int) * *outLen);
}

void countOcurrencesVec(int *targets, int targetsLen, int *vec, int vecLen,
                        int **out, int *outLen) {
  *outLen = max(targets, targetsLen);
  *out = malloc(sizeof(int) * *outLen);
  for (int i = 0; i < targetsLen; i++) {
    (*out)[targets[i]] = countOcurrences(targets[i], vec, vecLen);
  }
}

int similarityScore(int *vec1, int *vec2, int len) {
  int *dist;
  int distLen;

  distinctElements(vec1, len, &dist, &distLen);

  int *occurrencesVec;
  int occurrencesLen;
  countOcurrencesVec(dist, distLen, vec2, len, &occurrencesVec,
                     &occurrencesLen);
  free(dist);

  int sum = 0;
  for (int i = 0; i < len; i++) {
    sum += occurrencesVec[vec1[i]] * vec1[i];
  }

  return sum;
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
  fclose(f);

  int value = similarityScore(vec1, vec2, len);
  printf("%d\n", value);

  return 0;
}
