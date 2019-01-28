#include "../Headers/googletest.h"
#include "../../GameboyLib/Headers/MMU.h"
#include "../../GameboyLib/Headers/GPU.h"

// Note: We will test the GPU memory stuff here too.
TEST(MMUandGPU, Init) 
{
	GPU * gpu = new GPU();
	MMU mmu(gpu);

	//If 0x0000 to 0xFFFF is addressable, that means that the size of the address space is 0xFFFF + 1
	for (int i = 0; i < 0x10000; i++)
	{
		mmu.WriteByte(i, 237);
	}

	for (int i = 0; i < 0x10000; i++)
	{
		Memory val = mmu.GetByte(i);

		if (i >= 0xFEA0 && i <= 0xFEFF)
		{
			//Unused RAM always returns 0 and disallows being set.
			//TODO: Anything we should actually do instead?
			EXPECT_EQ(val.Byte(), 0);
		}
		else
		{
			EXPECT_EQ(val.Byte(), 237);
		}
	}

	delete gpu;
}

TEST(MMUandGPU, TestEachSection)
{
	GPU * gpu = new GPU();
	MMU mmu(gpu);

	//Note: I know I could use one for loop. But i'd prefer two just to separate set and get.

	// Set
	for (int i = 0; i < 0x10000; i++)
	{
		if (i >= 0x0000 && i <= 0x7FFF)
		{
			mmu.WriteByte(i, 33);
		}
		else if (i >= 0x8000 && i <= 0x9FFF)
		{
			mmu.WriteByte(i, 44);
		}
		else if (i >= 0xA000 && i <= 0xBFFF)
		{
			mmu.WriteByte(i, 55);
		}
		else if (i >= 0xC000 && i <= 0xDFFF)
		{
			mmu.WriteByte(i, 66);
		}
		else if (i >= 0xE000 && i <= 0xFDFF)
		{
			mmu.WriteByte(i, 77);
		}
		else if (i >= 0xFE00 && i <= 0xFE9F)
		{
			mmu.WriteByte(i, 88);
		}
		else if (i >= 0xFEA0 && i <= 0xFEFF)
		{
			mmu.WriteByte(i, 99);
		}
		else if (i >= 0xFF00 && i <= 0xFF7F)
		{
			mmu.WriteByte(i, 110);
		}
		else if (i >= 0xFF80 && i <= 0xFFFE)
		{
			mmu.WriteByte(i, 121);
		}
		else if (i == 0xFFFF)
		{
			mmu.WriteByte(i, 132);
		}
	}


	// Get
	int j = 0;
	for (int i = 0; i < 0x10000; i++)
	{
		if (i >= 0x0000 && i <= 0x7FFF)
		{
			Memory byte = mmu.GetByte(i);
			EXPECT_EQ(byte.Byte(), 33);
			EXPECT_EQ(byte.Region(), MemoryRegion::ROMBANK);
		}
		else if (i >= 0x8000 && i <= 0x9FFF)
		{
			Memory byte = mmu.GetByte(i);
			EXPECT_EQ(byte.Byte(), 44);
			EXPECT_EQ(byte.Region(), MemoryRegion::VIDEORAM);
		}
		else if (i >= 0xA000 && i <= 0xBFFF)
		{
			Memory byte = mmu.GetByte(i);
			EXPECT_EQ(byte.Byte(), 55);
			EXPECT_EQ(byte.Region(), MemoryRegion::EXTERNALRAM);
		}
		else if (i >= 0xC000 && i <= 0xDFFF)
		{
			//Since the echo ram, first 0x1E00 bytes should be 77
			//rest should be 66 (since echo ram doesn't fill the work ram all the way, only 7.5kb/8kb)
			Memory byte = mmu.GetByte(i);
			if (j < 0x1E00)
			{
				EXPECT_EQ(byte.Byte(), 77);
			}
			else
			{
				EXPECT_EQ(byte.Byte(), 66);
			}

			EXPECT_EQ(byte.Region(), MemoryRegion::WORKRAM);
			j++;
		}
		else if (i >= 0xE000 && i <= 0xFDFF)
		{
			Memory byte = mmu.GetByte(i);
			EXPECT_EQ(byte.Byte(), 77);
			EXPECT_EQ(byte.Region(), MemoryRegion::ECHORAM);
		}
		else if (i >= 0xFE00 && i <= 0xFE9F)
		{
			Memory byte = mmu.GetByte(i);
			EXPECT_EQ(byte.Byte(), 88);
			EXPECT_EQ(byte.Region(), MemoryRegion::SPRITEATTRIBUTETABLE);
		}
		else if (i >= 0xFEA0 && i <= 0xFEFF)
		{
			//Unused RAM always returns 0 and disallows being set.
			//TODO: Anything we should actually do instead?
			Memory byte = mmu.GetByte(i);
			EXPECT_EQ(byte.Byte(), 0);
			EXPECT_EQ(byte.Region(), MemoryRegion::UNUSED);
		}
		else if (i >= 0xFF00 && i <= 0xFF7F)
		{
			Memory byte = mmu.GetByte(i);
			EXPECT_EQ(byte.Byte(), 110);
			EXPECT_EQ(byte.Region(), MemoryRegion::IOREGISTERS);
		}
		else if (i >= 0xFF80 && i <= 0xFFFE)
		{
			Memory byte = mmu.GetByte(i);
			EXPECT_EQ(byte.Byte(), 121);
			EXPECT_EQ(byte.Region(), MemoryRegion::HIGHRAM);
		}
		else if (i == 0xFFFF)
		{
			Memory byte = mmu.GetByte(i);
			EXPECT_EQ(byte.Byte(), 132);
			EXPECT_EQ(byte.Region(), MemoryRegion::INTERRUPTFLAG);
		}
	}



	delete gpu;
}