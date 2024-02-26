#include "main.h"


	double diameter = 4.125f;//diameter of the omni wheels for distance measuring

	float radius = diameter * 0.5;//radius of the omni wheel for distance measuring

	float pi =  3.14;//just a shorter  pi for easier processing which is at 3.14

    int LeftMotorEncoder; // takes the encoder values from the the left motors and averages them

    int RightMotorEncoder; // takes the encoder values from the the left motors and averages them

    int calculatedFlywheelRPM;// calculates the rpm based on the gear ratio i added

    const int Tolerance = 12;//fixed variable for the error to try to get the motors degrees in this range
    const int RotationTolerance = 10;

    float kP; //nothin... this isnt here at all im not lazy...
    float kI; // universals for DriveTrain PID
    float kD;

    float Left;
    float Right;

    float DeltaLeft;
    float DeltaRight;
    float DeltaFacing;

    float LastLeft; //for delta calculations
    float LastRight;
    float LastFacing;

    float LeftDistance; // distance traveled
    float RightDistance;
        
    const float TrackLength = 11.75;

    float Facing;
    float AverageOrentation;
    float DistanceOffset;

    double heading;

Odom::Odom(){//calls the variables inside class
    float FkD;
    float FKi;
    float FkP;//universals for FlywheelPID
    float FKa;
    int RightMotorEncoder;
    int LeftMotorEncoder;
    float PID;
    float error;
    float X;
    float Y;
}
  
int Odom::sgn(int val) { //signum function
    if (val > 0){
        return (1);
    }else if (val < 0) {
        return (-1);
    }else {
        return (0);
    }}
