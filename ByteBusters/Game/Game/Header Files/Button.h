#pragma once
#include "SDL.h"
#include <iostream>

class Button {
public:
    Button(void (*func)(Uint32), Uint32 UIEvent, int tR, int x, int y, int w, int h, int xh, int yh, int wh, int hh, SDL_Texture* t, SDL_Texture* th); //!< Button konstruktor, kattintásra végrehajtandó funkció, egyedi UI_Event, pozíció-méret hover/no-hover, textúra hover/no-hover 
    Button(void (*func)(), int tR, int x, int y, int w, int h, int xh, int yh, int wh, int hh, SDL_Texture* t, SDL_Texture* th); //!< Button konstruktor, kattintásra végrehajtandó funkció, pozíció-méret hover/no-hover, textúra hover/no-hover

    void HandleEvent(const SDL_Event* Event); //!< Egérmozgás, kattintás lekezelése 

    void Render(); //!< Megjelenítés

private:


    bool IsWithinBounds(int x, int y); //!< Egér pozíció evaluálása

    void Update(); //!< Textúra cserélése, ha rajta van az egér a gombon

    SDL_Texture* objTexture_display; //!< Aktuális textúra
    SDL_Texture* objTexture_hover; //!< Textúra amikor rajta van az egér
    SDL_Texture* objTexture_basic; //!< Textúra amikor nincs rajta az egér

    bool isHovered; //!< Rajta van-e az egér
    SDL_Rect dstRect_display; //!< Aktuális pozíció és méret
    SDL_Rect dstRect_hover; //!< Pozíció és méret amikor rajta van az egér
    SDL_Rect dstRect_basic; //!< Pozíció és méret amikor nincs rajta az egér

    void (*funcP)(Uint32); //!< gomb funkciója, egyedi Event-et push-ol
    void (*func)(); //!< gomb funkciója

    Uint32 UIEvent; //!< Egyedi event azonosító

};