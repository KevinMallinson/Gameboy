#pragma once
#include <iostream>
#include <stdexcept>
typedef enum {
	SETONLY					= 0x0,
	ROMBANK					= 0x1,
	VIDEORAM				= 0x2,
	EXTERNALRAM				= 0x3,
	WORKRAM					= 0x4,
	ECHORAM					= 0x5,
	SPRITEATTRIBUTETABLE	= 0x6,
	UNUSED					= 0x7,
	IOREGISTERS				= 0x8,
	HIGHRAM					= 0x9,
	INTERRUPTFLAG			= 0xA
} MemoryRegion;

//This class exists to help debugging.
//It will contain the memory value, as well as the section of memory that it was retreived from.
class Memory
{
public:
	Memory(); //default constructor is set only
	Memory(MemoryRegion reg, uint16_t byteOrWord, uint16_t addr);
	uint8_t Byte();
	uint16_t Word();
	MemoryRegion Region();

private:
	bool isByte; //controls if it's a byte or word
	MemoryRegion region;
	uint16_t data;
	uint16_t address;
};