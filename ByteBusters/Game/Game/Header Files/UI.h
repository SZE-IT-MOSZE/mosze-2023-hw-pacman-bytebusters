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
	static std::shared_ptr<UI> GetInstance(const int tR); //!< Singleton GetInstance
	UI(UI& other) = delete; //!< Törölt copy konstruktor
	void operator=(const UI&) = delete; //!< Törörlt = operátor
	~UI(); //!< Destruktor

	int Init(); //!< UI inicializálása
	void RenderMainMenu(); //!< Fõmenü kirajzolása
	void RenderGameMenu(); //!< Játék közbeni menü kirajzolása
	void SetHP(int hp); //!< Player HP beállítása
	void HandleMainMenuEvents(const SDL_Event* event); //!< Események fõmenüben
	void HandleGameMenuEvents(const SDL_Event* event); //!< Játék közbeni menü események
	Uint32 Get_UI_EVENT() { return UIEvent; } //!< Egyedi UI event lekérése

private:
	UI(const int tR); //!< Privát konstruktor, cella méret
	static std::weak_ptr<UI> instance_; //!< Singleton instance
	static std::mutex mutex_; //!< Thread guard

	int tileRes; //!< Cella méret

	std::vector<std::unique_ptr<Button>> menuButtons; //!< Fõmenü gombok
	std::vector<std::unique_ptr<Button>> gameButtons; //!< Játék közbeni menü gombok
	SDL_Rect titleRect; //!< Fõmenü háttér pozíció/méret
	SDL_Rect HPDisplay; //!< Életpont kijelzés pozíció/méret

	Uint32 UIEvent; //!< Egyedi UI Event

	int playerHP; //!< Játékos életpontjai

	void DisplayHP(); //!< Életpontok kirajzolása
};
