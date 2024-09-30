#pragma once

#include <string>
#include <list>

#include <SDL2/SDL.h>

#include "Tile.h"

class Map {
 public:
  Map(SDL_Renderer *renderer, int width, int height);

  void Render() const;

 private:
  typedef std::list<Tile> TileList;

  void LoadBackground();
  void LoadTiles();

  void RenderBackground() const;
  void RenderTiles() const;

  std::string const BACKGROUND_PATH = "assets/sky.png";
  std::string const TILE_PATH = "assets/tiles/GrassJoinHillRight2&Left2.png";

  SDL_Renderer *renderer = nullptr;

  SDL_Texture *backgroundTexture = nullptr;

  int sizeWidth = 0;
  int sizeHeight = 0;

  TileList tiles;
};
