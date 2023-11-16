#pragma once
#include "SDL.h"
#include <iostream>
#include "Window.h"

class Button {
public:
    Button(Window* window)
    { 
        SDLWindowSurface = SDL_GetWindowSurface(window->GetWindow());
        Update();
        std::cout << "button created" << "\n";
    }
    Button(SDL_Window* window)
    {
        SDLWindowSurface = SDL_GetWindowSurface(window);
        Update();
        std::cout << "button created" << "\n";
    }

    bool HandleEvent(const SDL_Event* Event) {
        if (Event->type == SDL_MOUSEBUTTONDOWN && Event->button.button == SDL_BUTTON_LEFT && isHovered) 
        {
            std::cout << "button pressed" << "\n";
        }
        else if (Event->type == SDL_MOUSEMOTION) [[likely]]
        {
            if (isHovered != IsWithinBounds(Event->motion.x, Event->motion.y)) {
                isHovered = !isHovered;
                Update();std::cout << "hover" << "\n";
            }
                
            return isHovered;
        }
        return false;
    }


private:
    bool IsWithinBounds(int x, int y) {
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

    void Update() {
        auto [r, g, b, a] { isHovered ? HoverColor : BGColor };
        SDL_FillRect(SDLWindowSurface, &Rect, SDL_MapRGB(SDLWindowSurface->format, r, g, b));
    }

    bool isHovered{ false };
    SDL_Color BGColor{ 255, 50, 50, 255 };
    SDL_Color HoverColor{ 50, 50, 255, 255 };
    SDL_Rect Rect{ 50, 50, 50, 50 };

    SDL_Surface* SDLWindowSurface{ nullptr };

};