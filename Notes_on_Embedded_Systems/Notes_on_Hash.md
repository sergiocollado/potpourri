# HASH FUNCTIONS

Is a mathematical function with 3 propierties:
- It can take as input any string of any length
- It outputs always a string of fixed size
- Its effiently computable

Its security propierties are:
- collision free
- hiding
- puzzle friendly

## Collision free.

There is impossible to find two inputs X and Y, that H(X) equals H(Y). Notice the statement 'is impossible to find', because actually, 
there are collitions, meaning, that collitions, DO exists. The point is that it can not be found.

If we assume that we are using a Hash function that is collision free, we can use that Hash function as a message digest, meaning, that we
have a file, and we want to know if we see it again in the future, we could just store initial file, and store it, and compute it. Or we can
just store the Hash of the file, and supouse that if we find another file, with the same Hash, then it is equal to the first file.

## Hiding

We can concatenate x with r (r|x), that is, r is from a probability distribution very spread out. So given H(r|x) is infeasible to find x.

### Commitment
Its usefull to check the validity of a message: </br>

First we use a publication function, 'commit message': </br>
(com,msg) := com := commit(msg) := (H(key|msg),key) //'key' is a random 256 value.

The we have a verification function 'verify': </br>
match (true or false) := verify(com, key, msg) := [H(key|msg) == com]

Security propierties:

Hiding: Given a commintment, H(key|msg) is infeaseble to find msg. </br>
Binding: is infeaseble to finde a msg\'!= msg that: H(key,msg) == H(key,msg\') </br>
Puzzle-friendly: For every possible output value y, if a random input k is chosen from a very spread out distribution,
then it is infeasible to find x, such H(key,x) = y.
