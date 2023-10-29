#include "Game.h"

SDL_Renderer* Game::renderer;

Game::Game() {
	height = 480; // default is smallest res
	width = 640;
	tileRes = 32;
	isRunning = false;
	window = nullptr;

}

Game::~Game() {
	//looks too empty, youre forgetting things
	delete map;
}

bool Game::Init(const char* title, int xPos, int yPos, int w, int h, int tR, bool fullscreen)
{	
	height = h;
	width = w;
	tileRes = tR;
	

	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem:" << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			std::cout << "Renderer created!" << std::endl;
		}
	}
	else {
		return false;
	}

	TextureManager::LoadAllTextures(); /*/////////////////////////////////*/

	GameObjectManager::SetTileSize(tileRes);

	map = new Map(tileRes);

	return true;
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	map->DrawMap(); ///////////////////////////////////////////////// only for background now

	GameObjectManager::RenderAllGameObjects();

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	//GameObjectManager::DestroyAllGameObjects();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			player->SetVelX(-1);
			break;
		case SDLK_RIGHT:
			player->SetVelX(1);
			break;
		case SDLK_UP:
			player->SetVelY(-1);
			break;
		case SDLK_DOWN:
			player->SetVelY(1);
			break;
		default:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			player->SetVelX(0);
			break;
		case SDLK_RIGHT:
			player->SetVelX(0);
			break;
		case SDLK_UP:
			player->SetVelY(0);
			break;
		case SDLK_DOWN:
			player->SetVelY(0);
			break;
		default:
			break;
		}
		break;


	case SDL_QUIT:
		
		isRunning = false;
		gameUpdates->join(); // ?????????? this is a feature (X loaded the next map, did not quit the program...)
		quitGame = true; //this is a "fix" for that...........
		break;
	default:
		break;
	}
}

void Game::Start()
{

	const int FPS = 30;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	// generally better to create player before everything, as player is pointer that can be null, while the rest are in lists that exist from the beggining as an empty list empty and get filled in later
	player = GameObjectManager::CreateGameObject(GameObjectManager::player, tileRes, tileRes); //only need pointer to call SetVelX/Y at this time

	for (size_t i = 1; i <= 20; i++) // map counter
	{
		
		map->LoadMap(i);
		GameObjectManager::CreateGameObject(GameObjectManager::soldier, tileRes * 18, tileRes * 13);
		GameObjectManager::CreateGameObject(GameObjectManager::soldier, tileRes * 18, tileRes * 13);

		isRunning = true;

		gameUpdates = new std::thread(&Game::UpdateThread, this); // pointer to non-static member function (Game:: necessary), pointer to object (this)

		while (isRunning)
		{
			frameStart = SDL_GetTicks();
			
			HandleEvents();
			Render();

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (GameObjectManager::AreAllItemsPickedUp())
			{
				isRunning = false;
				gameUpdates->join();

				std::cout << "All Items Picked Up" << std::endl;
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime);
			}
		}

		GameObjectManager::DestroyAllExceptPlayer();
		player->Reset();

		if (quitGame) // stupid quick fix
		{
			break;
		}
	}
}

void Game::UpdateThread() {
	
	std::cout << "Thread Created" << std::endl;
	std::cout << tileRes << std::endl;

	const int UPS = tileRes * 3;
	const int frameDelay = 1000 / UPS;

	Uint32 frameStart;
	int frameTime;

	while (isRunning)
	{

		frameStart = SDL_GetTicks();

		GameObjectManager::UpdateAllGameObjects();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	
	std::cout << "Thread Finished" << std::endl;
	
}