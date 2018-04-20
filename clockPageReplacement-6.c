/* clockPageReplacement.c - a program implements the enhanced clock page
*  replacement algorithm. The clock will be implemented as a 4-element
*  circular array.
*  @author Junjie Wu
*  @sid  47503174
*  @server genuse32
*  @compiler gcc
*  @option -o
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CLOCK_SIZE 4

/* define struct page_table to store the clock output results. */
struct page_table {
  int tb[CLOCK_SIZE][4];
  int nextFrame;
} pt;

/* step 2: check the page, if it is in the clock, update the appropriate flags,
*  and return 0, otherwise return 1.
*/
int page_check(int page, char operation) {
  bool flag = false;
  int i = 0;
  for(; i < CLOCK_SIZE; i++) {
    if(pt.tb[i][1] == page) {
      flag = true;
      pt.tb[i][2] = 1;
      if(operation == 'w') {
        pt.tb[i][3] =1;
      }
      break;
    }
  }
  if(flag == true) {
    return 0;
  }
  else return 1;
}

/* if the page in the record is not in the clock,
*  replace one page in the clock throuth step 3 to step 5.
*/
void page_replacement(int page, char operation) {
  bool flag = false;
  /* repeat step 3 and step 4 using while loops, then one frame will be
  *  found for page replacement.
  */
  while(flag != true) {
    /* step 3: from the current postion of the nextFrame pointer, find the
    *  first frame encounted with (use = 0; modify = 0) and replace it.
    */
    int clock = pt.nextFrame;
    int i = 0;
    for(; i < CLOCK_SIZE; i++) {
      if(pt.tb[clock][2] == 0 && pt.tb[clock][3] == 0) {
        flag = true;
        pt.tb[clock][1] = page;
        pt.tb[clock][2] = 1;
        if(operation == 'w') {
          pt.tb[clock][3] = 1;
        }
        pt.nextFrame = (clock + 1) % CLOCK_SIZE;
        break;
      }
      clock = (clock + 1) % CLOCK_SIZE;
    }

    /* step 4: if step 3 fails, then  scan the clock again, find the first
    *  frame with (use = 0; modify = 1) and replace it. During the scan,
    *  set the use bit to 0 for each frame that is bypassed.
    */
    if(flag == false) {
      clock = pt.nextFrame;
      i = 0;
      for(; i < CLOCK_SIZE; i++) {
        if(pt.tb[clock][2] == 0 && pt.tb[clock][3] == 1) {
          flag = true;
          pt.tb[clock][1] = page;
          pt.tb[clock][2] = 1;
          if(operation == 'r') {
            pt.tb[clock][3] = 0;
          }
          pt.nextFrame = (clock + 1) % CLOCK_SIZE;
          break;
        }
        pt.tb[clock][2] = 0;
        clock = (clock + 1) % CLOCK_SIZE;
      }
    }

    /* step 5: if step 4 fails, set nextFrame pointer to original 0 position,
    *  and also set the use bit of all frames to 0.
    */
    if(flag == false) {
      pt.nextFrame = 0;
      i = 0;
      for(; i < CLOCK_SIZE; i++) {
        pt.tb[i][2] = 0;
      }
    }
  }
}

void writeClockToFile(FILE* filePtr, int page, char operation) {
  int i = 0;
  fprintf(filePtr, "FRAME     PAGE     USE     MODIFY\n");
  int j = page_check(page, operation);
  if(j!=0) {
    page_replacement(page, operation);
  }
  for(; i < CLOCK_SIZE; i++) {
    if(pt.nextFrame == i) {
      fprintf(filePtr,"%3d      %3d      %3d      %3d  <- next frame\n",
             pt.tb[i][0], pt.tb[i][1], pt.tb[i][2], pt.tb[i][3]);
    }
    else {
    fprintf(filePtr,"%3d      %3d      %3d      %3d\n",
           pt.tb[i][0], pt.tb[i][1], pt.tb[i][2], pt.tb[i][3]);
    }
  }
}

int main() {
  int i = 0;
  for(;i < CLOCK_SIZE; i++) {
    pt.tb[i][0] = i;
    pt.tb[i][1] = -1;
    pt.tb[i][2] = 0;
    pt.tb[i][3] = 0;
  }
  pt.nextFrame = 0;

  char inFileName[] = "testdata.txt";
  FILE *inFilePtr = fopen(inFileName, "r");
  if(inFilePtr == NULL) {
    printf("File %s could not be a opened.\n", inFileName);
    exit(1);
  }

  char outFileName[] = "result.txt";
  FILE *outFilePtr = fopen(outFileName,"w");
  if(outFilePtr == NULL) {
    printf("File %s could not be opened.\n", outFileName);
    exit(1);
  }

  int page;
  char operation;
  fscanf(inFilePtr, "%d%c", &page, &operation);
  while(!feof(inFilePtr)) {
    fprintf(outFilePtr,"Page referenced: %d %c\n", page, operation);
    writeClockToFile(outFilePtr, page, operation);
    fprintf(outFilePtr,"\n");
    fscanf(inFilePtr, "%d%c", &page, &operation);
  }

  fclose(inFilePtr);
  fclose(outFilePtr);
  return 0;
}
