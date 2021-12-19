# NOTES ON DATA STRUCTURES IN C++

## Lineal structures


### ARRAY

Arrays is a data structure which is a collection of elements of the same type and which is stored in contiguous memory. 

An array can be coded like:  (NOTE: actually this is the C style, c++ would use std::array ) 

```
 int values[10] = { 2, 3, 5, 7, 11, 13, 15, 17, 21, 23}; 
```

Well in C++ you can also use the std::array type. 

the elements are 0-indexed (the index count starts in 0)

 - The elements of the array must all be of the same type. 
 - The size of the array is known, as the size of the array is known, and the size of its elementen is kwnown. 
 - Arrays have a FIXED capacity
 - Arrays store its data sequencially in memory
 - The capacity of the array is the maximum number of elemenes that can be stored. 
 - The size of the array is the number of elements stored in the array. 
 - An array is full, when it size is equal to its capacity. 
 - to have a bigger array the only option is to allocate a new bigger array and copy over all the data. 

```
           +----+----+----+----+----+----+----+----+----+----+
           |    |    |    |    |    |    |    |    |    |    |
           |    |    |    |    |    |    |    |    |    |    |
           +----+----+----+----+----+----+----+----+----+----+

```

### Vector

An std::vector implements an array that can dinamically grow in size automatically, with the following propierties:

ref: https://en.cppreference.com/w/cpp/container/vector

- all elements are of the same type.
- at any given point the array has a fixed capacity
- the vector must be expanded when the capacity is reached.
- Each time the capacity is reaches and an increas size is requested, it is expected to double the capacity.!!!


### Linked memory/lists

- Linked memory stores data together with a link (pointer) to the location in memory of the next memory node. 
- In C++ the linked list will have data, and a sequencial list of memory pointers
 
 ```c++
 template <typename T>
 class ListNode (
     public: 
	 T & data;
	 ListNode *next;
	 ListNode(T & data) : data(data), next(nullptr) {} //simple constructor
 }
 ```
- There are two special pointers a "head_" pointer that will point the begining of tle linked list, and a "nullptr" that will mark the end of the list.

```c++
 template <typename T>
 class List {
     public: 
	 const T & operator[](unsigned index);
	 void insertAtFront(const & data);
	 
	 private: 
	 ListNode *head_; //head pointer of the List
 };
```

```
           +-----+--+    +-----+--+    +-----+--+    +-----+--+
           |     |  |    |     |  |    |     |  |    |     |  |
head__ ---->     |  +--->|     |  +--->|     |  +--->|     |  +-----> nullptr
           |     |  |    |     |  |    |     |  |    |     |  |
           +-----+--+    +-----+--+    +-----+--+    +-----+--+

```
the brackets operator can be edited to point a given element:

```c++
template <typename>
const T & List<T>::operator[](unsigned index) {
    ListNode *thru = head_;
	while (index > 0 && thru->next != nullptr) {
	   thru = thru->next;  //go to the next element
	   --index;
    }
	return thru->data;
```

Comparing with the Array, we can see to move through the list, it will take longer.
In the array, if we want to go to the 'nth' element, we only need to go to the 'nth' position.
(due to the array is stored in a continous memory). In a list, it is not possible do it in one
operation, to go to the 'nth' element, we need to go throug 'n' pointers, to retrieve it. 

If we want to insert an element, we only need to point correctly the next pointers.

```c++
template <typename T>
void List<T>::instertAtFront(const T & data) {
   ListNode *node = new ListNode(data); //create new node on the heap
   node->next = head_; //point tthe next pointer to the first element
   head_ = node;       //point the head_ pointer to this element.
}
```
In contrast, and array had limited capacity, and no more elements could be added to it. List don't have 
data limitation.


reference: https://en.cppreference.com/w/cpp/container/forward_list

reference: https://en.cppreference.com/w/cpp/container/list
	  
### run time analisys between arrays and linked lists

#### access a given index

In an array to go to the nth position, we only need move to  n*sizeof(element) into the memory. That is 1 operation.
It is O(1) aka constant time.

In a linked list, to go to the nth element, it is necesary to go throught n element's pointer to get 
to the nth element. That are n operations. That is O(n), aka linear time, time needed is lineal to the size of the list.

#### resize of the arrays and lists

To resize an array, we have to copy it over to a chunck of memory with bigger capacity. 
If every time an array need to increment its capacity, we add the double of elements, the overall number of copies is n,
so the runtime is O(n), and the overall amortized time, which is O(n)/n, equals O(1): 

### find data

For an array, finding a given element, all the strucutures have to be checked, so that is O(n), lineal time. And checking all
the elements is known as linear search.

In case the data is sorted, then it takes less time. In case we are using a binary search then the the search time
is O(lg(n)) [ lg(n) = log_2(n) ] (that means logarithm of base 2).

In the case of linked lists, as we cannot go to the middle of the link, is is needed a linear search, so the time is O(n) 

### insert after an element or delete after an element. 

In an array we have to move all the data after the desired position, that are n/2 elements, so this is O(n) time.

In a list, only an insertion is needed, that means only change the pointes, so 1 operation, that is O(1) time. 

### QUEUE

A queue is a first-in first-out structure

```
           +----+----+----+----+----+----+----+----+----+----+
         >>|    |    |    |    |    |    |    |    |    |    | >>
           +----+----+----+----+----+----+----+----+----+----+

```

When commenting on data structures, those will be refered as ADT (Abstract Data Structures), 
without focusing in its implementation. ADT is a description. 

For the queue ADT, 4 functions are going to be considered:

- create: create a queue 
- push  : add data at the back of the queue
- pop   : remove data from the front of the queue
- empty : reports true if the queue is empty

a queue can be implemented as a n array or as a linked list. Both implementations can achieve O(1) operations. (maybe the linked list is a shade better).

reference: https://en.cppreference.com/w/cpp/container/queue


### STACK

A stack First In First Out structure (like a pile). we consider 4 operations as a adt (abstract data type): create, push, pop, Isempty.

- create: create a stack
- push: add data to the top of the stack
- pop: remove data from the top of the stack
- empty: returns true if the stack is empty

Notice the pop values from a queue and a stack are the oppossite. 

The stack implementation can be based on an array or a linked lists.  Both implementations can achieve O(1) operations. (maybe the linked list is a shade better).


## TREE STRUCTURES

