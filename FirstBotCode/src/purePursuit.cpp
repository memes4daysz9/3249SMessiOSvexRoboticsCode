#include "main.h"
//your average waypoint system
//X then Y
const int num;//number of points
const TotalTolerance = 30;
void WayPointMovement(){ //moves through straight Waypoints NOT PUREPURSUIT

int currCordNum = 0;
double[2] currentCord;
double[2] PastCord = {0,0};//would be the cordinate the bot is at
int[num][num] cords = {{5},{5}};
double NeededHeading;
double NeededDistance;
double LineA;
double LineB;
double HeadingError;
double ForwardError;
for(int i; i < num; i++){
LineA = currentCord[0] - PastCord[0];
LineB = currentCord[1] - PastCord[1];
while (abs(HeadingError + ForwardError) > TotalTolerance){
NeededDistance = sqrt(pow(LineA)+pow(LineB));//this would also the hypotnuse
NeededHeading = (cos(NeededDistance/LineA)/M_PI)*180;

}
}
}
void PurePursuitMovement(){
    
}



