//
// Created by marco on 01/06/2023.
//

#ifndef CALCULATORSDL_BUTTON_H
#define CALCULATORSDL_BUTTON_H
#include <SDL3/SDL.h>
#define WIDTH 600.0f
#define HEIGHT 400.0f
#define BUTTON_WIDTH (WIDTH / 6.0f)
#define BUTTON_HEIGHT (70)
#define NUM_OF_BUTTONS 18

enum buttonID {
    NUM0,
    NUM1,
    NUM2,
    NUM3,
    NUM4,
    NUM5,
    NUM6,
    NUM7,
    NUM8,
    NUM9,
    POINT,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    EQUALS,
    BACKSPACE,
    DELETE
};

void drawButton(SDL_Window* window, SDL_Renderer* renderer, int ID);
void colorButton(SDL_Window* window, SDL_Renderer* renderer, int ID, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void pressButton(SDL_Window* window, SDL_Renderer* renderer, SDL_Event* ev, int ID, int x, int y);
void getButton(SDL_Window* window, SDL_Renderer* renderer, int ID, int x, int y);
void initFont();
void renderText(SDL_Renderer* renderer);
void initButtons(SDL_Window* window, SDL_Renderer* renderer);
void freeSDL(SDL_Window* window, SDL_Renderer* renderer);

#endif //CALCULATORSDL_BUTTON_H