- Every element of a tree is known as a **node**, usually is represented as a cicle
- the connections between nodes are known as **edges**, usually is represented by an arroy (with direction) 
- A tree has always a **root node** and it has no incomming edges. 
- Nodes that have no outgoing edges are known as **leaves**
- The nodes can have a name and data
- Edges usually have no name, and have no data. Edges can be identified by the name of the nodes it belongs.
- Every node, except the root node has exactly one **parent node**
- A **node's children**, are the nodes that have that node as a parent.
- **Sibling** are nodes with the same parent

A tree: 
- Must have a root.
- Must have directed edges.
- Must not contain a cicle. 

### BINARY TREES

- Every single node can have only two childs, left child and right child.

 - The height of a binary tree, is the number of edges in the longest path from the root to a leaf. (... so the height is measured in edges).
 - A binary tree is said to be **full**, if every node has either zero or two children.
 - A binary tree is said to be **perfect**, if and only if, all interior nodes, have two children and all leaves are at the same level. 
 - A binary tree is said to be **complete**, if and only if, is perfect, up until the last level and all leaf nodes on the last level are pushed to the left. 
 
 
 ```
 perfect tree of heigth 2
 
        #
	   / \
	  #   #
	 / \ / \
	#  # #  #
 ```
 
 ```
 complete tree of heigth 2
 
        #
	   / \
	  #   #
	 / \ /
	#  # # 
 ```
 
 ### types of traversals
 
 Traversal is the way to go throught the nodes of a tree.
 
 #### preorder traversal. 
 
 ```     
            + 
          /   \	
        -      * 
      /  \    / \ 
     a    /  d   e 
        /  \
        b  c 
 ```
 
 if we make the order of geting the node data, then go left child, and then right child, the traversal is like:
 
 ```
 + - a / b c * d e 
 ```
 
 ### in order traversal
 
 in order traversal, means, we are going left, node, and right. 
 
 ```
 a - b / c + d * e
 ```
 this is how a math equation can be encoded in a tree
 
 
### post-order traversal,

the order is left, right and node, 

in the example: 

```
a b c / - d c * + 
```

### level order traversal

it traverses the tree level by level. 

in the example: 

```
+ - * a / d e b c
```
 
 
### BINARY SEARCH TREE (BST) 

A binary Search tree (BST) is an ordered binary tree, that is a special structure used to for searches. 

A binary tree is a binary search tree (bst), if only if for every node of the tree:

- nodes values in the left of the subtree are less that the node value itself
- nodes values in the right of the subtree are greater that the node value itself. 


  ```     
            37 
          /    \	
        19       51
      /   \     / \ 
     4     22  42  55 
    / \   /  
   2  11 20   
 ```
 
 Dictionaries are common applications of BST.
 
 For a dictionary ADT (abtract data type) there are 4 operations to consider:
 
 - find
 - insert
 - remove
 - empty
 
 an example possible implementation:
 
 ```c++
 template<typename K, typename D> 
 class Dictionary {
   public:
   Dictionary();
   const D& find(const K& key);
   void insert(const K& key, const D& data);
   const D& remove(const K& key);
   
   private:
   class TreeNode {
     public:
	 const K& key;
	 const D& data;
	 TreeNode *left, *right;
	 TreeNode(const K& key, const D& data)
	   : key(key), data(data), left(nullptr), right(nullptr){}
	   };
    
	TreeNode *head_;
	...
 ```
 
 the worst case in a BST search would be travel the longest path, but it is better that travel a full tree. The worst case in a BST tree, 
 would be visit the heigth of the tree, so in big O notation that would be: O(heigth)  < O(number_of_elements)
 
 an example for the find function would be: 
 
 ```C++
 template <typename K, typename D>
 const D& Dictionary<K, D>::find(const K& key) {
   TreeNode*& node = _find(key, head_);
   if (node == nullptr) { throw  std::runtime_error("key not found!"); }
   return node->data;
 }
 
 ...
 
 template <typename K, typename D>
 const D& Dictionary<K, D>::TreeNode*& Dictionary<K,D>::_find(
 const K& key, TreeNode *& cur) const {
  if (cur == nullptr) { return cur; }
  else if (key == cur->key) { return cur; }
  else if (key < cur->key) { return _find(key, cur->left); }
  else                     { return _find(key, cur->right); }
 }
 ```
 to insert a node:
 
 ```C++
 template <typename K, typename D>
 void Dictionary<K, D>::insert(const K& key, const D& data) {
   TreeNode *& node = _find(key, head_);
   node = new TreeNode(key, data);
 ```
  
 Removing elements is more tricky: 
 
 there are 3 cases, dependin on the number of children of the node we want to remove: 
 
 - zero children 
 - one children
 - two children
   - find the IOP of the node to be removed.
   - swap with the IOP
   - remove the node in the new position. 
   
In-Order-Predecessor (IOP): The in-order-predecessor, is the previous node in an in-order traversal of a BST.

The IOP is always the right-most node of the node's left sub-tree.

```c++
template <typename K, typename D>
const D& Dictionary<K, D>::remove(const K& key) {
  TreeNode *& = _find(key, head_);
  return _remove(node);
}

template <typename K, typename D>
const D& Dictionary<K, D>::_remove(TreeNode *& node) {
  // zero child remove
  if (node->left == nullptr && node->rigth == nullptr) {
    const D& data = node->data;
	delete(node);
	node = nullptr;
	return data;
  }
  // one-child (left) to remove
  else if (node->left != nullptr && node->right == nullptr) {
    const D& data = node->data;
	TreeNode* temp = node;
	node = node->left;
	delete(temp);
	return data;
  }
  else if (node->left == nullptr && node->right != nullptr) {
    const D& data = node->data;
	node = node->right;
	delete(temp);
	return data;
  }
  // two children remove
  else {
    //find the IOP
	TreeNode *& iop = _iop(node->left) ;
	//swap the node to remove and the iop
	_swap(node, iop);
	//remove the node
	return _remove(node);
  }
}
```

#### Algorithmic analysis of the Binary Search TreeNode


BST (binary Search Trees) can have many different forms, even if they have the same data.


With de data set = {1, 2, 3, 4, 5, 6, 7 }

insert order: 4 2 3 6 7 1 5
```
           4
        /     \
      2        6
    /  \     /   \
   1   2    5     7
```
 
insert order: 1 3 2 4 5 7 6 
```
     1  
	  \ 
	   3
	  / \
	 2   4
	      \
		   5
		    \
			 7
			/
		   6
```
so those previous trees have the same data, but their structures are very different. 
All depend on the insertion order.

