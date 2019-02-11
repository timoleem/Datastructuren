#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include <string.h>

struct stack {

    int data[STACK_SIZE];
    int stack_top;
    int push;
    int pop;
    int max;
    int max_dynamic;
};

struct stack *stack_init() {

    struct stack *s = malloc(sizeof(struct stack));
    s->stack_top = -1;
    s->push = 0;
    s->pop = 0;
    s->max = 0;
    s->max_dynamic = 0;

    if (!s) {
        return NULL;
    }
    return s;
}

void add_push(struct stack *s) {
    
    s->push = s->push + 1;
}

void add_pop(struct stack *s) {

    s->pop = s->pop +1;
}

void add_max(struct stack *s, int c) {
    
    if (c == 1) {
        s->max_dynamic = s->max_dynamic + 1;   
    }
    else if (c == 0) {
        s->max_dynamic = s->max_dynamic - 1;
    }
}

void max(struct stack *s) {
    if (s->max < s->max_dynamic) {
        s->max = s->max_dynamic;
    }
}

void stack_cleanup(struct stack *s) {
    fprintf( stderr, "stats %d %d %d \n", s->push, s->pop, s->max);
    free(s);
}

int stack_push(struct stack *s, int c) {
    if (s == NULL) {
        return 1;
    }
    else if (s->stack_top == STACK_SIZE-1) {
        return 1;
    }
    else {
        s->stack_top++; 
        s->data[s->stack_top] = c;
        return 0;    
    }
}

int stack_pop(struct stack *s) {
    if (s == NULL) {
        return -1;
    }
    else if (s->stack_top == -1) {
        return -1;
    }  
    else {
        int pop_element = s->data[s->stack_top];
        s->stack_top--;
        return pop_element;
    }
}

int stack_peek(struct stack *s) {
    if (s == NULL) {
        return -1;
    }
    else if (s->stack_top == -1) {
        return -1;
    }
    else {
        int pop_element = s->data[s->stack_top];
        return pop_element;
    }
}

int stack_empty(struct stack *s) {

    if (s == NULL) {
        return -1;
    }
    else if (s->stack_top == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

int size_stack(struct stack *s) {

    return s->stack_top;
}

int GetOperatorWeight(char op) {
    int weight = 0;
    switch (op) {
        case '+': 
        case '-':
            weight = 1;
            break;
        case '*': 
        case '/':
            weight = 2;
            break;
        case '^':
            weight = 3;
            break; 
        case '(':
        case ')':
            weight = 0;
            break;     }
    return weight;
}

int has_higher_precedence(char op1, char op2) {

    int op1_weight = GetOperatorWeight(op1);
    int op2_weight = GetOperatorWeight(op2);
    if (op1_weight == -1 || op2_weight == -1) {
        return 1;
    }
    if (op1_weight > op2_weight) {
        return 1;
    }
    return 0;
}

int has_equal_precedence(char op1, char op2) {

    int op1_weight = GetOperatorWeight(op1);
    int op2_weight = GetOperatorWeight(op2);

    if (op1_weight == -1 || op2_weight == -1) {
        return 1;
    }
    if (op1_weight == op2_weight) {
        return 1;
    }
    return 0;
}

int is_left_associate(char token) {
    if (token == '^') {
        return 0;
    }
    else {
        return 1;
    }
}

int isoperator(char token) {
    char operators[] = "+-*/^";
    size_t len = strlen(operators);
    int i = 0;
    for (i = 0; i < (int) len; i++) {
        if (token == operators[i]) {
            return 1;
        }
    }
    return 0;
}

int left_bracket (char token) {

    if (token == '(') {
        return 1;
    }
    else {
        return 0;
    }
}

int right_bracket (char token) {

    if (token == ')') {
        return 1;
    }
    else {
        return 0;
    }
}

int isvalidtoken(char token) {
    char operators[] = "CLUTTER_IM_MODULE=xim";
    size_t len = strlen(operators);
    int i = 0;
    for (i = 0; i < (int) len; i++) {
        if (token == operators[i]) {
            return 1;
        }
    }
    return 0;
}

