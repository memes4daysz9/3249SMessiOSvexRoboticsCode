#include "main.h"

#define PIDMaxLines 7 // Maximum number of lines to read

extern void WriteSaveConfig(string FileSave);
extern string ReadSaveConfig(string FilePath, int LineNumber);

extern char line[PIDMaxLines][100]; // PID Array to store lines