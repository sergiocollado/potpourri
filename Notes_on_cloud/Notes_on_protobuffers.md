	# PROTOBUFS

references:
 - https://protobuf.dev/
 - https://protobuf.dev/getting-started/cpptutorial/
 - https://github.com/protobuf-c/protobuf-c

## What is serialization/deserialization?

Serialization is the process of converting a data object—a combination of code and data represented within 
a region of data storage—into a series of bytes that saves the state of the object in an easily transmittable form.

There are some points that serialization/deserialization have to account for: 

- languaje agnosticim: the data is accessible easily from different programming languajes.
- communication: to be possible to not be dependand on any operating system and different networks
- object relationships: objects keeps its relationships
- storage space: data structure as small as possible (also relevant for time and energy usage)
- human-friendly & readability : readable formats are prefered to debug and develop


## Data schema & data schema strictness:

Usually the data, follows a data schema. And that data schema can be very strict or more forgiving. 
A strict data schema usually is less error-prone, but it can be less dynamic. 

## Serilazation formats:

- xml
- json
- protobuf 

protobuf was developed by Google at 2001 and released at 2008. Protobuf is much smaller that xml and json. 
But the serialized data is not human readable. 


What are protocol buffers and why are they useful?

Protocol buffers are an IDL (Interface Description Language). 

- Inteface: define types, properties ...
- Description: Describes relationships between types
- Language: Syntax and rules

The copiler of the language is `Protoc`, it is an S2S (Source to Source tranlator), a transpiler. 

So Protoc gets a .proto file, and it returns  a code in the selected language. 

## Types in protobuffers

	
```
syntax = "proto3"; 

message Book {
	string title = 1;
	string subtitle = 2;
	uint32 year = 3;
	repeat string authors = 4;
	string isbn = 5;
}
```

`syntax` indicates which version syntax is used. 

A `message` is a collection of 'fields'. A message is similar to classes/struct in your favorite programming language. They group certain properties together.

Each 'field' has 3 parts: 
- type
- name
- tag (its an identifier) (A field tag is a unique identifier for a given field. This is the part of a field that comes after the equal sign.)

### basic types

The basic types are: 
 - integers: int32, uint32, fixed32, sint32, sfixed32, int64, uint64, fixex64, sint64, sfixed64
 - floating points: float, double.
 - boolean: bool
 - arrays: string, bytes
 
 Every thing is optional, so that means, it can have a value or not. 
 
 The default value of a numeric type is 0. 
 
 For boolean, the default value is false.
 
 For arrays, the default value is an empty array. 
 
 
 ### enumerations
 
 ```
 enum FileType {
     UNSPECIFIED = 0;
	 MP3 = 1; 
	 MP4 = 2;
	 JPEG = 3;
 }
 ```
 
 We can see that the fist tag is 0, this would be incorrect in a message, but it is correct in an enumeration. 
 
 The default value of an enum will be 0.
 
 ### repeated fields
 
 To make lists use the 'repeated' field. 
 
 **Watch out! protobuffers doen't ensure the order for repeated fields or maps.**
 
 To store 0 or more values in an array
 
 ```
 message User {
     repeated string middle_names = 1;
 }
 ```
 
 ### Maps
 
 A dictionary structure.
 
 **Watch out! protobuffers doen't ensure the order for repeated fields or maps.**
 
 ```
 message PhoneBook {
     map<string, string> contacts = 1;
 }
 ```
 
 As values, complex types can be used, but as keys, only basic types (numbers (but not floating), strings...)  can be used.
 
 A map cannot be `repeated`
 
 The default value for a Map, is an empty Map.
 
 
 ### Oneofs 
 
 ```
 message Cat { ... }
 
 message Dog { ... }
  
  
 message CatOrDog {
    oneof result {
       Cat cat = 1;
       Dot dog = 2; 
    }
 }
 ```
 
 'Oneofs', can only be defined inside messages, and cannot be 'repeated'. Its default value is a default value 'not-setted'.
 
 
 ## Proto files
 
 ### All in one file
 
 The first thing to understand is that, in Protocol Buffers, we import files (more on that in the imports section) by their file name. Thus, this file name, if properly chosen, is giving us some context or, more precisely, some explanation of what is inside. This can be seen in several proto files defined by Google.

Let’s take the example of wrappers.proto file, which defines the following messages:

