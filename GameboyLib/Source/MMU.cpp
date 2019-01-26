#include "../Headers/MMU.h"

MMU::MMU(GPU * gpuPtr) :gpu(gpuPtr)
{
	for (int i = 0; i < 0x8000; i++)
	{
		romBank[i] = 0;
	}

	for (int i = 0; i < 0x2000; i++)
	{
		externalRam[i] = 0;
	}

	for (int i = 0; i < 0x2000; i++)
	{
		workRam[i] = 0;
	}

	for (int i = 0; i < 0x1E00; i++)
	{
		echoRam[i] = 0;
	}

	for (int i = 0; i < 0x0060; i++)
	{
		unused[i] = 0;
	}

	for (int i = 0; i < 0x0080; i++)
	{
		ioRegisters[i] = 0;
	}

	for (int i = 0; i < 0x007F; i++)
	{
		highRam[i] = 0;
	}

	interruptEnableFlag = 0;
}

/**
	Get the byte at the given address, and return it.
	@param addr the memory address to read
	@return the byte at the given address
*/
Memory MMU::GetByte(uint16_t addr)
{
	return SetOrGetMemory(addr, 0, false);
}

/**
	Write a byte at the given address.
	@param addr the memory address to write to
	@param val the byte to write
*/
void MMU::WriteByte(uint16_t addr, uint8_t val)
{
	SetOrGetMemory(addr, val, true);
}

/**
	Get the 16 bit word at the given address, and return it.
	@param addr the memory address to read
	@return the word at the given address
*/
Memory MMU::GetWord(uint16_t addr)
{
	//its stored in our RAM implementation in little endian
	Memory msb = GetByte(addr + 1); //higher address contains most significant byte
	Memory lsb = GetByte(addr); //lower address contains least significant byte

	if (msb.Region() != lsb.Region())
	{
		throw std::logic_error("WORD IS COMPRISED OF TWO DISTINCT MEMORY REGIONS");
	}

	return Memory(msb.Region(), (msb.Byte() << 8) | lsb.Byte(), addr);
}

/**
	Write a 16 bit word at the given address.
	@param addr the memory address to write to
	@param val the word to write
*/
void MMU::WriteWord(uint16_t addr, uint16_t val)
{
	//Store in little endian
	WriteByte(addr, val & 0x00FF); //least significant byte in lower address
	WriteByte(addr+1, val >> 8); //most significant byte in higher address
}