int abs(float Value){//absolute value
    if(Value < 0){
        return -Value;
    }else {
        return Value;
    }
}
void Odom::ClearTrackers(){//resets the positions
    pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);


    FrontLeftMotor.tare_position();
    FrontRightMotor.tare_position();
    BackLeftMotor.tare_position();
    BackRightMotor.tare_position();

    while(heading != 0){
        heading = 0;
    }
}
double degRad(double x) {
    return (x * (M_PI/180));
}
double radDeg(double x) {
    return (x* (180/M_PI));
}
void OdomTracking(){
    
    pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);

    double lastPosition[4]; // x,y then left and right rotations in inches
    double lastHeading; // last Theta value
        double motorLeftAvg = 0;
        double motorRightAvg = 0;
        double distanceOffset = 0;
        double deltaLeft = 0;
        double deltaRight = 0;
        double distLeft = 0;
        double distRight = 0;
        double newHeading = 0;
        double orientationAvg = 0;
        double cartToPolarR = 0;  
        double cartToPolarθ = 0;
        double deltaAngle = 0;
        double gearRatio = 1;
        double TrackLength;
        double wheelSize = diameter;
        double trackLength = 11.75;
        double position[4];
        while (true) { // ONLY INITIALIZE AS THREAD, NEVER FUNCTION

  /*      for (int i = 0; i < std::size(motorPortLeft); ++i) {
            motorLeftAvg = motorLeftAvg + pros::c::motor_get_position(motorPortLeft[i]);
            motorRightAvg = motorRightAvg + pros::c::motor_get_position(motorPortRight[i]);
        } */
        odom.LeftMotorEncoder = FrontLeftMotor.get_position();
        odom.RightMotorEncoder = FrontRightMotor.get_position();

        motorLeftAvg = -1 * FrontLeftMotor.get_position() * gearRatio;
        motorRightAvg = -1 * BackRightMotor.get_position()* gearRatio;
        deltaLeft = (motorLeftAvg - lastPosition[2]);
        deltaRight = (motorRightAvg - lastPosition[3]);
        distLeft = degRad(deltaLeft) * (wheelSize/2);
        distRight = degRad(deltaRight) * (wheelSize/2);  

        heading = heading + ((distLeft - distRight)/trackLength); 
      //  heading = pros::c::imu_get_heading(11);
        deltaAngle = heading - lastHeading;
        if(deltaAngle < 0.1) {
            if (distRight == 0) { 
            distanceOffset = distRight;
            }
            else {
                distanceOffset = distLeft;
            }
        }
        else {

            if (distRight == 0) { 
                distanceOffset = 2*sin(heading/2) * (distRight/deltaAngle + (trackLength/2)); // this is the distance travelled, it will be added to "distance" which is purely a PID variable that does not matter whatsoever. 
            }
            else {
                distanceOffset = 2*sin(heading/2) * (distLeft/deltaAngle + (trackLength/2)); // this is the distance travelled, it will be added to "distance" which is purely a PID variable that does not matter whatsoever. 
            }    
        }
        orientationAvg = lastHeading + deltaAngle/2;
        cartToPolarR = distanceOffset;  
        cartToPolarθ = 0; 
        position[0] = cartToPolarR*cos(cartToPolarθ-orientationAvg)+position[0];
        position[1] = cartToPolarR*sin(cartToPolarθ-orientationAvg)+position[1];

        
        lastPosition[0] = position[0]; 
        lastPosition[1] = position[1];
        lastPosition[2] = motorLeftAvg;
        lastPosition[3] = motorRightAvg;
        lastHeading = heading;
 
        pros::delay(10);   
        // DEBUG FUNCTIONS
    
     pros::screen::print(pros::E_TEXT_MEDIUM,1,"X: %f", position[0]);
     pros::screen::print(pros::E_TEXT_MEDIUM,2,"Y: %f", position[1]);
     pros::screen::print(pros::E_TEXT_MEDIUM,3,"Head: %d", int(radDeg(heading)));
 //    pros::lcd::print(3,"kms: %f", distanceOffset);
 //    pros::lcd::print(4,"z: %f", position[0]);
 //    pros::lcd::print(5,"j: %f", position[1]);
    
    }
}
void Odom::Forward(float WantedDistance){ //distance in inches
	// for every 360degrees, the wheel will go its circumference
    bool TargetMet;
	pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);
    pros::Controller MainController(pros::E_CONTROLLER_MASTER);//main controller

	BackLeftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	FrontRightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	BackRightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    FrontLeftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	float circumference =pi*diameter;//funny geometry calculation
    odom.ClearTrackers();

	float distancePerDegree = circumference/360;//more funny calculations

	float AngleInDegrees = WantedDistance/distancePerDegree;// forwards angle movement
    bool variablebug = false; //i belive this is the way to go about fixing funny variables... dunno how it does it but it does it
    float P;
    float I;
    float D;
    float LastError;//gets the error from the last loop
    float MotorAdjuster;
    odom.LeftTarget = AngleInDegrees + odom.LeftMotorEncoder;//668 for 5 in
    odom.RightTarget = AngleInDegrees + odom.RightMotorEncoder;
    odom.error = Tolerance + 10; //kickstarts the loop
while ((abs(error) > Tolerance)){//PID Loop W
//pid Calculations
    odom.error = ((odom.LeftTarget - odom.LeftMotorEncoder) + (odom.RightTarget - odom.RightMotorEncoder))/2;
    P = error * 75;
    I = (I+odom.error) *0.05;
    D = (odom.error - LastError) * 10;
    pros::screen::print(pros::E_TEXT_MEDIUM,4,"Individual PID Values %f,%f,%f",P,I,D);
    pros::screen::print(pros::E_TEXT_MEDIUM,5,"Error %f",odom.error);
    pros::screen::print(pros::E_TEXT_MEDIUM,6,"Left%f",odom.LeftMotorEncoder);
    pros::screen::print(pros::E_TEXT_MEDIUM,7,"Right%f",odom.RightMotorEncoder);

    odom.PID = P + I + D;

//LeftAndRightCorrections
MotorAdjuster = LeftMotorEncoder - RightMotorEncoder;

//Motor OutPut
	FrontLeftMotor.move_voltage(odom.PID - MotorAdjuster);
	BackLeftMotor.move_voltage(odom.PID - MotorAdjuster);
	FrontRightMotor.move_voltage(odom.PID + MotorAdjuster + 50);
	BackRightMotor.move_voltage(odom.PID + MotorAdjuster + 50);

    pros::delay(20);// delays the loop from calling everything else, helps to keep things cool inside the brain and saves battery

    if (odom.error == LastError){//helps fix stuf
            MainController.print(0,0,"PID Error!");
            variablebug = true;
            	FrontLeftMotor.move_voltage(6000);
	            BackLeftMotor.move_voltage(6000);
	            FrontRightMotor.move_voltage(6000);
	            BackRightMotor.move_voltage(6000);//PID boost
                pros::delay(20);
            	FrontLeftMotor.move_voltage(0);
	            BackLeftMotor.move_voltage(0);
	            FrontRightMotor.move_voltage(0);
	            BackRightMotor.move_voltage(0);              
        }
    LastError = odom.error;//haha heres where it gets the last error

                if (abs(error) <= Tolerance) {
            break;
        }
    }
    FrontLeftMotor.brake();
    BackLeftMotor.brake();
    FrontRightMotor.brake();
    BackRightMotor.brake();

}

