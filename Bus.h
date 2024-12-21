#pragma once 
// When the compiler encounters #pragma once in a file, it marks the file as included.
// If the file is encountered again during the same compilation process, the compiler skips it.
#include<cstdint>
#include<array>
#include"olc6502.h"

class Bus
{
private: // The private: access specifier means that the members (data and functions) declared below it are accessible only within the class itself.
    /* data */
public:
    Bus(/* args */); // A constructor is a special function that is automatically called when an object of the class is created.
    ~Bus(); // A destructor is a special function that is automatically called when an object of the class is destroyed.

public: // Here we are going to include the devices connected to the bus
    olc6502 cpu; // This is our 6502 processor

    // Generally, there are many other devices connected to the bus. Like mapper, PPU etc
    // Here we're considering every other device to be one and naming it as RAM

    std::array<uint8_t, 64*1024> ram;

public: // Here we are defining the read and write operations for the bus
    void write(uint16_t address, uint8_t data); // So, we take 16 bit address and 8 bit (byte) data to be written
    uint8_t read(uint16_t address, bool bReadOnly = false); // For read operation we need the address in the memory. The output will be the byte read
};
