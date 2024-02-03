/*#include "main.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "Odom.h"
#include "SaveTemplates.h"

#define PIDMaxLines 7 // Maximum number of lines to read
#define PID "PID"

void WriteSaveConfig(std::string FilePath,std::string WhatToSave){
FILE* SaveFile;

if (WhatToSave == PID){
SaveFile = fopen("/usd/RoboticsSaveFile/PID.Robo","r+");
std::fprintf(SaveFile, PIDSave);
}


}

std::string ReadSaveConfig(std::string FilePath, int LineNumber){
FILE* ReadFile;
ReadFile = fopen("/usd/RoboticsSaveFile/PID.txt","r+");

    int lineCount;
    char line[PIDMaxLines][100]; // Array to store lines

    while (fgets(line[lineCount], sizeof(line[lineCount]), ReadFile) != NULL && lineCount < PIDMaxLines) {
        lineCount++;
    }
    fclose(ReadFile);


}




/*
For DriveTrain PIDs

kP
jI
kP

For The Flyhwheel Controller

kP
kI
kD
Num Type Of Controller 1 = FeedForward 2 = PID 3=Basic move velocity 100%



*/
