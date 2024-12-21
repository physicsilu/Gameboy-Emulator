#pragma once
#include<cstdint>
class Bus;

class olc6502
{
private:
    Bus *bus = nullptr;
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t data);
public:
    olc6502(/* args */);
    ~olc6502();

    void ConnectBus(Bus *n){
        bus = n;
    }
};

/*
    class A;  // Forward declaration

    class B {
        A *a_ptr;  // Pointer to A, we don't need A's full definition here
    };

    You should use forward declarations when:
    1.You only need a pointer or reference to another class (as in this case).
    2.Including the full definition of the class is unnecessary or would cause circular dependencies.

    However, if you use the actual object (not a pointer or reference), or if you call its methods directly, you need the full definition:

    class A;  // Forward declaration

    class B {
        A a_obj;  // Error: Forward declaration is not enough for full objects
    };

    Here, in our case, "class Bus" is forward declaration. 'bus' is a pointer to Bus object.
*/