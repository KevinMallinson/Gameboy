#pragma once
//Using memory map from http://gbdev.gg8.se/wiki/articles/Memory_Map

#include <iostream>
#include "Memory.h"
class GPU
{
public:

	GPU();

	void SetVideoRam(uint16_t addr, uint8_t val);
	Memory GetVideoRam(uint16_t addr);

	void SetSpriteAttributeTable(uint16_t addr, uint8_t val);
	Memory GetSpriteAttributeTable(uint16_t address);


private:
	//Start		End		Description						Notes																	//Implementation
	//8000		9FFF	8KB Video RAM(VRAM)				Only bank 0 in Non - CGB mode, Switchable bank 0 / 1 in CGB mode		GPU
	//FE00		FE9F	Sprite attribute table(OAM)																				GPU

	uint8_t     videoRam[0x2000]; //8kb
	uint8_t     spriteAttributeTable[0x00A0]; //160 bytes
};