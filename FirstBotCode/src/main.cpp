#include "main.h"
#include <iostream>
#include <fstream>
using namespace std;

int PowerSavingMode = 0; 
const int triballAmount = 12; // the amount of triballs that will be shot from the pnumatics, normally this variable will be used once during auton




    pros::ADIDigitalIn ButtonOfPowerSaving (1);

	ofstream CurrentLog ("/usd/LogData.txt"); // global functions/variables
	int pollingRate = 2000;







// Wheel Nerdy Stuf
	float diameter = 4.125f;//diameter of the omni wheels for distance measuring

	float radius = diameter * 0.5;//radius of the omni wheel for distance measuring

	float pi =  3.14;//just a shorter  pi for easier processing which is at 3.14


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
bool RightSide;
bool LeftSide;
void initialize() {
	pros::lcd::initialize();
	pros::Motor FrontLeftMotor_initializer(1, pros::E_MOTOR_GEARSET_06, false,pros::E_MOTOR_ENCODER_COUNTS);
	pros::Motor FrontRightMotor_initializer(2,pros::E_MOTOR_GEARSET_06, true,pros:: E_MOTOR_ENCODER_COUNTS);
//front Motors


//Back Motors
	pros::Motor BackLeftMotor_initializer(3, pros::E_MOTOR_GEARSET_06, false,pros::E_MOTOR_ENCODER_COUNTS);
	pros::Motor BackRightMotor_initializer(4, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);






	pros::lcd::initialize();

	pros::lcd::set_text(1, "Nerd");
	CurrentLog << "File started"; 
}

void DistanceToTravel(float WantedDistance, int Power){ //distance in inches
	// for every 360degrees, the wheel will go its circumference

	pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);



	float circumference =pi*diameter;

	float distancePerDegree = circumference/360;

	float AngleInDegrees = WantedDistance/distancePerDegree;// forwards angle movement

	FrontLeftMotor.move_relative(AngleInDegrees,Power);
	FrontRightMotor.move_relative(AngleInDegrees,Power);
	BackLeftMotor.move_relative(AngleInDegrees,Power);
	BackRightMotor.move_relative(AngleInDegrees,Power);

}

void AmountToRotate(float DegreesToRotate, int Power){
	pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);

	float circumference =pi*diameter;
	float DistanceToMoveOnCircumference = DegreesToRotate/360  * circumference;
	float DegreesToMove = DistanceToMoveOnCircumference / diameter * 360;
	
	FrontLeftMotor.move_relative(-DegreesToMove, Power);
	BackLeftMotor.move_relative(-DegreesToMove, Power);
	FrontRightMotor.move_relative(DegreesToMove,Power);
	BackRightMotor.move_relative(DegreesToMove,Power);
}               

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	pros::Controller MainController(pros::E_CONTROLLER_MASTER);
	CurrentLog << "Initiation Complete! Running Competition initialized";
	
	while (true){
		if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
			RightSide = true;
		}else if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
			LeftSide = true;
		}
	}
	
}
void autonomous() {


if(RightSide){
	pros::lcd::clear;
	pros::lcd::set_text(1, "Set To Right Side!");
	DistanceToTravel(7,25);
	pros::delay(2000);
	AmountToRotate(50, 20);
	pros::delay(2000);
	DistanceToTravel(30,70);
}else if (LeftSide){
	pros::lcd::clear;

	pros::lcd::set_text(1, "Set To Left Side!");
	DistanceToTravel(7,25);
	pros::delay(2000);
	AmountToRotate(-50, 20);
	pros::delay(2000);
	DistanceToTravel(30,70);
}else{
	AmountToRotate(720,100);
}







}


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


void opcontrol() {
	pros::ADIDigitalOut FirstWingMan(1 ,'a');
	pros::ADIDigitalOut SecondWingMan(2 ,'b');

    pros::Controller MainController(pros::E_CONTROLLER_MASTER);
	pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);
	pros::Motor CataMotor(5);


	pros::lcd::set_text(1, "Motors Compiled!");

float cPower;
 float cTurn;
 float left;
 float right;
 float curve = 0.7f;





	while (true) {         // the while true Command
		
	cPower = MainController.get_analog(ANALOG_LEFT_Y);
	cTurn = MainController.get_analog(ANALOG_RIGHT_X);

	left = cPower + cTurn;
	right = cPower - cTurn;



if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){

	FirstWingMan.set_value(HIGH);
	SecondWingMan.set_value(HIGH);

}else if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){

	FirstWingMan.set_value(LOW);
	SecondWingMan.set_value(LOW);

}


if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
	CataMotor.move(100);
}else{
	CataMotor.brake();
}



	
	
		
// 4 motor drive
 	FrontLeftMotor.move(100*(((1-curve)*left)/100+(curve*pow(left/100,7))));
 	FrontRightMotor.move(100*(((1-curve)*right)/100+(curve*pow(right/100,7))));
  	BackLeftMotor.move(100*(((1-curve)*left)/100+(curve*pow(left/100,7))));
 	BackRightMotor.move(100*(((1-curve)*right)/100+(curve*pow(right/100,7))));


		pros::delay(20); //delay for resource saving
	}

	}


