#include "../Headers/CPU.h"

CPU::CPU()
{
	//Initialize our registers
	regA = new uint8_t(0);
	regB = new uint8_t(0);
	regC = new uint8_t(0);
	regD = new uint8_t(0);
	regE = new uint8_t(0);
	regF = new uint8_t(0);
	regH = new uint8_t(0);
	regL = new uint8_t(0);

	SP = 0;
	PC = 0;
	
	////B, C, D, E, H, L, F, A
	registers.reserve(8);
	registers.push_back(regB);
	registers.push_back(regC);
	registers.push_back(regD);
	registers.push_back(regE);
	registers.push_back(regH);
	registers.push_back(regL);
	registers.push_back(regF);
	registers.push_back(regA);
}

CPU::~CPU()
{
	//Delete our pointers - no need to delete vector (since it's not a pointer at all)
	delete regA;
	delete regB;
	delete regC;
	delete regD;
	delete regE;
	delete regF;
	delete regH;
	delete regL;
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
			uint8_t * dest = registers[opcode >> 3 & 0b00000111]; //bitmask so get only last 3 bits
			uint8_t * src = registers[opcode & 0b00000111]; //as above
			LD(dest, src);
			break;
		}
	}
}