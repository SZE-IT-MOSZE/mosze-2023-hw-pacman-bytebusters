#pragma once
#include "SDL.h"
#include <iostream>

class Button {
public:
    Button(void (*func)(Uint32), Uint32 UIEvent, int tR, int x, int y, int w, int h, int xh, int yh, int wh, int hh, SDL_Texture* t, SDL_Texture* th); //!< Button konstruktor, kattint�sra v�grehajtand� funkci�, egyedi UI_Event, poz�ci�-m�ret hover/no-hover, text�ra hover/no-hover 
    Button(void (*func)(), int tR, int x, int y, int w, int h, int xh, int yh, int wh, int hh, SDL_Texture* t, SDL_Texture* th); //!< Button konstruktor, kattint�sra v�grehajtand� funkci�, poz�ci�-m�ret hover/no-hover, text�ra hover/no-hover

    void HandleEvent(const SDL_Event* Event); //!< Eg�rmozg�s, kattint�s lekezel�se 

    void Render(); //!< Megjelen�t�s

private:


    bool IsWithinBounds(int x, int y); //!< Eg�r poz�ci� evalu�l�sa

    void Update(); //!< Text�ra cser�l�se, ha rajta van az eg�r a gombon

    SDL_Texture* objTexture_display; //!< Aktu�lis text�ra
    SDL_Texture* objTexture_hover; //!< Text�ra amikor rajta van az eg�r
    SDL_Texture* objTexture_basic; //!< Text�ra amikor nincs rajta az eg�r

    bool isHovered; //!< Rajta van-e az eg�r
    SDL_Rect dstRect_display; //!< Aktu�lis poz�ci� �s m�ret
    SDL_Rect dstRect_hover; //!< Poz�ci� �s m�ret amikor rajta van az eg�r
    SDL_Rect dstRect_basic; //!< Poz�ci� �s m�ret amikor nincs rajta az eg�r

    void (*funcP)(Uint32); //!< gomb funkci�ja, egyedi Event-et push-ol
    void (*func)(); //!< gomb funkci�ja

    Uint32 UIEvent; //!< Egyedi event azonos�t�

};