/**
	Set or get the memory at the given address.
	@param addr the memory address to write to
	@param val the byte to write (if set == true), otherwise discarded
	@param set whether to set (set == true) or get (set == false)
	@return the byte at address (set == false), or 0 (set == true)
*/
Memory MMU::SetOrGetMemory(uint16_t addr, uint8_t val, bool set)
{
	//Using memory map at http://gbdev.gg8.se/wiki/articles/Memory_Map
	uint8_t byte = 0;
	switch (addr & 0xF000)
	{

	case 0x0000: case 0x1000: case 0x2000: case 0x3000: //16KB ROM bank 00
	case 0x4000: case 0x5000: case 0x6000: case 0x7000: //16KB ROM Bank 01~NN

		if (!set) 
		{
			return Memory(MemoryRegion::ROMBANK, romBank[addr], addr); //addr guaranteed to be 0x0000 to 0x7FFF, thus will fit in RomBank which is 0x8000 in size (including zero).
		}
		else
		{
			romBank[addr] = val;
			return Memory(MemoryRegion::SETONLY, 0, 0);
		}
		break;

	case 0x8000: //4kb VRAM
	case 0x9000: //4kb VRAM - total 8kb

		if (!set)
		{
			return Memory(MemoryRegion::VIDEORAM, gpu->GetVideoRam(addr & 0x1FFF).Byte(), addr);
		}
		else
		{
			gpu->SetVideoRam(addr & 0x1FFF, val);
			return Memory(MemoryRegion::SETONLY, 0, 0);
		}
		break;

	case 0xA000: //4kb external ram
	case 0xB000: //4kb external ram - total 8kb

		//Note: ExternalRam has a range of 0x2000. Of course, 0xA000 or 0xB000 is too large. It is out of range.
		//Let's say we receive 0xBFFF. This should be the last element of the array. Of course, it's out of range.
		//We need to apply a bitmask to reduce the value. In this case, ignoring the first 3 bits serves this purpose.
		if (!set)
		{
			return Memory(MemoryRegion::EXTERNALRAM, externalRam[addr & 0x1FFF], addr);
		}
		else
		{
			externalRam[addr & 0x1FFF] = val;
			return Memory(MemoryRegion::SETONLY, 0, 0);
		}
		break;

	case 0xC000: //4kb work ram bank 0
	case 0xD000: //4kb work ram bank 1-N - total 8kb

		if (!set)
		{
			return Memory(MemoryRegion::WORKRAM, workRam[addr & 0x1FFF], addr);
		}
		else
		{
			workRam[addr & 0x1FFF] = val;
			return Memory(MemoryRegion::SETONLY, 0, 0);
		}
		break;

	case 0xE000: //7.5kb echo ram. Only part, rest in 0xF000

		if (!set)
		{
			return Memory(MemoryRegion::ECHORAM, echoRam[addr & 0x1FFF], addr); //This can actually produce some out of range values (since it's actually 7.5kb and not 8kb)
		}
		else
		{
			echoRam[addr & 0x1FFF] = val;
			return Memory(MemoryRegion::SETONLY, 0, 0);
		}
		break;

	case 0xF000:
		switch (addr & 0x0F00)
		{

		case 0x000: case 0x100: case 0x200: case 0x300: case 0x400: //this is the rest of the echo ram
		case 0x500: case 0x600: case 0x700: case 0x800: case 0x900: //this is the rest of the echo ram
		case 0xA00: case 0xB00: case 0xC00: case 0xD00:				//this is the rest of the echo ram

			if (!set)
			{
				return Memory(MemoryRegion::ECHORAM, echoRam[addr & 0x1FFF], addr); //This can actually produce some out of range values (since it's actually 7.5kb and not 8kb)
			}
			else
			{
				echoRam[addr & 0x1FFF] = val;
				return Memory(MemoryRegion::SETONLY, 0, 0);
			}
			break;

		case 0xE00:

			switch (addr & 0x00F0)
			{

			case 0x00: case 0x10: case 0x20: case 0x30: case 0x40: //Sprite attribute table (OAM)
			case 0x50: case 0x60: case 0x70: case 0x80: case 0x90: //Sprite attribute table (OAM)

				if (!set)
				{
					return Memory(MemoryRegion::SPRITEATTRIBUTETABLE, gpu->GetSpriteAttributeTable(addr & 0x00FF).Byte(), addr);
				}
				else
				{
					gpu->SetSpriteAttributeTable(addr & 0x00FF, val);
					return Memory(MemoryRegion::SETONLY, 0, 0);
				}
				break;

			case 0xA0: case 0xB0: case 0xC0: //Not Usable
			case 0xD0: case 0xE0: case 0xF0: //Not Usable

				if (!set)
				{
					//Not sure if anything wrong with storing stuff here since it's technically not usable.
					return Memory(MemoryRegion::UNUSED, unused[addr & 0x7F], addr);
				}
				else
				{
					//NOP
					unused[addr & 0x7F] = val;
					return Memory(MemoryRegion::SETONLY, 0, 0);
				}

				break;
			}

			break;

		case 0xF00:

			switch (addr & 0x00F0)
			{
			case 0x00: case 0x10: case 0x20: case 0x30: //IO Registers
			case 0x40: case 0x50: case 0x60: case 0x70: //IO Registers

				if (!set)
				{
					return Memory(MemoryRegion::IOREGISTERS, ioRegisters[addr & 0x007F], addr);
				}
				else
				{
					ioRegisters[addr & 0x007F] = val;
					return Memory(MemoryRegion::SETONLY, 0, 0);
				}
				break;

			case 0x80: case 0x90: case 0xA0: case 0xB0: //High RAM (HRAM)
			case 0xC0: case 0xD0: case 0xE0:			//High RAM (HRAM)

				if (!set)
				{
					return Memory(MemoryRegion::HIGHRAM, highRam[addr & 0x007F], addr);
				}
				else
				{
					highRam[addr & 0x007F] = val;
					return Memory(MemoryRegion::SETONLY, 0, 0);
				}
				break;

			case 0xF0:
				//if the last nibble is not F, it is still high ram, else it's the interrupts enable register
				if (addr & 0x000F == 0x000F)
				{
					if (!set)
					{
						return Memory(MemoryRegion::INTERRUPTFLAG, interruptEnableFlag, addr);
					}
					else
					{
						interruptEnableFlag = val;
						return Memory(MemoryRegion::SETONLY, 0, 0);
					}
				}
				else
				{
					if (!set)
					{
						return Memory(MemoryRegion::HIGHRAM, highRam[addr & 0x007F], addr);
					}
					else
					{
						highRam[addr & 0x007F] = val;
						return Memory(MemoryRegion::SETONLY, 0, 0);
					}
				}
				break;

			}
			break;

		}
		break;

	}

	throw std::logic_error("ERROR IN RAM. COULD NOT FIND AN APPROPRIATE LOCATION FOR THE GIVEN ADDRESS");
}
