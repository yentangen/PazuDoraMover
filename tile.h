//tile.h

#ifndef TILE_H
#define TILE_H

typedef struct Tile_n {
  char color;
  int set;
  //struct Tile_n *top,*bottom,*left,*right;
} Tile;

Tile t_initialize( char Color);

#endif
