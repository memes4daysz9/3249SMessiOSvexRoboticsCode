#include "main.h"

extern pros::Motor FrontLeftMotor_initializer(1, pros::E_MOTOR_GEARSET_18, false,pros::E_MOTOR_ENCODER_COUNTS);
extern pros::Motor FrontRightMotor_initializer(2,pros::E_MOTOR_GEARSET_18, true,pros:: E_MOTOR_ENCODER_COUNTS);
//front Motors


//Back Motors
extern pros::Motor BackLeftMotor_initializer(3, pros::E_MOTOR_GEARSET_18, false,pros::E_MOTOR_ENCODER_COUNTS);
extern pros::Motor BackRightMotor_initializer(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

extern pros::Motor CataMotor_initializer(5, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

extern pros::Motor Intake_initializer(6, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

extern pros::Motor LeftShotBlock_initializer(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
extern pros::Motor RightShotBlock_initializer(8, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);