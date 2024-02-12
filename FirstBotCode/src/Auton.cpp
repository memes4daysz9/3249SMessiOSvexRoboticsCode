#include "main.h"




void autonomous(){
    pros::ADIDigitalOut FirstWingMan(1 ,'a');
	pros::ADIDigitalOut SecondWingMan(2 ,'b');
	pros::Motor CataMotor(5);

if(AutonSide == 1){
Odom::Forward(5);
Odom::Rotate(90);
Odom::Forward(6);
Odom::Rotate(-45);
SecondWingMan.set_value(HIGH);
Odom::Forward(6);
Odom::Rotate(-45);
SecondWingMan.set_value(LOW);
Odom::Forward(24);
//prime flywheel
Odom::RunFlywheel(1200);
pros::delay(3000);
Odom::RunFlywheel(0);

}else if (AutonSide == 2){
//yes matchload blue
 Odom::Forward(5);
 Odom::Rotate(-135);
 FirstWingMan.set_value(HIGH);
 Odom::Forward(7);
 Odom::Rotate(225);
 Odom::Forward(6);
 Odom::Rotate(90);
 SecondWingMan.set_value(HIGH);
 Odom::Forward(36);

 FirstWingMan.set_value(LOW);
 SecondWingMan.set_value(LOW);
 Odom::Forward(-24); //return to matchloader
 Odom::Rotate(-45);
 Odom::Forward(-24);
 //prime flywheel
Odom::RunFlywheel(1200);
pros::delay(3000);
Odom::RunFlywheel(0);

}else if(AutonSide == 3){
//Red Yes matchload
Odom::Forward(5);
Odom::Rotate(-45);
FirstWingMan.set_value(HIGH);
Odom::Forward(12);
Odom::Rotate(135);
Odom::Forward(36);
Odom::Rotate(-45);
SecondWingMan.set_value(HIGH);
Odom::Forward(36);
SecondWingMan.set_value(LOW);
FirstWingMan.set_value(LOW);
//return to matchloader
Odom::Forward(-36);
Odom::Rotate(-45);
Odom::Forward(-36);
//prime flywheel
Odom::RunFlywheel(1200);
pros::delay(3000);
Odom::RunFlywheel(0);

}else if (AutonSide == 4){

Forward(5);
Rotate(90);
Forward(6);
Rotate(45);
SecondWingMan.set_value(HIGH);
Forward(6);
Rotate(45);
Forward(24);
//prime flywheel
RunFlywheel(1200);
pros::delay(3000);
RunFlywheel(0);
}else{
	odom::Forward(10);
}
}

