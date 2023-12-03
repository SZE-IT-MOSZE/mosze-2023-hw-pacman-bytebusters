#pragma once
#include "UI.h"
#include "TextureManager.h"
#include "Defines.h"

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
	returnValue = 0;
	tileRes = tR;	
	playerHP = 0;

	UIEvent = (Uint32)-1;
}

UI::~UI()
{
	for (auto e : menuButtons) {
		delete e;
	}
	menuButtons.clear();
	for (auto e : gameButtons) {
		delete e;
	}
	gameButtons.clear();
}

int UI::Init() {
	UIEvent = SDL_RegisterEvents(1);
	if (UIEvent == ((Uint32)-1)) {
		std::cout << "CUSTOM EVENT CREATON FAILED \n";
		return -1;
	}

	menuButtons.push_back(new Button(StartGame, UIEvent, tileRes, START, TextureManager::start));
	menuButtons.push_back(new Button(LoadGame, UIEvent, tileRes, LOAD, TextureManager::load));
	menuButtons.push_back(new Button(QuitGame, tileRes, QUIT, TextureManager::quit));
	gameButtons.push_back(new Button(SaveGame, UIEvent, tileRes, SAVE, TextureManager::save));
	gameButtons.push_back(new Button(ToMenu, UIEvent, tileRes, MENU, TextureManager::menu));

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
	for (auto e : menuButtons) {
		e->Render();
	}
	TextureManager::Draw(TextureManager::title, NULL, &titleRect);
}

void UI::RenderGameMenu() {
	for (auto e : gameButtons) {
		e->Render();
	}
	DisplayHP();
}

void UI::HandleMainMenuEvents(const SDL_Event* event) {
	for (auto e : menuButtons) {
		e->HandleEvent(event);
	}
}

void UI::HandleGameMenuEvents(const SDL_Event* event) {
	for (auto e : gameButtons) {
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