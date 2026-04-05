//
// Created by marco on 02/04/2026.
//

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Common.h"

extern SDL_Texture* display;
extern SDL_FRect displayRect;
extern SDL_Texture* text[18];
extern TTF_Font* buttonFont;

extern SDL_Color black;
extern SDL_Color white;

void initFont();
void updateText(SDL_Renderer* renderer, const char* buffer);
void freeSDL(SDL_Window* window, SDL_Renderer* renderer);
