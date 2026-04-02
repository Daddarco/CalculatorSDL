//
// Created by marco on 01/06/2023.
//

#include "Button.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct button {
    SDL_FRect rect;
    bool isPressed;
    int ID;
} Button;

SDL_Color black = {0, 0, 0, SDL_ALPHA_OPAQUE};
SDL_Color white = {244, 244, 244, SDL_ALPHA_OPAQUE};

Button button[NUM_OF_BUTTONS];
TTF_Font* font;
TTF_Font* buttonFont;
SDL_Texture* text[18];
SDL_Texture* display;
SDL_FRect textRect[18];
SDL_FRect displayRect;
char buffer[11];
bool isDisplayClear = false;

void updateText(SDL_Window* window, SDL_Renderer* renderer);
void buttonText(SDL_Window* window, SDL_Renderer* renderer, int ID, SDL_FRect parentButton);

void drawButton(SDL_Window* window, SDL_Renderer* renderer, int ID) {
    if (!SDL_RenderRect(renderer, &button[ID].rect)) {
        printf("%s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(-5);
    }
}

void colorButton(SDL_Window* window, SDL_Renderer* renderer, int ID, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    if (!SDL_SetRenderDrawColor(renderer, r, g, b, a)) {
        printf("%s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(-6);
    }
    if (!SDL_RenderFillRect(renderer, &button[ID].rect)) {
        printf("%s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(-7);
    }
}

void pressButton(SDL_Window* window, SDL_Renderer* renderer, SDL_Event* ev, int ID, int x, int y) {
    if (ev->type == SDL_EVENT_MOUSE_BUTTON_DOWN && ev->button.button == SDL_BUTTON_LEFT) {                          // Clicchi un tasto del mouse AND Il tasto cliccato è il sinistro
        if ((ev->button.x > button[ID].rect.x && ev->button.x < (button[ID].rect.x + button[ID].rect.w))    // Il cursore è orizzontalmente nel rettangolo
        && (ev->button.y > button[ID].rect.y && ev->button.y < (button[ID].rect.y + button[ID].rect.h)))    // AND Il cursore è verticalmente nel rettangolo
            button[ID].isPressed = true;                                                                // Il bottone è nello stato "premuto"
    }
    else if (button[ID].isPressed == true) {                                                            // Il bottone è nello stato "premuto"
        if (ev->type == SDL_EVENT_MOUSE_MOTION) {
            if (!(ev->motion.x > button[ID].rect.x && ev->motion.x < (button[ID].rect.x + button[ID].rect.w))   // Il cursore è orizzontalmente fuori dal rettangolo
            || !(ev->motion.y > button[ID].rect.y && ev->motion.y < (button[ID].rect.y + button[ID].rect.h)))   // AND Il cursore è verticalmente fuori dal rettangolo
                button[ID].isPressed = false;                                                               // Il bottone è nello stato "non premuto"
        }
        else if (ev->type == SDL_EVENT_MOUSE_BUTTON_UP && ev->button.button == SDL_BUTTON_LEFT) {                   // Il cursore è nel rettangolo e rilasci il tasto sinistro del mouse
            //printf("\e[1;1H\e[2J");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
            getButton(window, renderer, button[ID].ID, x, y);
            printf("%s", buffer);
            button[ID].isPressed = false;                                                               // Il bottone è nello stato "non premuto"
        }
    }
}

void getButton(SDL_Window* window, SDL_Renderer* renderer, int ID, int x, int y) {
    if (isDisplayClear != true) {
        memset(buffer, 0, sizeof(buffer));
        isDisplayClear = true;
    }
    if ((strlen(buffer) + 1) != sizeof(buffer))
        switch (ID) {
            case NUM0:
                strcat(buffer, "0");
                updateText(window, renderer);
                break;
            case NUM1:
                strcat(buffer, "1");
                updateText(window, renderer);
                break;
            case NUM2:
                strcat(buffer, "2");
                updateText(window, renderer);
                break;
            case NUM3:
                strcat(buffer, "3");
                updateText(window, renderer);
                break;
            case NUM4:
                strcat(buffer, "4");
                updateText(window, renderer);
                break;
            case NUM5:
                strcat(buffer, "5");
                updateText(window, renderer);
                break;
            case NUM6:
                strcat(buffer, "6");
                updateText(window, renderer);
                break;
            case NUM7:
                strcat(buffer, "7");
                updateText(window, renderer);
                break;
            case NUM8:
                strcat(buffer, "8");
                updateText(window, renderer);
                break;
            case NUM9:
                strcat(buffer, "9");
                updateText(window, renderer);
                break;
            case POINT:
                strcat(buffer, ".");
                updateText(window, renderer);
                break;
            case ADD:
                strcat(buffer, "+");
                updateText(window, renderer);
                break;
            case SUBTRACT:
                strcat(buffer, "-");
                updateText(window, renderer);
                break;
            case MULTIPLY:
                strcat(buffer, "*");
                updateText(window, renderer);
                break;
            case DIVIDE:
                strcat(buffer, "/");
                updateText(window, renderer);
                break;
            case BACKSPACE:
                if(strlen(buffer) > 0) {
                    buffer[strlen(buffer) - 1] = '\0';
                    updateText(window, renderer);
                }
                break;
            case DELETE:
                memset(buffer, 0, sizeof(buffer));
                updateText(window, renderer);
                break;
            default:
                break;
        }
    if (ID == EQUALS)
        printf("La somma e': %d\n", x + y);
    else return;
}

void initFont() {
    font = TTF_OpenFont("fonts/Roboto-Regular.ttf", 68);
    if (font == NULL) {
        printf("%s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
    }
    buttonFont = TTF_OpenFont("fonts/Roboto-Regular.ttf", 24);
    if (buttonFont == NULL) {
        printf("%s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
    }
}

void renderText(SDL_Renderer* renderer) {
    for (int i = 0; i < NUM_OF_BUTTONS; i++) {
        if (i < 10) SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        else if (i == EQUALS) SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
        else SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);

        SDL_RenderFillRect(renderer, &button[i].rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderRect(renderer, &button[i].rect);
    }

    SDL_RenderTexture(renderer, display, NULL, &displayRect);
    for (int i = 0; i < NUM_OF_BUTTONS; ++i) {
        if (text[i])
            SDL_RenderTexture(renderer, text[i], NULL, &textRect[i]);
    }
}

void updateText(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_Surface* textSurface = TTF_RenderText_LCD(font, buffer, 0, black, white);
    display = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
    displayRect.x = displayRect.y = 0;
    SDL_GetTextureSize(display, &displayRect.w, &displayRect.h);
}

void initButtons(SDL_Window* window, SDL_Renderer* renderer) {
    int firstPart[] = {NUM7, NUM8, NUM9, BACKSPACE, DELETE, NUM4, NUM5, NUM6, ADD, MULTIPLY, NUM1, NUM2, NUM3, SUBTRACT, DIVIDE};
    int secondPart[] = {NUM0, POINT, EQUALS};
    const int displayPadding = 80;
    const int hPadding = 12;
    const int vPadding = 8;

    for (int vPad = vPadding, currentButton = 0, columnElement = 0; columnElement < 3; columnElement++) {
        for (int hPad = hPadding, rowElement = 0; rowElement < 5 ; rowElement++) {
            if (rowElement == 3)
                hPad += 28;
            currentButton = columnElement * 5 + rowElement;
            button[firstPart[currentButton]].rect.x = (BUTTON_WIDTH) * rowElement + hPad;
            button[firstPart[currentButton]].rect.y = (BUTTON_HEIGHT) * columnElement + displayPadding + vPad;
            button[firstPart[currentButton]].rect.w = (BUTTON_WIDTH);
            button[firstPart[currentButton]].rect.h = (BUTTON_HEIGHT);
            button[firstPart[currentButton]].isPressed = false;
            button[firstPart[currentButton]].ID = firstPart[currentButton];
            buttonText(window, renderer, firstPart[currentButton], button[firstPart[currentButton]].rect);
            hPad += 12;
        }
        vPad += 8;
    }

    int equalButtonModifier = 0;
    for (int hPad = hPadding, rowElement = 0; rowElement < 3 ; rowElement++) {
        if (rowElement == 2) {
            hPad += 28;
            equalButtonModifier = BUTTON_WIDTH + hPadding;
        }
        button[secondPart[rowElement]].rect.x = (BUTTON_WIDTH) * (rowElement + 1) + hPad + hPadding;
        button[secondPart[rowElement]].rect.y = (BUTTON_HEIGHT) * 3 + displayPadding + vPadding * 4;
        button[secondPart[rowElement]].rect.w = (BUTTON_WIDTH) + equalButtonModifier;
        button[secondPart[rowElement]].rect.h = (BUTTON_HEIGHT);
        button[secondPart[rowElement]].isPressed = false;
        button[secondPart[rowElement]].ID = secondPart[rowElement];
        buttonText(window, renderer, secondPart[rowElement], button[secondPart[rowElement]].rect);
        hPad += 12;
    }
}

void buttonText(SDL_Window* window, SDL_Renderer* renderer, int ID, SDL_FRect parentButton) {
    char glyph[3];
    memset(glyph, 0, sizeof(glyph));
    switch (ID)  {
        case NUM0:
            strcpy(glyph, "0");
            break;
        case NUM1:
            strcpy(glyph, "1");
            break;
        case NUM2:
            strcpy(glyph, "2");
            break;
        case NUM3:
            strcpy(glyph, "3");
            break;
        case NUM4:
            strcpy(glyph, "4");
            break;
        case NUM5:
            strcpy(glyph, "5");
            break;
        case NUM6:
            strcpy(glyph, "6");
            break;
        case NUM7:
            strcpy(glyph, "7");
            break;
        case NUM8:
            strcpy(glyph, "8");
            break;
        case NUM9:
            strcpy(glyph, "9");
            break;
        case POINT:
            strcpy(glyph, ".");
            break;
        case ADD:
            strcpy(glyph, "+");
            break;
        case SUBTRACT:
            strcpy(glyph, "-");
            break;
        case MULTIPLY:
            strcpy(glyph, "*");
            break;
        case DIVIDE:
            strcpy(glyph, "/");
            break;
        case EQUALS:
            strcpy(glyph, "=");
            break;
        case BACKSPACE:
            strcpy(glyph, "<-");
            break;
        case DELETE:
            strcpy(glyph, "CE");
            break;
        default:
            break;
    }
    SDL_Surface* textSurface = TTF_RenderText_LCD(buttonFont, glyph, 0, black, white);
    text[ID] = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
    textRect[ID].x = parentButton.x + ((parentButton.w / 5) * 2);
    textRect[ID].y = parentButton.y + (parentButton.h / 6);
    SDL_GetTextureSize(text[ID], &textRect[ID].w, &textRect[ID].h);
}

void freeSDL(SDL_Window* window, SDL_Renderer* renderer) {
    TTF_CloseFont(font);
    TTF_CloseFont(buttonFont);
    SDL_DestroyTexture(display);
    for (int i = 0; i < NUM_OF_BUTTONS; ++i) {
        if (text[i]) SDL_DestroyTexture(text[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
