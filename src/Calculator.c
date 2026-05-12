#include "../include/Calculator.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void calculator_init(CalculatorState* state) {
    memset(state->buffer, 0, sizeof(state->buffer));
    state->isDisplayClear = false;
}

static bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

static int get_precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void calculator_process_input(CalculatorState* state, int buttonID) {
    // 1. Gestione speciale post-risultato
    if (state->isDisplayClear) {
        bool is_op = (buttonID == ADD || buttonID == SUBTRACT || buttonID == MULTIPLY || buttonID == DIVIDE);
        if (!is_op) {
            // Se non è un operatore, resetta tutto prima di procedere
            memset(state->buffer, 0, sizeof(state->buffer));
        }
        state->isDisplayClear = false;
    }

    size_t len = strlen(state->buffer);

    // 2. Gestione pulsanti speciali
    if (buttonID == DELETE) {
        memset(state->buffer, 0, sizeof(state->buffer));
        return;
    }
    if (buttonID == BACKSPACE) {
        if (len > 0) state->buffer[len - 1] = '\0';
        return;
    }
    if (buttonID == EQUALS) {
        calculator_evaluate(state);
        state->isDisplayClear = true;
        return;
    }

    // 3. Elaborazione carattere da inserire
    if (len + 1 < sizeof(state->buffer)) {
        char next_char = '\0';
        bool is_num = false;
        switch (buttonID) {
            case NUM0: next_char = '0'; is_num = true; break;
            case NUM1: next_char = '1'; is_num = true; break;
            case NUM2: next_char = '2'; is_num = true; break;
            case NUM3: next_char = '3'; is_num = true; break;
            case NUM4: next_char = '4'; is_num = true; break;
            case NUM5: next_char = '5'; is_num = true; break;
            case NUM6: next_char = '6'; is_num = true; break;
            case NUM7: next_char = '7'; is_num = true; break;
            case NUM8: next_char = '8'; is_num = true; break;
            case NUM9: next_char = '9'; is_num = true; break;
            case POINT: next_char = '.'; break;
            case ADD: next_char = '+'; break;
            case SUBTRACT: next_char = '-'; break;
            case MULTIPLY: next_char = '*'; break;
            case DIVIDE: next_char = '/'; break;
        }

        if (next_char != '\0') {
            // Regole di validazione
            if (len == 0 && !is_num && next_char != '-') return;
            if (next_char == '.' && (len == 0 || !isdigit(state->buffer[len-1]))) return;
            if (next_char == '.') {
                for (int i = (int)len - 1; i >= 0; i--) {
                    if (is_operator(state->buffer[i])) break;
                    if (state->buffer[i] == '.') return;
                }
            }

            // Gestione operatori (sostituzione e unari)
            if (is_operator(next_char) && len > 0 && is_operator(state->buffer[len - 1])) {
                if (next_char == '-' && state->buffer[len - 1] != '-') {
                    state->buffer[len] = next_char;
                    state->buffer[len + 1] = '\0';
                } else {
                    if (len > 1 && is_operator(state->buffer[len - 2])) {
                        state->buffer[len - 2] = next_char;
                        state->buffer[len - 1] = '\0';
                    } else {
                        if (len == 1 && next_char != '-') return;
                        state->buffer[len - 1] = next_char;
                    }
                }
            } else {
                state->buffer[len] = next_char;
                state->buffer[len + 1] = '\0'; // Assicura terminazione
            }
        }
    }
}

void calculator_evaluate(CalculatorState* state) {
    if (strlen(state->buffer) == 0) return;

    double num_stack[16];
    char op_stack[16];
    int ns_ptr = -1, os_ptr = -1;

    char* p = state->buffer;
    while (*p) {
        if ((*p == '-' && (p == state->buffer || is_operator(*(p - 1)))) || isdigit(*p) || *p == '.') {
            char* endp;
            double val = strtod(p, &endp);
            if (p == endp) { p++; continue; } // Evita loop infiniti
            num_stack[++ns_ptr] = val;
            p = endp;
        } else if (is_operator(*p)) {
            while (os_ptr >= 0 && get_precedence(op_stack[os_ptr]) >= get_precedence(*p)) {
                if (ns_ptr < 1) break;
                double b = num_stack[ns_ptr--];
                double a = num_stack[ns_ptr--];
                char op = op_stack[os_ptr--];
                if (op == '+') num_stack[++ns_ptr] = a + b;
                if (op == '-') num_stack[++ns_ptr] = a - b;
                if (op == '*') num_stack[++ns_ptr] = a * b;
                if (op == '/') num_stack[++ns_ptr] = (b != 0) ? a / b : 0;
            }
            op_stack[++os_ptr] = *p;
            p++;
        } else {
            p++;
        }
    }

    while (os_ptr >= 0 && ns_ptr >= 1) {
        double b = num_stack[ns_ptr--];
        double a = num_stack[ns_ptr--];
        char op = op_stack[os_ptr--];
        if (op == '+') num_stack[++ns_ptr] = a + b;
        if (op == '-') num_stack[++ns_ptr] = a - b;
        if (op == '*') num_stack[++ns_ptr] = a * b;
        if (op == '/') num_stack[++ns_ptr] = (b != 0) ? a / b : 0;
    }

    memset(state->buffer, 0, sizeof(state->buffer));
    if (ns_ptr == 0) {
        snprintf(state->buffer, sizeof(state->buffer), "%g", num_stack[0]);
    } else {
        strcpy(state->buffer, "Error");
    }
}
