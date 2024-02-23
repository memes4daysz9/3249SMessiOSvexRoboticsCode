#include "main.h"


	float diameter = 4.125f;//diameter of the omni wheels for distance measuring

	float radius = diameter * 0.5;//radius of the omni wheel for distance measuring

	float pi =  3.14;//just a shorter  pi for easier processing which is at 3.14

    int LeftMotorEncoder; // takes the encoder values from the the left motors and averages them

    int RightMotorEncoder; // takes the encoder values from the the left motors and averages them

    int calculatedFlywheelRPM;// calculates the rpm based on the gear ratio i added

    const int Tolerance = 36;//fixed variable for the error to try to get the motors degrees in this range

    float kP; //nothin... this isnt here at all im not lazy...
    float kI; // universals for DriveTrain PID
    float kD;



Odom::Odom(){//calls the variables inside class
    float FkD;
    float FKi;
    float FkP;//universals for FlywheelPID
    float FKa;
    int RightMotorEncoder;
    int LeftMotorEncoder;
    float PID;
    float error;
}
  
int Odom::sgn(int val) { //signum function
    if (val > 0){
        return (1);
    }else if (val < 0) {
        return (-1);
    }else {
        return (0);
    }}
int abs(float Value){//absolute value
    if(Value < 0){
        return -Value;
    }else {
        return Value;
    }
}
void ClearTrackers(){//resets the positions
    pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);


    FrontLeftMotor.tare_position();
    FrontRightMotor.tare_position();
    BackLeftMotor.tare_position();
    BackRightMotor.tare_position();
}
void OdomTracking(){ //tracks the motors without any limits because i said so
    
    pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);

        float kP = 30;
        float kI = 0.1;
        float kD = 0.3;
    while (true){
        odom.LeftMotorEncoder = FrontLeftMotor.get_position() + BackLeftMotor.get_position() / 2;
        odom.RightMotorEncoder = FrontRightMotor.get_position() + BackRightMotor.get_position()/2;
        pros::screen::print(pros::E_TEXT_MEDIUM,3,"left Side DriveTrain: %d",odom.LeftMotorEncoder);// same as above function
        pros::screen::print(pros::E_TEXT_MEDIUM,4,"Right Side DriveTrain %d",odom.RightMotorEncoder);//same too lmao
    }
    

}
void Odom::Forward(float WantedDistance){ //distance in inches
	// for every 360degrees, the wheel will go its circumference
    bool TargetMet;
	pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);
    pros::Controller MainController(pros::E_CONTROLLER_MASTER);//main controller

	float circumference =pi*diameter;//funny geometry calculation

	float distancePerDegree = circumference/360;//more funny calculations

	float AngleInDegrees = WantedDistance/distancePerDegree;// forwards angle movement
    bool variablebug = false; //i belive this is the way to go about fixing funny variables... dunno how it does it but it does it
    float P;
    float I;
    float D;
    float LastError;//gets the error from the last loop
    odom.LeftTarget = AngleInDegrees + odom.LeftMotorEncoder;//668 for 5 in
    odom.RightTarget = AngleInDegrees + odom.RightMotorEncoder;
    odom.error = Tolerance + 10; //kickstarts the loop
while ((abs(error) > Tolerance)){//PID Loop W
    odom.error = ((odom.LeftTarget - odom.LeftMotorEncoder) + (odom.RightTarget - odom.RightMotorEncoder))/2;
    P = error * 32.5;
    I = (I+odom.error) *0.1;
    D = (odom.error-LastError)*10; //PID live time Calculation
    pros::screen::print(pros::E_TEXT_MEDIUM,10,"Individual PID Values %f,%f,%f",P,I,D);
    odom.PID = P + I + D;
	FrontLeftMotor.move_voltage(odom.PID);
	BackLeftMotor.move_voltage(odom.PID);
	FrontRightMotor.move_voltage(odom.PID);
	BackRightMotor.move_voltage(odom.PID);

    pros::delay(20);// delays the loop from calling everything else, helps to keep things cool inside the brain and saves battery

    if (odom.error == LastError){//helps fix stuf
            MainController.print(0,0,"PID Error!");
            variablebug = true;
            	FrontLeftMotor.move_voltage(6000);
	            BackLeftMotor.move_voltage(6000);
	            FrontRightMotor.move_voltage(6000);
	            BackRightMotor.move_voltage(6000);//PID boost
                pros::delay(1);
            	FrontLeftMotor.move_voltage(0);
	            BackLeftMotor.move_voltage(0);
	            FrontRightMotor.move_voltage(0);
	            BackRightMotor.move_voltage(0);              
        }
    LastError = odom.error;//haha heres where it gets the last error

    }
    FrontLeftMotor.brake();
    BackLeftMotor.brake();
    FrontRightMotor.brake();
    BackRightMotor.brake();
    break;

}
void Odom::Rotate(float DegreesToRotate){//you spin me right round baby right round like a record baby round round round round
    
    bool TargetMet;
	pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);
    pros::Controller MainController(pros::E_CONTROLLER_MASTER);//main controller

    FrontLeftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);//when told to stop. itll stay right where its at and not coast
	BackLeftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	FrontRightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	BackRightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	float circumference =pi*diameter;//weird turning calculations
	float DistanceToMoveOnCircumference = DegreesToRotate/360  * circumference;
	float DegreesToMove = DistanceToMoveOnCircumference / diameter * 360;
    bool variablebug = false; //i belive this is the way to go about fixing 
	float P;
    float I;
    float D;
    float kP = 0.3;
    float kI = 0.3;
    float kD = 0.3;
    float right;
    float left;
    float LastError;
    odom.LeftTarget = -DegreesToMove + odom.LeftMotorEncoder;//fixes any clearing problems is there is any
    odom.RightTarget = DegreesToMove + odom.RightMotorEncoder;
    odom.error = Tolerance + 10; //kickstarts the loop
    const float curve = -1.6;
    const int maxVolt;
    float anotherPID;
