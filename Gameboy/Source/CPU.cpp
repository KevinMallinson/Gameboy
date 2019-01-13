#include "../Headers/CPU.h"

CPU::CPU()
{
	//Initialize our registers
	A = new int8_t(0);
	B = new int8_t(0);
	C = new int8_t(0);
	D = new int8_t(0);
	E = new int8_t(0);
	F = new int8_t(0);
	H = new int8_t(0);
	L = new int8_t(0);

	SP = 0;
	PC = 0;
	
	registers.reserve(8);
	registers.push_back(A);
	registers.push_back(B);
	registers.push_back(C);
	registers.push_back(D);
	registers.push_back(E);
	registers.push_back(F);
	registers.push_back(H);
	registers.push_back(L);
}

CPU::~CPU()
{
	//Delete our pointers - no need to delete vector (since it's not a pointer at all)
	delete A;
	delete B;
	delete C;
	delete D;
	delete E;
	delete F;
	delete H;
	delete L;
}

void CPU::Cycle()
{
	int opcode = 0; //placeholder

	switch (opcode)
	{
		//------------LD INSTRUCTIONS FOR REGISTERS (NON PAIR), AND NON MEMORY (HL)------------//
		//LD instructions from 0x40 to 0x7F
		//Excluding 0x46, 0x56, 0x66                                due to --> LD reg, (HL)
		//Excluding 0x4E, 0x5E, 0x6E, 0x7E                          due to --> LD reg, (HL)
		//Excluding 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x77        due to --> LD (HL), reg
		//Excluding 0x76 because it's a HALT instruction.
		//------------------------------------------------------------------------------------//
		case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x47: // ld b,reg
		case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4f: // ld c,reg
		case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x57: // ld d,reg
		case 0x58: case 0x59: case 0x5a: case 0x5b: case 0x5c: case 0x5d: case 0x5f: // ld e,reg
		case 0x60: case 0x61: case 0x62: case 0x63: case 0x64: case 0x65: case 0x67: // ld h,reg
		case 0x68: case 0x69: case 0x6a: case 0x6b: case 0x6c: case 0x6d: case 0x6f: // ld l,reg
		case 0x78: case 0x79: case 0x7a: case 0x7b: case 0x7c: case 0x7d: case 0x7f: // ld a,reg
		{
			int dest = opcode >> 3 & 0b00000111; //bitmask so get only last 3 bits
			int src = opcode & 0b00000111; //as above
			LD(dest, src);
			break;
		}
	}
}

/**
	Perform No-Operation.
	@return the number of cycles
*/
int CPU::NOP()
{
	return 4;
}

/**
	Load register B in to register A
	@param dest the destination register
	@param src the source register
	@return the number of cycles
*/
int CPU::LD(int dest, int source)
{
	//Set the value of dest to the value of source
	*registers[dest] = *registers[source];

	return 4;
}