So for a set of n elements, there are n factorial (n!) different insertion orders. 

So there are n! ways to create a BST with the same data. The worst case BST has a 
height proportional to the number of nodes (like a linked list). The average BST
will have a height proportional to the logarithm of the numbers of the nodes.

The worst case would be that one, that is the same as a linked list.

```
  x
   \
    x
	 \
	  x
	   \
	    ...
```


```
|        | BST average   |  BST worst case  |  sorted array   |  sorted list |
| find   |   O(lg(n))    |       O(n)       |     O(lg(n))    |     O(n)     |
| insert |   O(lg(n))    |       O(n)       |     O(n)        |     O(n)     |
| remove |   O(lg(n))    |       O(n)       |     O(n)        |     O(n)     |
```

To measure the balance of a tree, a new metric will be defined: 

**High Balance Factor**: the height balance factor (b) of a node is the difference in height between its two subtrees. 

b = height(right_subtree) - height(left_subtree)

So for the next tree:
```
           4
        /     \
      2        6
    /  \     /   \
   1   2    5     7
```

b = 1 - 1 = 0. The tree is balanced.

And for this tree: 

```
     1  
	  \ 
	   3
	  / \
	 2   4
	      \
		   5
		    \
			 7
			/
		   6
```
 like the left subtree has no height, its value is -1
 
 so: b = 4 - (-1) = 5 . the balance factor is +5, so the tree is heavily skeew to the right. 
 
 We define that a Balanced BST, is a BST where every node's balance factor has a value of 0 or 1. 
 
 Using the height balance factor, we can formalize if a given BST is balanced. 
 

## Balanced binary trees (AVL trees) 

Balanced binary trees, hare height-balanced trees that ensures nearly half of the data is located in each sub-tree.

Two sub-trucutures will be diferenciated:

- mountain
- stick

```
Mountain

      *
	 / \
	*   * 
```

```
Stick 
       *
	    \
		 *
		  \
		   *
```

A Stick is something that we will want to transfor into a mountain. That would allow that a Binary tree stays as balanced as possible.

So if we have the following example

```

              u          b = 2 - deepest node out of balance = 2
			/  \ 
	b = 0  *     v       b = 1
                / \ 
		b = 0  *   *     b = 1
				    \ 
					 *   b = 0
```

In this example, the stick is what makes the tree out of balance. Lets transform it into a mountain.

For that, pick the middle node of the stick, raise it up, and transform the middle node into the peak of the mountain.

```
   u             v
    \     =>    /  \
	 v         u    *   
	  \
	   *
```

we consider the generic case known as left rotation:

Consider an arbitrary tree that:
 - the deepest point of inbalace it at node b  
 - the balance factor of b is 2 
 - the balance factor of c is 1 (that means b is inbalanced to the right) 
 - an insert on subtrees t3 or t4 caused the inbalance


```
    ...
	  \
	   b
     /   \
   t1	   c
         /   \
       t2      d
             /   \
            t3    t4			 
	   
	   
```

An inbalaced node is a node that has a balance factor greater than 1.

To solve this, we can perform a left rotation, visually:

```
    ...                               ...
	  \                                  \
	   b                                  c
     /   \                              /   \    
   t1	   c              =>         b         d
         /   \                     /   \     /   \
       t2      d                 t1    t2   t3   t4
             /   \
            t3    t4			 
	   
	   
```

The left rotation, means bringing the middle node of the inbalanced branch (c) up, and rotatin the subtrees to the left, therefore the name: left rotation.

That would mean, detach `b` and attach `c` instead, attach `b` to `c`, and move `t2` under `b`


Lets consider other situation:

```
     *
   /   \ 
  *     *
         \
		  *
         /
	    +	  

```

In an initially balanced tree, a new node is add (the `+` node)

This structure is known as an elbow

``` 
   *    b = 2 
    \
	 *  
    /
   *
```

In this elbow structure the blance factor is 2.

This a mix example, it is mix between a stic, and and elbow. To balance the tree, it is needed to fix the elbow,
and make it an stick, this is done by doing a rotation in the bend of the elbow, by moving the `+` node up:

```
     *                     *
   /   \                 /   \
  *     *               *     *
         \       =>            \
		  *                     +
         /                       \
	    +	                      *

```


Once we have the stick, whe only have to make a left rotation.
This is knwon as generic right-left rotation:

 - the deepest point of inbalace it at node b  
 - the balance factor of b is 2 
 - the balance factor of c is -1 (that means b is inbalanced to the left) 
 - an insert on subtrees t2 or t3 caused the inbalance
 
 ```
    ...
	  \
	   b
     /   \
   t1	   c
         /   \
        d     t4			 
	   / \
	 t2  t3
```

visually, would be:

 ```
  initially
    ...                                  ...                                       ... 
	  \                                     \                                        \
	   b                                      b                                       d
     /   \             move d up            /   \               move d up           /    \
   t1	   c               =>             t1      d                 =>             b      c 
         /   \                                  /   \                            /  \    /  \
        d     t4     transform the             t2    c        make into a       t1  t2  t3  t4    
	   / \            elbow into a                  /  \       mountain,                   
	 t2  t3             stick                     t3    t4       moving up the               
	 	                                                          middle node of
																   the stick
```

	
table of rotations

|                       |  balance factor of lowest point of inbalance  | balance factor of the node in the direction of inbalance |
| left rotation         |                     2                         |                            1                             |  sign match - simple rotation
| right rotation        |                    -2                         |                           -1                             |  sign match - simple rotation
| right-left rotation   |                     2                         |                           -1                             |  sign differ (elbow -> double rotation)
| left-right rotation   |                    -2                         |                            1                             |  sign differ (elbow -> double rotation)


BST rotations restore the balance property to a tree after an insert causes a BST to be out of balance.

For possible rotations: L, R, LR, RL

- rotations are local operations
- rotations do not impact the broader tree.
- rotations run in O(1) time.

These are known as AVL trees. An AVL is the same as a binary balanced tree, but we always asure that the balance is mantained. 

for that:

- extra operations are done when inserting and removing. 
- to quickly compute the balance factor AVL trees store the height of every node as a part of the nodes itselves.

## B-TREE

 The main idea, is to get a structure that can grab data, as well in main memory as in disk, in particular,  a strucuture, that needs
 as few operations as possible, ... would it be search in a disk, or remote requests... 
 
 A B-Tree is constructed by having a node that has a number of keys. Between the keys, there is a pointer to another node that has the values
 