while (abs(error) > Tolerance ){//PID Loop W
    odom.error = ((odom.LeftTarget - odom.LeftMotorEncoder) + (odom.RightTarget - odom.RightMotorEncoder))/2;
    P = odom.error * 10;
    I = (I+odom.error) * 0.1;
    D = (odom.error-LastError) * 3; 
    PID = P + I + D;
    anotherPID = odom.PID;
    right = -anotherPID;
    left = odom.PID;
	FrontLeftMotor.move_voltage(maxVolt*(((1-curve)*left)/maxVolt+(curve*pow(left/maxVolt,7))));
	BackLeftMotor.move_voltage(maxVolt*(((1-curve)*left)/maxVolt+(curve*pow(left/maxVolt,7))));//doesnt actually mean the max voltage, just a variable name 
	FrontRightMotor.move_voltage(maxVolt*(((1-curve)*right)/maxVolt+(curve*pow(right/maxVolt,7))));
	BackRightMotor.move_voltage(maxVolt*(((1-curve)*right)/maxVolt+(curve*pow(right/maxVolt,7))));
    
    pros::delay(20);    
    if (odom.error == LastError){
            MainController.print(0,0,"PID Error!");
            variablebug = true;
                FrontLeftMotor.move_voltage(6000);
	            BackLeftMotor.move_voltage(6000);
	            FrontRightMotor.move_voltage(6000);
	            BackRightMotor.move_voltage(6000); //gives the loop a little boost
                pros::delay(1);
            	FrontLeftMotor.move_voltage(0);
	            BackLeftMotor.move_voltage(0);
	            FrontRightMotor.move_voltage(0);
	            BackRightMotor.move_voltage(0);  

    }
    LastError = odom.error;
    }
    FrontLeftMotor.brake();
    BackLeftMotor.brake();
    FrontRightMotor.brake();
    BackRightMotor.brake();
    break;
} 

void Odom::RunFlywheel(int target){

pros::Motor CataMotor(5);

int prevCalculatedFlywheelRPM;//different PID only its now just a P and no I and D
const int FlywheelGearRatio = 7; //look here it is!
float K;
float P;
float DT;// delta Target RPM
int prevTarget; // for delta calculations
float Output;//voltage for the motors to use
float error;// the distance from the target
float a;
float DeadLength;
while (true){
    

    calculatedFlywheelRPM = CataMotor.get_actual_velocity() * FlywheelGearRatio;//calc for flywheel rpm
    int accel = calculatedFlywheelRPM - prevCalculatedFlywheelRPM; //  glorified deltaRPM
	float FF = FKi * sgn(calculatedFlywheelRPM) + FkD * calculatedFlywheelRPM + FKa * accel;  //FF calc(cant say what it is lmao)
	odom.error = target - calculatedFlywheelRPM;//error
	Output = P*FF;//motor output
    CataMotor.move_voltage(Output);
    while (target == 0){//cool motor cooling feature when not needed
        CataMotor.move_voltage(0); // helps keep the motors not try to apply voltage to stop it
        Output = 0;
    }
    pros::delay(250); // allows for deltas to properly work
    prevCalculatedFlywheelRPM = calculatedFlywheelRPM;

    }
}