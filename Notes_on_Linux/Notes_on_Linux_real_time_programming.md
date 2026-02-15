# Notes on Linux real time programming

## Introduction real time computing 

Real time computing, refers to to systems where the corretness of the operations depends on not only the logical results of computations, but also on the time at which the results are produced. The **timeliness** is relevant in a real-time program.

The defining characteristic of a real-time system is compliance with the **timing constrains**. These constrains are called **deadlines**. 
- **Met deadline**: the system operates correctly.
- **Missed deadline**: the system has failed, even if the computed result is mathematical perfect.

Key characteristics of a real-time system:
- **Determinism**: this is the ability of a system to respond to events within  a known, predictable and guaranteed time frame. It's not about being "fast" but about being **predictable**.
- **Predictability**: The system's behaviour must be predictable under all possible conditions, including peak loads. The system should be possible to be analyzed and guarantee all deadlines before the system is even build.
- **Responsiveness**: This involves two factors:
    - **Latency**: The time between an event occurring and the system recognizing it (e.g. an interrupt being serviced)
    - **Jitter**: The variation in latency. For tasks that need to happen periodically. High jitter means the timing is unpredictable. 