```
           +----+----+----+----+----+
           |  1 | 10 | 25 | 40 | 70 | 
           *----*----*----*----*----*
	       |    |    |    |    |    |    
	       V    V    V    V    V    V
```

 A node is defined with an order, the order stands for the size of the node, the order of a node is the maximum number of keys
 that the node can have plus 1. 
 
 For a B-tree of order m:
 - All keys within the node are sorted in order
 - Each node contains no more that m-1 keys
 - Each internal node can have at most m children, so a B-tree of order m, is like an m-way tree. 
   - a root node can be a leaf or have [2, m] children
   - each non-root, internal node has [ceil(m/2), m] children.
 - All leaves are on the same level. 
 
 
 reference: https://www.cs.utexas.edu/users/djimenez/utsa/cs3343/lecture16.html
 reference: https://www.geeksforgeeks.org/introduction-of-b-tree-2/
 
#### B-tree insertion example

We have a B-tree nodes order 5.

We want to insert the keys: 14, 19, 47 and 81, so:

```
         | 14| 19| 47| 81|
```

then we want to insert 42. It needs to go into the middle, but that would exceed the capacity of the B-tree


```             
               42
                V  we want to insert 42, but it would exceed the order 5.			   
                V
         | 14| 19| 47| 81|
```

So then, we need to throught up the value 42, and thus create a new node.

```
                |42|
			    /  \
        |14| 19|    | 47| 81|
```

### B-tree insertion example 2

We have the B-tree:

```
             __|23|42|___   m=3
		    /    |       \
      |-3|8|    |25|31|   |43|55| 		 
```
we want to insert the number 30. we try to find 30 in the B-tree.

```
             __|23|42|___   m=3
		    /    |       \
      |-3|8|    |25|31|   |43|55| 
                   /\
                    Here should be 30.				   
```
so:

```
             __|23|42|_______   m=3
		    /    |           \
      |-3|8|    |25|30|31|   |43|55| 
                   /\
                   But now the node has exceed the order m=3
```

The node has exceed the order 3, so the 30 has to be brought up

```
             __|23|30|42|__  m=3
		    /    |   |     \
      |-3|8|    |25  |31|   |43|55| 
				   
```

Since the root node is also full, we need to throught up the middle value:
				   
				   
```
                  |30|
		         /    \
              |23|    |42|        m=3
		      /     /     \
        |-3|8|   |25|31|  |43|55| 
				   
```

### insertion in B-Tree

Insertion 
1) Initialize X as root. 
2) While X is not leaf, do following 
..a) Find the child of X that is going to be traversed next. Let the child be Y. 
..b) If Y is not full, change X to point to Y. 
..c) If Y is full, split it and change X to point to one of the two parts of Y. If K is smaller than mid key in Y, then set X as the first part of Y.
     Else second part of Y. When we split Y, we move a key from Y to its parent X. 
3) The loop in step 2 stops when X is leaf. X must have space for 1 extra key as we have been splitting all nodes in advance. So simply insert K to X. 

Note this algorithm is actually a proactive insertion algorithm where before going down to a node, 
the next node is split if it is full. The advantage of splitting before is, the node is never traversed twice. If the node is not split before 
going down to it and split it only if a new key is inserted (reactive), we may end up traversing all nodes again from leaf to root. 
This happens in cases when all nodes on the path from the root to leaf are full. So when we come to the leaf node, we split it and move
 a key up. Moving a key up will cause a split in parent node (because the parent was already full). This cascading effect never happens
 in this proactive insertion algorithm. There is a disadvantage of this proactive insertion though, we may do unnecessary splits. 
 
#### search in B-Tree

```
bool Btree::_exists(BTreeNode& node, const K& key) {                // node, is the node we are starting from
    unsigned i;
	for( i = 0; i < node.keys_ct_ && key < node.keys_[i]; ++i) {}   // this is a lineal search O(n), although we could do it with binary search O(log(n)) 
	                                                                // it doesnt matter, because, the costly operation is fetch the next Child.
	
	if ( i < node.keys_ct_ && keys == node.keys_[i] ) {             // if this node complies, then it exists.
	    return true;
	}
	
	if (node.isLeaf()) {
	    return false;
	
	else {
	    BTreeNode nextChild = node._fetchChild(i);                  // fetchChild() is to move to the next child. This is the most costly operation.
		return _exits(nextChild, key);
	}
}
```
The height of the Btree is what determines the maximum number of seeks possible to search all the data. The height of the structure is log_n(n). 
Then the number of seeks is no more than log_m(n) 


## Heaps

Lets think in a set of numbers (without care for their order) 

```
   3    -17    42
   e     42     pi 
   -10   -pi  ...
```

In this data structure, we dont want to keep data order, but the only interesting operation is that it can remove the minimum value in an efficient way
We look to convert this into a priority queue, in which data has a priority, and it is possible to remove acording to the highiest or lowest priority 

Lets compare with other common data structures 

```

                    Insert      Remove Min
					
unsorted array       O(1)*         O(n)

unsorted lists       O(1)          O(n) 

sorted array         O(n)          O(1)

sorted list          O(n)          O(1) 

```

unsorted arrays or lists have good insert times, but bad remove min times. A sorted array or lists, have a bad insertion time, but the removal time is good O(1).

We can build a data structure like a tree (we will call it a Heap or min-Heap), and its properties:

 - The heap tree is o an empty tree, or have nodes, so right and left nodes are larger than the root node.  > The parent is larger than any of its descendands


```
           4
        /      \
      5          6
    /   \       /   \
  15     9      7     20
 / \    / \    / 
16  25 14 12  11 
```

We need to ensure that the heap tree is always a complete tree, which is a tree completelly fill in up to the last level, and in the last level all the nodes
will be pushed to the left. Once whe have this, we can store it as an array 

```
       |  | 4 | 5 | 6 | 15 | 9 | 7 | 20 | 16 | 26 | 14 | 12 | 11 |
  
index:  0   1   2   3   4    5   6    7   8    9    10   11    12

NOTE: the first position [0] is always empty.
```

So, if we ar einterested on the node ov value 9, index 5, its parent is at index 2, and its is possible to easy calculate because 5/2 = 2, its integer division.
Its other sibling 15, index 4, its parent is 4/2 = 2. So inside the array we can easily identify the parent of a node. 

```
   index_parent = index_children/2
```
in the same way but in reverse we can indentify the childrens of a node. 

