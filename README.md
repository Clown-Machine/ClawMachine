# Claw Machine

This project aims at helping unload small weights from some things, or grab some candies, ....

# Requirements

### Hardware

To use this project, you will need the following hardware:

- Two Texas Instruments MSP432P401R microcontroller
- One [Educational BoosterPack MKII](https://www.ti.com/tool/BOOSTXL-EDUMKII)
- Bluetooth modules:
  - HC-05
  - HC-06
- Jumper wires
- Barre di metallo
- Gancio
- Filo per gancio
- Stepper motors
- Servo motor
- Ruote

### Software

- [Code Composer Studio](https://www.ti.com/tool/CCSTUDIO) Integrated Development Environment (IDE)
- driverlib
  - graphic lib
- UART drivers lib

# Project layout

```

├── README.md
├── source
│    ├── motors                # CMake toolchains for cross-compiling
│    ├── bluetooth             # ImmortalThreads runtime library
│    ├── joystick              # ImmortalThreads runtime library
│    ├── screen                # ImmortalThreads runtime library
│    └── ...                   # Test applications
└── powerpoint
```

# Getting started

### Setting up the hardware

Connect the various components as follows:

- Connect the BoosterPack MKII to the MSP432P401R Launchpad.
- Connect the MOTORS
- Connect the CLAW
- Connect the BLUETOOTH
- Connect the Bluetooth module wires to the GND and 3.3V for power and to PIN 3.2 and PIN 3.3 for data transmitting and receiving.

### Setting up the software

1. Clone this GitHub repo by using:

```sh
git clone TODO
```

2. Open the project in **Code Composer Studio**.
3. Go to: _Project → Properties → Build → Arm Compiler → Include Options_ and add the _source_ directory located in _simplelink_msp432p4_sdk_3_40_01_02/_
4. Go to: _Project → Properties → Build → Arm Linker → File Search Path_ and add:
   - _msp432p4xx\_**dreivelib**.lib_ directory located in _[..]/source/ti/devices/msp432p4xx/driverlib/ccs/_
   - _grlib.a_ located in _[..]/source/ti/grlib/lib/ccs/m4f/_
5. Build and run the project. The Launchpad should now be displaying the graphics.

# How to burn(?)

# User guide

è colpicato

# Link to powerpoint and Youtube video

- Youtube [video](todo)
- PowerPoint [slides](todo)

# Team members

The project was a developed in a team and the code was divided into many different areas (Claw, Communications, Graphics, Hardware, ...); each member concentrated therefore only on certain aspects of the project.

- Luca Podavini (Leader)
  - Contributed to ...
- Alberto Cimmino
  - Contributed to ...
- Angela Hu
  - Contributed to ...
- Sara Tait
  - Contributed to ...
