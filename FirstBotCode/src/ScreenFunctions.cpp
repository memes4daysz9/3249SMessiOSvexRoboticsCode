#include "main.h"



int PixelPos = 0;
bool autonSelected = false;
int AutonSide = 0;
void competition_initialize() {
	pros::screen_touch_status_s_t TouchPos; //auton selector
    pros::Controller MainController(pros::E_CONTROLLER_MASTER);
    pros::screen::set_pen(COLOR_RED);
    pros::screen::fill_rect(1,100,480,200);
    pros::screen::set_pen(COLOR_BLUE);
    pros::screen::fill_rect(1,1,480,100);
    pros::screen::set_pen(COLOR_BLACK);
    pros::screen::draw_line(240,0,240,200); //Vertical Line
    pros::screen::draw_line(0,100,480,100); //Horizontal Line
    pros::screen::set_pen(COLOR_WHITE);
    while (AutonSide == 0){
                //blue Side
                if (MainController.get_digital(DIGITAL_UP) && !MainController.get_digital(DIGITAL_B)){
                    AutonSide = 1; // no matchloading blue 
                }else if (MainController.get_digital(DIGITAL_UP) && MainController.get_digital(DIGITAL_B)) {
                    AutonSide = 2; // yes matchloading blue
                }//red Side
                if (MainController.get_digital(DIGITAL_DOWN) && MainController.get_digital(DIGITAL_B)){
                    AutonSide = 3; // yes matchload red
                }else if (MainController.get_digital(DIGITAL_DOWN) && !MainController.get_digital(DIGITAL_B)) {
                    AutonSide = 4; // no matchload red
                }
        }
        pros::delay(100);
    }
void ScreenStats(){
    pros::ADIDigitalOut FirstWingMan(1 ,'a');
	pros::ADIDigitalOut SecondWingMan(2 ,'b');
    pros::Controller MainController(pros::E_CONTROLLER_MASTER); //port conifigs


    while (true){
            pros::screen::set_pen(COLOR_BLACK);
            pros::screen::fill_rect(1,1,480,240); // this is after auton is selected
            pros::screen::set_pen(COLOR_WHITE);
            pros::screen::print(pros::E_TEXT_MEDIUM,1,"flywheel RPM:  %d",calculatedFlywheelRPM);
            pros::screen::print(pros::E_TEXT_MEDIUM,2,"Brain Battery:  %d",pros::battery::get_capacity());
            pros::screen::print(pros::E_TEXT_MEDIUM,3,"ControllerBattery:  %d",MainController.get_battery_level())
            pros::screen::print(pros::E_TEXT_MEDIUM,4,"Reft Side DriveTrain: %d",Odom::LeftMotorEncoder);
            pros::screen::print(pros::E_TEXT_MEDIUM,5,"Right Side DriveTrain %d",Odom::RightMotorEncoder);
            //end Brain Screen func and now controller functions
            if(AutonSide == 0){
                MainController.print(0,0,"Autonomus Not Selected!");
            }
            MainController.print(0,0,"AutonSide:%d",AutonSide);
            pros::delay(10);    
    }
}
void AutonStats(){//polls all related odometry functions for debuigging in autonomus
        pros::screen::set_pen(COLOR_BLACK);
        pros::screen::fill_rect(1,1,480,240); // this is after auton is selected
        pros::screen::clear();
        pros::screen::set_pen(COLOR_WHITE);
    while(pros::competition::is_autonomous()){
        pros::screen::print(pros::E_TEXT_MEDIUM,1,"PID: %d",Odom::PID);
        pros::screen::print(pros::E_TEXT_MEDIUM,2,"Error: %d",Odom::error);
        pros::screen::print(pros::E_TEXT_MEDIUM,3,"Reft Side DriveTrain: %d",Odom::LeftMotorEncoder);
        pros::screen::print(pros::E_TEXT_MEDIUM,4,"Right Side DriveTrain %d",Odom::RightMotorEncoder);
        pros::delay(100);


    }
}