//Grid.h

#ifndef GRID_H
#define GRID_H

#define MAX_PATH 14 //The max allowed moves
#define OFFSET 6    //How much to push optimal solution for even better one
#define MAX_X 6   //5 = right-most tiles
#define MAX_Y 5   //4 = bottom-most tiles
#define NUM_DIRECTIONS 4  //number of possible directions (NO DIAGONALS)
#define THRESHOLD 9 //set tiles needed to be a viable solution
#include "tile.h"
//REMEMBER: ACCESS INDIVIDUAL TILES BY Grid[Y][X]!!!

char *spath;
int path_len,startx,starty,num_sets;
struct grid_n rgrid;

struct grid_n {
  Tile Tiles[5][6];
} grid;
void g_find_path(int tx,int ty,
                 int sx,int sy,
                 char *path,char prev,char prev2,
                 int nox,int noy);
int g_find_sets(struct grid_n *Grid);
void g_initialize();
void g_reset();
void swap( struct grid_n *Grid,int X, int Y, char dir);

void run_naive();
int n_run(struct grid_n *Grid, 
          int x, int y, 
          int sx,int sy,
          char *path, int moves, 
          char prev);
int get_set_amt(struct grid_n Grid);
void n_printoutput();
#endif
