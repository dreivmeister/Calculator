#include <stdio.h>
#include<stdlib.h>
 
#define MAXOP 100
#define MAXTOKEN 100
#define NUMBER '0'
//SOURCE: https://cboard.cprogramming.com/c-programming/141496-k-r-reverse-polish-calculator.html
struct token {
    //General
    char *token;
    double value;
    
    //Helpers (maybe)
    int isOperator;
    int isFunction;
    int isNumber;

    //only Operators
    char* associativity; //left or right or both
    int precedence; // relative scale
};

//possible inputs
/*
NUM - 1,-2,3.2,-2.3
+
-
*
/
(
)
*/

/**/

/* function prototypes */
int getop(char []);
void push(double);
double pop(void);
 
/* reverse Polish calculator */
int main()
{
    int type;
    int currElem;
    double op2;
    char s[MAXOP];
    struct token tokens[MAXTOKEN];
    
    currElem = 0;
    while ((type = getop(s)) != '\n') {
        switch(type) {
        case NUMBER:
            tokens[currElem].token = "NUM";
            tokens[currElem].value = atof(s);
            tokens[currElem].isNumber = 1;
            break;
        case '+':
            tokens[currElem].token = "ADD";
            tokens[currElem].isOperator = 1;
            break;
        case '*':
            tokens[currElem].token = "MUL";
            tokens[currElem].isOperator = 1;
            break;
        case '-':
            tokens[currElem].token = "SUB";
            tokens[currElem].isOperator = 1;
            break;
        case '/':
            tokens[currElem].token = "DIV";
            tokens[currElem].isOperator = 1;
            break;
        case '(':
            tokens[currElem].token = "LP";
            tokens[currElem].isOperator = 1;
            break;
        case ')':
            tokens[currElem].token = "RP";
            tokens[currElem].isOperator = 1;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
        currElem++;
    }

    for(int i = 0; i < currElem; i++) {
        printf("%s %f\n", tokens[i].token, tokens[i].value);
    }
    return 0;
}
 
#define MAXVAL 100  /* maximum depth of val stack */
 
int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */
 
/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}
 
/*pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
        printf("error: stack empty\n");
    return 0.0;
}
 
#include <ctype.h>
 
int getch(void);
void ungetch(int);
 
/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    /* support for negative numbers
    
    if there is a '-' character followed by digit
    then treat this as a negative number. assumption
    is that all operands and operators are separated by
    whitespace(s)
    */
    i = 0;
    if (c == '-' && !isdigit(s[++i] = c = getch())) {
        ungetch(c);
        c = s[0];
    }

    if (!isdigit(c) && c != '.')
        return c;

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}
 
#define BUFSIZE 100
 
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;
/* getch: the function which actually gets chars! */
int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
 
void ungetch(int c) /* push character back in input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