```
// Wrapper message for `double`.
//
// The JSON representation for `DoubleValue` is JSON number. message DoubleValue {
  // The double value.
  double value = 1;
}

// Wrapper message for `float`.
//
// The JSON representation for `FloatValue` is JSON number. message FloatValue {
  // The float value.
  float value = 1;
} 

// and many more …
```

Don’t worry too much about where to find them and what is the use case for these messages. We are going to use some of these wrappers later in this course, and we will explain where you can find them.

You can see that the wrappers.proto is basically grouping the same kind of messages in one file. These messages all have a single field with one of the simple types that we defined earlier. They wrap these fields with a message.

The second important thing that differentiates Protocol Buffers and Object-Oriented languages are that in Protocol Buffers, we are simply defining a schema for the data; we are not defining any business logic. Thus, writing a message will take significantly less space than a fully-fledged class. This is important because, for the same amount of lines, we can define considerably more messages.

Now, obviously, there are some disadvantages to defining all of the messages in one single file. The first one is that, if you are not careful, the context given by the file name can become too broad, and the file will become a catch-all that will become the default choice for developers when they do not know where to put this new message. This is similar to the enormous Utils class that we can see emerging in Object-Oriented languages. Just be aware that this can become messy and make developers’ life more difficult.

The second disadvantage is that if you put too many definitions in there, it will simply be hard to find the message you want to inspect, and it might even be scary for some developers. The first reaction might be something like: “A 1000 lines file? No thanks”.

So, to summarize, you want to declare multiple messages in the same file when they are related to each other. The name of the file should express this relationship. But be careful not to create a catch-all file because it will become disorganized and unnerving for other developers

 ### Imports
 

As was stated in the previous section, defining everything in a single file can become disorganized and unnerving. To solve this problem, we can define smaller files with more precise contexts and import them where needed.

In order to import a proto file in a message, you will simply write:

```
import “myfile.proto”;
```

Where myfile can be replaced by the name of your proto file. This is as simple as that.

Now, let’s get to the details. This is important to understand that we are not necessarily going as extreme as defining a message per proto file.
 This can be useful sometimes, but in some cases, it might also clutter your main proto file, which includes all of these files. 
 We saw in the previous section that the `wrappers.proto` is a good example of a file containing multiple messages, and importing it into a proto 
 file will grant you access to these different wrappers. So, let’s take a look at when you might want to define a single message in a file and import it.

Such an example can be seen in a proto file defined by Google and provided with Protocol Buffers: `duration.proto`.

Here is the shortened content of this file: 

```
// A Duration represents a signed, fixed-length span of time represented
// as a count of seconds and fractions of seconds at nanosecond
// resolution. It is independent of any calendar and concepts like "day"
// or "month". It is related to Timestamp in that the difference between
// two Timestamp values is a Duration and it can be added or subtracted
// from a Timestamp. Range is approximately +-10,000 years. 

message Duration {
    // Signed seconds of the span of time. Must be from -315,576,000,000
    // to +315,576,000,000 inclusive. Note: these bounds are computed from:
    // 60 sec/min * 60 min/hr * 24 hr/day * 365.25 days/year * 10000 years
    int64 seconds = 1; 

    // Signed fractions of a second at nanosecond resolution of the span
    // of time. Durations less than one second are represented with a 0
    // `seconds` field and a positive or negative `nanos` field. For durations
    // of one second or more, a non-zero value for the `nanos` field must be
    // of the same sign as the `seconds` field. Must be from -999,999,999
    // to +999,999,999 inclusive.
    int32 nanos = 2;
}   
```

This duration.proto defines a single message called `Duration`, and the goal here is to define an object that is generic 
and that can be used by itself. So, `Duration` is not bound to any larger context, and thus the name of the file is simply `duration.proto`.

Another thing to note is that, when importing this file, you are limited to only using `Duration`. You do not have access to any other message.
 This might sound limiting and push you to import a lot of proto files, but this is designed in this way to show the genericity of this object.
 Durations are often used for communication purposes, and thus it is important to have this message and only this message in a single proto file. 
 This limits import overhead.

So, to summarize, "imports" are useful when you want to separate messages in multiple files. 
This might be the case when we are defining generic objects such as Duration but also for importing
 a group of messages at once, such as for the wrappers.
 
 
 ### Packages
 
 Now that we have seen why we would want to define multiple messages in one file and why we 
 might want to define one message in one file, we can introduce the concept of `package`.
 The package is another construct that gives context to your proto file architecture.

The `package` is defined in a proto file like this:

```
package a.b;
```

Where `a` is the parent package, and `b` is the child package (note: you can have more children),
 gives a broader context than the file name. This is the case because the identical 
 packages in different files will regroup all these files in the same package.

