#include "main.h"
void initialize() {

    pros::Task OdomTask(OdomTracking); //multithreading W
    pros::Task ScreenTask(ScreenStats);
    //MotorsInitialization
    pros::Motor FrontLeftMotor_initializer(1, pros::E_MOTOR_GEARSET_18, false,pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor FrontRightMotor_initializer(2,pros::E_MOTOR_GEARSET_18, true,pros:: E_MOTOR_ENCODER_COUNTS);
    pros::Motor BackLeftMotor_initializer(3, pros::E_MOTOR_GEARSET_18, false,pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor BackRightMotor_initializer(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
    //others
    pros::Motor CataMotor_initializer(5, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor Intake_initializer(6, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor LeftShotBlock_initializer(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor RightShotBlock_initializer(8, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
}
