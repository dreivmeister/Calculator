#pragma once
#include "queue.h"
struct parser {
    struct queue* input;
    struct queue* output;
    struct stack* st;
};

struct parser* newParser(struct queue* input, int size, int cap);
int precedence(struct token o1, struct token o2);
int associativity(struct token o);
void shuntingyard(struct parser* pa);