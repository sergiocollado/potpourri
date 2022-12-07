
# Notes on distributed systems

Notes based on http://www.distributedsystemscourse.com/

Other references: 
- https://www.youtube.com/watch?v=cQP8WApzIQQ&list=PLrw6a1wE39_tb2fErI4-WkMbsvGQk9_UB
- https://pdos.csail.mit.edu/6.824/
- https://github.com/Sorosliu1029/6.824

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
but they have to be taken into account in order to design a robust algorithm. The solution to a partition can be a trade-off between the system's reliability and consistency. -> CAP principle: Consistency - Availability - Partitioning tolerance (Eric Brewer) https://en.wikipedia.org/wiki/CAP_theorem

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


|    | Node | Network |
| --- | --- | --- | 
| Fail Stop | Checkpoint & recover or Replicate & fail over | worry about partitions Network protocol handles the rest | 
| Byzantine | Attempt to transform into fail stop | worry about partitions Network protocol handles the rest | 

## Byzantine Fault Tolerance

How to design and build a distrubuted system that can survive the workt possible errors in the system?

A node, with some malfuction, which send incorrect of conflicting messages, is known as a 'traitor node'. 

This can be cause as a flaky node in the sytem, o by a malicious node (owned by an adversary). 

## what assumptions are to be taken?

- can all nodes see all messages? some? none?
- do nodes fail? how about the network?
- finite computation?
- static or dynamic adversary? 
- bounded communication time?
- fully connected network?
- randomized algorithms?

## The two generals problem

The two generals problem is a consensus problem. A consensus problem, is a problem in which two nodes
of the distributed system have to agree. 

In this problem, there are two armies: A and B, and they need to agree if they attack army C in the morning, or retreat. If both armies attack army C in the morning, they would win. But if only one army attacks army C
it would be defeated. 

The generals of armies A and B, can only communicate though couriers, and the couriers have to go through 
the territory of an enemy army C, so may or may not make it to the other general. 

So, the two generals have to have a protocol, or a series of messages, that allow them to reach and comfirm a consensus of when to attack. What kind of messages or protocols should they use to achieve the consensus?

It can be proof that there is no perfect solution to this problem. 

In a distributed problem, the network is the byzantine general. 

In practice, we suppouse the enemy general is not considered perfectly byzantine. 

How would be the problem, if the network works, an the nodes of the system are the ones that are corrupted, 
that is what is know as the "Byzantine generals problem", this is a seminal paper by: Leslie, Lamport and Robert in 1982. In this case, one of the general is a traitor. 

For the 3 generals and 1 traitor, there is no solution. So, how many generals do we need to solve the issue?
In the paper, is the lemma, that there is no solution for (3m+1) generals, when there is more that m traitors. That is if there is more that 1/3 of the generals are traitors.

references:
- https://en.wikipedia.org/wiki/Two_Generals%27_Problem
- https://lamport.azurewebsites.net/pubs/byz.pdf
- https://pmg.csail.mit.edu/papers/bft-tocs.pdf


## SLIs, SLOs and SLAs

Those are metrics that inform abut the performance and reliability of
a distributed system.

SLI, stands for Service Level Indicator. It is what it is being 
measured, for example, an uptime. Or how long does it take to
respond to a query to the system. SLIs are important because if a 
metric is monitored, then that is the first stept, in the case
it wants to be improved. 

SLO, stands for Service Level Objetive, those try to represent how 
good the expected inidicators are, or how good should those be.

SLA, stands for Service Level Agreement, is an SLO, plus the consecuences
in case the system doesn't perform as expected in the SLA. This is
useful, for contract relations. 




