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
    size_t len = strlen(state->buffer);
    
    // Se il display deve essere pulito (dopo un errore o risultato)
    if (state->isDisplayClear) {
        memset(state->buffer, 0, sizeof(state->buffer));
        state->isDisplayClear = false;
        len = 0;
    }

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
            // Regola 1: Il primo carattere può essere un numero o il segno meno
            if (len == 0 && !is_num && next_char != '-') return;

            // Regola 2: Il punto si può mettere solo dopo un numero
            if (next_char == '.' && (len == 0 || !isdigit(state->buffer[len-1]))) return;

            // Regola 3: Massimo un punto per ogni numero
            if (next_char == '.') {
                for (int i = (int)len - 1; i >= 0; i--) {
                    if (is_operator(state->buffer[i])) break;
                    if (state->buffer[i] == '.') return; 
                }
            }

            if (is_operator(next_char) && len > 0 && is_operator(state->buffer[len - 1])) {
                // Se inseriamo un '-' dopo un altro operatore (che non sia già un '-'), lo permettiamo
                if (next_char == '-' && state->buffer[len - 1] != '-') {
                    state->buffer[len] = next_char;
                } else {
                    // Se stiamo sostituendo e c'è una sequenza tipo "*-", dobbiamo rimuovere entrambi
                    if (len > 1 && is_operator(state->buffer[len - 2])) {
                        state->buffer[len - 2] = next_char;
                        state->buffer[len - 1] = '\0';
                    } else {
                        // Impediamo che il primo carattere diventi un operatore diverso da '-'
                        if (len == 1 && next_char != '-') return;
                        state->buffer[len - 1] = next_char;
                    }
                }
            } else {
                state->buffer[len] = next_char;
            }
        }
    }
}

void calculator_evaluate(CalculatorState* state) {
    if (strlen(state->buffer) == 0) return;

    // --- 1. Tokenizzazione ---
    double values[16];
    char ops[16];
    int v_top = -1, o_top = -1;

    // --- 2. Shunting-Yard + RPN simultaneo ---
    // Useremo due stack per calcolare direttamente mentre processiamo
    double num_stack[16];
    char op_stack[16];
    int ns_ptr = -1, os_ptr = -1;

    char* p = state->buffer;
    while (*p) {
        // Un '-' è un segno se è all'inizio o segue un altro operatore
        if ((*p == '-' && (p == state->buffer || is_operator(*(p - 1)))) || isdigit(*p) || *p == '.') {
            double val = strtod(p, &p);
            num_stack[++ns_ptr] = val;
        } else if (is_operator(*p)) {
            while (os_ptr >= 0 && get_precedence(op_stack[os_ptr]) >= get_precedence(*p)) {
                // Esegui l'operazione in cima allo stack
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

    // Risolvi le operazioni rimanenti
    while (os_ptr >= 0) {
        double b = num_stack[ns_ptr--];
        double a = num_stack[ns_ptr--];
        char op = op_stack[os_ptr--];
        if (op == '+') num_stack[++ns_ptr] = a + b;
        if (op == '-') num_stack[++ns_ptr] = a - b;
        if (op == '*') num_stack[++ns_ptr] = a * b;
        if (op == '/') num_stack[++ns_ptr] = (b != 0) ? a / b : 0;
    }

    if (ns_ptr == 0) {
        double res = num_stack[0];
        snprintf(state->buffer, sizeof(state->buffer), "%g", res);
    } else {
        strcpy(state->buffer, "Error");
    }
}
