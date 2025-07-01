#include "misc/logs/log.hpp"

using namespace std;
logger logs;
void logger::log(const string &new_log)
{
    time_t currentTime = time(nullptr);// time var
    string timeStr = ctime(&currentTime); // Convert time to string
    timeStr.pop_back();// Remove the newline character form time string

    ofstream file("/home/a/hoverbot/logs.txt", ios::app); //open log file in append mode
    if (file.is_open())
    {
        file << timeStr << ": " << new_log << endl; // Write log
    }
    else
    {
        cerr << "Error: Could not open file." << endl; // Error handling
    }
    file.close();
}
