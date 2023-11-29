#pragma once
#include "SDL.h"
#include <iostream>
#include "Window.h"

class Button {
public:
    Button(void (*func)(Uint32), Uint32 UIEvent, int tR, int x, int y, int w, int h, SDL_Texture* t);
    Button(void (*func)(), int tR, int x, int y, int w, int h, SDL_Texture* t);

    //Button(SDL_Window* window, void (*func)(), int tR, int pos[4]);

    bool HandleEvent(const SDL_Event* Event);

    void Render();

private:


    bool IsWithinBounds(int x, int y);

    void Update();

    SDL_Texture* objTexture;

    bool isHovered;
    SDL_Rect Rect;

    //SDL_Surface* SDLWindowSurface{ nullptr };

    void (*funcP)(Uint32);
    void (*func)();

    Uint32 UIEvent;

};