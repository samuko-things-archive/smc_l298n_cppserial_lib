
#include <sstream>
#include <iostream>
#include<unistd.h>

#include <chrono>

#include <iomanip>

#include "smc_cppserial_lib.hpp"

SMC smc;


void delay_ms(unsigned long milliseconds) {
  usleep(milliseconds*1000);
}





int main(int argc, char **argv) {

  bool sendHigh = false;

  float lowTargetVel = 1.571; // in rad/sec
  float highTargetVel = 3.142; // in rad/sec

  float angPosA, angPosB;
  float angVelA, angVelB;

  auto prevTime = std::chrono::system_clock::now();
  std::chrono::duration<double> duration;
  float sampleTime = 0.02;

  auto ctrlPrevTime = std::chrono::system_clock::now();
  std::chrono::duration<double> ctrlDuration;
  float ctrlSampleTime = 10.0;



  // std::string port = "/dev/serial/by-path/pci-0000:00:14.0-usb-0:1.4:1.0-port0";
  std::string port = "/dev/ttyUSB0";
  smc.connect(port);

  // wait for the smc to fully setup
  for (int i=1; i<=5; i+=1){ 
    delay_ms(1000);
    std::cout << "configuring controller: " << i << " sec" << std::endl;
  }
  smc.sendTargetVel(0.0, 0.0); // targetA, targetB
  std::cout << "configuration complete" << std::endl;


  smc.sendTargetVel(lowTargetVel, lowTargetVel); // targetA, targetB
  sendHigh = true;

  prevTime = std::chrono::system_clock::now();
  ctrlPrevTime = std::chrono::system_clock::now();

  while (true)
  {

    ctrlDuration = (std::chrono::system_clock::now() - ctrlPrevTime);
    if (ctrlDuration.count() > ctrlSampleTime)
    {
      if(sendHigh){
        smc.sendTargetVel(highTargetVel, highTargetVel); // targetA, targetB
        sendHigh = false;
      }
      else {
        smc.sendTargetVel(lowTargetVel, lowTargetVel); // targetA, targetB
        sendHigh = true;
      }

      ctrlPrevTime = std::chrono::system_clock::now();
    }
    

    duration = (std::chrono::system_clock::now() - prevTime);
    if (duration.count() > sampleTime)
    {
      try{
        smc.getMotorsPos(angPosA, angPosB); // gets angPosA, angPosB
        smc.getMotorsVel(angVelA, angVelB); // gets angVelA, angVelB
      } catch(...) {
        // std::cout << "motorA_readings: [" << angPosA << std::fixed << std::setprecision(4) << "," << angVelA << std::fixed << std::setprecision(4) << "]" << std::endl;
        // std::cout << "motorB_readings: [" << angPosB << std::fixed << std::setprecision(4) << "," << angVelB << std::fixed << std::setprecision(4) << "]" << '\n' << std::endl;
      }

      std::cout << "motorA_readings: [" << angPosA << std::fixed << std::setprecision(4) << "," << angVelA << std::fixed << std::setprecision(4) << "]" << std::endl;
      std::cout << "motorB_readings: [" << angPosB << std::fixed << std::setprecision(4) << "," << angVelB << std::fixed << std::setprecision(4) << "]" << '\n' << std::endl;

      prevTime = std::chrono::system_clock::now();
    }

  }
  
}