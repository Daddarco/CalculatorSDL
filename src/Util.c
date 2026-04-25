//
// Created by marco on 02/04/2026.
//

#include "../include/Util.h"
#include <stdio.h>

SDL_Texture* display = NULL;
SDL_FRect displayRect = {0, 0, 0, 0};
SDL_Texture* text[18] = {0};
TTF_Font* buttonFont = NULL;

SDL_Color black = {0, 0, 0, SDL_ALPHA_OPAQUE};
SDL_Color white = {244, 244, 244, SDL_ALPHA_OPAQUE};

static TTF_Font* font = NULL;

void initFont() {
    font = TTF_OpenFont("fonts/Roboto-Regular.ttf", 68);
    if (font == NULL) {
        printf("%s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
    }
    buttonFont = TTF_OpenFont("fonts/Roboto-Regular.ttf", 48);
    if (buttonFont == NULL) {
        printf("%s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
    }
}

void updateText(SDL_Renderer* renderer, const char* buffer) {
    if (buffer == NULL || strlen(buffer) < 0) return;
    SDL_Surface* textSurface = TTF_RenderText_LCD(font, buffer, 0, black, white);
    if (display) SDL_DestroyTexture(display);
    display = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
    displayRect.x = displayRect.y = 0;
    SDL_GetTextureSize(display, &displayRect.w, &displayRect.h);
}

void freeSDL(SDL_Window* window, SDL_Renderer* renderer) {
    if (font) TTF_CloseFont(font);
    if (buttonFont) TTF_CloseFont(buttonFont);
    if (display) SDL_DestroyTexture(display);
    for (int i = 0; i < NUM_OF_BUTTONS; ++i) {
        if (text[i]) SDL_DestroyTexture(text[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
