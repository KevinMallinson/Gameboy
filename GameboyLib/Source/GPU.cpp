#include "../Headers/GPU.h"

GPU::GPU()
{
	videoRam[0x2000];
	for (int i = 0; i < 0x2000; i++)
	{
		videoRam[i] = 0;
	}

	spriteAttributeTable[0x00A0];
	for (int i = 0; i < 0x00A0; i++)
	{
		spriteAttributeTable[i] = 0;
	}
}

void GPU::SetVideoRam(uint16_t addr, uint8_t val)
{
	//Note: possible to overflow the array  
	videoRam[addr] = val;
}

Memory GPU::GetVideoRam(uint16_t addr)
{
	//Note: possible to overflow the array
	return Memory(MemoryRegion::VIDEORAM, videoRam[addr], addr);
}

void GPU::SetSpriteAttributeTable(uint16_t addr, uint8_t val)
{
	//Note: possible to overflow the array
	spriteAttributeTable[addr] = val;
}

Memory GPU::GetSpriteAttributeTable(uint16_t addr)
{
	//Note: possible to overflow the array
	return Memory(MemoryRegion::SPRITEATTRIBUTETABLE, spriteAttributeTable[addr], addr);
}
