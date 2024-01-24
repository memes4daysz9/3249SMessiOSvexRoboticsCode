#include "main.h"
#include <fstream>
#include "Odom.h"
#include "Screen.h"
#include "pros/adi.h"
#include "Drive.h"
using namespace std;

int AutonSide;
const int triballAmount = 12; // the amount of triballs that will be shot from the pnumatics, normally this variable will be used once during auton






	ofstream CurrentLog ("/usd/LogData.txt"); // global functions/variables
	int pollingRate = 2000;







// Wheel Nerdy Stuf



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



  pros::Task OdomTask(OdomTracking); //multithreading W
  pros::Task ScreenTask(ScreenStats); 


	pros::lcd::initialize();

	
	CurrentLog << "File started"; 
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
	
}


void autonomous() {
AutonRun();


}





void opcontrol() {
	
Allowdriving();

	}


