**EMBEDDED SYSTEM**: An embedded system is a system, that combines software and hardware, although is also common that they have some  kind of HMI (human machine interface). Embedded systems have fixed capabilities but are programmable, and they are designed for a specific function or functions. 
Examples are: industrial equipments and machines, agricultural, automotive, medical, aeronautical or space systems, telecomunication systems or even household apliances, toys or vending machines...

**SAFETY**: Is the propierty of a system that evaluates the risk of the ocurrence of an accident.

**FUNCTIONAL SAFETY** Is the safety of a system that correspond to the correct actions acording to the system inputs, it also includes
detection of potential dangerous states, and activation of protective, corrective or mitigation measures.

Functional safety implies active measures, as an example is the airbag systems in vehicles, when a crash is detected, a safety system
is triggered. On the other hand, a helmet that protects the driver, is a passive system; passive systems are not functional safety.

The leading standard for functional safety is the IEC 61508

**SECURITY**: Is the propierty of a system that evaluates its ability to deal with malicious actions or attacks.

Take into account, that there is a significance difference between the concepts of safety and security, both terms account protection against a damage, but security implies a malicious or intended action to do a damage, while safete relates to an unintended situation.

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
- Safety
- Security 

**FAULT TOLERANT SYSTEM**: Is a system that performs correctly, although might have some errors in it. Usually this is
achieved by means of repeated computations, monitoring data, and redundant systems.
