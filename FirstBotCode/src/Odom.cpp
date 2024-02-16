#include "main.h"


	float diameter = 4.125f;//diameter of the omni wheels for distance measuring

	float radius = diameter * 0.5;//radius of the omni wheel for distance measuring

	float pi =  3.14;//just a shorter  pi for easier processing which is at 3.14
    float LeftMotorEncoder; // takes the encoder values from the the left motors and averages them

    float RightMotorEncoder; // takes the encoder values from the the left motors and averages them

    int calculatedFlywheelRPM;

    float kP;
    float kI; // universals for DriveTrain PID
    float kD;



Odom::Odom(){

}
  
int Odom::sgn(int val) {
    if (val > 0){
        return (1);
    }else if (val < 0) {
        return (-1);
    }else {
        return (0);
    }}
int abs(float Value){
    if(Value < 0){
        return -Value;
    }else {
        return Value;
    }
}

void OdomTracking(){
    
    pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);

        float kP = 30;
        float kI = 0.1;
        float kD = 0.3;
    while (true){
        LeftMotorEncoder = float(FrontLeftMotor.get_encoder_units() + BackLeftMotor.get_encoder_units()) / 2;
        RightMotorEncoder = float(FrontRightMotor.get_encoder_units() + BackRightMotor.get_encoder_units())/2;
    
        pros::delay(500);
    }
    

}
bool Odom::Forward(float WantedDistance){ //distance in inches
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
    float error;
    float LastError;
    float PID;
    float LeftTarget;
    float RightTarget;
    LeftTarget = AngleInDegrees + LeftMotorEncoder;
    RightTarget = AngleInDegrees + RightMotorEncoder;
    
while (abs(error) > 50){//PID Loop W
    error = ((LeftTarget - LeftMotorEncoder) + (RightTarget - RightMotorEncoder))/2;
    P = error * kP;
    I = (I+error) *kI;
    D = (error-LastError)*kD; 
    PID = P + I + D;
	FrontLeftMotor.move_voltage(PID);
	BackLeftMotor.move_voltage(PID);
	FrontRightMotor.move_voltage(PID);
	BackRightMotor.move_voltage(PID);
    
    }
    if (-(abs(error) > 50)){
    return true;
    }

}
bool Odom::Rotate(float DegreesToRotate){
    
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
    float kP = 0.3;
    float kI = 0.3;
    float kD = 0.3;
    float error;
    float LastError;
    float PID;
    float LeftTarget;
    float RightTarget;
    LeftTarget = -DegreesToMove + LeftMotorEncoder;
    RightTarget = DegreesToMove + RightMotorEncoder;
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
    
    if (error < 5){
        return true;
    }
    LastError = error;
    }
} 

void Odom::RunFlywheel(int target){

pros::Motor CataMotor(5);

int prevCalculatedFlywheelRPM;
const int FlywheelGearRatio = 7;
float K;
float P;
float DT;// delta Target RPM
int prevTarget; // for delta calculations
float Output;//voltage for the motors to use
float error;// the distance from the target
float Time;
float a;
float DeadLength;
while (true){
    

    calculatedFlywheelRPM = CataMotor.get_actual_velocity() * FlywheelGearRatio;
    int accel = calculatedFlywheelRPM - prevCalculatedFlywheelRPM; //  glorified deltaRPM
	float FF = FKi * sgn(calculatedFlywheelRPM) + FkD * calculatedFlywheelRPM + FKa * accel; 
	error = target - calculatedFlywheelRPM;
	Output = P*FF;
    CataMotor.move_voltage(Output);
    while (target == 0){
        CataMotor.move_voltage(0); // helps keep the motors not try to apply voltage to stop it
        Output = 0;
    }
    pros::delay(250); // allows for deltas to properly work
    prevCalculatedFlywheelRPM = calculatedFlywheelRPM;
    Time += 1;

    }
}