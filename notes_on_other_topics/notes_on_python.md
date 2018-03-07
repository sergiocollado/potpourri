
# NOTES ON PYTHON

The main reference is:  https://docs.python.org/3/library/index.html

Other reference: http://docs.python-guide.org/en/

## Looking for help()

If help or reference is needed, you can type: `help()` -- dont forget the parenthesys.

```python
>>> help()

Welcome to Python 3.6's help utility!

If this is your first time using Python, you should definitely check out
the tutorial on the Internet at http://docs.python.org/3.6/tutorial/.

Enter the name of any module, keyword, or topic to get help on writing
Python programs and using Python modules.  To quit this help utility and
return to the interpreter, just type "quit".

To get a list of available modules, keywords, symbols, or topics, type
"modules", "keywords", "symbols", or "topics".  Each module also comes
with a one-line summary of what it does; to list the modules whose name
or summary contain a given string such as "spam", type "modules spam".

help> 
```


Also there is great documentation at:  https://docs.python.org/3/library/index.html


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

- **booleans**: **True** and **False**
- **integers** (base 10): 16
- **octals** (base 8): 0o100 (this is 16 in decimal)
- **hexadecimal** (base 16): 0x10 
- **binary** (base 2): 0b00010000
- **floating point**: 3.14159
- **complex numbers**: 1 + j

With the functions: **bin(), oct(), hex()** - you can convert the numbers to its string representation.

With the function: **int()** - you can convert a string into its corresponding number.

With the function: **str()** - you can convert a number to a string type.

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

 - **concatenation**: the + operator
 ```python
 message = 'Hello' + 'World!'
'HelloWold!' //you should had written and space ;)
```

 - **repetition**: the * (number) operator
 ```python
 message_2 = 'tic tac ' * 4 
 tic tac tic tac tic tac tic tac
```

 - **slicing**: the [ num1 : num2 ] operator. The characters from num1 to num2, the num2 character is not included.
```python
>>>message_3 = 'Hello Wold!'
 >>>message_3[0:5] //the 5 is not included. 
 'Hello' 
```


  - **spliting**:  It is possible to siplit strings
  
```python
>>myString="hello world"
>>myString.split(' ')
>>['hello', 'world']
```
this answer is idexed, so it is possible to do:

```python
>>myString="hello world"
>>myString.split(' ')[1]
>>'hello'
```
 - **lenght of the string**: len(string)
 ```python
 >>> len('hello')
 5
```

##### Strings are inmutable

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

Lists in python are a sequenced and **ordered** group of objects, they can be of any type, and even is possible, that they can be nestested lists (or sublists) as elements of lists. Those elements can be edited, and changed in value, and they are accessed through its index.

they are defined, as follows:

```python
>>numberlist = [ 'one' , 2 , '3']
```

 - **slicing**
 
```python
>>first_two = numberlist[0:2]
>>print(first_two)
>>['one', 2]
>>last_two = numberlist[:-2]
>>print(last_two)
>>[2,'3']
```
  
you can also jump every other step according to the structure: list[start:end:step]

 - **length**
 
```python
>> len(numberlist)
>> 3
```

 - **concatenations**: is possible to concatenate list with the '+' operator. the '+=' operator also works.
 
 ```python
 >> list_concatenated = list_one + list_two
 ```
 
 - **extensions**: is possible also to use the method '.extend()' to expand a list.
 
  ```python
 >> male_names = ['John', 'Seamus', 'Richard']
 >> female_names =  ['Carol', 'Ameee', 'Leanne']
 >> names = female_names
 >> names 
 >> ['Carol', 'Amee', 'Leanne']
 >> names.extend(male_names)
 >> names
 >> ['Carol', 'Amee', 'Leanne', 'John', 'Seamus', 'Richard']
 ```
 
  - **element existence**: to check if an element is contained in a list or not, the operators 'in' and 'not in' are used.
  
  ```python
 >>names = ['John', 'Seamus', 'Richard']
 >> 'John' in names
 >> True
 >> 'Anne' not in names
 >> True
 >> Silvie in names
 >> False
 ```
 - **repetitions**: Is possible the repetition with the operator '*'
 
