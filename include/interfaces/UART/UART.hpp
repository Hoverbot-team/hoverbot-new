#include <string>

class Uart {
public:
    Uart(const std::string& device, int baudRate);
    ~Uart();

    void write(const std::string& data);
    bool available() const;
    char readChar();
    std::string readLine();  // Optional helper

private:
    int fd;
};
