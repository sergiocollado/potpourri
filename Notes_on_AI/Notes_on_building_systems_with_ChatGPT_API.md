# Notes on building systems with ChatGPT API

## Introduction

Welcome to this course on building systems using the ChatGPT API. 
Previously, Isa and I had presented a 
course on how to prompt ChatGPT, but a system requires 
much more than a single prompt or a single call to an 
LLM or large language model. 
In this short course, we'd like to share with 
you best practices for building a complex application 
using an LLM. 
We used the running example of building an end-to-end customer 
service assistant system that chains multiple 
calls to a language model, using different instructions depending on 
the output of the previous call, and sometimes 
even looking things up from external sources. 
So for example, given a user input like, 
"Tell me about what TVs are for sale?", we'd use the following steps 
to process this. 
First, you can evaluate the input to make sure it doesn't 
contain any problematic content, such as hateful speech. Next, the 
system will process the input. It will identify what type 
of query this is. Is it a complaint or 
a product information request and so on? Once 
it has established that it is a product inquiry, it 
will retrieve the relevant information about 
TVs and use a language model to write a helpful response. 
Finally, you'll check the output to make sure it isn't problematic, 
such as inaccurate or inappropriate answers. 
One theme you see throughout this course is that an application often 
needs multiple internal steps that are invisible to the end-user. 
 
You often want to sequentially process the user 
input in multiple steps to get to the final output that is 
then shown to the user. 
And as you build complex systems using LLMs, 
over the long term you often want to 
also keep on improving the system. So I'll also share with you 
what the process of developing an LLM-based application 
feels like, and some best practices for evaluating 
and improving a system over time. 
We're grateful to many people that have contributed to 
this short course. 
On the OpenAI side, we're grateful to Andrew Kondrich, Joe 
Palermo, Boris Power, and Ted Sanders. 
And from the DeepLearning.AI team, thank you also to Geoff Ladwig, Eddy 
Shyu, and Tommy Nelson. 
Through this short course we hope you'll come away confident in 
your abilities to build a complex multi-step application 
and also be set up to maintain and keep on improving it. 


## Language models, the chat format and tokens

### Setup 

Load the API key and relevant Python libaries.
In this course, we've provided some code that loads the OpenAI API key for you.

```
import os
import openai
import tiktoken
from dotenv import load_dotenv, find_dotenv
_ = load_dotenv(find_dotenv()) # read local .env file
​
openai.api_key  = os.environ['OPENAI_API_KEY']
```


helper function
This may look familiar if you took the earlier course "ChatGPT Prompt Engineering for Developers" Course

```
def get_completion(prompt, model="gpt-3.5-turbo"):
    messages = [{"role": "user", "content": prompt}]
    response = openai.ChatCompletion.create(
        model=model,
        messages=messages,
        temperature=0,
    )
    return response.choices[0].message["content"]
Prompt the model and get a completion
response = get_completion("What is the capital of France?")
print(response)
Tokens
response = get_completion("Take the letters in lollipop \
and reverse them")
print(response)
"lollipop" in reverse should be "popillol"

response = get_completion("""Take the letters in \
l-o-l-l-i-p-o-p and reverse them""")
response
```

### Helper function (chat format)
Here's the helper function we'll use in this course.

```
def get_completion_from_messages(messages, 
                                 model="gpt-3.5-turbo", 
                                 temperature=0, 
                                 max_tokens=500):
    response = openai.ChatCompletion.create(
        model=model,
        messages=messages,
        temperature=temperature, # this is the degree of randomness of the model's output
        max_tokens=max_tokens, # the maximum number of tokens the model can ouptut 
    )
    return response.choices[0].message["content"]
```

```
messages =  [  
{'role':'system', 
 'content':"""You are an assistant who\
 responds in the style of Dr Seuss."""},    
{'role':'user', 
 'content':"""write me a very short poem\
 about a happy carrot"""},  
] 
response = get_completion_from_messages(messages, temperature=1)
print(response)
```

```
# length
messages =  [  
{'role':'system',
 'content':'All your responses must be \
one sentence long.'},    
{'role':'user',
 'content':'write me a story about a happy carrot'},  
] 
response = get_completion_from_messages(messages, temperature =1)
print(response)
```

```
# combined
messages =  [  
{'role':'system',
 'content':"""You are an assistant who \
responds in the style of Dr Seuss. \
All your responses must be one sentence long."""},    
{'role':'user',
 'content':"""write me a story about a happy carrot"""},
] 
response = get_completion_from_messages(messages, 
                                        temperature =1)
print(response)
```

```
def get_completion_and_token_count(messages, 
                                   model="gpt-3.5-turbo", 
                                   temperature=0, 
                                   max_tokens=500):
    
    response = openai.ChatCompletion.create(
        model=model,
        messages=messages,
        temperature=temperature, 
        max_tokens=max_tokens,
    )
    
    content = response.choices[0].message["content"]
    
    token_dict = {
'prompt_tokens':response['usage']['prompt_tokens'],
'completion_tokens':response['usage']['completion_tokens'],
'total_tokens':response['usage']['total_tokens'],
    }
​
    return content, token_dict
```

```
messages = [
{'role':'system', 
 'content':"""You are an assistant who responds\
 in the style of Dr Seuss."""},    
{'role':'user',
 'content':"""write me a very short poem \ 
 about a happy carrot"""},  
] 
response, token_dict = get_completion_and_token_count(messages)
```

```
print(response)
print(token_dict)
```

Notes on using the OpenAI API outside of this classroom
To install the OpenAI Python library:

```
!pip install openai
```
The library needs to be configured with your account's secret key, which is available on the website.

You can either set it as the OPENAI_API_KEY environment variable before using the library (https://platform.openai.com/account/api-keys): 

```
 !export OPENAI_API_KEY='sk-...'
Or, set openai.api_key to its value:

import openai
openai.api_key = "sk-..."
```

A note about the backslash:
In the course, we are using a backslash \ to make the text fit on the screen without inserting newline '\n' characters.
GPT-3 isn't really affected whether you insert newline characters or not. But when working with LLMs in general, you may consider whether newline characters in your prompt may affect the model's performance.
