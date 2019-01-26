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

uint8_t Memory::Byte()
{
	if (!isByte)
	{
		throw std::logic_error("ATTEMPTING TO GET A BYTE, WHEN THE DATA IS ACTUALLY A WORD");
	}

	return data;
}

uint16_t Memory::Word()
{
	if (isByte)
	{
		throw std::logic_error("ATTEMPTING TO GET A WORD, WHEN THE DATA IS ACTUALLY A BYTE");
	}

	return data;
}

MemoryRegion Memory::Region()
{
	return region;
}
