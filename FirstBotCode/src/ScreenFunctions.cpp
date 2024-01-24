#include "main.h"
#include "pros/colors.h"
#include "pros/screen.hpp"

int PixelPos = 0;
bool autonSelected = false;
int AutonSide;

void ScreenStats(){
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
        if ((autonSelected = false)){
            if (TouchPos.y > 100){//blue Side
                if (TouchPos.x < 240){
                    AutonSide = 1; // no 
                    autonSelected = true;
                }else if (TouchPos.x > 240) {
                    AutonSide = 2;
                    autonSelected = true;
                }
            }else if (TouchPos.y < 100){//red Side
                if (TouchPos.x < 240){
                    AutonSide = 3;
                    autonSelected = true;
                }else if (TouchPos.x > 240) {
                    AutonSide = 4;
                    autonSelected = true;
                }
            }
        }else {
            if (autonSelected == true){
                pros::screen::set_pen(COLOR_BLACK);
                pros::screen::fill_rect(1,1,480,240);
                pros::screen::print(pros::E_TEXT_LARGE,5)
            }
            // start normal functions
        }
    }
}





