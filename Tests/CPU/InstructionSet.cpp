#include "../headers/googletest.h"
#include "../../GameboyLib/Headers/InstructionSet.h"

TEST(Instructions, NOP) {
	InstructionSet is;

	int cycles = is.NOP();
	EXPECT_EQ(cycles, 4);
}