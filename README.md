# smc_arduino_libserial_comm
This is a child project of the Samuko Motor Control (SMC) project. This library can be used in your linux cpp robotic project (as it depends on the libserial-dev package) to communicate with the **smc_driver module** in order to send target angular velocities to the motors or receive the motor's angular velocity and angular position, after successful velocity PID setup with the [smc_app](https://github.com/samuko-things/EMC2_gui_application).

> you can use it in your microcomputer robotics project **running on linux** (e.g Raspberry Pi, Nvida, PC, etc.)

A simple way to get started is simply to try out and follow the example code in the example folder


## How to Use the Library
- install the libserial-dev package
  > sudo apt-get update
  >
  > sudo apt install libserial-dev

- Ensure you have the **smc_driver module** shield with a preffered arduino board of your choice (NANO or UNO) fully set up for velocity PID control.

- Download (by clicking on the green Code button above) or clone the repo into your PC

- make, build and run the example code.
  > cd into the root directory
  >
  > mkdir build (i.e create a folder named build)
  >
  > following command in terminal in the root folder:
    ````
    cmake -B ./build/
    ````
    ````
    cmake --build ./build/
    ````
    ````
    ./build/example_control_code
    ````


## Basic Library functions and usage

- connect to **smc_driver shield** module
  > connect("port_name or port_path")

- send target angular velocity command
  > sendTargetVel(motorATargetVel, motorBTargetVel)

- read motors angular position
  > getMotorsPos(&angPosA, &angPosB) // copies the motors angular position into angPosA, angPosB

- read motors angular velocity
  > getMotorsVel(&angVelA, &angVelB) // copies the motors ang vel angVelA, angVelB
