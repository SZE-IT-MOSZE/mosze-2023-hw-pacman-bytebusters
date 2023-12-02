#pragma once
#include "Button.h"
#include "Window.h"
#include <vector>
#include <mutex>

#define TITLE 0,  0,  22, 6
#define START 9,  7,  4,  1
#define LOAD  9,  9,  4,  1
#define QUIT  9,  11, 4,  1
#define SAVE  20, 6,  2,  1
#define MENU  20, 8,  2,  1
#define HP_X 20
#define HP_Y 10

class UI
{
public:
	static std::shared_ptr<UI> GetInstance(const int tR);
	UI(UI& other) = delete;
	void operator=(const UI&) = delete;
	~UI();

	int Init();
	void RenderMainMenu();
	void RenderGameMenu();
	void SetHP(int hp);
	void HandleMainMenuEvents(const SDL_Event* event);
	void HandleGameMenuEvents(const SDL_Event* event);
	Uint32 Get_UI_EVENT() { return UIEvent; }

private:
	UI(const int tR);
	static std::shared_ptr<UI> instance_;
	static std::mutex mutex_;

	int tileRes;
	int returnValue;

	std::vector<Button*> menuButtons;
	std::vector<Button*> gameButtons;
	SDL_Rect* titleRect;
	SDL_Rect* HPDisplay;

	Uint32 UIEvent;

	int playerHP;

	void DisplayHP();
};
