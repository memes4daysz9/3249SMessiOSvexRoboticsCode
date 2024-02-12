#include "main.h"


class Odom{
    public:
    float kP;
    float kI; // universals for DriveTrain PID
    float kD;


    float FkD;
    float FKi;
    float FkP;//universals for FlywheelPID
    float FKa;
    Odom();
    void OdomTracking();
    bool Forward(float WantedDistance);
    bool Rotate(float DegreesToRotate);
    void RunFlywheel(int target);


    int sgn(int val);
}
extern Odom Odom;