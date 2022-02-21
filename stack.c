#include <stdio.h>
#include <stdlib.h>

struct stack {
    struct token *items;
    int maxsize;
    int top;
};

struct token {
    char *token;
    char *value;
    char* associativity; //left or right
    int isOperator;
    int precedence;
};

struct stack* newStack(int capacity) {
    struct stack *pt = (struct stack*) malloc(sizeof(struct stack));

    pt->maxsize = capacity;
    pt->top = -1;
    pt->items = (struct token*)malloc(sizeof(struct token) * capacity);

    return pt;
}

int sizeS(struct stack *pt) {
    return pt->top + 1;
}

int isEmptyS(struct stack *pt) {
    return pt->top = -1;
}

int isFull(struct stack *pt) {
    return pt->top == pt->maxsize - 1;
}

void push(struct stack *pt, struct token x) {
    if(isFull(pt)) {
        printf("Full\n");
        return;
    }
    printf("Inserting %d\n", x);

    pt->items[++pt->top] = x;
}

struct token peek(struct stack *pt) {
    if(!isEmptyS(pt)) {
        return pt->items[pt->top];
    }
    else {
        printf("Empty\n");
        return;
    }
}

struct token pop(struct stack *pt) {
    if(isEmptyS(pt)) {
        printf("Empty\n");
    }
    printf("Removing %d\n", peek(pt));

    return pt->items[pt->top--];
}

