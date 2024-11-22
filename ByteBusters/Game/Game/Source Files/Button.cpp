#pragma once
#include "Game.h"
#include "Button.h"

Button::Button(void (*func)(Uint32), Uint32 UIEvent, int tR, int x, int y, int w, int h, int xh, int yh, int wh, int hh, SDL_Texture* t, SDL_Texture* th)
{
    dstRect_basic.x = x * tR;
    dstRect_basic.y = y * tR;
    dstRect_basic.w = w * tR;
    dstRect_basic.h = h * tR;

    dstRect_hover.x = xh * tR;
    dstRect_hover.y = yh * tR;
    dstRect_hover.w = wh * tR;
    dstRect_hover.h = hh * tR;

    objTexture_basic = t;
    objTexture_hover = th;

    isHovered = false;

    this->funcP = func;
    this->UIEvent = UIEvent;

    Update();
}

Button::Button(void (*func)(), int tR, int x, int y, int w, int h, int xh, int yh, int wh, int hh, SDL_Texture* t, SDL_Texture* th)
{
    dstRect_basic.x = x * tR;
    dstRect_basic.y = y * tR;
    dstRect_basic.w = w * tR;
    dstRect_basic.h = h * tR;

    dstRect_hover.x = xh * tR;
    dstRect_hover.y = yh * tR;
    dstRect_hover.w = wh * tR;
    dstRect_hover.h = hh * tR;

    objTexture_basic = t;
    objTexture_hover = th;

    isHovered = false;

    this->func = func;
    this->UIEvent = (Uint32)-1;

    Update();
}

void Button::HandleEvent(const SDL_Event* Event) {
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
        return;// isHovered;
    }
    return;// false;
}

bool Button::IsWithinBounds(int x, int y) {
    // Too far left
    if (x < dstRect_basic.x) return false;

    // Too far right
    if (x > dstRect_basic.x + dstRect_basic.w) return false;

    // Too high
    if (y < dstRect_basic.y) return false;

    // Too low
    if (y > dstRect_basic.y + dstRect_basic.h) return false;

    // Inside rectangle
    return true;
}

void Button::Update() {
    if (isHovered)
    {
        dstRect_display = dstRect_hover;
        objTexture_display = objTexture_hover;
    }
    else {
        dstRect_display = dstRect_basic;
        objTexture_display = objTexture_basic;
    }
}

void Button::Render() {
    SDL_RenderCopy(Game::renderer, objTexture_display, NULL, &dstRect_display);
}