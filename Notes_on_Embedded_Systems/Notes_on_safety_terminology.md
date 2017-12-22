 # NOTES ON EMBEDDED SYSTEMS SAFETY

**EMBEDDED SYSTEM**: An embedded system, is a system, that combines software and hardware, and also is common, that they have some kind of HMI (human machine interface) or UI (User Interface) as displays, keyboards, et cetera. Embedded systems have fixed capabilities but are programmable, and they are designed for a specific function or functions. 

Examples are: industrial equipments, machine's controllers, agricultural, automotive, medical, aeronautical, space and telecomunication systems, household apliances, enterntaiment systems, toys, vending machines, measurent systems, security and identity checks, robotics, logistics, production lines ...

Most of the times, embedded systems are reactive, that means, they wait for an input, or measure some propierty or signal, and when they have it, they perform some computation, and then it generates an output. Than means they can be modelled as an Automata.

Key propierties to take into account into an embedded system are:

- Dedicated functionality
- Limited resources.
- Performance and efficiency.
- Real-time constrains.
- Interaction with the enviroment.
- Dependability:
     - Availability.
     - Reliability.
     - Safety.
     - Integrity.
     - Mantenebility.

**SAFETY**: Is the propierty of a system that evaluates the risk of the ocurrence of an accident or material losses.

**FUNCTIONAL SAFETY** Is the safety of a system that correspond to the correct actions acording to the system inputs, it also includes
detection of potential dangerous states, and activation of protective, corrective or mitigation measures.

Functional safety implies active measures, as an example is the airbag systems in vehicles, when a crash is detected, a safety system
is triggered. On the other hand, a helmet that protects the driver, is a passive system; passive systems are not functional safety.

The leading standard for functional safety is the IEC 61508.

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

**ERROR**: An error is a systematic fault: An error is a desing flaw or desviation from an intended or designed state.

