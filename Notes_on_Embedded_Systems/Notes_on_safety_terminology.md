**EMBEDDED SYSTEM**: An embedded system is a system, that combines software and hardware, although is also common that they have some  kind of HMI (human machine interface). Embedded systems have fixed capabilities but are programmable, and they are designed for a specific function or functions. 

Examples are: industrial equipments, machine's controllers, agricultural, automotive, medical, aeronautical or space systems, telecomunication systems or even household apliances, enterntaiment systems, toys, vending machines, measurent systems, security and identity checks, robotics, logistics, production lines ...

Most of the times, embedded systems are reactive, that means, they wait for an input, when they have it, they perform some computation, and then it generates an output. Than means they can be modelled as an Automata.

**SAFETY**: Is the propierty of a system that evaluates the risk of the ocurrence of an accident.

**FUNCTIONAL SAFETY** Is the safety of a system that correspond to the correct actions acording to the system inputs, it also includes
detection of potential dangerous states, and activation of protective, corrective or mitigation measures.

Functional safety implies active measures, as an example is the airbag systems in vehicles, when a crash is detected, a safety system
is triggered. On the other hand, a helmet that protects the driver, is a passive system; passive systems are not functional safety.

The leading standard for functional safety is the IEC 61508

**SECURITY**: Is the propierty of a system that evaluates its ability to deal with malicious actions or attacks.

Take into account, that there is a significance difference between the concepts of safety and security, both terms account protection against a damage, but security implies a malicious or intended action to do a damage, while safety relates to an unintended situation.

**ACCIDENT**: The event of causing/receiving damage of any kind (either directly or indirectly): equipment damage, property damage, or damage to the enviroment, and human injuries or even deaths.

**RISK**: Combination of the likehood on an accident and its severity.   Risk = probability(accident) * severity(accident)

ISO 31000 - standards for risk management:
 - ISO 31000 - Principles and guide lines for implementation.
 - ISO 31010 - Risk management, and risk assesment techniques. 
 - ISO Guide 73 - Vocabulary

**Risk Assestment**: Is the analisys to identify and determine the possible situations or conditions that may end in an accident, thus there is a thread(hazard). If the risk assesment is quantitative, it needs two factors: the Risk(R) = magnitude of the potencial lost (L) and the probability (p) that lost happens.

Ri = Li * p(Li);

**HAZARD**: Set of combinations of conditions or requisites or events that lead to an accident

**ERROR/MISTAKE**: A human being can make an error(mistake), with produces a defect (fault, bug) in the program or code, or in a document.  If a defect in code is executed, the system amy fail to do what it shoud do, what it should do (or do something it shouldnt)
causing a failure. Defects in software, systms or documnets may result in failures, bot no all defects do.

**FAILURE**: A failure is the misperformance or lack of hability of a component to comply with its designed function, during certain
time, or under specified enviromental system conditions.

**ERROR**: An error is a desing flaw or desviation from an intended or designed state.

