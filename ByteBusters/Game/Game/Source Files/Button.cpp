#pragma once
#include "Button.h"
#include "Game.h"
#include "TextureManager.h"

Button::Button(Window* window, void (*func)(Uint32), Uint32 UIEvent, int tR, int pos[4], SDL_Texture* t)
{
    Rect.x = pos[0] * tR;
    Rect.y = pos[1] * tR;
    Rect.w = pos[2] * tR;
    Rect.h = pos[3] * tR;

    objTexture = t;

    SDLWindowSurface = SDL_GetWindowSurface(window->GetWindow());
    Update();
    std::cout << "button created" << "\n";

    this->funcP = func;

    this->UIEvent = UIEvent;

    isHovered = false;
}

Button::Button(Window* window, void (*func)(), int tR, int pos[4], SDL_Texture* t)
{
    Rect.x = pos[0] * tR;
    Rect.y = pos[1] * tR;
    Rect.w = pos[2] * tR;
    Rect.h = pos[3] * tR;

    objTexture = t;

    SDLWindowSurface = SDL_GetWindowSurface(window->GetWindow());
    Update();
    std::cout << "button created" << "\n";

    this->func = func;

    this->UIEvent = (Uint32)-1;

    isHovered = false;
}

//Button::Button(SDL_Window* window, void (*func)())
//{
//    objTexture = TextureManager::err_;
//
//    SDLWindowSurface = SDL_GetWindowSurface(window);
//    Update();
//    std::cout << "button created" << "\n";
//
//    this->func = func;
//}

bool Button::HandleEvent(const SDL_Event* Event) {
    if (Event->type == SDL_MOUSEBUTTONDOWN && Event->button.button == SDL_BUTTON_LEFT && isHovered)
    {
        std::cout << "button pressed" << "\n";
        if (UIEvent == (Uint32)-1)
        {
            func(); // call the function pressed into the button
        }
        else {
            funcP(UIEvent);
        }
        
    }
    else if (Event->type == SDL_MOUSEMOTION) [[likely]]
    {
        if (isHovered != IsWithinBounds(Event->motion.x, Event->motion.y)) {
            isHovered = !isHovered;
            Update(); std::cout << "hover" << "\n";
        }

        return isHovered;
    }
    return false;
}

bool Button::IsWithinBounds(int x, int y) {
    // Too far left
    if (x < Rect.x) return false;

    // Too far right
    if (x > Rect.x + Rect.w) return false;

    // Too high
    if (y < Rect.y) return false;

    // Too low
    if (y > Rect.y + Rect.h) return false;

    // Inside rectangle
    return true;
}

void Button::Update() {
    
}

void Button::Render() {
    SDL_RenderCopy(Game::renderer, objTexture, NULL, &Rect);
}