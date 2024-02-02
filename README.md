# Claw Machine

This project tries to find out what a real claw machine entails, be either a big one to unload cargo ships or a small one that one may find at a festival. "What challenges does a claw machine face?", "How do you go about to solve them?", basically, "How _do_ it work?". These and many other were the questions we had in mind when we decided to start to work on this project.

Due to our limited budget, we built an even limited one which, unfortunatly, is not fit for harbor work. Nor festival work. But we believe that we learned a lot anyway.

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
- Progetti stampanti 3D custom
- [Claw Grabber](https://www.thingiverse.com/thing:4826548/files)

### Software

- [Code Composer Studio](https://www.ti.com/tool/CCSTUDIO) Integrated Development Environment (IDE)
- [MSP432 DriverLib](https://www.ti.com/tool/download/SIMPLELINK-MSP432-SDK/3.40.01.02)
- UART drivers lib

# Project layout

```
├── README.md
├── readme_assets
│    ├── images                # Images used in the readme
│    └── STL                   # STLs to 3D print to mount circuit boards on the machine
├── source
│    ├── Bluetooth             # Manages bluetooth connection
│    ├── motors                # CMake toolchains for cross-compiling
│    ├── joystick              # ImmortalThreads runtime library
│    ├── screen                # ImmortalThreads runtime library
│    └── ...                   # Test applications
└── powerpoint
```

# Getting started

### Setting up the hardware

Connect the various components as follows:

- Connect the **BoosterPack MKII** to the **MSP432P401R Launchpad**.
- Bluetooth setup
  - Connect the **HC-05**'s wires to the GND and 5V for power and to PIN 3.2(as the reciever, RXD) and PIN 3.3(as the transmitter, TXD), re of the board that is mounted on the machine
  - Connect the **HC-06**'s wires to the GND and 5V for power and to PIN 3.2(as the reciever, RXD) and PIN 3.3(as the transmitter, TXD) of the board that will function as a hand-held controller
- Connect the MOTORS
- Connect the CLAW

### Setting up the software

1. Clone this GitHub repo by using:

```sh
git clone TODO
```

2. Open the project in **Code Composer Studio**.
3. Go to: _Project → Properties → Build → Arm Compiler → Include Options_ and add the _source_ directory located in _simplelink_msp432p4_sdk_3_40_01_02/_
4. Go to: _Project → Properties → Build → Arm Linker → File Search Path_ and add:
   - _msp432p4xx_driverlib.lib_ directory located in _[..]/source/ti/devices/msp432p4xx/driverlib/ccs/_
   - _grlib.a_ located in _[..]/source/ti/grlib/lib/ccs/m4f/_
5. Uart driver lib TODO @Sara
6. Build and run the project. The Launchpad should now be displaying the graphics.

# How to burn(?)

https://electronics.stackexchange.com/questions/188107/burn-code-using-code-composer-studio

# User guide

1. Follow the instruction displayed on the screen.
2. keep in mind this:
   [TODO Finite State Machine]
3. have fun!

# Link to powerpoint and Youtube video

- Youtube [video](todo)
- PowerPoint [slides](todo)

# Team members

The project was a developed in a team and the code was divided into many different areas (Claw, Communications, Graphics, Hardware, ...); each member concentrated therefore only on certain aspects of the project.

- Luca Podavini (Leader)
  - Contributed to the creation of the physical machine and of it's control
- Alberto Cimmino
  - Contributed to the graphics and the comunication, be either the Bluetooth one or the GitHub one and to the tests
- Angela Hu
  - Contributed to the control of the machine thanks to the read of the Booster pack features
- Sara Tait
  - Contributed to the comunication, the control and the tests
