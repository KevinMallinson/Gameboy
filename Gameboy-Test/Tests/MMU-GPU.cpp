#include "../Headers/googletest.h"
#include "../../GameboyLib/Headers/MMU.h"
#include "../../GameboyLib/Headers/GPU.h"

// Note: We will test the GPU memory stuff here too.
TEST(MMUandGPU, Zero) 
{
	GPU * gpu = new GPU();
	MMU mmu(gpu);

	// 0x8000 + 0x2000 + 0x2000 + 0x1E00 + 0x0060 + 0x0080 + 0x007F + 0x2000 + 0x00A0 + 1 = 65536
	for (int i = 0; i < 65536; i++)
	{
		mmu.WriteByte(i, 0);
	}

	for (int i = 0; i < 65536; i++)
	{
		int val = mmu.GetByte(i);
		EXPECT_EQ(val, 0);
	}

	delete gpu;
}