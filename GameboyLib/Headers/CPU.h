#pragma once
#include <iostream>
#include "InstructionSet.h"
#include "MMU.h"
#include <vector>

//B, C, D, E, H, L, F, A
enum class REG {
	B = 0,
	C = 1,
	D = 2,
	E = 3,
	H = 4,
	L = 5,
	F = 6,
	A = 7
};

class CPU : InstructionSet
{
public:
	CPU(MMU * mmu);
	~CPU();

	//Setters (for register pairs)
	//CANNOT UNDERFLOW/OVERFLOW/WRAP!!!
	inline void SetAF(uint16_t val) { *regA = (val & 0xFF00) >> 8;	*regF = (val & 0x00F0); } //Flag bits: ZNHC0000
	inline void SetBC(uint16_t val) { *regB = (val & 0xFF00) >> 8;	*regC = (val & 0x00FF); }
	inline void SetDE(uint16_t val) { *regD = (val & 0xFF00) >> 8;	*regE = (val & 0x00FF); }
	inline void SetHL(uint16_t val) { *regH = (val & 0xFF00) >> 8;	*regL = (val & 0x00FF); }

	//Getters (for register pairs)
	inline uint16_t GetAF() { return ((*regA << 8) | *regF); }
	inline uint16_t GetBC() { return ((*regB << 8) | *regC); }
	inline uint16_t GetDE() { return ((*regD << 8) | *regE); }
	inline uint16_t GetHL() { return ((*regH << 8) | *regL); }

	//Setters (for individual registers)
	inline void SetA(uint8_t val) { *regA = val; }
	inline void SetB(uint8_t val) { *regB = val; }
	inline void SetC(uint8_t val) { *regC = val; }
	inline void SetD(uint8_t val) { *regD = val; }
	inline void SetE(uint8_t val) { *regE = val; }
	inline void SetF(uint8_t val) { *regF = val & 0xF0; } //Flag bits: ZNHC0000
	inline void SetH(uint8_t val) { *regH = val; }
	inline void SetL(uint8_t val) { *regL = val; }

	//Getters (for individual registers)
	inline uint8_t GetA() { return *regA; }
	inline uint8_t GetB() { return *regB; }
	inline uint8_t GetC() { return *regC; }
	inline uint8_t GetD() { return *regD; }
	inline uint8_t GetE() { return *regE; }
	inline uint8_t GetF() { return *regF; } //Flag bits: ZNHC0000
	inline uint8_t GetH() { return *regH; }
	inline uint8_t GetL() { return *regL; }

	//Public Access to all registers (alternate access to registers)
	inline std::vector<uint8_t *>& Registers() { return registers; }

private:
	//Let's define our registers... They are pointers so we can store them in a vector and have them stay consistent
//THEY CAN UNDERFLOW/OVERFLOW/WRAP WITHOUT CAUSING PROBLEMS
	uint8_t * regA;
	uint8_t * regB;
	uint8_t * regC;
	uint8_t * regD;
	uint8_t * regE;
	uint8_t * regF; //flags
	uint8_t * regH;
	uint8_t * regL;

	uint16_t PC;
	uint16_t SP;

	//Our container for our registers, used in some situations (e.g. for parameterising LD instructions)
	std::vector<uint8_t *> registers; //B, C, D, E, H, L, F, A

	// Fetch Decode Execute Cycle
	void Cycle();

	//If you are using this CPU emulator, it's up to you to include an implementation of RAM.
	//The CPU does not contain ram, it merely contains a reference to the RAM.
	//Also, the CPU does not destroy the RAM when it terminates.
	MMU * mmu;
};