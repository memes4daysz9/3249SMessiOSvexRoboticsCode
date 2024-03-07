#include "main.h"

Odom odom; //calls the object


void autonomous(){ //auton function
    pros::ADIDigitalOut FirstWingMan(1 ,'a');
	pros::ADIDigitalOut SecondWingMan(2 ,'b');
	pros::Motor CataMotor(5);
	


if(AutonSide == 1){
	pros::Task AutonPoll(AutonStats);
odom.Forward(5);
odom.Rotate(45);
odom.Forward(6);
FirstWingMan.set_value(HIGH);
odom.Forward(12);
odom.Rotate(135);
odom.Forward(16);


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
//motor OverHeating Protocall

}else if (AutonSide == 4){
	//red no matchload
}else{
	odom.Forward(2.5);
}
}

