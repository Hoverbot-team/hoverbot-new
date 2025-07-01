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

using namespace std;
//class
class logger {
public:
    logger(string filePath);
    void log(const std::string& new_log);  // Pass by const reference
private:
    string path;  // Store the file path
};
extern logger logs;
#endif
