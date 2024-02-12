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
    float FkP;//universals for FlywheelPID
    float FKa;

void opcontrol(){

	pros::ADIDigitalOut FirstWingMan(1 ,'a');
	pros::ADIDigitalOut SecondWingMan(2 ,'b');

    pros::Controller MainController(pros::E_CONTROLLER_MASTER);
	pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);
	pros::Motor CataMotor(5);
	pros::Motor Intake(6);
	pros::Motor LeftBlocker(7);
	pros::Motor RightBlocker(8);
	 




float cPower;
 float cTurn;
 float left;
 float right;
 float curve = 0.7f;


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
bool KILLMODE;
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

	while (true) {         // the while true Command

	cTurn = MainController.get_analog(ANALOG_LEFT_Y);
	cPower = MainController.get_analog(ANALOG_RIGHT_X);
	Intake = MainController.get_analog(ANALOG_LEFT_X);
	left = cPower + cTurn;
	right = cPower - cTurn;
	if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){\
		target = 3000;//sets the target RPM to 3000, which is 700 rpms more than normal
		CataMotor.set_voltage_limit(30000);//NOTE this is in mV meaning that its doing 30V.... and yes, PROS lets this happen and the motors smell alot
		CataMotor.set_current_limit(5000);//2500mA is the normal amount
	}else if(MainController.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
		target = 0;
	}
	    calculatedFlywheelRPM = CataMotor.get_actual_velocity() * FlywheelGearRatio;
    int accel = calculatedFlywheelRPM - prevCalculatedFlywheelRPM; //  glorified deltaRPM
	float FF = sgn(calculatedFlywheelRPM + target) * sgn(target)( 2 * calculatedFlywheelRPM + 3 * accel + 100 * error); //target is in the sgn to help get the flywheel intitally going, once the target is 0, itll stop and same for negatives
	error = target - calculatedFlywheelRPM;
	Output = FF;
	MainController.print(0, 0, "running at %d",calculatedFlywheelRPM);
	if (target >= 1){
    CataMotor.move_voltage(-Output);
	}else {
		CataMotor.move_voltage(0);
	}
	if (MainController.get_digital(DIGITAL_B)){
		target = 0;
	}


if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){

	FirstWingMan.set_value(HIGH);
	SecondWingMan.set_value(HIGH);

}else if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){

	FirstWingMan.set_value(LOW);
	SecondWingMan.set_value(LOW);

}


if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
	target = 2000;
		
}else if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
	target = -2000;
}else if(MainController.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
	target = 0;
}


	
if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
	KILLMODE = true;
	FrontLeftMotor.set_voltage_limit(30000);
	FrontRightMotor.set_voltage_limit(30000);
	BackLeftMotor.set_voltage_limit(30000);
	BackRightMotor.set_voltage_limit(30000);
	FrontLeftMotor.set_current_limit(5000);
	FrontRightMotor.set_current_limit(5000);
	BackLeftMotor.set_current_limit(5000);
	BackRightMotor.set_current_limit(5000);

}else if (MainController.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
	KILLMODE = false;
	FrontLeftMotor.set_voltage_limit(12000);
	FrontRightMotor.set_voltage_limit(12000);
	BackLeftMotor.set_voltage_limit(12000);
	BackRightMotor.set_voltage_limit(12000);
}
	
	
if (KILLMODE == false){
// 4 motor drive
 	FrontLeftMotor.move(100*(((1-curve)*left)/100+(curve*pow(left/100,7))));
 	FrontRightMotor.move(100*(((1-curve)*right)/100+(curve*pow(right/100,7))));
  	BackLeftMotor.move(100*(((1-curve)*left)/100+(curve*pow(left/100,7))));
 	BackRightMotor.move(100*(((1-curve)*right)/100+(curve*pow(right/100,7))));}
else if (KILLMODE ==  true){
		FrontLeftMotor.move_voltage(30000 * left);
		BackLeftMotor.move_voltage(30000 * left);
		FrontRightMotor.move_voltage(30000 * right);
		BackRightMotor.move_voltage(30000 * right);
	}


		pros::delay(20); //delay for resource saving
		
	}
}