//grid.c

#include "tile.h"
#include "grid.h"

int g_find_sets(struct grid_n *Grid) {
  int x,y,nsets=0;
  
  //reset the field... need to find new sets, after all!
  for (y=0;y<MAX_Y;y++) 
    for (x=0;x<MAX_X;x++) 
      if (Grid->Tiles[y][x].set != 0)
        Grid->Tiles[y][x].set = 0;

  
/* 
    For every. single. tile. in the grid, check all 4 directions at a maximum of
    length two to see if there is a set of 3. Do not ignore tiles that already 
    are part of a set as it has possibility of producing a set of 5. This
    approach, although more time/energy consuming, will help produce special
    sets of any length greater than 3.
*/
  //Remember... grid.Tiles[y][x]
  for (y=0;y<MAX_Y;y++) {
    for (x=0;x<MAX_X;x++) {
      //bounds checking is incorporated... 
      if (y >= 2 )            //For any tiles NOT in the top two rows
        if (Grid->Tiles[y][x].color == Grid->Tiles[y-1][x].color && 
            Grid->Tiles[y][x].color == Grid->Tiles[y-2][x].color) {
          Grid->Tiles[y][x].set = 1;
          Grid->Tiles[y-1][x].set = 1;
          Grid->Tiles[y-2][x].set = 1;
        }
        
      if (y <= 2 )            //For any tiles NOT in the bottom two rows
        if (Grid->Tiles[y][x].color == Grid->Tiles[y+1][x].color && 
            Grid->Tiles[y][x].color == Grid->Tiles[y+2][x].color) {
          Grid->Tiles[y][x].set = 1;
          Grid->Tiles[y+1][x].set = 1;
          Grid->Tiles[y+2][x].set = 1;
        }
      
      if (x >= 2)             //For any tiles NOT in the left two columns
        if (Grid->Tiles[y][x].color == Grid->Tiles[y][x-1].color && 
            Grid->Tiles[y][x].color == Grid->Tiles[y][x-2].color) {
          Grid->Tiles[y][x].set = 1;
          Grid->Tiles[y][x-1].set = 1;
          Grid->Tiles[y][x-2].set = 1;
        }

      if (x <= 3)             //For any tiles NOT in the right two columns
        if (Grid->Tiles[y][x].color == Grid->Tiles[y][x+1].color && 
            Grid->Tiles[y][x].color == Grid->Tiles[y][x+2].color) {
          Grid->Tiles[y][x].set = 1;
          Grid->Tiles[y][x+1].set = 1;
          Grid->Tiles[y][x+2].set = 1;
        }
      //nsets for return purposes
      if (Grid->Tiles[y][x].set == 1) nsets++;
    } 
  }
  
  return nsets;
}

void g_initialize() {
  int x,y;
  path_len=999;
  num_sets=0;
  /*
  for (y=0;y<MAX_Y;y++) {
    for (x=0;x<MAX_X;x++) {
      grid.Tiles[y][x] = t_initialize('Z');
      
      //bounds initialization
      if (y == 0)             //topmost tiles. tile->top = NULL
        grid.Tiles[y][x].top = 0;
      else
        grid.Tiles[y][x].top = &grid.Tiles[y-1][x];
      if (y == MAX_Y-1)         //bottommost tiles. tile->bottom = NULL
        grid.Tiles[y][x].bottom = 0;
      else
        grid.Tiles[y][x].bottom = &grid.Tiles[y+1][x];
      if (x == 0)             //leftmost tiles. tile->left = NULL
        grid.Tiles[y][x].left = 0;
      else  
        grid.Tiles[y][x].left = &grid.Tiles[y][x-1];
      if (x == MAX_X-1)         //rightmost tiles. tile->right = NULL
        grid.Tiles[y][x].right = 0;
      else
        grid.Tiles[y][x].right = &grid.Tiles[y][x+1];
    }
  }
  */
  spath = (char *)malloc(MAX_PATH+OFFSET+2 * sizeof(char));
  
}

void g_reset() {
  int x,y;
  strcpy(spath,"");
  path_len = 999;
  num_sets=0;
  
  //This double for loop may be unnecessary, but more of for double assurance.
  //Doesn't run often anyway..
  for (y=0;y<MAX_Y;y++) 
    for (x=0;x<MAX_X;x++)
      rgrid.Tiles[y][x].set = 0;
  //colors can be ignored since it will all be overwritten anyway
}

