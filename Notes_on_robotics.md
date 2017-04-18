# NOTES ON ROBOTICS

# DEFINITION:
In the production/industrial context, a Robot, is a reprogrammable machine that can be multifunctional and do diverse specified tasks.

The word "Robot", was coined by the Czech novelist Karel Capek, and it refers to a "servant" or "slave". 

Robotics engineering is a branch of engineering that englobe mechanical, electrical, electronics, control theory, measurement systems (sensor theory, filtering, amplification ...), programming and even artificial intelligence. 

# ROBOT ELEMENTS

## Mechanical Design:

 Mechanical structure, linkage, joins, mechanical design (stresses, forces, critical sections, fatigue limits, inertias, deformations, elasticity, gears/reductions, grips,  ... )

## Sensors:

Accelerometers, gyroscopes, pressure, forces, torques, tilt, distance, proximity, optics, cameras, 3D vision, computer vision, infrared ... 
If needed apply amplification, filters on hardware, software, FIR, IIR, Kalman .... or even sensor fusion.

## Actuators:

 - Servo motors
 - Brushless motor
 - Synchronous motors
 - Steppers motors
 - Reluctance motors
 - AC motor
 - Hydraulic motor
 - Pneumatic motor
 - Pneumatic cylinders

## Control:

Good control design is mandatory, for that you have to apply control theory. You have to process the sensor data, and feed to the actuators, until the specified tasks are done.

Also other techniques should be used, planning trajectory, or other algorithms are commonly used.

## Electronics:

 Most of the system that is not mechanical, will be developed into electronics, that means, the control systems, with a CPU, and memory systems, the design and amplification of sensors, and also telecommunication and interface systems.

# APPLICATIONS

 - Material Handling
 - Material transfer
 - Machine loading and/or unloading
 - Spot welding / Continuous arc welding
 - Spray painting and coating
 - Assembly
 - Inspections
 - Repetitive tasks for humans
 - Hazard tasks for humans (harmful environments, as contaminated places (nuclear plants), or with extreme conditions (blast furnaces))
 - Pnp (pick and place)

# HISTORICAL EVOLUTION
Robots inherits its design basically from the evolution of CNC systems (Computer Numeric Control), and also from mechanical handling material devices as cranes.

 ![Dock_Crane](https://github.com/sergiocollado/potpourri/blob/master/image/mechanical_grua_de_pico_de_pato_crane.jpg)


# Top robot companies in the world – robot install base worldwide

 - Fanuc / 400,000.
 - Yaskawa / 300,000.
 - ABB / 300,000.
 - Kawasaki / 110,000.
 - Nachi / 100,000.
 - Kuka / 80,000.
 - Denso / 80,000.
 - Mitsubishi / 70,000.

# Standards 
**ISO/TC 299**
**Robotics**

IEC/CD 80601-2-77 [Under development]
Medical electrical equipment -- Part 2-77: Particular requirements for the basic safety and essential performance of medical robots for surgery

IEC/CD 80601-2-78 [Under development]
Medical electrical equipment -- Part 2-78: Particular requirements for the basic safety and essential performance of medical robots for rehabilitation, compensation or alleviation of disease, injury or disability

IEC/DTR 60601-4-1 [Under development]
Medical electrical equipment -- Part 4-1: Guidance and interpretation -- Medical electrical equipment and medical electrical systems employing a degree of autonomy

ISO 10218-1:2011
Robots and robotic devices -- Safety requirements for industrial robots -- Part 1: Robots

ISO 10218-2:2011
Robots and robotic devices -- Safety requirements for industrial robots -- Part 2: Robot systems and integration

ISO 11593:1996
Manipulating industrial robots -- Automatic end effector exchange systems -- Vocabulary and presentation of characteristics

ISO 13482:2014
Robots and robotic devices -- Safety requirements for personal care robots

ISO 14539:2000
Manipulating industrial robots -- Object handling with grasp-type grippers -- Vocabulary and presentation of characteristics

ISO 18646-1:2016
Robotics -- Performance criteria and related test methods for service robots -- Part 1: Locomotion for wheeled robots

ISO 19649:2017
Mobile robots -- Vocabulary

ISO 8373:2012
Robots and robotic devices -- Vocabulary

ISO 9283:1998
Manipulating industrial robots -- Performance criteria and related test methods

ISO 9409-1:2004
Manipulating industrial robots -- Mechanical interfaces -- Part 1: Plates

ISO 9409-2:2002
Manipulating industrial robots -- Mechanical interfaces -- Part 2: Shafts

ISO 9787:2013
Robots and robotic devices -- Coordinate systems and motion nomenclatures

ISO 9946:1999
Manipulating industrial robots -- Presentation of characteristics

ISO/AWI 22166-1 [Under development]
Robotics -- Part 1: Modularity for service robots -- Part 1: General requirements

ISO/CD 18646-2 [Under development]
Robotics -- Performance criteria and related test methods for service robots -- Part 2: Navigation

ISO/CD TR 23482-1 [Under development]
Robotics -- Application of ISO 13482 -- Part 1: Safety-related test methods

ISO/CD TR 23482-2 [Under development]
Robotics -- Application of ISO 13482 -- Part 2: Application guide

ISO/NP TR 20218-1 [Under development]
Robots and robotic devices -- Safety requirements for industrial robots -- Part 1: Industrial robot system end of arm tooling (end-effector)
	
ISO/NP TR 20218-2 [Under development]
Robots and robotic devices -- Safety requirements for industrial robots -- Part 2: Industrial robot system manual load stations

ISO/TR 13309:1995
Manipulating industrial robots -- Informative guide on test equipment and metrology methods of operation for robot performance evaluation in accordance with ISO 9283

ISO/TS 15066:2016
Robots and robotic devices -- Collaborative robots