An example of a package can be once again seen in the proto files provided by Google.
 Remember the proto file definitions in the previous lectures? These files are grouped under the `google.protobuf` package.

What this means is that Google has a copyright on them, but most importantly, these messages are relevant in the context of the Protobuf project.
 Now, I understand this might be a little bit too broad for you to understand the real consequences, but let’s take a look at the following example.

Let’s say that we are defining a simple FileSystem in our company called "mycompany". If I define a message file like this:

```
package mycompany.fs;

message File { /*…*/ }
```

This message will only be relevant in the context of mycompany’s FileSystem and nowhere else.
 Furthermore, if I define another message for Folder in a separate file, like this:

```
package mycompany.fs;

import “file.proto”;

message Folder {
  repeated File files = 1;
}
```

The Folder message understands that the File type that I’m talking about is the mycompany.fs file. This is possible because they both are in the same package.

Now, to get why this is important, it is worth understanding what happens when you have two messages in different packages.
 Let’s take the example of using the Timestamp message defined by Google.

The Timestamp message is in the package google.protobuf and is defined as such:

```
message Timestamp {
   // Represents seconds of UTC time since Unix epoch
   // 1970-01-01T00:00:00Z. Must be from 0001-01-01T00:00:00Z to
   // 9999-12-31T23:59:59Z inclusive. int64 seconds = 1;
   // Non-negative fractions of a second at nanosecond resolution. Negative
   // second values with fractions must still have non-negative nanos values
   // that count forward in time. Must be from 0 to 999,999,999
   // inclusive.
   int32 nanos = 2;
}
```

We are going to use it in our File message to specify when the File was created. And to do that, because File and Timestamp 
are not defined in the same package (mycompany.fs and google.protobuf respectively), we are going to need to provide the 
fully qualified name for Timestamp. So now the file will be defined like this:

```
package mycompany.fs; 

import “google/protobuf/timestamp.proto”; 

message File {
  google.protobuf.Timestamp created_at = 1;
}
```

It is important to note that google.protobuf.Timestamp is the fully qualified name of Timestamp. 
This lets the Protobuf compiler know that we are talking about the Timestamp defined in the `google.protobuf` package
 and not any other Timestamp. And finally, this also makes defining messages less error-prone because the developer 
 needs to explicitly write the whole name, and thus, he/she needs to be sure about the type to use.

So, to summarize, the packages are regrouping a set of files together, and they are providing extra security for developers 
because if we are accessing a message defined in another package, we need to provide the fully qualified name 
and thus be sure that this is the right message.


### Nested messages

The final context that I want to present is the context given by a file. Protocol Buffers let you define nested messages.
 And what this means is that the inner classes are only relevant in the context of the parent class. 
 Let’s take an example. We will define two messages, one for a dog and one for a cat, and in these messages,
 we will want to store the breed of the animal.

A naïve approach is to define an enum for breeds and the two messages:

```
enum Breed {
  UNSPECIFIED = 0; 
  DALMATIAN = 1; //dog
  DOBERMANN = 2; //dog
  BENGAL = 3; //cat
  BURMESE = 4; //cat
  //…
} 

message Cat {
  Breed breed = 1;
} 

message Dog {
  Breed breed = 1;
}
```

This might seem fine at first sight, but there is a problem. The problem is that the Cat message can use a Dog Breed,
 and the Dog can use a Cat Breed. So, the next iteration would be to write two enums: CatBreed and DogBreed, and now we don’t have this problem. We can do something like this:

```
enum CatBreed {
  UNSPECIFIED = 0;
  BENGAL = 1;
  BURMESE = 2;
} 

message Cat {
  CatBreed breed = 1;
} 

enum DogBreed {
  UNSPECIFIED = 0;
  DALMATIAN = 1;
  DOBERMANN = 2;
  //…
} 

message Dog {
  DogBreed breed = 1;
}
```

This is indeed solving the problem but notice the fact that we are prepending the message name with the animal’s name.
 This is a classic pattern for where you might want to use nested messages. So, a better approach is to define your messages like this:

```
message Cat {
  enum Breed {
    UNSPECIFIED = 0;
    BENGAL = 1;
    BURMESE = 2;
  } 

  Breed breed = 1;
} 

message Dog {
  enum Breed {
    UNSPECIFIED = 0;
    DALMATIAN = 1;
    DOBERMANN = 2;
    //…
  } 

  Breed breed = 1;
}
```

