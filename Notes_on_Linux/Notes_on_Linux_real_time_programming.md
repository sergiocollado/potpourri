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


### Types of real-time systems

Real time systems are categorized on the severity of missing a deadline.

**Hard real-time system**: Missing a deadline is catasthrophic and considered a total system failure. It can lead to human injury, death, significant material losses or enviromental damages. It is requiered to have absolute predictibillity and 100% guarantee to met all the deadlines. This is achieved by means of mathematical scheduling analisys. Examples of a hard real-time systems: airbag, aircraft flight control system, nuclear reactor cooling control system.  

**Soft real-time system**: Missing a deadline is undesireable and degrades performance or quality but it is not catastrophic. The system continues to operate , but its utility or effectiveness is reduced. The system strives to meet deadlines and has high predictability, but occasional misses are tolerated. The focus in on high average throughput and low average latency. Examples of soft real-time systems are: video/audio streaming, live video conferency system. 

**Firm real-time system**: Is a sub-set of soft real-time system, missing a deadline is not catastrophic, but the result of the computation has not value after the deadline. There is no point in executing the task late. The consecuence of missing a deadline is that the data is dropped and the system moves into the next step. Examples: radar sweep, stock trading algorithms. 




