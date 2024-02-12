#include "main.h"



int PixelPos = 0;
bool autonSelected = false;
int AutonSide = 0;
void competition_initialize() {
	pros::screen_touch_status_s_t TouchPos; //auton selector
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
        TouchPos = pros::screen_touch_status();
                    if (TouchPos.y > 100){//blue Side
                if (TouchPos.x < 240||MainController.get_digital(DIGITAL_UP)){
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
            pros::screen::print(pros::E_TEXT_MEDIUM,1,"flywheel RPM: ",calculatedFlywheelRPM);
            pros::screen::print(pros::E_TEXT_MEDIUM,2,"Brain Battery:",pros::battery::get_capacity(),"ControllerBattery:",MainController.get_battery_level());
            pros::screen::print(pros::E_TEXT_MEDIUM,3,"        Pnumatics");
            pros::screen::print(pros::E_TEXT_MEDIUM,4,"left: %s",FirstWingMan);
            pros::screen::print(pros::E_TEXT_MEDIUM,5,"right: %s",SecondWingMan);
            //end Brain Screen func and now controller functions
            if (calculatedFlywheelRPM >=100){
                MainController.print(0,0,"RPM:",calculatedFlywheelRPM);
                if (calculatedFlywheelRPM >= 1400){
                        MainController.rumble(". .");
                }else if (calculatedFlywheelRPM >= 1200){
                        MainController.rumble("- - -");
                }
            }
            MainController.print(1,0,"LeftWing",FirstWingMan);
            MainController.print(2,0,"RightWing",SecondWingMan);
            pros::delay(500); //half second updates
            

            
            
        
    }
}





