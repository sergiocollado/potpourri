# Notes on modern CUDA C++

 - https://enccs.github.io/gpu-programming/
 - https://learn.nvidia.com/my-learning
 - https://developer.nvidia.com/blog/even-easier-introduction-cuda/

# CUDA Made Easy: Accelerating Applications with Parallel Algorithms

To make your first steps in GPU programming as easy as possible, in this lab you'll learn how to leverage powerful parallel algorithms that make GPU acceleration of your code as easy as changing a few lines of code. While doing so, you’ll learn fundamental concepts such as execution space and memory space, parallelism, heterogeneous computing, and kernel fusion. These concepts will serve as aWhy GPU Programming?

Before we dive into why programming GPUs is worth it, let’s think about a different question. Which is faster, a bus or a car? It might seem like a simple question, but it’s missing some context. Faster at what? A car might be quicker if you’re moving four people, but a bus will probably get forty people there faster.  foundation for your advancement in accelerated computing. 

## Execution spaces


By the end of this lab, you’ll have your first code running on a GPU! But what exactly does it mean to run code on GPU? For that matter, what does it mean to run code anywhere? Let's start by working our way through this question.

To build intuition around such fundamental questions, we'll be simulating heat conduction. We'll start with a very simple version that simulates how objects cool down to the environment temperature. As we gain proficiency with necessary tools, we'll advance this example.


```
%%writefile Sources/cpu-cooling.cpp

#include <cstdio>
#include <vector>

int main() {
    float k = 0.5;
    float ambient_temp = 20;
    std::vector<float> temp{ 42, 24, 50 };

    std::printf("step  temp[0]  temp[1]  temp[2]\n");
    for (int step = 0; step < 3; step++) {
        for (int i = 0; i < temp.size(); i++) {
            float diff = ambient_temp - temp[i];
            temp[i] = temp[i] + k * diff;
        }

        std::printf("%d     %.2f    %.2f    %.2f\n", step, temp[0], temp[1], temp[2]);
    }
}
```

At the beginning of the main function, we construct a std::vector and store three elements in it:

```
std::vector<float> temp{ 42, 24, 50 }
```

After that, we transform each element of this vector:
```
for (int i = 0; i < temp.size(); i++) {
    float diff = ambient_temp - temp[i];
    temp[i] = temp[i] + k * diff;
}
```
Here, we are updating each element of the vector by a constant factor times the difference between the ambient temperature and the current temperature. The result of this computation overwrites each previous element:

```
diff    = 20 - 42;        // -22
temp[0] = 42 + 0.5 * -22; // 31.0
```

Finally, we print the new contents of the vector:

If everything goes well and your environment is set up correctly, the cell below should print:

```
step 	temp[0] 	temp[1] 	temp[2]
0 	31.00 	22.00 	35.00
1 	25.50 	21.00 	27.50
2 	22.75 	20.50 	23.75
```

compile and execute the program:

```
# g++ Sources/cpu-cooling.cpp -o /tmp/a.out # compile the code
# /tmp/a.out # run the executable
```
Let's revisit the steps that we've just made. We started by compiling our code using the g++ compiler:

```
g++ Sources/cpu-cooling.cpp -o /tmp/a.out
```

The g++ compiler consumed C++ code and produced an executable file, a.out, which contains a set of machine instructions. However, there’s a problem: different CPUs support different sets of instructions. For example, if you compile the program above for an x86 CPU, the temp[i] + k * diff expression will be compiled into the vfmadd132ss instruction on the x86 architecture. If you try running the resulting executable on an ARM CPU, it won’t work because the ARM architecture does not support this instruction. To run this code on an ARM CPU, you would need to compile it specifically for the ARM architecture. In that case, the expression would be compiled into the vmla.f32 instruction.


![compilation](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/execution-policy.svg)


From this perspective, GPUs are no different. GPUs have their own set of instructions, therefore, we have to compile our code for GPUs somehow.

```
# nvcc -x cu Sources/cpu-cooling.cpp -o /tmp/a.out # compile the code
# /tmp/a.out # run the executable
```

Congratulations! You just compiled your first CUDA program!
There's one issue, though: ***none of the code above runs on the GPU***.
That might be surprising because when we compiled our code for the CPU, the entire program could be executed on a CPU.
But now we compile our program for the GPU, and nothing runs on the GPU. 
This confusion is an indicator that we are missing an important piece of CUDA programming model.

## Heterogeneous Programming Model

GPUs are accelerators rather than standalone processors. A lot of computational work, like interactions with network and file system, is done on the CPU. So a CUDA program always starts on the CPU. You, the programmer, are responsible for explicitly specifying which code has to run on the GPU. In other words, you are responsible for specifying which code runs where. The established terminology for where code is executed is execution space.

![heterogeneous](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/heterogeneous.png)


At a high level, execution spaces are partitioned into **host** (CPU) and **device** (GPU). These terms are used to generalize the programming model. Something other than a CPU could host a GPU, and something other than a GPU could accelerate a CPU.

By default, code runs on the host side. You are responsible for specifying which code should run on the device. This should explain why using nvcc alone was insufficient: we haven't marked any code for execution on GPU.

So, let's try fixing that. The CUDA compiler, **NVCC**, is accompanied by a set of core libraries. These libraries allow you to explicitly specify the execution space where you want a given algorithm to run. To prepare our code for these libraries, let's refactor the temperature update for loop first:

```c++
%%writefile Sources/gpu-cooling.cu

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
    float k = 0.5;
    float ambient_temp = 20;
    std::vector<float> temp{ 42, 24, 50 };
    auto transformation = [=] (float temp) { return temp + k * (ambient_temp - temp); };

    std::printf("step  temp[0]  temp[1]  temp[2]\n");
    for (int step = 0; step < 3; step++) {
        std::transform(temp.begin(), temp.end(), temp.begin(), transformation);
        std::printf("%d     %.2f    %.2f    %.2f\n", step, temp[0], temp[1], temp[2]);
    }
}
```

compile and execute the program (note the .cu extension):

```bash
# nvcc Sources/gpu-cooling.cu -o /tmp/a.out # compile the code
# /tmp/a.out # run the executable
```

Instead of a for loop, we used the `std::transform` algorithm from the C++ standard library. One of the benefits of using algorithms instead of custom loops is reduced mental load. Instead of "executing" the loop in your mind to see that it implements a transformation pattern, you can quickly recognize it by the algorithm name.

But above all else, using algorithms enables you to easily leverage GPUs! For that, we'll be using one of the CUDA Core Libraries called Thrust. Thrust provides standard algorithms and containers that run on the GPU. Let's try using those:


```c++
%%writefile Sources/thrust-cooling.cu

#include <thrust/execution_policy.h>
#include <thrust/universal_vector.h>
#include <thrust/transform.h>
#include <cstdio>

int main() {
    float k = 0.5;
    float ambient_temp = 20;
    thrust::universal_vector<float> temp{ 42, 24, 50 };
    auto transformation = [=] __host__ __device__ (float temp) { return temp + k * (ambient_temp - temp); };

    std::printf("step  temp[0]  temp[1]  temp[2]\n");
    for (int step = 0; step < 3; step++) {
        thrust::transform(thrust::device, temp.begin(), temp.end(), temp.begin(), transformation);
        std::printf("%d     %.2f    %.2f    %.2f\n", step, temp[0], temp[1], temp[2]);
    }
}
```

compile and run it:

```bash
# nvcc --extended-lambda Sources/thrust-cooling.cu -o /tmp/a.out # compile the code
# /tmp/a.out # run the executable
```

Let's take a look at the changes that we've just made. We started by replacing `std::vector` with `thrust::universal_vector`. We'll explain why this change was necessary later in this lab. More importantly, we annotated the lambda with `__host__` `__device__` execution specifiers.

As discussed earlier, we have to compile some of the code into GPU instructions. Execution space specifiers tell NVCC which code can be executed on GPU. The `__host__` specifier denotes that a given function is executable by CPU. This specifier is used by default on every C++ function. For example, this means that `int main()` is the same as `__host__ int main()`.

The `__device__` specifier, on the other hand, denotes a function that's executable by GPU. That's how NVCC knows which functions to compile for the GPU and which ones for the CPU. In the code above, we combined the `__host__` `__device__` specifiers. This indicates that the function can be executed by both CPU and GPU.

Finally, we replace `std::transform` with `thrust::transform`. Unlike `std::transform`, `thrust::transform` accepts the execution space as the first parameter. In the code above, we explicitly asked Thrust to perform the transformation on device (GPU) by passing `thrust::device`.


## Execution policy

![execution_policy](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/execution-policy.svg)



## Exercise: Annotate Execution Spaces

The notion of execution space is a foundational concept of accelerated computing. 
In this exercise you will verify your expectation of *where* any given code is executed.

Replace all `???` with `CPU` or `GPU`, based on where you think that specific line of code is executing.  The `dli::where_am_I` function is a helper function for you in this exercise.

After making all the changes, run the subsequent cell to verify your expectations.  

```c++
%%writefile Sources/no-magic-execution-space-changes.cu
#include "dli.h"

int main() {
  dli::where_am_I("???");

  thrust::universal_vector<int> vec{1};
  thrust::for_each(thrust::device, vec.begin(), vec.end(),
                   [] __host__ __device__(int) { dli::where_am_I("???"); });

  thrust::for_each(thrust::host, vec.begin(), vec.end(),
                   [] __host__ __device__(int) { dli::where_am_I("???"); });

  dli::where_am_I("???");
}
```

compile and run it:

```bash
# nvcc -o /tmp/a.out --extended-lambda Sources/no-magic-execution-space-changes.cu # build executable
# /tmp/a.out # run executable
```

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

Hints

 - for invocations in the main function consult heterogeneous programming model section
 - for invocations in lambdas consult execution policy section

Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.
Solution

Key points:

 -  The main function always runs on the CPU
 -  According to thrust::device execution policy, the first thrust::for_each call invokes lambda on the GPU
 -  According to thrust::host execution policy, the second thrust::for_each call invokes lambda on the CPU

Solution:

```c++
#include "dli.h"

int main() {
  dli::where_am_I("CPU");

  thrust::universal_vector<int> vec{1};
  thrust::for_each(thrust::device, vec.begin(), vec.end(),
                   [] __host__ __device__(int) { dli::where_am_I("GPU"); });

  thrust::for_each(thrust::host, vec.begin(), vec.end(),
                   [] __host__ __device__(int) { dli::where_am_I("CPU"); });

  dli::where_am_I("CPU");
}
```


Congratulations! You are now familiar with the concept of execution spaces in CUDA. 

## Exercise: Changing Execution Space

In this exercise, you have to modify the thrust algorithm which is currently running on the CPU and change it to execute on the GPU instead. 
After your changes, program should print:

```
printing 1 on GPU
printing 2 on GPU
printing 3 on GPU
```

```c++
%%writefile Sources/port-thrust-to-gpu.cu
#include "dli.h"

int main() {
    thrust::universal_vector<int> vec{ 1, 2, 3 };
    thrust::for_each(thrust::host, vec.begin(), vec.end(), []__host__(int val) {
        std::printf("printing %d on %s\n", val, dli::execution_space());
    });
}
```
compile and run it:

```
# nvcc -o /tmp/a.out --extended-lambda Sources/port-thrust-to-gpu.cu # build executable
# /tmp/a.out # run executable
```

Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.
Solution

Key points:
 - change execution policy from thrust::host to thrust::device
 - change execution space specifier from __host__ to __device__

Solution:

```c++
#include "dli.h"

int main() {
  thrust::universal_vector<int> vec{1, 2, 3};
  thrust::for_each(
      thrust::device, vec.begin(), vec.end(), [] __device__(int val) {
        std::printf("printing %d on %s\n", val, dli::execution_space());
      });
}
```

You can find full solution here.

## Exercise: Compute Median Temperature

In many cases, porting code from CPU to GPU is as simple as replacing `std::` with `thrust::`.
To verify this, we'll focus on calculating the median temperature in the vector. 

The _median_ is the middle value in a sorted list of numbers. This differs from the _mean_, which is the arithmetic average, calculated by summing all values and dividing by the number of values.

You'll start with a CPU-based implementation and modify the code to run on the GPU. 
Below is the original CPU code that you'll need to adapt:

```c++
%%writefile Sources/port-sort-to-gpu.cu
#include "dli.h"

float median(thrust::universal_vector<float> vec) 
{
    std::sort(vec.begin(), vec.end());
    return vec[vec.size() / 2];
}

int main() 
{
    float k = 0.5;
    float ambient_temp = 20;
    thrust::universal_vector<float> temp{ 42, 24, 50 };
    auto transformation = [=] __host__ __device__ (float temp) { return temp + k * (ambient_temp - temp); };

    std::printf("step  median\n");
    for (int step = 0; step < 3; step++) {
        thrust::transform(thrust::device, temp.begin(), temp.end(), temp.begin(), transformation);
        float median_temp = median(temp);
        std::printf("%d     %.2f\n", step, median_temp);
    }
}
```

```bash
# nvcc -o /tmp/a.out --extended-lambda Sources/port-sort-to-gpu.cu # build executable
# /tmp/a.out # run executable
```

If everything goes well, the cell above should print:

| step | median
| :--- | :-----
| 0    | 31.00
| 1    | 25.50
| 2    | 22.75

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

<details>
  <summary>Hints</summary>
  
  - Thrust provides a `thrust::sort` function that can be used to sort data on the GPU
  - Use `thrust::device` execution policy to specify where you want `thrust::sort` to run
</details>

Solution:

<details>
  <summary>Solution</summary>

  Key points:
  - change `std::sort` to `thrust::sort`
  - add `thrust::device` execution policy parameter

  Solution:
  ```c++
  float median(thrust::universal_vector<float> vec) {
    thrust::sort(thrust::device, vec.begin(), vec.end());
    return vec[vec.size() / 2];
  }
  ```
 </details>


## Extending Standard algorithms

Occasionally, you might encounter a use case that's not directly covered by standard algorithms. In this section, we'll explore techniques that can help you extend existing algorithms to your unique use cases.

### Extend the algorithm example 

Let's consider a scenario where such customization might be necessary. In our earlier example, we were computing the next temperature based on the previous one. Now let's say we have to find the maximum change in temperature made in the current step.

// max diff image

```
%%writefile Sources/naive-max-diff.cu
#include "dli.h"

float naive_max_change(const thrust::universal_vector<float>& a, 
                       const thrust::universal_vector<float>& b) 
{
    // allocate vector to store `a - b`
    thrust::universal_vector<float> unnecessarily_materialized_diff(a.size());

    // compute products
    thrust::transform(thrust::device, 
                      a.begin(), a.end(),                       // first input sequence
                      b.begin(),                                // second input sequence
                      unnecessarily_materialized_diff.begin(),  // result
                      []__host__ __device__(float x, float y) { // transformation (abs diff)
                         return abs(x - y); 
                      });

    // compute max difference
    return thrust::reduce(thrust::device, 
                          unnecessarily_materialized_diff.begin(), 
                          unnecessarily_materialized_diff.end(), 
                          0.0f, thrust::maximum<float>{});
}

int main() 
{
    float k = 0.5;
    float ambient_temp = 20;
    thrust::universal_vector<float> temp[] = {{ 42, 24, 50 }, { 0, 0, 0}};
    auto transformation = [=] __host__ __device__ (float temp) { return temp + k * (ambient_temp - temp); };

    std::printf("step  max-change\n");
    for (int step = 0; step < 3; step++) {
        thrust::universal_vector<float> &current = temp[step % 2];
        thrust::universal_vector<float> &next = temp[(step + 1) % 2];

        thrust::transform(thrust::device, current.begin(), current.end(), next.begin(), transformation);
        std::printf("%d     %.2f\n", step, naive_max_change(current, next));
    }
}

```

compile with:

```
!nvcc --extended-lambda -o /tmp/a.out Sources/naive-max-diff.cu # build executable
!/tmp/a.out # run executable
```
In the code above, we started by allocating storage for products:

```c++
thrust::universal_vector<float> unnecessarily_materialized_diff(a.size());
```

Then, we used a version of `thrust::transform` algorithm that accepts two sequences.
It then applies transformation to each pair of elements in these sequences.
In our case, the transformation is computing absolute difference:

```c++
thrust::transform(thrust::device, 
                  a.begin(), a.end(),                       // first input sequence
                  b.begin(),                                // second input sequence
                  diff.begin(),                             // result
                  []__host__ __device__(float x, float y) { // transformation (abs diff)
                      return abs(x - y); 
                  });
```

And finally, we use `thrust::reduce` with the `thrust::maximum` operator to find the maximum absolute difference:

```c++
    return thrust::reduce(thrust::device, 
                          unnecessarily_materialized_diff.begin(), 
                          unnecessarily_materialized_diff.end(), 
                          0.0f, thrust::maximum<float>{});
```

Although this implementation is functionally correct, it's far from being performant.
To discover this inefficiency, let's consider our algorithm from the memory point of view.
Let's count all memory accesses in our naive implementation.
As part of the transformation step, 
we read `2 * n` floats total from `a` and `b` and store `n` elements back to memory.
As part of the reduction step, we load `n` integers.
In total, our version performs `4 * n` memory accesses. 
However, if we were to implement this algorithm as a for loop, we'd likely write something along the lines of:

```c++
float max_diff = 0;
for (int i = 0; i < a.size(); i++) {
  max_diff = std::max(max_diff, std::abs(a[i] - b[i]));
}
```

This raw loop only performs `2 * n` memory accesses.
This means that materialization of products in memory leads to 2x overhead in terms of memory accesses.
But how does this affect performance?
Like the majority of algorithms, our algorithm is memory bound meaning the ratio of communication (memory accesses) to computation is so large that the overall performance of the code will be limited by the theoretical peak memory performance of the hardware.  As a programmer, this means we will focus performance optimizations on memory usage and data movement specifically.
Since our algorithm is memory bound, a two-fold reduction in amount of memory accesses should result in about two-fold speedup. 
Besides performance implications, the absolute differences that we compute occupy space in memory. 
If our vectors were large enough, there might be no space left in GPU memory for them and the temporary space we use to compute and save the differences.

## Iterators
Fortunately, there's a way to avoid materializing these differences in memory and address these issues.
The workaround consists of using iterators. 
Using an iterator can be thought of as a generalization of using a pointer: 
* A pointer, `int* pointer`, points to a sequence of integers in memory. 
* You can dereference a pointer to get access to the integer it currently points to.
* You can advance pointer with `pointer++` to make it point to the next element in the sequence.

The following code demonstrates using a pointer to access data in an array.

```c++
%%writefile Sources/pointer.cu
#include "dli.h"

int main() 
{
    std::array<int, 3> a{ 0, 1, 2 };

    int *pointer = a.data();

    std::printf("pointer[0]: %d\n", pointer[0]); // prints 0
    std::printf("pointer[1]: %d\n", pointer[1]); // prints 1
}
```

compile with:

```
!nvcc --extended-lambda -o /tmp/a.out Sources/pointer.cu # build executable
!/tmp/a.out # run executable
```

### Simple Counting Iterator

C++ allows operator overloading. 
This means that we can define what operators such as `*` or `++` do.
The concept of an iterator builds on top of this idea.
With this, we don't even need an underlying container.
Here's an example of how we can create an infinite sequence without allocating a single byte.  Note the redefinition of the square brackets `[]` operator.

