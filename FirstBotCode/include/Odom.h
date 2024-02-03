extern void OdomTracking();
extern bool Forward(float WantedDistance);
extern bool Rotate(float DegreesToRotate); // must use an .h file for using a function multiple times
extern void RunFlywheel(int target);//runs the flywheel at a certain target RPM

extern float kP;
extern float kI; // universals for DriveTrain PID
extern float kD;


extern float FkD= 0.3;
extern float FKi= 0.3;
extern float FkP= 0.1;//flywheel
extern float FKa = 0.3;