>__A word about SW context__
> A human being can make an error (mistake), wich produces a defect (fault, bug) in the program, code, or in a document. If a defect in the
> code is executed, the system may fail to do what it must do (or do something it shouldn't) causing a failure. 

**RELIABILITY**: Is the probability that a piece of equipment or component will perform correctly its intended goal, inside the defined time, and under the correct enviroment. So Reliability is defined by the probability that for an given time interval [0,t], the systems performs ok, during all the time interval up to time t, starting working at time t=0. 

This has significative importance to systems, that perform a critical action, and cannot be in any case replaced as could be an aircraft computer. And also in systems that must work without manteinance, or cannot be easily or ever replaced, as for example: inner reactor nuclear systems, systems controlling/monitoring a blast furnace, or satellite systems, .... 

Reliability is often quantified with the merit figure of **MTBF** (Mean Time Between Failures) 

**AVAILABILITY**: Is the probability that the system will be working/performing as expected at any given time. When calculating this parameter, it has to be taken into account, both maintenace times, preventive mantenaice times, and reparation times.

Availabilty is commonly meanfully for evaluating those systems, where its functions can be delayed or denied for a short time period, without serius consequences.

Availability is often quantified by the merit figure of: 1-MTTR / MTTF 

where:

**MTTR** stands for Mean Time To Repair the system

and 

**MTTF** stands for Mean Time To Failure


**DEPENDABILITY**: Is the truthworthiness of a system so there is a justified confidence in the tasks it must perform.

Dependability is a concept that usually refers to a figure of merit that is based on:

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

 Suppouse, you have a system, in which two tasks are working togeder, one of them, task_1 - senses, gadthers and updates data in real time. task_2: request that data, and do some data processing algorithm. 
 
 In the event, that for whatever reason, maybe some bug, as could be: that there aren't enough memory..., the task_1 stops on working, or performing properly, so it may report the unfriendly: segmentation fault... at that point, the task_2, should be able to detect the problem, - there are some methods to do this - and it should try to fix the system, for example, re-launching, the task_1, or reseting/rebooting the whole system in the worst case.
 
References:
https://en.wikipedia.org/wiki/Fault-tolerant_computer_system </br>
https://en.wikipedia.org/wiki/Software_fault_tolerance </br>
https://users.ece.cmu.edu/~koopman/des_s99/sw_fault_tolerance/ </br>


**ROBUST SYSTEMS** Robust systems are those in which the computer system has the ability to cope with errors during execution and cope with erroneous inputs. Usually you test those systems with the technique of *Fault Injection*, other techniques are for example *Fuzzy testing* that involves invalid or unexpected inputs. 
<br>
<br>

## SOME CLARIFICATIONS on the CONCEPTS:

**Safety** is related to freedom from accidents and material damages and looses.

**Safety** is NOT **Reliability**!! Reliability is the correctness of a system performing it's intended duty/function during a consecutive period.

**Safety** is NOT **Security**!! Security is the ability to defence against intended damages and malicious actions.
<br>

## SAFETY RELATED CONCEPTS:

**Accident**: It's the situation in which there is a loss of some kind: death or material damage.

**Risk**: It's the likehood of an accident and its severity. -> R(a) = p(a) * s(a);

**Hazard**: The set of conditions or enviromental variables, that will lead or result in an accident.
<br>

## FAILURES vs ERRORS:

**Failure**: is the non-performance of the system or component, at random. Thus, it can be estimated from a pdf (probability density function). FAILURES ARE EVENTS.

**Error**: is a systematic fault, thus a design flaw. ERRORS ARE STATES.

**Fault**: A fault is either a failure or an error.





















# PROGRAMMING TECHNIQUES:

## Robust programming

Robust programming is a style of programming that focus on handling unexpected terminations and unexpected actions. The code should handle those events gracefully and log or display accurate and unambigous **error mensages**, this will allow to detect and correct
much easily the pernicious event.

### Principles:

#### Paranoia
 The programmer must undestand that its code can produce bug, that make the system fail or work incorrectly. Also that the users are there to break their code. - You know the saying: *--Even paranoids have enemies--*
 
#### User proof
 The programmers assumes that the user at some point will use incorrect, malformed, and bogus inputs. So he has to code error-proof inputs, and emit **error mesages**, that must be: clear, specific, intuitive, unambigous, effective, detailed, explicit and that don't require to look up error codes. The message must be as accurate as possible, to the problem, so it can be detected and corrected with ease.
 
#### Avoid Dangerous implementations

 Users should not gain access to the inners of the system/program - that is: libraries, internal states, internal values, or pointer to data structures ... The interfece with the user should be that, and be probed against loopholes.
 
 Avoid anti-patters, ie: for concurrent systems, take special care with racing conditions...
 
References:
https://en.wikipedia.org/wiki/Robustness_(computer_science)#Robust_programming </br>
http://nob.cs.ucdavis.edu/bishop/secprog/robust.html </br>

#### Coding standards and best practices

Follow recomendations for implementing the system.

- Use coding standards and recomendations:
    - Always define the variable types.
    - Never ever programm an infinite loop.
- Write modular systems.
- Design self-tests (for hardware control).
- Use watchdog's (sw and/or hw implemented).
- Implementation of recovery systems.
- Follow Design and architecture patterns
    - SOLID principles
         - Single responsability principle.
         - Open - Closed principle.
    - HW patterns: ie. pulsed sources induce more EMC problems, ...
- Implement a logging mechanism in the system.
- Test, test, test.

## Defensive programming

Defensive programming is a defensive coding style intended to ensure the continuing function of a program under unforeseen circunstances. This code style is usually used in systems with need high availability, safety and security.

### Techniques:

#### Intelligent code reuse:
Existing code is tested and is knwon to work. Reuse of it may reduce the chance of new bugs. 

 - [ ] TODO: complete this.

References: 
https://en.wikipedia.org/wiki/Defensive_programming </br>

## Inmunity-aware programming

When writing code for an embedded system, inmunity-aware programming, refers to programming techniques which improve tolerance of transient errors in the program counter or in other modules that may lead to a failure. Transient errors usually are cause for single events, as a micro-cut in the power supply or a strong electromagnetic event, transmitted from another source to our device. 

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

## Bisimulation (or Strong Bisimulation)
Bisimulation is a relationship between state transition systems, that associates systems that behaves in the same way in the sense
*that one system simulates the other and vice versa*.

Bisimulation is important because if two systems comply with bisimulation, then it is safe to consider them as equivalent. Bisimulation
is always the safe choice.

Formal definition:
Given a LTS (S,Λ,→) a bisimulation relation is a binary relation **R**, over **S**, i.e.( **R ⊆ to S x S**) such both **R** and its inverse **R^-1** are simulations.

Equivalently **R** is a bisimulation if for every pair of elements **p**,**q** in the space of states **S**, with (p,q) in **R**, ∀ α in Λ:

  for all **p'** in **S**: p  → (α) → p'
  implies that there is a **q'** in **S**, that: q  → (α) → q 
  and (p',q') ∈ **R**

  and, simetrically:
  
  for all **q'** in **S**:  q  → (α) → q'
  implies that there is a **p'** in **S**, that: p  → (α) → p'
  and (p',q')  ∈ **R**

So given two states **p** and **q** that belong to the state space **S**, **p** is _**bisimilar**_ to **q**, and is writen as: **p ~ q**, if there is a bisimulation **R** such that **(p,q)** are in **R**.

¡if two process are bisimulation equivalents, they are equivalents from any perspective you can think of!

![bisimulation.png](./image/bisimulation.png)


**THEOREM:**
Every trasition system has a _**unique**_ minimal transition system that is bisimulation equivalent to it.


## Trace of a system:
Traces, are the sequence of actions that can be executed in that system.

## Trace equivalence
Two Transitions systems are trace equivalent if they have the same _**set**_ of traces.

### Properties of trace equivalences:

watch out! because the trace equivalence, don't conserve deadlocks.

If two states are bisimilar, then they are also trace equivalent

For deterministic trasnsition systems bisimulation and trace equivalence coincide.

### Branching bisimulation: 

-> is a bisimulation that takes hidden actions into account.

Branching bisimulation eliminates divergencies.

- All states in an invisible action (tau) loop, will be removed.


## Divergence preserving branching bisimulation.

In a state that is followed by invisible actions, its equivalent state in its bisimulated system, also will be followed by invisible actions.

## Weak trace equivalence:

Two systems are weak trace equivalens, if they have the same set of traces, where invisible actions (tau) are ommited.

- It's advantage is that this equivalence remove all the invisible actions, making an equivalent system smaller, thus easier to work with.

- It remove all the invisible actions of the behavior of the system.

- A disadvantage is that the branching structure of the system is not conserved.

Reference: https://en.wikipedia.org/wiki/Bisimulation

Reference: http://theory.stanford.edu/~rvg/abstracts.html#45

Reference: http://theory.stanford.edu/~rvg/abstracts.html

Ref: http://ai.cs.unibas.ch/papers/theses/scherrer-bachelor-12.pdf

Ref: https://www.cs.ox.ac.uk/files/6715/ICFEM%202014%20Version%2010.pdf

Ref: http://theory.stanford.edu/~rvg/




**TODO**: Check and elavorate: https://en.wikipedia.org/wiki/Calculus_of_communicating_systems


Check, the methods, for testing: ccpcheck, vera ++, RATS, Jeckins, SonarQube, 
Test Unitarios: XUnit, CppUTest
Other sys: lcov, valgrind, ltrace, strace....

Refernece to check: Dependability through Assuredness™ (O-DA) Framework: https://www2.opengroup.org/ogsys/catalog/C13F



# TESTING METHODOLOGY AND PROCESS

 The most important pearl of wisdom to take into account, is that is not the development process the one that assures quality of
 the system, is the testing process.
 
  Testing of a system is the action of evaluating it to attain its true capabilities and to check its conformance with the design requisites, and to find bug/erroes or other defect. Summing up the quality of the Product. 
  
  >> Testing of a system is of main importance, due it asures the quality of the system.
  
  One topic that always pops up is: how much testing is needed?
  
  The number of test you can possibli plan for most of the systems tends to infinity. The stop point is that in which, the asurance of the quality of the procudt, has been reached and probed by the tests. Of course this level is different depending on the nature of the projet. Design of a video streamming home-appliance, usually doesn't need as much testing as the design of an emergency train brake system. 
 
 ## TESTING METHODS
 
  Specificaions/requirements testing, checks the desing is compliant with the stackholders idea (expected work). This often is done by means of 'test cases', where the 'tester' evaluates the action of the system for certain inputs, and compares the system outputs with respect the expected outputs.
  
  The specifications include all the 'functional' aspects of the system, but they can also include non-functional requiremets, as performance, usability, scalability ...
  
  Specification testing is necesry to asure proper funtion. But for complex or high-risk projects, it may be not nearly enoght. For example it doesnt cover a 'foul' user. 
  

### Dinamic vs Static testing

When a test case of a system involves the actual run of the system, this is known as 'dinamic testing', on the other hand when it doens't inolve the run of the sysem is known as 'static testing'.

 Dinamic testing usually makes us of stubs/driviers, execution from a debugger enviroment.And is also common to automate it.
 
 Static testing, is referred to those evaluations that don't need the system to be running. Those are techniques as: code review, revision, walkthoruhgs, inspection, and alsouse of programs that automatically ckeck the code propierties (as could be: detection of 'dead code' (code that will never execute)unused varialbles, mising pointers, out of bound arrays, wrong types varaible asignations, lost of precission in mathematical operations, ...) 
 
## The seven principles of testing

over time, testing has learned important leasons, these concepts are the followings:

**1- Testing shows presence of defects** <br>
Testing, shows defects, but it cannot proof that there are not defects. Testing
increases the asurance over the system, because when a bug is found and corrected, the chance that would be remaining 
bugs is less likely. So even in the case, that no defects can be found any further, that there is no proof that there aren't any.

**2- Exhaustive testing is impossible** <br>
test of all the possible combinations of a system is impossible. So to determine how much testing should be dont, an 
estimation of the risks, risk analysys and priorities, must be done. The testing will stop, when there is certainty that the systems complies.

**3- Early testing** <br>
Testing activities should be started as soon as possible in the system development live.

**4- Defect clustering** <br>
As following the pareto law, in many cases some components have most of the defect density. Testing should be focus to them,
to maximice the effectiveness of the testing efforts.

**5- Pesticide paradox** <br>
Running the same test again and again, makes that eventually the same set of test don't find any defect at all. Having into account that some schools of thought consider a succesfull test, that one that find defects ... it's a bit, like that set of test loses "effect". 
The set of test, needs to be reviewed and updated, to exercice different parts of the system, and in different ways.

**6- Testing is context dependant** <br>
Testing depends on the context. A safe-critical system test is not at all the same that the test of a video streamming appliance.

**7- Absence of errors falacy** <br>
Even if no defects are found, it doesn't proof that the system is usable, or complies with the end-user expectations.


## Development of the Test Plan

The first point in a system development, at the testing context, is to define the **Testing Plan** for that, several key points have to
be defined:

 - Test planning and control
 - Test analysis and design
 - Test implementation and execution
 - Evaluating exit criteria and reporting
 - Test clousure and activities.
 
 
### Test planning and control 

 **Test planning** is the document that aims to define the objectives of the testing, and the needed action to achieve those objectives.
 
 **Test control**: Testing activities should be monitored through the project. It is the comparation between the state of the project, against the expected planned result. It also covers the report of the testing status, including desviations from the plan. Also include proposals to the actions that need to be done, in order to meet again the goals, and expectations of the project. 
 
So **test control** is related to guide the corrective actions taken as a result of informantion or metrics. These actions can be applied to any part of the system.

Examples of test control actions are:

- Take decisions based on the information from test monitoring:
- Repriorinzing tests, and identify risks.
- Change of the test schedule, based on the abailability of equipmento or facilities.
- Setting criterion about re-testing issues, for including those modifications into the system build.

**Test design and analysis**
At this step, the real tests are designed,(actions, contexts, expected results)  and defined the objetives they want to ckeck.

This include go through the following points:

- Review requirements, software integrity level (that is compliance with some system parameters previously defined as software complexity, risk assesment, safety and security level, performance, reliability, cost ... Usualy these points are defined by the stakeholders):
- Evaluation the testability of the test basis and test objects.
- Identify and priority test conditions based on the overal project.
- Design and prioritaze high level tests.
- Identify necessary test data and resources. 
- Design the test enviroment, platform, and required infraestructures and materials.
- Create a method to a bidirectional traceability between test basis and test cases.

 
## Test implementation and execution

The designed test procedures are implemented, and a certain execution order has to be stablish, in order to run the set of test (usually according to priority). When the test enviroment is set up, the test cases are run.

The objetive and aim of the text execution is:

- Implement and prioritaze the test cases.
- develop test procedures, create test data, optionally preparing test hardeness and writting automating test scripts.
- creation of test suits, for efficient test execution.
- verification that the test enviroment has been set up properly.
- verification and update if needed, of bi-directional trazability between the test cases and requeriments.
- Execution of the test, according to the test procedure. Log of the test execution relevant information, as identification of the
different elements involved, as software version, prototype, tools, device under test, execution time, software and hardware version.
- Comparation with the expected results.
- Report discrepancies, or outliers as incidents, and analyse them in order to identify a possible root-cause. (defect in the code implementation, data out of bounds, damaged equipment, wrong procedure, ...)
- Repeat test that failed out of the expected results to confirm the issue, and gather new information details if possible. check if the 
efect is always reproducible, or it is sporadic....
- Record and logging of the tests results, significant test conditions and enviroments.
- If new issues are found, _regression testing_ (test all the system to asure that new code or components haven't affected the rest of the developed system) may be advisable, to check that new issues has not appear in other stable parts of the systems.

### Test results (evaluation and exit criteria).

- The data obtained from the test should be compared with the expected results.
- Report of the failed test!!!
- Modification over the test, or expected results should be planned.
- Reports should be done for the stackholders.

### Test plan clousure activities.
 
At the end of the project, or at significant project milestones, certain activites are observed.
 
 - Report of the system acceptance.
 - review and learned lessons.
 - project metrics, and evaluation of the testware.
 





