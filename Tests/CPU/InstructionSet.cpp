#include "../headers/googletest.h"
#include "../../GameboyLib/Headers/InstructionSet.h"
#include "../../GameboyLib/Headers/CPU.h"

TEST(Instructions, NOP) {
	// Set up
	CPU cpu(nullptr);
	int cycles = cpu.NOP();

	//NOP does nothing apart from taking 4 cycles.
	EXPECT_EQ(cycles, 4);
}

TEST(Instructions, LDRegToReg) {
	// Set up
	CPU cpu(nullptr);
	*cpu.Registers()[REG::B] = 141;
	*cpu.Registers()[REG::D] = 227;

	int cycles = cpu.LD(cpu.Registers()[REG::B], cpu.Registers()[REG::D]);

	//The value of register D should now be in Register B
	//Cycles for this OPCODE is 4.
	EXPECT_EQ(cycles, 4);
	EXPECT_EQ(*cpu.Registers()[REG::B], 227);
}