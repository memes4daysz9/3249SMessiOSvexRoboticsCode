extern void OdomTracking();
extern bool Forward(float WantedDistance);
extern bool Rotate(float DegreesToRotate); // must use an .h file for using a function multiple times
extern void RunFlywheel(int target);//runs the flywheel at a certain target RPM