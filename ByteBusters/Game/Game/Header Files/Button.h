#pragma once
#include "SDL.h"
#include <iostream>
#include "Window.h"

class Button {
public:
    Button(void (*func)(Uint32), Uint32 UIEvent, int tR, int x, int y, int w, int h, int xh, int yh, int wh, int hh, SDL_Texture* t, SDL_Texture* th); //!< Button konstruktor, kattint�sra v�grehajtand� funkci�, egyedi UI_Event, poz�ci�-m�ret hover/no-hover, text�ra hover/no-hover 
    Button(void (*func)(), int tR, int x, int y, int w, int h, int xh, int yh, int wh, int hh, SDL_Texture* t, SDL_Texture* th); //!< Button konstruktor, kattint�sra v�grehajtand� funkci�, poz�ci�-m�ret hover/no-hover, text�ra hover/no-hover

    void HandleEvent(const SDL_Event* Event); //!< Eg�rmozg�s, kattint�s lekezel�se 

    void Render(); //!< Megjelen�t�s

private:


    bool IsWithinBounds(int x, int y);

    void Update();

    SDL_Texture* objTexture_display;
    SDL_Texture* objTexture_hover;
    SDL_Texture* objTexture_basic;

    bool isHovered;
    SDL_Rect dstRect_display;
    SDL_Rect dstRect_hover;
    SDL_Rect dstRect_basic;

    void (*funcP)(Uint32);
    void (*func)();

    Uint32 UIEvent;

};