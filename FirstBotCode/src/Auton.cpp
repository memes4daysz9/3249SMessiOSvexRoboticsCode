#include "main.h"

Odom odom;


void autonomous(){
    pros::ADIDigitalOut FirstWingMan(1 ,'a');
	pros::ADIDigitalOut SecondWingMan(2 ,'b');
	pros::Motor CataMotor(5);
	
odom.Forward(5);
odom.Rotate(90);
odom.Forward(6);
odom.Rotate(-45);
SecondWingMan.set_value(HIGH);
odom.Forward(6);
odom.Rotate(-45);
SecondWingMan.set_value(LOW);
odom.Forward(24);
//prime flywheel
odom.RunFlywheel(1200);
pros::delay(3000);
odom.RunFlywheel(0);

/*if(AutonSide == 1){

}else if (AutonSide == 2){
//yes matchload blue
 odom.Forward(5);
 odom.Rotate(-135);
 FirstWingMan.set_value(HIGH);
 odom.Forward(7);
 odom.Rotate(225);
 odom.Forward(6);
 odom.Rotate(90);
 SecondWingMan.set_value(HIGH);
 odom.Forward(36);

 FirstWingMan.set_value(LOW);
 SecondWingMan.set_value(LOW);
 odom.Forward(-24); //return to matchloader
 odom.Rotate(-45);
 odom.Forward(-24);
 //prime flywheel
odom.RunFlywheel(1200);
pros::delay(3000);
odom.RunFlywheel(0);

}else if(AutonSide == 3){
//Red Yes matchload
odom.Forward(5);
odom.Rotate(-45);
FirstWingMan.set_value(HIGH);
odom.Forward(12);
odom.Rotate(135);
odom.Forward(36);
odom.Rotate(-45);
SecondWingMan.set_value(HIGH);
odom.Forward(36);
SecondWingMan.set_value(LOW);
FirstWingMan.set_value(LOW);
//return to matchloader
odom.Forward(-36);
odom.Rotate(-45);
odom.Forward(-36);
//prime flywheel
odom.RunFlywheel(1200);
pros::delay(3000);
odom.RunFlywheel(0);

}else if (AutonSide == 4){

odom.Forward(5);
odom.Rotate(90);
odom.Forward(6);
odom.Rotate(45);
SecondWingMan.set_value(HIGH);
odom.Forward(6);
odom.Rotate(45);
odom.Forward(24);
//prime flywheel
odom.RunFlywheel(1200);
pros::delay(3000);
odom.RunFlywheel(0);
}else{
	odom.Forward(10);
}*/
}