```python
>>clock = ['tick', 'tack']
>>two_clocks = clock*2
>>print(two_clocks)
>>['tick', 'tack','tick', 'tack']
```
 - **append elements**: to append a new element to the list, the .append() method is used:
 
 ```python
  >>names = ['John', 'Seamus', 'Richard']
  >>names.append('James')
  >>names
  >> ['John', 'Seamus', 'Richard', 'James']
  ```
  Watch out! if you append a list to a list, it will be added as a sublist. If it is what you were looking for, thats good, but,
  if you wanted to just add the two list, you should had used the .extend() method or the '+' operator.
  
  - **inserting elements**: is possible to insert a new element at a given position with the method: .insert(index, element)
  
   ```python
  >>names = ['John', 'Seamus', 'Richard']
  >>names.insert(1,'Charles')
  >>names
  >> ['John','Charles', 'Seamus', 'Richard', 'James']
  ```
  
  - **retrieving the ith element**: for getting the ith element of the list, 'pop()' is used. It returns the ith element, and removes it from the list.
  
  ```python
  >>names = ['John', 'Seamus', 'Richard']
  >>names.pop(0)
  >> 'John'
  >> names
  ['Seamus', 'Richard']
  ``` 
  
 In case the element of that index don't exists, or the list is empty, then and IndexErrorException is raised.
 
 In case .pop() is called without an argument, it returns the last element in the list. 
 
 In case is called with .pop(-1) also the last element of the list is returned, as negative indexing is used.
 
- **removing** it is possible to remove an element, without knowing its index, as:

```python
>> names =  ['Carol', 'Amee', 'Leanne', 'John', 'Seamus', 'Richard']
>> names.remove('Leanne')
>> names
>>  ['Carol', 'Ameee', 'John', 'Seamus', 'Richard']
```

If the value doen't exist you will get a ValueError.

- **index of an element** to get the index of a given element, with the method '.index(element, start_index, end_index)'

```python
>> names =  ['Carol', 'Amee', 'Leanne', 'John', 'Seamus', 'Richard']
>> names.index('Amee')
>> 1
```

An ValueError will be raised if the element is not present.


#### Tuples

Tuples are inmutable lists, once they are defined its elements cannot be changed. They are defined as the lists, but with parenthesis.

tuples are defined as follows:
```python
numbertuple = ('one' , 2 , '3')
```

## FUNCTIONS

Functions are defined by the keyword `def` followed by the functions name, the parameters list, and a colon. The code that is the function, must be indented.

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
## USING LIBRARIES

For using libraries, it is need to declare it with the code word: **import** ... **as**

```python
import Super_library as S_lib
```

reference: https://docs.python.org/3.0/library/index.html


some frequently used, are:

<hr>

```python
import sys
```
reference:  https://docs.python.org/3.0/library/sys.html

this module, adds functions to interact with the python interpreter, as:

```python
sys.arg 
```
returns the number of parameters passed to the python script

```python
sys.exc_info()
```
returns info about the triggered exception

```python
sys.path
```
a list that points to the location path of modules

```python
sys.platform
```
returns identification about the system platform (window, mac, linux)

```python
sys.settrace(function)
```
usefull to work out a debugger
<hr>



## WRITTING SCRIPTS

At least in linux, you have to put in the first line:

```bash
#!/usr/bin/env python
```


## installing mqtt

reference: https://pypi.python.org/pypi/paho-mqtt/1.1

reference: http://www.steves-internet-guide.com/into-mqtt-python-client/

```
$ pip3 install paho-mqtt
Collecting paho-mqtt
  Downloading https://www.piwheels.hostedpi.com/simple/paho-mqtt/paho_mqtt-1.3.1-py3-none-any.whl (57kB)
Installing collected packages: paho-mqtt
Successfully installed paho-mqtt-1.3.1
```
