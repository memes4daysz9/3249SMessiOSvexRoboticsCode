#include "main.h"



using namespace std;

/* 
float cPower;
 float cTurn;
 float left;
 float right;
 float curve

	cPower = MainController.get_analog(ANALOG_LEFT_Y);
	cTurn = MainController.get_analog(ANALOG_RIGHT_X);
	left = cPower + cTurn;
	right = cPower - cTurn;

 	FrontLeftMotor.move(forward,(100*(((1-curve)*left)/100+(curve*pow(left/100,7)))));
 	FrontRightMotor.move(forward,(100*(((1-curve)*right)/100+(curve*pow(right/100,7)))));
  	BackLeftMotor.move(forward,(100*(((1-curve)*left)/100+(curve*pow(left/100,7)))));
 	BackRightMotor.move(forward,(100*(((1-curve)*right)/100+(curve*pow(right/100,7)))));
 */ 
    float FkD;
    float FKi;
    float FkP;//universals for FlywheelPIDFF
    float FKa;

void opcontrol(){
	pros::Imu Inertia(15);
	pros::Task OdomTask(OdomTracking); //multithreading W
	pros::ADIDigitalOut FirstWingMan(1 ,'a');
	pros::ADIDigitalOut SecondWingMan(2 ,'b');
    pros::Controller MainController(pros::E_CONTROLLER_MASTER);//main controller
	pros::Controller SideCon(pros::E_CONTROLLER_PARTNER);//second controller

    pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);
	pros::Motor FlyMotor(5);
	pros::Motor Intake(6);
	pros::Motor LeftMiddleMotor(7);
	pros::Motor RightMiddleMotor(8);
/*PID info
P=error *kP
I=integral*kI
D=(error-last error)*kD
/
integral = integral + error
*/


float I;
float D;
float integral;
float target;//the target voltage for the PID to hit
float CataMotorTemp;
bool KILLMODE;// dont worry bout it
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
float Blocker;
float IntakePower;
float BlockerPower;


float cPower;
 float cTurnSpot;//does not include the friction wheel Motors
 float cTurnNormal;//engages the friction wheel Motors
 float left;
 float right;
 float leftMiddle;
 float rightMiddle;
 const int curve = 1;

	while (true) {         // the while true Command
//BackRightMotor.move(100*(((1-curve)*right)/100+(curve*pow(right/100,7))));
cPower = MainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
cTurnNormal = MainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
cTurnSpot = MainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

left = cPower + cTurnNormal + cTurnSpot;
right = cPower - cTurnNomal - cTurnSpot;
leftMiddle = cPower - cTurnNormal;
RightMiddle = cPower + cTurnNormal;

FrontLeftMotor.move(100*(((1-curve)*left)/100+(curve*pow(left/100,7))));
FrontRightMotor.move(100*(((1-curve)*right)/100+(curve*pow(right/100,7))));
BackLeftMotor.move(100*(((1-curve)*left)/100+(curve*pow(left/100,7))));
BackRightMotor.move(100*(((1-curve)*right)/100+(curve*pow(right/100,7))));
RightMiddleMotor.move(100*(((1-curve)*rightMiddle)/100+(curve*pow(rightMiddle/100,7))));
LeftMiddleMotor.move(100*(((1-curve)*leftMiddle)/100+(curve*pow(leftMiddle/100,7))));

}
}