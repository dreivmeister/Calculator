#include <stdio.h>
#include <stdlib.h>
struct queue {
    struct token *items;
    int maxsize;
    int front;
    int back;
    int size;
};

struct token {
    char *token;
    char *value;
    char* associativity; //left or right
    int isOperator;
    int precedence;
};

struct queue* newQueue(int size) {
    struct queue* pt = NULL;
    pt = (struct queue*)malloc(sizeof(struct queue));

    pt->items = (struct token*)malloc(sizeof(struct token) * size);
    pt->maxsize = size;
    pt->front = 0;
    pt->back = -1;
    pt->size = 0;

    return pt;
}

int sizeQ(struct queue *pt) {
    return pt->size;
}

int isEmptyQ(struct queue *pt) {
    return !sizeQ(pt);
}

struct token front(struct queue *pt) {
    if(isEmptyQ(pt)) {
        printf("Empty Queue (front)\n");
        return;
    }
    return pt->items[pt->front];
}

void enqueue(struct queue *pt, struct token x) {
    if(sizeQ(pt) == pt->maxsize) {
        printf("Full Queue\n");
        return;
    }
    
    pt->back = (pt->back + 1) % pt->maxsize;
    pt->items[pt->back] = x;
    pt->size++;
}

void dequeue(struct queue *pt) {
    if(isEmptyQ(pt)) {
        printf("Empty Queue (dequeue)\n");
        return;
    }
    pt->front = (pt->front + 1) % pt->maxsize;
    pt->size--;
}

void printQueue(struct queue *pt) {
    for(int i = 0; i < pt->size; i++) {
        printf("%s: %s  ", pt->items[i].token, pt->items[i].value);
    }
}