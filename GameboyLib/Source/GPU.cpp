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
	uint16_t bitmask = addr & 0x1FFF;
	videoRam[bitmask] = val;
}

uint8_t GPU::GetVideoRam(uint16_t addr)
{
	//Note: possible to overflow the array
	uint16_t bitmask = addr & 0x1FFF;
	return videoRam[bitmask];
}

void GPU::SetSpriteAttributeTable(uint16_t addr, uint8_t val)
{
	//Note: possible to overflow the array
	spriteAttributeTable[addr & 0x00FF] = val;
}

uint8_t GPU::GetSpriteAttributeTable(uint16_t addr)
{
	//Note: possible to overflow the array
	return spriteAttributeTable[addr & 0x00FF];
}
