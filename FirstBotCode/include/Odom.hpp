#include "main.h"
#pragma once
#ifndef ODOM_HPP
#define ODOM_HPP

class Odom{
    public:
    float kP; // progressive for drivetrain PID.. how much it wants to go up
    float kI; // interval for DriveTrain PID.. how much does it wanna move up and down exponentially
    float kD = 50; // tries to prevent it needing to go down


    float FkD;
    float FKi;//flywheels info tbh idk what they do all i know is they it works
    float FkP;//universals for FlywheelPID
    float FKa;
    int RightMotorEncoder;//encoders from motors to be used in multiple files
    int LeftMotorEncoder;
    float LeftTarget;
    float RightTarget;
    float error; // difference between where its supposed to be compared to where it actually wants to be
    Odom();//calls the class to call variables
    
    void Forward(float WantedDistance);//function for going forward
    void Rotate(float DegreesToRotate);//function for turning in degrees because radians are weird
    void RunFlywheel(int target); // runs the flywheel using the target
    

    int sgn(int val);
};

extern void OdomTracking();
#endif