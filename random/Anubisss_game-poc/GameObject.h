#pragma once

#include <SDL2/SDL.h>

class GameObject {
 public:
  GameObject(SDL_Renderer *renderer) : renderer(renderer) {}

  virtual void Update(Uint32 const diff) = 0;
  virtual void Render() = 0;

 protected:
  SDL_Renderer *renderer = nullptr;
};
