#pragma once
#include "Button.h"
#include "Game.h"
#include "TextureManager.h"

Button::Button(void (*func)(Uint32), Uint32 UIEvent, int tR, int x, int y, int w, int h, SDL_Texture* t)
{

    Rect.x = x * tR;
    Rect.y = y * tR;
    Rect.w = w * tR;
    Rect.h = h * tR;

    objTexture = t;

    Update();

    this->funcP = func;

    this->UIEvent = UIEvent;

    isHovered = false;
}

Button::Button(void (*func)(), int tR, int x, int y, int w, int h, SDL_Texture* t)
{
    Rect.x = x * tR;
    Rect.y = y * tR;
    Rect.w = w * tR;
    Rect.h = h * tR;

    objTexture = t;

    this->func = func;

    this->UIEvent = (Uint32)-1;

    isHovered = false;
}

bool Button::HandleEvent(const SDL_Event* Event) {
    if (Event->type == SDL_MOUSEBUTTONDOWN && Event->button.button == SDL_BUTTON_LEFT && isHovered)
    {
        if (UIEvent == (Uint32)-1)
        {
            func(); // call the function passed into the button
        }
        else {
            funcP(UIEvent);
        }
    }
    else if (Event->type == SDL_MOUSEMOTION) [[likely]]
    {
        if (isHovered != IsWithinBounds(Event->motion.x, Event->motion.y)) {
            isHovered = !isHovered;
            Update(); 
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