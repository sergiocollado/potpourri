# NOTES ON EMBEDDED SYSTEMS SAFETY
## CODE WARRIORS, HW TANKS, TEST MONKS, AND MANAGER ONIs
### Unselected readings
#### Read at your own risk

<hr>
<hr>

 # BASIC CONCEPTS and DEFINITIONS:
 
**EMBEDDED SYSTEM**: An embedded system, is a system, that combines software and hardware designs. It is common, that they have some kind of HMI (human machine interface) or UI (User Interface) as displays, keyboards, et cetera. Also is quite common, at least use of one network communication protocol. Embedded systems have fixed capabilities but are programmable, and they are designed for a specific function or functions. 

Examples are: industrial equipments and control systems, production lines, machine's controllers,safety mechanism in heavy machinery, agricultural, automotive, train, railway, aeronautical, avionic, space and comunication systems, medical systems, household apliances, entertaiment devices, toys, vending machines, measurement/sensor and monitoring systems, security sytems, identity checks, access controls, robotics, logistics ...

Most of the times, embedded systems are **reactive**, that means that they wait for an input, or they keep on measure some propierty or signal, and when they have it, they perform some computation, or check a defined threashold or condition; and then it generates a defined output: as could be: activation or triggering of an acutator, as: a motor, a brake, or an alarm, triggers another system, send a message ... **Than means they can be modelled as an Automata**. 

Key propierties to take into account for an embedded system are:

- Dedicated functionality
- Limited resources (the system cannot be easily expanded).
- Interaction with the enviroment.
- Performance and efficiency. (definition of the maximum work load capabilities)
- Real-time constrains (definition of the maximum reaction/response/actuation time, it also includes start-up times).
- Dependability:E
     - Availability.
     - Reliability.
     - Safety.
     - Integrity.
     - Mantenebility.

**DEDICATED FUNCTIONALITY** An embedded system usually must perform a very specific function, or maybe a set of specific functions, but its design is so, that its performance is maximized for given system components, usually that implies, that it is unable to be a generalistic function system, as opposed to PC and laptops, that may do quite a big variety of functions, at the cost of being over designed. 

**LIMITED RESOURCES** An embedded system is designed to achive only the defined functions and requirements; the system only needs a certain number of resources and no more. That means in most cases, that the harware cannot be upgraded or expanded. As such, it's is also very rare that an embedded system can be designed for increase its hardware dependant capabilities, functions, or it is possible to expand its systems parts or modules. On the other hand, most of the embedded systems can be re-programmed, so its software can be changed and upgraded, that means thatt it is possible to improve the system, or adapt it to new requirements or new cases, as far as it is possible with the designed hardware.

**SAFETY**: Is the propierty of a system that evaluates, weight and analyze the risk of the ocurrence of an accident (injury or death of people), material, propierty, equipment or resources damage or losses, also enviromental degradation.

**FUNCTIONAL SAFETY** Is propierty of a systems that evaluates the safety of a system that correspond the correct actions according to the system inputs, this also includes detection of potential dangerous states or actions, and activation of protecttion, corrective or mitigation measures.

Functional safety implies _**active measures**_, that _**develop and implement mechanism and risk-reduction measurements**_, as an example: the airbag systems in automotive vehicles, when a crash is detected, the safety system is triggered. On the other hand, a helmet that protects the driver, is a passive system; passive systems do not comply with the functional safety concept.

The leading standard for functional safety is the IEC 61508.

The funtional safety level of a system is evaluated with a figure of merit, known as **SIL** (Safety Integrity Level):

**SAFETY FUNCTION**: function, method or mechanism that reduces the risk of a system.

**FAIL-SAFE DESIGN** Is an engineering design practice that makes a system to respond the minimun damage in the event of a failure.

**SINGLE-FAULT CONDITION SAFETY**: Even in the event that a fault happens in the system, the system must remain safe.

**ACCIDENT**: The event of causing/receiving damage of any kind (either directly or indirectly): equipment damage, property damage, or damage to the enviroment, and human injuries or even deaths.

**RISK**: Is the combination of the likehood on an accident and its severity. That is to say, the chances of an accident to happen,  evaluated according of the potenctial damage that risk can do. As a mathematical expression it is usually evaluated with the following formula:

Risk = probability(accident) * severity(accident)

ISO 31000 - standards for risk management:
 - ISO 31000 - Principles and guide lines for implementation.
 - ISO 31010 - Risk management, and risk assesment techniques. 
 - ISO Guide 73 - Vocabulary
 
**RISK ASSESMENT**: Is the analisys to identify and determine the possible situations or conditions that may end in an accident, thus there is a thread(hazard). If the risk assesment is quantitative, it needs two factors: the Risk(R) = magnitude of the potencial lost, the severity (s) and the probability (p) that lost happens.

R(accident_i) = P(accident_i) · Severity(accident_i)

 **Risk matrix**: In practice the risk formula is difficult to apply, due the probablities of given accident are difficult to pin-point with an exact number, so it is common to apply categories to the probability and severity, so instead of numbers they are classified in ranges, for example is common to evaluate: Very low, low, medium, high, very high. With this classification then it is possible to make what is refered to, as a risk matrix, or risk table. 

**Tolerable Risk**: acceptable risk in certain given enviroment for a society.

**RESIDUAL RISK**: risk in a system after protective measures have been applied.

**HAZARD**: Set of combinations of conditions or requisites or enviroments or events that lead to an accident