>__A word about SW context__
> A human being can make an error (mistake), wich produces a defect (fault, bug) in the program, code, or in a document. If a defect in the
> code is executed, the system may fail to do what it must do (or do something it shouldn't) causing a failure. 

**RELIABILITY**: Is the probability that a piece of equipment or component will perform correctly its intended goal, inside the defined time, and under the correct enviroment.

Reliability is often quantified with the merit figure of MTBF (Mean Time Between Failures) 

**AVAILABILITY**: Is the probability that the system will be working/performing as expected at any given time.

Availability is often quantified by 1-MTTR / MTTF 

where:

**MTTR** stands for Mean Time To Repair the system

and 

**MTTF** stands for Mean Time To Failure


**DEPENDABILITY**: Is the truthworthiness of a system so the is a justified confidence in the tasks it must perform.

Dependability is a concept that includes:
- Reliability
- Availability
- Maintanability
- Safety
- Security 

**FAULT TOLERANT SYSTEM**: Is a system that performs correctly, although might have some errors in it. Usually this is
achieved by means of repeated computations, monitoring data, and redundant systems.

RECOVERING FROM ERRORS:
For recoverign from errors there are two aproaches:

 - roll forward
 - roll back

When the systems detects an error, the *roll forward* recovery takes the system state at that point and corrects it, to be able to move forward. *Roll back* recovery revert the system state back to some earlier correct state (i.e. last checkpoint) and moves forward from there.

N-VERSION SOFTWARE:
N-version programming (NVP) or multiversion programming or multiple version dissimilar software, is a method where multiple equivalent functional programs are generated from the same especifications. The goal of this methodology is that with this the probability of identical software faults is greatly reduced. 

- [] todo: finish this

References:
https://en.wikipedia.org/wiki/N-version_programming </br>
http://ieeexplore.ieee.org/document/532621/ </br>


SELF-CHECKING SOFTWARE - Built In Self Test (BIST)
Usually an internal check of the components of the systems, helps to prevent further errors, in case some component doesn't comply with an optimal state. Thus preventing us an upcomming failure during operation of the system.

Is very common, that some hardware components include these techniques embedded in them.

http://www.eventhelix.com/RealtimeMantra/FaultHandling/hardware_diagnostics.htm#.WRoST2jyjIU </br>

EXAMPLE:

 Suppouse, you have a sistem, in which two task/phreatds/programs ... are working togeder, one of them, task_1 - senses, gadthers and updates data in real time. task_2: request that data, and do some kind of that processing. 
 In the event, that for whatever reason, maybe some bug, or that there arent enough memory..., the task_1 stops on working, or performing ok, may be it reports the dreaded: segmentation fault... at that point, the task_2, should be able to detect the problem, - there are some methods to do this - and it should try to fix the system, for example, relaunching, the task_1, or reseting the whole system in the wort case.
 
 
References:
https://en.wikipedia.org/wiki/Fault-tolerant_computer_system </br>
https://en.wikipedia.org/wiki/Software_fault_tolerance </br>
https://users.ece.cmu.edu/~koopman/des_s99/sw_fault_tolerance/ </br>


**ROBUST SYSTEMS** Robust systems are those in which the computer system has the ability to cope with errors during execution and cope with erroneous inputs. Usually you test those systems with the technique of *Fault Injection*, other techniques are for example *Fuzzy testing* that involves invalid or unexpected inputs. 

























# PROGRAMMING TECHNIQUES:

## Robust programming

Robust programming is a style of programming that focus on handling unexpected terminations and unexpected actions. The code should handle those events gracefully and log or display accurate and unambigous **error mensages**, this will allow to detect and correct
much easily the pernicious event.

### Principles:

#### Paranoia
 The programmmer must undestand that its code can produce bug, that make the system fail or work incorrectly. Also that the users are there to break their code. - You know the saying: *--Even paranoids have enemies--*
#### Stupity
 The programmers assumes that the user at some point will use incorrect, malformed, and bogus inputs. So he has to code error-proof inputs, and emit **error mesages**, that are clear, intuitive, unambigous, and that don't require to look up error codes. The message should be as accurate as possible, to the problem can be detected and corrected with ease.
#### Dangerous implementations
 Users should not gain access to the inners of the system/program - that is: libraries, internal states, internal values, or pointer to data structures ... The interfece with the user should be that, and be probed against loopholes.
 
References:
https://en.wikipedia.org/wiki/Robustness_(computer_science)#Robust_programming </br>
http://nob.cs.ucdavis.edu/bishop/secprog/robust.html </br>

## Defensive programming

Defensive programming is a defensive coding style intended to ensure the continuing function of a program under unforeseen circunstances. This code style is usually used in systems with need high availability, safety and security.

### Techniques:

#### Intelligent code reuse:
Existing code is tested and is knwon to work. reuse of it may reduce the chance of new bugs. 

 - [ ] TODO: complete this.

References: 
https://en.wikipedia.org/wiki/Defensive_programming </br>

## Inmunity-aware programming

When writing code for an embedded system, inmunity-aware programming, refers to programming techniques which improve tolerance of transient errors in the program counter or in other modules that may lead to a failure. Transient errors usually are cause for single events, as a micro-cut in the power supply or a strong electromagnetic event, trasnmitted from another source to our device. 

Inmunity-aware programming is an example of defensive programming and EMC-aware programming. The techniques usually are applied to the 'victim' of the emmision, to make it more reliable. 


References:
https://en.wikipedia.org/wiki/Immunity-aware_programming </br>
http://www.st.com/content/ccc/resource/technical/document/application_note/1c/6c/02/93/79/c8/4e/32/CD00004037.pdf/files/CD00004037.pdf/jcr:content/translations/en.CD00004037.pdf </br>

https://web.archive.org/web/20110524052840/http://www.conformity.com/artman/publish/printer_214.shtml </br>
http://www.nxp.com/assets/documents/data/en/application-notes/AN2764.pdf </br>


## Failure mode and effects analysis (FMEA)

 - [ ] todo: complete
 
References: 
https://en.wikipedia.org/wiki/Failure_mode_and_effects_analysis </br>
 
 
 
# MORE ON PROGRAMMING TECHNIQUES

As stated previously, most of the times, embedded systems are reactive, that means, they wait for an input, when they have it, they perform some computation, and then it generates an output. Than means they can be modelled as an Automata.

**OPERATIONAL SEMANTICS**: are a category of formal programming lenguaje semantics, in which certain desired propierties of a program, such correctness, safety or security are verified by proofs of logical statements about its execution and procedures, 

**TRANSITION SYSTEM**: In computer science, a transition system is used to describe the potential of a discrete system. It consists in states, and trasitions between states.

Transitions systems differs from *Finite State Automata* in several ways:
- The set of states, is not necessarily finite, but it must be contable.
- The set of transitions, is not necessarily finite, or even countable
- Not *Start* state, or *End* state, are given.

Reference: https://en.wikipedia.org/wiki/Transition_system </br>

Formal definition:

## Transition system:
Is a pair (S,→), where S, is a set of states, and → is a set of transitions. The case, where there is a transition from state **p** to state **q**, is written as: **p→q**.

## Labelled transition system (LTS):
Is a tuple (S,Λ,→), where S, is a set of states, Λ is a set of labels, and → is a set of labelled transitions.

Labels, can represent different things, depending of the context, usually they are the representation of th einput expected, or the conditions that must comply to trigger the transition. 

If for any given state *p*, and label *α*, only exits one tuple *(p,α,q)*, then it is said, that *α*, is **_deterministic_** for *p*.

## Bisimulation
Bisimulation is a relationship between state transition systems, that associates systems that behaves in the same way in the sense
that one system simulates the other and vice versa.

Formal definition:
Given a LTS (S,Λ,→) a bisimulation relation is a binary relation **R**, over **S**, i.e.( **R ⊆ to S x S**) such both **R** and its inverse **R^-1** are simulations.

Equivalently **R** is a bisimulation if for every pair of elements **p**,**q** in the space of states **S**, with (p,q) in **R**, ∀ α in Λ:

for all **p'** in **S**: p  → (α) → p'
implies that there is a **q'** in **S**, that: q  → (α) → q 
and (p',q') ∈ **R**

and, simetrically: for all **q'** in **S**:  q  → (α) → q'
implies that there is a **p'** in **S**, that: p  → (α) → p'
and (p',q')  ∈ **R**

So given two states **p** and **q** that belong to the state space **S**, **p** is _**bisimilar**_ to **q**, and is writen as: **p ~ q**, if there is a bisimulation **R** such that **(p,q)** are in **R**.



!if two process are bisimulation equivalents, they are equivalents from any perspective you can think of!

![bisimulation.png](./image/bisimulation.png)

Reference: https://en.wikipedia.org/wiki/Bisimulation

Reference: http://theory.stanford.edu/~rvg/abstracts.html#45

Reference: http://theory.stanford.edu/~rvg/abstracts.html







TODO: Check and elavorate: https://en.wikipedia.org/wiki/Calculus_of_communicating_systems
