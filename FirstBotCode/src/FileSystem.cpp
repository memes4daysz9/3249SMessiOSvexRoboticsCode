#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "Odom.h"


void WriteSaveConfig(string FilePath,string FileSave){

FILE* SaveFile = fopen(FilePath, w);
fprintf(SaveFile, FileSave);

}

string ReadSaveConfig(string FilePath, int LineNumber){

FILE* ReadFile = fopen(FilePath, r);

    int lineCount;
    char line[PIDMaxLines][100]; // Array to store lines

    while (fgets(line[lineCount], sizeof(line[lineCount]), file) != NULL && lineCount < MAX_LINES) {
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