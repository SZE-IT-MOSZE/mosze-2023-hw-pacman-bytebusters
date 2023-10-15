#include "SDL.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int FPS = 30;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->Init("DEER-MURDER-HORROR-BLOOD-GORE (The Game)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 960, false); //1280x960 would be the perfect fit

	while (game->Running())
	{
		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

	}

	game->Clean();

	return 0;
}