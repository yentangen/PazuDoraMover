/*  Puzzles and Dragons Move Optimizer

    Details to follow...
    
*/

#include <stdio.h>
#include "grid.h"
#include <time.h>
#include <windows.h>

char COLORS[6] = {'r','g','b','l','d','h'};
void prompt() {
  printf("Please enter a 6x5 grid of colors, pressing enter after each row.\n");
  printf("Program will recognize when the grid has been completed, and will\n");
  printf("let you know if there is an error (invalid color input, etc).\n");
  printf("Extra inputs after the first 6 letters will be ignored..\n\n");
  printf("Valid colors:\nRed (fire)= r\nGreen (wood)= g\nBlue (water)= b\n");
  printf("Yellow (light)= l\nDark (dark)= d\nHeal (rcv) = h\n\n");
}


//"rgbldh\ngbldhr\nrgbldh\ngbldhr\nrgbldh\n"
int main(int argc, char *argv[]) {
  time_t start;     //timekeeping and performance evaluation purposes
  int found = 0;
  char again=' '; //again is also used to gobble extra input
  char row[MAX_X+1];  //+1 for null terminate
  int x,y,valid=1;
  g_initialize();

  while (again != 'q') {
    //sanitize grid (wipe set counts clean)
    g_reset();
    //prompt and ask user input
    prompt();
    
    for (y=0;y<MAX_Y;y++) {
      fgets(row,7,stdin);
      //gobble up rest of row if exceed 6
      again = getchar();  
      while (again != '\n') again = getchar();
      //check for valid colors
      for (x=0;x<MAX_X;x++)
        if (row[x] != COLORS[0] && row[x] != COLORS[1] && row[x] != COLORS[2] && 
            row[x] != COLORS[3] && row[x] != COLORS[4] && row[x] != COLORS[5] ) {
              printf("Invalid input detected. Please re-enter row:\n");
              valid = 0;
              break;
            }
      if (!valid) {
        valid = 1;
        y--;
        continue;
      }
      //input into grid
      for (x=0;x<MAX_X;x++)
        grid.Tiles[y][x].color = row[x];
    }
    
    //Confirmation before proceeding. Doubles as check whether inputted into
    //the grid correctly and can regurgitate
    printf("\nYou have entered: \n");
    for (y=0;y<MAX_Y;y++) {
      for (x=0;x<MAX_X;x++)
        printf("%c",grid.Tiles[y][x].color);
      printf("\n");
    }
    printf("If correct, please press 'y'. Otherwise, press any other key:\n");
    again = getch();
    if (again != 'y')
      continue;
    
    //parsing moment of truth starts here...
    start = clock();
    run_naive();
    n_printoutput();
    printf("Running time: %d seconds...\n",(clock()-start)/CLOCKS_PER_SEC);
    
    //one more??
    printf("Another? (press 'q' to exit): ");
    again = getch();
    printf("\n");
  }
  
  free(spath);
  return 0;
}
