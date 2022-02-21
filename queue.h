#pragma once

struct queue {
    struct token *items;
    int maxsize;
    int front;
    int back;
    int size;
};

struct queue* newQueue(int size);
void enqueue(struct queue *pt, struct token x);
void dequeue(struct queue *pt);
int sizeQ(struct queue *pt);
int isEmptyQ(struct queue *pt);
struct token front(struct queue *pt);
void printQueue(struct queue *pt);