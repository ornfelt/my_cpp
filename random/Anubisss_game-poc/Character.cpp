#include "Character.h"

#include <iostream>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <cmath>
#include <sstream>

#include <SDL2/SDL_image.h>

#include "Game.h"

Character::Character(SDL_Renderer *renderer, std::string const textureRootPath) : GameObject(renderer) {
  LoadTextures(textureRootPath);

  font = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 18);
  if (!font) {
    std::cerr << "Can't load font: " << std::endl;
    std::cerr << TTF_GetError() << std::endl;
  }

  position.X = 30.0;
  position.Y = 839.0; // -size.Height;

  dstRect.w = size.Width;
  dstRect.h = size.Height;
}

void Character::LoadTextures(std::string const textureRootPath) {
  std::map<TextureTypes, std::string> textureDirectoryPathMap = {
    { TextureTypes::IDLE, textureRootPath + "/idle" },
    { TextureTypes::RUN, textureRootPath + "/run" },
  };

  SDL_Surface *surface;
  for (auto const& textureDirectoryPath : textureDirectoryPathMap) {
    if (!boost::filesystem::is_directory(textureDirectoryPath.second) ||
        boost::filesystem::is_empty(textureDirectoryPath.second)) {
      std::cerr << "Invalid or empty directory: \"" << textureDirectoryPath.second << "\"" << std::endl;
      return;
    }

    std::vector<std::string> texturePaths;
    for (auto const& filePath : boost::filesystem::directory_iterator(textureDirectoryPath.second))
      texturePaths.push_back(filePath.path().string());
    std::sort(texturePaths.begin(), texturePaths.end());

    for (auto const& texturePath : texturePaths) {
      surface = IMG_Load(texturePath.c_str());
      if (!surface) {
        std::cerr << "Can't load the texture: \"" << texturePath << "\"" << std::endl;
        std::cerr << IMG_GetError() << std::endl;
        return;
      }

      if (!size.Width) {
        float sizeConversionRate = static_cast<float>(IDEAL_SIZE_WIDTH) / static_cast<float>(surface->w);

        size.Width = static_cast<int>(surface->w * sizeConversionRate);
        size.Height = static_cast<int>(surface->h * sizeConversionRate);
      }

      SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
      if (!texture) {
        std::cerr << "Can't create texture from surface: \"" << texturePath << "\"" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return;
      }
      SDL_FreeSurface(surface);

      textures[textureDirectoryPath.first].push_back(texture);
    }
  }
}

void Character::Update(Uint32 const diff) {
  if (movementState == TextureTypes::RUN) {
    double mod = static_cast<double>(diff) / Game::SECOND * MOVEMENT_MOVE_SPEED;
    if (movementMoveDirection == MovementMoveDirections::LEFT)
      mod *= -1.0;
    position.X += mod;
  }

  dstRect.x = static_cast<int>(std::nearbyint(position.X));
  dstRect.y = static_cast<int>(std::nearbyint(position.Y));

  Uint32 ticks = SDL_GetTicks();
  if (ticks - animationFrameChangedTime >= 55) {
    animationFrameChangedTime = ticks;

    if (++animationFrame > textures[movementState].size() - 1)
      animationFrame = 0;

    textureToRender = textures[movementState][animationFrame];
  }
}

void Character::Render() {
  SDL_RenderCopyEx(renderer, textureToRender, nullptr, &dstRect, 0, nullptr, flip);

  std::ostringstream text;
  text << "X: " << position.X << " Y: " << position.Y;
  SDL_Surface *surface = TTF_RenderText_Blended(font, text.str().c_str(), { 0, 0, 0, 255 });
  SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_Rect t;
  t.x = dstRect.x;
  t.y = dstRect.y;
  t.w = surface->w;
  t.h = surface->h;

  SDL_RenderCopy(renderer, textTexture, nullptr, &t);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(textTexture);
}

void Character::HandleEvents(SDL_Event const* event) {
  switch (event->type) {
    case SDL_KEYDOWN:
    case SDL_KEYUP: {
      SDL_Keycode keycode = event->key.keysym.sym;
      switch (keycode) {
        case SDLK_LEFT:
        case SDLK_RIGHT:
          if (event->type == SDL_KEYDOWN)
            HandleMovementMove(keycode == SDLK_LEFT ? MovementMoveDirections::LEFT : MovementMoveDirections::RIGHT);
          else if (event->type == SDL_KEYUP)
            HandleMovementIdle();
          break;
        case SDLK_UP:
          if (event->type == SDL_KEYDOWN)
            position.Y -= 1.0;
          break;
        case SDLK_DOWN:
          if (event->type == SDL_KEYDOWN)
            position.Y += 1.0;
          break;
      }
      break;
    }
    default:
      std::cerr << "Unhandled event type: " << std::endl;
      break;
  }
}

void Character::ChangeMovementState(TextureTypes const state) {
  movementState = state;
  animationFrameChangedTime = 0;
  animationFrame = -1;
}

void Character::HandleMovementIdle() {
  ChangeMovementState(TextureTypes::IDLE);
}

void Character::HandleMovementMove(MovementMoveDirections const direction) {
  if (direction == MovementMoveDirections::LEFT)
    flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
  else
    flip = SDL_RendererFlip::SDL_FLIP_NONE;

  movementMoveDirection = direction;
  ChangeMovementState(TextureTypes::RUN);
}
