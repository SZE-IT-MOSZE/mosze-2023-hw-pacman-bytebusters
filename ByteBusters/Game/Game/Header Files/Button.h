#pragma once
#include "SDL.h"
#include <iostream>
#include "Window.h"

class Button {
public:
    Button(void (*func)(Uint32), Uint32 UIEvent, int tR, int x, int y, int w, int h, int xh, int yh, int wh, int hh, SDL_Texture* t, SDL_Texture* th);
    Button(void (*func)(), int tR, int x, int y, int w, int h, int xh, int yh, int wh, int hh, SDL_Texture* t, SDL_Texture* th);

    void HandleEvent(const SDL_Event* Event);

    void Render();

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

    //SDL_Surface* SDLWindowSurface{ nullptr };

    void (*funcP)(Uint32);
    void (*func)();

    Uint32 UIEvent;

};