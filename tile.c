//tile.c

#include "tile.h"



Tile t_initialize( char Color) {
  Tile tile_s;
  tile_s.color = Color;
  tile_s.set = 0;
  
  return tile_s;
}
