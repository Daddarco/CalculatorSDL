#include <SDL3/SDL_main.h>
#include "../include/Button.h"
#include "../include/Util.h"
#include "../include/Calculator.h"
#include <stdio.h>
#include <stdlib.h>

void initializeSDL();
SDL_Window* createWindow(char* title);
SDL_Renderer* createRenderer(SDL_Window* window);
void whiteBG(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char** argv) {
    setvbuf(stdout, NULL, _IONBF, 0);

    initializeSDL();
    if (!TTF_Init()) {
        printf("%s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }
    initFont();

    CalculatorState calcState;
    calculator_init(&calcState);

    SDL_Window* window = createWindow("Calcolatrice");
    SDL_Renderer* renderer = createRenderer(window);
    whiteBG(window, renderer);

    initButtons(window, renderer);

    SDL_Event ev;
    int isRunning = true;
    bool needsRedraw = true;
    while (isRunning) {
        if (needsRedraw) {
            whiteBG(window, renderer);
            renderText(renderer);
            SDL_RenderPresent(renderer);
            needsRedraw = false;
        }

        if (SDL_WaitEvent(&ev)) {
            if (ev.type == SDL_EVENT_QUIT)
                isRunning = false;

            for (int i = 0; i < NUM_OF_BUTTONS; i++) {
                if (pressButton(window, renderer, &ev, i, &calcState)) {
                    needsRedraw = true;
                }
            }
        }
    }
    freeSDL(window, renderer);
    return 0;
}

void initializeSDL() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("%s\n", SDL_GetError());
        exit(-1);
    }
}

SDL_Window* createWindow(char* title) {
    SDL_Window* window = SDL_CreateWindow(title, WIDTH, HEIGHT, SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (window == NULL) {
        printf("%s\n", SDL_GetError());
        SDL_Quit();
        exit(-2);
    }
    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        printf("%s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(-3);
    }
    return renderer;
}

void whiteBG(SDL_Window* window, SDL_Renderer* renderer) {
    if (!SDL_SetRenderDrawColor(renderer, 44, 44, 44, SDL_ALPHA_OPAQUE)) {
        printf("%s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(-4);
    }
    SDL_RenderClear(renderer);
}
