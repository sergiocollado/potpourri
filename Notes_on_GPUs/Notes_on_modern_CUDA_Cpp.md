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












```c++

```
compile and run with:
```

```
