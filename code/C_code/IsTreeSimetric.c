#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Given a binary tree, implement a function which checks if it is symmetric or not.
//       3
//      / \
//      1 1 -> Symmetric
//    / \ / \
//    3 5 5 3
//      \ /
//      5 5

struct node {
    struct node* right;
    struct node* left;
    int data;
};

bool areRightAndLeftEqual (struct node *mynoderight, struct node *mynodeleft) {
    
    if ( mynoderight->right != NULL && mynodeleft->left != NULL) {
        
        if (mynoderight->data == mynodeleft->data) {
             printf("mynoderigth data: %d \t mynodeleft data: %d\n", mynoderight->data, mynodeleft->data);
             //      1 -> mynoderight
             //    / \
             //    3 5 
             return areRightAndLeftEqual( mynoderight->right, mynodeleft->left)
                  && areRightAndLeftEqual( mynoderight->left, mynodeleft->right);
        }
        
        //areRightAndLeftEqual(n);
    }
   
     if ( mynoderight->right == NULL || mynodeleft->left == NULL) {
            return (mynoderight->data == mynodeleft->data);
     }
     
    return false;
}

int main() {
    
    struct node node3l = { NULL, NULL, 2};
    struct node node3r = { NULL, NULL, 2};
    struct node node2l = { NULL, NULL, 2};
    struct node node2r = { NULL, NULL, 2};
    struct node node3 = { &node3r, &node3l, 1};
    struct node node2 = { &node2r, &node2l, 1};
    struct node node1 = { &node1, &node2, 0};
    
    //    0
    //   / \
    //   1  1 
    
    if( areRightAndLeftEqual( &node2, &node3) == true) printf("the tree is equal\n");
    
    //return 0;
}