```
   index_left_child = index_parent * 2
   index_right_child = index_parent * 2 + 1
```

### heap insert

Lets insert 8 in the previous heap tree

```
           4
        /      \
      5          6
    /   \       /   \
  15     9      7     20
 / \    / \    / \
16  25 14 12  11  8
```
After inserting 8, we need to make sure that each parent has a smaller value that its children. In this case it is straight to see it complies

Now lets insert the element 3.


We put 3 at the end of the array 

```
        |  | 4 | 5 | 6 | 15 | 9 | 7 | 20 | 16 | 26 | 14 | 12 | 11 | 8 | 3 |
```

this results in:

```
           4
        /      \
      5          6
    /   \       /   \
  15     9      7     20
 / \    / \    / \    /
16  25 14 12  11  8  3
```
now 3 and 20 are out of order. To solve this we just need to swap 20 and 3. 

```
        |  | 4 | 5 | 6 | 15 | 9 | 7 | 3 | 16 | 26 | 14 | 12 | 11 | 8 | 20 |
```
```
           4
        /      \
      5          6
    /   \       /   \
  15     9      7     3
 / \    / \    / \   /
16  25 14 12  11  8 20
```

But now, 3 and 6 are out of order, so we swap them again

```
        |  | 4 | 5 | 3 | 15 | 9 | 7 | 6| 16 | 26 | 14 | 12 | 11 | 8 | 20 |
```
```
           4
        /      \
      5           3
    /   \       /   \
  15     9      7     6
 / \    / \    / \   /
16  25 14 12  11  8 20
```

Now we have to swap 3 and 4

```
       |  | 3 | 5 | 4 | 15 | 9 | 7 | 6| 16 | 26 | 14 | 12 | 11 | 8 | 20 |
```
```
           3
        /      \
      5           4
    /   \       /   \
  15     9      7     6
 / \    / \    / \   /
16  25 14 12  11  8 20
```

The function is:


```
template <class T>
void Heap<T>::_insert(const T& key) 
    // check there is space to insert the an element
	// ... if not grow the array
	if (size_ == capacity_) { growArray(); }
	
	// insert the new element at the end of the array
	item_[++size] = key;
	
	//restore the heap propierty
	_heapifyUp(size);                //this is the functions that ensures that the propierties of the heap are maintained.
}
```

Keep in mind that every time we have to grow the Array we have to grow it for the whole next level. 

```
template <class T>
void Heap<T>::_heapifyUp(int index) {
    if ( index > 1 ) {
	    if ( item_[index] < item_[ parent(index) ] ) {
		    std::swap( item_[index], item_[ parent(index) );  // parent(index) is index/2
			_heapifyUp( parent(index);
		}
	}
}	

```

### Heap min removing element

The relevant operation for the heap min is to remove the minimum element: removeMin()

Lets see an example, with the previous tree, and trying to removeMin().


```
           4
        /      \
      5          6
    /   \       /   \
  15     9      7     20
 / \    / \    /
16  25 14 12  11
```

```
        |  | 4 | 5 | 6 | 15 | 9 | 7 | 3 | 16 | 26 | 14 | 12 | 11 | 
```

the root element is 4, to try to keep the propierties of the tree, lets use a clever trick and swap 4 and the last element 11.


```
           11
        /      \
      5          6
    /   \       /   \
  15     9      7     20
 / \    / \    /
16  25 14 12  4
```

```
        |  | 11 | 5 | 6 | 15 | 9 | 7 | 3 | 16 | 26 | 14 | 12 | 4 | 
```

now we have to heapifyDown. next nodes are 5 and 6. 5 is the lowest so we swap 5 and 11


```
            5
        /      \
      11          6
    /   \       /   \
  15     9     7     20
 / \    / \   
16  25 14 12 
```

We have to heapifyDown the next level of 15 and 9. 15 is bigger that 11, so it is ok. 9 is smaller than 11, so we swap 11 and 9.

```
            5
        /      \
      9          6
    /   \       /   \
  15     11    7     20
 / \    / \   
16  25 14 12 
```

In the next level 14 and 12, both are bigger that 11, so the process has finised.

now we can remove the 4.


```
            5
        /      \
      9          6
    /   \       /   \
  15     11     7   20
 / \    / \    
16  25 14 12 
```

```
       |  | 5 | 9 | 6 | 15 | 11 | 7 | 20 | 16 | 26 | 14 | 12 |
```

Lets try again removeMin(), so we are removing the element 5

We swap 5 and 12.

```
           12
        /      \
      9          6
    /   \       /   \
  15     11     7   20
 / \    / \    
16  25 14  5 
```

we can remove the 5

```
           12
        /      \
      9          6
    /   \       /   \
  15     11     7   20
 / \    /    
16  25 14  
```

we have to update the next level of 9 and 6. 6 is the smallest element, so 6 becomes the root, we swap 12 and 6.


```
           6
        /      \
      9           12
    /   \       /   \
  15     11     7   20
 / \    /    
16  25 14  
```

we compare now the childrens of 12 in the next level: 7 and 20. 7 is the smallest element, so we swap 7 and 12.


```
           6
        /      \
      9           7
    /   \       /   \
  15     11    12   20
 / \    /    
16  25 14  
```

the code could be like:

```
template <class T>
void Heap<T>::_removeMin() {
    // Swap with the last value
	T minValue = item_[1];
	item_[1] = item_[size];      //swap between the root and the last element.
	size--;
	
	//restore the heap propierty
	heapifyDown();
	
	//Return the minimum value
	return minValue;
	}
}
```
and the heapyfyDown function:

```
template <class T>
void Heap<T>::_heapifyDown(int index) {
    if ( !_isLeaf(index) )  {
	    T minChildren = _minChild(index); 
		if ( item[index] > item_[minChildIndex] ) {
		    std::swap( item_[index], item_[minChildIndex] );
			_heapifyDown( minChildIndex );
		}
	}
}
```
### Build heap 


To build a heap out of a set of data, there are 3 options

1 - sort the array
2 - use heapifyUp() 
3 - use heapifyDown() - but this has an advantage

Ifthe heapifyDown operation is used, we have to realize that it doesn't matter what is in the lowest level of the tree. 

Example:

```
  |  | B | U | I | L | H | E | A | P | N | O | W | 
  
              B 
		  /        \
		 U          I
       /   \      /    \
	 L      D    H      E 
	/  \   / \  / 
   A   P   N O  W 	
```

