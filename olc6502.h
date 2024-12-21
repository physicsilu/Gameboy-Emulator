#pragma once
#include<cstdint>
#include<vector>
class Bus;

class olc6502
{
private:
    Bus *bus = nullptr;
    // These are read/write methods for the cpu. They should be private
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t data);
public:
    olc6502(/* args */);
    ~olc6502();

    void ConnectBus(Bus *n){
        bus = n;
    }
    /*
        A public method that connects the olc6502 object to a Bus object.
        Takes a pointer to a Bus object (Bus *n) and assigns it to the private bus pointer.
        This establishes a relationship between the CPU and the Bus, enabling the CPU to read from and write to the memory or devices managed by the Bus.
    */
public:
    enum FLAGS6502{
        // Bitwise left shift is done
        C = (1<<0), // Carry bit
        Z = (1<<1), // Zero
        I = (1<<2), // Disable Interrupts
        D = (1<<3), // Decimal mode
        B = (1<<4), // Break
        U = (1<<5), // Unused
        V = (1<<6), // Overflow
        N = (1<<7), // Negative
    };
    /*
        C (Carry bit):
        1 << 0 → Bit 0 of the status register.
        Indicates if an arithmetic operation generated a carry out (or borrow in subtraction).

        Z (Zero):
        1 << 1 → Bit 1 of the status register.
        Set when the result of an operation is zero.

        I (Disable Interrupts):
        1 << 2 → Bit 2 of the status register.
        Controls whether interrupts are disabled (1) or enabled (0).

        D (Decimal mode):
        1 << 3 → Bit 3 of the status register.
        Enables Binary-Coded Decimal (BCD) mode for arithmetic operations.

        B (Break):
        1 << 4 → Bit 4 of the status register.
        Set when a BRK (break) instruction is executed.

        U (Unused):
        1 << 5 → Bit 5 of the status register.
        This bit is unused but is typically set to 1.

        V (Overflow):
        1 << 6 → Bit 6 of the status register.
        Set when an arithmetic operation results in signed overflow.

        N (Negative):
        1 << 7 → Bit 7 of the status register.
        Reflects the most significant bit (MSB) of the result, used to indicate a negative number in two's complement representation.    
    */

    // We will define the registers in the CPU here:
    uint8_t a = 0x00; // Accumulator register
    uint8_t x = 0x00; // X register
    uint8_t y = 0x00; // Y register
    uint8_t stkp = 0x00; // Stack pointer
    uint16_t pc = 0x0000; // Program counter
    uint8_t status = 0x00; // Status Register

    // Addressing Modes
    uint8_t IMP();	uint8_t IMM();	
	uint8_t ZP0();	uint8_t ZPX();	
	uint8_t ZPY();	uint8_t REL();
	uint8_t ABS();	uint8_t ABX();	
	uint8_t ABY();	uint8_t IND();	
	uint8_t IZX();	uint8_t IZY();

    // Opcodes
    // These are the 56 legal instructions for 6502 ISA
    uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
	uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
	uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
	uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
	uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
	uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
	uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
	uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
	uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
	uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
	uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
	uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
	uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
	uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

    // If there's any unidentified opcode, we'll handle using this:
    uint8_t XXX();

    void clock(); // As clock is input to 6502
    void reset(); // reset signal
    void InterruptRequestSignal();
    void NonMaskableInterrupt();

    // Internal helper functions
    uint8_t fetch();
    uint8_t fetched = 0x00; // Here the data fetched is stored

    uint16_t addrs_abs = 0x0000; // Memory location
    uint16_t addrs_rel = 0x00; // Relative address for branch instructions
    uint8_t opcode = 0x00; // Opcode of the current instruction
    uint8_t cycles = 0; // no of cycles left for the duration of the instruction

    // We are going to create a lookup matrix for the instruction below
    struct INSTRUCTION
	{
		std::string name;		
		uint8_t     (olc6502::*operate )(void) = nullptr;
		uint8_t     (olc6502::*addrmode)(void) = nullptr;
		uint8_t     cycles = 0;
	};

    /*
        struct INSTRUCTION:
        This structure represents a single instruction in the 6502 CPU's instruction set. Each instruction has the following components:

        std::string name:

        The name of the instruction as a string (e.g., "LDA", "STA", "ADC").
        This is used for debugging or disassembly.

        uint8_t (olc6502::*operate)(void):

        A pointer to a member function in the olc6502 class that performs the operation of the instruction.
        For example, LDA (Load Accumulator) would have a corresponding function in the olc6502 class that implements its behavior.
        
        uint8_t (olc6502::*addrmode)(void):

        Another pointer to a member function in the olc6502 class that determines the addressing mode of the instruction.
        Addressing modes define how the instruction locates its operands (e.g., immediate, absolute, indexed).
        
        uint8_t cycles:

        The number of clock cycles required to execute this instruction.    
    */

	std::vector<INSTRUCTION> lookup;

private:
    // We can declare functions to know about the status flags
    uint8_t GetFlag(FLAGS6502 f);
    void SetFlag(FLAGS6502 f, bool v);
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