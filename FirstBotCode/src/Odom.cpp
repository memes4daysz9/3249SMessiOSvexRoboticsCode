#include "main.h"
#include "pros/screen.h"
#include "Odom.h"



	float diameter = 4.125f;//diameter of the omni wheels for distance measuring

	float radius = diameter * 0.5;//radius of the omni wheel for distance measuring

	float pi =  3.14;//just a shorter  pi for easier processing which is at 3.14
    float LeftMotorEncoder; // takes the encoder values from the the left motors and averages them

    float RightMotorEncoder; // takes the encoder values from the the left motors and averages them
void  OdomTracking(){
    
    pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);

    while (true){
        LeftMotorEncoder = (FrontLeftMotor.get_encoder_units() + BackLeftMotor.get_encoder_units()) / 2;
        RightMotorEncoder = (FrontRightMotor.get_encoder_units() + BackRightMotor.get_encoder_units())/2;
    

    }
    

}
bool Forward(float WantedDistance, int Power){ //distance in inches
	// for every 360degrees, the wheel will go its circumference
    bool TargetMet;
	pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);

	FrontLeftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	BackLeftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	FrontRightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	BackRightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);




	float circumference =pi*diameter;

	float distancePerDegree = circumference/360;

	float AngleInDegrees = WantedDistance/distancePerDegree;// forwards angle movement

    float P;
    float I;
    float D;
    float kP;
    float kI;
    float kD;
    float error;
    float LastError;
    float PID;
    float LeftTarget;
    float RightTarget;
while (true){//PID Loop W
    error = ((LeftTarget - LeftMotorEncoder) + (RightTarget - RightMotorEncoder))/2;
    P = error * kP;
    I = (I+error) *kI;
    D = (error-LastError)*kD; 
    PID = P + I + D;
	FrontLeftMotor.move_relative(AngleInDegrees,Power);
	FrontRightMotor.move_relative(AngleInDegrees,Power);
	BackLeftMotor.move_relative(AngleInDegrees,Power);
	BackRightMotor.move_relative(AngleInDegrees,Power);

    if (TargetMet == true){
        return true;
    }
    }

}
bool Rotate(float DegreesToRotate, int Power){
    
    bool TargetMet;
	pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);

	float circumference =pi*diameter;
	float DistanceToMoveOnCircumference = DegreesToRotate/360  * circumference;
	float DegreesToMove = DistanceToMoveOnCircumference / diameter * 360;
	float P;
    float I;
    float D;
    float kP;
    float kI;
    float kD;
    float error;
    float LastError;
    float PID;
    float LeftTarget;
    float RightTarget;
while (true){//PID Loop W
    error = ((LeftTarget - LeftMotorEncoder) + (RightTarget - RightMotorEncoder))/2;
    P = error * kP;
    I = (I+error) * kI;
    D = (error-LastError) * kD; 
    PID = P + I + D;
	FrontLeftMotor.move_voltage(-PID);
	BackLeftMotor.move_voltage(-PID);
	FrontRightMotor.move_voltage(PID);
	BackRightMotor.move_voltage(PID);
    
    if (TargetMet == true){
        return true;
    }
    LastError = error;
    }
} 
