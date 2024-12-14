#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int signal(int x) {
  if (x < 0)
    return -1;
  if (x > 0)
    return 1;
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Wrong argument count!\n");
    printf("Usage: %s <input>", argv[0]);
    return -1;
  }

  FILE *f = fopen(argv[1], "r");
  char buffer[255];
  int stableCount = 0;
  while (!feof(f)) {
    if(fscanf(f, "%[^\n]%*c", buffer) != 1) break;
    char *tok = strtok(buffer, " ");
    printf("%s ", tok);

    int num = atoi(tok);
    int direction = 0;
    while (tok) {
      tok = strtok(NULL, " ");
      if (!tok) {
        printf("safe");
        ++stableCount;
        break;
      }
      printf("%s ", tok);
      int prev = num;
      num = atoi(tok);

      int difference = prev - num;
      int diffDirection = signal(difference);
      int variation = abs(difference);
      if (variation < 1 || variation > 3) {
        printf("unsafe (variation %d)", variation);
        break;
      }
      if (direction == 0)
        direction = diffDirection;
      if (diffDirection != direction) {
        printf("unsafe (direction %d != %d)", direction, diffDirection);
        break;
      }
    }
    printf("\n");
  }

  printf("%d\n", stableCount);
}
