
# NOTES ON PYTHON

## Looking for help()

If help or reference is needed, you can type: `help()` -- dont forget the parenthesys.

## BLOCKS

Blocks of code are indicated in python by means of indentation. Blocks of code, are, what is inside the curly braces in C/C++

Blocks are commonly used in code flow control structures as for loops, do loops, or conditional loops (if's)- Conditions must end with a colon (':').

## DATA, VARIABLES AND OBJECTS

In python there is no data declaration (as in C: `int x;`), also the data representation automatically handled

```python
x = 42
x = x + 1
print(x)

>> 43
```

```python
x = 42           //data declared implicity as integer
x = x + 0.1      //data cast to float
x = "hello wold"    //data cast to string
```

This dynamic casting is done by means of defining objects. You can check the object referenced by a variable with the `id()` function.

### Core data types

#### Numbers

- **integers** (base 10): 16
- **octals** (base 8): 0o100 (this is 16 in decimal
- **hexadecimal** (base 16): 0x10 
- **binary** (base 2): 0b00010000
- **floating point**: 3.14159
- **complex numbers**: 1 + j

With the functions: **bin(), oct(), hex()** - you can convert the numbers to its string representation.

With the function: **int()** - you can convert a string into its corresponding number.

#### Strings

Strings are defined either with single or double quotes. If a quote is needed inside the string it can be scaped with a backslash '\'

```python
string_1 = "hello world!"
string_2 = 'hello to you!'
string_3 = 'I\'m here!'
```

Also, multiline strings can be defined by enclosing them in triple quoutes

```python
message = 
'''Hello,
my name is
Iñigo Montoya'''
```

Single carcaters inside a string can be retrieved by indexing from the start, or from the end (with a negative number).
Indexing starts at 0 and -1.

```python
my_string = 'Hello Wold!'

>>> my_string[0] 
'H'
>>> my_string[4]
'o'
>>> my_string[-1]
'!'
>>> my_string[-5]
'W'
 ```
 
##### basic string functions     

 - concatenation: the + operator
 ```python
 message = 'Hello' + 'World!'
'HelloWold!' //you should had written and space ;)
```

 - repetition: the * (number) operator
 ```python
 message_2 = 'tic tac ' * 4 
 tic tac tic tac tic tac tic tac
```

 - slicing: the [ num1 : num2 ] operator. The characters from num1 to num2, the num2 character is not included.
```python
>>>message_3 = 'Hello Wold!'
 >>>message_3[0:5] //the 5 is not included. 
 'Hello' 
```

 - lenght of the string: len(string)
 ```python
 >>> len('hello')
 5
```

##### Inmutable strings

Like in java or c# strings cannot be edited. so I you try to reasignate it, you will get an error

```python
>>>mystring = 'hello'
>>>mystring[4] = '!'
Traceback (most recent call last):
File "<stdin>", line 1, in <module>
TypeError: 'str' object does not support item assignment
```

But asignation to a new object is ok. Because the variable is a reference to an object
so the following is ok:

```python
>>>my_message = 'hello!'
>>>my_message = 'hi there!'
```
remember You can check the object referenced by a variable with the `id()` function.

 
reference: https://www.python-course.eu/python3_variables.php

#### Lists

Lists in python are a sequenced and ordered group of objects, they can be of any type, and even is possible, that they can be nestested
lists as elements of lists. Those elements can be edited, and changed in value, and they are accessed through its index.



## FUNCTIONS

Functions are defined by the keyword `def`

```python
def foo(parameter_lit):
   operation1
   operation2
   ...
   operation_n
```

### OPTIONAL PARAMETERS and DEFAULT VALUES



## Execution of a python file, giving parameters:

You need to define the system library for that:

```python
import sys
```

then define the function:

```python
def hello(a,b):
    print 'hello and thats your sum:'
    sum=a+b
    print sum
```

and to take the arguments:

```
if __name__ == "__main__":
    hello(sys.argv[1], sys.argv[2])
```

so all the file is like:

```python
import sys

def hello(a,b):
    print 'hello and thats your sum:'
    sum=a+b
    print sum

if __name__ == "__main__":
    hello(sys.argv[1], sys.argv[2])
```

You can call the file inside the python IDE, but if you call it from a console, you have to call th epython intepreter previously like:

```python
>>> python hello.py 1,1
```

