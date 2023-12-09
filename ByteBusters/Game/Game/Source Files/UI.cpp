#pragma once
#include "UI.h"
#include "Defines.h"
#include "TextureManager.h"

//codes: 0-nothing, 1-start, 2-load, 3-save, 4-menu (quit is basic sdl event)
void QuitGame() {
	std::cout << "QuitGame \n";
	SDL_Event quitEvent;
	quitEvent.type = SDL_QUIT;
	SDL_PushEvent(&quitEvent);
}
//codes: 0-nothing, 1-start, 2-load, 3-save, 4-menu (quit is basic sdl event)
void StartGame(Uint32 UIEvent) {
	SDL_Event event;
	//SDL_zero(event);
	event.type = UIEvent;
	event.user.code = EVENT_START;
	SDL_PushEvent(&event);
	std::cout << "StartGame \n";
}
//codes: 0-nothing, 1-start, 2-load, 3-save, 4-menu (quit is basic sdl event)
void LoadGame(Uint32 UIEvent) {
	SDL_Event event;
	//SDL_zero(event);
	event.type = UIEvent;
	event.user.code = EVENT_LOAD;
	SDL_PushEvent(&event);
	std::cout<< "LoadGame \n";
}
//codes: 0-nothing, 1-start, 2-load, 3-save, 4-menu (quit is basic sdl event)
void SaveGame(Uint32 UIEvent) {
	SDL_Event event;
	//SDL_zero(event);
	event.type = UIEvent;
	event.user.code = EVENT_SAVE;
	SDL_PushEvent(&event);
	std::cout << "SaveGame \n";
}
//codes: 0-nothing, 1-start, 2-load, 3-save, 4-menu (quit is basic sdl event)
void ToMenu(Uint32 UIEvent) {
	SDL_Event event;
	//SDL_zero(event);
	event.type = UIEvent;
	event.user.code = EVENT_MENU;
	SDL_PushEvent(&event);
	std::cout << "ToMenu \n";
}

std::weak_ptr<UI> UI::instance_;
std::mutex UI::mutex_;

std::shared_ptr<UI> UI::GetInstance(const int tR) {
	std::lock_guard<std::mutex> lock(mutex_);
	std::shared_ptr<UI> sharedInstance;
	if (!(sharedInstance = instance_.lock())) {
		sharedInstance = std::shared_ptr<UI>(new UI(tR));
		instance_ = sharedInstance;
	}
	return sharedInstance;
}

UI::UI(int tR)
{
	tileRes = tR;	
	playerHP = 0;

	UIEvent = (Uint32)-1;

	titleRect.x = 0;
	titleRect.y = 0;
	titleRect.w = 0;
	titleRect.h = 0;
				  
	HPDisplay.x = 0;
	HPDisplay.y = 0;
	HPDisplay.w = 0;
	HPDisplay.h = 0;
}

UI::~UI()
{
	menuButtons.clear();
	gameButtons.clear();
}

int UI::Init() {
	UIEvent = SDL_RegisterEvents(1);
	if (UIEvent == ((Uint32)-1)) {
		std::cout << "CUSTOM EVENT CREATON FAILED \n";
		return -1;
	}

	menuButtons.push_back(std::make_unique<Button>(StartGame, UIEvent, tileRes, START, START_HOVER, TextureManager::start, TextureManager::start_hover));
	menuButtons.push_back(std::make_unique<Button>(LoadGame, UIEvent, tileRes, LOAD, LOAD_HOVER, TextureManager::load, TextureManager::load_hover));
	menuButtons.push_back(std::make_unique<Button>(QuitGame, tileRes, QUIT, QUIT_HOVER, TextureManager::quit, TextureManager::quit_hover));
	gameButtons.push_back(std::make_unique<Button>(SaveGame, UIEvent, tileRes, SAVE, SAVE_HOVER, TextureManager::save, TextureManager::save_hover));
	gameButtons.push_back(std::make_unique<Button>(ToMenu, UIEvent, tileRes, MENU, MENU_HOVER, TextureManager::menu, TextureManager::menu_hover));

	constexpr int pos[4] = { TITLE }; // it's fine
	titleRect.x = pos[0] * tileRes;
	titleRect.y = pos[1] * tileRes;
	titleRect.w = pos[2] * tileRes;
	titleRect.h = pos[3] * tileRes;

	HPDisplay.x = 0;
	HPDisplay.y = 0;
	HPDisplay.w = tileRes;
	HPDisplay.h = tileRes;
	return 0;
}

void UI::RenderMainMenu() {
	TextureManager::Draw(TextureManager::title, NULL, &titleRect); // render first because it overlays the buttons
	for (auto& e : menuButtons) {
		e->Render();
	}
}

void UI::RenderGameMenu() {
	for (auto& e : gameButtons) {
		e->Render();
	}
	DisplayHP();
}

void UI::HandleMainMenuEvents(const SDL_Event* event) {
	for (auto& e : menuButtons) {
		e->HandleEvent(event);
	}
}

void UI::HandleGameMenuEvents(const SDL_Event* event) {
	for (auto& e : gameButtons) {
		e->HandleEvent(event);
	}
}

void UI::SetHP(int hp)
{
	playerHP = hp;
}

void UI::DisplayHP() {
	for (size_t i = 0; i < playerHP; i++)
	{
		HPDisplay.x = HP_X * tileRes + (i % 2) * tileRes;
		HPDisplay.y = HP_Y * tileRes + (i / 2) * tileRes;
		TextureManager::Draw(TextureManager::heart, NULL, &HPDisplay);
	}
}