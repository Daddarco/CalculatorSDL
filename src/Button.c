//
// Created by marco on 01/06/2023.
//

#include "../include/Button.h"
#include "../include/Calculator.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct button {
    SDL_FRect rect;
    bool isPressed;
    bool isHovered;
    int ID;
} Button;

Button button[NUM_OF_BUTTONS];
SDL_FRect textRect[18];

void buttonText(SDL_Window* window, SDL_Renderer* renderer, int ID, SDL_FRect parentButton);

void drawButton(SDL_Renderer* renderer, int ID) {
    if (ID < 10 || ID == POINT) {
        // Grigio scuro
        if (button[ID].isPressed) SDL_SetRenderDrawColor(renderer, 80, 80, 80, SDL_ALPHA_OPAQUE);
        else if (button[ID].isHovered) SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
        else SDL_SetRenderDrawColor(renderer, 60, 60, 60, SDL_ALPHA_OPAQUE);
    } else if (ID == EQUALS) {
        // Verde
        if (button[ID].isPressed) SDL_SetRenderDrawColor(renderer, 30, 130, 70, SDL_ALPHA_OPAQUE);
        else if (button[ID].isHovered) SDL_SetRenderDrawColor(renderer, 46, 204, 113, SDL_ALPHA_OPAQUE);
        else SDL_SetRenderDrawColor(renderer, 39, 174, 96, SDL_ALPHA_OPAQUE);
    } else {
        // Arancione
        if (button[ID].isPressed) SDL_SetRenderDrawColor(renderer, 180, 90, 20, SDL_ALPHA_OPAQUE);
        else if (button[ID].isHovered) SDL_SetRenderDrawColor(renderer, 230, 126, 34, SDL_ALPHA_OPAQUE);
        else SDL_SetRenderDrawColor(renderer, 211, 84, 0, SDL_ALPHA_OPAQUE);
    }

    SDL_RenderFillRect(renderer, &button[ID].rect);

    // Bordo
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, SDL_ALPHA_OPAQUE);
    SDL_RenderRect(renderer, &button[ID].rect);
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

bool pressButton(SDL_Window* window, SDL_Renderer* renderer, SDL_Event* ev, int ID, CalculatorState* state) {
    bool hasToRedraw = false;
    bool isHovering = (ev->motion.x > button[ID].rect.x && ev->motion.x < (button[ID].rect.x + button[ID].rect.w))      // Il cursore è orizzontalmente nel rettangolo
                    && (ev->motion.y > button[ID].rect.y && ev->motion.y < (button[ID].rect.y + button[ID].rect.h));    // AND Il cursore è verticalmente nel rettangolo

    switch (ev->type) {
        case SDL_EVENT_MOUSE_MOTION:
            if (isHovering != button[ID].isHovered) {
                button[ID].isHovered = isHovering;
                if (!isHovering) button[ID].isPressed = false;
                hasToRedraw = true;
            }
        break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (button[ID].isHovered && ev->button.button == SDL_BUTTON_LEFT) {
                button[ID].isPressed = true;
                hasToRedraw = true;
            }
        break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (button[ID].isPressed && ev->button.button == SDL_BUTTON_LEFT) {
                printf("\n\n\n\n\n\n\n\n\n\n\n");
                calculator_process_input(state, button[ID].ID);
                updateText(renderer, state->buffer);
                printf("%s", state->buffer);
                button[ID].isPressed = false;
                hasToRedraw = true;
            }
        break;
    }
    return hasToRedraw;
}

void drawButtonsGraphics(SDL_Renderer* renderer) {
    for (int i = 0; i < NUM_OF_BUTTONS; i++) {
        drawButton(renderer, i);
    }
}

void drawLabels(SDL_Renderer* renderer) {
    SDL_RenderTexture(renderer, display, NULL, &displayRect);
    for (int i = 0; i < NUM_OF_BUTTONS; ++i) {
        if (text[i])
            SDL_RenderTexture(renderer, text[i], NULL, &textRect[i]);
    }
}

void renderText(SDL_Renderer* renderer) {
    drawButtonsGraphics(renderer);
    drawLabels(renderer);
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
            button[firstPart[currentButton]].isHovered = false;
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
        button[secondPart[rowElement]].isHovered = false;
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
    SDL_GetTextureSize(text[ID], &textRect[ID].w, &textRect[ID].h);
    textRect[ID].x = parentButton.x + ((parentButton.w / 2) - (textRect[ID].w / 2));
    textRect[ID].y = parentButton.y + ((parentButton.h / 2) - (textRect[ID].h / 2));
}
