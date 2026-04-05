#include "../include/Calculator.h"
#include <string.h>
#include <stdio.h>

void calculator_init(CalculatorState* state) {
    memset(state->buffer, 0, sizeof(state->buffer));
    state->isDisplayClear = false;
}

void calculator_process_input(CalculatorState* state, int buttonID, int x, int y) {
    if (!state->isDisplayClear) {
        memset(state->buffer, 0, sizeof(state->buffer));
        state->isDisplayClear = true;
    }

    size_t len = strlen(state->buffer);
    switch (buttonID) {
        case NUM0: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "0"); break;
        case NUM1: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "1"); break;
        case NUM2: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "2"); break;
        case NUM3: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "3"); break;
        case NUM4: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "4"); break;
        case NUM5: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "5"); break;
        case NUM6: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "6"); break;
        case NUM7: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "7"); break;
        case NUM8: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "8"); break;
        case NUM9: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "9"); break;
        case POINT: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "."); break;
        case ADD: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "+"); break;
        case SUBTRACT: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "-"); break;
        case MULTIPLY: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "*"); break;
        case DIVIDE: if (len + 1 < sizeof(state->buffer)) strcat(state->buffer, "/"); break;
        case BACKSPACE:
            if (len > 0) state->buffer[len - 1] = '\0';
            break;
        case DELETE:
            memset(state->buffer, 0, sizeof(state->buffer));
            break;
        case EQUALS:
            printf("La somma e': %d\n", x + y);
            break;
        default: break;
    }
}
