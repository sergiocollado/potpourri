# NOTES ON SELINUX

## Introduction

Security Enhaced Linux (SELinux) is a Linux Kernel Security Module (aka LSM) that provides a mechanism for supporting access control security policies, 
including mandatory access control (MAC). SELinux is a label-based mandatory acess control. There are labeled processes on one side (subjects) and labeled
resouces (objects) on other side, and the "allow" rueles regulate the relationship of subjects and objects

 - subjects are the elememts that perform operations
 - objects are the elements in which operations are made on.

An example for a context: "u:object_r_etc_t:s0"

- u: user use
- Object_r: the role
- etc_t: the type
- s0: the multi-level-security (MLS) sensitivity level.

### MAC features

- Restricts/allows acess based on a centralized policy
- SELinux is an implementaion of MAC (mandatory access control)
- The owner of a resource doesn't decide on its access mode
- Everything is denied by default
- The kernel provides an MAC API: LSM (linux security module)
- MAC in not dependant of DAC (Discreccional Access Control). Both access have to be allowed
- Other LSM-based MAC implementations are: Smack, Tomoy, Yama

### Disadvantes

- Expensive setup. Big effort is required
- All the components need to be aligned with this policy development
- Complicated policy update process in a running system

## How SELinux is implemented

- The system is viewed as subject (processes) performing actions of objetcs (files, devices, ports ...)
- All subjects and all objects get a label. **Everything gets a label** 
- The **input** of the access control system are **requests**: Subject lable, operation and object label
- The **output** are **decisions**: Allow or Deny.

Lets see an example: a subject Alice, wants to read a document "My-Document" from a folder "Filling-Cabinet".

The subjet is Alice and there are two objects

- Object: My-Document
  - Class: file
  - type: My-Document_t
  
- Object: Filling cabinet
  - Class: cabinet
  - Type: Filling-cabinet
  
 step 1: opening the cabinet.
 
 Alice wants to read teh document "My-Document" form the folder "Filling-cabinet"
 
 Subject: Alice
 - Object type: Filling-cabinet
    - Class: cabinet
 - operation: 
    - open
	
 step 2: search for the document
 
  Alice wants to seach a cabinet of type Filling-cabinet_t
  
  Subject: Alice
  - object: Filling-cabinet
     - class: cabinet
  - operation: 
     - Search
	 
 step 3: opening the document
 
 Alice wants to oepn a file of type My-Document_t
 
 Subjetc: Alice
  - object: My-Document
    -class: file
  - operation: 
    - open
	
 step 4: reading the document
 
 Alice wants to read the file of type My-Document_t
 
 Subject: Alice
  - object: My-Document
    - class: file
  - operation:
      - read

 Summary: 
  Subject: Alice
  Objects: Filing-cabinet, My-Docuemnt
  Operations: cabinet:open, cabinet:search, file:open, file:search
  
  pseudo-code:
  
  ```
  allow Alice to { opean search } cabinet of type Filing-Cabinet_t
  allow Alice to { open read } file of type My-Docuemnt_t
  ```
  
  ## SELinux labels (aka context)
  
  A policy rule has to be created to define the acess of: 
  - user or domain
  - rol or object
  - type of operation
  - level acess
  
  ```
  user:role:type:level: category {.selinux-label}
  ```
  
  The label is the name of the rule. Once created the policy rule,
  the next step is to label the file system and processes in order to SELinux knows which rule policy has to be used in every case. 
  
  SELinux access control paradigms
  
  Labels (also known as context) is a string with 5 parameters: user, role, type, level and category
  
