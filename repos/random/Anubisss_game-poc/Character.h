#pragma once

#include <map>
#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "GameObject.h"

class Character : public GameObject {
 public:
  Character(SDL_Renderer *renderer, std::string const textureRootPath);

  void Update(Uint32 const diff) override;
  void Render() override;

  void HandleEvents(SDL_Event const* event);

 private:
  enum TextureTypes {
    IDLE,
    RUN,
  };

  typedef std::map<TextureTypes, std::vector<SDL_Texture*> > TextureContainer;

  struct Size {
    int Width;
    int Height;
  };

  struct Position {
    double X;
    double Y;
  };

  enum MovementMoveDirections {
    LEFT,
    RIGHT,
  };

  void LoadTextures(std::string const textureRootPath);

  void ChangeMovementState(TextureTypes const state);

  void HandleMovementIdle();
  void HandleMovementMove(MovementMoveDirections const direction);

  int const IDEAL_SIZE_WIDTH = 130;
  int const MOVEMENT_MOVE_SPEED = 300;

  TextureContainer textures;

  Size size = {0, 0};
  Position position = {0.0, 0.0};

  TextureTypes movementState = TextureTypes::IDLE;
  MovementMoveDirections movementMoveDirection = MovementMoveDirections::RIGHT;

  Uint32 animationFrameChangedTime = 0;
  Sint16 animationFrame = -1;

  SDL_Rect dstRect = {0, 0, 0, 0};
  SDL_Texture *textureToRender = nullptr;
  SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;

  TTF_Font *font = nullptr;
};
