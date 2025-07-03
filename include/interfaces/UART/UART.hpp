#include <string>
#include <cstdint>

class Uart {
public:
    Uart(const std::string& device, int baudRate);
    ~Uart();

    void writeByte(uint8_t byte);
    void writeBytes(const uint8_t* data, size_t length);

    bool available() const;
    uint8_t readByte();

private:
    int fd;
};