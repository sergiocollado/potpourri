# Notes on modern CUDA C++

https://learn.nvidia.com/my-learning

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

std::vector<float> temp{ 42, 24, 50 }

After that, we transform each element of this vector:

for (int i = 0; i < temp.size(); i++) {
    float diff = ambient_temp - temp[i];
    temp[i] = temp[i] + k * diff;
}

Here, we are updating each element of the vector by a constant factor times the difference between the ambient temperature and the current temperature. The result of this computation overwrites each previous element:

diff    = 20 - 42;        // -22
temp[0] = 42 + 0.5 * -22; // 31.0

Finally, we print the new contents of the vector:

If everything goes well and your environment is set up correctly, the cell below should print:
step 	temp[0] 	temp[1] 	temp[2]
0 	31.00 	22.00 	35.00
1 	25.50 	21.00 	27.50
2 	22.75 	20.50 	23.75

!g++ Sources/cpu-cooling.cpp -o /tmp/a.out # compile the code
!/tmp/a.out # run the executable

Let's revisit the steps that we've just made. We started by compiling our code using the g++ compiler:

g++ Sources/cpu-cooling.cpp -o /tmp/a.out

The g++ compiler consumed C++ code and produced an executable file, a.out, which contains a set of machine instructions. However, there’s a problem: different CPUs support different sets of instructions. For example, if you compile the program above for an x86 CPU, the temp[i] + k * diff expression will be compiled into the vfmadd132ss instruction on the x86 architecture. If you try running the resulting executable on an ARM CPU, it won’t work because the ARM architecture does not support this instruction. To run this code on an ARM CPU, you would need to compile it specifically for the ARM architecture. In that case, the expression would be compiled into the vmla.f32 instruction.




// image GPU / cpu expression of compilation.svg



From this perspective, GPUs are no different. GPUs have their own set of instructions, therefore, we have to compile our code for GPUs somehow.

```
!nvcc -x cu Sources/cpu-cooling.cpp -o /tmp/a.out # compile the code
!/tmp/a.out # run the executable
```
Congratulations! You just compiled your first CUDA program!
There's one issue, though: ***none of the code above runs on the GPU***.
That might be surprising because when we compiled our code for the CPU, the entire program could be executed on a CPU.
But now we compile our program for the GPU, and nothing runs on the GPU. 
This confusion is an indicator that we are missing an important piece of CUDA programming model.

## Heterogeneous Programming Model

GPUs are accelerators rather than standalone processors. A lot of computational work, like interactions with network and file system, is done on the CPU. So a CUDA program always starts on the CPU. You, the programmer, are responsible for explicitly specifying which code has to run on the GPU. In other words, you are responsible for specifying which code runs where. The established terminology for where code is executed is execution space.

// heterogeneous svg

// execution policy svg

At a high level, execution spaces are partitioned into **host** (CPU) and **device** (GPU). These terms are used to generalize the programming model. Something other than a CPU could host a GPU, and something other than a GPU could accelerate a CPU.

By default, code runs on the host side. You are responsible for specifying which code should run on the device. This should explain why using nvcc alone was insufficient: we haven't marked any code for execution on GPU.

So, let's try fixing that. The CUDA compiler, **NVCC**, is accompanied by a set of core libraries. These libraries allow you to explicitly specify the execution space where you want a given algorithm to run. To prepare our code for these libraries, let's refactor the temperature update for loop first:

```
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

compile it:

```
!nvcc Sources/gpu-cooling.cu -o /tmp/a.out # compile the code
!/tmp/a.out # run the executable
```

Instead of a for loop, we used the `std::transform` algorithm from the C++ standard library. One of the benefits of using algorithms instead of custom loops is reduced mental load. Instead of "executing" the loop in your mind to see that it implements a transformation pattern, you can quickly recognize it by the algorithm name.

But above all else, using algorithms enables you to easily leverage GPUs! For that, we'll be using one of the CUDA Core Libraries called Thrust. Thrust provides standard algorithms and containers that run on the GPU. Let's try using those:


```
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

compile it:

```
!nvcc --extended-lambda Sources/thrust-cooling.cu -o /tmp/a.out # compile the code
!/tmp/a.out # run the executable
```

Let's take a look at the changes that we've just made. We started by replacing std::vector with thrust::universal_vector. We'll explain why this change was necessary later in this lab. More importantly, we annotated the lambda with __host__ __device__ execution specifiers.

As discussed earlier, we have to compile some of the code into GPU instructions. Execution space specifiers tell NVCC which code can be executed on GPU. The __host__ specifier denotes that a given function is executable by CPU. This specifier is used by default on every C++ function. For example, this means that int main() is the same as __host__ int main().

The __device__ specifier, on the other hand, denotes a function that's executable by GPU. That's how NVCC knows which functions to compile for the GPU and which ones for the CPU. In the code above, we combined the __host__ __device__ specifiers. This indicates that the function can be executed by both CPU and GPU.

Finally, we replace std::transform with thrust::transform. Unlike std::transform, thrust::transform accepts the execution space as the first parameter. In the code above, we explicitly asked Thrust to perform the transformation on device (GPU) by passing thrust::device.


## Execution policy

// image



Congratulations! You've learned some basic truths about execution spaces. Overall, the goal of this lab is to show you that there's no magic behind CUDA:

    Code that starts execution on the host stays on the host.
    Code that runs on the device stays on the device.

## Exercise: Annotate Execution Spaces

The notion of execution space is a foundational concept of accelerated computing. 
In this exercise you will verify your expectation of *where* any given code is executed.

Replace all `???` with `CPU` or `GPU`, based on where you think that specific line of code is executing.  The `dli::where_am_I` function is a helper function for you in this exercise.

After making all the changes, run the subsequent cell to verify your expectations.  

```
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

compile it:

```
!nvcc -o /tmp/a.out --extended-lambda Sources/no-magic-execution-space-changes.cu # build executable
!/tmp/a.out # run executable
```

If you’re unsure how to proceed, consider expanding this section for guidance. Use the hint only after giving the problem a genuine attempt.
Hints

    for invocations in the main function consult heterogeneous programming model section
    for invocations in lambdas consult execution policy section


Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.
Solution

Key points:

    The main function always runs on the CPU
    According to thrust::device execution policy, the first thrust::for_each call invokes lambda on the GPU
    According to thrust::host execution policy, the second thrust::for_each call invokes lambda on the CPU

Solution:

```
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

```
%%writefile Sources/port-thrust-to-gpu.cu
#include "dli.h"

int main() {
    thrust::universal_vector<int> vec{ 1, 2, 3 };
    thrust::for_each(thrust::host, vec.begin(), vec.end(), []__host__(int val) {
        std::printf("printing %d on %s\n", val, dli::execution_space());
    });
}
```
compile it:

```
!nvcc -o /tmp/a.out --extended-lambda Sources/port-thrust-to-gpu.cu # build executable
!/tmp/a.out # run executable
```

Open this section only after you’ve made a serious attempt at solving the problem. Once you’ve completed your solution, compare it with the reference provided here to evaluate your approach and identify any potential improvements.
Solution

Key points:
 - change execution policy from thrust::host to thrust::device
 - change execution space specifier from __host__ to __device__

Solution:

```
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

```
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

```
!nvcc -o /tmp/a.out --extended-lambda Sources/port-sort-to-gpu.cu # build executable
!/tmp/a.out # run executable
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
