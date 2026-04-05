//
// Created by marco on 01/06/2023.
//

#pragma once

#include "Util.h"
#include "Common.h"

#define BUTTON_WIDTH (WIDTH / 6.0f)
#define BUTTON_HEIGHT (70)

typedef struct CalculatorState CalculatorState;

void drawButton(SDL_Window* window, SDL_Renderer* renderer, int ID);
void colorButton(SDL_Window* window, SDL_Renderer* renderer, int ID, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
bool pressButton(SDL_Window* window, SDL_Renderer* renderer, SDL_Event* ev, int ID, int x, int y, CalculatorState* state);
void renderText(SDL_Renderer* renderer);
void initButtons(SDL_Window* window, SDL_Renderer* renderer);
