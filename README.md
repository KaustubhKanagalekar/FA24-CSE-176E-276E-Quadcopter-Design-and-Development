Quadcopters designed by Kaustubh Kanagalekar and Alexander Haken

## Introduction

In this project class, we were challenged to design a printed circuit board (PCB) quadcopter and program it using Arduino software in order to achieve flight. 

The class was broken into multiple smaller milestones- PCB design for electronic components, PCB design for quadcopter, sensor filtering and calibration, Proportional, Integral, Derivative (PID) tuning, PCB quadcopter assembly, and flight. As we were designing the PCB quadcopter using computer software, we were provided with a test flight control board (FCB) that we could work on concurrently. In case our PCB quadcopter wouldn’t work as intended, we could use the FCB for demonstration purposes. 

The skills that we learned from the class were-
1. PCB design and fabrication
2. Embedded systems programming 
3. Control theory and sensor calibration 

## Electronic Design

Using Fusion 360, we were tasked with designing the following components from scratch- 

1. Resistor (0805 0Ohm) 
2. Red LED 
3. MOSFET (N-channel) 
4. Inertial measurement unit (IMU) (LSM6DSOXTR 6-Axis) 

We referenced the data sheets for each component online and extensively studied the footprints. 
More specifically, we utilised the footprints tab in Fusion 360 to add SMD pads, silkscreens, keepouts, etc. to accurately replicate the dimensions. 

We also took advantage of the automated building tool at times to accurately build the electronic components.  

{insert pictures of footprints} 

After creating the footprints, we built symbols for each electronic component using the standard IEEE styling conventions using the symbols tab. 

Finally, we connected the footprints and the symbols of each component in the components tab so that we could use them in our quadcopter schematic and design. 

We ensured that we met all the necessary guidelines and requirements set forth by the PCB manufacturer and instructor in our designs.  

## Quadcopter Design 

We were tasked with creating the schematic for the PCB quadcopter. In addition to our custom made components, we were also provided with additional parts from the instructor. 
The quadcopter had multiple smaller sketches- 
1. The microcontroller connections  
2. Bootloader 
3. IMU 
4. Debug/Rescue Header 
5. Motor Driver 
6. Netbridge and power supply 

### Microcontroller connections
We connected various pins and components to the microcontroller. The most significant connection we had was the balun (used for allowing balanced and unbalanced lines to be interfaced without major disturbances in impedances). This was significant as it allowed us to securely connect the antenna in our design. We were deliberate in our antenna placement as incorrect placements would yield spotty data transmission, and the quadcopter may not be able to fly.  

### Bootloader 
The primary objective of including the bootloader was  to load code to the microcontroller. Pins were connected to the microcontroller from the bootloader. 

### IMU 
We established a communication protocol with the microcontroller using I2C (Inter-Integrated Circuit). We incorporated two wires (Serial Data Line and Serial Clock Line) to transmit data between the microcontroller and IMU. 

### Debug/Rescue Header 
The rescue header was incorporated in order to help with debugging signals during testing. We also added a IMU reuse header in case our soldered IMU had issues. 

### Motor Driver 
We built four copies of the motor driver sketch as there were four motors driving the quadcopter. We included motor pads, mosfets, and a diode in the sketch. More importantly, we also included a decoupling capacitor to help absorb switching noise from the motors.

### Netbridge and Power Supply 
We designed a low-dropout voltage regulator in the schematic to provide a stable power output of 3V to the motors. This was because the batteries were providing power ranging from 4V to 5V. We had two power rails: An unregulated power rail (called VBAT) that provides power to the motors and input of the voltage regulator and is driven directly by the battery, and a regulated supply driven by the voltage regulator (called 3V) 

A netbridge was also created in order to electrically connect two nets in a schematic while keeping the nets separate in schematic . This was done to connect digital ground (BAT_GND) to regular ground. 