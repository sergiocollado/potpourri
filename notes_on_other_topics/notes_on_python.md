
# NOTES ON PYTHON

## Looking for help()

If help or reference is needed, you can type: `help()` -- dont forget the parenthesys.

## BLOCKS

Blocks of code are indicated in python by means of indentation. Blocks of code, are what is inside the curly braces in C/C++

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


reference: https://www.python-course.eu/python3_variables.php

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