We have to mainaint the heap propierty in L, so we swap L and A. 

```
              B 
		  /        \
		 U          I
       /   \      /    \
	 A     D    H      E 
	/  \   / \  / 
   L   P   N O  W 	
```

So after heapifingDown, we now everything under the nodes is balanced. That makes n/2 operations, that is O(n) operations.

### Heap sort

Lets see how we can build an array when we have a heap.

```
           4
        /      \
      5          6
    /   \       /   \
  15     9      7     20
 / \    / \    / 
16  25 14 12  11 
```

```
       |  | 4 | 5 | 6 | 15 | 9 | 7 | 20 | 16 | 26 | 14 | 12 | 11 |
```

1 - build the heap O(n)
2 - n times call removeMin() ( removeMin is O(log(n))) son the operations are: n * log(n) 
3 - swap elements to order 

It is possible to do a heap Sort without any additional space in the memory. This is a very good sort algorithm that has the benefits of being in the memory.


## NORDERED DATA STRUCTURES


# HASHING & HASH TABLE

Hashing is an algorith, that gets a set of values (keyspace) and tranforms it in other values. And the goal is to map every single key 

A hash table needs 3 elements:

- A hash function, that maps the input keyspace into an array index.
- An array that stores the data. 
- A method to handle collision, when the hash function maps two different values to the same point in the array. 

To evaluate how a given hash function is appropiate, we have to consider: 

- A hash: how it transforms the input data into a numeric value. 
- A compression: make sure the hash function is within the bounds of the array. It is common to use the modulo operator (remainder of division operation). 

Some caracteristics of a good hash function: 

- Computation time: it should have contant time: O(1). 
- Deterministic: If we hash a given data once, and then other time, the hash result must be the same.
- Satisfy the SHUSA (Simple Hash unified Assuption): The result of a hash algorithm must be uniform across the entire key space. 

Ìn case of collisions there are several collision strategies: 

- separate chaining, each collision is treated as a linked list, and the value that collisioned is added at the begining of the linked list. Separate chaining is best suited for cases with big records.
- probing and double hashing. Double hashing is better suited to be used in cases that need structure speed. 

Hash tables are the best algorith to look up data.

HASH TABLES ARE THE BEST ALGORITHM TO LOOK UP DATA.

In c++ actually there is a hash table implemented into the standard library. 

std::map is a black-red tree under the hood. std::unordered_map is implemented as a hash table under the hood. 

## DISJOINT SETS

Disjoint sets are a series of sets which are disjoint from one another, but every single element within a set, is considered to be equivalent within that set. 

One of the operations we need is find(), so we can identify elements within those sets.

The other operation that is interesting, is union() of sets. 

A proposed API, is:

```
void makeSet(const T& t);
void set_union(const T& k1, const T& k2);
T& find(const T& k);
```

Disjoint-set data structures model the partitioning of a set, for example to keep track of the connected components of an undirected graph.
 This model can then be used to determine whether two vertices belong to the same component, or whether adding an edge between them would result in a cycle

reference: https://en.wikipedia.org/wiki/Disjoint-set_data_structure

reference: https://courses.cs.washington.edu/courses/cse373/01sp/Lect21_4up.pdf

reference: https://www.boost.org/doc/libs/1_31_0/libs/disjoint_sets/disjoint_sets.html


lets imagin we have a group of sets

```
{2, 5, 9}  {7}  {0, 1, 4, 8}   {3, 6}

```

In those sets, we consider every element inside each of the sets, absolute equivalent, so for example, for the fist group: 2 = 5 = 9.  Mathematically it is said
that those elements have an equivalen relationship with one each other. 

We will use the first element of the set definition, as the identifier for the set, so for example, for the set {2, 5, 9} the identifier would be the 2.

One set operation we are interested in is union two sets together, within a set that contains the elements of both groups. 

so for exaple:

```
union(find(2), find(3)) = {2, 5, 9, 3, 6}
```

So a disjont sets, is the group of differnt sets: S = {s0, s1, s2 ... }, in which every set has a representative number.

A proposed API, is:

```
void makeSet(const T& t);
void set_union(const T& k1, const T& k2);
T& find(const T& k);
```

Lets consider a simple implementation: we are going to store all the elements in an array, 

```
    array index       | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
		              |   |   |   |   |   |   |   |   |
```

so we can say that the value on the array is the identiy of the group it belongs to:


```
Disjoint set: {0, 1, 4} {2,7} {3, 5, 6}

```

```
    array index       | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
		              | 0 | 0 | 2 | 3 | 0 | 3 | 3 | 2 |
```

This implementation has the problem, that it doesn't allow to easily know what elements belong to a given set, if we want to know the elements that belongs
to the set with identy 2, we have to traverse the whole array, that is O(n). We will look for a better implementation that this, the up-trees implementation.

The up-trees implementation will use an array there the index is the key, 

The value of the array is: 
 - -1, if the value found is the representative element
 - the index of the parent, if we haven't found the representative element
 
 
 So imagin, we have the disjoint set, with all representative elements:
 

```
    array index       | 0  | 1  | 2  | 3  |
		              | -1 | -1 | -1 | -1 |
```

So we want to make the union of 0 and 3, so, we make the 3 element to point to 0

```
      ↑
	  0
	  ↑
	  3
```

This will be represented in the array like:

```
    array index       | 0  | 1  | 2  | 3 |
		              | -1 | -1 | -1 | 0 |
```

now we want to union 1 and 2

```
      ↑     ↑ 
	  0     1
	  ↑     ↑ 
	  3     2
```

so: 

```
    array index       | 0  | 1  | 2  | 3 |
		              | -1 | -1 | 1  | 0 |
```

Now we want to union 0 and 1. For that we can just point 1 to 0, and that will do. 


 ```
      ↑      
	  0  ←  1
	  ↑     ↑ 
	  3     2
```


```
    array index       | 0  | 1  | 2  | 3 |
		              | -1 | 0 | 1  | 0 |
```


So for exaple with this disjoint set: 

```
        {5, 2, 9}  {7}  {4, 0, 1, 8}   {3, 6}
	    
		 ↑         ↑         ↑           ↑
		 5         7         4           3
		/ \                 / \          ↑
	   2   9               0   8         6
                           ↑
						   1
						 
array index       | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
		          | 4 | 0 | 5 | -1| -1| -1| 3 | -1|

```

The worst case with this implementation, would be a up-tree that looks like a linked list.

