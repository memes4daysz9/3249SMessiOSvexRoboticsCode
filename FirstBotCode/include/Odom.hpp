#include "main.h"
#pragma once
#ifndef ODOM_HPP
#define ODOM_HPP

class Odom{
    public:
    float kP;
    float kI; // universals for DriveTrain PID
    float kD = 50;


    float FkD;
    float FKi;
    float FkP;//universals for FlywheelPID
    float FKa;
    int RightMotorEncoder;
    int LeftMotorEncoder;
    float error;
    Odom();
    
    void Forward(float WantedDistance);
    void Rotate(float DegreesToRotate);
    void RunFlywheel(int target);
    

    int sgn(int val);
};

extern void OdomTracking();
#endif