```c++
%%writefile Sources/counting.cu
#include "dli.h"

struct counting_iterator 
{
  int operator[](int i) 
  {
    return i;
  }
};

int main() 
{
  counting_iterator it;

  std::printf("it[0]: %d\n", it[0]); // prints 0
  std::printf("it[1]: %d\n", it[1]); // prints 1
}
```

compile with: 

```
!nvcc --extended-lambda -o /tmp/a.out Sources/counting.cu # build executable
!/tmp/a.out # run executable
```

### Simple Transform Iterator

Below we again redefine the square brackets `[]` operator, but this time instead of simple counting, we multiple each input value times 2.  This is an example of applying a simple function to the input before returning a value.

```c++
%%writefile Sources/transform.cu
#include "dli.h"

struct transform_iterator 
{
  int *a;

  int operator[](int i) 
  {
    return a[i] * 2;
  }
};

int main() 
{
  std::array<int, 3> a{ 0, 1, 2 };

  transform_iterator it{a.data()};

  std::printf("it[0]: %d\n", it[0]); // prints 0 (0 * 2)
  std::printf("it[1]: %d\n", it[1]); // prints 2 (1 * 2)
}
```
compile and run with:

```
!nvcc --extended-lambda -o /tmp/a.out Sources/transform.cu # build executable
!/tmp/a.out # run executable
```

### Simple Zip Iterator

We can continue to redefine the square brackets `[]` operator, to combine multiple sequences.  The zip iterator below takes two arrays and combines them into a sequence of tuples.


```c++
%%writefile Sources/zip.cu
#include "dli.h"

struct zip_iterator 
{
  int *a;
  int *b;

  std::tuple<int, int> operator[](int i) 
  {
    return {a[i], b[i]};
  }
};

int main() 
{
  std::array<int, 3> a{ 0, 1, 2 };
  std::array<int, 3> b{ 5, 4, 2 };

  zip_iterator it{a.data(), b.data()};

  std::printf("it[0]: (%d, %d)\n", std::get<0>(it[0]), std::get<1>(it[0])); // prints (0, 5)
  std::printf("it[0]: (%d, %d)\n", std::get<0>(it[1]), std::get<1>(it[1])); // prints (1, 4)
}
```
compile and run with: 


```
!nvcc --extended-lambda -o /tmp/a.out Sources/zip.cu # build executable
!/tmp/a.out # run executable
```

### Combining Input Iterators


One very powerful feature of iterators is that you can combine them with each other.  If we think about our original code above where we computed the absolute value of the difference between each element in two arrays, you can see below that we can combine, or nest, the zip_iterator with the transform_iterator to first combine the two arrays `a` and `b` with zip, and then transform them via the transform iterator with our custom operation to compute the absolute value of the differences of each successive element in the original arrays `a` and `b`.

```c++
%%writefile Sources/transform-zip.cu
#include "dli.h"

struct zip_iterator 
{
  int *a;
  int *b;

  std::tuple<int, int> operator[](int i) 
  {
    return {a[i], b[i]};
  }
};

struct transform_iterator 
{
  zip_iterator zip;

  int operator[](int i) 
  {
    auto [a, b] = zip[i];
    return abs(a - b);
  }
};

int main() 
{
  std::array<int, 3> a{ 0, 1, 2 };
  std::array<int, 3> b{ 5, 4, 2 };

  zip_iterator zip{a.data(), b.data()};
  transform_iterator it{zip};

  std::printf("it[0]: %d\n", it[0]); // prints 5
  std::printf("it[0]: %d\n", it[1]); // prints 3
}
```

compile and run with:

```
!nvcc --extended-lambda -o /tmp/a.out Sources/transform-zip.cu # build executable
!/tmp/a.out # run executable
```

### Transform Output Iterator

The concept of iterators is not limited to inputs alone.  With another level of indirection one can transform values that are written into a transform output iterator.  Note in the code below, both `=` and `[]` operators are being redefined.

```c++
%%writefile Sources/transform-output.cu
#include "dli.h"

struct wrapper
{
   int *ptr; 

   void operator=(int value) {
      *ptr = value / 2;
   }
};

struct transform_output_iterator 
{
  int *a;

  wrapper operator[](int i) 
  {
    return {a + i};
  }
};

int main() 
{
  std::array<int, 3> a{ 0, 1, 2 };
  transform_output_iterator it{a.data()};

  it[0] = 10;
  it[1] = 20;

  std::printf("a[0]: %d\n", a[0]); // prints 5
  std::printf("a[1]: %d\n", a[1]); // prints 10
}

```

compile and run with:

```
!nvcc --extended-lambda -o /tmp/a.out Sources/transform-output.cu # build executable
!/tmp/a.out # run executable
```


### Discard Iterator

```c++
%%writefile Sources/discard.cu
#include "dli.h"

struct wrapper
{
   void operator=(int value) {
      // discard value
   }
};

struct discard_iterator 
{
  wrapper operator[](int i) 
  {
    return {};
  }
};

int main() 
{
  discard_iterator it{};

  it[0] = 10;
  it[1] = 20;
}
```

```
!nvcc --extended-lambda -o /tmp/a.out Sources/discard.cu # build executable
!/tmp/a.out # run executable
```

## CUDA Fancy Iterators

CUDA Core Libraries provide a variety of iterators. 
Let's take a look at some of them as we try to improve the performance of our inner product implementation.
The first step is computing the absolute differences of corresponding vector components. 
To do that, we have to somehow make operator `*` return a pair of values, one taken from `a` and another taken from `b`.
This functionality is covered by `thrust::zip_iterator`.


```c++
%%writefile Sources/zip.cu
#include "dli.h"

int main() 
{
    // allocate and initialize input vectors
    thrust::universal_vector<float> a{ 31, 22, 35 };
    thrust::universal_vector<float> b{ 25, 21, 27 };

    // zip two vectors into a single iterator
    auto zip = thrust::make_zip_iterator(a.begin(), b.begin());

    thrust::tuple<float, float> first = *zip;
    std::printf("first: (%g, %g)\n", thrust::get<0>(first), thrust::get<1>(first));

    zip++;

    thrust::tuple<float, float> second = *zip;
    std::printf("second: (%g, %g)\n", thrust::get<0>(second), thrust::get<1>(second));
}
```

```
!nvcc --extended-lambda -o /tmp/a.out Sources/zip.cu # build executable
!/tmp/a.out # run executable
```

However, we don't need just pairs of vector components.
We need their absolute differences.
A `thrust::transform_iterator` allows us to attach a function to the dereferencing of an iterator. 
When combined with the zip iterator, it allows us to compute absolute differences without materializing them in memory.

```c++
%%writefile Sources/transform.cu
#include "dli.h"

int main() 
{
    thrust::universal_vector<float> a{ 31, 22, 35 };
    thrust::universal_vector<float> b{ 25, 21, 27 };

    auto zip = thrust::make_zip_iterator(a.begin(), b.begin());
    auto transform = thrust::make_transform_iterator(zip, []__host__ __device__(thrust::tuple<float, float> t) {
        return abs(thrust::get<0>(t) - thrust::get<1>(t));
    });

    std::printf("first: %g\n", *transform); // absolute difference of `a[0] = 31` and `b[0] = 25`

    transform++;

    std::printf("second: %g\n", *transform); // absolute difference of `a[1] = 22` and `b[1] = 21`
}
```

compile and run with:

```
!nvcc --extended-lambda -o /tmp/a.out Sources/transform.cu # build executable
!/tmp/a.out # run executable
```

The only remaining part is computing a maximum value.
We already know how to do that using `thrust::reduce`.

Now, the code below is functionally equivalent to our starting code example at the top of this notebook.  Notice we have eliminated the need for the temporary array to store the differences.


```c++
%%writefile Sources/optimized-max-diff.cu
#include "dli.h"

float max_change(const thrust::universal_vector<float>& a, 
                 const thrust::universal_vector<float>& b) 
{
    auto zip = thrust::make_zip_iterator(a.begin(), b.begin());
    auto transform = thrust::make_transform_iterator(zip, []__host__ __device__(thrust::tuple<float, float> t) {
        return abs(thrust::get<0>(t) - thrust::get<1>(t));
    });

    // compute max difference
    return thrust::reduce(thrust::device, transform, transform + a.size(), 0.0f, thrust::maximum<float>{});
}

int main() 
{
    float k = 0.5;
    float ambient_temp = 20;
    thrust::universal_vector<float> temp[] = {{ 42, 24, 50 }, { 0, 0, 0}};
    auto transformation = [=] __host__ __device__ (float temp) { return temp + k * (ambient_temp - temp); };

    std::printf("step  max-change\n");
    for (int step = 0; step < 3; step++) {
        thrust::universal_vector<float> &current = temp[step % 2];
        thrust::universal_vector<float> &next = temp[(step + 1) % 2];

        thrust::transform(thrust::device, current.begin(), current.end(), next.begin(), transformation);
        std::printf("%d     %.2f\n", step, max_change(current, next));
    }
}
```


```
!nvcc --extended-lambda -o /tmp/a.out Sources/optimized-max-diff.cu # build executable
!/tmp/a.out # run executable
```

Recall that this code is memory bound, so we'd expect that the elimination of unnecessary memory usage (in this case, temporary storage to hold the differences) should improve our performance. Let's evaluate performance of this implementation to see if it matches our intuition. 
To do that, we'll allocate much larger vectors.



```c++
%%writefile Sources/naive-vs-iterators.cu
#include "dli.h"

float naive_max_change(const thrust::universal_vector<float>& a, 
                       const thrust::universal_vector<float>& b) 
{
    thrust::universal_vector<float> diff(a.size());
    thrust::transform(thrust::device, a.begin(), a.end(), b.begin(), diff.begin(),
                      []__host__ __device__(float x, float y) {
                         return abs(x - y); 
                      });
    return thrust::reduce(thrust::device, diff.begin(), diff.end(), 0.0f, thrust::maximum<float>{});
}

float max_change(const thrust::universal_vector<float>& a, 
                 const thrust::universal_vector<float>& b) 
{
    auto zip = thrust::make_zip_iterator(a.begin(), b.begin());
    auto transform = thrust::make_transform_iterator(zip, []__host__ __device__(thrust::tuple<float, float> t) {
        return abs(thrust::get<0>(t) - thrust::get<1>(t));
    });
    return thrust::reduce(thrust::device, transform, transform + a.size(), 0.0f, thrust::maximum<float>{});
}

int main() 
{
    // allocate vectors containing 2^28 elements
    thrust::universal_vector<float> a(1 << 28);
    thrust::universal_vector<float> b(1 << 28);

    thrust::sequence(a.begin(), a.end());
    thrust::sequence(b.rbegin(), b.rend());

    auto start_naive = std::chrono::high_resolution_clock::now();
    naive_max_change(a, b);
    auto end_naive = std::chrono::high_resolution_clock::now();
    const double naive_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_naive - start_naive).count();

    auto start = std::chrono::high_resolution_clock::now();
    max_change(a, b);
    auto end = std::chrono::high_resolution_clock::now();
    const double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::printf("iterators are %g times faster than naive approach\n", naive_duration / duration);
}
```

```
!nvcc --extended-lambda -o /tmp/a.out Sources/naive-vs-iterators.cu # build executable
!/tmp/a.out # run executable
```
The resulting speedup exceeds our expectations because we included memory allocation in our measurements.


## Exercise: Computing Variance

So far, you've learned how to compute mean variance and maximal difference.
In this exercise, you'll apply techniques of extending standard algorithms that we just covered.
This time, you'll be implementing an efficient variance algorithm.
Variance is computed on a sequence of data.
It measures how far the values in the sequence are spread from the mean:

$$
\frac{\sum\left(x_{i} - \overline{x} \right)^{2}}{N}
$$

As the equation above suggests, for each value in the sequence we have to compute the squared difference between this value and mean.
We then add all those squared differences together and divide the resulting sum by `N`. 

The next exercise consists of using a transform iterator to compute the squared differences.

Transform iterator API for your reference:

```c++
int constant = 2;
auto transform_it = thrust::make_transform_iterator(
    // iterator to the beginning of the input sequence
    vector.begin(), 
    // capture constant in the lambda by value with `[name]`
    [constant]__host__ __device__(float value_from_input_sequence) { 
      // transformation of each element
      return value_from_input_sequence * constant; 
    });
```

Use `thrust::reduce` to compute the sum of squared differences. 

```c++
%%writefile Sources/variance.cu
#include "dli.h"

float variance(const thrust::universal_vector<float> &x, float mean) {
  // update the following line so that dereferencing `squared_differences`
  // returns `(xi - mean) * (xi - mean)`
  auto squared_differences = ...;

  return thrust::reduce(thrust::device, squared_differences,
                        squared_differences + x.size()) /
         x.size();
}

float mean(thrust::universal_vector<float> vec) {
  return thrust::reduce(thrust::device, vec.begin(), vec.end()) / vec.size();
}

int main() {
  float ambient_temp = 20;
  thrust::universal_vector<float> prev{42, 24, 50};
  thrust::universal_vector<float> next{0, 0, 0};

  std::printf("step  variance\n");
  for (int step = 0; step < 3; step++) {
    thrust::transform(thrust::device, prev.begin(), prev.end(), next.begin(),
                      [=] __host__ __device__(float temp) {
                        return temp + 0.5 * (ambient_temp - temp);
                      });
    std::printf("%d     %.2f\n", step, variance(next, mean(next)));
    next.swap(prev);
  }
}
```
compile and run with:
```
!nvcc --extended-lambda -o /tmp/a.out Sources/variance.cu # build executable
!/tmp/a.out # run executable
```

The output of your program should be:

| Step | Variance |
|------|----------|
| 0    | 29.56    |
| 1    | 7.39     |
| 2    | 1.85     |

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

<details>
  <summary>Hints</summary>
  
  - You can capture mean in a lambda function with `[mean]__host__ __device__ (...` 
  - You can transform the input sequence into squared differences with `thrust::transform_iterator`
  - You can create a transform iterator with `thrust::make_transform_iterator`
</details>

Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.

<details>
  <summary>Solution</summary>

  Key points:
  - use `thrust::make_transform_iterator`
  - capture mean by value in lambda

  Solution:
  ```c++
  auto squared_differences = thrust::make_transform_iterator(
    x.begin(), [mean] __host__ __device__(float value) {
      return (value - mean) * (value - mean);
    });
  ```

  You can find full solution:
  
```c++
#include "dli.h"

float variance(const thrust::universal_vector<float> &x, float mean) {
  auto squared_differences = thrust::make_transform_iterator(
      x.begin(), [mean] __host__ __device__(float value) {
        return (value - mean) * (value - mean);
      });

  return thrust::reduce(thrust::device, squared_differences,
                        squared_differences + x.size()) /
         x.size();
}

float mean(thrust::universal_vector<float> vec) {
  return thrust::reduce(thrust::device, vec.begin(), vec.end()) / vec.size();
}

int main() {
  float ambient_temp = 20;
  thrust::universal_vector<float> prev{42, 24, 50};
  thrust::universal_vector<float> next{0, 0, 0};

  std::printf("step  variance\n");
  for (int step = 0; step < 3; step++) {
    thrust::transform(thrust::device, prev.begin(), prev.end(), next.begin(),
                      [=] __host__ __device__(float temp) {
                        return temp + 0.5 * (ambient_temp - temp);
                      });
    std::printf("%d     %.2f\n", step, variance(next, mean(next)));
    next.swap(prev);
  }
}
```

```c++
#pragma once

#include <cstdio>

#include <nv/target>

#include <cstdint> // CHAR_BIT

#include <thrust/fill.h>
#include <thrust/tabulate.h>
#include <thrust/universal_vector.h>

#include <cstdio>
#include <thrust/execution_policy.h>
#include <thrust/for_each.h>
#include <thrust/iterator/constant_iterator.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/iterator/transform_iterator.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/sequence.h>
#include <thrust/universal_vector.h>

#include <cuda/std/mdspan>

namespace dli {

static __host__ __device__ bool is_executed_on_gpu() {
  NV_IF_TARGET(NV_IS_HOST, (return false;));
  return true;
}

static __host__ __device__ const char *execution_space() {
  return is_executed_on_gpu() ? "GPU" : "CPU";
}

static double max_bandwidth() {
  cudaDeviceProp prop;
  cudaGetDeviceProperties(&prop, 0);

  const std::size_t mem_freq =
      static_cast<std::size_t>(prop.memoryClockRate) * 1000; // kHz -> Hz
  const int bus_width = prop.memoryBusWidth;
  const std::size_t bytes_per_second = 2 * mem_freq * bus_width / CHAR_BIT;
  return static_cast<double>(bytes_per_second) / 1024 / 1024 /
         1024; // B/s -> GB/s
}

__host__ __device__ void I_expect(const char *expected) {
  std::printf("expect %s; runs on %s;\n", expected, execution_space());
}

} // namespace dli

namespace heat {
inline thrust::universal_vector<float> generate_random_data(int height,
                                                            int width) {
  const float low = 15.0;
  const float high = 90.0;
  thrust::universal_vector<float> data(height * width, low);
  thrust::fill(thrust::device, data.begin(), data.begin() + width, high);
  thrust::fill(thrust::device, data.end() - width, data.end(), high);
  return data;
}

template <class ContainerT>
void simulate(int height, int width, const ContainerT &in, ContainerT &out) {
  cuda::std::mdspan temp_in(thrust::raw_pointer_cast(in.data()), height, width);

  thrust::tabulate(
      thrust::device, out.begin(), out.end(), [=] __host__ __device__(int id) {
        const int column = id % width;
        const int row = id / width;

        // loop over all points in domain (except boundary)
        if (row > 0 && column > 0 && row < height - 1 && column < width - 1) {
          // evaluate derivatives
          float d2tdx2 = temp_in(row, column - 1) - 2 * temp_in(row, column) +
                         temp_in(row, column + 1);
          float d2tdy2 = temp_in(row - 1, column) - 2 * temp_in(row, column) +
                         temp_in(row + 1, column);

          // update temperatures
          return temp_in(row, column) + 0.2f * (d2tdx2 + d2tdy2);
        } else {
          return temp_in(row, column);
        }
      });
}
} // namespace heat

```
  
</details>


# Vocabulary Types

dli will be defined as:
<details>
 <summary>dli</summary>
 
