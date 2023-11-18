#pragma once
#include "Button.h"
#include "Window.h"
#include <vector>

#define TITLE {0,  0,  22, 6}
#define START {9,  7,  4,  1}
#define LOAD  {9,  9,  4,  1}
#define QUIT  {9,  11, 4,  1}
#define WEIRD_HP_THING_ something
#define SAVE  {20, 3,  2,  1}
#define MENU  {20, 5,  2,  1}

class UI
{
public:
	UI(Window* w, int tR);
	~UI();
	void Init();
	void RenderMainMenu();
	void RenderGameMenu();
	void HandleMainMenuEvents(const SDL_Event* event);
	void HandleGameMenuEvents(const SDL_Event* event);
	Uint32 Get_UI_EVENT() { return UIEvent; }

private:
	int tileRes;
	Window* window;

	int returnValue;

	std::vector<Button*> menuButtons;
	std::vector<Button*> gameButtons;
	//the rest will be renderdraw-ed on the screen for now
	SDL_Rect titleRect;

	Uint32 UIEvent;

};
