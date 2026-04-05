#pragma once

#include <stdbool.h>
#include "Common.h"

typedef struct CalculatorState {
    char buffer[15];
    bool isDisplayClear;
} CalculatorState;

void calculator_init(CalculatorState* state);
void calculator_process_input(CalculatorState* state, int buttonID, int x, int y);
