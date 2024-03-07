#include "main.h"
using namespace std;//gets the funny file system info
void initialize() {
    pros::Task OdomTask(OdomTracking); //multithreading W
    pros::Task ScreenTask(ScreenStats);
    pros::ADIDigitalOut FirstWingMan(1 ,'a');//solonoid calling
	pros::ADIDigitalOut SecondWingMan(2 ,'b');
    FirstWingMan.set_value(LOW);//da kenny fix
    SecondWingMan.set_value(LOW);
    pros::screen::set_eraser(COLOR_BLACK);
    //MotorsInitialization
    pros::Motor FrontLeftMotor_initializer(1, pros::E_MOTOR_GEARSET_18, false,pros::E_MOTOR_ENCODER_DEGREES);
    pros::Motor FrontRightMotor_initializer(2,pros::E_MOTOR_GEARSET_18, true,pros:: E_MOTOR_ENCODER_DEGREES);//initializes the motors... not sure if they are working as of this moment
    pros::Motor BackLeftMotor_initializer(3, pros::E_MOTOR_GEARSET_18, false,pros::E_MOTOR_ENCODER_DEGREES);//drivetrain motors
    pros::Motor BackRightMotor_initializer(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
    //others
    pros::Motor CataMotor_initializer(5, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor Intake_initializer(6, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);//other motors
    pros::Motor LeftMiddleMotor_initializer(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
    pros::Motor RightMiddleMotor_initializer(8, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
    
    pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);
	pros::Motor FlyMotor(5);
	pros::Motor Intake(6);
	pros::Motor LeftMiddleMotor(7);
	pros::Motor RightMiddleMotor(8);

    if (pros::usd::is_installed()){ // filesystem currently not avaliable... definitly at worlds if somehow i make it
        ofstream CurrentLog ("/usd/LogData.txt");
    }
}
