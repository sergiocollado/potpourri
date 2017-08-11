# HASH FUNCTIONS

## Use:

Hash functions have many applications, one of the most common, is to apply them to recognice files, objects, data or messages, because the hash function is intended to be smaller that its original source, so the origina can be much bigger, and in that way it is used as a 'message digest'.

## Hash Propierties:

The hash function is represented as H(). So for a data x, it's hash function is H(x).

Is a mathematical function with 3 propierties:

- It can take as input any string of any length
- It outputs always a string of fixed size
- Its effiently computable

Its security propierties are:

- collision free
- hiding
- puzzle friendly

### Collision free.

No body can find two values: x and y; So x != y and H(x)= H(y) 

That means, it is impossible to find two inputs X and Y, that H(X) equals H(Y). Notice the statement 'is impossible to find', because actually, there are collitions, meaning, that collitions, DO exists. The point is that they cannot be found.

If we assume that we are using a Hash function that is collision free, we can use that Hash function as a message digest, meaning, that we
have a file, and we want to know if we see it again in the future, we could just store initial file, and store it, and compute it. Or we can
just store the Hash of the file, and supouse that if we find another file, with the same Hash, then it is equal to the first file.

No body can find two values: x and y; So x != y and H(x)= H(y) 

### Hiding

We can concatenate x with r (r|x), that is, r is from a probability distribution very spread out. So given H(r|x) is infeasible to find x.

### Commitment

Its usefull to check the validity of a message: 

#### 1

First we use a publication function, 'commit message': </br>

A random value, knwon as a _**key**_ is generated for its use, concatenating it with the message.

note: the vertical bar '|' stands for concatenation.

>> (com,msg) := com := commit(msg) := (H(key|msg),key)  

That commit, represents a message, that is infearseble to deduce its original meaning.

So, it has the 'hiding' securty propiertie: given 'com' [com = H(key|msg)]  is infearsible to know 'msg'


#### 2

Then we can publish the key, and the message, then the previous commit can be verified:


#### 3

For that the verification function 'verify()' is used, and it's return value will be _**true**_ or _**false**_: 

note: the vertical bar '|' stands for concatenation.

>> match (true or false) := ( verify(com, key, msg) := [H(key|msg) == com] )

This holds to the 'Binding' security propierty: It is infeasible to find another message (msg'), for msg' != msg, that
the commintment is the same with the same key: H(key|msg') == H(key|msg).


#### Security propierties:

Hiding: Given a commintment, H(key|msg) is infeaseble to find msg. 

Binding: is infeaseble to find a msg'!= msg that: H(key,msg) == H(key,msg\').

Puzzle-friendly: For every possible output value _y_, if a random input _k_ is chosen from a very spread out distribution,
then it is infeasible to find _x_, such H(key,_x_) = _y_.

# Commonly use hashes:

- SHA: Secure Hash Algorithm
- MD5: 

# Some libraries for C programming that implement Hash:

- uthash [:link:](http://troydhanson.github.io/uthash/index.html)
- Judy [:link:](http://judy.sourceforge.net/)
- SGLIB [:link:](http://judy.sourceforge.net/)


