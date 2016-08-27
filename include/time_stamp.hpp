#pragma once

#include<windows.h>
#include<string>

char* getTimeStamp(char* buffer) {
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    sprintf(buffer, "[%02d:%02d:%02d.%03d]", sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
    return buffer;
}

std::string getTimeStamp() {
    char buffer[128];
    getTimeStamp(buffer);
    return std::string(buffer);
}