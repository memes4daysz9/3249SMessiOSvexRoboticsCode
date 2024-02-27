#include "main.h"

Odom odom; //calls the object


void autonomous(){ //auton function
    pros::ADIDigitalOut FirstWingMan(1 ,'a');
	pros::ADIDigitalOut SecondWingMan(2 ,'b');
	pros::Motor CataMotor(5);
	pros::Motor Intake(6);
	


if(AutonSide == 1){
	pros::Task AutonPoll(AutonStats);
odom.Forward(30);
Intake.move_velocity(600);
odom.ClearTrackers();
pros::delay(600);
odom.Forward(-30);
odom.ClearTrackers();
odom.Rotate(-420);
FirstWingMan.set_value(1);
odom.Forward(7);
odom.Rotate(89);
odom.ClearTrackers();
pros::delay(10);
odom.Forward(18);
odom.Rotate(89);
odom.Forward(8);
Intake.move_velocity(-600);


}else if (AutonSide == 2){
odom.Forward(2.5);
odom.Rotate(300);
FirstWingMan.set_value(HIGH);
odom.Forward(16);
odom.Rotate(320);
odom.Forward(13);
odom.Rotate(360);
odom.Forward(48.5);



}else if(AutonSide == 3){

}else if (AutonSide == 4){
	//red no matchload
}else{
	int P1[2] = {0,0};
	int P2[2] = {12,0};
	int P3[2] = {12,12};
	odom.PurePursuitThreeHandles(P1,P2,P3);
}
}

