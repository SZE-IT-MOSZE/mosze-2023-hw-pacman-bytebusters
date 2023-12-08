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
	UI(UI& other) = delete; //!< T�r�lt copy konstruktor
	void operator=(const UI&) = delete; //!< T�r�rlt = oper�tor
	~UI(); //!< Destruktor

	int Init(); //!< UI inicializ�l�sa
	void RenderMainMenu(); //!< F�men� kirajzol�sa
	void RenderGameMenu(); //!< J�t�k k�zbeni men� kirajzol�sa
	void SetHP(int hp); //!< Player HP be�ll�t�sa
	void HandleMainMenuEvents(const SDL_Event* event); //!< Esem�nyek f�men�ben
	void HandleGameMenuEvents(const SDL_Event* event); //!< J�t�k k�zbeni men� esem�nyek
	Uint32 Get_UI_EVENT() { return UIEvent; } //!< Egyedi UI event lek�r�se

private:
	UI(const int tR); //!< Priv�t konstruktor, cella m�ret
	static std::weak_ptr<UI> instance_; //!< Singleton instance
	static std::mutex mutex_; //!< Thread guard

	int tileRes; //!< Cella m�ret

	std::vector<std::unique_ptr<Button>> menuButtons; //!< F�men� gombok
	std::vector<std::unique_ptr<Button>> gameButtons; //!< J�t�k k�zbeni men� gombok
	SDL_Rect titleRect; //!< F�men� h�tt�r poz�ci�/m�ret
	SDL_Rect HPDisplay; //!< �letpont kijelz�s poz�ci�/m�ret

	Uint32 UIEvent; //!< Egyedi UI Event

	int playerHP; //!< J�t�kos �letpontjai

	void DisplayHP(); //!< �letpontok kirajzol�sa
};
