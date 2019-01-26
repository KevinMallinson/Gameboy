//This test file tests the instruction set, independent of any CPU implementation.
//Of course, in the real world an instruction set is of no use without a CPU to Fetch->Decode->Execute->Cycle
//However, this is abstracted in to two separate classes to expose the instruction sets functionality to the public
//and allow testing of it, instead of hiding them by implementing them in the CPU and having them only indirectly tested
//via the CPU's Cycle() method. That would be an "Iceberg Class" and as such I feel this is a better design.

#include "../Headers/googletest.h"
#include "../../GameboyLib/Headers/InstructionSet.h"

TEST(Instructions, NOP) {
	InstructionSet is;

	int cycles = is.NOP();
	EXPECT_EQ(cycles, 4);
}