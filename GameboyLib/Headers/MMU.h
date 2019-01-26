#pragma once
//Using memory map from http://gbdev.gg8.se/wiki/articles/Memory_Map

#include <iostream>
#include <stdexcept>
#include "GPU.h"
#include "Memory.h"

class MMU
{
public:
	MMU(GPU * gpuRef);
	Memory GetByte(uint16_t addr);
	Memory GetWord(uint16_t addr);

	void WriteByte(uint16_t addr, uint8_t val);
	void WriteWord(uint16_t addr, uint16_t val);

private:
	//Start		End		Description						Notes																	//Implementation
	//0000		3FFF	16KB ROM bank 00				From cartridge, fixed bank												MMU
	//4000		7FFF	16KB ROM Bank 01~NN				From cartridge, switchable bank via MBC(if any)							MMU
	//8000		9FFF	8KB Video RAM(VRAM)				Only bank 0 in Non - CGB mode, Switchable bank 0 / 1 in CGB mode		GPU
	//A000		BFFF	8KB External RAM				In cartridge, switchable bank if any									MMU
	//C000		CFFF	4KB Work RAM(WRAM) bank 0																				MMU
	//D000		DFFF	4KB Work RAM(WRAM) bank 1~N		Only bank 1 in Non - CGB mode, Switchable bank 1~7 in CGB mode			MMU
	//E000		FDFF	Mirror of C000~DDFF(ECHO RAM)	Typically not used														MMU
	//FE00		FE9F	Sprite attribute table(OAM)																				GPU
	//FEA0		FEFF	Not Usable																								MMU
	//FF00		FF7F	I / O Registers																							MMU
	//FF80		FFFE	High RAM(HRAM)																							MMU
	//FFFF		FFFF	Interrupts Enable Register(IE)																			MMU

	uint8_t     romBank [0x8000]; //32kb
	uint8_t externalRam [0x2000]; //8kb external ram
	uint8_t     workRam [0x2000]; //8kb - next to eachother - can combine
	uint8_t     echoRam [0x1E00]; //7.5kb - this echos the entire work ram. It's slightly less size. Why? Also, apparently this is usually unused.
	uint8_t      unused [0x0060]; //96 bytes unused
	uint8_t ioRegisters [0x0080]; //128 bytes
	uint8_t     highRam [0x007F]; //127 bytes
	uint8_t  interruptEnableFlag; //One byte for Interrupt Enable Register

	Memory SetOrGetMemory(uint16_t addr, uint8_t val, bool set);

	//Note: VideoRam and SpriteAttributeTable will be in GPU.
	GPU * gpu;
};