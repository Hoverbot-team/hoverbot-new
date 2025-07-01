/*
implements a log function
to use it 
logger.log(string)
*/
#ifndef LOG_H
#define LOG_H
//libs needed
#include <iostream>
#include <fstream>
#include <ctime>
//class
class logger {
public:
    void log(const std::string& new_log);  // Pass by const reference
};
extern logger logs;
#endif