This is the same as the previous definitions; however, now we don’t need the animal’s name prepended. 
The two animals are defining their specific set of breeds, and if an external message wants to access a breed,
 it will have to use the fully qualified name for that message which Cat.Breed or Dog.Breed (prepended with the 
 package name if the message accessing them is not in the same package).

So, to summarize, nested messages can provide specialization of a certain message/enum depending on the parent message. 
And it will make it safer to use because now A cat can’t access a dog breed, and when an external message wants 
to access a Breed, it will have to provide the fully qualified name.


## Protoc trancompiler

### Installation

Installing
In order to download a version of protoc that suits your OS, we need to define a few variables. We first start by getting the latest version of protoc:

```
PROTOC_VERSION=$(curl -sL "ht‌tps://api.github.com/repos/protocolbuffers/protobuf/releases/latest" | awk '/"tag_name": "v[0-9.]+"/{print $2}' | awk 'match($0, /[0-9.]+/) { print substr( $0, RSTART, RLENGTH )}')
```

Or, if you want a specific version:

```
PROTOC_VERSION=21.10
```

Which is the version number without the prefix `v`.

Then we need to define the variable for our OS (we assume you are on Linux but for other OS, check the GitHub releases):

```
PROTOC_OS=linux
```

And finally, we set a variable for our machine architecture (the most common ones are: x86_64 and aarch_64. For others, check the GitHub releases):

```
PROTOC_ARCH=x86_64
```

With these variables set, we can now download the protoc compiler from Github:

```
curl -Lo protoc.zip "ht‌tps://github.com/protocolbuffers/protobuf/releases/latest/download/protoc-${PROTOC_VERSION}-${PROTOC_OS}-${PROTOC_ARCH}.zip"
```

Then we extract content from the zip file (except readme.txt), and we place the content into our /usr/local path.

```
unzip -q protoc.zip -x readme.txt -d /usr/local
```

We remove the zip file that is not needed anymore:

```
rm -f protoc.zip
```

And finally, we can make the protoc file executable and try to use it:

```
chmod a+x /usr/local/bin/protoc
protoc --version
```

If everything went fine, you should be able to have an output similar to this:

```
libprotoc 3.21.5
```

### Uninstall

If you need to uninstall protoc for any reason, you can simply delete the binary and the include files, like so:

```
sudo rm -f /usr/local/bin/protoc
sudo rm -rf /usr/local/include/google/protobuf
```

### API

#### Getting help
```
protoc --help ## help options
```

#### Compiling

```
protoc --cpp_out=OUT_DIR <filename i.e: dummy.prot> ## generate c++ header and source
```

For example: 

```
protoc --cpp_out=. *.proto
```

If you programming language is not in the help list, you will need to use a plugin. For example: https://crates.io/crates/protobuf-codegen

Also, other relevant options:

```
protoc --I<PATH>
protoc --proto_path=<PATH>
# specifies the directory to search for imports
```
For example: 

```
protoc --cpp_out=. --proto_path=imports imports/*.proto
# this is the same as:
protoc --cpp_out=. -Iimports imports/*.proto
```

#### Encoding and decoding

To encode: 


```
cat file.txt | protoc -I <../your/path> --encode=<full_qualified_message_name>  yourMessage.proto # this will write in the standard output the serialized binary, but you can redirect it to a file

```


```
cat file.txt | protoc -I <../your/path> --encode=<full_qualified_message_name> yourMessage.proto > file.bin

```

To decode it: 


```
cat file.bin | protoc -I <../your/path> --decode=<type_to_be_decoded_from> yourMessage.proto 
```


To decode raw: 


```
protoc --decode_raw # Read an arbitrary protocol message from standard input and write the raw tag/value pairs in text format
```

`--decode_raw`, as its name suggests, takes raw data and decodes it. This lets us get an idea of how the data is laid out. To use it for example:


```
cat file.bin | protoc -I <../your/path> --decode_raw > result_tab_value.txt 
```


## Services

Services are a generic concept, and are not designed for communications. Services are a set of end-points that
are defining an API. Protocol Buffers cannot send messages over the network, but the main framework that does
this are gRPC. 


```
message GetSomethingRequest {
...

message GetSomethingResponse {
...
}

message ListSomethingRequest {
...
}

message ListSomethingResponse {
...
}

service FooService{
   rpc GetSomething(GetSomethingRequest) returns (GetSomethingResponse);
   rpc ListSomething(ListSomethingRequest) returns (ListSomethingResponse);


```
