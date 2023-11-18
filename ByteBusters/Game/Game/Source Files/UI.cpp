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

void StartGame(Uint32 UIEvent) {
	SDL_Event event;
	//SDL_zero(event);
	event.type = UIEvent;
	event.user.code = EVENT_START;
	SDL_PushEvent(&event);
	std::cout << "StartGame \n";
}

void LoadGame(Uint32 UIEvent) {
	SDL_Event event;
	//SDL_zero(event);
	event.type = UIEvent;
	event.user.code = EVENT_LOAD;
	SDL_PushEvent(&event);
	std::cout<< "LoadGame \n";
}

void SaveGame(Uint32 UIEvent) {
	SDL_Event event;
	//SDL_zero(event);
	event.type = UIEvent;
	event.user.code = EVENT_SAVE;
	SDL_PushEvent(&event);
	std::cout << "SaveGame \n";
}

void ToMenu(Uint32 UIEvent) {
	SDL_Event event;
	//SDL_zero(event);
	event.type = UIEvent;
	event.user.code = EVENT_MENU;
	SDL_PushEvent(&event);
	std::cout << "ToMenu \n";
}

UI::UI(Window* w, int tR)
{
	returnValue = 0;
	tileRes = tR;
	window = w;
	

	UIEvent = SDL_RegisterEvents(1);
	if (UIEvent == ((Uint32)-1)) {
		std::cout << "CUSTOM EVENT CREATON FAILED \n";
	}

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

void UI::Init() {
	int pos0[4] = START; // do this properly later
	menuButtons.push_back(new Button(window, StartGame, UIEvent, tileRes, pos0, TextureManager::start));
	int pos1[4] = LOAD;
	menuButtons.push_back(new Button(window, LoadGame, UIEvent, tileRes, pos1, TextureManager::load));
	int pos2[4] = QUIT;
	menuButtons.push_back(new Button(window, QuitGame, tileRes, pos2, TextureManager::quit));
	int pos3[4] = SAVE;
	gameButtons.push_back(new Button(window, SaveGame, UIEvent, tileRes, pos3, TextureManager::save));
	int pos4[4] = MENU;
	gameButtons.push_back(new Button(window, ToMenu, UIEvent, tileRes, pos4, TextureManager::menu));
	//int pos[4] = WEIRD_HP_THING_;
	//Buttons.push_back(new Button(window, StartGame, tileRes, pos));
	int pos5[4] = TITLE;
	titleRect.x = pos5[0] * tileRes;
	titleRect.y = pos5[1] * tileRes;
	titleRect.w = pos5[2] * tileRes;	// you should really do this properly
	titleRect.h = pos5[3] * tileRes;
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
