

Uninformed search, refers to the fact that the intelligent agent, doen't know in advance the searching space. 

For representing the searching space, usually a tree structure (root, branches and leafs) are used.

There are several common methods to use:

- Breath first search (BFS) - seach advances on the shallowest node
- Depth-first search (DFS) - search advances on the deepest node
- Depth limited search (DLS) - Depth-first search with depth limit. 
- Uniform cost search - seach advances on less expensive node. this assumes the edges of a tree have different costs.

## BFS - BREADTH FIRST SEARCH

```
ALGORITHM BREADTH FIRST SEARCH:
=============================

function BFS(initial_node, goal)

  //the 'frontier' set is the groups of nodes pending to search/explore.
  //the 'frontier' set needs to be a FIFO (Firt-In, First-Out), thus a queue structure.
  frontier = new Queue();
  frontier.enqueue(initial_state);
  
  //the 'explored' set is the nodes already checked.
  explored = new Set();
  
  //the search will go on until all the nodes are checked
  WHILE NOT( frontier.IsEmpty() ):
  
       //we take out one of the frontier nodes
       current_node = frontier.dequeue();
       
       //we add to the 'explored' set, the current selected node
       explorer.add_nodes(current_node);
       
       //we check if the selected node is the goal.
        IF goal == current_node.IsGoal();
             return SUCCEED(current_node) //the search has succesfully finished.
             
        //in the case the selected node is not the goal, then
        //we add all its neigbours to the 'frontier' set, only
        //if they haven't been already visited.
        
        FORALL neighbour IN current_node.neighbours():
           IF neighbour (NOT_IN frontier) AND (NOT_IN explored):
               frontier.enqueue(current_node)

  //if we have searched all the nodes, and the goals hasn't been found
  //we return failure in the search
  return FAILURE
```

## DFS - DEPTH FIRST SEARCH


```
ALGORITHM  DEPTH-FIRTS-SEARCH
=============================

function DFS(initial_node, goal)

  //the 'frontier' set is the groups of nodes pending to search/explore.
  //the 'frontier' set needs to be a LIFO (Last-In, First-Out), thus a stack structure.
  frontier = new Stack();
  frontier.push(initial_node);
  
  //the 'explored' set is the nodes already checked.
  explored = new Set();
  
  //the search will go on until all the nodes are checked
  WHILE NOT( frontier.IsEmpty() ):
  
       //we take out one of the frontier nodes
       current_node = frontier.pop();
       
       //we add to the 'explored' set, the current selected node
       explorer.add_nodes(current_node);
       
       //we check if the selected node is the goal.
        IF goal == current_node.IsGoal();
             return SUCCEED(current_node) //the search has succesfully finished.
             
        //in the case the selected node is not the goal, then
        //we add all its neigbours to the 'frontier' set, only
        //if they haven't been already visited.
        
        FORALL neighbour IN current_node.neighbours():
           IF neighbour (NOT_IN frontier) AND (NOT_IN explored):
               frontier.push(current_node)

  //if we have searched all the nodes, and the goals hasn't been found
  //we return failure in the search
  return FAILURE
```
