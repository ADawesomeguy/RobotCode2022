//@notSam25
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Joystick.h>
#include <frc2/command/button/JoystickButton.h>
#include <cmath>
enum JoystickKey  {
  TRIGGER = 1,
  SIDETRIGGER,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  ELLEVEN,
  TWELVE
};

class Joystick : public frc2::SubsystemBase {
 public:

  Joystick(int port = 0, float dz = 0.2f) : joystick(port), deadZone(dz) {} //Init constructer

  double getX() {
    return std::abs(joystick.GetX()) <= deadZone ? 0.0f : joystick.GetX(); //Get the Y val of the joystick, doesn't include values within deadzone
  }  

  double getY() {
    return std::abs(joystick.GetY()) <= deadZone ? 0.0f : joystick.GetY(); //Get the Y val of the joystick, doesn't include values within deadzone
  }  

  inline double getXRaw() { //Gets Joystick Raw values witout deadzone
    return joystick.GetX();
  }

  inline double getYRaw() { //Gets Joystick Raw values witout deadzone
    return joystick.GetY();
  }

  frc2::JoystickButton getButton(JoystickKey button)  { //Gets the button passed through the enum
    return frc2::JoystickButton(&joystick, (int)button);
  }
  
  double getTwist() { //Gets joystick twist/rotation
    double twist = (std::abs(std::pow(joystick.GetTwist(),2)) <= deadZone) ? 0.0 : std::pow(joystick.GetTwist(),2);
    return (joystick.GetTwist() >= 0) ? twist : -twist;
  }

  private:
    frc::Joystick joystick;
    float deadZone = 0.2f;
};