```c++
// dli.h
#pragma once

#include <cstdio>

#include <nv/target>

#include <cstdint> // CHAR_BIT

#include <thrust/fill.h>
#include <thrust/tabulate.h>
#include <thrust/universal_vector.h>

#include <cstdio>
#include <thrust/execution_policy.h>
#include <thrust/for_each.h>
#include <thrust/iterator/constant_iterator.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/iterator/transform_iterator.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/sequence.h>
#include <thrust/universal_vector.h>

#include <cuda/std/mdspan>

#include <fstream>

namespace dli {

static __host__ __device__ bool is_executed_on_gpu() {
  NV_IF_TARGET(NV_IS_HOST, (return false;));
  return true;
}

static __host__ __device__ const char *execution_space() {
  return is_executed_on_gpu() ? "GPU" : "CPU";
}

static double max_bandwidth() {
  cudaDeviceProp prop;
  cudaGetDeviceProperties(&prop, 0);

  const std::size_t mem_freq =
      static_cast<std::size_t>(prop.memoryClockRate) * 1000; // kHz -> Hz
  const int bus_width = prop.memoryBusWidth;
  const std::size_t bytes_per_second = 2 * mem_freq * bus_width / CHAR_BIT;
  return static_cast<double>(bytes_per_second) / 1024 / 1024 /
         1024; // B/s -> GB/s
}

__host__ __device__ void I_expect(const char *expected) {
  std::printf("expect %s; runs on %s;\n", expected, execution_space());
}

static 
thrust::universal_vector<float> init(int height, int width)
{
  const float low  = 15.0;
  const float high = 90.0;
  thrust::universal_vector<float> data(height * width, low);
  thrust::fill(thrust::device, data.begin(), data.begin() + width, high);
  thrust::fill(thrust::device, data.end() - width, data.end(), high);
  return data;
}

static
void store(int step, int height, int width, const thrust::universal_vector<float> &data)
{
  std::ofstream file("/tmp/heat_" + std::to_string(step) + ".bin", std::ios::binary);
  file.write(reinterpret_cast<const char*>(&height), sizeof(int));
  file.write(reinterpret_cast<const char*>(&width), sizeof(int));
  file.write(reinterpret_cast<const char *>(data.data().get()), height * width * sizeof(float));
}


} // namespace dli

namespace heat {
inline thrust::universal_vector<float> generate_random_data(int height,
                                                            int width) {
  const float low = 15.0;
  const float high = 90.0;
  thrust::universal_vector<float> data(height * width, low);
  thrust::fill(thrust::device, data.begin(), data.begin() + width, high);
  thrust::fill(thrust::device, data.end() - width, data.end(), high);
  return data;
}

template <class ContainerT>
void simulate(int height, int width, const ContainerT &in, ContainerT &out) {
  cuda::std::mdspan temp_in(thrust::raw_pointer_cast(in.data()), height, width);

  thrust::tabulate(
      thrust::device, out.begin(), out.end(), [=] __host__ __device__(int id) {
        const int column = id % width;
        const int row = id / width;

        // loop over all points in domain (except boundary)
        if (row > 0 && column > 0 && row < height - 1 && column < width - 1) {
          // evaluate derivatives
          float d2tdx2 = temp_in(row, column - 1) - 2 * temp_in(row, column) +
                         temp_in(row, column + 1);
          float d2tdy2 = temp_in(row - 1, column) - 2 * temp_in(row, column) +
                         temp_in(row + 1, column);

          // update temperatures
          return temp_in(row, column) + 0.2f * (d2tdx2 + d2tdy2);
        } else {
          return temp_in(row, column);
        }
      });
}
} // namespace heat

void simulate(int height, int width, 
              const thrust::universal_vector<float> &in,
                    thrust::universal_vector<float> &out);

int main() 
{
  int height = 256;
  int width = 1024;

  thrust::universal_vector<float> prev = dli::init(height, width);
  thrust::universal_vector<float> next(height * width);

  for (int write_step = 0; write_step < 100; write_step++) 
  {
    for (int compute_step = 0; compute_step < 100; compute_step++) 
    {
      simulate(height, width, prev, next);
      next.swap(prev);
    }

    dli::store(write_step, height, width, prev);
  }
}

```

```
#dli.py
import subprocess
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from IPython.display import HTML
import numpy as np
import glob
import os


def run(filename):
    for file in glob.glob('/tmp/heat_*'):
        os.remove(file)

    if os.path.exists('/tmp/a.out'):
        os.remove('/tmp/a.out')

    # Execute commands above
    result = subprocess.run(
        ['nvcc', '--extended-lambda', '-o', '/tmp/a.out', filename])
    if result.returncode != 0:
        print(result.stdout)
        print(result.stderr)
    subprocess.run(['/tmp/a.out'])

    img = None
    fig = plt.figure(figsize=(8, 2))
    fig.tight_layout()

    def drawframe(i):
        with open(f"/tmp/heat_{i}.bin", 'rb') as f:
            height, width = np.fromfile(f, dtype=np.int32, count=2)
            data = np.fromfile(f, dtype=np.float32, count=height * width)
            data = data.reshape((height, width))

        nonlocal img
        if img is None:
            img = plt.imshow(data, cmap='hot', interpolation='none', vmin=10)
        else:
            img.set_data(data)
        return img,

    ani = animation.FuncAnimation(
        fig, drawframe, frames=100, interval=20, blit=True)
    plt.close(fig)  # Suppress the figure display
    return HTML(ani.to_html5_video())

```

</details>



---
## Naive Heat Transfer

You've learned enough tools and concepts to improve our small heat simulator. 

Below is the code for the naive `simulate` function.  Execute the following two cells to run the code and observe the heat transfer via a visualization.  Note the use of `thrust::transform` and also `thrust::make_counting_iterator(0)`.

```c++
%%writefile Sources/naive-heat-2D.cu
#include "dli.h"

void simulate(int height, int width, 
              const thrust::universal_vector<float> &in,
                    thrust::universal_vector<float> &out) 
{
  const float *in_ptr = thrust::raw_pointer_cast(in.data());

  auto cell_indices = thrust::make_counting_iterator(0);
  thrust::transform(
      thrust::device, cell_indices, cell_indices + in.size(), out.begin(),
      [in_ptr, height, width] __host__ __device__(int id) {
        int column = id % width;
        int row = id / width;

        if (row > 0 && column > 0 && row < height - 1 && column < width - 1) {
          float d2tdx2 = in_ptr[(row) * width + column - 1] - 2 * in_ptr[row * width + column] + in_ptr[(row) * width + column + 1];
          float d2tdy2 = in_ptr[(row - 1) * width + column] - 2 * in_ptr[row * width + column] + in_ptr[(row + 1) * width + column];

          return in_ptr[row * width + column] + 0.2f * (d2tdx2 + d2tdy2);
        } else {
          return in_ptr[row * width + column];
        }
      });
}
```

```py
import Sources.dli
Sources.dli.run("Sources/naive-heat-2D.cu")
```

## Thrust Tabulate

The Thrust library has another function called `tabulate` that applies an operator to element indices and stores the result at the same index.  It is essentially the equivalent of the above example of transformation of the counting iterator.

Execute the following two cells to illustrate the heat transfer function with the `thrust::tabulate` function.

```c++
%%writefile Sources/tabulate.cu
#include "dli.h"

void simulate(int height, int width,
              const thrust::universal_vector<float> &in,
                    thrust::universal_vector<float> &out)
{
  const float *in_ptr = thrust::raw_pointer_cast(in.data());

  thrust::tabulate(
    thrust::device, out.begin(), out.end(), 
    [in_ptr, height, width] __host__ __device__(int id) {
      int column = id % width;
      int row = id / width;

      if (row > 0 && column > 0 && row < height - 1 && column < width - 1) {
        float d2tdx2 = in_ptr[(row) * width + column - 1] - 2 * in_ptr[row * width + column] + in_ptr[(row) * width + column + 1];
        float d2tdy2 = in_ptr[(row - 1) * width + column] - 2 * in_ptr[row * width + column] + in_ptr[(row + 1) * width + column];

        return in_ptr[row * width + column] + 0.2f * (d2tdx2 + d2tdy2);
      } else {
        return in_ptr[row * width + column];
      }
    });
}
```
```
import Sources.dli
Sources.dli.run("Sources/tabulate.cu")
```

## Code Reuse

You may have noticed that in the body of the function we are doing some involved offset arithmetic to index into the correct values of the array that we're working with.  Since we are in C++, we are doing these offset calculations in row major order and we can use the `make_pair` function to do this arithmetic for us once, instead of calculating `row` and `column` repeatedly.

Execute the following two cells to illustrate the use of `make_pair` to create the function `row_col`.


```c++
%%writefile Sources/std-pair.cu
#include "dli.h"

__host__ __device__
std::pair<int, int> row_col(int id, int width) {
    return std::make_pair(id / width, id % width);
}

void simulate(int height, int width,
              const thrust::universal_vector<float> &in,
                    thrust::universal_vector<float> &out)
{
  const float *in_ptr = thrust::raw_pointer_cast(in.data());

  thrust::tabulate(
    thrust::device, out.begin(), out.end(), 
    [in_ptr, height, width] __host__ __device__(int id) {
      auto [row, column] = row_col(id, width);

      if (row > 0 && column > 0 && row < height - 1 && column < width - 1) {
        float d2tdx2 = in_ptr[(row) * width + column - 1] - 2 * in_ptr[row * width + column] + in_ptr[(row) * width + column + 1];
        float d2tdy2 = in_ptr[(row - 1) * width + column] - 2 * in_ptr[row * width + column] + in_ptr[(row + 1) * width + column];

        return in_ptr[row * width + column] + 0.2f * (d2tdx2 + d2tdy2);
      } else {
        return in_ptr[row * width + column];
      }
    });
}
```
compile and run with:
```
!nvcc --extended-lambda -std=c++17 -o /tmp/a.out Sources/std-pair.cu
```
If you didn't change any code, you'll have encountered a warning message similar to the following:

`calling a __host__ function("make_pair") from a __host__ __device__ function("row_col") is not allowed.`

`std::make_pair` is a host function, not a device function.  Thinking back to the earlier part of our course, a host function is compiled to run on the host, and if there is no equivalent device function, that code will NOT run on the device.  That is what the error message is telling us, i.e., we don't have any device function called `std::make_pair` and therefore it can't run on the device.

