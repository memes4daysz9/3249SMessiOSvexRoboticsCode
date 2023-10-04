#include <iostream>
#include <fstream>
#include "globals.cpp"
#include "main.h"
#include "PowerAllocationFunctions.cpp"
using namespace std;


ofstream CurrentLog ("/usd/LogData.txt"); // global functions/variables
int pollingRate;

void initialize() {
    

    CurrentLog << "File started"; 
}
void competition_initialize() {
    CurrentLog << "Initiation Complete! Running Competition initialized";
}

void autonomous() {

    CurrentLog << "Running Auton, starting Motor and Battery polling";

    if (PowerSavingMode == -1){
        pollingRate = 250;
    }else if (PowerSavingMode == 0){ //polliong rate Functions
        pollingRate = 750;
    }else{
    pollingRate = PowerSavingMode * 1000;
    }

    while (true){ // runs auton polling
    int RobotBatLevel = pros::battery::get_capacity();

    int LFMtemp = FrontLeftMotor.get_temperature();
    int LBMtemp = BackLeftMotor.get_temperature();
    int RFMtemp = FrontRightMotor.get_temperature();
    int RBMtemp = BackRightMotor.get_temperature();

    CurrentLog << "Robot battery Level " + RobotBatLevel;

    CurrentLog << "Left Front Motor Temp" + LFMtemp;
    CurrentLog << "Left Back Motor Temp" + LBMtemp;  
    CurrentLog << "Right Front Motor Temp" + RFMtemp;
    CurrentLog << "Right Back Motor Temp" + RBMtemp;  




    pros::delay(pollingRate);
    }

}
void opcontrol() {

        while (true){ // runs auton polling
    int RobotBatLevel = pros::battery::get_capacity();

    int LFMtemp = FrontLeftMotor.get_temperature();
    int LBMtemp = BackLeftMotor.get_temperature();
    int RFMtemp = FrontRightMotor.get_temperature();
    int RBMtemp = BackRightMotor.get_temperature();

    CurrentLog << "Robot battery Level " + RobotBatLevel;

    CurrentLog << "Left Front Motor Temp" + LFMtemp;
    CurrentLog << "Left Back Motor Temp" + LBMtemp;  
    CurrentLog << "Right Front Motor Temp" + RFMtemp;
    CurrentLog << "Right Back Motor Temp" + RBMtemp;  




    pros::delay(pollingRate);
    }
	
	//Brain display
	while(true){
		int VexBat = pros::battery::get_capacity();
		pros::lcd::set_text(0,"ControllerBat" + MainController.get_battery_capacity()); //Brain displayed
        CurrentLog << "ControllerBat" + MainController.get_battery_capacity();
        pros::delay(pollingRate);
	}

	//controller Display
	while (true){
		int VexBat = pros::battery::get_capacity();
		MainController.clear();
		MainController.set_text(0,0,"Your Controller's Battery is at " + MainController.get_battery_capacity() ); //initial Battery information
		MainController.set_text(1,0,"your Robot's Battery is at " + VexBat );
		pros::delay(pollingRate);//delay for the controller is 110 with certain brains and you dont need anything sooner than 150ms of delay for your battery
	}
		
	


}

