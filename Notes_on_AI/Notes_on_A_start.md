Notes on A* (A star) algorithm - Path finding algorithm-
====================================================================

Lets assume we have an mapped area and we want to go from a starting point A, to a point B, and for simplicity, lets assume all,
except a wall in the middle of those two points is clear (we can move to any point, except for those points that are from the wall),
of course we cannot move through the wall.

```
+----+----+----+----+----+----+----+----+----+
|    |    |    |    |    |    |    |    |    |
+----+----+----+----+----+----+----+----+----+
|    |    |    |    | W  |    |    |    |    |
+----+----+----+----+----+----+----+----+----+
|    |    |    |    | W  |    |    |    |    |
+----+----+----+----+----+----+----+----+----+
|    |  A |    |    | W  |    |    | B  |    |
+----+----+----+----+----+----+----+----+----+
|    |    |    |    | W  |    |    |    |    |
+----+----+----+----+----+----+----+----+----+
|    |    |    |    | W  |    |    |    |    |
+----+----+----+----+----+----+----+----+----+
|    |    |    |    |    |    |    |    |    |
+----+----+----+----+----+----+----+----+----+
```

We have to divide the map into a grid, to be able to evaluate the 'terrain', also with this, we simplify the map, so now we can
represent it by an actual 2D array of coordenates or nodes. The objective is clear, to figure out, what path of nodes we have to
follow to go from point A to point B. 


The next step is to launch a search to find the shortest path possible. We start at point A, and check all the adjacent nodes,
and then we search outwards, until the path is found.

The search process is as follows:

We start at node A, and add it to an open list, where we will keep an account of the nodes, that are candidates, to belong to the desired path.

> open list (it=0):
> > (0,0) = A
	
We look at the valid (walkable) adjacent nodes of A - nodes that belong to the wall, are not valid nodes-. We add those nodes at
the list of candidates. For each of those nodes, we keep track of the origin nodes (or parent node), where it moves from. At this point is the node A.
	
>open list (it=0):
> (0,0) = A
> (0,1)
> (-1,1)
> (-1,0)
> (-1,-1)
> (0,-1)
> (1,-1)
> (1,0)
> (1,1)	

 The coordinates (x,y) are:

```
+----+----+----+
|-1,1|0, 1| 1,1|
+----+----+----+
|-1,0|  A | 0,1|
+----+----+----+
|--1 |0,-1|1,-1|
+----+----+----+	
```

(1)- Remove the parent node, A, from the open list, because we don't need to check that node again.
	
>open list (it=0):
  > (0,1)
  > (-1,1)
  > (-1,0)
  > (-1,-1)
  > (0,-1)
  > (1,-1)
  > (1,0)
  > (1,1)	
  
(2)- Next, we choose on the nodes of the open list, and repeat the process of adding its adjacent nodes. But, how do we choose the correct node? - We evaluate it with a cost function (a figure of merit or parameter that let us compare how good that move is). We will choose the next node, that one that evaluates to the lowest cost function value.
	
The cost function is based on:
	
F = G + H
	
where:
	
 - G, is the movement cost from the starting node A, to the node we are evaluating on the map.
	 
 - H, is an estimation of the movement cost from that node, to the final destination node B. The term estimation, it actually
	 means that its a sort of guess, and of course, there are many ways to implement this function.
	
 - F, is the general cost function value, that accounts, for the path already covered up to the current node (G), and how far is the destination point (H).
	 
So, the path is generated, by actually going through all the open list, and then choosing the path with the lowest F cost.
	
As example, for the movement cost to an adjacent node, we can just simply have a cost of 10 units, for vertical and horizontal,
moves, and 14, for diagonal movements. Just for simplicity, because we are considering a squared grid.
	
For calculating the G, of a given node, we have to add, the last movement to the G cost of its parent node.
	
In the firs iteration, the cost G of the node A, is 0.
	
The values for the movement cost function from the starting point: G, for first iteration are:

```
+----+----+----+
| 14 | 10 | 14 |
+----+----+----+
| 10 | A  | 10 |
+----+----+----+
| 14 | 10 | 14 |
+----+----+----+
```
	
To estimate H, we can use, what is named: 'the Manhattan distance', that is the movement cost of the sum of all the horizontal moves needed to reach the end point B, plus, the movement cost of all the vertical moves to reach B. It's named Manhattan distance, because, is just like calculating the number of city blocks, you have to move in Manhattan -where you cannot cut across diagonals- to reach a destination. You don't need to implement this distance allways, in other cases, is better to consider, otherestimation methods.
	
The values for the estimation distance to the destination node: H, for the first iteration are:

```
+----+----+----+
| 71 | 70 | 60 |
+----+----+----+
| 70 |  A | 50 |
+----+----+----+
| 71 | 70 | 60 |
+----+----+----+	
```

where:

 50 = 5 h * 10 + 0 v * 10
 60 = 5 h * 10 + 1 v * 10
 70 = 7 h * 10 + 0 v * 10
 71 = 7 h * 10 + 1 v * 10
	