lets have a look to the find algorith for:

```
int DisjointSet::find(i) {
    if ( s[i] < 0 ) { return i; }   // the representative element was found
	else { return _find( s[i] ); }  // check the parent of the element
}
```

So the running time of this algorithm is going to be proportional to the height of the tree: h. So it would be O(h). 
The deepest node of the tree dictates the find speed. In the worst case h = n, and the execution time is O(n). 

So we could build a up-tree that improves this: we could have an representative node in which all the children depend on that node. 
So the disjoint set has a height of 1 in the whole tree. 

```
        {5, 2, 9}  {7}  {4, 0, 1, 8}   {3, 6}
	    
		 ↑         ↑         ↑            ↑
		 5         7         4  __        3
		/ \                 / \   \       ↑
	   2   9               0   8   1      6

```

Lets see if we can improve the disjoint sets operations with smart unions and compressions.

We have two sets: 

```
	         ↑          ↑
	      __ 7 _        4
	     /   ↑  \       ↑
		6    8   9      10
      / ↑ \  ↑          ↑
	 0  1  2 3			5
                        ↑
                       	11
						
array index       | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
		          | 6 | 6 | 6 | 8 | -1| 10| 7 | -1| 7 | 7 | 4  |  5 |

```

One possibility is to improve the structure, so the the representative value, insted of having the value -1, has the value (-height-1), this way
we have encoded the height in the strucuture, and when an union is requested, we can unify with the highest tree, so the tree doens't increase in height. 
so we can keep the height of the tree as small as possible adding the smaller tree into the higher tree. 

** remember the height of a tree is the number of edges to the deepest node** 

```				
array index       | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
		          | 6 | 6 | 6 | 8 | -4| 10| 7 | -3| 7 | 7 | 4  |  5 |

```

Other possibilty is to store in the value of the representative element the size of the set. 


```				
array index       | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
		          | 6 | 6 | 6 | 8 | -4| 10| 7 | -8| 7 | 7 | 4  |  5 |

```

In the union by size, the smaller of the trees is union with the larger one.


In both options: union by size or union by height, both algorithm ensure, we have a tree whose structure  which height is bounded by O(log n) 

Using either size or height strategies above results in the same overall run time complexity.

<br>

Now lets look the path compression strategy. We are given a very high tree

```
            ↑
			10
		   /  \
		  9    11
		 / \
		1   7
		   / \
		  2   8
	     / \
		3   4
		   / \
		  5   6
		 
```

and a find(5) operation is requested. so, we have to do: ' 5-> 4 -> 2 -> 7 -> 9 -> 10' 

So we known that 5 is gona have the same value as 4, 2, 7, and 9. It is possible now rolling back in recursion, and update the structure, and point all the values to the representative element.  

Path compression: When traversing the up-tree from an element to its root, if any elements in the traversal (including the first element, but excluding the root itself) do not point directly 
to the root as their parent yet, they will have their parent pointer changed to point directly to the root.

example code for path compression: 

```
int DisjointSets::find(int i) {
  static std::vector<int> traversed;
  if ( s[i] < 0 ) {
    for(unsigned j= 0; j < traversed.size(); ++j) { s[traversed[j]] = i; }
	//  for( const int& element: traversed) { s[element] = i; } // also :)
    return i;
  } else {
    traversed.push_back(i);
    return find(s[i]);
  }
}
```

The running time of the disjoint set, is what is known as the 'iterate log'

The iterate log function is denoted as: 'log*'

The iterate log is defined as the number of times you can take the log of a number. 

```
log*(n)  =
 
 - 0                ,    ∀ n <= 1,
 - 1 + log*(log(n)) ,  , ∀ n >  1

```

So for example: what is the log*(2^65536)?

log*(2^65536) ->  log*(16) -> log*(4) -> log*(2) -> log*(1) = 0.

or what is equal to lg*(2^64)?

```
lg*(2^64) = 1 + lg*(64) = 1 + 1 + lg*(6) = 1+ 1 + 1 + lg*(~2.6) = 1 + 1 + 1 + 1 + lg*(1.4) = 1 + 1 + 1 + 1 + 1 + lg*(0.5) = 5
```


So the iterative log is a very good performance.


So for a disjoint set, the total number of operations, after a series of m find and union operations, is going to be equal in worst case to a runntime of O(m * log*(n)),
where n is the number of elements in the disjoint set. This performance is so good, that it is considered for practical purpouses is O(1) amortized time: O(1)*. 


More references:

 -  https://github.com/wadefagen/coursera
 - 	http://mfleck.cs.illinois.edu/building-blocks/
 -  http://jeffe.cs.illinois.edu/teaching/algorithms/
 

## GRAPHS

A graph is a collection of vertices/node and edges. Edges connect two vertices/nodes. The number of vertices in the graph is named 'n', |V|=n, and the number of edges,
is denomied as 'm'. |E|=m. 

So a graph (G) is defined by its given vertices (V) and edges (E): 

G(V,E):
 - |V| = n  // n usually reports the number of vertices
 - |E| = m  // m usually reports the number of edges

Some vocabulary:

 - An incident edge, is an edge, which directly connects with a node. The node has a degree, which is the number of incident edges to the node. I(v) = { (x,v) in E}
 - The degree of a vertex/node is the number of incident edges it has. Degree(v): |I|
 - Adjacent vertices that are all the vertices adjacent to a node. 
 - A path, is a given sequence of vertices connected by edges.
 - A cycle is a path with a common begin and end vertex. 
 - A simple graph is graph with no self loops or multi-edges.
 - A subgrap, is a graph that is part of a graph that contains it.

With this vocabulary, lets think some questions: 

Q1: How many edges can exist on a graph that is the minimum number of edges, on a not connected graph?

- A non connected graph, doesn't need edges, so all the vertices can be on their own, so the answer is 0. 

Q2: And if the graph is connected?

 - The most simple graph is such that all the nodes are connected in a path, and only one path. This means, that is the number of nodes minus 1. So n-1.

Q3: And the most number of edges, in a connected simple graph?

Lets think, for graph with different number of vertices:

@ n = 1 -> m = 0
@ n = 2 -> m = 1
@ n = 3 -> m = 3
@ n = 4 -> m = 6

So this looks like the sequence: n*(n-1)/2, this has an order of O(n^2).

The explanation is: for every node, it connects with every other node except with itself, that is where the n-1 comes from. 
Those edges are shared between the nodes, so then it is (n-1)/2. And that factor is for every node: n. So it results in: n*(n-1)/2

