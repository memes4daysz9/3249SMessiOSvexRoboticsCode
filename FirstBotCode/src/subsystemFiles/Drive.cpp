#include "Drive.h"
#include "globals.cpp"


pros::Controller MainController (pros::E_CONTROLLER_MASTER);

    pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);
	//urgay please send help
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
        FrontRightMotor.move(VerticalPower + RotatePower);
        BackRightMotor.move(VerticalPower + RotatePower);

		pros::delay(20); //delay for resource saving

	}}