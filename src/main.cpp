// Cross-platform serial tester using serialib
// Works on Windows and Linux

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "serialib.h"  // from https://github.com/imabot2/serialib

#ifdef _WIN32
#define DEFAULT_PORT "COM5"
#else
#define DEFAULT_PORT "/dev/ttyUSB0"
#endif

int main(int argc, char* argv[]) {
    std::string portName = (argc > 1) ? argv[1] : DEFAULT_PORT;
    int baudrate = (argc > 2) ? std::stoi(argv[2]) : 9600;

    std::cout << "----------------------------------------\n";
    std::cout << " Serial Tester using serialib\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Port: " << portName << " @ " << baudrate << " baud\n";

    serialib serial;

    // Try to open the port
    int result = serial.openDevice(portName.c_str(), baudrate);
    if (result != 1)
    {
        std::cerr << "Error opening serial port (" << result << ")\n";
        return 1;
    }
    std::cout << "Port opened successfully.\n\n";

    // Flush buffers
    serial.flushReceiver();
    serial.flushReceiver();

    // Spawn a reader thread
    bool running = true;
    std::thread reader([&]()
    {
        char buffer[256];
        while (running)
        {
            int n = serial.readString(buffer, '\n', sizeof(buffer), 500);
            if (n > 0)
            {
                std::cout << "[RX] " << buffer;
                std::cout.flush();
            }
            else if (n == 0)
            {
                // timeout - just loop again
                continue;
            }
            else
            {
                std::cerr << "Read error or timeout: " << n << "\n";
            }
        }
    });

    // Main loop: allow user to type lines to send
    std::cout << "Type lines to send to the serial port. Type 'exit' to quit.\n";
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line == "exit") break;
        line += "\r\n"; // Append CRLF
        serial.writeString(line.c_str());
    }

    // Clean up
    running = false;
    reader.join();
    serial.closeDevice();

    std::cout << "Serial port closed.\n";
    return 0;
}
