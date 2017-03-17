# NOTES ON AIML

AIML stands for Artificial Intelligence Mark-up Languaje, it was developed for a chat-bot named A.L.I.C.E (Artificial Linguistic Internet Computer Entity)[:link:](http://www.alicebot.org/).


## BASIC CONCEPTS:

AIML defines a classes of objects called AIMLs, and are made of __**units**__ and __**categories**__. AIMLs objects contain, the stimoulus
-response of the AI.

### _**CATEGORIES**_

_**Categories**_ are the basic unit of kwnolegde, each one, is made of a question (the stimulus or _**pattern**_), an answer (also refered
as the _**template**_), and an optional _**context**_: there are two types _**'that'**_ and _**'topic'**_. _**that**_ refers to the
previous answer of the bot, and _**topic**_ is a general group of categories.

```
Categories 
         L__ pattern   (stimoulus - question)
         |
         L__ template  (reply - answer) 
         |
         L__ context   (optional)
                |
                L__ that
                |
                L__ topic

```


The AIML __**pattern**__ is simple it just consists on words, and two wildcard symbols _ and *. The __**template**__ uses the tags, 
to run a program, that react to the __**pattern**__.

AIML is heavily based on the \<srai\ tag, that implements recursion.

### RECURSION

There are several options:

 1. Simbolic recursion: Simplifies the grammar 
 2. Divide and conquer: divides the input in two parts, and combines the response of the two.
 3. Synonims: Maps different ways to say the same.
 4. Handle spellings or grammar corrections.
 5. Detection of keywords.
 6. Conditionals: implements branching 
 7. Any combination of the above mentioned: (1)-(6).
 
### Simbolic recursion

```XML
<category>
<pattern>DO YOU KNOW WHO * IS</pattern>
<template><srai>WHO IS <star/></srai></template>
</category>
```

The * is the wildcaracter, whenever the question matches:

- 'Do you know who Maxwell is?'
- 'Who Maxwell is?'

- 'Do yoy know who XXXX is?'
- 'Who XXXX is?'

### Divide and conquer

Some structures, as in a sentece that starts with 'Yes, ...'  is usually divisible in two sentences.

```xml
<category> 
<pattern>YES *</pattern> 
<template><srai>YES</srai> <sr/></template> 
</category>
```

The markup \<sr/\> is simply an abbreviation for \<srai\>\<star/\>\</srai\>.

### Synonims

```xml
<category> 
<pattern>HELLO</pattern> 
<template>Hi there!</template> 
</category>

<category>
<pattern>HI</pattern> 
<template><srai>HELLO</srai></template>
</category>

<category>
<pattern>HI THERE</pattern> 
<template><srai>HELLO</srai></template>
</category>

<category>
<pattern>HOLA</pattern> 
<template><srai>HELLO</srai></template>
</category>
```

### Spelling and grammar correction

```xml
<category>
<pattern>YOUR A *</pattern>
<template>I think you mean "you’re" or "you are" not "your." 
<srai>YOU ARE A <star/></srai>
</template>
</category>
``` 

Here, the bot trolls the user as a languaje policeman.

### Keywords

```xml
<category>
<pattern>MOTHER</pattern> 
<template> Tell me more about your family. </template>
</category>

<category>
<pattern>_ MOTHER</pattern> 
<template><srai>MOTHER</srai></template>
</category>

<category>
<pattern>MOTHER _</pattern>
<template><srai>MOTHER</srai></template>
</category>

<category>
<pattern>_ MOTHER *</pattern>
<template><srai>MOTHER</srai></template>
</category>
```

### Conditionals

```xml
<category>
<pattern>WHO IS HE</pattern>
<template><srai>WHOISHE <get name="he"/></srai></template>
</category>

<category>
<pattern>WHOISHE *</pattern>
<template>He is <get name="he"/>.</template>
</category>

<category>
<pattern>WHOISHE UNKNOWN</pattern>
<template>I don’t know who he is.</template>
</category>
```

For the given value of the predicate 'he', where if it is UNKWNOWN, or not, this will trigger one or other response.







