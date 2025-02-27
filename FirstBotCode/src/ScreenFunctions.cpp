#include "main.h"




int AutonSide = 0; // selects the side for autonomus period. more will be explained later
void competition_initialize() {
    pros::Controller MainController(pros::E_CONTROLLER_MASTER); // declaring The Main Controller to a variable
    pros::screen::set_pen(COLOR_RED);//sets every screen function to the color of red AKA. pen color
    pros::screen::fill_rect(1,100,480,200);//fills the bottom with red with pen color
    pros::screen::set_pen(COLOR_BLUE);//set pen color with to blue
    pros::screen::fill_rect(1,1,480,100);//fills top with pen color
    pros::screen::set_pen(COLOR_BLACK);//sets to black
    pros::screen::draw_line(240,0,240,200); //Vertical Line as a divider
    pros::screen::draw_line(0,100,480,100); //Horizontal Line as a divider
    pros::screen::set_pen(COLOR_WHITE);// sets pen to white
    while (AutonSide == 0){
                //blue Side
                if (MainController.get_digital(DIGITAL_UP) && !MainController.get_digital(DIGITAL_B)){ // if your pressing the up button on the controller and NOT the B button:
                    AutonSide = 1; // no matchloading blue 
                }else if (MainController.get_digital(DIGITAL_UP) && MainController.get_digital(DIGITAL_B)) {// if your pressing the up button on the controller AND the B button:
                    AutonSide = 2; // yes matchloading blue
                }//red Side
                if (MainController.get_digital(DIGITAL_DOWN) && MainController.get_digital(DIGITAL_B)){// if your pressing the down button on the controller AND the B button:
                    AutonSide = 3; // yes matchload red
                }else if (MainController.get_digital(DIGITAL_DOWN) && !MainController.get_digital(DIGITAL_B)) {// if your pressing the down button on the controller and NOT the B button:
                    AutonSide = 4; // no matchload red
                }
        }
        pros::delay(100);// delays the loop from calling everything else, helps to keep things cool inside the brain and saves battery
    }
void ScreenStats(){
    pros::ADIDigitalOut FirstWingMan(1 ,'a');//calls the left solonoid into funny pun
	pros::ADIDigitalOut SecondWingMan(2 ,'b');//declares the right solonoid into another funny pun
    pros::Controller MainController(pros::E_CONTROLLER_MASTER); //MainController assinging in here

    pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);
	pros::Motor FlyMotor(5);
	pros::Motor Intake(6);
	pros::Motor LeftMiddleMotor(7);
	pros::Motor RightMiddleMotor(8);


    while (AutonSide != 3){
            pros::screen::set_pen(COLOR_BLACK);//set pen color
            pros::screen::fill_rect(1,1,480,240); // this is after auton is selected... fills entire screen
            pros::screen::set_pen(COLOR_WHITE);//set pen color
            pros::screen::print(pros::E_TEXT_MEDIUM,1,"flywheel RPM:  %d",calculatedFlywheelRPM);//displays the flywheel RPM at the first line
            pros::screen::print(pros::E_TEXT_MEDIUM,2,"Brain Battery:  %f",pros::battery::get_capacity());//gets the brain battery... dont ask what the unit is i have no idea
            pros::screen::print(pros::E_TEXT_MEDIUM,3,"ControllerBattery:  %d",MainController.get_battery_level());//controller battery in Mah i belive
            pros::screen::print(pros::E_TEXT_MEDIUM,4,"Reft Side DriveTrain: %d",odom.LeftMotorEncoder);//gets the averaged left side drivetrain encoder
            pros::screen::print(pros::E_TEXT_MEDIUM,5,"Right Side DriveTrain %d",odom.RightMotorEncoder);//gets the averaged right side drivetrain encoder calculation, found in odom.cpp and odom.hpp
            pros::screen::print(pros::E_TEXT_MEDIUM,6,"PID: %f",odom.PID);//gets the PID voltage coming from the motors
            pros::screen::print(pros::E_TEXT_MEDIUM,7,"Error: %f",odom.error);//gets the error from where its supposed to be to where its at right
            pros::screen::print(pros::E_TEXT_MEDIUM,8,"Left Target: %f",odom.LeftTarget);
            pros::screen::print(pros::E_TEXT_MEDIUM,9,"Right Target: %f",odom.RightTarget);
            //end Brain Screen func and now controller functions
            if(AutonSide == 0){ //yelling function
                MainController.print(0,0,"Autonomus Not Selected!");//yells in controller
            }
            MainController.print(0,0,"AutonSide:%d",AutonSide);//gets the autonside name
            pros::delay(100); // delays the loop from calling everything else, helps to keep things cool inside the brain and saves battery   
    }
    while (AutonSide == 3){ // temp function essentially
        pros::screen::set_eraser(COLOR_BLUE);
        pros::screen::erase();
        pros::delay(500);
        pros::screen::print(pros::E_TEXT_MEDIUM,1,"Left Motors in C %d,%d,%d",FrontLeftMotor.get_temperature(),LeftMiddleMotor.get_temperature(),BackLeftMotor.get_temperature());
        pros::screen::print(pros::E_TEXT_MEDIUM,2,"Right Motors in C %d,%d,%d",FrontRightMotor.get_temperature(),RightMiddleMotor.get_temperature(),BackRightMotor.get_temperature());   
        pros::delay(500);
    }
}