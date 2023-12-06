#pragma once
#include "Button.h"
#include "Window.h"
#include <vector>
#include <mutex>

#define TITLE		0,  0,  22, 15
#define START		9,  3,  4,  1
#define START_HOVER 9,  3,  5,  1
#define LOAD		9,  5,  4,  1
#define LOAD_HOVER  9,  5,  5,  1
#define QUIT		9,  7, 4,  1
#define QUIT_HOVER  9,  7, 5,  1
#define SAVE		20, 3,  2,  1
#define SAVE_HOVER  20, 3,  2,  1
#define MENU		20, 5,  2,  1
#define MENU_HOVER  20, 5,  2,  1
#define HP_X 20
#define HP_Y 7

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
	static std::weak_ptr<UI> instance_;
	static std::mutex mutex_;

	int tileRes;
	int returnValue;

	std::vector<std::unique_ptr<Button>> menuButtons;
	std::vector<std::unique_ptr<Button>> gameButtons;
	SDL_Rect titleRect;
	SDL_Rect HPDisplay;

	Uint32 UIEvent;

	int playerHP;

	void DisplayHP();
};
