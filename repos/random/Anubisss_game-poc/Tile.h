#pragma once

#include <SDL2/SDL.h>

class Tile {
 public:
  static int const SIZE = 96;

  Tile(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y) : renderer(renderer), texture(texture) {
    pos.x = x;
    pos.y = y;
  }

  void Render() const {
    SDL_RenderCopy(renderer, texture, nullptr, &pos);
  }

 private:
  SDL_Renderer *renderer = nullptr;
  SDL_Texture *texture = nullptr;

  SDL_Rect pos = {0, 0, SIZE, SIZE};
};
