#include"main.h"
#include "globals.cpp"

extern int PowerSavingMode = 0; //-1 = Extra Power mode. 0 is normal mode. 1 is moderate power saving mode. 2 is minor power saving mode. 3 is major poower saving mode. 
void competition_initialize() { // Checks the initial power state then sets the power saving mode accordingly
    while (true){
    if (PowerSavingButton.get_new_press()){
        if (PowerSavingMode <= 2){
            PowerSavingMode += 1; //cycles the power saving mode then tells the controller and the brain the said power saving mode
            MainController.set_text(2,0, "PowerSavingSetting now at " + PowerSavingMode); 
        }else {
            PowerSavingMode = -1;// when its at max,
        }
        
    }
    pros::delay(250);
    }

    if (PowerSavingMode < 1){
        FrontLeftMotor.set_voltage_limit(13000);
        BackLeftMotor.set_voltage_limit(13000); //maxing out the motors. note these motors will and shall NEVER go past this limit
        FrontRightMotor.set_voltage_limit(13000);
        BackRightMotor.set_voltage_limit(13000);
    }else if(PowerSavingMode == 1){
        FrontLeftMotor.set_voltage_limit(10000);
        BackLeftMotor.set_voltage_limit(10000); //Current limited the motors
        FrontRightMotor.set_voltage_limit(10000);
        BackRightMotor.set_voltage_limit(10000);
    }else{
        FrontLeftMotor.set_voltage_limit(8400);
        BackLeftMotor.set_voltage_limit(8400); //Current limited the motors
        FrontRightMotor.set_voltage_limit(8400);
        BackRightMotor.set_voltage_limit(8400);
    }
if (PowerSavingMode == -1){
    ArmMotor.set_voltage_limit(10000);
    ArmMotor2.set_voltage_limit(10000);
    ClawLeftMotor.set_voltage_limit(10000);
    ClawRightMotor.set_voltage_limit(10000);
}else{
    ArmMotor.set_voltage_limit(5000);
    ArmMotor2.set_voltage_limit(5000);
    ClawLeftMotor.set_voltage_limit(5000);
    ClawRightMotor.set_voltage_limit(5000);
    }
    

}
