<h1 align="center">Claw Machine</h1>
<p align="center">
  <img src="readme_assets/logo.png" width="325" height="240" alt="logo">
</p>

---

This project tries to find out what a real claw machine entails, be either a big one to unload cargo ships or a small one that one may find at a festival.<br> "What challenges does a claw machine face?", "How do you go about to solve them?", basically, "How _does_ it work?".
These and many other were the questions we had in mind when we decided to start to work on this project.

Due to our limited resources and time, we had to build an even limited machine which, unfortunatly, is not fit for harbor work. Nor festival work. But we believe that we learned a lot anyway.

# Requirements

### Hardware

To use this project, you will need the following hardware:

- 2x Texas Instruments MSP432P401R microcontroller
- 1x [Educational BoosterPack MKII](https://www.ti.com/tool/BOOSTXL-EDUMKII)
- Bluetooth modules:
  - 1x HC-05
  - 1x HC-06
- Metal bars (enough to make a 50x50x30cm frame, a 10x50cm cart and a 10x10 frame for the claw to hang on)
- 5x Stepper motors
- 5x Stepper motors' driver
- 8x Wheels to make the cart move on 2 axis
- Jumper wires
- [Claw Grabber](https://www.thingiverse.com/thing:4826548/files)
- 1x Servo motor
- A rope to connect to the claw

<p float="left">
  <img src="readme_assets/msp432p401r.png" alt="msp432p401r" width="140" height="225">
  <img src="readme_assets/boosterpack.png" alt="boosterpack" width="350" height="175">
</p>
  
### Software

- [Code Composer Studio](https://www.ti.com/tool/CCSTUDIO) Integrated Development Environment (IDE)
- [MSP432 DriverLib](https://www.ti.com/tool/download/SIMPLELINK-MSP432-SDK/3.40.01.02)
- UART drivers lib todo

# Project layout

```
├── README.md
├── readme_assets              # Images used in the readme
├── source
│    ├── Bluetooth             # Manages bluetooth connection
│    ├── Controller            # Manages the boosterpack and the state of the machine
│    ├── Graphics              # Writes to the screen
│    ├── MotorDriver           # TODO
│    └── ...
└── presentation.pdf           # Slide presentation
```

# Getting started

### Setting up the hardware

1. Build the frame, as well as everything the rest. TODO
2. Connect the various components as follows:
   - Connect the **BoosterPack MKII** to the **MSP432P401R Launchpad**.
   - Bluetooth setup
     - **HC-05** Configuration
       - Connect it to the hand-held controller.
         - Connect the HC-05 to a GND and a 5V pins of the board.
         - Connect the TXD wire to the PIN 3.2 and the RXD wire to the PIN 3.3 of the board.
       - Send it the following AT commands:
         - `AT+ROLE=1`
         - `AT+CMODE=1`
         - `AT+UART=9600,0,0`
         - `AT+PSWD=1234`
     - **HC-06** Configuration:
       - Connect it to the machine.
         - Connect the HC-06 to a GND and a 5V pins of the board.
         - Connect the TXD wire to the PIN 3.2 and the RXD wire to the PIN 3.3 of the board.
       - Send it the following AT commands:
         - `AT+BAUD4`
         - `AT+PIN1234`

- **MOTOR SETUP**
  - todo
- **CLAW SETUP**
  - todo

### Setting up the software

1. Clone this GitHub repo by using:

```sh
git clone https://github.com/Clown-Machine/ClawMachine.git
```

2. Open the project in **Code Composer Studio**.
3. Go to: _Project → Properties → Build → Arm Compiler → Include Options_ and add the _source_ directory located in _simplelink_msp432p4_sdk_3_40_01_02/_
4. Go to: _Project → Properties → Build → Arm Linker → File Search Path_ and add:
   - _msp432p4xx_driverlib.lib_ directory located in _[..]/source/ti/devices/msp432p4xx/driverlib/ccs/_
   - _grlib.a_ located in _[..]/source/ti/grlib/lib/ccs/m4f/_
5. Uart driver lib TODO
6. Build and run the project. The Launchpad should now be displaying the graphics.

# How to burn(?)

https://electronics.stackexchange.com/questions/188107/burn-code-using-code-composer-studio

# User guide

1. Follow the instruction displayed on the screen.
2. Keep in mind:
   [TODO Finite State Machine]
   Starting up the controller may take some time as the device must connect itself to the claw machine through a Bluetooth connection. Wait for the LED on both devices to stop blinking.
   - Click Button 1 (the first button on the right) to enter manual movement mode. You will be able to move the cart og the claw machine horizontally by moving the joystick: left, right, back and forth.
   - Click the Joystick Pushbutton to change the movement into vertical mode. Moving the joystick around you will be able to move the gripper as you like:
       - Up: raise the gripper
       - Down: lower the gripper
       - Left: close the gripper
       - Right: open the gripper
   
4. have fun!

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