Fortunately NVIDIA has implemented many of these standard types in CUDA via the [libcu++](https://nvidia.github.io/cccl/libcudacxx/) library, and for the `std::` types implemented in `libcu++`, it's as simple as prepending `cuda::` in front of the `std::` types you're using.

Notice below the code is identical to the previous example, with the two small changes of prepending `cuda::` in front of both `std::pair` and `std::make_pair`.

Run the code and observe that it compiles and runs without error.


```c++


%%writefile Sources/pair.cu
#include "dli.h"

__host__ __device__
cuda::std::pair<int, int> row_col(int id, int width) {
    return cuda::std::make_pair(id / width, id % width);
}

void simulate(int height, int width,
              const thrust::universal_vector<float> &in,
                    thrust::universal_vector<float> &out)
{
  const float *in_ptr = thrust::raw_pointer_cast(in.data());

  thrust::tabulate(
    thrust::device, out.begin(), out.end(), 
    [in_ptr, height, width] __host__ __device__(int id) {
      auto [row, column] = row_col(id, width);

      if (row > 0 && column > 0 && row < height - 1 && column < width - 1) {
        float d2tdx2 = in_ptr[(row) * width + column - 1] - 2 * in_ptr[row * width + column] + in_ptr[(row) * width + column + 1];
        float d2tdy2 = in_ptr[(row - 1) * width + column] - 2 * in_ptr[row * width + column] + in_ptr[(row + 1) * width + column];

        return in_ptr[row * width + column] + 0.2f * (d2tdx2 + d2tdy2);
      } else {
        return in_ptr[row * width + column];
      }
    });
}
```

```
import Sources.dli
Sources.dli.run("Sources/pair.cu")
```

## `mdspan`

`pair` is not the only vocabulary type that will improve our code.  Consider how we are manually flattening the 2D coordinates to access the 1D array.  This approach is error-prone and makes the code difficult to read and understand.  Additionally, consider situations where more than 2D coordinates are being used; the complexity of the pointer indexing will rapidly increase!

For the section exercise, we'll explore the use of `mdspan`, which is a vocabulary type used to make this type of indexing much easier.  See a simple use of `mdspan` below.


```c++
%%writefile Sources/mdspan-intro.cu

#include <cuda/std/mdspan>
#include <cuda/std/array>
#include <cstdio>

int main() {
  cuda::std::array<int, 6> sd {0, 1, 2, 3, 4, 5};
  cuda::std::mdspan md(sd.data(), 2, 3);

  std::printf("md(0, 0) = %d\n", md(0, 0)); // 0
  std::printf("md(1, 2) = %d\n", md(1, 2)); // 5

  std::printf("size   = %zu\n", md.size());    // 6
  std::printf("height = %zu\n", md.extent(0)); // 2
  std::printf("width  = %zu\n", md.extent(1)); // 3
}
```

```
!nvcc -std=c++17 -o /tmp/a.out Sources/mdspan-intro.cu && /tmp/a.out
```


## Exercise: `mdspan`

Usage of `cuda::std::mdspan` API for your reference:
```cpp
int height = 2;
int width = 3;
cuda::std::array<int, 6> sd {0, 1, 2, 3, 4, 5};
cuda::std::mdspan md(sd.data(), height, width);

std::printf("md(0, 0) = %d\n", md(0, 0)); // 0
std::printf("md(1, 2) = %d\n", md(1, 2)); // 5

std::printf("size   = %zu\n", md.size());    // 6
std::printf("height = %zu\n", md.extent(0)); // 2
std::printf("width  = %zu\n", md.extent(1)); // 3
```

Complete the exercise below by adding the use of `cuda::std::mdspan` instead of dereferencing the raw pointer via pointer offset arithmetic.


<details>
<summary>Original heat-2D.cu code in case you need to refer back to it.</summary>

```c++
%%writefile Sources/heat-2D.cu
#include "dli.h"

__host__ __device__
cuda::std::pair<int, int> row_col(int id, int width) {
    return cuda::std::make_pair(id / width, id % width);
}

void simulate(int height, int width,
              const thrust::universal_vector<float> &in,
                    thrust::universal_vector<float> &out)
{
  const float *in_ptr = thrust::raw_pointer_cast(in.data());

  thrust::tabulate(
    thrust::device, out.begin(), out.end(), 
    [in_ptr, height, width] __host__ __device__(int id) {
      auto [row, column] = row_col(id, width);

      if (row > 0 && column > 0 && row < height - 1 && column < width - 1) {
        float d2tdx2 = in_ptr[(row) * width + column - 1] - 2 * in_ptr[row * width + column] + in_ptr[(row) * width + column + 1];
        float d2tdy2 = in_ptr[(row - 1) * width + column] - 2 * in_ptr[row * width + column] + in_ptr[(row + 1) * width + column];

        return in_ptr[row * width + column] + 0.2f * (d2tdx2 + d2tdy2);
      } else {
        return in_ptr[row * width + column];
      }
    });
}
```

</details>



```c++
%%writefile Sources/heat-2D.cu
#include "dli.h"

__host__ __device__
cuda::std::pair<int, int> row_col(int id, int width) {
    return cuda::std::make_pair(id / width, id % width);
}

void simulate(int height, int width,
              const thrust::universal_vector<float> &in,
                    thrust::universal_vector<float> &out)
{
  const float *in_ptr = thrust::raw_pointer_cast(in.data());

  thrust::tabulate(
    thrust::device, out.begin(), out.end(), 
    [in_ptr, height, width] __host__ __device__(int id) {
      auto [row, column] = row_col(id, width);

      if (row > 0 && column > 0 && row < height - 1 && column < width - 1) {
        float d2tdx2 = in_ptr[(row) * width + column - 1] - 2 * in_ptr[row * width + column] + in_ptr[(row) * width + column + 1];
        float d2tdy2 = in_ptr[(row - 1) * width + column] - 2 * in_ptr[row * width + column] + in_ptr[(row + 1) * width + column];

        return in_ptr[row * width + column] + 0.2f * (d2tdx2 + d2tdy2);
      } else {
        return in_ptr[row * width + column];
      }
    });
}
```

```
import Sources.dli
Sources.dli.run("Sources/heat-2D.cu")
```

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

<details>
  <summary>Hints</summary>
  
  - `cuda::std::mdspan` constructor takes a pointer followed by the height and width of the 2D array
  - Two-dimensional `cuda::std::mdpsan` provides `operator()(int row, int column)` to access elements
</details>


Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.

<details>
  <summary>Solution</summary>

  Key points:

  - You can use `md.extent(0)` and `md.extent(1)` to get the height and width of the 2D array

  Solution:
  ```cpp
  cuda::std::mdspan temp_in(thrust::raw_pointer_cast(in.data()), height, width);

  thrust::tabulate(thrust::device, out.begin(), out.end(), [temp_in] __host__ __device__(int id) {
    int column = id % temp_in.extent(1);
    int row    = id / temp_in.extent(1);

    if (row > 0 && column > 0 && row < temp_in.extent(0) - 1 && column < temp_in.extent(1) - 1)
    {
      float d2tdx2 = temp_in(row, column - 1) - 2 * temp_in(row, column) + temp_in(row, column + 1);
      float d2tdy2 = temp_in(row - 1, column) - 2 * temp_in(row, column) + temp_in(row + 1, column);

      return temp_in(row, column) + 0.2f * (d2tdx2 + d2tdy2);
    }
    else
    {
      return temp_in(row, column);
    }
  });
  ```
</details>

# Serial vs Parallel

## Segmented Sum

This time, let's say we are interested in the segment close to the heat source. 
Let's try changing the grid size to "zoom" in into that part.
Instead of looking at the visualization, we'll be looking at the total temperature in each row.
This row-based computation can be framed as a segmented problem. A *segmented sum* is defined as taking a single input array and, given a segment size, calculating the sum of each segment.

// image segmented sum


We could build a segmented sum on top of `thrust::tabulate`. 
The `tabulate` algorithm receives a sequence and a function.
It then applies this function to index of each element in the sequence, and stores the result into the provided sequence.
For example, after the following invocation:

```c++
thrust::universal_vector<int> vec(4);
thrust::tabulate(
   thrust::device, vec.begin(), vec.end(), 
   []__host__ __device__(int index) -> int { 
      return index * 2; 
   });
```

`vec` would store `{0, 2, 4, 6}`. 
We can use this algorithm to implement our segmented sum as follows:

```c++
thrust::universal_vector<float> sums(num_segments);
thrust::tabulate(
   thrust::device, sums.begin(), sums.end(), 
   []__host__ __device__(int segment_id) -> float {
      return compute_sum_for(segment_id);
   });
```

As we implement the algorithm, let's consider its performance from a new perspective.
Reduction is a memory-bound algorithm.
This means that instead of analyzing its performance in terms of elapsed time,
we could take a look at how many bytes does our implementation process in a second.
This metric is called _achieved throughput_. 
By contrasting it with the peak theoretical bandwidth of our GPU,
we'll understand if our implementation is efficient or not.

```c++
%%writefile Sources/naive-segmented-sum.cu
#include <cstdio>
#include <chrono>

#include <thrust/tabulate.h>
#include <thrust/execution_policy.h>
#include <thrust/universal_vector.h>

thrust::universal_vector<float> row_temperataures(
    int height, int width,
    const thrust::universal_vector<float>& temp) 
{
    // allocate vector to store sums
    thrust::universal_vector<float> sums(height);

    // take raw pointer to `temp`
    const float *d_temp_ptr = thrust::raw_pointer_cast(temp.data());

    // compute row sum
    thrust::tabulate(thrust::device, sums.begin(), sums.end(), [=]__host__ __device__(int row_id) {
        float sum = 0;
        for (int i = 0; i < width; i++) {
            sum += d_temp_ptr[row_id * width + i];
        }
        return sum; 
    });

    return sums;
}

thrust::universal_vector<float> init(int height, int width) {
  const float low = 15.0;
  const float high = 90.0;
  thrust::universal_vector<float> temp(height * width, low);
  thrust::fill(thrust::device, temp.begin(), temp.begin() + width, high);
  return temp;
}

int main() 
{
    int height = 16;
    int width = 16777216;
    thrust::universal_vector<float> temp = init(height, width);

    auto begin = std::chrono::high_resolution_clock::now();
    thrust::universal_vector<float> sums = row_temperataures(height, width, temp);
    auto end = std::chrono::high_resolution_clock::now();
    const double seconds = std::chrono::duration<double>(end - begin).count();
    const double gigabytes = static_cast<double>(temp.size() * sizeof(float)) / 1024 / 1024 / 1024;
    const double throughput = gigabytes / seconds;

    std::printf("computed in %g s\n", seconds);
    std::printf("achieved throughput: %g GB/s\n", throughput);
}
```
compile and run with:
```
!nvcc --extended-lambda -o /tmp/a.out Sources/naive-segmented-sum.cu # build executable
!/tmp/a.out # run executable
```


Let's take a look at the achieved throughput and contrast it with maximal bandwidth.
Out implementation achieves less than a percent of what GPU can provide.
The reason our implementation underperforms is due to the way we used `thrust::tabulate`:

```c++
thrust::tabulate(thrust::device, sums.begin(), sums.end(), [=]__host__ __device__(int segment_id) {
    float sum = 0;
    for (int i = 0; i < segment_size; i++) {
        sum += d_values_ptr[segment_id * segment_size + i];
    }
    return sum; 
});
```

## Reduce by Key

GPUs are massively parallel processors.
That said, code that ends up being executed by GPU doesn't get magically parallelized.
The `for` loop in the operator we provided to `thrust::tabulate` is executed sequentially. 
Tabulate could process each of the 16 elements in parallel, while the operator processes over 16 million elements.
To fix performance, let's try increasing parallelism.

To do that, we can try the `thrust::reduce_by_key` algorithm, which is a generalization of the `thrust::reduce` algorithm. 
Instead of reducing the sequence into a single value,
it allows you to reduce segments of values. 
To distinguish these segments, you have to provide keys. 
Consecutive keys that are equal form a *segment*.
As the output, `reduce_by_key` returns one value per segment. 

For example:

```c++
int in_keys[] = {1, 1, 1, 3, 3};
int in_vals[] = {1, 2, 3, 4, 5};
int out_keys[2];
int out_vals[2];

thrust::reduce_by_key(in_keys, in_keys + 5, in_vals, out_keys, out_vals);
// out_keys = {1, 3}
// out_vals = {6, 9}
```

Lets try to frame our segmented sum in terms of reduce by key:

```c++
%%writefile Sources/reduce-by-key.cu
#include "dli.h"

thrust::universal_vector<float> row_temperatures(
    int height, int width,
    thrust::universal_vector<int>& row_ids,
    thrust::universal_vector<float>& temp)
{
    thrust::universal_vector<float> sums(height);
    thrust::reduce_by_key(
        thrust::device, 
        row_ids.begin(), row_ids.end(),   // input keys 
        temp.begin(),                     // input values
        thrust::make_discard_iterator(),  // output keys
        sums.begin());                    // output values

    return sums;
}
```
compile and run with:
```
!nvcc --extended-lambda -o /tmp/a.out Sources/reduce-by-key.cu # build executable
!/tmp/a.out # run executable
```
We are not interested in output keys, so we made a `discard` iterator. 
This technique often helps you save memory bandwidth when you don't need certain parts of the algorithm's output.
Speaking of bandwidth, we've got much better results now. 
That's because we eliminated the serialization that was dominating execution time. 
However, there's still an issue: Now we are reading keys.

## Exercise: Segmented Sum Optimization

Below is an example of the `transform` iterator API:

```c++
int constant = 2;
auto transform_it = thrust::make_transform_iterator(
    // iterator to the beginning of the input sequence
    vector.begin(), 
    // capture constant in the lambda by value with `[name]`
    [constant]__host__ __device__(float value_from_input_sequence) { 
      // transformation of each element
      return value_from_input_sequence * constant; 
    });
```

Here's an example of the Counting iterator API:

```c++
// start counting from 0
auto count_it = thrust::make_counting_iterator(0);
```

Rewrite the segmented sum code below without materializing keys in memory.


<details>
    <summary>Copy of the original code in case you need to refer back to it.</summary>

```c++
%%writefile Sources/segmented-sum-optimization.cu
#include "dli.h"

thrust::universal_vector<float> row_temperatures(
    int height, int width,
    thrust::universal_vector<int>& row_ids,
    thrust::universal_vector<float>& temp)
{
    thrust::universal_vector<float> sums(height);

    // Modify line below to use counting and transform iterators to 
    // generates row indices `id / width` instead
    auto row_ids_begin = row_ids.begin(); 
    auto row_ids_end = row_ids_begin + temp.size();

    thrust::reduce_by_key(thrust::device, 
                          row_ids_begin, row_ids_end, 
                          temp.begin(), 
                          thrust::make_discard_iterator(), 
                          sums.begin());

    return sums;
}
```  

</details>

```c++
%%writefile Sources/segmented-sum-optimization.cu
#include "dli.h"

thrust::universal_vector<float> row_temperatures(
    int height, int width,
    thrust::universal_vector<int>& row_ids,
    thrust::universal_vector<float>& temp)
{
    thrust::universal_vector<float> sums(height);

    // Modify the line below to use counting and transform iterators to 
    // generates row indices `id / width` instead
    auto row_ids_begin = row_ids.begin(); 
    auto row_ids_end = row_ids_begin + temp.size();

    thrust::reduce_by_key(thrust::device, 
                          row_ids_begin, row_ids_end, 
                          temp.begin(), 
                          thrust::make_discard_iterator(), 
                          sums.begin());

    return sums;
}
```
compile and run with:
```
!nvcc --extended-lambda -o /tmp/a.out --run Sources/segmented-sum-optimization.cu 
```

The output of your program should end with:

```
row 0: { 90, 90, ..., 90 } = 1.50995e+09
row 1: { 15, 15, ..., 15 } = 2.51658e+08
row 2: { 15, 15, ..., 15 } = 2.51658e+08
```

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

<details>
  <summary>Hints</summary>
  
  - Combine `transform` and `counting` iterators to generate row indices
</details>


Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.

<details>
  <summary>Solution</summary>

  Key points:

  - `thrust::make_counting_iterator(0)` creates an integer sequence of cell indices
  - `thrust::make_transform_iterator` converts cell indices to row indices by dividing by `width`

  Solution:
  ```c++
  auto row_ids_begin = thrust::make_transform_iterator(
      thrust::make_counting_iterator(0),
      [=] __host__ __device__(int i) { return i / width; });
  ```

```c++
#include "dli.h"

thrust::universal_vector<float> row_temperatures(
    int height, int width,
    thrust::universal_vector<int>& row_ids,
    thrust::universal_vector<float>& temp)
{
    thrust::universal_vector<float> sums(height);

    // Modify the line below to use counting and transform iterators to 
    // generates row indices `id / width` instead
    auto row_ids_begin = row_ids.begin(); a
    auto row_ids_end = row_ids_begin + temp.size();

    thrust::reduce_by_key(thrust::device, 
                          row_ids_begin, row_ids_end, 
                          temp.begin(), 
                          thrust::make_discard_iterator(), 
                          sums.begin());

    return sums;
}

```

</details>

## Exercise: Segmented Mean

The total raw temperature was a bit hard to read. 
What we are actually interested in is the mean temperature rather than total temperature.
So far, we've used different input iterators to extend algorithms.
But fancy iterators are not limited to that.

Here's an example of the usage of a transform output iterator:

```c++
struct functor {
  __host__ __device__ 
  float operator()(float value_about_to_be_stored_in_output_sequence) const 
  { 
    // will store value / 2 in the output sequence instead of the original value
    return value_about_to_be_stored_in_output_sequence / 2; 
  }
};

auto transform_output_it = 
  thrust::make_transform_output_iterator(
    // iterator to the beginning of the output sequence
    vector.begin(), 
    // functor to apply to value before it's written to the `vector`
    functor{});
```

In this exercise, you'll have to modify `row_temperature` so it computes the segmented mean. 
Use `transform_output_iterator` to turn the total temperature into the mean and remove the `thrust::transform` call.

<details>
    <summary>Original code in case you need to refer back to it</summary>
    
```c++
%%writefile Sources/segmented-mean.cu
#include "dli.h"

struct mean_functor {
    int width;
    __host__ __device__ float operator()(float x) const {
        return x / width;
    }
};

thrust::universal_vector<float> row_temperatures(
    int height, int width,
    thrust::universal_vector<int>& row_ids,
    thrust::universal_vector<float>& temp)
{
    thrust::universal_vector<float> means(height);

    // use `transform_output_iterator` instead of `means.begin()`
    auto means_output = means.begin(); 

    auto row_ids_begin = thrust::make_transform_iterator(
        thrust::make_counting_iterator(0), 
        [=]__host__ __device__(int i) {
            return i / width;
        });
    auto row_ids_end = row_ids_begin + temp.size();

    thrust::reduce_by_key(thrust::device, 
                          row_ids_begin, 
                          row_ids_end, 
                          temp.begin(), 
                          thrust::make_discard_iterator(), 
                          means_output);

    auto transform_op = mean_functor{width};

    // remove this `transform` call
    thrust::transform(thrust::device, 
                      means.begin(), 
                      means.end(), 
                      means.begin(), 
                      transform_op);

    return means;
}   
```

</details>

```c++
%%writefile Sources/segmented-mean.cu
#include "dli.h"

struct mean_functor {
    int width;
    __host__ __device__ float operator()(float x) const {
        return x / width;
    }
};

thrust::universal_vector<float> row_temperatures(
    int height, int width,
    thrust::universal_vector<int>& row_ids,
    thrust::universal_vector<float>& temp)
{
    thrust::universal_vector<float> means(height);

    // use `transform_output_iterator` instead of `means.begin()`
    auto means_output = means.begin(); 

    auto row_ids_begin = thrust::make_transform_iterator(
        thrust::make_counting_iterator(0), 
        [=]__host__ __device__(int i) {
            return i / width;
        });
    auto row_ids_end = row_ids_begin + temp.size();

    thrust::reduce_by_key(thrust::device, 
                          row_ids_begin, 
                          row_ids_end, 
                          temp.begin(), 
                          thrust::make_discard_iterator(), 
                          means_output);

    auto transform_op = mean_functor{width};

    // remove this `transform` call
    thrust::transform(thrust::device, 
                      means.begin(), 
                      means.end(), 
                      means.begin(), 
                      transform_op);

    return means;
}
```
compile and run with:
```
!nvcc --extended-lambda -o /tmp/a.out Sources/segmented-mean.cu # build executable
!/tmp/a.out # run executable
```
The output of your program should end with:

```
row 0: { 90, 90, ..., 90 } = 90
row 1: { 15, 15, ..., 15 } = 15
row 2: { 15, 15, ..., 15 } = 15
```

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

<details>
  <summary>Hints</summary>
  
  - The `transform_output_iterator` has the same API as the `transform` iterator
</details>

Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.

<details>
  <summary>Solution</summary>

  Key points:

  - We need to divide the sum by the number of elements in each segment to get the mean
  - We can use a `transform_output_iterator` to divide the sum by the number of elements in each segment

  Solution:
  ```c++
  auto means_output =
      thrust::make_transform_output_iterator(
        means.begin(), 
        mean_functor{width});
  ```
</details>



# Memory Spaces

---
At the beginning of this section, we covered execution spaces but left one change without explanation.
We replaced `std::vector` with `thrust::universal_vector`.
By the end of this lab, you'll understand why this change was necessary.

But before we start, let's try to figure out why GPUs are so good at massive parallelism.
Many benefits of GPUs result focusing on high throughput.
To support massive compute that GPUs are able of sustaining, 
we have to provide memory speed that matches these capabilities.
This essentially means that memory also has to be throughput-oriented.
That's why GPUs often come with built-in high-bandwidth memory rather than relying on system memory.
Let's return to our code to see how it's affected by this fact.


```c++
%%writefile Sources/heat-2D.cu
#include "dli.h"

int main()
{
  int height = 4096;
  int width  = 4096;

  thrust::universal_vector<float> prev = dli::init(height, width);
  thrust::universal_vector<float> next(height * width);

  for (int write_step = 0; write_step < 3; write_step++) {
    std::printf("   write step %d\n", write_step);
    dli::store(write_step, height, width, prev);
    
    for (int compute_step = 0; compute_step < 3; compute_step++) {
      auto begin = std::chrono::high_resolution_clock::now();
      dli::simulate(height, width, prev, next);
      auto end = std::chrono::high_resolution_clock::now();
      auto seconds = std::chrono::duration<double>(end - begin).count();
      std::printf("computed step %d in %g s\n", compute_step, seconds);
      prev.swap(next);
    }
  }
}
```

In the code above, we allocate data in `thrust::universal_vector`.
Then, `dli::store` accesses content of this vector on CPU to store results on disk.
After that, the data is repeatedly accessed by the GPU in the `dli::simulate` function.
This is a bit suspicious. 
We just said that CPU and GPU have distinct memory spaces, 
but we are not seeing anything that'd reflect this in the code.
Maybe performance can reveal something?


compile and run with:

```
!nvcc --extended-lambda -o /tmp/a.out Sources/heat-2D.cu # build executable
!/tmp/a.out # run executable
```

There's a strange pattern in the execution times. 
Every time we write data, the next compute step takes 100 times longer to compute.
This happens because the data is being implicitly copied between CPU and GPU memory spaces.

//Implicit Memory Transfers image - managed.png

Let's say our data resides in the GPU memory.
When `dli::store` accesses it, the data has to be copied to the CPU memory.
Next, when we call `dli::simulate`, the data is being accessed by the GPU, so the data has to be copied back.
So `thrust::universal_vector` works as a vector that lives in both CPU and GPU memory spaces and automatically migrates between them.
The problem is that we know that `dli::store` is not modifying the data, so the copy back to the GPU is unnecessary.
Fortunately, we can avoid this extra copy by using explicit memory spaces.

## Host and Device Memory Spaces

Presense of distinct host and device memory spaces is a fundamental concept in GPU programming.
For you, as a software engineer, this means that in addition to thinking about where code runs, 
you also have to keep in mind where the bytes that this code accesses live.
On a high level, we have a **host memory space** and a **device memory space**.
Thrust provides container types that manage memory in the associated memory spaces.
Let's take a look at a program that allocates vectors in corresponding memory spaces:

```c++
thrust::host_vector<int> h_vec{ 11, 12 };
thrust::device_vector<int> d_vec{ 21, 22 };
thrust::copy_n(h_vec.begin(), 1, d_vec.begin());
```

Let's take a look at this code step by step.
We started by allocating a vector with two element in host memory.
We initialized these two elements with `11` and `12`:

```c++
thrust::host_vector<int> h_vec{ 11, 12 };
```

Functionally, there's little difference between `std::vector` and `thrust::host_vector`.
As you learn, we suggest using `thrust::host_vector` just to make memory space more pronounced.
Besides host vector, we also allocated device one:

```c++
thrust::device_vector<int> d_vec{ 21, 22 };
```

We then copied one element from host memory space to device memory space using Thrust copy algorithm.
In general, copy is one of the few algorithms that you can provide mixed memory spaces.

```c++
thrust::copy_n(h_vec.begin(), 1, d_vec.begin());
```

// memory.png 
<img src="Images/memory.png" alt="Memory Spaces" width=800>

---
For now, it's safe to assume that:

- Device memory space is accessible from device execution space
- Host memory space is accessible from host execution space
- Thrust data movement algorithms can copy data between memory spaces

Let's try to internalize these points by practical examples.


## Exercise: Explicit Memory Spaces

Usage of `thrust::copy` for your reference:

```c++
thrust::copy(src_vector.begin(), src_vector.end(), dst_vector.begin());
```

Rewrite the code below to use `thrust::device_vector` and `thrust::host_vector`:

<details>
<summary>Original code in case you need to refer to it.</summary>

```c++
%%writefile Sources/heat-2D-explicit-memory-spaces.cu
#include "dli.h"

int main()
{
  int height = 4096;
  int width  = 4096;

  thrust::universal_vector<float> prev = dli::init(height, width);
  thrust::universal_vector<float> next(height * width);

  for (int write_step = 0; write_step < 3; write_step++) {
    std::printf("   write step %d\n", write_step);
    dli::store(write_step, height, width, prev);
    
    for (int compute_step = 0; compute_step < 3; compute_step++) {
      auto begin = std::chrono::high_resolution_clock::now();
      dli::simulate(height, width, prev, next);
      auto end = std::chrono::high_resolution_clock::now();
      auto seconds = std::chrono::duration<double>(end - begin).count();
      std::printf("computed step %d in %g s\n", compute_step, seconds);
      prev.swap(next);
    }
  }
}
```
    
</details>

```c++
%%writefile Sources/heat-2D-explicit-memory-spaces.cu
#include "dli.h"

int main()
{
  int height = 4096;
  int width  = 4096;

  thrust::universal_vector<float> prev = dli::init(height, width);
  thrust::universal_vector<float> next(height * width);

  for (int write_step = 0; write_step < 3; write_step++) {
    std::printf("   write step %d\n", write_step);
    dli::store(write_step, height, width, prev);
    
    for (int compute_step = 0; compute_step < 3; compute_step++) {
      auto begin = std::chrono::high_resolution_clock::now();
      dli::simulate(height, width, prev, next);
      auto end = std::chrono::high_resolution_clock::now();
      auto seconds = std::chrono::duration<double>(end - begin).count();
      std::printf("computed step %d in %g s\n", compute_step, seconds);
      prev.swap(next);
    }
  }
}
```
compile and run with:
```
!nvcc --extended-lambda -o /tmp/a.out Sources/heat-2D-explicit-memory-spaces.cu # build executable
!/tmp/a.out # run executable
```
If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

<details>
  <summary>Hints</summary>
  
  - `dli::simulate` should accept `thrust::device_vector` as input and output
  - `dli::store` should accept `thrust::host_vector` as input
  - You can use `thrust::copy` to copy data between `thrust::device_vector` and `thrust::host_vector`
</details>

Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.

<details>
  <summary>Solution</summary>

  Key points:

  - 

  Solution:
  ```c++
  thrust::device_vector<float> d_prev = dli::init(height, width);
  thrust::device_vector<float> d_next(height * width);
  thrust::host_vector<float> h_prev(height * width);

  for (int write_step = 0; write_step < 3; write_step++) {
    std::printf("   write step %d\n", write_step);
    thrust::copy(d_prev.begin(), d_prev.end(), h_prev.begin());
    dli::store(write_step, height, width, h_prev);

    for (int compute_step = 0; compute_step < 3; compute_step++) {
      auto begin = std::chrono::high_resolution_clock::now();
      dli::simulate(height, width, d_prev, d_next);
      auto end = std::chrono::high_resolution_clock::now();
      auto seconds = std::chrono::duration<double>(end - begin).count();
      std::printf("computed step %d in %g s\n", compute_step, seconds);
      d_prev.swap(d_next);
    }
  }
  ```
</details>

# CUDA Made Easy: Summary

Congratulations on completing the first part of the course!  You have accomplished all of the following lab objectives:

- Understand the differences between parallel and serial algorithms
- Control where your C++ code runs and run it on CPU or GPU
- Control whether your data resides in CPU or GPU memory and how to move between them 
- Refactor standard algorithms to execute on GPU
- Leverage powerful parallel algorithms that simplify adding GPU acceleration to your code
- Use fancy iterators to fuse operations and extend algorithms to fit your unique use cases


---

## Key Takeaways

Let's review a few key points from this part of the course.

// image: takeaway_1_1

### Leverage accelerated libraries whenever you can.
Existing libraries are already tuned to make the most of GPU hardware. 
For example, use Thrust for general-purpose parallel algorithms and container management.
Use cuSPARSE when you need GPU-accelerated sparse linear algebra functions.
Use MatX for array-based numerical computing, etc.

// image: takeaway_1_2

### When writing your CUDA code, remember the difference between execution specifiers and policies:
Use __host__ __device__ execution space specifiers to specify where given function could be executed.
Use thrust::host and thrust::device execution policies to specify where given thrust algorithm will be executed.

// image: takeaway_1_3

### Avoid serialization as much as possible.


// image: takeaway_1_4


### Where possible, use explicit memory spaces to avoid unexpected slowdowns. 
Rather than relying on implicit managed memory transfers, define separate host and device vectors and manage data movement yourself. 
This way, you’re always in control of when and how data travels between the CPU and GPU.

// image: takeaway_1_5

### And lastly, fancy iterators give you a powerful way to extend existing parallel algorithms to your unique use cases. 
By encapsulating custom logic, you can reuse Thrust’s highly optimized building blocks without having to rewrite entire algorithms from scratch.

// image: takeaway_1_5



# Asynchrony and CUDA Streams

The concept of parallelism is not sufficient for accelerating your applications. To fully utilize GPUs, this lab will teach you another fundamental concept: asynchrony. In this lab, you'll learn how and when to leverage asynchrony. You’ll use NVIDIA Nsight Systems to distinguish synchronous and asynchronous algorithms and identify performance bottlenecks.


## Asynchrony

In the previous sections, we learned about:
- Execution spaces (where code runs: CPU vs. GPU)
- Memory spaces (where data is stored: host vs. device)
- Parallel algorithms (how to run operations in parallel using Thrust)

By combining these concepts, we improved our simulator. Here’s what the updated simulator code looks like:

```c++
void simulate(int height, int width, 
              thrust::device_vector<float> &in, 
              thrust::device_vector<float> &out) 
{
  cuda::std::mdspan temp_in(thrust::raw_pointer_cast(in.data()), height, width);
  thrust::tabulate(
    thrust::device, out.begin(), out.end(), 
    [=] __host__ __device__(int id) { /* ... */ }
  );
}

for (int write_step = 0; write_step < 3; write_step++) 
{
  thrust::copy(d_prev.begin(), d_prev.end(), h_prev.begin());
  dli::store(write_step, height, width, h_prev);

  for (int compute_step = 0; compute_step < 3; compute_step++) {
    simulate(height, width, d_prev, d_next);
    d_prev.swap(d_next);
  }
}
```

In this loop we do the following:
 - Copy data from the device (GPU) to the host (CPU).
 - Write the host data to disk.
 - Compute the next state on the GPU.
 - This process can be visualized as follows:

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_2_02/sync.png" alt="Sync" width=800>


### Overlapping
We see that Thrust launches work on the GPU for each simulation step (thrust::tabulate). However, it then waits for the GPU to finish before returning control to the CPU. Because Thrust calls are synchronous, the CPU remains idle whenever the GPU is working. Writing efficient heterogeneous code means utilizing all available resources, including the CPU. In many real-world applications, we can keep the CPU busy at the same time the GPU is computing. This is called overlapping. Instead of waiting idly, the CPU could do something useful, like write data while the GPU is crunching numbers.

Here’s a simple way to visualize that concept:

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_2_02/overlap.png" alt="Compute/IO Overlap" width=800>

While the GPU is computing the next simulation step, the CPU can be writing out the previous results to disk.

This overlap uses both CPU and GPU resources efficiently, reducing the total runtime.
Unfortunately, Thrust’s interface doesn’t provide a direct way to separate launching GPU work from waiting for its completion.
Under the hood, Thrust calls another library called [CUB (CUDA UnBound)](https://nvidia.github.io/cccl/cub/) to implement its GPU algorithms.  If you look at the software stack, you'll see CUB us underneath Thrust.  CUB is also a library in it's own right.

### CUB

If we want finer control to use the CPU while GPU kernels are still running, we need more flexible tools. That’s where direct libraries like CUB come into play.

Let's take a closer look at CUB:


```c++
%%writefile Sources/cub-perf.cu
#include "dli.h"

float simulate(int width,
               int height,
               const thrust::device_vector<float> &in,
                     thrust::device_vector<float> &out,
               bool use_cub) 
{
  cuda::std::mdspan temp_in(thrust::raw_pointer_cast(in.data()), height, width);
  auto compute = [=] __host__ __device__(int id) {
    const int column = id % width;
    const int row    = id / width;

    // loop over all points in domain (except boundary)
    if (row > 0 && column > 0 && row < height - 1 && column < width - 1)
    {
      // evaluate derivatives
      float d2tdx2 = temp_in(row, column - 1) - 2 * temp_in(row, column) + temp_in(row, column + 1);
      float d2tdy2 = temp_in(row - 1, column) - 2 * temp_in(row, column) + temp_in(row + 1, column);

      // update temperatures
      return temp_in(row, column) + 0.2f * (d2tdx2 + d2tdy2);
    }
    else
    {
      return temp_in(row, column);
    }
  };

  auto begin = std::chrono::high_resolution_clock::now();

  if (use_cub) 
  {
    auto cell_ids = thrust::make_counting_iterator(0);
    cub::DeviceTransform::Transform(cell_ids, out.begin(), width * height, compute);
  }
  else 
  {
    thrust::tabulate(thrust::device, out.begin(), out.end(), compute);
  }
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration<float>(end - begin).count();
}

int main()
{
  std::cout << "size, thrust, cub\n";
  for (int size = 1024; size <= 16384; size *= 2)
  {
    int width = size;
    int height = size;
    thrust::device_vector<float> current_temp(height * width, 15.0f);
    thrust::device_vector<float> next_temp(height * width);

    std::cout << size << ", "
              << simulate(width, height, current_temp, next_temp, false) << ", "
              << simulate(width, height, current_temp, next_temp, true) << "\n";
  }
}
```

compile and run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Sources/cub-perf.cu # build executable
!/tmp/a.out # run executable
```

When you run the example cell, you might see some unexpected performance results:
 - When using Thrust, the runtime increases as the number of cells increases. This makes sense because the GPU is doing more work.
 - When using CUB, the runtime seems almost constant, regardless of how many cells you use.

Why does this happen?

Thrust is synchronous, meaning it waits for the GPU to finish all work before giving control back to the CPU. Naturally, as we scale the workload, the GPU takes longer, so you see longer total run times.
CUB, on the other hand, is asynchronous. It launches the GPU kernels and then immediately returns control to the CPU. That means your CPU timer stops quickly, and it looks like the GPU work is instantaneous, even though the GPU may still be processing in the background.
In other words, CUB’s asynchronous behavior explains why the measured runtime doesn’t grow as expected with the problem size. The GPU is still doing the work, but the CPU measurements aren’t accounting for its actual duration.

This answers the question of how Thrust launches work on the GPU, but what causes Thrust to wait? Thrust uses a function from the CUDA Runtime, cudaDeviceSynchronize(), to wait for the GPU to finish. If we insert this function when using CUB, we should see the same behavior:

```c++
%%writefile Sources/cub-perf-sync.cu
#include "dli.h"

float simulate(int width,
               int height,
               const thrust::device_vector<float> &in,
                     thrust::device_vector<float> &out,
               bool use_cub) 
{
  cuda::std::mdspan temp_in(thrust::raw_pointer_cast(in.data()), height, width);
  auto compute = [=] __host__ __device__(int id) {
    const int column = id % width;
    const int row    = id / width;

    // loop over all points in domain (except boundary)
    if (row > 0 && column > 0 && row < height - 1 && column < width - 1)
    {
      // evaluate derivatives
      float d2tdx2 = temp_in(row, column - 1) - 2 * temp_in(row, column) + temp_in(row, column + 1);
      float d2tdy2 = temp_in(row - 1, column) - 2 * temp_in(row, column) + temp_in(row + 1, column);

      // update temperatures
      return temp_in(row, column) + 0.2f * (d2tdx2 + d2tdy2);
    }
    else
    {
      return temp_in(row, column);
    }
  };

  auto begin = std::chrono::high_resolution_clock::now();

  if (use_cub) 
  {
    auto cell_ids = thrust::make_counting_iterator(0);
    cub::DeviceTransform::Transform(cell_ids, out.begin(), width * height, compute);
    cudaDeviceSynchronize();
  }
  else 
  {
    thrust::tabulate(thrust::device, out.begin(), out.end(), compute);
  }
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration<float>(end - begin).count();
}

int main()
{
  std::cout << "size, thrust, cub\n";
  for (int size = 1024; size <= 16384; size *= 2)
  {
    int width = size;
    int height = size;
    thrust::device_vector<float> current_temp(height * width, 15.0f);
    thrust::device_vector<float> next_temp(height * width);

    std::cout << size << ", "
              << simulate(width, height, current_temp, next_temp, false) << ", "
              << simulate(width, height, current_temp, next_temp, true) << "\n";
  }
}
```
compile and run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Sources/cub-perf-sync.cu # build executable
!/tmp/a.out # run executable
```
The code above is similar to the previous example, but with the addition of `cudaDeviceSynchronize()` after the calls to CUB.
`cudaDeviceSynchronize()` is a CUDA Runtime function that causes the CPU to wait until the GPU has finished all work.
With `cudaDeviceSynchronize()`, you can see that it takes the same time for both Thrust and CUB to complete the work.

We can now use CUB and `cudaDeviceSynchronize()` to control overlap computation and I/O.
This change should result in a significant speedup, as the CPU can now write data to disk while the GPU is computing the next simulation step:

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_2_02/sync-cub-vs-thrust.png" alt="Expected Speedup" width=800>


### Exercise: Compute-IO Overlap

Usage of `cub::DeviceTransform` for your reference:

```c++
cub::DeviceTransform::Transform(input_iterator, output_iterator, num_items, op);
```

In the code below, replace `thrust::tabulate` with `cub::DeviceTransform` and use `cudaDeviceSynchronize` appropriately:

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_2_02/overlap.png" alt="Compute/IO Overlap" width=800>


<details>
    <summary>Original code in case you need to refer to it</summary>

```c++
%%writefile Sources/compute-io-overlap.cu
#include "dli.h"

void simulate(int width,
              int height,
              const thrust::device_vector<float> &in,
                    thrust::device_vector<float> &out)
{
  cuda::std::mdspan temp_in(thrust::raw_pointer_cast(in.data()), height, width);
  thrust::tabulate(out.begin(), out.end(), [=] __device__(int id) {
    return dli::compute(id, temp_in);
  });
}

int main()
{
  int height = 2048;
  int width  = 8192;

  thrust::device_vector<float> d_prev = dli::init(height, width);
  thrust::device_vector<float> d_next(height * width);
  thrust::host_vector<float> h_prev(height * width);

  const int compute_steps = 500;
  const int write_steps = 3;
  for (int write_step = 0; write_step < write_steps; write_step++)
  {
    auto step_begin = std::chrono::high_resolution_clock::now();
    thrust::copy(d_prev.begin(), d_prev.end(), h_prev.begin());

    for (int compute_step = 0; compute_step < compute_steps; compute_step++)
    {
      simulate(width, height, d_prev, d_next);
      d_prev.swap(d_next);
    }

    auto write_begin = std::chrono::high_resolution_clock::now();
    dli::store(write_step, height, width, h_prev);
    auto write_end = std::chrono::high_resolution_clock::now();
    auto write_seconds = std::chrono::duration<double>(write_end - write_begin).count();

    auto step_end = std::chrono::high_resolution_clock::now();
    auto step_seconds = std::chrono::duration<double>(step_end - step_begin).count();
    std::printf("compute + write %d in %g s\n", write_step, step_seconds);
    std::printf("          write %d in %g s\n", write_step, write_seconds);
  }
}
```
    
</details>

```c++
%%writefile Sources/compute-io-overlap.cu
#include "dli.h"

void simulate(int width,
              int height,
              const thrust::device_vector<float> &in,
                    thrust::device_vector<float> &out)
{
  cuda::std::mdspan temp_in(thrust::raw_pointer_cast(in.data()), height, width);
  thrust::tabulate(out.begin(), out.end(), [=] __device__(int id) {
    return dli::compute(id, temp_in);
  });
}

int main()
{
  int height = 2048;
  int width  = 8192;

  thrust::device_vector<float> d_prev = dli::init(height, width);
  thrust::device_vector<float> d_next(height * width);
  thrust::host_vector<float> h_prev(height * width);

  const int compute_steps = 500;
  const int write_steps = 3;
  for (int write_step = 0; write_step < write_steps; write_step++)
  {
    auto step_begin = std::chrono::high_resolution_clock::now();
    thrust::copy(d_prev.begin(), d_prev.end(), h_prev.begin());

    for (int compute_step = 0; compute_step < compute_steps; compute_step++)
    {
      simulate(width, height, d_prev, d_next);
      d_prev.swap(d_next);
    }

    auto write_begin = std::chrono::high_resolution_clock::now();
    dli::store(write_step, height, width, h_prev);
    auto write_end = std::chrono::high_resolution_clock::now();
    auto write_seconds = std::chrono::duration<double>(write_end - write_begin).count();

    auto step_end = std::chrono::high_resolution_clock::now();
    auto step_seconds = std::chrono::duration<double>(step_end - step_begin).count();
    std::printf("compute + write %d in %g s\n", write_step, step_seconds);
    std::printf("          write %d in %g s\n", write_step, write_seconds);
  }
}
```
compile and run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Sources/compute-io-overlap.cu # build executable
!/tmp/a.out # run executable
```

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

<details>
  <summary>Hints</summary>
  
  - `cub::DeviceTransform::Transform` accepts the following parameters (in order):
    - input iterator  (Think about what we learned earlier using counting iterators)
    - output iterator
    - number of elements
    - unary function
  - You should synchronize the device in a place that allows in-flight transformations to overlap writing data to the file system.  It should be somewhere in the `main` function.
</details>

Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.

<details>
  <summary>Solution</summary>

  Key points:

  - Synchronizing the device after the write step allows us to overlap computation with I/O

  Solution:
  ```c++
  void simulate(int width, int height, const thrust::device_vector<float> &in,
                thrust::device_vector<float> &out) {
    cuda::std::mdspan temp_in(thrust::raw_pointer_cast(in.data()), height, width);
    cub::DeviceTransform::Transform(
        thrust::make_counting_iterator(0), out.begin(), width * height,
        [=] __host__ __device__(int id) { return dli::compute(id, temp_in); });
  }

  // ... 

  for (int write_step = 0; write_step < write_steps; write_step++) {
    thrust::copy(d_prev.begin(), d_prev.end(), h_prev.begin());

    for (int compute_step = 0; compute_step < compute_steps; compute_step++) {
      simulate(width, height, d_prev, d_next);
      d_prev.swap(d_next);
    }

    dli::store(write_step, height, width, h_prev);
    cudaDeviceSynchronize();
  }
  ```
</details>
 
### Exercise: Profile Your Code with Nsight Systems

In this exercise, you will learn how to profile your code with Nsight Systems. 
Nsight Systems is a system-wide performance analysis tool, designed to visualize CPU and GPU activities. The short video 

<div style="background-color: #e7f3fe; border-left: 6px solid #2196F3; padding: 10px; margin: 10px 0;">
  <strong>NOTE:</strong> There are some systems that are unable to display the Nsight Streamer due to firewalls or bandwidth limitations and its use of the WebRTC protocol. If this is your situation, you can still review the solution and images provided to see the profiling results.  To improve your bandwidth, you might try closing other applications and browser tabs on your computer or on your network.
</div>

To run Nsight Systems, you can use the command-line interface provided by `nsys`:
run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Solutions/compute-io-overlap.cu # build executable
!nsys profile --force-overwrite true -o ../nsight-reports/compute-io-overlap /tmp/a.out # run and profile executable
```
The code above stores the output in a file called `compute-io-overlap` in the `nsight-reports` directory.

### Exercise: Use NVTX

In this exercise, you will learn how to ease the analysis of your application by using NVTX to annotate your code.

```c++
%%writefile Sources/nvtx.cu
#include "dli.h"

void simulate(int width, int height, const thrust::device_vector<float> &in,
              thrust::device_vector<float> &out) 
{
  cuda::std::mdspan temp_in(thrust::raw_pointer_cast(in.data()), height, width);
  cub::DeviceTransform::Transform(
      thrust::make_counting_iterator(0), out.begin(), width * height,
      [=] __host__ __device__(int id) { return dli::compute(id, temp_in); });
}

int main() 
{
  int height = 2048;
  int width = 8192;

  thrust::device_vector<float> d_prev = dli::init(height, width);
  thrust::device_vector<float> d_next(height * width);
  thrust::host_vector<float> h_prev(height * width);

  const int compute_steps = 750;
  const int write_steps = 3;
  for (int write_step = 0; write_step < write_steps; write_step++) 
  {
    nvtx3::scoped_range r{std::string("write step ") + std::to_string(write_step)};

    {
        // 1. Annotate the "copy" step using nvtx range
        thrust::copy(d_prev.begin(), d_prev.end(), h_prev.begin());
    }

    {
        // 2. Annotate the "compute" step using nvtx range
        for (int compute_step = 0; compute_step < compute_steps; compute_step++) 
        {
        simulate(width, height, d_prev, d_next);
        d_prev.swap(d_next);
        }
    }

    {
        // 3. Annotate the "write" step using nvtx range
        dli::store(write_step, height, width, h_prev);
    }

    {
      // 4. Annotate the "wait" step using nvtx range
      cudaDeviceSynchronize();
    }
  }
}
```
compile and run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Sources/nvtx.cu # build executable
!nsys profile --force-overwrite true -o ../nsight-reports/nvtx /tmp/a.out # run and profile executable
```

The code above stores the output in a file called `nvtx` in `nsight-reports` directory.

If you just completed the Nsight exercise, your UI interface should still be open.  If not, review the steps provided in the [Nsight exercise](02.02.03-Exercise-Nsight.ipynb).

Open the new `nvtx` report and navigate to see the timeline of your application.
Identify:
- when GPU compute is launched
- when CPU writes data on disk
- when CPU waits for GPU
- when data is transferred between CPU and GPU

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

<details>
  <summary>Hints</summary>
  
  - `nvtx3::scoped_range r{"name"}` creates a range called `name`
  - you can find NVTX ranges in the "NVTX" timeline row of Nsight Systems
</details>

Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.

<details>
  <summary>Solution</summary>

  You can annotate scopes as follows:
  ```c++
  {
    nvtx3::scoped_range r{"copy"};
    thrust::copy(d_prev.begin(), d_prev.end(), h_prev.begin());
  }

  {
    nvtx3::scoped_range r{"compute"};
    for (int compute_step = 0; compute_step < compute_steps; compute_step++) {
      simulate(width, height, d_prev, d_next);
      d_prev.swap(d_next);
    }
  }

  {
    nvtx3::scoped_range r{"write"};
    dli::store(write_step, height, width, h_prev);
  }

  {
    nvtx3::scoped_range r{"wait"};
    cudaDeviceSynchronize();
  }
  ```
</details>

## Streams

So far, you’ve learned how to use asynchronous APIs to overlap computation (on the GPU) and I/O (on the CPU). 
Here’s what our simulator code looks like when we overlap compute and I/O:

```c++
void simulate(int width, int height, const thrust::device_vector<float> &in,
              thrust::device_vector<float> &out)
{
  cuda::std::mdspan temp_in(thrust::raw_pointer_cast(in.data()), height, width);
  cub::DeviceTransform::Transform(
    thrust::make_counting_iterator(0), out.begin(), width * height,
    [=] __host__ __device__(int id) { return dli::compute(id, temp_in); });
}

int main() 
{
  int height = 2048;
  int width = 8192;

  thrust::device_vector<float> d_prev = dli::init(height, width);
  thrust::device_vector<float> d_next(height * width);
  thrust::host_vector<float> h_prev(height * width);

  for (int write_step = 0; write_step < 3; write_step++) 
  {
    thrust::copy(d_prev.begin(), d_prev.end(), h_prev.begin());

    for (int compute_step = 0; compute_step < 750; compute_step++) 
    {
      simulate(width, height, d_prev, d_next);
      d_prev.swap(d_next);
    }

    dli::store(write_step, height, width, h_prev);

    cudaDeviceSynchronize(); 
  }
}
```

This code is already fast, but there are still further optimizations we can make. <br>
Right now, the simulator:
1. Synchronously copies data from GPU to CPU memory.
2. Overlaps computation and I/O to some extent.
3. Waits for the copy to finish before proceeding with the computation.

To improve performance even more, we can also overlap the data copy with the GPU computation, just as we did with the disk I/O.



### Copying Memory Asynchronously

To achieve this, we need an asynchronous version of `thrust::copy`. 
Because Thrust itself doesn’t have direct “magical” powers to copy between the CPU and GPU, it relies on the CUDA Runtime API.
The CUDA Runtime API provides asynchronous memory copy functions such as `cudaMemcpyAsync`, which has the following interface:

```c++
cudaError_t cudaMemcpyAsync(
  void*           dst,  // destination pointer
  const void*     src,  // source pointer
  size_t        count,  // number of bytes to copy
  cudaMemcpyKind kind   // direction of copy
);
```

Unlike Thrust, `cudaMemcpyAsync` works on raw pointers and operates in terms of bytes rather than elements.
This means that we need to calculate the size of the data we want to copy in bytes.
Besides that, `cudaMemcpyAsync` also requires an explicit copy direction, which can be one of the following:

- `cudaMemcpyHostToDevice`: instructs `cudaMemcpyAsync` to copy data from CPU to GPU
- `cudaMemcpyDeviceToHost`: instructs `cudaMemcpyAsync` to copy data from GPU to CPU
- `cudaMemcpyDeviceToDevice`: instructs `cudaMemcpyAsync` to copy data from GPU to GPU

You might have also noticed that `cudaMemcpyAsync` returns a `cudaError_t`.
What kind of error can it be?
Well, it can actually be any error from previous asynchronous operations.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_2_03/async-errors.png" alt="Async Errors" width=600>

In the diagram above, we have two asynchronous operations: `A` and `B` followed by a `cudaMemcpyAsync`.
Since both `A` and `B` are computed asynchronously, `A` can start executing after `B` was launched.
This means that if `A` fails, the error can be caught by `cudaMemcpyAsync`.

Unfortunately, if we just use `cudaMemcpyAsync` in our code, we won't get any performance improvement.
To figure out why, let's take a look at the following diagram:

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_2_03/async-copy-same-stream.png" alt="Same Stream" width=900>


The problem is that all asynchronous operations are ordered on the GPU.
Just as when we launched multiple asynchronous CUB calls, we expected the next invocation to start after the previous one finished, but the same thing happened with `cudaMemcpyAsync`.
Subsequent CUB computations wait for `cudaMemcpyAsync` to finish, even though the copy operation is asynchronous.

## CUDA Stream

This is an appropriate time to introduce a new concept called a _CUDA stream_.  You can think of a CUDA stream as an in-order work queue of things (commands, functions, etc.) that will be executed on the GPU.  In all the code we've been writing, we've been executing our GPU work in a stream - we just didn't know it.  If the programmer doesn't specify a stream (which we haven't up to this point), then the work is issued to something called the _default CUDA stream_.  

Very importantly, the work issued to a specific CUDA stream is executed synchronously and in-order with respect to that stream.  This makes sense intuitively as a typical GPU programming flow is to do something like the following:

1. Copy data from host to device
2. Compute on the device
3. Copy data from device to host

For example, one would not want the compute in step 2 to begin before all the data from step 1 is copied to the device.  So again, work in the _same_ stream is executed synchronously with respect to that stream.  However, work in _different_ streams is not synchronized. This is how we can achieve proper concurrency among all the parts of the application that can be executed asynchronously.  In our example, specifically, we can use different streams to allow computation and data transfer to be executed concurrently.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_2_03/async-copy.png" alt="Different Streams" width=900>

On the language level, a CUDA stream is represented by a specific type:

```c++
cudaStream_t copy_stream, compute_stream;
```

To construct a stream, we use the following function:

```c++
cudaStreamCreate(&compute_stream);
cudaStreamCreate(&copy_stream);
```

We can also synchronize the CPU with a given stream, instead of synchronizing with the entire GPU using `cudaDeviceSynchronize`:

```c++
cudaStreamSynchronize(compute_stream);
cudaStreamSynchronize(copy_stream);
```

This is a recommended way to synchronize CPU with GPU, as it allows for more fine-grained control over the synchronization.

Finally, you can destroy a stream using the following function:

```c++
cudaStreamDestroy(compute_stream);
cudaStreamDestroy(copy_stream);
```

`cudaMemcpyAsync` actually has an additional parameter that allows you to specify a stream in which the copy operation should be executed:

```c++
cudaError_t 
cudaMemcpyAsync(
  void*           dst, 
  const void*     src, 
  size_t        count, 
  cudaMemcpyKind kind,
  cudaStream_t stream = 0 // <- 
);

CUB also allows you to specify which stream to use.

```c++
cudaError_t 
cub::DeviceTransform::Transform(
  IteratorIn 	  input, 
  IteratorOut  output,
  int       num_items,
  TransformOp 	   	op, 
  cudaStream_t stream = 0 // <-
);
```

It's very common for accelerated libraries to provide an optional stream parameter.
The idea is that you as a user of these libraries will likely want to overlap their operations with data transfers, CPU computations, or even other library calls.

Returning to our simulator, if we just use `cudaMemcpyAsync` and `cub::DeviceTransform::Transform` with different streams, we'll end up with a data race.
If you take a look at each iteration, you'll notice how the second iteration step overwrites `d_prev` while it's being copied to the CPU.

```c++
cudaMemcpyAsync(
  thrust::raw_pointer_cast(h_prev.data()),
  thrust::raw_pointer_cast(d_prev.data()), // reads d_prev
  height * width * sizeof(float),
  cudaMemcpyDeviceToHost,
  copy_stream);

simulate(width, height, d_prev, d_next, compute_stream); // reads d_prev, writes d_next
simulate(width, height, d_next, d_prev, compute_stream); // reads d_next, writes d_prev
```

We can fix this with another level of indirection.
We can allocate a staging buffer on the GPU, copy the data from `d_prev` to the staging buffer synchronously, and then copy the data from the staging buffer to the CPU.

```c++
thrust::copy(d_prev.begin(), d_prev.end(), d_buffer.begin()); // reads d_prev synchronously

cudaMemcpyAsync(
  thrust::raw_pointer_cast(h_prev.data()),
  thrust::raw_pointer_cast(d_buffer.data()), // reads d_buffer asynchronously
  height * width * sizeof(float),
  cudaMemcpyDeviceToHost,
  copy_stream);

simulate(width, height, d_prev, d_next, compute_stream); // reads d_prev, writes d_next
simulate(width, height, d_next, d_prev, compute_stream); // reads d_next, writes d_prev
```

But doesn't this defeat the purpose of overlapping computation and IO?
We just made the copy synchronous again!
To answer this question, let's return to our high-level overview of bandwidth provided by different subsystems:

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_2_03/cpu-vs-gpu-memory-pci.png" alt="PCIe" width=900>

Here you can see how the bandwidth of CPU-GPU interconnect is much lower than the bandwidth of GPU memory.
This means that copying data from GPU to GPU should be significantly faster than copying data from GPU to CPU.
So this change can still lead to a performance improvement, at the small expense of having a small temporary buffer in memory.

### Exercise: Async Copy and Streams

Usage of streams:

```c++
cudaStream_t stream;

// create a stream
cudaStreamCreate(&stream); 

// make CPU wait for all operations in the stream to complete
cudaStreamSynchronize(stream); 

// destroy the stream
cudaStreamDestroy(stream);
```

Usage of `cub::DeviceTransform`:

```c++
cub::DeviceTransform::Transform(input_iterator, output_iterator, num_items, op, stream);
```

Usage of `cudaMemcpyAsync`:

```c++
cudaMemcpyAsync(dst, src, num_bytes, cudaMemcpyDeviceToHost, stream);
```

For this exercise, we'll attempt to make transfers between the host and device asynchronous.
To do this, you are expected to:

- replace `thrust::copy` with `cudaMemcpyAsync`
- put compute and copy operations in separate CUDA streams
- synchronize the streams to follow the pattern from the diagram below

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_2_03/async-copy.png" alt="Compute/Copy Overlap" width=900>


## Pinned memory

Let’s take another look at our current simulator state:

```c++
cudaStream_t compute_stream;
cudaStreamCreate(&compute_stream);

cudaStream_t copy_stream;
cudaStreamCreate(&copy_stream);

for (int write_step = 0; write_step < write_steps; write_step++) 
{
  thrust::copy(d_prev.begin(), d_prev.end(), d_buffer.begin());
  cudaMemcpyAsync(thrust::raw_pointer_cast(h_prev.data()),
                  thrust::raw_pointer_cast(d_buffer.data()),
                  height * width * sizeof(float), cudaMemcpyDeviceToHost,
                  copy_stream);

  for (int compute_step = 0; compute_step < compute_steps; compute_step++) 
  {
    simulate(width, height, d_prev, d_next, compute_stream);
    d_prev.swap(d_next);
  }

  cudaStreamSynchronize(copy_stream);
  dli::store(write_step, height, width, h_prev);

  cudaStreamSynchronize(compute_stream);
}

cudaStreamDestroy(compute_stream);
cudaStreamDestroy(copy_stream);
```

We use two CUDA streams to overlap the expensive device-to-host copy (`copy_stream`) with ongoing computations (`compute_stream`). 
However, if you profile this code (for instance, using Nsight Systems), you will see that the copy and compute still run sequentially. 
This indicates we’re missing a key concept about how the hardware works. 
To understand why, we need to step back and look at how memory operates.

### Swap Memory

Operating systems do not provide direct access to physical memory. Instead, programs use virtual memory, which is mapped to physical memory. Virtual memory is organized into pages, enabling the operating system to manage them flexibly, such as swapping pages to disk when physical memory runs low.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_2_04/swap.png" alt="Swap" width=800>

So any given page can be in physical memory, on disk, or in some other place, and the operating system keeps track of that.
When the page can be relocated to disk, it's called *pageable*. 
But memory can also be page-locked, or "pinned" to physical memory.


### GPU Access

What does this have to do with CUDA?
GPU can only copy data from physical memory. 
This means that when copying data between host and device, memory has to be pinned.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_2_04/pinned-staging.png" alt="GPU Access" width=500>

But this cannot be right. 
We just copied data between 
host and device without doing anything special like pinning memory.
How did that work?
Under the covers, when moving memory from host to device the CUDA Runtime utilizes a staging buffer in pinned memory.
When you copy data from host to device, the CUDA Runtime first copies data to the staging buffer, and then copies it to device.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_2_04/read-from-pageable.png" alt="Read from Pageable" width=500>

This should explain why our copy wasn't overlapped with compute.
It was actually synchronous, because under the covers the data was copied to a staging buffer. 
Unbeknownst to us at the time, the code first copied a chunk of data into pinned staging buffer, waited till the copy is done, and then proceeded to copy the next chunk of data that fit into the staging buffer.

The good news is that we can pin memory ourselves via an explicit function call.
In this case, there'll be no need to stream data through staging buffer, enabling asynchrony.

To allocate pinned memory, it's sufficient to use another container from Thrust:

```c++
thrust::universal_host_pinned_vector<float> pinned_memory(size);
```

### Exercise: Async Copy and Pinned Memory

For this exercise, we'll attempt to fix our program to make the copy actually asynchronous.
To do this, you are expected to:

- Use `thrust::universal_host_pinned_vector` to allocate pinned memory for the host buffer
- Profile the program to see if the copy becomes asynchronous

<details>
<summary>Copy of the original code if you need to refer to it.</summary>

```c++
%%writefile Sources/copy-overlap.cu
#include "dli.h"

int main() 
{
  int height = 2048;
  int width = 8192;

  cudaStream_t compute_stream;
  cudaStreamCreate(&compute_stream);

  cudaStream_t copy_stream;
  cudaStreamCreate(&copy_stream);

  thrust::device_vector<float> d_prev = dli::init(height, width);
  thrust::device_vector<float> d_next(height * width);
  thrust::device_vector<float> d_buffer(height * width);

  // 1. Change code below to allocate host vector in pinned memory
  thrust::host_vector<float> h_prev(height * width);

  const int compute_steps = 750;
  const int write_steps = 3;
  for (int write_step = 0; write_step < write_steps; write_step++) 
  {
    cudaMemcpy(thrust::raw_pointer_cast(d_buffer.data()),
               thrust::raw_pointer_cast(d_prev.data()),
               height * width * sizeof(float), cudaMemcpyDeviceToDevice);
    cudaMemcpyAsync(thrust::raw_pointer_cast(h_prev.data()),
                    thrust::raw_pointer_cast(d_buffer.data()),
                    height * width * sizeof(float), cudaMemcpyDeviceToHost,
                    copy_stream);

    for (int compute_step = 0; compute_step < compute_steps; compute_step++) 
    {
      dli::simulate(width, height, d_prev, d_next, compute_stream);
      d_prev.swap(d_next);
    }

    cudaStreamSynchronize(copy_stream);
    dli::store(write_step, height, width, h_prev);

    cudaStreamSynchronize(compute_stream);
  }

  cudaStreamDestroy(compute_stream);
  cudaStreamDestroy(copy_stream);
}
```
    
</details>

```c++
%%writefile Sources/copy-overlap.cu
#include "dli.h"

int main() 
{
  int height = 2048;
  int width = 8192;

  cudaStream_t compute_stream;
  cudaStreamCreate(&compute_stream);

  cudaStream_t copy_stream;
  cudaStreamCreate(&copy_stream);

  thrust::device_vector<float> d_prev = dli::init(height, width);
  thrust::device_vector<float> d_next(height * width);
  thrust::device_vector<float> d_buffer(height * width);

  // 1. Change code below to allocate host vector in pinned memory
  thrust::host_vector<float> h_prev(height * width);

  const int compute_steps = 750;
  const int write_steps = 3;
  for (int write_step = 0; write_step < write_steps; write_step++) 
  {
    cudaMemcpy(thrust::raw_pointer_cast(d_buffer.data()),
               thrust::raw_pointer_cast(d_prev.data()),
               height * width * sizeof(float), cudaMemcpyDeviceToDevice);
    cudaMemcpyAsync(thrust::raw_pointer_cast(h_prev.data()),
                    thrust::raw_pointer_cast(d_buffer.data()),
                    height * width * sizeof(float), cudaMemcpyDeviceToHost,
                    copy_stream);

    for (int compute_step = 0; compute_step < compute_steps; compute_step++) 
    {
      dli::simulate(width, height, d_prev, d_next, compute_stream);
      d_prev.swap(d_next);
    }

    cudaStreamSynchronize(copy_stream);
    dli::store(write_step, height, width, h_prev);

    cudaStreamSynchronize(compute_stream);
  }

  cudaStreamDestroy(compute_stream);
  cudaStreamDestroy(copy_stream);
}
```
compile and run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Sources/copy-overlap.cu # build executable
!nsys profile --force-overwrite true -o ../nsight-reports/pinned /tmp/a.out # run and profile executable
``` 

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

Hints
You can allocate pinned memory with thrust::universal_host_pinned_vector

Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.

<details>
  <summary>Solution</summary>

  Key points:

  - Use `thrust::universal_host_pinned_vector` to allocate pinned memory for the host buffer

  Solution:
  ```c++
  thrust::universal_host_pinned_vector<float> h_prev(height * width);

  const int compute_steps = 750;
  const int write_steps = 3;
  for (int write_step = 0; write_step < write_steps; write_step++) {
    cudaMemcpy(thrust::raw_pointer_cast(d_buffer.data()),
               thrust::raw_pointer_cast(d_prev.data()),
               height * width * sizeof(float), cudaMemcpyDeviceToDevice);
    cudaMemcpyAsync(thrust::raw_pointer_cast(h_prev.data()),
                    thrust::raw_pointer_cast(d_buffer.data()),
                    height * width * sizeof(float), cudaMemcpyDeviceToHost,
                    copy_stream);
    // ...
  }
  ```
</details>

# Implementing New Algorithms with CUDA Kernels

Previous labs equipped you with a necessary understanding of how using standard parallel algorithms can provide both convenient and speed-of-light GPU acceleration. 
However, sometimes your unique use cases are not covered by accelerated libraries. 
In this lab, you’ll learn the CUDA SIMT (Single Instruction Multiple Threads) programming model to program the GPU directly using CUDA kernels. 
In addition, this lab will cover utilities provided by the CUDA ecosystem to facilitate development of custom CUDA kernels.


![CUDA_Kernels](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_02/implementing_new_algo_with_CUDA_kernels.png)


## CUDA kernels

In the previous section, we learned how to use asynchrony to improve the performance of a heterogeneous program by overlapping computation with I/O. 
We switched from a synchronous Thrust algorithm to the asynchronous CUB interface, which allowed the computational part of our program to look like this:


```c++
%%writefile Sources/cub.cu
#include "dli.h"

void simulate(dli::temperature_grid_f temp_in, float *temp_out, cudaStream_t stream)
{
  auto cell_ids = thrust::make_counting_iterator(0);
  cub::DeviceTransform::Transform(
    cell_ids, temp_out, temp_in.size(), 
    [temp_in] __host__ __device__ (int cell_id) { 
      return dli::compute(cell_id, temp_in); 
    }, stream);
}
```
compile and run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Sources/cub.cu # build executable
!/tmp/a.out # run executable
```

### Launching a CUDA Kernel with `__global__`

However, sometimes the algorithm you need is not available in existing accelerated libraries. 
What can you do when you cannot simply extend these existing algorithms (as we did in the first section) to fit your unique use case? At this point, it helps to understand the “magic” behind these accelerated libraries—specifically, how to launch a function on the GPU from the CPU.

So far, we have only used the `__host__` and `__device__` function specifiers, where host functions run on the CPU and device functions run on the GPU. 
To launch a function on the GPU from the CPU, we need a different specifier. 
That is where `__global__` comes in.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_02/global.png" alt="Global" width=800>

A function annotated with `__global__` is called a *CUDA kernel*. 
It is launched from the CPU but runs on the GPU. 
To launch a kernel, we use the specialized “triple chevrons” syntax:

```c++
kernel<<<1, 1, 0, stream>>>(...);
```
The first two numbers in the triple chevrons will be explained in more detail soon, but for now, note that CUDA kernels are asynchronous. 
In fact, CUB achieves its asynchrony by launching multiple CUDA kernels.  Because kernels themselves are asynchronous, CUB can provide asynchronous functionality.

Let’s try to reimplement the functionality of `cub::DeviceTransform` directly as a CUDA kernel.  We'll start with the code below which runs the algorithm with a single thread.


```c++
%%writefile Sources/simple-kernel.cu
#include "dli.h"

__global__ void single_thread_kernel(dli::temperature_grid_f in, float *out)
{
  for (int id = 0; id < in.size(); id++) 
  {
    out[id] = dli::compute(id, in);
  }
}

void simulate(dli::temperature_grid_f temp_in, float *temp_out, cudaStream_t stream)
{
  single_thread_kernel<<<1, 1, 0, stream>>>(temp_in, temp_out);
}
```
compile and run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Sources/simple-kernel.cu # build executable
!/tmp/a.out # run executable
```

### Parallelizing

Notice that we specify the CUDA Stream (`stream`) in the triple chevrons `<<<1, 1, 0, stream>>>`. 
However, as you might guess, this kernel is significantly slower than the CUB version because it processes the loop in a serial fashion. 
As we've learned already, the GPU does not automatically parallelize serial code.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_02/serial-kernel.png" alt="Serial" width=600>

We want to avoid serialization whenever possible. 
To parallelize this kernel, we need to launch more threads. 
The second parameter in the triple chevrons `kernel<<<1, NUMBER-OF-THREADS, 0, stream>>>` represents the number of threads. 
By increasing this number, we can launch more threads on the GPU. 
Of course, we also need to ensure that each thread processes a different subset of the data.

CUDA provides the built-in variable `threadIdx.x`, the value of which is used inside a kernel and stores the index of the current thread within a thread block, starting from `0`. 
If we launch more threads, we can use `threadIdx.x` to split the work across them:

```c++
const int number_of_threads = 2;

__global__ void block_kernel(dli::temperature_grid_f in, float *out)
{
  int thread_index = threadIdx.x;

  for (int id = thread_index; id < in.size(); id += number_of_threads) 
  {
    out[id] = dli::compute(id, in);
  }
}
```

In this example, two threads run with indices `threadIdx.x = 0` and `threadIdx.x = 1`. 
Each thread starts processing from its own index and increments by `number_of_threads` to avoid overlapping.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_02/threadIdx.png" alt="Thread Index" width=800>

This change will evenly distribute work between threads, which should result in a speedup.
Let's take a look if this is the case.  When you run the next two cells you should observe a speedup over the previous iteration of the code.


```c++
%%writefile Sources/block-kernel.cu
#include "dli.h"

const int number_of_threads = 2;

__global__ void block_kernel(dli::temperature_grid_f in, float *out)
{
  int thread_index = threadIdx.x;

  for (int id = thread_index; id < in.size(); id += number_of_threads) 
  {
    out[id] = dli::compute(id, in);
  }
}

void simulate(dli::temperature_grid_f temp_in, float *temp_out, cudaStream_t stream)
{
  block_kernel<<<1, number_of_threads, 0, stream>>>(temp_in, temp_out);
}
```
compile and run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Sources/block-kernel.cu # build executable
!/tmp/a.out # run executable
```


### Adding More Threads
While this provides some speedup, it may still be far from the performance of the CUB implementation. 
Increasing the number of threads further should help.  Run the next two cells and observe how performance changes when the number of threads is increased.


```c++
%%writefile Sources/block-256-kernel.cu
#include "dli.h"

const int number_of_threads = 256;

__global__ void block_kernel(dli::temperature_grid_f in, float *out)
{
  int thread_index = threadIdx.x;

  for (int id = thread_index; id < in.size(); id += number_of_threads) 
  {
    out[id] = dli::compute(id, in);
  }
}

void simulate(dli::temperature_grid_f temp_in, float *temp_out, cudaStream_t stream)
{
  block_kernel<<<1, number_of_threads, 0, stream>>>(temp_in, temp_out);
}
```
compile and run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Sources/block-256-kernel.cu # build executable
!/tmp/a.out # run executable
```

This works well, but if you try to go too high (for example, `number_of_threads = 2048`), you might see an error regarding invalid configuration.  Run the following two cells to observe this error.


```c++
%%writefile Sources/failed-block-kernel.cu
#include "dli.h"

const int number_of_threads = 2048;

__global__ void block_kernel(dli::temperature_grid_f in, float *out)
{
  int thread_index = threadIdx.x;

  for (int id = thread_index; id < in.size(); id += number_of_threads) 
  {
    out[id] = dli::compute(id, in);
  }
}

void simulate(dli::temperature_grid_f temp_in, float *temp_out, cudaStream_t stream)
{
  block_kernel<<<1, number_of_threads, 0, stream>>>(temp_in, temp_out);
}
```
compile and run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Sources/failed-block-kernel.cu # build executable
!/tmp/a.out # run executable
```

This error happens because there is a limit on the number of threads in a single block... 
So, what is a thread block?

Threads in a CUDA kernel are organized into a hierarchical structure.
This structure consists of equally-sized blocks of threads. 
All thread blocks together form a grid.

The second parameter of the triple chevron specifies the number of threads in a block, and this number can't exceed 1024.  (There's nothing magic about 1024, it's simply a limit enforced by NVIDIA based on HW resources.)
To launch more than 1024 threads, we need to launch more blocks.
The first parameter in the triple chevrons `kernel<<<NUMBER-OF-BLOCKS, NUMBER-OF-THREADS, 0, stream>>>` specifies the number of blocks. 

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_02/grid.png" alt="Grid" width=800>

The thread indexing we saw earlier is local to a block, so `threadIdx.x` will always be in the range `[0, NUMBER-OF-THREADS)`.  
To uniquely identify each thread across blocks, we need to combine both the block index and the thread index.
To do that, we can combine the `blockIdx.x` variable, which stores the index of the current block, with `blockDim.x`, which stores the number of threads in each block:

```c++
int thread_index = blockDim.x * blockIdx.x + threadIdx.x;
```

For more details on these built-in variables see the [CUDA Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/#thread-hierarchy).

Here are a few examples of how `thread_index` is calculted for a few selected threads in different thread blocks.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_02/thread-in-grid.png" alt="Thread in Grid" width=800>


Note that `blockDim.x` is a constant and is the same for every thread, while `blockIdx.x` and `threadIdx.x` vary depending on which thread and which block are running.

Besides that, we'll also have to update the stride calculation in the loop. 
To do this, we'll need to compute the total number of threads in the grid which we can do using another built-in variable called `gridDim.x`.
This variable stores the number of blocks in the grid, so the total number of threads in the grid can be computed as:

```c++
int number_of_threads = blockDim.x * gridDim.x;
```

Choosing how many threads go in each block is often independent of problem size. 
A common rule of thumb is to use a multiple of 32 (a warp size), with 256 being a reasonable starting choice. 
The number of blocks, by contrast, is usually derived from the problem size so that all elements can be covered.

If you attempt to do something like this:

```c++
int problem_size = 6;
int block_size = 4;
int grid_size = 6 / 4; // results in 1 block, but we need 2
```

you would not launch enough blocks because of the integer division. To fix this, you can use a helper function that performs a ceiling division:

```c++
int ceil_div(int a, int b) 
{
  return (a + b - 1) / b;
}
```

This ensures enough blocks are launched to cover every element in the data. Putting it all together, we can write:

```c++
%%writefile Sources/grid-kernel.cu
#include "dli.h"

__global__ void grid_kernel(dli::temperature_grid_f in, float *out)
{
  int thread_index = blockDim.x * blockIdx.x + threadIdx.x;
  int number_of_threads = blockDim.x * gridDim.x;

  for (int id = thread_index; id < in.size(); id += number_of_threads) 
  {
    out[id] = dli::compute(id, in);
  }
}

int ceil_div(int a, int b) 
{
  return (a + b - 1) / b;
}

void simulate(dli::temperature_grid_f temp_in, float *temp_out, cudaStream_t stream)
{
  int block_size = 1024;
  int grid_size = ceil_div(temp_in.size(), block_size);

  grid_kernel<<<grid_size, block_size, 0, stream>>>(temp_in, temp_out);
}
```
compile and run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Sources/grid-kernel.cu # build executable
!/tmp/a.out # run executable 
```

You should observe a significant speedup of this code compared to versions earlier in this notebook.  This makes sense intuitively as with each now kernel we are launching more threads.  We'd expect launching more threads to result in a faster execution time.

With this approach, our kernel more effectively utilizes the GPU. 
While it may still not be as fast as the CUB implementation,which uses additional optimizations beyond our current scope, understanding how to write and launch CUDA kernels directly is crucial for creating high-performance custom algorithms.

### Exercise: Symmetry

For your reference, the following is an example of launching a simple kernel.  Execute the next two cells to view the results.

```c++
%%writefile Sources/kernel-launch.cu
#include <cstdio>

__global__ void kernel(int value) {
  std::printf("value on device = %d\n", value);
}

int main() {
  int blocks_in_grid = 1;
  int threads_in_block = 1;
  cudaStream_t stream = 0;
  kernel<<<blocks_in_grid, threads_in_block, 0, stream>>>(42);
  cudaStreamSynchronize(stream);
}
```
compile and run with:
```bash
!nvcc -o /tmp/a.out Sources/kernel-launch.cu && /tmp/a.out
```

Change the code below the image to launch a kernel with a single thread that checks if the input array is symmetric.  If the code does NOT obtain the correct answer, an error message will be printed.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_02/symmetry.png" alt="Symmetry Check" width=600>

<details>
<summary>Original code if you need to refer back.</summary>

```c++
%%writefile Sources/symmetry-check.cu
#include "dli.cuh"

// 1. convert the function below from a CPU function into a CUDA kernel
void symmetry_check_kernel(dli::temperature_grid_f temp, int row)
{
  int column = 0;

  if (abs(temp(row, column) - temp(temp.extent(0) - 1 - row, column)) > 0.1)
  {
    printf("Error: asymmetry in %d / %d\n", column, temp.extent(1));
  }
}

void symmetry_check(dli::temperature_grid_f temp, cudaStream_t stream)
{
  int target_row = 0;
  // 2. use triple chevron to launch the kernel
  symmetry_check_kernel(temp, target_row);
}
```
    
</details>


```c++
%%writefile Sources/symmetry-check.cu
#include "dli.cuh"

// 1. convert the function below from a CPU function into a CUDA kernel
void symmetry_check_kernel(dli::temperature_grid_f temp, int row)
{
  int column = 0;

  if (abs(temp(row, column) - temp(temp.extent(0) - 1 - row, column)) > 0.1)
  {
    printf("Error: asymmetry in %d / %d\n", column, temp.extent(1));
  }
}

void symmetry_check(dli::temperature_grid_f temp, cudaStream_t stream)
{
  int target_row = 0;
  // 2. use triple chevron to launch the kernel
  symmetry_check_kernel(temp, target_row);
}
```
compile and run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Sources/symmetry-check.cu # build executable
!/tmp/a.out # run executable
```

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

<details>
  <summary>Hints</summary>
  
  - Kernels are functions that are executed on the GPU but launched from the CPU
  - Kernels are annotated with `__global__` and launched with triple chevrons `<<<1, 1, 0, stream>>>`
</details>

Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.

<details>
  <summary>Solution</summary>

  Key points:

  - Annotate the kernel with `__global__`
  - Launch the kernel with triple chevrons `<<<1, 1, 0, stream>>>`

  Solution:
  ```c++
  __global__ void symmetry_check_kernel(dli::temperature_grid_f temp, int row)
  {
    int column = 0;

    if (abs(temp(row, column) - temp(temp.extent(0) - 1 - row, column)) > 0.1)
    {
      printf("Error: asymmetry in %d / %d\n", column, temp.extent(1));
    }
  }

  void symmetry_check(dli::temperature_grid_f temp, cudaStream_t stream)
  {
    int target_row = 0;
    symmetry_check_kernel<<<1, 1, 0, stream>>>(temp, target_row);
  }
  ```

</details>







### Exercise: Row Symmetry

Threads are grouped into blocks, 
and each thread in a block has a unique ID `threadIdx.x` ranging from `0` to `blockDim.x - 1`. 
Blocks themselves are indexed by `blockIdx.x` within a grid, which ranges from `0` to `gridDim.x - 1`.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_02/grid.png" alt="Grid" width=900>

The global (grid-level) thread index is:

```c++
int thread_index = blockIdx.x * blockDim.x + threadIdx.x;
```

And the total number of threads in the entire grid is:

```c++
int num_threads = gridDim.x * blockDim.x;
```

Given a problem size `N` and thread block size, we can compute the number of blocks we need in a grid as:
For a problem of size `N`, if block size is `threads_per_block` threads, you can compute the number of blocks as:

```c++
int threads_per_block = 256;
int num_blocks = cuda::ceil_div(N, threads_per_block);
```

This ensures you launch enough threads to cover all N elements in the problem.
Using this information, modify the code below to launch a grid of threads, checking for symmetry of a given row:

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_02/row-symmetry.png" alt="Symmetry Check" width=600>

Assign each thread to a unique column index.  An error will be printed if your code does not obtain the correct answer.

<details>
<summary>Original code if you need to refer back</summary>

```c++
%%writefile Sources/row-symmetry-check.cu
#include "dli.cuh"

__global__ void symmetry_check_kernel(dli::temperature_grid_f temp, int row)
{
  // 1. change the line below so that each thread in a grid 
  //    checks exactly one column
  int column = 0;

  if (abs(temp(row, column) - temp(temp.extent(0) - 1 - row, column)) > 0.1)
  {
    printf("Error: asymmetry in %d / %d\n", column, temp.extent(1));
  }
}

void symmetry_check(dli::temperature_grid_f temp, cudaStream_t stream)
{
  int width      = temp.extent(1);
  // 2. launch sufficient number of threads to assign one thread per column

  int target_row = 0;
  symmetry_check_kernel<<<1, 1, 0, stream>>>(temp, target_row);
}
```
    
</details>


```c++
%%writefile Sources/row-symmetry-check.cu
#include "dli.cuh"

__global__ void symmetry_check_kernel(dli::temperature_grid_f temp, int row)
{
  // 1. change the line below so that each thread in a grid 
  //    checks exactly one column
  int column = 0;

  if (abs(temp(row, column) - temp(temp.extent(0) - 1 - row, column)) > 0.1)
  {
    printf("Error: asymmetry in %d / %d\n", column, temp.extent(1));
  }
}

void symmetry_check(dli::temperature_grid_f temp, cudaStream_t stream)
{
  int width      = temp.extent(1);
  // 2. launch sufficient number of threads to assign one thread per column

  int target_row = 0;
  symmetry_check_kernel<<<1, 1, 0, stream>>>(temp, target_row);
}
```
compile and run with:
```bash
!nvcc --extended-lambda -g -G -o /tmp/a.out Sources/row-symmetry-check.cu # build executable
!/tmp/a.out # run executable
```

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

<details>
  <summary>Hints</summary>
  
  - Modify the `int column = 0` line such that every thread checks a different column
  - Modify the triple chevron to launch a grid of threads
</details>


Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.

<details>
  <summary>Solution</summary>

  Key points:

  - Launch a grid of threads
  - Use thread index as column index

  Solution:
  ```c++
  __global__ void symmetry_check_kernel(dli::temperature_grid_f temp, int row)
  {
    int column = blockIdx.x * blockDim.x + threadIdx.x;

    if (abs(temp(row, column) - temp(temp.extent(0) - 1 - row, column)) > 0.1)
    {
      printf("Error: asymmetry in %d / %d\n", column, temp.extent(1));
    }
  }

  void symmetry_check(dli::temperature_grid_f temp, cudaStream_t stream)
  {
    int width      = temp.extent(1);
    int block_size = 1024;
    int grid_size  = cuda::ceil_div(width, block_size);

    int target_row = 0;
    symmetry_check_kernel<<<grid_size, block_size, 0, stream>>>(temp, target_row);
  }
  ```
</details>

### Dev Tools

Let's start with the simplest CUDA kernel.  Observe the error messages that occur when executing the following cell.  Notice that we are building the executable and then running it with `compute-sanitizer`.

```bash
!nvcc --extended-lambda -g -G -o /tmp/a.out Solutions/row-symmetry-check.cu # build executable
!/tmp/a.out # run executable
!compute-sanitizer /tmp/a.out # run sanitizer
```

There are a lot of error messages printed, and the instructive errors are at the very top.  Note one of the errors printed `Invalid __global__ read of size 4 bytes at symmetry_check_kernel`.  This tells you exactly where to look to find the memory access error.


```
Invalid __global__ read of size 4 bytes
=========     at symmetry_check_kernel(cuda::std::__4::mdspan<float, cuda::std::__4::extents<int, (unsigned long)18446744073709551615, (unsigned long)18446744073709551615>, cuda::std::__4::layout_right, cuda::std::__4::default_accessor<float>>, int)+0x2490 in /home/jbentz/dli/c-ac-01-v2/task1/task/03.02-Kernels/Solutions/row-symmetry-check.cu:6
=========     by thread (928,0,0) in block (4,0,0)
=========     Address 0x709388060 is out of bounds
=========     and is 97 bytes after the nearest allocation at 0x708000000 of size 20480000 bytes
```

The code below fixes the error.  Note the use of the `if (column < temp.extent(1))` statement, which guards the execution of the thread.  Each thread checks whether its `column` is less than the size of the array, `temp`.  If it is less, it executes the symmetry check, but if it is NOT, then it just returns.  This type of simple fix is very common in CUDA kernel programming to ensure that threads don't access out-of-bounds memory.

Execute the next two cells and verify that `compute-sanitizer` does not report any further errors.


```c++
%%writefile Sources/row-symmetry-check-fixed.cu
#include "dli.h"

__global__ void symmetry_check_kernel(dli::temperature_grid_f temp, int row)
{
  int column = blockIdx.x * blockDim.x + threadIdx.x;

  if (column < temp.extent(1))
  {
    if (abs(temp(row, column) - temp(temp.extent(0) - 1 - row, column)) > 0.1)
    {
        printf("Error: asymmetry in %d / %d\n", column, temp.extent(1));
    }
  }
}

void symmetry_check(dli::temperature_grid_f temp_in, cudaStream_t stream)
{
  int width      = temp_in.extent(1);
  int block_size = 1024;
  int grid_size  = cuda::ceil_div(width, block_size);

  int target_row = 0;
  symmetry_check_kernel<<<grid_size, block_size, 0, stream>>>(temp_in, target_row);
}

void simulate(dli::temperature_grid_f temp_in, float *temp_out, cudaStream_t stream)
{
  symmetry_check(temp_in, stream);
  dli::simulate(temp_in, temp_out, stream);
}
```
compile and run with:
```bash
!nvcc --extended-lambda -o /tmp/a.out Sources/row-symmetry-check-fixed.cu # build executable
!compute-sanitizer /tmp/a.out # run sanitizer
```

#@ Atomics

We recently fixed a bug caused by our thread hierarchy, which might prompt the question: why did we need that hierarchy in the first place? To illustrate its value, let’s look at a related problem: computing a histogram of our temperature grid.

## Histogram of Temperature Grid
A histogram helps visualize the distribution of temperatures by grouping values into "bins".
In this example, each bin covers a 10-degree range, so the first bin represents temperatures in `[0, 10)`, the second in `[10, 20)`, and so on.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_02/histogram.png" alt="Histogram" width=800>

Given a cell’s temperature, how do we determine the bin it belongs to? We can simply use integer division:

```c++
int bin = static_cast<int>(temperatures[cell] / bin_width);
```

So, a temperature of 14 falls into bin 1, while 4 maps to bin 0. 
Next, we’ll implement this logic in a CUDA kernel, assigning one thread per cell to calculate its bin.

```c++
%%writefile Sources/histogram-bug.cu
#include "dli.cuh"

constexpr float bin_width = 10;

__global__ void histogram_kernel(cuda::std::span<float> temperatures, 
                                 cuda::std::span<int> histogram)
{
  int cell = blockIdx.x * blockDim.x + threadIdx.x;
  int bin = static_cast<int>(temperatures[cell] / bin_width);
  int old_count = histogram[bin];
  int new_count = old_count + 1;
  histogram[bin] = new_count;
}

void histogram(cuda::std::span<float> temperatures, 
               cuda::std::span<int> histogram, 
               cudaStream_t stream)
{
  int block_size = 256;
  int grid_size = cuda::ceil_div(temperatures.size(), block_size);
  histogram_kernel<<<grid_size, block_size, 0, stream>>>(
    temperatures, histogram);
} 
```
compile and run with:
```bash
import Sources.dli
Sources.dli.run("Sources/histogram-bug.cu")
```
## Data Race
Something went wrong. 
Despite having four million cells, our histogram comes out nearly empty. 
The culprit is in this kernel code:

```c++
int old_count = histogram[bin];
int new_count = old_count + 1;
histogram[bin] = new_count;
```

Because this code runs simultaneously on millions of threads while attempting to read/write a single copy of the `histogram` span, it introduces a data race.  
For example, if two threads increment the same bin at the same time, 
both read the same initial value and overwrite one another’s updates, 
causing the bin to increment only once instead of twice. 
Multiplied by millions of cells, this leads to a nearly empty histogram.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_02/race.png" alt="Data Race" width=1000>

To fix this, we need to make the read, modify, and write steps a single, indivisible operation. 
CUDA provides atomic operations that handle concurrency safely, ensuring we don’t lose any increments in our histogram.

```c++
%%writefile Sources/atomic.cu
#include <cuda/std/span>
#include <cuda/std/atomic>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

__global__ void kernel(cuda::std::span<int> count)
{
    // Wrap data in atomic_ref
    cuda::std::atomic_ref<int> ref(count[0]);

    // Atomically increment the underlying value
    ref.fetch_add(1);
}

int main()
{
    thrust::device_vector<int> count(1);

    int threads_in_block = 256;
    int blocks_in_grid = 42;

    kernel<<<blocks_in_grid, threads_in_block>>>(
        cuda::std::span<int>{thrust::raw_pointer_cast(count.data()), 1});

    cudaDeviceSynchronize();

    thrust::host_vector<int> count_host = count;
    std::cout << "expected: " << threads_in_block * blocks_in_grid << std::endl;
    std::cout << "observed: " << count_host[0] << std::endl;
}
```
compile and run with:
```bash
!nvcc -arch=native Sources/atomic.cu -o /tmp/a.out -run
```


In the example above, we reproduce our histogram kernel’s structure, where multiple threads attempt to increment the same memory location. 
This time, however, we wrap the memory reference in a `cuda::std::atomic_ref<int>`:

```c++
cuda::std::atomic_ref<int> ref(count[0]);
```

Here, `int` indicates the type of the underlying value, and the constructor accepts a reference to the memory we want to modify. 
The resulting atomic_ref object offers atomic operations, such as:

```c++
ref.fetch_add(1);
```

This call performs an indivisible read-modify-write operation: it reads the current value of `count[0]`, adds one, and writes the result back atomically.
You can think of atomics as writing an instruction rather than a direct value. 

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_02/atomic.png" alt="Atomics" width=800>

The "?" is replaced by the current value of `count[0]`, incremented by one, and stored in a single step. 
It doesn’t matter how many threads do this concurrently - the result remains correct.


### Exercise: Fix Histogram

The code below has a data race in it.
Multiple threads concurrently increment the same element of the histogram array.
Use `cuda::std::atomic_ref` to fix this bug. 

Interface of `cuda::std::atomic_ref` is equivalent to `std::atomic_ref`:

```c++
__global__ void kernel(int *count)
{
  // Wrap data in atomic_ref
  cuda::std::atomic_ref<int> ref(count[0]);

  // Atomically increment the underlying value
  ref.fetch_add(1);
}
```

<details>
<summary>Original code in case you need to refer to it.</summary>

```c++
%%writefile Sources/histogram.cu
#include "dli.cuh"

constexpr float bin_width = 10;

__global__ void histogram_kernel(cuda::std::span<float> temperatures, 
                                 cuda::std::span<int> histogram)
{
  int cell = blockIdx.x * blockDim.x + threadIdx.x;
  if (cell < temperatures.size()) {
    int bin = static_cast<int>(temperatures[cell] / bin_width);

    // fix data race in incrementing histogram bins by using `cuda::std::atomic_ref`
    int old_count = histogram[bin];
    int new_count = old_count + 1;
    histogram[bin] = new_count;
  }
}

void histogram(cuda::std::span<float> temperatures, 
               cuda::std::span<int> histogram,
               cudaStream_t stream)
{
  int block_size = 256;
  int grid_size = cuda::ceil_div(temperatures.size(), block_size);
  histogram_kernel<<<grid_size, block_size, 0, stream>>>(
    temperatures, histogram);
}
```
    
</details>


```c++
%%writefile Sources/histogram.cu
#include "dli.cuh"

constexpr float bin_width = 10;

__global__ void histogram_kernel(cuda::std::span<float> temperatures, 
                                 cuda::std::span<int> histogram)
{
  int cell = blockIdx.x * blockDim.x + threadIdx.x;
  if (cell < temperatures.size()) {
    int bin = static_cast<int>(temperatures[cell] / bin_width);

    // fix data race in incrementing histogram bins by using `cuda::std::atomic_ref`
    int old_count = histogram[bin];
    int new_count = old_count + 1;
    histogram[bin] = new_count;
  }
}

void histogram(cuda::std::span<float> temperatures, 
               cuda::std::span<int> histogram,
               cudaStream_t stream)
{
  int block_size = 256;
  int grid_size = cuda::ceil_div(temperatures.size(), block_size);
  histogram_kernel<<<grid_size, block_size, 0, stream>>>(
    temperatures, histogram);
}
```
compile and run with:
```bash
import Sources.dli
Sources.dli.run("Sources/histogram.cu")
```

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

<details>
  <summary>Hints</summary>
  
  - `cuda::std::atomic_ref` wraps a reference and applies atomic operations to the underlying object
  - You can increment a variable atomically using `ref.fetch_add(1)`
</details>

Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.

<details>
  <summary>Solution</summary>

  Key points:

  - Wrap selected bin in `cuda::std::atomic_ref<int>` for atomic operations
  - Use `fetch_add` to increment the bin value atomically

  Solution:
  ```c++
  __global__ void histogram_kernel(cuda::std::span<float> temperatures,
                                   cuda::std::span<int> histogram) 
  {
    int cell = blockIdx.x * blockDim.x + threadIdx.x;
    int bin = static_cast<int>(temperatures[cell] / 10);

    cuda::std::atomic_ref<int> ref(histogram[bin]);
    ref.fetch_add(1);
  }
  ```
</details>

## Synchronization


### Memory Contention

With the fix from the previous exercise, our histogram kernel finally produces correct results, but performance remains suboptimal. 
Why? Because using a single shared histogram forces millions of atomic operations on the same memory location. 
This causes significant contention and implicit serialization.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_04/contention.png" alt="Contention" width=500>

In the worst case, all threads map their data to a single bin. 
With around 16 thousand blocks and 256 threads each, that’s roughly 4 million atomic operations contending for the same location.  So while we have launched a few million threads, the atomic operation serializes the write to the `histogram` span, and in effect our parallel code now runs partly in serial.  


## Private Histogram
To reduce this overhead, we can introduce a "private" histogram for each thread block. 
Each block would accumulate its own local copy of histogram, then merge it into the global histogram after all local updates are complete.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_04/private.png" alt="Private" width=800>

Now, in the worst case, up to 256 atomic operations occur within a block’s private histogram, plus about 16k merges (one per block). 
That’s 256 + 16k total atomic operations, a big improvement over 4 million.

Let’s see how to implement this optimization:

```c++
%%writefile Sources/bug.cu
#include "dli.cuh"

constexpr float bin_width = 10;

__global__ void histogram_kernel(
  cuda::std::span<float> temperatures, 
  cuda::std::span<int> block_histograms, 
  cuda::std::span<int> histogram) 
{
  cuda::std::span<int> block_histogram = 
    block_histograms.subspan(blockIdx.x * histogram.size(), histogram.size());

  int cell = blockIdx.x * blockDim.x + threadIdx.x;
  int bin = static_cast<int>(temperatures[cell] / bin_width);

  cuda::std::atomic_ref<int> block_ref(block_histogram[bin]);
  block_ref.fetch_add(1);

  if (threadIdx.x < 10) {
    cuda::std::atomic_ref<int> ref(histogram[threadIdx.x]);
    ref.fetch_add(block_histogram[threadIdx.x]);
  }
}

void histogram(
  cuda::std::span<float> temperatures, 
  cuda::std::span<int> block_histograms, 
  cuda::std::span<int> histogram,
  cudaStream_t stream) 
{
  int block_size = 256;
  int grid_size = cuda::ceil_div(temperatures.size(), block_size);
  histogram_kernel<<<grid_size, block_size, 0, stream>>>(
    temperatures, block_histograms, histogram);
}
```

Our updated kernel now accepts an additional argument for storing per-block histograms. 
Its size is the number of bins times the number of thread blocks. 
Within the kernel, we use `subspan` to focus on the portion of this buffer corresponding to the current block’s histogram.
However, if you run the code below, you’ll see that the result is still incorrect.


compile and run with:
```bash
import Sources.dli
Sources.dli.run("Sources/bug.cu")
```

### Data Race

The following code contains a data race:

```cpp
cuda::std::atomic_ref<int> block_ref(block_histogram[bin]);
block_ref.fetch_add(1);

if (threadIdx.x < 10) {
  cuda::std::atomic_ref<int> ref(histogram[threadIdx.x]);
  ref.fetch_add(block_histogram[threadIdx.x]);
}
```

We assumed all threads in the same thread block would finish updating the block histogram before any threads started reading from it, but CUDA threads can progress independently, even within the same thread block.  To state it more clearly, there is no guarantee that threads in the same thread block are synchonized with each other.  Some threads maybe be finished executing the entire kernel before other threads even start.  This is a very important concept to internalize as you write parallel algorithms and CUDA kernels.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_04/data-race-read-1.png" alt="Expected" width=800>


As a result, some threads may read the histogram before it’s fully updated.
Here, we assumed that all threads in the block finished upating block histogram before other threads start reading it.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_04/data-race-read-2.png" alt="Possible" width=800>

To fix this issue, we must force all threads to complete their updates before allowing any thread to read the block histogram. 
CUDA provides `__syncthreads()` function for this exact purpose.  The `__syncthreads()` function is a barrier which all threads in the thread block *must* reach before any thread is permitted to proceed to the next part of the code.

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_04/sync.png" alt="Synchronization" width=800>

### Add Synchronization

In the next exercise, you'll fix the issue by adding synchronization in the appropriate place.
Besides the correctness issue, we have some performance inefficiencies in the current implementation.
To figure out what's wrong, let's return to what's available in the `cuda::` namespace.
We've seen `cuda::std::atomic_ref` already, but there's also `cuda::atomic_ref` type.
These two types share the same interface except for one important difference.
`cuda::atomic_ref` has one extra template parameter, representing a thread scope.

```c++
cuda::std::atomic_ref<int> ref(/* ... */);
cuda::atomic_ref<int, thread_scope> ref(/* ... */);
```

Thread scope represents the set of threads that can synchronize using a given atomic. 
Thread scope can be system, device, or block.

For instance, all threads of a given system are related to each other thread by `cuda::thread_scope_system`. 
This means that a thread from any GPU (in a multi-GPU system) can synchronize with any other GPU thread, or any CPU thread. 
The `cuda::std::atomic_ref` is actually the same thing as `cuda::atomic_ref<int, cuda::thread_scope_system>`.

In addition to the system scope, there are also device and block scopes.
The device scope allows threads from the same device to synchronize with each other.
The block scope allows threads from the same block to synchronize with each other.

Since our histogram kernel is limited to a single GPU, we don't need to use the system scope.
Besides that, only threads of a single block are issuing atomics to the same block histogram.
This means that we can leverage the block scope to improve performance.


### Exercise: Fix Data Race

You can use `__syncthreads()` to synchronize threads within a block:

<img src="https://github.com/sergiocollado/potpourri/blob/master/Notes_on_GPUs/images/cuda_3_04/sync.png" alt="Sync" width=600>

Fix the data race using thread-block synchronization.
Optionally, switch to `cuda::atomic_ref` to reduce the scope of communication:

Fix the data race using thread-block synchronization.
Optionally, switch to `cuda::atomic_ref` to reduce the scope of communication:

<details>
<summary>Original code if you need to refer back to it.</summary>

```c++
%%writefile Sources/sync.cu
#include "dli.cuh"

constexpr float bin_width = 10;

// 1. Use `__syncthreads()` to synchronize threads within a block and avoid data race
__global__ void histogram_kernel(
  cuda::std::span<float> temperatures, 
  cuda::std::span<int> block_histograms, 
  cuda::std::span<int> histogram) 
{
  cuda::std::span<int> block_histogram = 
    block_histograms.subspan(blockIdx.x * histogram.size(), 
                             histogram.size());

  int cell = blockIdx.x * blockDim.x + threadIdx.x;
  int bin = static_cast<int>(temperatures[cell] / bin_width);

  cuda::std::atomic_ref<int> block_ref(block_histogram[bin]);
  block_ref.fetch_add(1);

  if (threadIdx.x < histogram.size()) {
    // 2. Reduce scope of atomic operation using `cuda::atomic_ref`
    cuda::std::atomic_ref<int> ref(histogram[threadIdx.x]);
    ref.fetch_add(block_histogram[threadIdx.x]);
  }
}


void histogram(
  cuda::std::span<float> temperatures, 
  cuda::std::span<int> block_histograms, 
  cuda::std::span<int> histogram,
  cudaStream_t stream) 
{
  int block_size = 256;
  int grid_size = cuda::ceil_div(temperatures.size(), block_size);
  histogram_kernel<<<grid_size, block_size, 0, stream>>>(
    temperatures, block_histograms, histogram);
}
```

</details>

```c++
%%writefile Sources/sync.cu
#include "dli.cuh"

constexpr float bin_width = 10;

// 1. Use `__syncthreads()` to synchronize threads within a block and avoid data race
__global__ void histogram_kernel(
  cuda::std::span<float> temperatures, 
  cuda::std::span<int> block_histograms, 
  cuda::std::span<int> histogram) 
{
  cuda::std::span<int> block_histogram = 
    block_histograms.subspan(blockIdx.x * histogram.size(), 
                             histogram.size());

  int cell = blockIdx.x * blockDim.x + threadIdx.x;
  int bin = static_cast<int>(temperatures[cell] / bin_width);

  cuda::std::atomic_ref<int> block_ref(block_histogram[bin]);
  block_ref.fetch_add(1);

  if (threadIdx.x < histogram.size()) {
    // 2. Reduce scope of atomic operation using `cuda::atomic_ref`
    cuda::std::atomic_ref<int> ref(histogram[threadIdx.x]);
    ref.fetch_add(block_histogram[threadIdx.x]);
  }
}


void histogram(
  cuda::std::span<float> temperatures, 
  cuda::std::span<int> block_histograms, 
  cuda::std::span<int> histogram,
  cudaStream_t stream) 
{
  int block_size = 256;
  int grid_size = cuda::ceil_div(temperatures.size(), block_size);
  histogram_kernel<<<grid_size, block_size, 0, stream>>>(
    temperatures, block_histograms, histogram);
}
```
compile and run with:
```bash
import Sources.dli
Sources.dli.run("Sources/sync.cu")
```

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.

<details>
  <summary>Hints</summary>
  
  - You can synchronize threads within a thread block using `__syncthreads()`
  - You need to synchronize after all threads have incorporated their changes to the block histogram
  - `cuda::atomic_ref` has exactly the same interface as `cuda::std::atomic_ref` with a difference of accepting thread scope as a second template parameter
</details>

Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.

<details>
  <summary>Solution</summary>

  Key points:

  - Synchronize before reading the block histogram

  Solution:
  ```c++
  cuda::std::span<int> block_histogram =
    block_histograms.subspan(blockIdx.x * histogram.size(), histogram.size());

  int cell = blockIdx.x * blockDim.x + threadIdx.x;
  int bin = static_cast<int>(temperatures[cell] / bin_width);

  cuda::atomic_ref<int, cuda::thread_scope_block> 
    block_ref(block_histogram[bin]);
  block_ref.fetch_add(1);
  __syncthreads();

  if (threadIdx.x < histogram.size()) 
  {
    cuda::atomic_ref<int, cuda::thread_scope_device> 
      ref(histogram[threadIdx.x]);
    ref.fetch_add(block_histogram[threadIdx.x]);
  }
  ```

</details>


## Shared Memory


With our previous optimizations, the kernel now performs significantly better. 
However, some inefficiencies remain. 
Currently, each block’s histogram is stored in global GPU memory, even though it’s never used outside the kernel. 
This approach not only consumes unnecessary bandwidth but also increases the overall memory footprint.


## Cache Memory

<img src="Images/L2.png" alt="L2" width=900>

As shown in the figure above, there’s a much closer memory resource: each Streaming Multiprocessor (SM) has its own L1 cache. 
Ideally, we want to store each block’s histogram right there in L1. 
Fortunately, CUDA makes this possible through software-controlled shared memory. 
By allocating the block histogram in shared memory, we can take full advantage of the SM’s L1 cache and reduce unnecessary memory traffic.


```c++
%%writefile Sources/simple-shmem.cu
#include <cstdio>

__global__ void kernel()
{
  __shared__ int shared[4];
  shared[threadIdx.x] = threadIdx.x;
  __syncthreads();

  if (threadIdx.x == 0)
  {
    for (int i = 0; i < 4; i++) {
      std::printf("shared[%d] = %d\n", i, shared[i]);
    }
  }
}

int main() {
  kernel<<<1, 4>>>();
  cudaDeviceSynchronize();
  return 0;
}
```
compile and run with:
```bash
!nvcc -o /tmp/a.out Sources/simple-shmem.cu && /tmp/a.out
```

To allocate shared memory, simply annotate a variable with the `__shared__` keyword.
This puts the variable into shared memory that coresides with the L1 cache.
Since shared memory isn't automatically initialized, 
we begin our kernel by having each thread write its own index into a corresponding shared memory location:

```c++
shared[threadIdx.x] = threadIdx.x;
__syncthreads();
```

The `__syncthreads()` call ensures that all threads have finished writing to the shared array before any thread reads from it. 
Afterwards, the first thread prints out the contents of the shared memory:

<img src="Images/simply-shared.png" alt="Shared Memory" width=600>

As you can see, each thread successfully stored its index in the shared array, and the first thread can read back those values.
















```c++

```
compile and run with:
```bash

```










