#include "main.h"
#include "pros/colors.h"
#include "pros/screen.hpp"
#include "globals.h"

int PixelPos = 0;
bool autonSelected = false;
int AutonSide = NULL;

void ScreenStats(){
    pros::ADIDigitalOut FirstWingMan(1 ,'a');
	pros::ADIDigitalOut SecondWingMan(2 ,'b');

    pros::screen_touch_status_s_t TouchPos;
    pros::screen::set_pen(COLOR_RED);
    pros::screen::fill_rect(1,100,480,200);
    pros::screen::set_pen(COLOR_BLUE);
    pros::screen::fill_rect(1,1,480,100);
    pros::screen::set_pen(COLOR_BLACK);
    pros::screen::draw_line(240,0,240,200); //Vertical Line
    pros::screen::draw_line(0,100,480,100); //Horizontal Line
    pros::screen::print(pros::TEXT_SMALL,60,25,"BlueSideNoMatchLoading");
    pros::screen::print(pros::TEXT_SMALL,120,25,"BlueSideYesMatchLoading");
    pros::screen::print(pros::TEXT_SMALL,60,75,"RedSideYesMatchLoading");
    pros::screen::print(pros::TEXT_SMALL,120,75,"RedSideNoMatchLoading");
    pros::screen::set_pen(COLOR_WHITE);
    pros::screen::print(pros::TEXT_SMALL,240,100, "Select Autonomous"); // screen is 480 by  240 pixels, meaning that half is at 240 by 100

    while (true){
        if ((autonSelected == false) || (AutonSide == nullptr)){
            if (TouchPos.y > 100){//blue Side
                if (TouchPos.x < 240){
                    AutonSide = 1; // no matchloading blue
                }else if (TouchPos.x > 240) {
                    AutonSide = 2; // yes matchloading blue
                }
            }else if (TouchPos.y < 100){//red Side
                if (TouchPos.x < 240){
                    AutonSide = 3; // yes matchload red
                }else if (TouchPos.x > 240) {
                    AutonSide = 4; // no matchload red
                }
            }
        pros::delay(100); //1/10 second updates
        }else{
            
            pros::screen::set_pen(COLOR_BLACK);
            pros::screen::fill_rect(1,1,480,240); // this is after auton is selected
            pros::screen::set_pen(COLOR_WHITE);
            pros::screen::print(pros::TEXT_MEDIUM,1,"flywheel RPM: ",calculatedFlywheelRPM);
            pros::screen::print(pros::TEXT_MEDIUM,2,"Brain Battery:",pros::battery::get_capacity(),"ControllerBattery:",MainController.get_battery_level());
            pros::screen::print(pros::TEXT_MEDIUM,3,"        Pnumatics");
            pros::screen::print(pros::TEXT_MEDIUM,4,"left:",FirstWingMan.get_value());
            pros::screen::print(pros::TEXT_MEDIUM,5,"right:",SecondWingMan.get_value());
            pros::delay(500); //half second updates
            
            
        }
    }
}





