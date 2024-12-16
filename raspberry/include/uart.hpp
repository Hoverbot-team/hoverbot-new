#include <iostream>

using namespace std;
class UART{
    public:
        UART(int baud);
        void write(string input);
        string read();
    private:
        int serialPort;
        
};