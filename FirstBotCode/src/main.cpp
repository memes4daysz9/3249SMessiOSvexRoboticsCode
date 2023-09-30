#include "main.h"
#include "subsystemFiles/globals.cpp"
/**
 * A callback function for LLEMU's center button.
 *
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "NUH UH");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

	pros::lcd::initialize();
	FrontLeftMotor.set_voltage_limit(12000);
    BackLeftMotor.set_voltage_limit(12000); //maxing out the motors
    FrontRightMotor.set_voltage_limit(12000);
    BackRightMotor.set_voltage_limit(12000);
	pros::lcd::set_text(1, "ROBOT WILL SELF DESTTRUCT IF WE LOSE");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

	FrontLeftMotor.brake();
    BackLeftMotor.brake(); // Brakes motor
    FrontRightMotor.brake();
    BackRightMotor.brake();
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
	int VexBat = pros::battery::get_capacity();
	MainController.clear();
	MainController.set_text(0,0,"Your Controller's Battery is at " + MainController.get_battery_capacity() ); //initial Battery information
	MainController.set_text(1,0,"your Robot's Battery is at " + VexBat );
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	float VerticalPower;
	float RotatePower;
	float PowerCurveVertical;
	float PowerCurveRotation;
	float curve = 0.7f;
	while (true) {
		
        VerticalPower = MainController.get_analog(ANALOG_LEFT_Y) * PowerCurveVertical; 
        RotatePower = MainController.get_analog(ANALOG_RIGHT_X)* PowerCurveRotation;

		PowerCurveVertical =  100*((1-curve)* VerticalPower / 100 + curve*(VerticalPower/100)*5);
		PowerCurveRotation = 100*((1-curve)* RotatePower / 100 + curve*(RotatePower/100)*5); 



        FrontLeftMotor.move(VerticalPower + RotatePower);
        BackLeftMotor.move(VerticalPower + RotatePower);
        FrontRightMotor.move(VerticalPower - RotatePower);
        BackRightMotor.move(VerticalPower - RotatePower);






		//Display Functions
		pros::delay(20);

	}
	
	//Brain display
	while(true){
		int VexBat = pros::battery::get_capacity();
		pros::lcd::set_text(0,"ControllerBat" + MainController.get_battery_capacity()); //Brain displayed
		pros::lcd::set_text(0,"MainBattery" + VexBat);
		pros::delay(50);
	}

	//controller Display
	while (true){
		int VexBat = pros::battery::get_capacity();
		MainController.clear();
		MainController.set_text(0,0,"Your Controller's Battery is at " + MainController.get_battery_capacity() ); //initial Battery information
		MainController.set_text(1,0,"your Robot's Battery is at " + VexBat );
		pros::delay(1000);//delay for the controller is 110 with certain brains and you dont need anything sooner than 150ms of delay for your battery
	}
		
	


}
