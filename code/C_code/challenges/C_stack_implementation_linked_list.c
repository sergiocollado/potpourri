#include <stdio.h>
#include <stdlib.h>
 
// A Linked List Node
struct Node
{
    int data;               // integer data
    struct Node* next;      // pointer to the next node
};
 
int nodesCount;
 
// Utility function to add an element `x` to the stack
void push(struct Node **top, int x)        // insert at the beginning
{
    // allocate a new node in a heap
    struct Node* node = NULL;
    node = (struct Node*)malloc(sizeof(struct Node));
 
    // check if stack (heap) is full. Then inserting an element would
    // lead to stack overflow
    if (!node)
    {
        printf("Heap Overflow\n");
        exit(-1);
    }
 
    printf("Inserting %d\n", x);
 
    // set data in the allocated node
    node->data = x;
 
    // set the .next pointer of the new node to point to the current
    // top node of the list
    node->next = *top;
 
    // update top pointer
    *top = node;
 
    // increase stack's size by 1
    nodesCount += 1;
}
 
// Utility function to check if the stack is empty or not
int isEmpty(struct Node* top) {
    return top == NULL;
}
 
// Utility function to return the top element of the stack
int peek(struct Node *top)
{
    // check for an empty stack
    if (!isEmpty(top)) {
        return top->data;
    }
    else {
        printf("The stack is empty\n");
        exit(EXIT_FAILURE);
    }
}
 
// Utility function to pop a top element from the stack
int pop(struct Node** top)        // remove at the beginning
{
    struct Node *node;
 
    // check for stack underflow
    if (*top == NULL)
    {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
 
    // take note of the top node's data
    int x = peek(*top);
 
    printf("Removing %d\n", x);
 
    node = *top;
 
    // update the top pointer to point to the next node
    *top = (*top)->next;
 
    // decrease stack's size by 1
    nodesCount -= 1;
 
    // free allocated memory
    free(node);
 
    return x;
}
 
// Utility function to return the nodesCount of the stack
int size() {
    return nodesCount;
}
 
int main(void)
{
    struct Node* top = NULL;
 
    push(&top, 1);
    push(&top, 2);
    push(&top, 3);
 
    printf("The top element is %d\n", peek(top));
 
    pop(&top);
    pop(&top);
    pop(&top);
 
    if (isEmpty(top)) {
        printf("The stack is empty\n");
    }
    else {
        printf("The stack is not empty\n");
    }
 
    return 0;
}

/*
 output: 
 
Inserting 1
Inserting 2
Inserting 3
The top element is 3
Removing 3
Removing 2
Removing 1
The stack is empty
*/

reference: https://www.techiedelight.com/stack-implementation-using-linked-list/