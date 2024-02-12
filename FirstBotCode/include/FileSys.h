#include "main.h"

#define PIDMaxLines 7 // Maximum number of lines to read

class SysFiles{
    public:
    char line[PIDMaxLines][100]; // PID Array to store lines
    SysFiles();
    void WriteSaveConfig(string FileSave);
    string ReadSaveConfig(string FilePath, int LineNumber);    
}
extern SysFiles SysFiles;
