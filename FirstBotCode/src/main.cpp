using namespace std;

int PowerSavingMode = 0; 
const int triballAmount = 12; // the amount of triballs that will be shot from the pnumatics, normally this variable will be used once during auton




    pros::ADIDigitalIn ButtonOfPowerSaving (1);

	ofstream CurrentLog ("/usd/LogData.txt"); // global functions/variables
	int pollingRate = 2000;
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
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
	CurrentLog << "Initiation Complete! Running Competition initialized";

	
}
void autonomous() {
		pros::ADIDigitalOut pneumatic(1 ,'a');
		for (int i = 0; i <= triballAmount; i++ ){
	pneumatic.set_value(LOW);
	pros::delay(700);
	pneumatic.set_value(HIGH);
	pros::delay(500);
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
	pros::ADIDigitalOut pneumatic(1 ,'a');

    pros::Controller MainController(pros::E_CONTROLLER_MASTER);
	pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);
	pros::Motor ArmMotor(5);
    pros::Motor ClawOpenMotor(9);
    pros::Motor ClawLeftMotor(7);
    pros::Motor ClawRightMotor(8);

	pros::lcd::set_text(1, "Motors Compiled!");

float cPower;
 float cTurn;
 float left;
 float right;
 float curve = 0.7f;
 float ClawMovement;



	float ArmUp;
	float ArmMove;


	while (true) {         // the while true Command
		
	cPower = MainController.get_analog(ANALOG_LEFT_Y);
	cTurn = MainController.get_analog(ANALOG_RIGHT_X);

	left = cPower + cTurn;
	right = cPower - cTurn;



if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
	pneumatic.set_value(HIGH);
}else if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
	pneumatic.set_value(LOW);
}else if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
	pneumatic.set_value(LOW);
}else if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
		pros::ADIDigitalOut pneumatic(1 ,'a');
		for (int i = 0; i <= triballAmount; i++ ){
	pneumatic.set_value(LOW);
	pros::delay(700);
	pneumatic.set_value(HIGH);
	pros::delay(500);
	}
}

ClawOpenMotor.move(ClawMovement*100);



	
	
		
// 8 motor drive
 	FrontLeftMotor.move(100*(((1-curve)*left)/100+(curve*pow(left/100,7))));
 	FrontRightMotor.move(100*(((1-curve)*right)/100+(curve*pow(right/100,7))));
  	BackLeftMotor.move(100*(((1-curve)*left)/100+(curve*pow(left/100,7))));
 	BackRightMotor.move(100*(((1-curve)*right)/100+(curve*pow(right/100,7))));


		ArmMotor.move(ArmUp);

		ClawLeftMotor.move(ArmMove);
		ClawRightMotor.move(-ArmMove);

		pros::delay(20); //delay for resource saving
	}

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

