NOTES on PARALLEL COMPUTING:
===========================

FOREWORD: This are my personal notes, about methods for develop systems in multicore architectures, I didn't invent/discover anything,
but keep my notes here, for my future reference, or as reference to help collegues, that need some intro to the topic. I guess I have used lots of references, and I'm not sure if I have named them all; I've just been picking stuff from here and there, without any particular order...
so everithing, is due to their respective owners :) - cool people!. thanks!


INTRO:
 During many years, the advance in computing hardware, were focus in doing smaller and faster CPUs, once it was hitten a point, where this wasn't possible anymore, the technology evolved to parallelize CPU cores in order to increase performance.
 
 Parallelization allows a program to be run in different computing units, allowing to short its executio time.
 
 For example a matrix multiplications is easily parallelized:
 
 
 ```
 |a1 a2|   *   | b1 b2|   =    |a1*b1+a2*b3   a1*b2 + a2*b4|
 |a3 a4|       | b3 b4|        |a1*b2+a2*b4   a3*b2 + a4*b4|
 ```
 
 Each element of the resulting matriz can be computed by different units:
 
 ```
 CPU 1 :    a1*b1 + a2*b3
 CPU 2 :    a1*b2 + a2*b4
 CPU 3 :    a1*b2 + a2*b4
 CPU 4 :    a3*b2 + a4+b4
 ```
 
 This is possible, due each element is not dependant on the others.
 If this squeme is followed, for this example it is possible to have a time improvement around x4.
 
 
 To parallelize a program, the first step is to identify what parts of the program can be parallelized: that is task or calculations or algorithms or data processing that don't depend on each other results. Two main models are used:
- Master/slave relationship, where a core organizes the work on the other cores.
- Data flow model, in which the work is done in parallelized pipelined stages.
 
 
 MASTER/SLAVE MODEL:
  One core to rule them all... a core distribute the tasks/threads in the remaining cores, usually those systems have quite a control structure, and tasks/threads are small and are allocated easily in the remainder cores. The challenge in this model, is to keep the balance of work between processors, to obtain an optimal parallelization.
  
 DATA FLOW MODEL:
  Each core works on certain task or tasks, and once the data is processed is passed to a common work that continues the process.This model is fitted to work with data intensive applications, as the data can come from sensors or networks or other services. And also fits real-time systems, as it reduces the latency of the system. 

HOW TO BEGIN TO WRITE PARALLEL CODE:
====================================

One recomended option to start is to use OpenMP.

OpenMP is the API (Application Program Interface) for programming multi-task application in multi-core systems with a SMP architecture (Shared Memory Parallel architecture).

One of the main advantages, is that OpenMP, is sequential-friendly, that is: you don't need to define each task separatelly, but, just indicate to the compiler what parts of the code you want to execute in different cores.

reference: http://www.openmp.org/
learning OpenMP: http://www.openmp.org/resources/
An introduction to Parallel programming with OpenMP- by Alina Kiessling.

SAMPLE Hello Wold!:
==================

Consider the program in C:


```C
#include 'omp.h' //includes the openMP library
void main()
{
  #pragma omp pararell //this prediretive defines that the following code block {...} is to be paralleliced.
       {
          int ID = omp_get_thread_num(); //retrieves the ID number of the current thread
          printf('Hello  (%d) ',ID);
          printf('World  (%d) \n',ID);
       }
}
```

the first line: #include 'omp.h', includes the OpenMP.

the paralelled region is placed under the directive: #prama opm pararell { ... }

The function 'omp_get_thread_num()", returns the thread ID of the programm.

To compile the program, we use:

> gcc -fopenmp HelloWold.c -o Hello

for the GNU compiler.


VOCABULARY:

SIMD - SINGLE INSTRUCTION MULTIPLE DATA (intel) (paralel operation)

Vector Instructions sets for Intel Architecture:
 - MMX - Multi Media Extensions (64 bits, only integers).
 - SSE - Streaming SIMD Extensions - (versions: 1,2,3,.., 4.2) (128 bits). Frome SSE2, floating point (single & double precission) numbers are supported.
 - AVX - Advanced Vector Extension - (256 bits) floating point vector operations (single & double precission)
 - IMCI, AVX-512 (512 bits)
 
 With vectorization a speed up of 2,4, ... even 16 is possible. If vectorization is not used, that means, you are expending even x16 times money (or time), more on you computer process data programs.
 
 
 Vectorization directives:
  - #pragma omp simd
  - #pragma vector always
  - #pragma vector aligned | unaligned
  - __asume_aligned **keyword**
  - #pragma vector nontemporal | temporal
  - #pragma novector
  - #pragma ivdev
  - restrict **qualifier and** -restrict **command-line argument**
  - #pragma loop count
  
  Multiversioning protection
  - #pragma ivdep
  
  >> link: Intel Intrinsic Vectorization Guide:  https://software.intel.com/sites/landingpage/IntrinsicsGuide/
  
 
TRICKS OF THE TRADE:

>> while loops, cannot be paralelized, due you cannot know at compiler and even at run time, the number of times it is going to loop around. Then, while loops, will not be paralleliced with authomatic tool, neither with compiler enformecements ...


>> To initialize vertors in C++, use the notation extentions for C++, most of the compiles can handle those definitions.

```C++
double A[n], B[n];
A[0:n] = B[0:n] = 1.0 //by the way, this inizialization value assignation, is also vectorized. :)
```

>> Definiton of variables with the keywords: 'extern const' will cause that in most of the compiles operation whith variables defined as such, will not be optimized, as its value can change without notice from external sources. ... so no optimization at all, for those varialbls. On the other hand, this behavior can have some advantage, in the case those variables are use to represent 
certain cases, as sensor or similar data, because they will be protected on its writting, so for these cases that varible definition, is like set those variable as a READ-ONLY.

```
extern const input_signal;  //treated as a READ-ONLY variable.
```


