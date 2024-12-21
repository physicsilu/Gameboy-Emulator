#include "Bus.h"

// Here we are going to define the constructors and function definitions of the Bus class

Bus:: Bus(){
    // Clearing the RAM contents
    for (auto &itr : ram)
    {
        itr = 0x00; // We can represent hex numbers like this in cpp
    }
    
}

Bus:: ~Bus(){

}

void Bus:: write(uint16_t address, uint8_t data){
    // It is a very simple operation. RAM is an array. So just update the array element
    
    if(address>=0x0000 && address<=0xFFFF){ // Although this if condition is redundant here, it is useful when we have many devices
        ram[address] = data;
    }
}

uint8_t Bus:: read(uint16_t address, bool bReadOnly){
    if(address>=0x0000 && address<=0xFFFF){
        return ram[address];
    }

    return 0x00; // if address is out of range
}