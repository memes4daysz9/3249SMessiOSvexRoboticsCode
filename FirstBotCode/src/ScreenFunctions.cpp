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
    pros::screen::print(pros::E_TEXT_SMALL,60,25,"BlueSideNoMatchLoading");
    pros::screen::print(pros::E_TEXT_SMALL,120,25,"BlueSideYesMatchLoading");
    pros::screen::print(pros::E_TEXT_SMALL,60,75,"RedSideYesMatchLoading");
    pros::screen::print(pros::E_TEXT_SMALL,120,75,"RedSideNoMatchLoading");
    pros::screen::print(pros::E_TEXT_SMALL,120,75, "Select Autonomous"); // screen is 480 by  240 pixels, meaning that half is at 240 by 100
    while (1){
        TouchPos = pros::screen::touch_status();
                    if (TouchPos.y > 100){//blue Side
                if (TouchPos.x < 240||(MainController.get_digital(DIGITAL_UP) && !MainController.get_digital(DIGITAL_B))){
                    AutonSide = 1; // no matchloading blue
                }else if (TouchPos.x > 240||(MainController.get_digital(DIGITAL_UP) && MainController.get_digital(DIGITAL_B))) {
                    AutonSide = 2; // yes matchloading blue
                }
            }else if (TouchPos.y < 100){//red Side
                if (TouchPos.x < 240||(MainController.get_digital(DIGITAL_DOWN) && MainController.get_digital(DIGITAL_B))){
                    AutonSide = 3; // yes matchload red
                }else if (TouchPos.x > 240||(MainController.get_digital(DIGITAL_DOWN) && !MainController.get_digital(DIGITAL_B))) {
                    AutonSide = 4; // no matchload red
                }
        }
        pros::delay(100);
    }
}
void ScreenStats(){
    pros::ADIDigitalOut FirstWingMan(1 ,'a');
	pros::ADIDigitalOut SecondWingMan(2 ,'b');
    pros::Controller MainController(pros::E_CONTROLLER_MASTER); //port conifigs


    while (true){

        
        
            
            pros::screen::set_pen(COLOR_BLACK);
            pros::screen::fill_rect(1,1,480,240); // this is after auton is selected
            pros::screen::set_pen(COLOR_WHITE);
            pros::screen::print(pros::E_TEXT_LARGE,1,"flywheel RPM:  %d",calculatedFlywheelRPM);
            pros::screen::print(pros::E_TEXT_LARGE,2,"Brain Battery:  %d",pros::battery::get_capacity());
            pros::screen::print(pros::E_TEXT_LARGE,3,"ControllerBattery:  %d",MainController.get_battery_level())
            pros::screen::print(pros::E_TEXT_LARGE,4,"Reft Side DriveTrain: %d",LeftMotorEncoder);
            pros::screen::print(pros::E_TEXT_LARGE,5,"Right Side DriveTrain %d",RightMotorEncoder);
            //end Brain Screen func and now controller functions
            if(AutonSide == 0){
                MainController.print(0,0,"Autonomus Not Selected!");
            }
            MainController.print(0,0,"AutonSide:%d",AutonSide);
            pros::delay(10); //half second updates
            

            
            
        
    }
}





