
# Notes on distributed systems

Notes based on http://www.distributedsystemscourse.com/

## What is a distributed system?

A distributed system, is a system which is not centralized on a single computer. So it is divided over several computer. 

This has some advantages:
- more robust, can tolerate failures of the computers that compose the system.
- more scalable, can suppport many user

As a disadvange: it is more complex. 

Due distrubuted systems are complex, are considered an advanced topic in computer science.

## Why build a distributed system?

- Scaling
- Reliability
- Dependency on th ecloud
- performance (latency/bandwidth)
- uptime requirments

## Topics in distributed systems

- How system fail 
- How to express goeals: SLIs (service level indicator), SLOs (service lebel objectibve) and SLAs (service level agreement)
- How to conbine unreliable components to make a mor reliable system (architecture)
- How nodes comunicate: RPCs 
- How nodes find each other - naming. 
- How to use time in a distributed world. what happens when you have event in different machines, and you care about the order of those events. Clock synchronizations. 
- How to get an agreement --consensus : Paxos & Raft protocols. https://en.wikipedia.org/wiki/Paxos_(computer_science) https://en.wikipedia.org/wiki/Raft_(algorithm)
- How to persist data --distributed storage
- How to secure your system
- How to operate your distributed system -- the art of SRE

## What failures can happen?

- one process stops, or go into a crash looop
- data corruption
- server down
- query of death - a query that brings the system down
- brocken dependency
- DoS attack
- cascade failure 
- system fails in production but now in development
- custom reported failue
- data los
- time travel
- Owned
- fatal errors .... 
- operator error
- runaway automation
- certification expiration
- performanc cliffs
- firewalls 
- kernel memory leak
- hash collision
- ...

## Types of failures

Usually systems are resiliant to categories of failures, and those categories are picked and chosed. Each classs of failuer is prioritized of assigned importace according to its: {frequency * impact} 

### Partitioin failure

At least 2 component of the system continue to run, but cannot communicate. Usually partition failuer, is a temporal issue, 
but they have to be taken into account in order to design a robust algorithm. The solution to a partition can be a trade-off between the system's reliability and consistency. -> CAP priinciple: Consistensy Availability Partitioning (Eric Brewer) https://en.wikipedia.org/wiki/CAP_theorem

To detect a partition, the cuorum algorithm is used:

For each node, periodically:
- ping all N nodes
- count responses R
- If R <= floor(N/2), node halts. (or goes into read-only mode)

floor(N/2) is to identify, the node is in a partition of less than half the original nodes.

### Nodes failures

Hen a fail stop happens, usually there are two solutions: 

- reboot: checkpoint state and restart (high latency)
- fail over to another node (hot spare): replicate state and fail over (high cost)

### Byzantine failure

A byzantine failure is everything that is not a fail stop. 

The goal is to turn this case is to turn into fails stop:
- checksum/ECC
- assertions
- timeouts


|    | NOde | Network |
| --- | --- | --- | 
| Fail Stop | Checkpoint & recover or Replicate & fail over | worry about partitions Network protocol handles the rest | 
| Byzantine | Attempt to transform into fail stop | worry about partitions Network protocol handles the rest | 



