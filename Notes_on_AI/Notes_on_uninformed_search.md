

Uninformed search, refers to the fact that the intelligent agent, doen't know in advance the searching space. 

For representing the searching space, usually a tree structure (root, branches and leafs) are used.

There are several common methods to use:

- Breath first search (BFS) - expands the shallowest node
- Depth-first search (DFS) - expands the deepest node
- Depth limited search (DLS) - Depth-first search with depth limit. 
- Uniform cost search - expands the less expensive node.

## BFS - BREADTH FIRST SEARCH

```
ALGORITHM BRADTH FIRST SEARCH:
=============================

function BFS(initial_state, goal)

  frontier = new Queue();
  frontier.enqueue(initial_state);
  
  explored = new Set();
  
  WHILE NOT frontier.IsEmpty():
       state = frontier.dequeue();
       explorer.add_nodes(state);
       
        IF goal = state.IsGoal();
             return SUCCEED(state)
             
        
        FORALL neighbour IN state.neighbours():
           IF neighbour (NOT_IN frontier) AND (NOT_IN explored):
               frontier.enqueue(state)

  return FAILURE
```

