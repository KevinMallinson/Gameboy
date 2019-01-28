#include "../Headers/Memory.h"

Memory::Memory()
{
	region = MemoryRegion::SETONLY;
	data = 0;
	address = 0;
	isByte = false;
}

Memory::Memory(MemoryRegion reg, uint16_t byteOrWord, uint16_t addr)
{
	region = reg;
	data = byteOrWord;
	address = addr;

	if (data >> 8 == 0)
	{
		isByte = true;
	}
	else
	{
		isByte = false;
	}
}

//Technically, it will return a word, but the caller should define its size
//so if it's uint8_t, only the last 8 bits are used.
uint16_t Memory::Data()
{
	return data;
}

MemoryRegion Memory::Region()
{
	return region;
}
