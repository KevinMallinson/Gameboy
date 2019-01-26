#include "../Headers/googletest.h"
#include "../../GameboyLib/Headers/MMU.h"
#include "../../GameboyLib/Headers/GPU.h"

// Note: We will test the GPU memory stuff here too.
TEST(MMUandGPU, Init) 
{
	GPU * gpu = new GPU();
	MMU mmu(gpu);

	// 0x8000 + 0x2000 + 0x2000 + 0x1E00 + 0x0060 + 0x0080 + 0x007F + 0x2000 + 0x00A0 + 1 = 65536
	for (int i = 0; i < 65536; i++)
	{
		mmu.WriteByte(i, 237);
	}

	for (int i = 0; i < 65536; i++)
	{
		Memory val = mmu.GetByte(i);
		EXPECT_EQ(val.Byte(), 237);
	}

	delete gpu;
}

TEST(MMUandGPU, TestEachSection)
{
	//GPU * gpu = new GPU();
	//MMU mmu(gpu);

	//// 0x8000 + 0x2000 + 0x2000 + 0x1E00 + 0x0060 + 0x0080 + 0x007F + 0x2000 + 0x00A0 + 1 = 65536
	//for (int i = 0; i < 65536; i++)
	//{
	//	if (i <= 0x7FFF)
	//	{
	//		mmu.WriteByte(i, 50);
	//		continue;
	//	}
	//	mmu.WriteByte(i, 133);
	//}

	//for (int i = 0; i < 65536; i++)
	//{
	//	int val = mmu.GetByte(i);
	//	EXPECT_EQ(val, 133);
	//}

	//delete gpu;
}