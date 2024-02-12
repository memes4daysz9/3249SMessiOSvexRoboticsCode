#include "main.h"




void autonomous(){
    pros::ADIDigitalOut FirstWingMan(1 ,'a');
	pros::ADIDigitalOut SecondWingMan(2 ,'b');
	pros::Motor CataMotor(5);

if(AutonSide == 1){
Forward(5);
Rotate(90);
Forward(6);
Rotate(-45);
SecondWingMan.set_value(HIGH);
Forward(6);
Rotate(-45);
SecondWingMan.set_value(LOW);
Forward(24);
//prime flywheel
RunFlywheel(1200);
pros::delay(3000);
RunFlywheel(0);

}else if (AutonSide == 2){
//yes matchload blue
 Forward(5);
 Rotate(-135);
 FirstWingMan.set_value(HIGH);
 Forward(7);
 Rotate(225);
 Forward(6);
 Rotate(90);
 SecondWingMan.set_value(HIGH);
 Forward(36);

 FirstWingMan.set_value(LOW);
 SecondWingMan.set_value(LOW);
 Forward(-24); //return to matchloader
 Rotate(-45);
 Forward(-24);
 //prime flywheel
RunFlywheel(1200);
pros::delay(3000);
RunFlywheel(0);

}else if(AutonSide == 3){
//Red Yes matchload
Forward(5);
Rotate(-45);
FirstWingMan.set_value(HIGH);
Forward(12);
Rotate(135);
Forward(36);
Rotate(-45);
SecondWingMan.set_value(HIGH);
Forward(36);
SecondWingMan.set_value(LOW);
FirstWingMan.set_value(LOW);
//return to matchloader
Forward(-36);
Rotate(-45);
Forward(-36);
//prime flywheel
RunFlywheel(1200);
pros::delay(3000);
RunFlywheel(0);

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
	Forward(10);
}
}

