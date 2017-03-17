# NOTES ON AIML

AIML stands for Artificial Intelligence Markup Languaje, it was developed for a chat-bot named A.L.I.C.E (Artificial Linguistic Internet
Computer Entity)[:link:](http://www.alicebot.org/).


## BASIC CONCEPTS:

AIML defines a classes of objects called AIMLs, and are made of __**units**__ and __**categories**__. AIMLs objects contain, the stimoulus
-response of the AI.

### __**CATEGORIES**__

__**Categories**__ are the basic unit of kwnolegde, each one, is made of a question (the stimulus or **pattern**), an answer (also refered
as the **template**), and an optional __**context**__: there are two types __**'that'**__ and __**'topic'**__. __**that**__ refers to the
objective of the bot, and __**topic**__ is a general group of categories.

```
Categories 
         L__ pattern   (stimoulus - question)
         |
         L__ template  (reply - answer) 
         |
         L__ context (optional)
                |
                L__ that
                |
                L__ topic

```

The AIML __**pattern**__ is simple it just consists on words, and two wildcard symbols _ and *. The __**template**__ uses the tags, 
to run a program, that react to the __**pattern**__.