void swap( struct grid_n *Grid, int X, int Y, char dir) {
  char temp = Grid->Tiles[Y][X].color;  //temporary place to store color

  switch (dir) {
    //switch with above tile
    case 'u':
      if (Grid->Tiles[Y][X].color == Grid->Tiles[Y-1][X].color) return;
      Grid->Tiles[Y][X].color = Grid->Tiles[Y-1][X].color;
      Grid->Tiles[Y-1][X].color = temp;
      break;
    case 'd':
      if (Grid->Tiles[Y][X].color == Grid->Tiles[Y+1][X].color) return;
      Grid->Tiles[Y][X].color = Grid->Tiles[Y+1][X].color;
      Grid->Tiles[Y+1][X].color = temp;
      break;
    case 'l':
      if (Grid->Tiles[Y][X].color == Grid->Tiles[Y][X-1].color) return;
      Grid->Tiles[Y][X].color = Grid->Tiles[Y][X-1].color;
      Grid->Tiles[Y][X-1].color = temp;
      break;
    case 'r':
      if (Grid->Tiles[Y][X].color == Grid->Tiles[Y][X+1].color) return;
      Grid->Tiles[Y][X].color = Grid->Tiles[Y][X+1].color;
      Grid->Tiles[Y][X+1].color = temp;
      break;
    default:
      break;
  }
  
}

//brute force method...!! RAAAAAWWWR
void run_naive( ) {
  struct grid_n tempgrid = grid;
  int x,y;
  
  printf("Please Wait.");
  for (y=0;y<MAX_Y;y++) {
    for (x=0;x<MAX_X;x++) {
      n_run(&grid,x,y,x,y,"",0,' ');
      grid = tempgrid;
    }
    printf(".");
  }
  printf("\n");
}


int n_run(struct grid_n *Grid, 
          int x, int y, 
          int sx, int sy,
          char *path, int moves, 
          char prev) {
  struct grid_n tempgrid = *Grid;
  char* result = (char *)malloc((strlen(path)+2) * sizeof(char));
  strcpy(result,path);  //to start
  int set_amt= g_find_sets(Grid);
  
  //determine how many tiles are "set" (part of a set)
  //"THRESHOLD" can be modified to expand/reduce possible combinations
  if ( ((set_amt  > num_sets) && (set_amt >= THRESHOLD ))||
     ( ((set_amt == num_sets) && (strlen(path) < path_len)) ) ){
    //startx and starty for reporting purposes.
    startx = sx;
    starty = sy;
    //copy path down
    strcpy(spath,path);
    //update amount of set tiles
    num_sets = set_amt;
    path_len = strlen(spath);
    rgrid = *Grid;
    
    if (path_len < MAX_PATH+OFFSET)
      //see how far this solution will go to be optimal
      n_run(Grid,x,y,sx,sy,path,0,prev);
  }
  
  //Max allowed moves reached.. no more moves allowed past this point
  if ((moves >= MAX_PATH) || (strlen(path) > MAX_PATH+OFFSET)) return 1;
  
  //Move orb
  //going up
  if ( (y != 0) && (prev != 'd') ) {
    strcat(result,"u");
    swap(Grid,x,y,'u');
    n_run(Grid,x,y-1,sx,sy,result,moves+1,'u');
  }
  strcpy(result,path);
  *Grid = tempgrid;
  //going left
  if ( (x != 0) && (prev != 'r') ) {
    strcat(result,"l");
    swap(Grid,x,y,'l');
    n_run(Grid,x-1,y,sx,sy,result,moves+1,'l');
  }
  strcpy(result,path);
  *Grid = tempgrid;
  //going down
  if ( (y != MAX_Y-1) && (prev != 'u') ) {
    strcat(result,"d");
    swap(Grid,x,y,'d');
    n_run(Grid,x,y+1,sx,sy,result,moves+1,'d');
  }
  strcpy(result,path);
  *Grid = tempgrid;
  //going right
  if ( (x != MAX_X-1) && (prev != 'l') ) {
    strcat(result,"r");
    swap(Grid,x,y,'r');
    n_run(Grid,x+1,y,sx,sy,result,moves+1,'r');
  }
  
  free(result);
  return 0;
}

int get_set_amt(struct grid_n Grid) {
  int nsets=0;
  int x,y;
  
  for (y=0;y<MAX_Y;y++) 
    for (x=0;x<MAX_X;x++) 
      if (Grid.Tiles[y][x].set) nsets++;

  return nsets;
}

void n_printoutput() {
  int x,y;
  printf("Result grid is:\n\n");
  
  for (y=0;y<MAX_Y;y++) {
    for (x=0;x<MAX_X;x++)
      printf("%c",rgrid.Tiles[y][x].color);
    printf("\n");
  }
  
  printf("A path generated:\n\nstart coords (y,x): (%d,%d)\n",starty,startx);
  printf("Path: %s\twith path length %d\n",spath,path_len);
  printf("Amount of orbs eliminated: %d\n",num_sets);
}