where: h stands for horizontal move, and v for vertical move.
 
According to the cost function:    F = G + H
	
The values of the cost function F, for the first iteration:
	
```
+----+----+----+
| 85 | 80 | 64 |
+----+----+----+
| 80 | A  | 60 |
+----+----+----+
| 85 | 80 | 64 |
+----+----+----+		
```

This kind of algorithm, is named an heuristic method, or heuristic search, because it develops, based on previous calculations, in iterative way.

(4)-To continue the search we choose the node with the lowest cost F, that is the node (1,0), just to the right of the starting point A, with a cost value of 60 units.
  
>open list (it=0):
  > (0,1)		F= 80
  > (-1,1)		F= 85
  > (-1,0)		F= 80
  > (-1,-1)		F= 85
  > (0,-1)		F= 80
  > (1,-1)		F= 64
  > (1,0)		F= 60  << selected node.
  > (1,1)		F= 64
  
Then we start the main/general loop of the algorithm:

[Main_loop:]

  (1)- We remove the selected node from the open list.
	
  (2)- The algorithm loop is repeated: all the adjacent nodes of the current selected node, are evaluated according to the cost functions, to evaluate which one will be the most appropiate. Invalid nodes - those belonging to the wall, won't be evaluated, as they are supposed to be not valid nodes-.
  
  (3)- Check if the evaluated node, is in the open list; it could be the case, where we find a path, that is better (lower cost, that is lower F), than in a previous calculation/iteration/path. If is not in the open list, nothing to do is needed, but if it is already on the list, you have to consider if the actual path calculation is better that the previous one (check the F value). If the path indeed is better, then you have to re-score it.
  
  (4)- Once all the adjacent nodes are evaluated, we choose the lower cost node, as the next node.
  
  
For the current case exposed, the selected node, was the A1(1,0) node. Node A is not longer in the open list, and the selected node is also removed, so the open list at iteration 1 would be:
 
> open list (it=1):
  > (0,1)		F= 80
  > (-1,1)		F= 85
  > (-1,0)		F= 80
  > (-1,-1)		F= 85
  > (0,-1)		F= 80
  > (1,-1)		F= 64
  > (1,1)		F= 64
  > - to be added nodes adjacent to A1(1,0)
  > (1,1)
  > (0,1)
  > (0,-1)
  > (1,-1)
  > (2,-1)
  > (2,0)
  > (2,1)

The coordenates (x,y) of the nodes are mapped:
  
```
+----+----+----+----+
|-1,1|0, 1| 1,1| 2,1|
+----+----+----+----+
|-1,0|  A | A1 | 2,0|
+----+----+----+----+
|--1 |0,-1|1,-1|2,-1|
+----+----+----+----+	
```

So then in the second iteration, for G we would have:

```
+----+----+----+
| 24 | 20 | 24 |
+----+----+----+
|  A | 10 | 20 |
+----+----+----+
| 24 | 20 | 24 |
+----+----+----+
```

Were G = G_parent + cost of movement:

so:

  24 = 10 + 14 //diagonal movement
  20 = 10 + 10 //vertical or horizontal movement.
  
And for H, we would have:

```
+----+----+----+
| 60 | 50 | 50 |
+----+----+----+
|  A |  X | 40 | 
+----+----+----+
| 60 | 60 | 50 |
+----+----+----+
```

So the cost function F, for the second iteration (it=1), would be:

```
+----+----+----+
| 84 | 70 | 74 |
+----+----+----+
|  A |  X | 60 | 
+----+----+----+
| 84 | 70 | 74 |
+----+----+----+
 ```
 
One we have F, we have to check if any of the points involved, already are in the open list. Actually there are points, which 
already are in the open list, but none of it, improves its previous funtion cost record.
 
If we remember the cost values the previous iteration (it=0).

```
+----+----+----+
| 80 | 64 |    |
+----+----+----+
| A  | 60 |    |
+----+----+----+
| 80 | 64 |    |
+----+----+----+	
```

 open list (it=1):
  > (0,1)		F= 80
  > (-1,1)		F= 85
  > (-1,0)		F= 80
  > (-1,-1)		F= 85  
  > (0,-1)		F= 80
  > (1,-1)		F= 64	<< repeated
  > (1,1)		F= 64   << repeated
  to be added nodes adjacent to A1(1,0)
  > (1,1)		F= 70	<<repeated
  > (0,1)		F= 74
  > (0,-1)		F= 84
  > (1,-1)		F= 70	<< repeated
  > (2,-1)		F= 74
  > (2,0)		F= 60
  > (2,1)		F= 74
  
 As stated, no node, improves it previous cost function. So in this case, we don't have to update its value.

 So then, is clear that the next point to select is the point just to the right of the previous one, which has the lowest cost function of 60 units. Once the next point is choosen, we actually can keep repeating the loop in the algorithm, until the destination is reached.
 
 
 
