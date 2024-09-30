#include "Game.h"

int main(int argc, char *argv[]) {
	Game game;

	game.Init();
	game.LoadCharacters();

	game.RunMainLoop();

	return 0;
}