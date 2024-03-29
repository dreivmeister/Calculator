#include "stack.h"
#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct parser {
    struct stack* input;
    struct queue* output;
    struct stack* st;
};

struct token {
    char *token;
    char *value;
    char* associativity; //left or right
    int isOperator;
    int isFunction;
    int isNumber;
    int precedence;
};


struct parser* newParser(struct stack* inp, int size, int cap) {
    struct parser* pa = (struct parser*) malloc(sizeof(struct parser));

    pa->st = newStack(cap);
    pa->input = newStack(size);
    pa->output = newQueue(size);
    pa->input = inp;
    
    return pa;
}

int precedence(struct token o1, struct token o2) {
    if(o1.precedence > o2.precedence) {
        return 1;
    }
    else if(o1.precedence > o2.precedence) {
        return -1;
    }
    return 0;
}

int associativity(struct token o) {
    if(strcmp(o.associativity, "left") == 0) {
        return 1;
    }
    return -1;
}




void shuntingyard(struct parser* pa) {
    int numelem = sizeS(pa->input);
    int currIndex = 0;
    while(currIndex < numelem) {
        struct token currToken = pop(pa->input);
        
        if(currToken.isNumber) {
            enqueue(pa->output, currToken);
        }
        else if(currToken.isFunction) {
            push(pa->st, currToken);
        }
        else if(currToken.isOperator) { //o1
            struct token topst = peek(pa->st); //o2
            while(strcmp(")", topst.value) != 0  && (precedence(topst, currToken) > 0 || 
                 (precedence(topst, currToken) == 0 && associativity(currToken) < 0))) {
                     enqueue(pa->output, topst);
                     pop(pa->st);
            }
            enqueue(pa->output, currToken);
        }
        else if(strcmp(")", currToken.value) == 0) {
            enqueue(pa->output, currToken);
        }
        else if(strcmp("(", currToken.value) == 0) {
            struct token topst = peek(pa->st); //top operator stack (o2)
            while(strcmp(")", topst.value) != 0) {
                if(isEmptyS(pa->st)) {
                    printf("Error: Mismatched Parentheses.\n");
                    return;
                }
                enqueue(pa->output, topst);
                pop(pa->st);
            }
            if(strcmp(")", topst.value) == 0) {
                pop(pa->st);
            }
            if(peek(pa->st).isFunction) {
                enqueue(pa->output, topst);
                pop(pa->st);
            }

        }
        currIndex++;
    }
    while(!isEmptyS(pa->st)) {
        struct token topst = peek(pa->st);
        if(strcmp(")", topst.value) == 0) {
            printf("Error: Mismatched Parentheses.\n");
            return;
        }
        enqueue(pa->output, topst);
        pop(pa->st);
    }
}





