#include "Screen.h"
#include "main.h"
#include "Odom.h"
#include "Auton.h"



void AutonRun(){
    pros::ADIDigitalOut FirstWingMan(1 ,'a');
	pros::ADIDigitalOut SecondWingMan(2 ,'b');


if(AutonSide = 1){
	
Forward(5);
Rotate(90);
Forward(6);
Rotate(-45);
SecondWingMan.set_value(HIGH);
Forward(6);
Rotate(-45);
SecondWingMan.set_value(LOW);
Forward(24);

}else if (AutonSide = 2){
//yes matchload blue
 Forward(5);
 Rotate(-135);
 FirstWingMan.set_value(HIGH);
 Forward(7);
 Rotate(225);
 Forward(6):
 Rotate(90);
 Forward(36);
 
}else if(AutonSide = 3){
//Red Yes matchload
Forward(5);
Rotate(-45);
FirstWingMan.set_value(HIGH);
Forward(12);
Rotate(-135);
Forward(36);
Rotate(-45);

}else if (AutonSide = 4){

Forward(5);
Rotate(90);
Forward(6);
Rotate(45);
SecondWingMan.set_value(HIGH);
Forward(6);
Rotate(45);
Forward(24);
}else{
	Rotate(720);
}
}

