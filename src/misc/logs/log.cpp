#include "misc/logs/log.hpp"

logger logs(std::string(getenv("HOME")) + "/hoverbot/logs/log.txt");

logger::logger(string filePath) : path(filePath) {}

void logger::log(const string &new_log)
{
    time_t currentTime = time(nullptr); // time var
    string timeStr = ctime(&currentTime); // Convert time to string
    timeStr.pop_back(); // Remove the newline character from time string

    ofstream file(path, ios::app); // open log file in append mode
    if (file.is_open())
    {
        file << timeStr << ": " << new_log << endl; // Write log
        cout << new_log << endl;
    }
    else
    {
        cerr << "Error: Could not open file." << endl; // Error handling
    }
    // file.close(); // Not needed
}
