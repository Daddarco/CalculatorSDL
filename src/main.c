#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "../assets/Button.h"
#include <stdio.h>
#include <stdlib.h>

void initializeSDL();
SDL_Window* createWindow(char* title);
SDL_Renderer* createRenderer(SDL_Window* window);
void whiteBG(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char** argv) {
    setvbuf(stdout, NULL, _IONBF, 0);
    int x = 0, y = 0;
    printf("Inserisci due numeri con cui fare la somma: ");
    scanf("%d %d", &x, &y);

    initializeSDL();
    if (!TTF_Init()) {
        printf("%s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }
    initFont();

    SDL_Window* window = createWindow("Calcolatrice");
    SDL_Renderer* renderer = createRenderer(window);
    whiteBG(window, renderer);

    initButtons(window, renderer);

    SDL_Event ev;
    int isRunning = true;
    while (isRunning) {
        while ((SDL_PollEvent(&ev)) != 0) {
            if (ev.type == SDL_EVENT_QUIT)
                isRunning = false;

            for (int i = 0; i < NUM_OF_BUTTONS; i++) {
                pressButton(window, renderer, &ev, i, x, y);
            }
            whiteBG(window, renderer);

            renderText(renderer);

            SDL_RenderPresent(renderer);
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