void Odom::Rotate(float DegreesToRotate) {
    pros::Motor FrontLeftMotor(1);
    pros::Motor FrontRightMotor(2);
    pros::Motor BackLeftMotor(3);
    pros::Motor BackRightMotor(4);
    pros::Controller MainController(pros::E_CONTROLLER_MASTER);//main controller
    // Constants for PID control
    odom.ClearTrackers();
    const float kP = 0.3;
    const float kI = 0.1;
    const float kD = 0.3;
    const int maxVoltage = 12000;
    const float curve = -1.6;
    //90 Degrees needs a modifer
    //45 is fine
    
    // Initialize PID variables
    float P, I = 0, D;
    float LastError = 0;
    while (heading != 0){
            heading = 0;
    }

    // Set target encoder values
    odom.RightTarget = DegreesToRotate;
    // Main PID control loop
    if (DegreesToRotate > 0){
        odom.error = odom.RightTarget - int (radDeg(heading));
    }else {
        odom.error = int (radDeg(heading)) - odom.RightTarget;
    }
    
   while (abs(error) > RotationTolerance) {
        // Calculate error
        odom.error = int(radDeg(heading)) - odom.RightTarget;
        //odom.error = odom.RightTarget - heading ;
        pros::screen::print(pros::E_TEXT_MEDIUM,4,"Error: %f", odom.error);
        pros::screen::print(pros::E_TEXT_MEDIUM,5,"RightTarget %f", odom.RightTarget);
        P = error * 200;
        I = (I+error) * 1;
        D = (odom.error - LastError)*15;
        odom.PID = P+I+D;
        // Adjust motor voltages based on PID output
        float right = -odom.PID;
        float left = odom.PID;
        
        FrontLeftMotor.move_voltage(left);
        BackLeftMotor.move_voltage(left);
        FrontRightMotor.move_voltage(right);
        BackRightMotor.move_voltage(right);
        
        // Update last error
        LastError = odom.error;
        
        // Delay to control loop rate
        pros::delay(20);
    }

    FrontLeftMotor.brake();
    BackLeftMotor.brake();
    FrontRightMotor.brake();//brake
    BackRightMotor.brake();
}


void Odom::RunFlywheel(int target){

pros::Motor CataMotor(5);

int prevCalculatedFlywheelRPM;//different PID only its now just a P and no I and D
const int FlywheelGearRatio = 7; //look here it is!
float K;
float P;
float DT;// delta Target RPM
int prevTarget; // for delta calculations
float Output;//voltage for the motors to use
float error;// the distance from the target
float a;
float DeadLength;
while (true){
    

    calculatedFlywheelRPM = CataMotor.get_actual_velocity() * FlywheelGearRatio;//calc for flywheel rpm
    int accel = calculatedFlywheelRPM - prevCalculatedFlywheelRPM; //  glorified deltaRPM
	float FF = FKi * sgn(calculatedFlywheelRPM) + FkD * calculatedFlywheelRPM + FKa * accel;  //FF calc(cant say what it is lmao)
	odom.error = target - calculatedFlywheelRPM;//error
	Output = P*FF;//motor output
    CataMotor.move_voltage(Output);
    while (target == 0){//cool motor cooling feature when not needed
        CataMotor.move_voltage(0); // helps keep the motors not try to apply voltage to stop it
        Output = 0;
    }
    pros::delay(250); // allows for deltas to properly work
    prevCalculatedFlywheelRPM = calculatedFlywheelRPM;

    }
}