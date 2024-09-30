#include "Map.h"

#include <iostream>
#include <cmath>

#include <SDL2/SDL_image.h>

Map::Map(SDL_Renderer *renderer, int width, int height) : renderer(renderer), sizeWidth(width), sizeHeight(height) {
  LoadBackground();
  LoadTiles();
}

void Map::LoadBackground() {
  SDL_Surface *surface = IMG_Load(BACKGROUND_PATH.c_str());
  if (!surface) {
    std::cerr << "Can't load the texture: \"" << BACKGROUND_PATH << "\"" << std::endl;
    std::cerr << IMG_GetError() << std::endl;
    return;
  }
  backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
}

void Map::LoadTiles() {
  SDL_Surface *surface = IMG_Load(TILE_PATH.c_str());
  if (!surface) {
    std::cerr << "Can't load the texture: \"" << TILE_PATH << "\"" << std::endl;
    std::cerr << IMG_GetError() << std::endl;
    return;
  }
  SDL_Texture *tileTexture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  int numberOfTiles = static_cast<int>(std::ceil(static_cast<float>(sizeWidth) / static_cast<float>(Tile::SIZE)));
  for (int i = 0; i < numberOfTiles; ++i)
    tiles.push_back(Tile(renderer, tileTexture, i * Tile::SIZE, sizeHeight - Tile::SIZE));
}

void Map::Render() const {
  RenderBackground();
  RenderTiles();
}

void Map::RenderBackground() const {
  SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
}

void Map::RenderTiles() const {
  for (auto const& tile : tiles)
    tile.Render();
}
