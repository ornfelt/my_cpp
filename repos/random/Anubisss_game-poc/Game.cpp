#include "Game.h"

#include <iostream>

#include <SDL2/SDL_image.h>

#include "Character.h"

void Game::Init() {
  isRunning = true;

  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

  SDL_Window *window = SDL_CreateWindow("Game title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
  //SDL_Window *window = SDL_CreateWindow("Game title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  SDL_GetRendererOutputSize(renderer, &windowSizeWidth, &windowSizeHeight);
  std::cout << windowSizeWidth << " " << windowSizeHeight << std::endl;

  font = TTF_OpenFont(FPS_TEXT_FONT_PATH.c_str(), FPS_TEXT_FONT_SIZE);
  if (!font) {
    std::cerr << "Can't load font: " << "\"" << FPS_TEXT_FONT_PATH << "\"" << std::endl;
    std::cerr << TTF_GetError() << std::endl;
  }

  map = new Map(renderer, windowSizeWidth, windowSizeHeight);
}

void Game::LoadCharacters() {
  Character *character = new Character(renderer, "assets/freeknight");
  player = character;
  Add(character);
}

void Game::RunMainLoop() {
  Uint32 updateStart, updateInterval;
  Uint32 previousUpdateStart = SDL_GetTicks();
  Uint32 updateDiff = 0;

  while (isRunning) {
    updateStart = SDL_GetTicks();
    updateDiff = updateStart - previousUpdateStart;
    previousUpdateStart = updateStart;

    HandleEvents();
    Update(updateDiff);
    Render();

    CalculateFps();

    updateInterval = SDL_GetTicks() - updateStart;
    if (updateInterval < MAX_UPDATE_DELAY)
      SDL_Delay(MAX_UPDATE_DELAY - updateInterval);
  }
}

void Game::HandleEvents() {
  SDL_Event event;
  if (SDL_PollEvent(&event) == 0)
    return;

  switch (event.type) {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        isRunning = false;
      else if (!event.key.repeat)
        player->HandleEvents(&event);
      break;
    case SDL_QUIT:
      isRunning = false;
      break;
    default:
      break;
  }
}

void Game::Update(Uint32 const diff) {
  for (auto& gameObject : gameObjects)
    gameObject->Update(diff);
}

void Game::Render() {
  SDL_RenderClear(renderer);

  map->Render();

  for (auto& gameObject : gameObjects)
    gameObject->Render();

  RenderFps();

  SDL_RenderPresent(renderer);
}

void Game::CalculateFps() {
  ++fps;

  Uint32 ticks = SDL_GetTicks();
  if (ticks - fpsLastCollectTime >= SECOND) {
    if (fps != fpsPrevious) {
      fpsPrevious = fps;

      if (fpsTexture)
        SDL_DestroyTexture(fpsTexture);

      std::string const fpsText = "FPS: " + std::to_string(fps);
      SDL_Surface *surface = TTF_RenderText_Blended(font, fpsText.c_str(), FPS_TEXT_COLOR);
      fpsTexture = SDL_CreateTextureFromSurface(renderer, surface);

      fpsTextPosition.x = windowSizeWidth - surface->w + FPS_TEXT_POSITION_X_OFFSET;
      fpsTextPosition.y = surface->h + FPS_TEXT_POSITION_Y_OFFSET;
      fpsTextPosition.w = surface->w;
      fpsTextPosition.h = surface->h;

      SDL_FreeSurface(surface);
    }

    fps = 0;
    fpsLastCollectTime = ticks;
  }
}

void Game::RenderFps() {
  SDL_RenderCopy(renderer, fpsTexture, nullptr, &fpsTextPosition);
}
