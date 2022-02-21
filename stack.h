#pragma once

struct stack {
    int maxsize;
    int top;
    struct token *items;
};

struct stack* newStack(int capacity);
void push(struct stack *pt, struct token x);
struct token peek(struct stack *pt);
struct token pop(struct stack *pt);
int sizeS(struct stack *pt);
int isEmptyS(struct stack *pt);
int isFull(struct stack *pt);