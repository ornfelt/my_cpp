#pragma once

#include <string>
#include <list>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "GameObject.h"
#include "Character.h"
#include "Map.h"

class Game {
 public:
  static Uint32 const SECOND = 1000;

  void Init();
  void LoadCharacters();

  void RunMainLoop();

  void Add(GameObject *gameObject) { gameObjects.push_back(gameObject); }

 private:
  void HandleEvents();
  void Update(Uint32 const diff);
  void Render();

  void CalculateFps();
  void RenderFps();

  Uint32 const MAX_FPS = 70;
  Uint32 const MAX_UPDATE_DELAY = SECOND / MAX_FPS;

  std::string const FPS_TEXT_FONT_PATH = "assets/fonts/OpenSans-Regular.ttf";
  int const FPS_TEXT_FONT_SIZE = 14;
  SDL_Color const FPS_TEXT_COLOR = { 0x75, 0x75, 0x75, 255 };
  int const FPS_TEXT_POSITION_X_OFFSET = -5;
  int const FPS_TEXT_POSITION_Y_OFFSET = -15;

  bool isRunning = false;
  int windowSizeWidth = 0;
  int windowSizeHeight = 0;

  SDL_Renderer *renderer = nullptr;
  TTF_Font *font = nullptr;

  Uint32 fps = 0;
  Uint32 fpsPrevious = 0;
  Uint32 fpsLastCollectTime = 0;
  SDL_Texture *fpsTexture = nullptr;
  SDL_Rect fpsTextPosition = {0, 0, 0, 0};

  Map const* map = nullptr;
  Character *player = nullptr;
  std::list<GameObject*> gameObjects;
};
