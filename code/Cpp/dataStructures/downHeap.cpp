/*

Please implement the downHeap procedure for
a min heap data structure, which we will represent
as node-based tree for this exercise (not an array).

the min heap property is that each parent node must be 
of lower value that any of its children. to keep it
in the donwHeap() function, in case the parent node 
is bigger than any of its children it will be swapped
with its children of lower value

Suppose you are given a tree where the left and right
subtrees are min heaps, but the root node in particular
might not maintain the min heap property. Your code
should modify the tree rooted at Node* n so it is a
min heap. This means you need to satisfy the min heap
property: it is okay for a node's value to be equal to
one or both of its children, but the node's value must
not be greater than either of its children.

Tips:
This challenge uses an ordinary binary tree with left and right child
pointers. This ordinary binary tree might not be complete
or balanced: any node might have only one child or the
other, or both, or neither. (You do not have to try to
balance the tree or turn it into a complete tree.)

If the root node exists, and if it has a left or right
child, and if one of the children has a smaller value
than the root node, then you should swap the root node
with the smaller child to move the large value down
into the tree. (This may need to be done recursively.)
Be careful to check whether pointers are null before
dereferencing them, as always; that includes using "->"
to access a class member through a pointer. In addition,
you must be careful not to accidentally compare "left"
and "right" pointers directly if you really intend to
compare the stored values "left->value" and "right->value".

Assume that these headers have already been included
for you:

#include <iostream>
#include <string>

You have the following class Node already defined.
You cannot change this class definition, so it is
shown here in a comment for your reference only:

class Node {
public:
  int value;
  Node *left, *right;
  Node(int val = 0) { value = val; left = right = nullptr; }
  ~Node() {
    delete left;
    left = nullptr;
    delete right;
    right = nullptr;
  }
};

This function has also previously been defined for you:

void printTreeVertical(const Node* n);

You can use it to print a verbose, vertical diagram of
a tree rooted at n. In this vertical format, a left child
is shown above a right child in the same column. If no
child exists, [null] is displayed.

*/

// You can also use this compact printing function for debugging.
void printTree(Node *n) {
  if (!n) return;
  std::cout << n->value << "(";
  printTree(n->left);
  std::cout << ")(";
  printTree(n->right);
  std::cout << ")";
}


void downHeap(Node *n) {
  
  // Implement downHeap() here.
  if ( n->left != nullptr && n->right != nullptr)
  {
      if ( n->left->value > n->right->value ) // right is min
      {
          if ( n->value > n->right->value ) // is right is lower that parent?
          {
            int auxValue = n->right->value ;
            n->right->value = n->value;
            n->value = auxValue;
          }
          downHeap(n->right);
      }
      else if ( n->right->value > n->left->value ) // left is min
      {
          if ( n->value > n->left->value ) // left is lower that parent
          {
            int auxValue = n->left->value ;
            n->left->value = n->value;
            n->value = auxValue;
          downHeap(n->left);      //heapifyDown() further
      }
      else {
        // repeated values?? is this possible?? yeah, go for the left one
          if ( n->value > n->left->value ) // left is lower that parent
          {
            int auxValue = n->left->value ;
            n->left->value = n->value;
            n->value = auxValue;
          downHeap(n->left);      //heapifyDown() further
      }

  }
  else if ( n->left != nullptr && n->right == nullptr)  // right is nullptr
  {
          if ( n->value > n->left->value ) // left is lower that parent
          {
            int auxValue = n->left->value ;
            n->left->value = n->value;
            n->value = auxValue;
            downHeap(n->left);      //heapifyDown() further
  }
  else if ( n->right != nullptr && n->left == nullptr) // left is nullptr
  {
          if ( n->value > n->right->value ) // is right is lower that parent?
          {
            int auxValue = n->right->value ;
            n->right->value = n->value;
            n->value = auxValue;
          }
          std::cout << "\n4downHeap(" << n->right << ")"; 
          downHeap(n->right);
  }
  else
  {
     //this is a leaf
  }
}

int main() {
  Node *n = new Node(100);
  n->left = new Node(2);
  n->right = new Node(1);
  n->right->left = new Node(4); 
  n->right->right = new Node(4); 
  n->right->right->right = new Node(5);
  n->right->right->left = new Node(5);

  /*
             100
            /   \
          2       1 
                /  \
               4    4 
                  /  \
                 5    5

  */


  downHeap(n);

  std::cout << "Compact printout:" << std::endl;
  printTree(n);
  std::cout << std::endl << "Vertical printout:" << std::endl;
  //printTreeVertical(n);

  delete n;
  n = nullptr;

  return 0;
}