**ERROR/MISTAKE**: A human being can make an error(mistake), with results in a **defect** in the system (fault, bug) in the program or code, or in a document. The defect in the system, might never be noticed, or can result in the case that the system might fail its expected function (or do something it shouldn't) causing a failure. Defects in software, systems or documents can result in failures, but no all defects do.

<br>
**(human) ERROR -> (code) DEFECT -> (system) FAILURE**
<br>

**FAILURE**: A failure is the misperformance or lack of ability of a component to comply with its designed function, during certain
time, or under specified enviromental system conditions. 

**FAILURE MODE**: A failure mode is one of the possible potentinal ways of a system to fail. Usually in a system there are several ways in which it can fail, each one is knwon as a failure mode. Usually different failures mode also are expected to have different probability distributions.

**FAULT**: An error is a systematic fault: An error is a desing flaw or desviation from an intended or designed state.

>__A word about SW context__
> A human being can make an error (mistake), wich produces a defect (fault,bug) in the program, code, or in a document. If a defect in the code is executed, the system may fail to do what it must do (or do something it shouldn't) causing a failure. 

**SAFETY INTEGRITY** probability in a safety-system that the safety functions perform as intended in a defined enviroment under all defined conditions for a defined amount of time.

**SAFETY INTEGRITY LEVEL** Level that qualifies the safety requirements and safety functions of a system. It is ranked on 4 levels being SIL4 the safest, and SIL1 the lowest safe.

**SOFTWARE SAFETY INTEGRITY**: probability or measurment of the likehood in a electronic programmable system that its safety funtions  perform as intended in a defined enviroment under all defined conditions for a defined amount of time.

**HARDWARE SAFETY INTEGRITY**: part of the system safety that depends in the random hardware failures that be hazarous.

**RELIABILITY**: Is the probability that a piece of equipment or component will perform correctly its intended goal, inside the defined time, and under the correct enviroment. So Reliability is defined by the probability that for an given time interval [0,t], the systems performs ok, during all the time interval up to time t, starting working at time t=0. 

This has significative importance to systems, that perform a critical functions, or cannot be in any case replaced during service, as could be an aircraft computer. Also in systems that must work without manteinance, or cannot be easily or ever replaced, as for example: inner reactor nuclear systems, systems controlling/monitoring a blast furnace, or aerospace or satellite systems, .... 

Reliability is often quantified with the merit figure of **MTBF** (Mean Time Between Failures) 

**AVAILABILITY**: Is the probability that the system will be working/performing as expected at any given time. When calculating this parameter, it has to be taken into account: maintenace times, preventive mantenaice times and estimated time for repair (**ETR**).

Availability is commonly meanfully for those systems, where its functions can be delayed or denied for a short time period, without serius consequences. Ensuring timely and reliable access to and use of information is an essential propierty of real time critical systems.

An example of a high availability (HA) system is the electric power distribution grid (anyway hospitals, airports ... have emergency power generation systems- as fail-safe measurements because the need to be a high avaliability facilites... just in case you were worried). The GPS system, for example, is an outstandig system, as it was designed as a **zero-down-time** system.

Availability is often quantified by the merit figure of: 1-MTTR / MTTF 

where:

**MTTR** stands for Mean Time To Repair the system

and 

**MTTF** stands for Mean Time To Failure

and

**MTBM** stands for Mean Time Between Maintenace - this also impacts the availability of the system.

Is also common to express availability as percentage between uptime and downtime of the system. For example a system availability 
referred as a 99% (two nines) means that over a year its downtime is 3.65 days. A system reliability with 99.999% is refered as five nines. 

**SECURITY**: Is the propierty of a system that evaluates its ability to deal with malicious actions or attacks.

Take into account, that there is a significative difference between the concepts of safety and security, both terms account protection against a damage, but security implies a malicious or intended action to do a damage, while safety relates to an unintended situation.

**DEPENDABILITY**: Is the truthworthiness of a system so there is a justified confidence in the tasks it must perform.

Dependability is a concept that usually refers to a figure of merit that is based on the evaluation of the following properties:

- Reliability
- Availability
- Maintanability
- Safety
- Security 

**CRITICAL SYSTEM** Is a system that must be highly reliable, and keep this reliability even when it is developed, and evolves. 
Usually, these systems are classified into the following groups:

 - **safety critical** : the misperformance of the system would mean, personal damage or loss, or material/propierty/resources or enviromental damages Examples: Energy systes (as nuclear plants), control in transportations systems, chemical reactors, medical devices (as a pacemaker or a heart-lung assistance systems) ...
 - **mission critical**: designed to avoid total misfunction of the designed functionality or objective. example: navigation systems.
 - **bussines critical**: designed to avoid a missfunctions that would result or imply huge economic/bussines impact or material losses, usually as a result of a service interruption. Example: bank, accounting and payment systems, stock-trading systems.
 - **security critical**: designed to protect data or sensible information. example: medical databases, customers data ...

**Critical systems must always identify and pin-point the worst case escenario, and also data throuputs and latencies!!**

Other related concepts are also:

**Integrity**: the property that represents how reliable and accurate data. To prevent fraud and other more harmful attacks measures must be taken to ensure that data is accurate and free from manipulation.

**Confidentiality** the data in a system must be confidential.

**Accountability**: Accountability is the idea that users of a system should be responsible for the actions they perform. This means that user interactions with sensitive systems should be logged and associated with a specific user. These logs should be difficult to forge, and have strong integrity protection.

**Real-time system**: a system is said to be real time, when it can guarantee tha tasks to be done, are done at the expected time time, or when the tasks are scheduled and expected to be done. also real-time systems are expected to have a predictable behavior, and very reliable way.


Referencess:

https://en.wikipedia.org/wiki/Critical_system

https://en.wikipedia.org/wiki/Reliability_engineering

https://en.wikipedia.org/wiki/Redundancy_(engineering)

https://en.wikipedia.org/wiki/Factor_of_safety

https://en.wikipedia.org/wiki/Formal_methods

https://en.wikipedia.org/wiki/Z_notation

https://en.wikipedia.org/wiki/Verification_and_validation

http://czt.sourceforge.net/

https://en.wikipedia.org/wiki/Design_by_contract

https://en.wikipedia.org/wiki/Defensive_design

https://en.wikipedia.org/wiki/Fail-safe

https://en.wikipedia.org/wiki/Idiot-proof

https://en.wikipedia.org/wiki/Inherent_safety

https://en.wikipedia.org/wiki/Poka-yoke

https://en.wikipedia.org/wiki/Usability_testing

https://en.wikipedia.org/wiki/Defensive_programming

https://en.wikipedia.org/wiki/Offensive_programming

https://ulir.ul.ie/bitstream/handle/10344/2085/2010_Hinchey,M.pdf?sequence=2

https://en.wikipedia.org/wiki/Formal_verification

https://en.wikipedia.org/wiki/List_of_model_checking_tools

https://mcc.lip6.fr/

https://en.wikipedia.org/wiki/Test-driven_development

https://en.wikipedia.org/wiki/Extreme_programming

https://en.wikipedia.org/wiki/Pair_programming

https://en.wikipedia.org/wiki/Product_lifecycle

https://www.crcpress.com/Design-and-Safety-Assessment-of-Critical-Systems/Bozzano-Villafiorita/p/book/9781439803318

https://www.crcpress.com/Practical-UML-Statecharts-in-CC-Event-Driven-Programming-for-Embedded/Samek/p/book/9780750687065?source=igodigital

https://www.crcpress.com/Practical-UML-Statecharts-in-CC-Event-Driven-Programming-for-Embedded/Samek/p/book/9780750687065?source=igodigital

https://www.micrium.com/books/ucosii/

http://www.omg.org/news/meetings/workshops/RT_2002_Workshop_Presentations/01-3_Douglass_Safety_Critical_Systems_Design.pdf

https://en.wikipedia.org/wiki/Capability_Maturity_Model

http://pubs.opengroup.org/architecture/togaf8-doc/arch/chap27.html

https://en.wikipedia.org/wiki/Testing_Maturity_Model

https://en.wikipedia.org/wiki/List_of_software_reliability_models

http://www.softrel.com/truth.html

https://www.techstreet.com/ieee/standards/ieee-p1633?product_id=1914936

https://en.wikipedia.org/wiki/Quality_assurance

https://www.crcpress.com/Practical-UML-Statecharts-in-CC-Event-Driven-Programming-for-Embedded/Samek/p/book/9780750687065?source=igodigital

https://www.crcpress.com/Math-Toolkit-for-Real-Time-Programming/Crenshaw/p/book/9781929629091?source=igodigital

https://www.crcpress.com/Handbook-of-Real-Time-and-Embedded-Systems/Lee-Leung-Son/p/book/9781584886785

https://www.crcpress.com/Handbook-of-Scheduling-Algorithms-Models-and-Performance-Analysis/Leung/p/book/9781584883975

https://www.crcpress.com/Designing-Complex-Systems-Foundations-of-Design-in-the-Functional-Domain/Aslaksen/p/book/9781420087536

https://www.crcpress.com/The-Practical-Handbook-of-Genetic-Algorithms-Applications-Second-Edition/Chambers/p/book/9781584882404

https://www.crcpress.com/Differential-Equations-with-Applications-and-Historical-Notes-Third-Edition/Simmons/p/book/9781498702591?source=igodigital

https://www.crcpress.com/Introduction-to-High-Performance-Computing-for-Scientists-and-Engineers/Hager-Wellein/p/book/9781439811924?source=igodigital

https://www.crcpress.com/Embedded-Systems-Building-Blocks-Complete-and-Ready-to-Use-Modules-in-C/Labrosse/p/book/9780879306045?source=igodigital

https://www.micrium.com/books/ucosii/

http://www.sohar.com/proj_pub/download/y2ktest.pdf

https://www.drexelbrook.com/support/faq/what-are-safety-systems


**SAFE-CRITICAL SYSTEM** Is a system that under misfunction, can result in an injury or loss of people's life, a damage to material or propierty, or an enviroment harm.

 Safety-critical systems design involves: software, hardware and human factors.
 
 According to its reliability regimes, there are the following concepts:
 
  - **Fail-safe systems**: In case of a misfunction, they addopt a safety state. So they become safe even when they cannot perform its function. Medical devices, usually are found in this category, for example a heart-pump: when it cannot work, it warns the medical personal, as the safety interval, is long enough, the live of the patient is not in thread.
 - **Fail-operational systems**: They continue to operate even when a part of the system fail. For example, when systems use rebundant subsystems, in case the main subsystem fails, the redundat subsystem, may take-over the control, and keep the overall system working. Examples are: elevators, automotive electronic throttle control, braking systems, circuit-breakers  ...
 - **Fail-soft systems**: they continue operation with a reduced efficiency even in the presence of a failure.
 - **Fail-Passive systems**: As a helmet or a shield. they achieve safety throught passive elements. (TODO: expand)
 - **Fault-tolerant sytems**: they continue to operate even when faults are present in the system. 
 
 These concepts are not exclusive. A given system, can be fail-safe, and also fail-operational. An example of this, are aircraft vehicles: they usually have three on-board control computers, in case one of the control computers fails, it is fails-safe, because it keeps yet other two control computers that keep all the functunality, but it also is fail-operational, because it retains all the system functionality.
 
 **SINGLE POINT of FAILURE** In a system, a given element of that system, is known as a *Single Point of Failure* in the case, that if that elements fails, that will prevent the whole system from working. Of course this element is considered as a critical component.
 
 Reference: https://en.wikipedia.org/wiki/Safety-critical_system
 
 TODO: SOTIF - Safety of the Intended Functionality -- ADD INFO
 
 **Safety Instrumented function** the task that needs to achieve a safe state for the given equipment, EUC (Equipment under control), in regards with a hazarous event.
 
 **Safety Integrity** Is the probability that a safety instrumented function (SIF) performs satisfactorily the required safety functions under all the stated conditions within a stated period of time.
 
 So, this means, the probability the safety function will work as expected when it is needed!!
 
 **Safety Integrity Level** it is a discrete level (one out of a possible four) for specifying the safety integrity requirements of the safety functions to be allocated to the E/E/PE safety-related systems
 
 So, this means, safety Integrity level is a qualification measure of the performance required from a safety instrumented system to maintain or achieve the required safety state

There are two basic elements associated with this measure:

**Hardware safety integrity**: which is typically based upon random hardware failures can normally be estimated to a reasonable level of accuracy via probability of failure on demand (PFD).

**Systematic safety integrity**: systematic integrity tends to be harder to quantify. This is due to the diversity of causes of failures; systematic failures may be introduced during the specification, design, implementation, operational and modification phase and may affect hardware as well as software

 
 https://blogs.dnvgl.com/software/2017/05/what-is-safety-integrity-level-sil/
 https://www.drexelbrook.com/support/faq/what-are-safety-systems
 https://www.drexelbrook.com/learningzone/articles/what-is-sil-certification

**FAULT TOLERANT SYSTEM**: Is a system that performs correctly, although might have some inner faults in it. Usually this is achieved by means of repeated operations (repetition in time), redundant systems (repetition in components), and/or monitoring the system and the system data.

RECOVERING FROM ERRORS:
For recovering from errors there are two aproaches:

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

 Suppose, you have a system, in which two tasks are working together, one of them, task_1 - senses, gathers and updates data in real time. task_2: request that data, and do some data processing algorithm. 
 
 In the event, that for whatever reason, maybe some bug, as could be: that there aren't enough memory..., the task_1 stops on working, or performing properly, so it may report the unfriendly: segmentation fault... at that point, the task_2, should be able to detect the problem, - there are some methods to do this - and it should try to fix the system, for example, re-launching, the task_1, or reseting/rebooting the whole system in the worst case.
 
References:
https://en.wikipedia.org/wiki/Fault-tolerant_computer_system </br>
https://en.wikipedia.org/wiki/Software_fault_tolerance </br>
https://users.ece.cmu.edu/~koopman/des_s99/sw_fault_tolerance/ </br>

https://www.mtl-inst.com/images/uploads/datasheets/App_Notes/AN9025.pdf

**ROBUST SYSTEMS** Robust systems are those, in which the system has the ability to cope with errors during execution and cope with erroneous inputs and stressfull enviroments. Usually you test those systems with the technique of *Fault Injection*, other techniques are for example *Fuzzy testing* that involves invalid or unexpected inputs. 
<br>
<br>

## CONCEPTS CLARIFICATIONS:

**Safety** is build-in in the system as first step, when it is designed... a system that aims to achieve safety through building outer layers, is not a good design.

**Safety** involves the **whole lifecycle of the system**: not only maintenace must be observed as defined, or redefined in case or need. Methods to evaluate, record, and log normal work of the system, and of course failures of the system must be present for study and evaluation. An in event of unsafety is detected even recalls must be done. 

**Safety** is the concept related to freedom from accidents and material/propierties/equipment damage and looses from the given system.

**Safety** is NOT **Reliability**!! Reliability is the correctness of a system performing it's intended duty/function during a consecutive period.

**Safety** is NOT **Security**!! Security is the ability to defence against intended damages and malicious actions.

**Safety** and **Availability** are DO NOT imply each other: the safest airplane, is that one never takes off... A system that is working at a given moment, doesn't imply it is safe. The opposite case, the lack of availability, also doesn't need to be true: an airbag for an automotive system, can be very safe, but once it is triggered, it is not available anymore; the triggering of the airbag, can even result on the system fallback, to block the car, due it is not safe; that is: entering a safe operation mode status, after an unexpected event that compromises the system safety. 

**working** is NOT the same as **safe**

A **Non-secure** system is also a **Non-safety** system, as it is susceptible of malicious intends and actions.

**Safety** and **Reliability** are not the same, although in coloquial languaje many times are thought equivalent, these concepts are not equivalent. Safety relates that an event X never happens, or its probability is very low. Reliability relates that an event Y always happens, or is intedend to happen with a high probability.

## SAFETY RELATED CONCEPTS:

**Accident**: It's the situation in which there is a loss of some kind: death or material damage.

**Hazard**: The set of conditions or enviromental variables, that will lead or result in an accident. injury or loss (people, material, financial or enviromental

**Hazard log** Is the document that lists the potential hazards for a system. Also records experience for previous similar or significant systems, previous experiences, and lessson learned from previous projects, even new data or knowledge to take into account.
the 'Hazard log' is a life document: initialy the hazards are defined by means of analisys, usually by the method HAZOP (Hazard and Operability study) or similar: FMEA, FMECA, HAZOP, ETA, FTA.... Later in the lifecycle, also records from field experience and system evaluation must be added to the document.

reference: https://en.wikipedia.org/wiki/Hazard_and_operability_study

**Risk**: It's the likehood or probability of an accident and its severity. In other words: is the figure of merit that provides a meaningful value, that allows the comparation of the risk on different cases. Its mathematical expressionn is:

R(a) = p(a) * s(a);

- R(a) is the risk of an accident 'a'
- p(a) is the probability an accident 'a' happen.
- s(a) is the severity of this accident. This is a factor that evaluates the overall damage, harm or loss in case on an accident 'a'. Usually the s(x) factor is defined by legal, customer or stackhorlders specifications. 

In practice this formula is difficult to apply, as the probablities and damage evaluation are dificult to pin-point with an exact number, so it is common to apply categories to the probability and severity, so instead of numbers they are classified in ranges, classifing the likelihood of an event, for example: Very low, low, medium, high, very high. With this classification then it is possible to make what is refered to, as a risk matrix, or risk table. 

## FAILURES vs ERRORS:

**Fault**: A fault is either a failure or an error.

**Failure**: is the non-performance of the system or component, AT RANDOM. Thus, it can be estimated from a pdf (probability density function). FAILURES ARE EVENTS.

**Error**: is a systematic fault, thus a design flaw, thus repetible. ERRORS ARE STATES.

# OTHER CONCEPTS:

**DEBUGING**: locate, pin-point the root-cause and correct a defect.

**TESTING**: exertion or exploration of the system to identify defects, wrong or unexpected behaviors or weak points in the systme.

**CERTIFICATION**: the design of a system following the best engineering principles is what must be done, Certification of that system,
means to be able to show other people that the system complies with the expected performance. Certifying a system is an expensive task
and is best to prepare for it from the start of the systme design, in case it is needed.


# STANDARDS AND NORMATIVES:

The standards, define the rules to observe and techniques and methodologies to use and comply depending in the application, industrie, national rules and stakeholders.


  ## BASIC FOR SAFETY:

Most standards, define a general requirements safety clause that must be complied with. Products must be designed and manufactured so they function in a safetly way without causing any danger or unnaceptable risk, in: 
 - intended use
 - foreesable misuse
 - single fault condition.


IEC 61508 - standard for functional safety in electric and electronic systems

IEC 61508 has several parts:

 - Part 1: General requirements
 - Part 2: Requirements for E/E/E safety related systems
 - Part 3: software requirements
 - Part 4: definitions and abreviations
 - Part 5: Examples for determining safety integrity levels (SILs)
 - Part 7: guidelines of application of parts 2 and 3
 - Part 8: overview of tecniques and measures

EN 60204-1 - Safety on Machinery - electrical equipment of machines. 

IEC 62061 - Safety of machinery – functional safety of electrical, electronic and programmable control systems for machinery

ANSI/ISA S84.01 Safety Instrumented Systems for the Process Industry Sector (Parts 1, 2 and 3)

EN ISO 12100 - Concepts and principles for risk assesment.
 
ISO 31000 - standards for risk management:
 - ISO 31000 - Principles and guide lines for implementation.
 - ISO 31010 - Risk management, and risk assesment techniques. 
 - ISO Guide 73 - Vocabulary

 ## SAFETY STANDARDS:

- IEC 61508 - General standard
- ISO 26262 - Automotive
- ISO 25119 - Agriculture
- ISO 13849 & IEC 62061 - Machinery
- IEC 60601 - Medical
- DO-178 - Aircrafts
- EN 50126 - 50126/8/9 Railway
- IEC 61513 - Nuclear Power
- IEC 50156 - Furnaces 
- IEC 60335 - Household and similar electrical appliances
- IEC 61511 - Industrial Processes
- IEC 62061 & ISO 13849 - Manufacturing industry
- MIL-STD 882 - Combat systems
- IEC 60703 - Consumer products
- EN 60950-1:200 + A2:2013 - Information technology equipment. Safety general Standards.
- ISO 14118 - Safety on Machinery - prevention of unexpected start-up
- IEC 60079 Series Explosive Atmosphere Standards

## Common points of the safety standards

Each application specific safety standard has its own characteristics, but all the safety standards share some key points:

 - Identification of hazards and risks for the system. A SIL (Safety Integrity level) is assigned based on the severity of the risk. A risk that has a great severity is assigned with a higher SIL level.
 
 - The SIL grade implies the effort o engineering effort for working with that risk. According to the SIL level, the higher it is, it will imply more effor, the use of more analisys techniques, and the use of more mitigation actions or functions.

- The safety evaluation is whole life-cycle work, that must be present and evaluated at all the stages of the life-cycle, and that 
requires of analisys, records and feedback of the development, testing and field experience on the system use. This is to obtain a continous feedback on the system that allows to ensure its safety.

## Related standards:

 (EMC) Directive 2014/30/EU   - https://ec.europa.eu/growth/sectors/electrical-engineering/emc-directive_en
 
 Low Voltage Directive (LVD) (2014/35/EU) - https://ec.europa.eu/growth/sectors/electrical-engineering/lvd-directive_en
 
 Radio Equipment Directive (2014/53/EU) - https://ec.europa.eu/growth/sectors/electrical-engineering/red-directive_en

 Standard for Software Test documentation: IEEE STD 829-1998.
 
 Software Quality Product -  ISO 9126
 
 MIL-HDBK-217 "Reliability Prediction of Electronic Equipment"
 
 ISO 9001

## Other stadards to observe

- ISO/IEC 15288: Systems life cycle process.
- ISO/IEC 12207: - IEEE Std 12207 - Systems and software engineering - Software life cycle processes.
Recomendations to define all the tasks required for and mantaining software.
- ISO/IEC/IEE 14764 - Software maintenance
- ISO/IEC/IEE 15026 - Software assurance
- ISO/IEC 9126 -SW quality
- ISO/IEC 20510 - SW quality
- IEC60300-3-1 - Reliability methods
- ISO/IEC/IEE 15289 - Information items (documentation)
- ISO/IEC/IEE 15939 - Measurement
- ISO/IEC/IEE 16085 - Risk management
- ISO/IEC/IEE 16326 - Project management
- ISO/IEC 9126 - overseed by ISO/IEC 25010 is quality product for sw systems.
- ISO/IEC/IEE 24765 - Vocabulary - avaliable freely at: http://www.computer.org/sevocab
- IPC-7351: Generic Requirements for Surface Mount Design and Land Pattern Standard.
- ISO/IEC 15504: Information Technology - Process assesment, also refered as Software Process Improvement and Capability Determination (SPICE)
- Recomendations for the computer software development process and related bussines management fuctions. This standard is derived from the ISO/IEC 12207, and madurity models as CMM (Capability Madurity Model).
- IEEE 829 - software test documentation
- ISO/IEC 27000 - Information security management systems.
- IEC 60812 Analysis techniques for system reliability - FMEA: procedures for failure mode effect and analysis
- IEC 61025 Fault Tree Analysis (FTA)
- IEC 61713:2000
- IEEE Std 1044-1993, Standard Classification of Software Anomalies
- IEEE Std 1012-1998, Standard for Software Validation and Verification Plans.
- IEC 60287 - current capacity in cables.
- ISO 9126 standard for classifying quality requirements. Classify the requirment main categories:functionality, realiability, usability, efficiency, maintainability, and portability
- IEEE Std 830 recomended practices to define software requirment specifications
- IEC 60068 (all parts), Environmental testing
-IEC 60300-3-1:2003, Dependability management – Part 3-1: Application guide – Analysis
        techniques for dependability – Guide on methodology
- IEC 60300-3-5, Dependability management – Part 3-5: Application guide – Reliability test
        conditions and statistical test principles
- IEC 60605-2, Equipment reliability testing – Part 2: Design of test cycles
- IEC 60721 (all parts), Classification of environmental conditions
- IEC 61014:2003, Programmes for reliability growth
- IEC 61164:2004, Reliability growth – Statistical test and estimation methods
- IEC 61124:2012, Reliability testing – Compliance tests for constant failure rate and constant
failure intensity
- IEC 61163-2, Reliability stress screening – Part 2: Electronic components
- IEC 61649:2008, Weibull analysis
- IEC 61709, Electronic components – Reliability – Reference conditions for failure rates and
        stress models for conversion
- IEC 61710, Power law model – Goodness-of-fit tests and estimation methods
- IEC 62303, Radiation protection instrumentation – Equipment for monitoring airborne tritium
- IEC/TR 62380, Reliability data handbook – Universal model for reliability prediction of
         electronics components, PCBs and equipment
- IEC 62429, Reliability growth – Stress testing for early failures in unique complex systems

## Relevant Organizations

SAE- Society Automotive Engineers: https://www.sae.org/
NTSB - National Trasnportation Safety Board: https://www.ntsb.gov/safety/safety-studies/Pages/SafetyStudies.aspx
EASA - European Aviation Safety Agency: https://www.easa.europa.eu/easa-and-you/safety-management
JTSB - Japan Transportation Safety Board: http://www.mlit.go.jp/jtsb/english.html
FAA - Federal Aviation Administration: https://www.faa.gov

Also safety standards as UL, ANSI, CSA and IEC, NRTL, ANSI, UL, IEEE standards. TODO: complete....

## HAZARD ANALYSIS

FMEA, FMECA, HAZOP, ETA, FTA...


### Aircraft systems

AC 20-115C "Airborne Software Assurance" 

RTCA DO-178C, Software Considerations in Airborne Systems and Equipment Certification

RTCA DO-330, Software Tool Qualification Considerations

RTCA DO-331, Model-Based Development and Verification Supplement to DO-178C and DO-278A

RTCA DO-332, Object-Oriented Technology and Related Techniques Supplement to DO-178C and DO-278A

RTCA DO-333, Formal Methods Supplement to DO-178C and DO-278A

http://listofavailabledocs.realviewdigital.com/?i=List%20of%20Available%20Documents-December%202017#folio=40


## relevant literature with software development

Understanding and controlling software costs  --Published in: IEEE Transactions on Software Engineering ( Volume: 14, Issue: 10, Oct 1988 )


Measuring software failure risk: Methodology and an example -- https://www.sciencedirect.com/science/article/pii/0164121294900345

safeware

Software Reliability Handbook -- https://books.google.dk/books?id=K7n52MOlDQsC&pg=PA520&lpg=PA520&dq=boehm+and+papaccio&source=bl&ots=BLsBcBQGpK&sig=Al0R1Vp0NeIdFxjzbiMSnjXHCEQ&hl=en&sa=X&ved=2ahUKEwiqlPP_s-TcAhWLKlAKHRZsB7YQ6AEwCHoECAMQAQ#v=onepage&q=boehm%20and%20papaccio&f=false

Making Software: What Really Works, and Why We Believe It -- https://books.google.dk/books?id=DxuGi5h2-HEC&pg=PA573&lpg=PA573&dq=boehm+and+papaccio&source=bl&ots=0WswskO6lT&sig=XXnHQR66VsnNthS9EYi8IrgJtak&hl=en&sa=X&ved=2ahUKEwiqlPP_s-TcAhWLKlAKHRZsB7YQ6AEwCXoECAEQAQ#v=onepage&q=boehm%20and%20papaccio&f=false

software reliability: is the probability of failure-free software execution for a specified period of time, in a specified enviroment.

ref: https://www.semanticscholar.org/paper/Software-Reliability-Theory-Lyu/873c93180359462543d51dd62f8c2b4a7b8cfe9d



# SYSTEM DEVELOPMENT LIFE CICLE

There are quite a few ways for a system development project; although at least the following steps always should be considered:

 - **Analysis**:This step aims to answer and evaluate the following questions:
 
What's the problem to solve? Has it be done before? what solution has been used previously? Desired requirements and specificationns: What's the function to perform? there are other non-functional features needed in the system (as user interfaces, usability, safety, security, scalability, performance, robustness, expected working life ...)?, what the stackholders and interested parties expectations? What will be system enviroment? Time-line and squedule of the project? Expected problems or issues that may come up? How many people does the project need to achieve the requested specifications, results, timing and goals? Evaluation of the expected project risks? Expected costs? What is the budget? Normative, contract, legal issues and laws to comply with? Do I have the skills, people and resources to do it?  
 
  Parts of the Analysis, include:

   - Concept definitions and concept studies: Evaluating the feasibility of the concept. The acronym TELOS identifies five areas of feasibility - Technical, Economic, Legal, Operational and Scheduling. Initial requirements, hazard, risks, architecture, design, components and also conceiving and characterizing quantitative and qualitative concepts.Budget estimations: How much will it cost: what are going to be the development costs? what are operation costs? (usually development costs and operational costs and inverse proportional). technologie readiness. producibility and operatibility requirement and estimations.
   - Preliminary design: evaluation of the design trade-offs (as develoment vs operational costs, or size vs weitgh, or size vs battery). design draft. 
   - Critical design: identification of critical key points of the desing, operation, production, ...
   - Production design: estimation on how it is going to be produced, proposal of suppliers and contractors, logistics, transportations, cost estimations ...
   - Certifications: what certification or standards are needed? how it is going to be proof that it is safe or reliable? 
   - Operations: How normal operation will be. How much will it cost? Definition of normal operations. List and proposal of Standard Operation Procedures (SOP) that will be needed. 

If there is significant confidence to overcome all those challenges, the the following step is -->  Definition of requirements and specifications of the system. **In a safety system the first step is always to define the hazard and risk requirements;** for this methodologies as FMEA, FMECA, HAZOP, ETA, FTA, STAMP... can be used.
 
 - **Design**: Reasoning, evaluation and design for the most fitting solution to achieve the specification, requirements and goals of the system. Consideration of problems and issues to overcome. Design of the system architecture: the different parts, modules, elements of the system. Comunications and interface between the different parts of the system. 
 
 Usually topics to take into account are:
 - Safety
 - Security
 - Response time
 - Bandwidth: The amount of information processed per time
 - Maintainability
 - Testability
 - Compatibility
 - Mean time between failure
 - Size and weight
 - Power
 - Nonrecurring engineering cost (NRE cost)
 - Unit cost
 - Time-to-prototype
 - Time-to-market
 - Human factors
 
 - **Development**: Implementation of the system, an the different modules it is made of: hardware, software, ... user interface, communication protocols, power supplies, logging system, metrics of the system. Also includes the project documentation, release notes, use instructions, manuals and learning lessons.
 
 - **Testing**: Evaluation of the performance of the systems, so it can be determined if it reaches the expected goals. Validation, verification and test, riks and acceptance reports. 
  
  
NOTE: a word of advice, all the previous will need a quite significant effort of documentation. Please use pictures and diagrams as much as possible, as those usually help into clarifing concepts.

# PROGRAMMING TECHNIQUES:

TODO: Desing for testeability.... write it!

## Robust programming

Robust programming is a style of programming that focus on handling unexpected terminations and unexpected actions. The code should handle those events gracefully and log or display accurate and unambigous **error mensages**, this will allow to detect and correct
much easily the pernicious event.

### Principles:

#### Paranoia
 The programmer must undestand that its code can produce bug, that make the system fail or work incorrectly. Also that the users are there to break their code. - You know the saying: *--Even paranoids have enemies--*
 
#### User-proof (aka fool-proof), foressable misuse.
 A system must behave sensibly even if the user doesn't. Designers assume that the user at some point will use incorrect, malformed, and bogus inputs. So he has to code error-proof inputs, and emit **error mesages**, that must be: clear, specific, intuitive, unambigous, effective, detailed, explicit and that don't require to look up error codes. The message must be as accurate as possible, to the problem, so it can be detected and corrected with ease. Wrong input to the system must be always tested.
 some plausible causes for a user incorrect use are:
  - lack of kwnoledge
  - carelesses or mistakes
  
 
#### Avoid dangerous implementations

 Users should not gain access to the inners of the system/program - that is: Its operating system, libraries, internal states, internal values, or pointer to data structures ... The interfece with the user should be that, and be probed against loopholes.
 
 Avoid anti-patters, ie: for concurrent systems, take special care with racing conditions, priority inversions, death-locks, ... other usual suspects are architectures that relay in heavyly coupled components or monolithic, as oppoused to modular architectures. 
 
References:
https://en.wikipedia.org/wiki/Robustness_(computer_science)#Robust_programming </br>
http://nob.cs.ucdavis.edu/bishop/secprog/robust.html </br>

#### Coding standards and best practices

Follow recomendations for implementing the system.

- Use coding standards and recomendations:
    - meaninfuly comments. the code must have a good 'readability'.
    - work on define good baselines and documentation.
    - Always define the variable inizialization values.
    - Use indentation. it improves readeability
    - Never ever program an infinite loop. (under a worst case design it will block execution)
    - Never ever use magic numbers.
    - Coding standards encorage developers to write a cleaner code.
    - two persons rule: at least two persons must be familiar with the overall design, arquitecture, configuration, software and hardware.
    - input/output records, data and logs.
    - system error log
    - use systems and sw watchdogs, heart-beats, and system memory & resources monitors for detection of faults on the system.
    - checking of system correctness.
    - Positive correct working report: the sistem must report that it is working as expected and correctly.
    - At least one safe state.
    - Unused memory: all the unused memory must be fill with such a patter, that forces the restart of the system if it is readed 
    by error.
    - evaluate the need for back-up systems
    - evaluate the need for fail-safe systems, sub-systems or measures.
    - implement error handling in their own functions (so they done use up cache memory).
    - always handle input invalid values or input excptions.
    - the readability of code is important, so other people can easily understand the code, expressions as a\*b+c/d are a NO NO, the operators precedence is complicated, and parentesis shoud be used to clarify the operation: a\*(b+c)/d
    - Clear and defined SOP (Standard Operation Procedures) - Plus this point is related to compliance with the ISO 9001
- Write modular systems (loose dependancy)
- Implentent and use configuration files for the system (this will provide a flexible configuration for the future).
- Design self checking tests (for hardware control).
- Use watchdog's (sw and/or hw implemented), and/or sw/functions/processes/threads/devices heartbeats.
- Implementation of recovery systems.
- Implement early warning systems in case of degradation.
- the software must indentify itself and its version, as a response of a command, or at reset of the system.
- Follow design and architecture patterns:
    - SOLID principles
         - Single responsability principle. (SRP).
         - Open - Closed principle.
         - Liskov substitution principle.
         - Segregation principle.
    - DRY : Don't Repeat Yourself - don't write the same code blocks over and over again, just once, and call it when needed.
    - White and black lists (for input data parsing).
    - safety and security recomendations and techniques.
    - use lint programs that advice about the coding.
    - HW patterns: ie. pulsed sources induce more EMC problems, shieldings, power supply misperformances, use DRC (design rule checks),  simulate the hardware, run montecarlo simulation analysis on the hardware, choose wisely the memory type (remember Flash, writes in blocks, and the number of writings is lower than for a EEPROM memory). Use poke-yoke connectors.
   - use discharge resistences in parallel to significant big capacitors, for handling safety porpouses... it will discharge the capacitor over the time, so in case someone handles it without care, the capacitor dont discharges on that person.
   - Isolate electric parts.
- Implement a log or trace mechanism in the system.
- Previous a modification of a file, make a back up copy, just in case a sudden power off, or corruption of the data.
- Have a method to identify the software, and version of the system (build system, build management)
- Verify integrity and Hash or crc's or alike for configuration files, parameters files, an such....
- For robustness: check input parameters into functions, and repor functions sucess or failure. 
- Test functions (unit testing) with wrong, and bad data- a program should behave sensibly even if the user don't.
- Test, test, test. (it's is not the developers skill what asures a good systems (although it helps, of course!), is the test of system the action that increases the asurance on the systems capabilities, quality and confidence). (test documentation must comply wit the ieee 829 standard)
- CSP: Concurrent Sequence Programming (techniques)
- poka-yoke (one type of hw fail-safe design)
- design and implementation of a recovery/reboot safety process, and recovery safe state.
- try to include random test checks.
- Privacy by design (if applies)
- Policy and strategy for critical and safety data backup.
- for files. - alwasys create a backup previous to modification of the file
- for files. - test always fist the rights in the file you are goint to access ( in C: int access(char \*path, int mode) -- determine accessibility of file. Also: stat(), and fstat() )

- Time accuracy and sync: Usually computer systems are drived by crystals to measure the time, a standard crystal for an embedded device as the NX5032GA crystal will have a variation in its measurement of 150 PPM (parts per millions), in the range of temperature from -40 C to 150 C. And an accurancy around 50 PPM, that is about 5 seconds per day. So when taking into account timings, it must be consider the stability and accuracy of the crystal.

Selection of communication protocols:

- RS-232 (low-speed, implemented by serial ports like we will use in this chapter),
- RS-422 (differential full duplex),
- RS-485 (differential half duplex, mult-drop),
- I²C (connection to I/O peripherals),
- I²S (connection to sound peripherals),
- CAN (controller area network),
- SPI (synchronous serial, used in the Nokia 5110 LCD),
- FireWire (high speed connection to external peripherals),
- Ethernet (wired network),
- Fibre Channel (high-speed, for connecting computers to mass storage devices),
- MIDI (control of electronic musical instruments),
- Serial ATA (high speed connection to external peripherals),
- SpaceWire (Spacecraft communication network),
- HyperTransport ( interconnection of computer processors),
- PCI Express (high speed connection to external peripherals), and
- T-1(high speed telecommunication over copper pairs)
- In signals or data from sensors, qualify the quality of the signal or the case in which the sensor is not calibrated, or error signals are detected, then desing and implement correction actions and safety estates as needed.

In communications must be checked: 

- BER: Bit error rate

- **Latency**: It's the time difference, between the time in which a taks is requested to start, and the time in which the task really starts. Also in other words, the time between a need is required, and the time it is fullfilled. This accounts for both hardware delays and software delays. A real-time system is one that can guarantee the wort-case latency, and this latency must be well-bounded and documented.

- **Throughput** or **bandwith** the ammount of data that can be processed by the system. This concept can be reported as an overall figure or as a short-term value (burst messages).

- there are some basic method to syncronize the hardware and software, 
 - Blind
 - Polling or periodic polling
 - Interrupt
 - direct memory acess.





ACcording to Straoup Book:
"tricky as error recovery.
Successful fault-tolerant systems are multilevel. Each level copes with as many errors as it can
without getting too contorted and leaves the rest to higher levels. Exceptions support that view.
Furthermore, terminate() supports this view by providing an escape if the exception-handling mechanism
itself is corrupted or if it has been incompletely used, thus leaving exceptions uncaught.
Similarly, noexcept provides a simple escape for errors where trying to recover seems infeasible.
Not every function should be a firewall. That is, not every function can test its preconditions
well enough to ensure that no errors could possibly stop it from meeting its postcondition. The reasons
that this will not work vary from program to program and from programmer to programmer.
However, for larger programs:
[1] The amount of work needed to ensure this notion of ‘‘reliability’’ is too great to be done
consistently.
[2] The overhead in time and space is too great for the system to run acceptably (there will be
a tendency to check for the same errors, such as invalid arguments, over and over again).
[3] Functions written in other languages won’t obey the rules.
[4] This purely local notion of ‘‘reliability’’ leads to complexities that actually become a burden
to overall system reliability.
However, separating the program into distinct subsystems that either complete successfully or fail
in well-defined ways is essential, feasible, and economical."



## Modular Design

Modular design is a methodology in which we break down the system functions or components into smaller components or modules, that build up toghether the functions or structure of the overall system. This allows us to better manage complexity

It is important to use a modular desing, because:

 - It makes easier to test and verify various parts of the system without the need to execute the whole system at once.
 - It increases maintainability and allows to easily add or remove software modules without modifing the whole system.
 - Improves greatly the loose decoupling of the diferent software parts. 
 - It makes the code easier to read and to understand.


tools for modular design:

- call-graph
- data-flow
- low level flow-charts


## Defensive programming

Defensive programming is a defensive coding style intended to ensure the continuing function of a program under unforeseen circunstances. This code style is usually used in systems with need high availability, safety and security. Techniques include error function handling for as much error types as possible and the use of exeptions.

Example of safe function:

```c
int16 safeSum ( int16 a, int16 b)
{
 //protection for overflow results
    if (((int)a + (int)b) > 32767)
        return 32767;
    if (((int)a + (int)b) < -32768)
        return -32768;
    return a+b;
}
```

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

**OPERATIONAL SEMANTICS**: Is a category of formal programming lenguaje semantics, in which certain desired propierties of a program, such correctness, safety or security are verified by proofs of logical statements about its execution and procedures, 

**TRANSITION SYSTEM**: In computer science, a transition system is used to describe the different status of a discrete system. It consists in states, and trasitions between states.

Transitions systems differs from *Finite State Automata* in several ways:
- The set of states, is not necessarily finite, but it must be contable.
- The set of transitions, is not necessarily finite, or even countable
- Not *Start* state, or *End* state, are given.

Reference: https://en.wikipedia.org/wiki/Transition_system </br>

Formal definition:

## Transition system:
Is a pair (S,→), where S, is a set of states, and → is a set of transitions. Event where there is a transition from state **p** to state **q**, is written as: **p→q**.

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
Given a LTS (labelled transition system): (S,Λ,→) a bisimulation relation is a binary relation **R**, over **S**, i.e.( **R ⊆ to S x S**) such both **R** and its inverse **R^-1** are simulations.

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

### Operators

- Sequence: p (dot) q or p · q ->  first p and then q

- Alternative composition: p + q -> it can happen p or q.

it is possible to combinate actios, so:  a·b + c·d

```
       / a ---> b ---> \
init <                  > --> end
       \ c ---> d ---> /
```
 - dead-lock or inaction: δ  - it represents an action that doesn't do anything at all, and it doens't end
   - so in the case a trace is:  a · δ -- it performs a and then \delta exectutes forever without ending
   - in the case a trace is: δ · a -- the dead-lock stays forever and the action a never is started.
 
 - multi-actions or simultaneous actions: those are actions that happen at the same time: a | b
   - multi-actions are conmutative: a | b = b | a
   
 - Conditional operator: 
     - condition:  ( n> 0)
     - if:            ->
     - else:          <>
     
     example:  (n>0) n-> n++  <> n--

### PROPIERTIES:

- Conmutativity: ' x + y = y + x'. In strong bisimulation, the order of the processes doesn't matter.
- Associativity of '+': '(x+y)+z = x+(y+z)' . the brackets are not meanfully for '+' operation in strong bisimulation. Brackets
can be dropt.
- Idempotence: 'x+x=x'
- Right distributivity: '(x+y)·z=x·z+y·z'

WATCH OUT with Left distribution:  'x·(y+z) = x·y + x·z' this equivalence is NOT valid with strong bisimulation!!!

- Associativity of '·': 'x·(y·z) = (x·y)·z'
- dead-lock equivalence 'x+δ = x' - dead-lock is not possible.
- dead-lock block: 'δ · x = δ' - there cannot be any action that follows delta

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
EXAMPLE: Can it be proof that the following process are equivalent: '(a+b)·c·(d+d) ?=? (b·c+a·c)·d'

Proof:

'(a+b)·c·(d+d)' use of idempotence propierty with '(d+d) = d', and we get

'(a+b)·c·d'use the associativity of '·', we can write, we can assure the sequencial execution

'((a+b)·c)·d', use of the right distributivity with '(a+b)', so we get

'(a·c+b·c)·d', we reorder the actions, with the conmutativity propierty:

'(b·c+a·c)·d'. we proof the estatement. -QED.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

EXAMPLE: Prove the strong bisimulation of: '(a·b+a·δ)·(δ+a) = (a·δ+a)·b·a'

Proof:

Start on the expression:  (a+b+a·δ)·(δ+a) 

Use of dead-lock equivalence 'x+δ = x', and the expresion results in: '(a·b+a·δ)·a'

use of dead-lock block: 'δ · x = δ' , as 'δ= δ·b', and results as: '(a·b + a·δ·b)·a'

use of the right distributivity: 'x·z+y·z=(x+y)·z', as: 'a· b + a·δ· b= (a + a·δ)· b', results as: '(a+a·δ)·b·a'

use of the conmutative propierty, results in: '(a·δ+a)·b·a' - QED.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

EXAMPLE: For a given processes, where 'x+y=δ'; prove that 'x=δ'

Proof:

Accoding to dead-lock equivalence 'x+δ = x', so in the other way around we have: 'x=x+δ'. We follow from here.

we were given that: 'x+y=δ' so it follows that 'δ=x+y' , so appling this: 'x+(x+y)=δ', and we have:'x= x+δ= x+(x+y)'

using the associativity and idempotence propierties, results in:  'x+(x+y)= x+y', so the overall expression is:'x= x+δ= x+(x+y)=x+y'

so with the given data: 'x+y=δ', the result is: 'x= x+δ= x+(x+y)=x+y=δ' - QED.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


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


## RECUSIVE STATES.

This is done by means of process equations. 'X' is known as a process variable.

'X= a·X'

'X=a·X & Y=a·b·Y+c·d·X'

A process variable is called __guarded__ if it is preceded by at least a single action.

for example the expression 'X+a·Y', is not guarded in 'X'

If the recursive state equations have all its process variable guarded, then then recursive especification is guarded.

### RSP Recursive Specification Principle

At recusive specification if it is guarded, has AT MOST one solution... it has exactly ONE solution.




TODO: tools to study systems 

https://workcraft.org/

http://www.es.ele.tue.nl/sdf3/


## PETRI NETS

Petri nets are a method for representing systems, usually systems that strongly represent production-consumption systems, sequece systems ...

Motivations: Petri-nets provide a method for representing and evaluatin a given system. They allow us to evaluate system propierties as concurrency, latencies, throuputs, ...

Wath out! not all the systems are possible to be represented with petri-nets... for example stocastic systems...

## Basic elements of a Petri net

The elements that define a petri-net are the following:

Graphically:

 - Bars: **A**ctions, processes or transitions or events,- this is an active event (T)
 - Circles: states, or **B**uffers or places,- this  is a passive state  (P)
 - Tokens (dots): represent consumable elements for the processes
 - Directed arrows: representation of the flow  (I or O)

Mathematically:

It is defined as the tuple:  **PN = <P, T, I, O, C, P>**

**A**: finite set of actions or process or transitions (the bars): {a1, a2, ... as}

**B**: finite set of states/places/buffers (the circles): {b1, b2, b3, ..., bn}

**I**: the set of Input arrows , these are the consumption arrow.

 - the functions I(AxB) --> (0,1) - maps inputs from a given transition (ti) to a Place (pj)
 - So if an action/process a1 goes to a state/place b1, then the I(a1,b1) = 1 because the 1 defines that it exits.

**C**: the consumption function, for a given Input arrow i:  C: I -> (A,B)

 - So for a given input arrow i, its consumption function :  C(i) = (ai, bi) 

**O**: the set of Output arrows, that is to say the production arrows.

 - the function: O(B,A) --> (0,1) - maps output from a state/place (B) to a action/process (A)
 - So if a state/place b1 goes action/process a1, then the O(b1,a1) = 1 because the 1 defines that it exits.

**P**: the production function, for a given output arrow j: O(j) -> (B,A)

 - So for a given output/production arrow j, its production function: P(j) = (bi, ai) 


Special types of petry nets are:

Multi-rate petri-net (Data-flow graphs aka marked graphs): Is the case in which the transitions consume or outputs more that one token.

Automata/State-Machine: In the case the Places, or processes have ONLY one incoming and other outgoing transition, then this petri-nets is equal to an Automata or State-Machine. Usually in this case, they are draw a bit different, as in this case the proceeses or transitions are redundant, so they are left out of the drawing, and only the cicles (states) are left. 

## Model patterns

There are three identificlable patterns 

 - Causallity: one event directly triggers other
 - Choice: one event has a choice, that is two or more options to trigger.
 - Concurrency: two or more processes run in parallel. 
 
 Also related to concurrecy is the concept of fork and syncronization. 
  - Fork: a process divides into two or more processes
  - Syncronization: two or more concurrent processes joint in a single event.
  
  
  
ref: https://isr.umd.edu/Labs/CIM/miscs/wmsor97.pdf

ref: http://www.site.uottawa.ca/~bochmann/ELG7187C/CourseNotes/BehaviorModeling/Petri-nets/index.html

ref: interactive tutorial for petri-nets: http://www.informatik.uni-hamburg.de/TGI/PetriNets/introductions/aalst/

references:
 - Petri Net Theory and the Modeling of Systems, J. L. Peterson, Prentice-Hall, 1981.
 - Petri Nets: An Introduction, W. Reisig, Springer-Verlag,1985


**TODO**: Check and elavorate: https://en.wikipedia.org/wiki/Calculus_of_communicating_systems

TODO: BER- Byte Error Rate --- add info.

TODO:  

- STAMP - Systems Theoretic Accident Model&Processes

<!-- https://macsphere.mcmaster.ca/bitstream/11375/11867/1/fulltext.pdf -->

TODO:

- Integrated Circuits reliability models. aging (e.g. HCI, NBTI etc) and transient (e.g. SEU, EMI etc).

<!-- 

http://ewh.ieee.org/r5/denver/sscs/Presentations/2005_02_Eaton.pdf


https://www.embedded.com/design/other/4018055/HCI-and-NBTI-Reliability-Impact-on-Submicron-IC-Design


https://www.dfrsolutions.com/hubfs/Resources/sherlock/IC-Reliability-Prediction-based-on-PoF-Models-Field-Return-Study.pdf?t=1513360245287


http://ceur-ws.org/Vol-1566/Paper1.pdf

http://www.mos-ak.org/washington_dc_2015/presentations/T05_Mohamed_Selim_MOS-AK_Washington_DC_2015.pdf

https://www.keysight.com/upload/cmc_upload/All/4-20170705.pdf

https://es.cs.uni-kl.de/publications/data/Kolh15.pdf

-->

Check, the methods, for testing: ccpcheck, vera ++, RATS, Jeckins, SonarQube, 
Test Unitarios: XUnit, CppUTest
Other sys: lcov, valgrind, ltrace, strace....

Refernece to check: Dependability through Assuredness™ (O-DA) Framework: https://www2.opengroup.org/ogsys/catalog/C13F

## CONTINOUS INTEGRATION

Continous integration is known as the techniques to run automatic tests in the system, each time a code is merged into the repository.

The spirit of the continous integration, is handle small changes in the code, merging the into the main trunk of the repository, so it favours frequent small changes, rather that more unfrequent bigger changes. So it aims to get a healthier code by means of developing and testing small changes. Usually is desired that once a new piece of code is done, the CI platform can autobuild the code, and test it automatically. Other features are desired, as notification and deployment capabilities.

Continous integration favours that testing is done so often that bugs dont stay for long as they tend to be detected very fast.

A famous platform for this is for example: Travis CI. https://docs.travis-ci.com/user/for-beginners.

### CI pros

- Regression error are minized due to early testing and early identification
- Building of the system and testing is automated

### CI cons

 - the repository must be monitored constantly
 - scripts and tools to automate the process can require a significanta amount of work
 

# OVERVIEW OF THE TESTING PROCESS:

**What is testing?:"** The test of a system is the process of evaluating the real capabilities of the system related with its desired/expected performance/behavior, and check it complies with the design requisites, expected behavior and desired capabilites.

Another important point, is that the test process helps to find and discover issues, bugs, faults or defects that may apppear in the system. The test process is even helpful for identification of major cases or points in the system, that have been left out of the specifications or requirements, an actually need to be taken into account.

A key concept to take into account is: that **it is not the development process what asures of the quality of the system** (of course, it helps quite a lot), **is the testing process what confirms and asures the quality of the project**

-- As a disambiguation, 'test' and 'debug' are different concepts. Usually the developers are the ones that debug the system. While testers identify issues and defects. 
**What is debuging?":** is the location, root-cause identification and fix of a defect or issue.

## WHY IS TESTING IMPORTANT?

**By testing a system behavior against its expected behavior, allows the identification of a defect in the system implementation. Once an defect is pin-pointed is then analized, corrected or fixed. As result of this action, the system is improved. Also, as a consequence, the chance that other defects, unknown issues or unexpected behaviors, remain in the system is reduced, and thus the confidence on the system is increased.**
 
The test process is of main importance in the project, due it evaluates the quality of the system, and give the stackholders, and the involved team, a sense of the expected confidence and risk level of the project. **This allows to take informed decisions and choices on the project execution, effort estimation, timelines and other project activities.**
  
## HOW MUCH TESTING IS NEEDED?

The number of test you can possibly plan for most of the systems tends to infinity. The stop point is that, in which, the asurance of the quality of the product, has been reached and checked satisfactory by the tests. Of course this level is different depending on the nature of the projet: the design of a video streamming home-appliance, usually doesn't need as much testing as the design of an emergency train brake system. 
 
## TESTING GOALS

Specifications/requirements test, checks the design is compliant with the stackholders or interested groups expectations. This often is done by means of 'test cases', where the 'tester' evaluates the action of the system for certain inputs, and compares the system outputs, actions and behavior with regart to the expected outputs.
  
  The specifications include all the 'functional' features of the system, but they can also include non-functional requiremets, as performance, usability, scalability, safety, security, availability,manteneability ...
  
  Specification testing is necesary to asure proper funtionality and behavior. But for complex or high-risk projects, it may be not nearly enoght. For example it doesn't cover a 'fool-user'. 
 
## The seven principles of testing aka the testing paradigms:

Over time, testing 'sages' have take notice of important learned leassons, and key-points to keep in mind in the test development. Those concepts are known as follows:

**1- Testing shows presence of defects** <br>
Testing, shows defects, but it cannot proof that there are not defects. Testing increases the asurance over the system, because when a bug is found and it corrected, the likehood (the chance) that remaining bugs may exist is lower. But even in the case, that no defects can be found any further, that is no proof that there aren't any.

**2- Exhaustive testing is impossible** <br>
Testing of all the possible combinations of a system is impossible. So to determine how much testing should be dont, an 
estimation of the risks, risk analysys and priorities, must be done. The testing will stop, when there is certainty that the systems complies.

**3- Early testing** <br>
Testing activities should be started as soon as possible in the system development live. (TDD - explain this!!!)

**4- Defect clustering** <br>
As following the pareto law, (it is said, that around 80% of the system faults, are caused by a 20% of the design) in many cases some components have most of the defect density. Testing should be focus to them, to maximice the effectiveness of the testing efforts.

**5- Pesticide paradox** <br>
Running the same test or the same types of tests, again and again, makes that eventually the same set of test don't find any defect at all. Having into account that some schools of thought consider a succesfull test, that one that find defects ... it's a bit, like that set of test loses "effect". 
The set of test, needs to be reviewed and updated, to exercice different parts of the system, and in different ways.

**6- Testing is context dependant** <br>
Testing depends on the context. A safe-critical system test is not at all the same that the test for a video streamming appliance.

**7- Absence of errors falacy: Failure-free test doesn't proof failure-free system** <br>
Even if no defects are found, it doesn't proof that the system is usable, or complies with the end-user expectations. As previously stated testing only increases the asurance of less possible errors.

## THE DEVELOPMENT - TESTING RATIO

TODO ... Work in progres .. but the recommendation is... two hours testing per each development hour.
 

## TEST LEVELS

The different test at different architectural system levels, are known by different names, and its objective evaluates different system levels. The concept of the different test levels follows below. Is important to take into account, that the actual test may differ quite a lot, regarding the understanding of the system concept: for example, in an aircraft desing the system is the aeroplane, and one of its componets may be the landing system. On the other hand the landing system, is also a system by itself, and it depends on other severals components. So the key point, is that their actual test are going to be quite different, but the following descriptions, are related to the hieraquical structure of system in hands.

### UNIT TEST aka MODULE TEST also COMPONENT TESTS:

At the software level, the **unit test** is understood as a test to all the  basic functions, algorithms, classes or componentes, which checks all the possible test cases positive and negative. Usually the lowest level unit on the system architecture. Its fundamental function and behavior is evaluated, not only its corretness but it can also cover not functional aspects, as performance, robustness, usability, ... 

Unlikely the following test descriptions, this test usually is done by a developer, and it's record tends to be quite informal.
At the hardware level, it is understand as a test to determine or clarify hardware components performance.

It will be explained later in the text, bus as reference is just annotaded here. In the units test, must be covered at least:
 - correct functionality
 - positive and negative test with valid and invalid data
 - data ranges and boundaries
 - code coverage  (percentage of the overall code in the function tested)
 - decision coverage (the flow of the program trough conditional statems, as: if, else, for, switch-case ...)
 
Depending on the system, even more things will need to be evaluated and tested.

The element **componet test** remains the same meaning as the unit test, but is more likely to be used with harware components.
 
### INTEGRATION TESTS:
The **integration test**, are understand as a test that looks for assesment of the performance and correct behavior between different **modules**, libraries or other componets in a system. It usually check the interfaces and the data workflows between them.

 Usually the following are tested at the software level
 - Interface between componets
 - Possible configurations and behavior on those configurations
 - The data workflows
 
 Once the integration level for software is done, the system integration test with the hardware platform takes place:
 
 Different strategies can be followd: Top-down, bottom-Up, functional tasks, user cases, ...
 
 The integration test, is better done incrementatlly, firstly, testing the intefeace between pair components, and increasing the number of elements/modules tested, up the point that all the componentes/modules are tested together. This allows, to identify more easily the source of a failure, due it tends to appear before, and the number of components at play, is not all the whole system.
 
 Non-functionoal characteristics, have to be tested also: as performance, ...

### SYSTEM TEST:

The **systems test** goal is to asure the fulfillment of the system expected functions as a whole element, and also the non-functional requirements, as performance, security, safety, ... System testing checks all the external interfaces of the system under development, which is a sub-system of another system.  In the system test, the enviroment, condition and test should be as close as possible to its expected real function. So usually, the test are of the types: bussines cases, user cases.

**Important** An independent test team, should carry the system tests.

### ACCEPTANCE TEST: 
The aceptance test usually is done by the client that requested the system design or similar stackhorlders, an outside of the desing 
team labs or place. The objetive of this test, is independent evaluation of the system regarding to its designers. Usually is also quite 
useful to define functions that are outside of the defined or specified requirements. It also have a very important role, for following up and check the project milestones. 

This type of test can have serveral faces:

#### UAT: USER ACCEPTANCE TEST
Evaluates the correct behavior of the system by a bussines user. As may be the case that a data system user interfece is correct for a person that is going to use it in a bank or similar.

#### OAT: OPERATIONAL ACCEPTANCE TEST
Evaluates that the system correctly performs it's defined function by the system adimistrators.

#### REGULATION and CONTRACT ACCEPTANCE TEST
Evaluates that the system complies and achieves acceptance criteria with legal issues (govern, law, contractual, materials, safety, enviromental, emitions ...)

#### ALPHA and BETA TESTS:
Alpha testing is understand as a test done at the design team organization, but for colleages outside that team or project.
Beta testing is a test done by the customer, client or interested parties at their own locations.

TODO:

Check, the methods, for testing: ccpcheck, vera ++, RATS, Jeckins, SonarQube, 
Test Unitarios: XUnit (C# .NET) , CppUTest, googletest ...
Other sys: lcov, valgrind, ltrace, strace....

Reference to check: Dependability through Assuredness™ (O-DA) Framework: https://www2.opengroup.org/ogsys/catalog/C13F

## TEST TYPES:

### Functional testing
Functional testing  is focus on evaluation of the correctness of the system behavior, and that it perfoms as expected. It is applied to all the different test levels: unit, component, integration, system. Its usually is done by means of requirement and specification checks, but also to user cases. Is also common that it uses the black-block testing methodology.
 
### Non-functional testing
There are things aside the main functionality that also are required, those migth be: data or communitcations throughput. User interfaces, performance, usability, scalability, safety, security, robustnes, avalibility, manteanability, stress testing, portability,  .. Non-functional testing can be done at all test levels: unit, component, integration, and system. 

 - Sometimes, this the non-functioal propierties, are mapped to the ISO 9126 - Software Quality Product.

A list of non-functional characteristics:

 - usability: how easy it is to use. This may also include some aspects as the learning curve, User interface, ... 
 - performance: evaluation of the system with regard to responses times and data throughput, latency, measurement of response times, transaction rates, respose to many transactions, or simulation of many users.
 - security: security evaluation
 - safety: safety evaluation
 - robustness: evaluation of the behavior of the system related to out of the system, or external mis-happenings. 
 - fault-tolerance: evaluation of the behavior of the system related to inner happenings, or inner faults.
 - predictivity: how much, and up to what point you can predict in advance the response or behavior of a system (just remember
 that for example cache-memories are bad for predictivility...)
 - repeativility: how much is the repeativility of the system (time responses, skews, ...)
 - availabilty: evaluation of the up time and down time of the system (MTBF) (due to failures or maintenance stops...)
 - requirements trazability: how easy is to track down the systems requirements to its actual implementation.
 - documentation: evaluation of documentation of the system.
 - testeability: evaluation of the easiness to test the system. 
 - portability: evaluation of the easines of the translation of the code to other posible platforms or architectures.
 - reliability: evaluation on the trusth of the proper behavior of the system
 - dependability: evaluation of the dependability of the system (let's say this is: how much confidence you can have in it)
 - grade of loose coupling: evaluation of the structure of the code implementation. 
 - scalability: ability to add elements to the system.
 - memory & storage: amount of memory needed, types of memory in hw (flass, eeprom, volatie)
 - data processing volume & load stress: performance under peaks of data
 - configuration: check behavior under defined configurations
 - compatibility: compatibility with defined versions
 - installation: evaluation of the methods and easianess to install the system.
 - recovery: evaluation of recovery methods
 - maintainability: evaluation of maintenance methods, or the ability to undergo repair or modifications.
 - code readability: how easy is the code to read and understand (this is quite subjetive)
 - interconnectivity: the ability to work with diferent related systems. For example a system might work only withy
 a propietary protocol that prevents it to work with equivalent systems from other manufacturers, thus
 having a low interconnectivity. A system that performs equally, and that uses an open protocol has higher
 interconnectivity, because it can be used with different manufacturer equipments/systems.
 - expanseability: is the ability to increase the functionality or propierties of a system. (architecture evaluation). for example if the system has a plug-in engine or similar.
 
## Structure or Architectural Testing: White-box test
It is also knwon as a **white-box** testing. Is the evaluation of some parameters of stadistics of the system behavior, as for example how complex it is (ciclomatix complexity), the number of control flow structures (if, else, for, while) and the overall of the tested code...  with the kwnoledge of its inner workings.

 - It is best used after the black-box techniques, to assert the throuroghness of the testing.

 - It can be used at all the testing levels: unit, component, integration and system levels.


## Testing related with changes: Re-testing and Regression testing (also Maintenance testing)
When doing the test sets, failded test, must be repeated to assert them, and exclude the possibility of a  possible error due to the context, conditions, enviroment, equipment used or other causes. 

On the other had, when a new part of the system is added to the development, some times that  new code, function, or component, affects other element of the system; and in the worst case, making the to fail its pourpose or expected function .... to check this possibility, a set of test, is done, so it checks previous functionalitites, in order to verify the rest of the system, keeps working fine. 

This type of testing, is usually good candidate for automation.

## TEST METHODOLOGIES AND DESIGN TECHNIQUES:

### BLACK-BOX TECHNIQUES:

Black-box techinques, refers to those test methods, that don't need to known the inner workings of the device under test. 
its is named: black-box ... because you can't see what is inside. Usually they are based and designed to evaluate the compliement of the requirements and specifications.

The most common black-box techniques are:
- Equivalence partitioning
- Boundary value analysis
- States and transition testing
- User-case testing

Also common techniques for implementing the previous tests are:
 - SIL: Software in a loop
 - HIL: Harware in a loop

#### EQUIVALENCE PARTITIONING:
The inputs to the system are classified into groups or value ranges, that have and expected equivalent response, so they are expected to be processed in the same way. This groups of values, can be for example: group of correct or valid inputs or data, group of incorrect (or not valid) inputs or data. These ranges of values, are kwnown as 'partitions'. This way the test, are designed so the check the behavior of the system for every partition. 

- Equivalence partitioning can be used in any test level. (unit, component, integration, system ...)

```
EXAMPLE:
A system has an integer numeric input and only data betwen 50 and 100 (both numbers included) is accepted as a valid data. How shoud be an equivalence partitining test designed?

The valid data is only the integer numbers that belong to [50,100], otherwise is an invalid data. Thus there is three intervals:

 - [0, 50): first partition- invalid data
 - [50, 100]:second partition- valid data
 - over 100: third partion- invalid data

So a possible test design would be to test the values: 25, 75 and 150.

The expected test results would be:

input: 25 - output: invalid
input: 75 - output: valid
input: 150 - output: invalid
```

#### BOUNDARY VALUE ANALYSIS:

Many times, for the input partitioning, the edge value, that limits between partitions, may have an incorrect behavior with respect its expected response. So the boundary values of the partitions are tested to look for defects. The boundary values of valid and invalid inputs must be tested. This methodology usually is tested at the same time that the equivalence partitioning, as they are very closely related.

- Equivalence partitioning can be used in any test level. (unit, component, integration, system ...)

Equivalence partitioning and boundary values analysis are methods, that evaluate the correct behavior of the device under test, according to the input and expected outputs. 

The design of equivalence partitioning tests, and boundary test analysis, starts from the analysys of the requirement and specifications of the system.

```
EXAMPLE:
In a form, a input field is intended for a data that represents a year. The field accepts, 
years from 1900 to 2035, both included. 

What would be the boundary values to test the input acceptance?

>> 1899, 1999, 2035, 2036

```

```
EXAMPLE:
Following with the previous example: 

A system has a integer numeric input and only data betwen 50 and 100 (both numbers included)
is accepted as a valid data. How shoud be an equivalence partitining test designed?

The valid data is only the integer numbers that belong to [50,100], 
otherwise is an invalid data. Thus there is three intervals:

 - [0, 50): first partition- invalid data: - 50 is not included
 - [50, 100]:second partition- valid data - 50 and 100 are included
 - over 100: third partion- invalid data - 100 is not included

For testing the boundary values, a possible test would be: 49, 50, 100, 101

The expected test results would be:

- input: 49  - output: invalid
- input: 50  - output: valid
- input: 100 - output: valid
- input: 101 - output: invalid
```


#### STATES and TRANSITION TESTING:

When the system under test has to behave according to state machines or transition systems, or other similar logical or sequencial behaviors, decision tables are a good option to check that the system complies with its expected behavior. So the decision tables, specifie the triggering condition or actions that imply a state change, then all the combination of this action or events are tested. This methodolgy, often is combined, with others as: **code coverage** and **decision coverage** (these are described later in the text). 

Remember, that an Automata model, that is a state machine, can be ot two types: combinational or sequential. A combinational system, has a defined output, for the given inputs. A sequential system, uses a memory, to keep an state. More elaborate models, are the LTS systems (Lineal transition systems):


#### USER-CASE TESTS aka USER-STORIES:

A test that mimics a real user scenario, is kwnow as user case test. A user-case test, aims to emulate the interaction, and common action and situations of the system under test and a normal user. User-case tests, check the data-flow and the process-flow, and how the system is likely to work.

User-cases test are specially useful to discover integration and sytem defect, because they exercice the behavior of the overall system. Also they are commonly used for acceptance tests by stackholders of the project. 

The design of the user-case test, starts **from gathering information from the stackhoders or final user**, of the expected common user interactions with the system under design.

#### SIL: Software in the Loop
   The software is tested against a model, that model reflects the requirements, specifications and expected behavior of the system. Is a method based on simulation. This method is best used at integration or system level, because with the models (logical, mathematic or physic ...) we can simulate the rest of the modules, or system elements, which makes the testing somehow easier and faster. Of course the models must be accurate, otherwise, false positives or negatives can be obtained in the test results. 
   [NOTE]... Although they have the same achronym, don't missunderstand with SIL, when it stands for: Safety Integrity Level.
   
#### HIL: Hardware in the Loop
  The hardware under test is tested, but the remain of the system or signals, or elements external to that hardware can be simulated, according to fitting models of elements. The advantage is that only the harware we are interest it is needed and the other elements of the system don't need to physically be in the test lab/facility.
  
  This is a simulation methodology, and best used at integration and system level. As with all the simulation methodologies the model must be significative enought. At the hardware level, it represents, signal propierties, response and reaction times, ...
  
  In both previous simulation techniques, a system model is used, so it must be such that it can reproduce accurately all the significant and relevant behaviours of the system.

### WHITE-BOX TECHNIQUES:

White-box techniques are those that require the kwnoledge of the inner workings of the system under test. 

For software the most common are:
 - Statement testing and statement coverage
 - Decision testing and decision coverage

#### STATEMENT COVERAGE:

Is the evaluation of the percentage of all statemenst (lines of code) which have been exercised by the testing. Usually test are designed so different code blocks can be executed, so the test suits will aim to cover and exercite as much code as possible. The account of the code executed is done by code instrumentation by means of auxiliar libraries. 

#### DECISION TESTING aka BRANCH COVERAGE:

This test accounts the percentage over all of different branchs exercised in the code execution (at the control flow structures: if, else, for, while ...). Tests are desiged, so different conditions are met at the different branch evaluation points. The aim is to account for as much program possible flows as possible. 

**NOTE**: A 100% decision coverage (or branch coverage) implies a 100% code coverage, but the other way around is not true: a 100% does not guarantee a 100% decision coverage.

```
EXAMPLE:

how many tests are needed to cover the 100% statement coverage and decision coverage of the following pseudo-code:

IF A > B THEN
C = A – B
ELSE
C = A + B
ENDIF
Read D
IF C = D Then
Print “Error”
ENDIF

>> 2 tests for SC and 2 test for DC....  of course this can be evaluated at the same time.

```

### EXPERIENCED BASED TECHNIQUES:

In experienced based tecniques, the test are done based on the previus project experiences or knwoledge of similar systems to the one 
is under test. Similar systems and previus experience on them, allow the testers to have an intuition on the weak and strong points at the system development. 


## WHITE-BOX vs BLACK-BOX testing:

As a clarification, just state, that a Black-box test is that which only regards for the inputs and outputs of the system under test, so without looking in the insides of the system, effectibily treating the system as a "black-box". On the other hand, the White-box test, regards for the inputs, outputs, and also for the inner values, signal and internal states, and inner workings on the inside of the system under test. A good testing strategy and test process, uses both approaches, it usually starts with a black-box approach, both in hardware and software, and builds up to a white-box approach.


## HARDWARE TESTING

There are test methodologies that are only applicable to the hardware of the system. Those methods aim to increase the reliability and confidence on the hardware components and subcomponets of the system.

 - ALT: Accelerated life testint.
 - HALT: Higly Accelerated life testing.
 - HASS: Higly Accelerated stress screening.
 
 When designing hardaware or mechanical tests, according to the expected goal, different classification can be made:
 
 - **pass/fail test**: the test subject is just evaluated according to if it complies or not with its goal.
 - **test to failure**: the test subject is evaluated up to the point of critical collapse or failure. this test improves the pass/test fail, as it explores the boundary limits of the test subject.
 - **degradation test**: the test subject is evaluated during certain life time of cycles, and different relevant paramenters or performance are evaluated. Then the the test subject is evaluated againg during other life time or cycles, and again the paramenters of interest or performance is evaluated, .... this continues up to the goal of the test is fullfilled. This method is preferred over the other two previous methods, as it gives information about the relevant parameters of interest and its evolution.
 
ALT (and HALT) and HASS are two methods that are complementary of each other.

**ALT** (Accelerated life testing) and **HALT** (Higly Accelerated life testing) is used during early desing and development phases, and aims to clearly identify the hardware operating limits and fault modes at its material level. 

During the design and development phase is the best change to modify the design and the point at which will have less impact overall the project. Sometimes, some devices, don't have clear specifications, in the range we would like to use them, this might be because we are using these devices out of its common design use, o because our design goes into never explored situations...

**HASS** (Higly Accelerated stress screening)  takes place in the industrialization phase, to screen hardware components, to indentify possible unidentified or lattent faults  - in practice it might just happen that a batch of a certain element, might be out of its specs, for wathever reason, ... if this is not detected in the fabrication stage, the proble will most possibly surface at the end user end, ...  As a reference is possible to look for the case of the Samsung Galaxy Note 7, that under some cases, was known to explode, allegedy due to irregularities in its batteries. It is estimated that this issues costed the firm around $5 billion. 


reference: https://www.techradar.com/news/samsung-galaxy-note-7-battery-fires-heres-why-they-exploded

![battery_issue.JPG](https://github.com/sergiocollado/potpourri/blob/master/image/battery_issue.JPG)


Some times, the hardware supplier, might by error provide components out of its specification, ... for reasons that it cannot handle directly, it might be and innadecuate storage, or the use of base materials under its prime performane. For example during the 2010s the gold rised to a very high value, and some foundries hat to resort to other materials to make the bondings of the chips, just for these reason, the skew of the electric signals was different, and all those components hat to be re-evaluated and characterized. 

reference: https://www.eetimes.com/document.asp?doc_id=1257340

![copper_turns_gold.JPG](https://github.com/sergiocollado/potpourri/blob/master/image/copper_turns_gold.JPG)


Other times a natural disaster, might force to change the production locations, and due to this, the components, might be also sligthly out of specs, because the production is not fine-tunned.

reference: https://www.theguardian.com/technology/2011/oct/25/thailand-floods-hard-drive-shortage

reference: https://www.theguardian.com/technology/2011/apr/11/smartphones-hit-by-japanese-earthquake

![thai_floods](https://github.com/sergiocollado/potpourri/blob/master/image/Thailand_floods.PNG)


These methods are used for IDENTIFICATION and CORRECTION of possible or eventual faults at the hardware component level.

### Fault injection techniques

Fault injection is the way to assert the grade of fault-tolerance or dependability of a system. It is usually related to the harware testing. The actual way to inject faults on the system may differ related to the phase on the development of the project. In a design phase, the fault injection may be just evaluated with a simulation. Later on the life cycle, fault injections is  actually done in prototypes.


## Design for Testeability (DFT)

Design for Testeability is the concept of including at the **design phase**, resources or methods to speed and improve the testeability
of the system... as the most clear example is the inclusion of test points or test traces or test-connection headers at the PCB.

reference: https://www.edn.com/electronics-blogs/all-aboard-/4434254/Designing-testability-into-a-PCB

## Poka yoke

Poka yoke means "error-proof" in japanese. ... this technique, stands for example on settng different (not-compatible) connectors
in the electronic-design/hardware of the system, so it is impossible to wire the hardware in a incorrect way. For example: a SD memory card only has a position that fits, so actually it is not possible to put it wrong without realsize of the mistake (at least it should be pretty difficult... ) 

reference: https://toughnickel.com/industries/Poka-Yokemistakeproofing

## TEST PROCESS STEPS and ACTIVITIES

At the testing context, the first action to do, is to define the **Test Plan** for that, several key points have to
be defined:

 - Test planning and control
 - Test analysis and design
 - Test implementation and execution
 - Exit criteria, evaluation and reports.
 - Test clousure and activities.
 
### Test planning and control 

 **Test planning** Definition and plan of the actions to perform, time-line, team, equipment, facilities and tools needed, that aims to define the objectives of the testing, and the needed actions and resources to achieve those objectives.
 
 </br> </br>
 
 **Test design and analysis**
At this step, tests for evaluation of the system are designed,(actions, contexts, enviroments and expected results) and defined the objetives they want to ckeck.

This include go through the following points:

- Review requirements, system integrity level (that is compliance with some system parameters previously defined as software complexity, risk assesment, safety and security level, performance, reliability, cost ... Usually these points are defined by the stakeholders):
- Evaluation the testability of the test basis and test objects.
- Identify and priority test conditions based on the overall project.
- Design and prioritaze high level tests.
- Identify necessary test data and resources. (who provides correct input data?)
- Design and define the test enviroment, platform, equipment, tools and required infraestructures and materials.
- Create a method to a bidirectional traceability between test basis and test cases and requirements.

 </br> </br>
 
 **Test control**: Testing activities must be monitored through the project. It is the comparation between the state of the project, against the expected planned result. It also covers the **report** of the testing status, including desviations and non-conformances  from the plan. Also include proposals to the actions that need to be done, in order to meet again the goals, and expectations of the project. 
 
So **test control** is related to guide the corrective actions taken as a result of information or metrics. These actions can be applied to any part of the system.

Examples of test control actions are:

- Take decisions based on the information from test monitoring, evaluation and test results:
- Repriorinzing tests, and identification of potential risks (need of more team members, need of more equipment, or additional tools ...)
- Change of the test squedule, based on the abailability of equipment or facilities.
- Setting the criteria about re-testing issues, for including those modifications into the system build.
- trace test done versus the requirements they check.

 </br> </br>
 
## Test implementation and execution

The designed test procedures are implemented, and a certain execution sequence for the tests has to be defined in order to run the set of test (usually according to priority). When the test platform and enviroment is set up, the test cases are run, executed, and evaluated.

The objetive and goals of the test execution is:

- Implementation, and definition of the expected results, and execution order and priority of the test cases.
- develop test procedures, create test data, optionally preparing test hardeness and writting automating test scripts.
- creation of test suits, for efficient test execution.
- verification that the test enviroment has been set up properly.
- verification and update if needed, of bi-directional trazability between the test cases and requeriments.
- Execution of the test, according to the test procedure. Log of the test execution relevant information, as identification of the
different elements involved, as system version: , software and hardware version, prototype identification, tools, device under test, execution time, and other significant data needed.
- definition of the test trazability to the requirements it checks.
- Definition of the criteria for comparation and evaluation of the test with the expected results.
- Repeat test that failed out of the expected results to confirm the issue, and gather new information details if possible. check if the 
efect is always reproducible, or it is sporadic....
- Record and logging of the tests results, significant test conditions, enviroment or other data that may be userful. 
- If new issues are found, _regression testing_ (test all the system to asure that new code or components haven't affected the rest of the developed system) may be advisable, to check that new issues has not appear in other stable parts of the systems.
- Report discrepancies with the expected results, outliers, incidents, and misperformances, or unexpected issues and analyse them in order to identify a possible root-cause. (defect in the code implementation, invalid input data or conditions (as could be: data out of bounds, damaged equipment, wrong procedure, ...)
- the test documentatinos must be according to the "Standard for Software Test documentation": IEEE STD 829-1998.

 </br> </br>
 
 
### Test results (Exit criteria, evaluation and reports.).

- Evaluation: the data obtained from the test should be compared with the expected results.
- Report of the failed test!!!
- Modification over the test, or expected results should be planned.
- Reports should be done for the stackholders, and system team members.
- The test documentatinos must be according to the "Standard for Software Test documentation": IEEE STD 829-1998.

### Test plan clousure activities.
 
At the end of the project, or at project milestones, certain activites are to be observed:
 
 - Report of the system acceptance.
 - review and learned lessons.
 - project metrics, and evaluation of the testware.
 
https://en.wikipedia.org/wiki/Testing_Maturity_Model

### Test plan document index example guide:

As always, the test documentation must be according to the "Standard for Software Test documentation": IEEE STD 829.


| iNDEX  | . | Description|
| :---:|     :---:      |          :--- |
| 1   | Presentation    |  Date of release, document version, document owner, approvals    |
| 2   |      | Introduction, presentation, motivations, overview and background of the project and the system |
| 3   |      | Document identification, objetives, goals, scope (this is the test plan document for XX project, and it explains the test plan for YY, intended for the system version ZZ, according to requirements version RR ...) and document history, and related needed documents (as normative, release notes, system version, system documentation, requirements document version).    |
| 4   |      | Testing team, responsabilities and roles    |
| 5  |      | References (list of normative elements, manuals, procedures, application notes, agreements, notes, ...)   |
| 6 |      Test Process      | Test goals and tasks  |
| 7 |        | List of documents, description and formats or templates to use at the test process |
| 8  |       | Asumptions and enviroments (hardware platform, operating system, applications, ...)   |
| 9  |      | Features to be tested   |
| 10  |      | Features to not be tested    |
| 11   |      | Dependencies and resposabilites    |
| 12   |      | test Tools (multimeters, debuggers ...) , equipment (data loggers, oscilloscopes, power-supplies ...) , software (protocol simulators, testware, test management tool, automation ...), resources and facilities    |
| 13   |       | Test strategy  (how are de test cases are designed)   |
| 14|       | Test process squedule (time for analysis and design, timeline test process, control points, deliverables, current and future expected events or needs)   |
| 15   |       | Test data generation (where the test data is comming from, does the customer or an specialist provide it? is it good enought data (relevant, accurate and significative) ?)    |
| 16   |       | Unit tests  (procedures, cases, objetives, goals, requirements, trazability, input data, **expected data**): functionalities tested, and its associated requirements. Positive and negative input value data and ranges. Code and condition coverage. |
| 17   |       | Integration tests (procedures, cases, objetives, goals, requirements, trazability, input data, **expected data**)  |
| 18   |       | System test  (procedures, cases, objetives, goals, requirements, trazability, input data, **expected data**)   |
| 19  |       | Non-functional test (performance, escalability, interface, usability, safety, robustness, availability,  ...)   |
| 20   |       | Traceability test-requirements and specifications |
| 21   |       | Minimun set of test to execute to evaluate viability of a new version release (test basic functions and safety/security concerns).    |
| 22   |      | Regression testing    |
| 23  |       | Automated testing   |
| 24  |       | Batch testing (automated regression testing)   |
| 25  |       | Metrics to take into account (sloc, ciclomatic complexity, code coverage, decision coverage)  |
| 26  |       | Control and monitoring points, milestones and procedures (report formats and expected information and data, risks reports and change requests.  |
| 27   |      | Risks: identification, evaluation and responses (possible risks for the project, as lack of resources, time deliveries overdue, lack of man-power, lack of quality test data, future preditions, problems to overcome or concerns   ...)    |
| 28 |   | Test completion criteria definition- definition of conditions to halt the testing.. to know when to stop of testing |
| 29 |   | Test executionUpriority order- the order of the test execution is defined by the risks levels that each test evaluates.  |



 <!-- http://www.softwaretestinghelp.com/test-plan-sample-softwaretesting-and-quality-assurance-templates/  -->
 
### Test Case description template example

| iNDEX  | . | Description|
| :---:|     :---:      |     :--- |
| Test case ID  | "   "   | Test case identification number   |
| Test case title  | "   "      |  tittle or summary of the test case    |
| Test case priority | "   "      |  priority of the test case based on the risks it evaluates   |
| Test case description  | "   "  | description of the test case    |
| Test case type | "   "      | test case type: white-box, black-box, user case, user acceptance...   |
| Test case requirements | "   "  | list of the requirments that the test case exercices  |
| prerequisites | "   "      | list of prerequisites or previous steps to launch the test case	   |
| data | "   "      | identification of the data to be used in the test   |
| expected result  | "   "  | description of the expected value to consider the test ok |

### Test Case execution template example

WIP: ...

## TEST TECHNIQUES:
  
### Software: Dynamic vs Static testing

When a test case of a system involves the actual run of the system, this is known as 'dinamic testing', on the other hand when it doens't inolve the run of the sysem is known as 'static testing'.

 - Dynamic testing usually makes us of stubs/drivers, execution from a debugger enviroment. And is also quite common to automate it.
 
Static testing, is referred to those evaluations that don't need the system to be running. Those are techniques as: code review, revision, walkthoruhgs, inspection, and alsouse of programs that automatically ckeck the code propierties (as could be: detection of 'dead code' (code that will never execute)unused variables, missing pointers, out of bound arrays, wrong types varaible asignations, lost of precission in mathematical operations, ...) 

### Static Techniques:

 Static techniques are based on the evaluation and analysis of the code, of the system, documentation, requirements or desing especifications, test plan, test cases, test scripts, without the execution of the code, also any other related work can be evaluated as, the  This is opposed to the dynamic testing, which relates to the actual run of the system and code. For example: a revision can find requirements issues, that are much more harder to pinpoint in dynamic testing.
 
 This is an important medhod and can be done well before the dynamic test execution.The advantages of the defect detectections at an early point in the project live include early correction, increase of productivity, reduction of development times, cost of testing, 

A common tool for static checking is the program "cppcheck". that is open source and also can check for CERT and MISRA standards.

A list of statics techniques are:
 - Review process (requirements, hazard, risks, architecture, design, components, code ...)
 - System analysis (as define the worst case scenario)
 - Code automated analysis.
 - Code complexity evaluation.

references:
- https://sourceforge.net/projects/cppcheck/
- http://cppcheck.sourceforge.net/manual.pdf

#### Review Process:
There are several levels of review process depending on how formal they are done. the way the revision is carried out depends on its objectives: gain understanding of the system, presentation of the sistem, introduction to new team mebers to the system, or even an auditory.

**The review process can be and should be applied at different activities, as: system design, hw and sw design, sw code, requirements and specifications, tests, plannifications, ...**

##### Types of review

##### Informal review (Peer review)
- There is no formal process
- May be part of pair programming, or technical review of design, code, or architecture
- Results may be documented
- Varies in usefulness depending on the reviewers

##### Walkthorugh
- Led by the author
- open-ended sessions. 
  - optional pre-meeting work.
  - optional report with findings.
- may vary form very incormal to very formal.
- main goal: gainning understanding, learning, finding defects.

##### Technical review
 - documented, defined formal defect-detection process.
 - includes team members, colleages, technical experts, and optionally managers.
 - may be performed by peer review.
 - ideally led by trained moderator (not the author)
 - pre-meeting preparation by the reviewers.
 - optional use of checklists.
 - includes a list of findings, notes, recommendations and veredict if the product meets the requirements.
 - main goal: discuss, plan, make decissions, evaluate alternatives, find defects, solve technical problems, check conformace to requirements and specifications, regulations, standards,
 
 ##### Inspections
  - Led by a trainned moderator (not the author)
  - usually conducted as a peer examination
  - defined roles for the participants
  - includes, metrics gatherings
  - formal process based on rules and checklists
  - defined entry and exit criteria for acceptace of the product
  - pre-meeting preparation.
  - documented by an inspection report, that includes findings.
  - formal follow-up process.
  - main goal: finding defects.
  
##### Activities for a formal review

The following activities use to be followed for a formal review.

 1 Planning
     - Definition of the documents to review.
     - Definition of the review criteria
     - Selection of the team personnel
     - Definition of roles.
     - Definition of entry and exit criterias (on formal review types: as inspections)
     - Selection of the documents and parts to review.
     - Check entry crietera.
     
 2 Kick-off
     - Distribution of the documentos
     - Explanation of the objetives, processes and documents to the team that is going to do the review.
     
 3 Individual work
     - Prepare the meeting tasts: as the review of the documents.
     - Annotate potential issues, defects, notes, open points and questions.
     
 4 Examination/Evaluation/record of the result (actual review meeting)
     - open discussion or evaluation about the findings. 
     - keep track of the defects found, make recomendations for handling them, and decisions. 
     - record of minutes of the meeeting, in the case it is a formal review.
     
 5 Rework
     - Fix the issues or topics found (usually done by the author)
     - Record status of the update of the defects (on formal reviews)
     
 6 Follow-up
     - Check the defects that have been adressed
     - Gather metrics
     - Checking exit criteria. (on formal reviews
     
**ADVICE**: Taking different points of view during a review, use of check lists, may made the review process more productive.
    
    
##### Roles and responsabilities

- **Manager** decides on the execution of reviews, allocates or reallocates project squedules and resources.
- **Moderator** leads the meeting, the review of documents, planns the reviw process and its follow-up activities. the sucess of the review use to fall on him.
- **Author** person with the final responsability of the document o set of documents to review.
- **Reviewers** people with technical or bussiness background, who after the pre-meeting preparation, may identify and describe findigs or defects, under the product review. Reviewers should be chosen to represent differnet points of view, perspectives and roles in the process.
- **Recorder** (Scribe) document all the relevant points, issues, questions, doubts, advices and considerations, identified during the meeting.

##### Success factors for a review:

- Each review has a definite objective
- the right people takes part in the review
- testers are valued reviewers who contribute to the review, who also learn from it, and helps them to start working on the test process earlier.
- findings, even defects, are expected to be found, welcomed, and expressed objectively.
- the review must take place in an athmosphere of trust; the outcome will no be used as an evaluation of the participants.
- review techinques and activities are done, according to the level of the project and objectives.
- Roles and checklist are used to increase effectiveness
- Trainning is given for the more challenging and formal review process, as could be the inspection.
- Management should suppor the review process, as for example allocating correct time for the review activities.
- There is always and emphasis, in learning  and process improvement in the reviews processes.

Also check the following topics:

http://www.sohar.com/proj_pub/download/

https://en.wikipedia.org/wiki/Testing_Maturity_Model

## TEST TEAM: ROLES and RESPONSABILITIES.

### Test Coordinator (aka test leader) tasks: 
 - Coordinate the test stategy with the management and development team.
 - Write and/or review the test strategy.
 - Plan the tests and re-adjust it as needed.
 - Lead tests especifications, implementation, execution, and test automatization.
 - Monitoring and control of the test plan, gather the necessary metrics, and evaluations.
 - Define test tools.
 - Report test plan status, controls ...
 
### Tester tasks:
 - Review and contribute to test plans.
 - Analyze, review  requirements, specifications and models.
 - Create test specifications.
 - Set up test enviroment, prepare and gather test data, implement, automate and execute and record tests.
 - Review test wrote by others.

## TEST PLANNING and ESTIMATION:

### TEST PLANNING:

Test planning is one of the activities that must be updated during all the project, due new information and situations arise. So one of the goals, is clearly identify possible risks to the project, so the project plann can be updated accordingly.
....

<hr>

### Test tools 

**Test management tool**: a tool that supports traceability, recording of incidents, or test scheduling and results.
**Catch and replay tool**: a tool to capture a user interaction with a system to evaluate it user interface.

 # IEEE 829 Overview - Standard test documentation

Test plan template:

## test plan identifier: 
Unique identifier to user for reference to this test plan

## references
list of documents that support this test plan document:

- project overview and description
- project plan 
- requirements and specification
- high level design overview and reference
- detailed reference and documentation
- methodology descrition and examples
- general, corporative and specifica standards that apply
- communication protocos used, its descrition, and examples.

## introduction aka "executive summary"
 Description, scope and goals of the test plan.
 
## Test items
 - List of the things that are going to be tested in this plan. 
 - Overview and descrition of the configuration management if one is used: version numbers, prototpes.
 - Squedule
 - Test and results to be reported and other deliverables (as for example metrics to be considered)

## Risks

Identification of risk areas for the software:

 - use and delivery with third party products.
 - new inteface versions
 - understanding of the project, and tools
 - system complexity
 - poorly documentation
 - requirements misunderstandings
 - lack of requirements or non defined situations
 
And system risks as:
 - impact on the client
 - compliement with standards, regulations and rules
 - safety
 - expected schedule
 
 ## features not to be tested
 List of things not to be tested and why
 
 ## test strategy
 - tools to be used (is it trainning needed?)
 - metrics to be collected and level of detail (mtbf, ciclomatic complexitiy, decision and coverage percentage...)
 - configuration management (version identification)
 - how many versions will be tested
 - software
 - hardware
 - combination of sw/hw
 - third party software or elements (COTS) (components of the shelf...)
 - regression testing
 - level of test defect severities
 
 ## item pass/fail criteria
 
 
 # test deliverables
  - test plan document
  - test cases
  - test design specification
  - tools & testware
  - static and dynamic testing
  - error logs and execution logs
  - problem reports and corrective actions
 
 
# test team
 - staff, trainning, roles and responsabilites.

the responsabilites for example are:
 - setting, definition and risk evaluation
 - selection of features to be testested and not to be tested
 - definition of the overall strategy
 - resolucion of conflics
 - planning of squedules
 - who takes the critical decisions.
 
 # approvals
 
 who can approve the complete process 
 
 # glossary, acronyms and abreviations


... to be done.


## ELECTRIC AND ELECTRONIC HARDWARE CONSIDERATIONS

### POINT TO DESIGN AND EVALUATE:

- PROTECTIVE EARTHING
- ELECTRIC STRENGH: Is defined as the maximum electric field strengh (V/mm) that a material can withstand without breaking down or experience failure in its insulation propierties. - In plain talking is when the electric field is so big that it actually brokes the material, throug a current/sparks... 

 The electric field value, actually is a function that depends on several factors, as temperaute, humidity (maximun electric field in inverse to the humidity) , also frequency of the electric field (the maximun electric field strengh decreases inversely to the frequency of the electric field).
 
 So any system must comply with the standard taking into account, its rated voltage, and the voltage that can be generated inside.
 
- INSULATION RESISTANCE
- LEAKAGE CURRENTS
- TOUCH CURRENTS


Electric Loads fault protection: Fuses, semicondutor fuses and circuits breakers are common protections methods. 

Also varistor, TVSs and crownbar circuits are common for overvoltage protections.

### CAPACITOR FAILURE MODES

- mechanical failure
- temperature cycling
- electrolitic failure (for electrolitic capacitors)
- capacitor life span (rated voltage, ripple current)

### SEMICONDUCTOR FAILURE MODES

- AVALACHE RELATED FAILURE
- THERMAL RUNAWAY
- THERMAL SECONDARY BREAKDOWN
- METALLIZATION FAILURE
- POLARITY REVERSALS
- ESD DAMAGE



## LIABILITY:

As far as the manufacturer complies with the required standards, it is assumed that it did not act negligently. Therefore, the legal consecuences in case of an issue, will be reduced to the minimum.

address any legal and regulatory requirements, such as FAA requirements for aviation. By setting a standard for which a system is required to be developed under, it forces the designers to stick to the requirements. The avionics industry has succeeded in producing standard methods for producing life-critical avionics software. Similar standards exist for automotive (ISO 26262), Medical (IEC 62304) and nuclear (IEC 61513) industries. The standard approach is to carefully code, inspect, document, test, verify and analyze the system. Another approach is to certify a production system, a compiler, and then generate the system's code from specifications. Another approach uses formal methods to generate proofs that the code meets requirements.[8] All of these approaches improve the software quality in safety-critical systems by testing or eliminating manual steps in the development process, because people make mistakes, and these mistakes are the most common cause of potential life-threatening errors.

FROM:  https://en.wikipedia.org/wiki/Safety-critical_system


https://www.mddionline.com/medical-device-safety-system-design-systematic-approach


JP Rankin, “Sneak Circuit Analysis,” 

http://klabs.org/DEI/References/design_guidelines/analysis_series/1314msfc.pdf


## TECHNIQUES FOR IMPROVEMENT

8D
5whys
RootCause Analysis
CAPA- Corrective Action / Preventive Actions -methodology to process improvement.  ref:L https://en.wikipedia.org/wiki/Corrective_and_preventive_action

SOP - Standard Operation Procedures - these are the documents developed by an organization that describes the procedures, checklist,
steps, and instructions to perform a certain task. the acronym also stands for Start of Procduction (watch out!)


### Learn from mistakes

https://aviation-safety.net/  

#### Mars Polar Lander

Issue with the imperial and internation metric units. :(

#### Hinderburg 

wip....


### Ford Pinto

#### Genesis Solar Wind Probe:
Went to Space, took samples of the solar wind, come back to Earth, but failed to open the parachutes : S
the MIB, resolved that the accelerometer sensor that was supposed to trigger the parachutes was mounted upside-down...  yahpp!
The reviews, didn't catch that mistake

ref: https://genesismission.jpl.nasa.gov/educate/kitchen/resource/factsheets/missionoverview.pdf

ref: https://en.wikipedia.org/wiki/Genesis_(spacecraft)

#### Asta railway accident
...

#### Lufthansa Flight 2904

...


### Mars rover pathfinder pitfail

... almost lost it... because a priority inversion pitfall... :S


### MARS CLIMATE OBSERVER. - fail in system verification: imperial vs metric units used. 

### Mariner1


### Boeing 787 Dreamliner 

In 2013, in the first year of service of the model Boeing 787 Dreamliner, several aircrafts suffered from thermal run-away from its
lithium-ion batteries.

The National Transportation Safety Board, issued a report pinpointed the causes of the issues
 - batteries manufactured processes that could introduce defects not detected in the inspection of the batteries.
 - Test that failed to consider the worst-case event of batteries failures
 - Failure to recognice the potencial hazard, dues failing to request testing methods for that event.
 
### Swissair 111 MD-11

 On 2 September 1998, the Swissair 111 MD-11 crashed into the Atlantic ocean outside of Halifax in Canada. This was the first aircraft with an entertainment system and when all passengers started to use it as the same time, it overheated. Experts believe that the crash was caused by faulty wiring in the cockpit after the entertainment system started to overheat
 
ref: https://en.wikipedia.org/wiki/Boeing_787_Dreamliner_battery_problems

ref: http://www.mlit.go.jp/jtsb/eng-air_report/JA804A.pdf

Examples of safety-critical systems[edit]
critical infrastructures monitoring systems[edit]
Circuit breaker
Emergency services dispatch systems (e-call)
Electricity generation, transmission and distribution
Fire alarm
Fire sprinkler
Fuse (electrical)
Fuse (hydraulic)
Telecommunications
Burner Control systems
Medicine[9][edit]
The technology requirements can go beyond avoidance of failure, and can even facilitate medical intensive care (which deals with healing patients), and also life support (which is for stabilizing patients).

Heart-lung machines
Mechanical ventilation systems
Infusion pumps and Insulin pumps
Radiation therapy machines
Robotic surgery machines
Defibrillator machines
Dialysis machines
Devices that electronically monitor vital functions (electrography; especially, electrocardiography, ECG or EKG, and electroencephalography, EEG)
Medical imaging devices (X ray, computerized tomography- CT or CAT, different magnetic resonance imaging- MRI- techniques, positron emission tomography- PET)
Nuclear engineering[10][edit]
Nuclear reactor control systems
Recreation[edit]
Amusement rides
Climbing equipment
Parachutes
SCUBA Equipment
Transport[edit]
Railway[11][edit]
Railway signalling and control systems
Platform detection to control train doors[12]
Automatic train stop[12]
Automotive[13][edit]
Airbag systems
Braking systems
Seat belts
Power Steering systems
Advanced driver-assistance systems (ADAS).
Electronic throttle control
Battery management system for hybrids and electric vehicles
Electric park brake
Shift by wire systems
Drive by wire systems
Park by wire
Aviation[14][edit]
Air traffic control systems
Avionics, particularly fly-by-wire systems
Radio navigation RAIM
Engine control systems
Aircrew life support systems
Flight planning to determine fuel requirements for a flight
Spaceflight[15][edit]
Human spaceflight vehicles
Rocket range launch safety systems
Launch vehicle safety
Crew rescue systems
Crew transfer systems
See also[edit]

https://www.crcpress.com/Design-and-Safety-Assessment-of-Critical-Systems/Bozzano-Villafiorita/p/book/9781439803318

Complex Safety-Critical Systems 
Dealing with Failures: A Short History of Safety Engineering 
The Role of Formal Methods 
A Case Study: Three Mile Island 
References

Dependability, Reliability, and Safety Assessment 
Concepts 
Classification of Faults
Fault Models 
Managing Faults
Fault Detection
Fault Prediction
Fault Tolerance
Fault Coverage 
Reliability Modeling
System Reliability

Techniques for Safety Assessment 
Hazard Analysis
Risk Analysis 
Risk Measures

Development of Safety-Critical Applications 
What Makes a System Complex 
What Makes the Development Complex
Measuring the Impact of Complexity 
From System to Process
A General Development Framework
Development Workflow
Testing Workflow
Safety Assessment Workflow
Certification Management Workflow
Project Management Workflow
Tool Support
Improving the Process: Maturity Models

Formal Methods for Safety Assessment 
Advantages of Formal Methods 
Formal Methods in the Development Process 
Problems and Limitations
History of Formal Methods
Formal Models and Specification
Formal Methods for Verification and Validation
Formal Safety Analysis
Industrial Applications of Formal Methods
Conclusions and Future Directions

Formal Methods for Certification 
Certification of Avionic Systems
So Many Standards, So Little Time
The ECSS System of Standards 
Avionics Reference Standards 
ARP 4754
ARP 4761 
DO-178B
The Case for the Safety Case 
Formal Methods and Certification 
References

Appendices:
The NuSMV Model Checker
The FSAP Safety Analysis Platform
Some Regulatory Bodies and Regulations
Index


MORE TOPICS TO CHECK.
1.	Quantitative Methods
System Safety Fundamentals
Set/Probability Theories
Bernoulli Process and Binomial Distribution
Poisson Analysis
Series/Parallel Networks
Fault Tree Analysis
Event Tree Approach
Boolean Algebra
Failure Data Analysis
Decision Theory
Risk Ranking
2.	Management
System and System Safety Life Cycle
Hazard Analysis Techniques including
	Logic/Change Analysis
	Energy/Trace
	FHA/FMECA
	FTA
	SCA
Hazard Analysis Types including
	PHA/SSHA, SHA and O & SHA
System Safety Order of Precedence
Amelioration
System Safety Management Tasks
Objectives/Life Cycles
System Safety Program Plan
Types of Risks/Assumption of Risks

### Interesting links

http://www.rvs.uni-bielefeld.de/research/WBA/
www.rvs.uni-bielefeld.de/publications/compendium/
https://www.ntsb.gov/investigations/AccidentReports/Pages/AccidentReports.aspx


ACRONYMS:

UAT - User Acceptance Test

COTS -Comertial Of The Shelcf (software, hardware or device)

DUT - Device Under Test

TDD - Test Driven Development.

sloc - source lines of code.

BER - byte error Rate

STAMP - Systems Theoretic Accident Model & Processes

SLA - Service Level Agreement. (to check the availability of the system).

HA - High Availability (system)

ETR - Estimated Time for Repair 

SOTIF - Safety of the Intended Functionality

FMEA - Failure Mode Effect and Analysis.

ISO 9126 - Software Product Quality.

SIL - SOFTWARE IN THE LOOP

SIL - SAFETY INTEGRITY LEVEL

SPOF - SINGLE POINT OF FAILURE

HIL - HARDWARE IN THE LOOP

CEN - European Comitee for Standarizacion 

CENELEC - European Committee for electrotechnical Standarization 

IEC - International Electrotechnical Commision

ISO - Internationale Organization for Standarization

SRS - System requirements specification

SQI - Software Quality Institute.

SPICE - International Standard for Software Process Assesment.

MIB - Mishap Investigation Board

SOP - Standard Operation Procedures

WKI - Working Instructions

ETSI

ITU

TELOS - Technical, Economic, Legal (liability), Operational and Scheduling. Refers to the five areas of feasibility

RAMS - Reliability, Availability, Maintainability and Safety 


## Draft on GENERAL PROJECT RISKS

MANAGEMENT 

1. The project management fail to support the project.
The managements fails to support the project. Someone must rise and be up to the task. 

2. Management is disregarded with the project.
The monitoring of the project is not followed. 

3. Management turnover disrupts the project.
A key management position on the project is empty.

4. Management underestimate the project.
The project needs more attention and support than estimated.

5. Failure to follow methodology 
Management don't follow the SOP (Standard Organization Procedures). Watch out: Lack of SOP (Standard Organization Procedures) does not comply with ISO 9001-

6. Lack of management or control 
A lack of project management should be documented as a risk. For example, if resource constraints cause the project to skip certain project management best practices. Watch out: Lack of SOP (Standard Organization Procedures) does not comply with ISO 9001-

7. Errors in key project management processes 
Errors in project management such as schedule errors, inaccurate objetives, inadequate decisions, or lack to manage the project team.

8. Management procedures overhead
Too much procedures or tasks, may cause a significant toll or over-head on the project. It may be for example, required administrative
procedures that need to much time, or documentation/paper-work or other limited resources.

DEFINITION and GOALS OF THE PROJECT 

8. Scope and goals of the project are poor defined 
The overall goal of the project is poorly defined.

9. Scope runaway
Uncontrolled changes and continuous growth of scope. For example: Cabbage mechanical calculation machine. This can be
also result of an energetic customer, that keeps on asking for more functions.

10. Over-design: Chase of perfection inflates scope 
The project team add their own features that aren't in requirements or change requests. 

11. Estimations are not accurate 
Inaccurate estimations are a common project risk. For example: the estimated effort needed for the project to succed.

12. Dependencies are inaccurate 
Dependencies impact the project schedule and costs. A wrong dependencies tree, directly impact on the critical path of the
project(Gantt).

13. Activities are missing from scope 
Required activities are missing or are not took into account for the scope definition and project planning.


PLANNING 

14. Forecasts and estimations are inaccurate, and/or underestimated.

16. Unrealistic planning
the planning and time-line are way too optimistic.

15. Monopoly dependency
The project depends on only one key supplier or partner. This is a strategic short-come that should be avoided.
 
 
COMMUNICATIONS. 

15. Project team misunderstand requirements 

When requirements are misinterpreted or misunderstood by the project team. There is a significant gap between expectations, requirements and project planning. 

16. Communication overhead 

The communication effort needed for the project succeed is out of the common. 

17. Under communication 

key people is not being informed and missing information. this situation has many risks. 

18. Inaccurate expectations 

End-users or stack-holders or involved people don't understand the product real capabilities.

19. Confusion / poor communication / poor understanding.

key people who must be involved can not grasp the meaning or implications of the project communications.

20. Communication latency: Too much time for an answer or decision.

When requesting any information or data critical to the project, an answer that takes too much time my stall the project and jeopardize it. For example: a requirement clarifications, a technical review, or a law compliance consultation...  (The approval of the boss is needed, and he just went on vacations....) 

REQUIREMENTS

21. Requirements fail to align with other systems 

The requirements fail to align with other systems (e.g. they duplicate functionality, or block or monopolize a common communication system with another component/module/... ).

22. Requirements have compliance issues 

If you have any doubt that requirements comply with the law list it as a risk. 

23. Requirements are ambiguous 
Requirements are unclear and open to interpretation. 

24. Requirements are low quality 

Requirements aren't fit for purpose. Eg. a 1GH dual-core processor is requested, but it should actually specify this in terms
of MFLOPS or MIPS, or data-prosseing throughput.

25. Requirements are incomplete 

You can spot obvious (or not) holes in the requirements. 

26. Requirements gathering.
Poor communication between client, or stakeholders might result in that the requirements fail to reflect its expectation.

27. Requirements runaway
Requirements constantly increase its number, and the requested features may not be implemented in the allocated time for the project.



SYSTEM ARCHITECTURE and DESIGN

28. Architecture, design or technical solution lacks flexibility 

The architecture is incapable of supporting change requests and needs to be reworked. For example: in a computer system a Round-robin
schecdule is a very neat architecture, and really good in some ways: as predictability and time estimation, but if lacks flexibility
when the system needs to include new functionality.

29. Architecture or design is not fit for purpose 

The architecture or technical solution is low quality. Don't use anti-patterns.

30. Architecture or design or technical solution is not feasible .

The architecture is impossible to implement, excessively costly or doesn't support the requirements. For example: the data-processing
requirements are impossible to achieve for the requested system.

31. Architecture or design fails peer review 

It's a good idea to have peers or architectural experts that review your designs. 

LEADERSHIP, DECISIONS AND RESOLUTIONS 

32. Decision delays impact project 

Establish guidelines for decision turnaround time (as a max answer time-limit). Identify the risk that guidelines will be exceeded. 

33. Decisions are ambiguous 

People may have a tendency to make decisions that are intentionally ambiguous (a responsibility avoidance technique), as 
for example: the resolution to optimice two parameters that are in opposition (For example: I want to do a lot with very little and very fast). This can be identified as a risk and managed. 

34. Decisions are low quality 

Decisions aren't fit for purpose. 

35. Decisions are incomplete 

Issue resolutions that don't address the issue or create more issues. 

SUPPLIERS

36. Suppliers fail to meet the needed quantities

37. Suppliers fail to meet the expected quality.

38. Suppliers don't meet a fitting price for the project.

39. Supply time don't meet the timeline needs for the project.


## list of possible technical issues with general elements.
 
1. Accuracy/precission of the element don't achieve the design goals

2. Aging of the element don't achieve the design goals

3. Robustness of the element don't achieve the design goals

4. reliability of the element is doesn't achieve the design goals

5. sensibility of the component doesn't achieve the design goals

6. working range of the component is not enought for the design goals

7. elements wears-out, design life or aging don't achieve the design goals

8. element doesn't meet design goals under defined enviroment or expected work conditions.

9. thermal performance don't achieve the design goals. (thermal stress, cooling issues or expasion joints needed)

10. mechanical performance don't achieve the design goals. (fatigue, yiel and deformations, max loads, resilience, rupture strength, rupture stress, vibration, protection (IP), corrosion, wear, noises, geometries, tolerances, unfitting materials, materials interfaces,  safety margins ... there are several factors to take into account).

11. dielectric isolation of components fails

12. EMC problems that don't achieve standards.

13. Weldings, traces, reflectios, noise, wires don't achieve the performance expectations from an electrical point of vie.

14. Supplied elements are out of the expected/negotiated specs.

15. critical element have protection elements or rebundant backup elements


## list of recomended battery tests

- Thermal and enviromental testing
- vibrations
- shocks, and mechanical testing
- External/internal shotcircuit
- battery life cycle/ recharges cicles /charge-discharge cicles
- overcharge
- forced discharge.
- protection circuits
- abuse use test
- compliance with safety standards as UL, ANSI, CSA and IEC, NRTL, ANSI, UL, IEEE  standards.

ref: https://batteryuniversity.com/learn/article/battery_testing_and_safety

ref: https://www.energy.gov/sites/prod/files/2014/05/f15/APR13_Energy_Storage_e_IV_Battery_Tstg_Design_2.pdf

ref: https://www.diva-portal.org/smash/get/diva2:716986/FULLTEXT01.pdf

ref: https://www.mpoweruk.com/testing.htm

https://blog.nxp.com/automotive/three-things-to-know-about-functional-safety


## list of possible issues with lithium-batteries

Lithium batteries may suffer for thermal-runaway and/or cells ruptures in case of overheating or overcharging. In extreame cases can lead to fire and/or explosions. This has to be consider as the wort-case scenario, and prepared and tested for detect and react to it.

Thus is recomend to use a baterie management system (BMU). Also short-circuit proctection

Viewed in: Samsung Galaxie Note 7, Boeing 787 Dreamliner.



https://pascal.computer.org/sev_display/index.action

**Real-time**. (1) problem, system, or application that is concurrent and has timing constraints whereby incoming events must be processed within a given timeframe (ISO/IEC/IEEE 24765:2017 Systems and software engineering-Vocabulary) (2) pertaining to a system or mode of operation in which computation is performed during the actual time that an external process occurs, in order that the computation results can be used to control, monitor, or respond in a timely manner to the external process (ISO/IEC/IEEE 24765:2017 Systems and software engineering-Vocabulary)

**Latency**. (1) time interval between the instant at which an instruction control unit issues a call for data and the instant at which the transfer of data is started (ISO/IEC/IEEE 24765:2017 Systems and software engineering-Vocabulary)." Copyright©, 2018, IEEE. Used by permission."

**Throughput**. (1) amount of work that can be performed by a computer system or component in a given period of time (ISO/IEC/IEEE 24765:2017 Systems and software engineering-Vocabulary) (2) rate (i.e., the average number per time unit with respect to the rating interval) of all tasks of a task type submitted to the SUT (ISO/IEC 14756:1999 Information technology -- Measurement and rating of performance of computer-based software systems, 4.24) Note: Usually throughput is defined by the rate of terminated tasks during a period of time. " Copyright©, 2018, IEEE. Used by permission."

**Test Plan** (1) document that describes the technical and management approach to be followed to test a system or component (IEEE 1012-2017 IEEE Standard for System, Software, and Hardware Verification and Validation, 3.1) (2) document describing the scope, approach, resources, and schedule of intended testing activities (IEEE 1012-2017 IEEE Standard for System, Software, and Hardware Verification and Validation) (ISO/IEC 25051:2014 Software engineering -- Software product Quality Requirements and Evaluation (SQuaRE) -- Requirements for quality of Ready to Use Software Product (RUSP) and instructions for testing, 4.1) (ISO/IEC 25062:2006 Software engineering -- Software product Quality Requirements and Evaluation (SQuaRE) -- Common Industry Format (CIF) for usability test reports, 4.1) (3) plan that establishes detailed requirements, criteria, general methodology, responsibilities, and general planning for test and evaluation of a system (ISO/IEC 2382:2015, Information technology -- Vocabulary) (4) detailed description of test objectives to be achieved and the means and schedule for achieving them, organized to coordinate testing activities for some test item or set of test items (ISO/IEC/IEEE 29119-1:2013 Software and systems engineering--Software testing--Part 1: Concepts and definitions, 4.75) Example: a project test plan (also known as a master test plan) that encompasses all testing activities on the project; further detail of particular test activities can be defined in one or more test sub-process plans (i.e. a system test plan or a performance test plan) Note: It identifies test items, the features to be tested, the testing tasks, who will do each task, and any risks requiring contingency planning. Typical contents identify the items to be tested, tasks to be performed, responsibilities, schedules, and required resources for the testing activity. " Copyright©, 2018, IEEE. Used by permission."


software managemente tools

https://trac.edgewall.org/

redmine
jira

requirements

DOORS



https://en.wikipedia.org/wiki/Hazard_and_operability_study

http://www.hse.gov.uk/research/hsl_pdf/2005/hsl0558.pdf

http://www.planning.nsw.gov.au/Policy-and-Legislation/~/media/C9CC2DA7E9B947C78C7C1355AD5B4B15.ashx

https://cdn.auckland.ac.nz/assets/ecm/documents/example-of-hazop.pdf

https://www.ntsb.gov/investigations/AccidentReports/Pages/AccidentReports.aspx

https://www.easa.europa.eu/easa-and-you/safety-management

https://en.wikipedia.org/wiki/Fail-safe

https://blog.nxp.com/automotive/automotive-functional-safety-the-evolution-of-fail-safe-to-fail-operational-architecture

https://en.wikipedia.org/wiki/Fault_tolerance

https://www.faa.gov/regulations_policies/handbooks_manuals/aviation/risk_management/ss_handbook/media/app_h_1200.pdf

https://www.its.bldrdoc.gov/fs-1037/dir-015/_2151.htm

https://blog.nxp.com/automotive/three-things-to-know-about-functional-safety


BIBLIOGRAPHY & References - TECHNICAL BOOKS & PAPERS:

- "Reliability Engineering Handbook",Kececioglu,Dimitri; Prentice-Hall, 1991.
- "A brief introduction to C++’s model for type- and resource-safety", B. Stroustrup, Herb Sutter, and G. Dos Reis.
- "Exception-Safety in Generic Components", D. Abrahams. https://www.boost.org/community/exception_safety.html
- " C++ Coding Standards", H. Sutter and A. Alexandrescu. Addison-Wesley 2005.
- "Safeware: System Safety and Computers", Nancy G. Leveson
- "Safety Critical Computer Systems", Neil Storey
- "Test Driven Development: by example", Kent Beck
- "Clean Code: A handbook of agile software craftmanship", Robert Martin
- "Software system safety Handbook- A technical & managerila team approach", Joint System Safety Commitee
- "Embedded Software Development for Safety-Critical Systems", Chris Hobbs
- "Risk assessment theory, methods and applications", Rausand
- "Orbiter Structural Design Verification" P.C. Glynn and T.L. Moser
- "Strengh Integrity of the Space Shuttle Orbiter Tiles", T.L. Moser and W.C. Schneider
- "Reliability Engineering of the Space Shuttle: Lessons Learned" T.L. Moser
- "Structural Load Challenges During Space Shuttle Development", A.C. Mackey and R.E. Gatto
- "Comparision of Bus architectures for Safety Critical Embedded Systems", NASNCR-2003-2 John Rushby, https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/20030032956.pdf
- "Second Edition of System Reliability Theory: Models, Statistical Methods, and Applications".
 # FMEA: Failure Mode and Effects Analysis
 
 Is one of the earliest approach to a systematic realiability analysis, that of course includes risk assesment.
  
 FMEA is a methodology and a structured systematic approach that aims to predict, anticipate and asses the possible failures of a system in its design phase, by means of identifying all possible failure causes and its effects in the system design, manufacture, production or operation.
 
 FMEA studies are very interesting due the advantage of identifing and preventing a failure early in the development or in the life of a product. As the discovering and solving failures in later stages of a system development increase significantly the cost of solving them.
 
 The leading standards for FMEA are the IEC 60812 and MIL 1629
 
Steps on FMEA:

- Assemble of the FMEA team
- Definition of the system, product or process
- Definition of the functions and requirements (and severity ranking of them)
- list of the potencial failures and prevention controls through occurrence ranking
- list of the effects of the failure modes
- identification of the causes of the failure modes
- Definition of controls, actions and test
- RPN (Risk Priority Number) calculation

 ref: https://quality-one.com/fmea/


Concetps in FMEA:

- **Function**: activity, or goal, or task in the system, device or element, that is expected to be done.
- **Failure**: when the given element fails to achieve its goal, task or expected funtionality.
- **failure mode**: it is the HOW a elemenent get to the failure result.
- **failure potential**: the posible consecuencies that might result due to a failure, in a direct or indirect way.
- **cause**: is the reason, that results in a failure as an effect. The ultimate reason is refered as "root-cause".


ARTICLES:
http://www.robertfeldt.net/publications/shahrokni_2013_sysrev_robustness.pdf
https://uwaterloo.ca/embedded-software-group/people-profiles/sebastian-fischmeister



# SECURITY

## A Security mindset - 

 A system designer must use a security mindset- this means to identify weak points in the system under design and address security at all levels of the system. Security is designed in the system, not an afterthought, the later is a bad design practice. 
 
kerckhoff's principle: a crypto system should be secure even if everything about the system is known, except the key.

Security through obscurity is not security... <- security through obscurity is not really a good practice, although it has been used, for example with the use of native american languajes in WWII. 

## secure points to consider.

The following points should be considered:

- confidentiality: unauthorized individuals can not read the protected data.
- integrity: the system or its data has not been modified without authorization
- authetication: is possible to positive identify the source of messages, files, commands or users as an aproved source.
- authorization: the system has a access control policy implemented
- non-repudiation: a user or a system cannot deny that they send a message, file, command..


## Secure software updates 

the device must connect to a secure server, and have a pair of secrets keys. the private key is kept in the server

So a possible way to implement this is:

1- Get a new sw image from a secure source (download the image)
2- Calculate hash, crc, mac and signature values
3- encript it all with the server key
4- send to the device the binary package
5- the device unencrypts the binary package
3 -check the hash, crc, mac and signature values
 - if ok update software and log updat event
 - if nok ok reject softeware an log security event
 
 so the update server and the system device, must share a secret key between them. 
 
Other mechanims desired for a resiliat and robust system are:

- update record: keep a log of update sw events, this will provide a useful information source in case to analyze tampering attacks or attemps, also identify sw versions, sources, times...
- version management: the device will record the os versions and application versions. 
- atomic updates: the update only will run after checking all the package has been recevided and checked
- automatic rollback: in case of failure with the latest firmware/swupdate, the device will revert to the previous version of the sw.+
- no disruption: a device or system will keep on running or executing its functions during the image or new sw transfer
- suppor for sleeping devices: devices sleeping or in low power mode should also be capable of sw updating.
- sender verification: check and secure the source of the sw provider
- encrypt communications: use of secure comunications
- planning the updates: the updates can take place under a command, or the devices can request it at given or suitable times.


implementation tips:

 This strategy can be implemented in many ways, but there are ways to do it in a simple maner. 
 
 for example the sw image gather and with secure comunciations can be achieved easly using a secure ftp service. 
 the automatinc rollback, can be done using two memory partitions, one keeps the previous sw image and the second the lates uploaded sw image, in case of catastrophic behavior of the image, the system can jump to use the other partition in the memory, so then geting the previous sw.

### secure libraries

https://github.com/intel/safestringlib

secure file systems:

 - https://en.wikipedia.org/wiki/Pretty_Good_Privacy
 - https://ecryptfs.org/about.html