Q4: What is the sum of all the degrees of all the nodes?

It would be 2m, because it means counting all the edges. 

### Basic implementation

The graph implementation would need to store a series of vectors, to store nodes and edges, and a data structure to keep the relationship between 
nodes and edges. 

For that, at least there are needed implementations of the functions: 

- insertVertex(K key)                        //insert a node, given some key
- insertEdge(Vertex v1, Vertex v2, K key)    //insert and edge between nodes v1 and v2, and with a data associated key
- removeVertex(Vertex v)
- removeEdge(Vertex v1, Vertex v2)
- incidentEdges(Vertex v)                    // report the edges of a given vertex
- areAdjacent(Vertex v1, Vertex v2)          // check if vertices v1 and v2 are adjacent
- origin(Edge e)                             // in case the edge is directionl
- destination(Edge e)                         // in case the edge is directionl

#### Edge list implementation

This is a very simple implementation. There are a list of vertices and other list of edges. 

So for the graph:

```
       U 
   a /   \ c
    /     \     d
   V ----- W ------ Z
       b
```

 So in the list of vertices, we 
 
 ``` 
  vertex 
  list             edges list 
  
     U           | U | V | a | 
     V           | V | W | b | 
     W           | U | W | c | 
     Z           | W | Z | d | 
	
 ```
 
 So for inserting a new node, it only needs to be added to the vertices list (operation O(1)), for example a new vertex K: 
 
 ``` 
  vertex 
  list             edges list 
  
     U           | U | V | a | 
     V           | V | W | b | 
     W           | U | W | c | 
     Z           | W | Z | d | 
	 
 ```
 
 If we want to know if two vertices are adjancent, it is needed to check all the edges lists. This is O(m) operation. 'm' is the number of edges in the graph. 
 
 To calculate the number of incident edges on a vertex, it is needed also to check all the elements in the edges list. Also an O(m) operation. 
 
 So this implementations actually runs very fast to insert nodes, but to get relational information about the nodes/edges takes a lot of time (O(m)).
 
 
 #### adjacent matrix implementation
 
 In this case the graph is represented by means of adjacent matrix.
 
 The vertex list is still needed, (implemented as a hash table, so it has O(1) access time), and also the edge list is also needed.
 
 So for the graph:

```
       U 
   a /   \ c
    /     \     d
   V ----- W ------ Z
       b
```

The adjancent matrix, would have a 0 (false) value, in case of two vertices that are not adjacent, 
and a 1 (true) in case both vertices are adjacent. Only the upper triangle is needed for non directed edges. 

```
          U    V   W   Z 

    U     0    1   1   0           
	
	V          0   1   0         
	
	W              0   1 
	
	Z                  0
	
````

And improventent in this structure, is instead of using only a 1, it would be better, to place a pointer to the 
edge list. And in that edge list, would be specified the nodes that belong to that edge. 

```
          U    V   W   Z 

    U     0    &a  &c  0           
	
	V          0   &b  0         
	
	W              0  &d 
	
	Z                  0
	
   vertex 
  list             edges list 
  
     U            | U | V | a | 
     V            | V | W | b | 
     W            | U | W | c | 
     Z            | W | Z | d | 
	 
	
````

This will make the operations needed much faster. 

InsertVertex(): That would need add a row in the vertex list, but also a row and column to the matrix. So this is O(n). 

RemoveVertex(): The same that insertVertex in reverse, so O(n).

AreAdjacent(): This is much faster, it is only check an index. It is constant time O(1)

IncidentEdges(): This is only read the entire column, and the entire row in the matrix. And there are the vertices. This is 2*n , that is O(n) 


 
 #### Adjacent list implementation
 
 
 This implementation conbines features of the two previous implementations. It has a vertex list, implemented as a hash table, so it has O(1) 
access time.  And also the edge list. But in this adjancent list implementation, there is going to ber linked list of all edges (pointers to the edges), of a given vertex.
 
 
  ``` 
  vertex    adjacent            
  list      list                   edges list 
		              
     U  -> &a -> &v                 | &U | &V | a | 
     V  -> &a -> &b                 | &V | &W | b | 
     W  -> &c -> &b -> &d           | &U | &W | c | 
     Z  -> &d                       | &W | &Z | d | 
		              
 ```
 
 So in the linked list there are pointers to the edge list, and in the edge list we have pointers to the vertex list. 
 
 
 Lets evaluate the performance for the operations.
 
 
 InsertVertex(): to insert a new vertex, a new element has to be added to the vertex list. Initally we don't have to create an initial linked list,
 because it will be a null pointer. So it would be O(1)* in amortized time.
 
 RemoveVertex(): removing a vertex will not be just removing a given vertex, but also clean the structure fo all the edges, so it is needed to check all the vertices, and all 
 its associated nodes. So this operation would be in the order of degrees of the vertex that wants to be removed: O(deg(v))

 AreAdjacent(v1,v2): The v1 adjacent list needs to be checked, and check if any of the edges in v1 points to a edge that also cointains v2. Or the other way around, check the 
v2's adjacent edges list, to check if any of the edges also contains v1. So the time will be dependand on either  the degree of v1, or the degree of v2, so the overall time
would be the min(deg(v1), deg(v2)) 

 IncidentEdges(v): It is only needed to walk the linked list of the edge. This will be an order of O(deg(v)) 
 

#### graphs implementations comparative

 
  O()                  |  Edge list  |  Adjacent Matrix | Adjacent List     |  
 ---------------------------------------------------------------------------| 
  Space                |    n+m      |         n^2      |        n+m        |   
  InsertVertex(v)      |      1      |          n       |      1            |   
  removeVertex(v)      |      m      |          n       |      deg(v)       |    -> considering removing the edges, and also removing the associated edges.
  insertEdge(v, w, k)  |      1      |          1       |      1            |   
  removeEdge(v,w)      |      1      |          1       |      1            |   
  incidentEdges(v)     |      m      |          n       |      deg(v)       |   
  areAdjacent(v,w)     |      m      |          1       | min(deg(v),deg(w))|   

 The take away is that depending on the desired performance, one implmentation may be better that the others.
 
 If the areAdjacet() operation is the most intereting to us, the Adjacent matrix operation, is the implementation with the best running time.
 
 If inserting and removing edges, is the most interesting operation, then, the adjancent list implementation would be the best option, or even edge list.
 
 
 
 
 
 


 
 
