//This test file will test the CPU, including registers work as they should, cycle, etc.


#include "../Headers/googletest.h"
#include "../../GameboyLib/Headers/CPU.h"

TEST(Processor, InitRegistersNormal) {
	CPU cpu(nullptr);

	//Some pretty normal inputs
	cpu.SetA(255);
	cpu.SetB(0);
	cpu.SetC(1);

	EXPECT_EQ((uint8_t)cpu.GetA(), 255);
	EXPECT_EQ((uint8_t)cpu.GetB(), 0);
	EXPECT_EQ((uint8_t)cpu.GetC(), 1);

}

TEST(Processor, SetRegPairsNormal) {
	CPU cpu(nullptr);

	cpu.SetAF(65535);		//0b1111111111111111 --> 0b1111111111110000 (4 last bits are ALWAYS zero)
	cpu.SetBC(0);			//0b0000000000000000
	cpu.SetDE(1);			//0b0000000000000001
	cpu.SetHL(35755);		//0b1000101110101011

	//A: 0b11111111 = 255
	//F: 0b11111111 = 255
	EXPECT_EQ((uint8_t)cpu.GetA(), 255);
	EXPECT_EQ((uint8_t)cpu.GetF(), 240); //0b11111111 --> 0b11110000 (4 last bits are ALWAYS zero)

	//B: 0b00000000 = 0
	//C: 0b00000000 = 0
	EXPECT_EQ((uint8_t)cpu.GetB(), 0);
	EXPECT_EQ((uint8_t)cpu.GetC(), 0);

	//D: 0b00000000 = 0
	//E: 0b00000001 = 1
	EXPECT_EQ((uint8_t)cpu.GetD(), 0);
	EXPECT_EQ((uint8_t)cpu.GetE(), 1);

	//H: 0b10001011 = 139
	//L: 0b10101011 = 171
	EXPECT_EQ((uint8_t)cpu.GetH(), 139);
	EXPECT_EQ((uint8_t)cpu.GetL(), 171);
}

TEST(Processor, GetRegPairsNormal) {
	CPU cpu(nullptr);

	cpu.SetAF(65535); //0b1111111111111111 --> 0b1111111111110000 (4 last bits are ALWAYS zero)
	cpu.SetBC(0);
	cpu.SetDE(1);
	cpu.SetHL(35755);

	EXPECT_EQ((uint16_t)cpu.GetAF(), 65520); //0b1111111111111111 --> 0b1111111111110000 (4 last bits are ALWAYS zero)
	EXPECT_EQ((uint16_t)cpu.GetBC(), 0);
	EXPECT_EQ((uint16_t)cpu.GetDE(), 1);
	EXPECT_EQ((uint16_t)cpu.GetHL(), 35755);
}

TEST(Processor, RegistersViaArray) {
	CPU cpu(nullptr);

	//Set some normal registers
	cpu.SetA(255);
	cpu.SetF(14);
	cpu.SetH(30);
	cpu.SetL(111);

	//Now some pairs
	cpu.SetBC(38483);
	cpu.SetDE(10631);

	//We can test A,F,H,L as-is.
	uint8_t A = *cpu.Registers()[(int)REG::A];
	uint8_t F = *cpu.Registers()[(int)REG::F];
	EXPECT_EQ(A, 255);
	EXPECT_EQ(F, 0); //0b00001110 --> 0b00000000

	uint8_t H = *cpu.Registers()[(int)REG::H];
	uint8_t L = *cpu.Registers()[(int)REG::L];
	EXPECT_EQ(H, 30);
	EXPECT_EQ(L, 111);

	//These next two are pairs, so we get the first and last 8 bits
	uint8_t B = *cpu.Registers()[(int)REG::B];
	uint8_t C = *cpu.Registers()[(int)REG::C];
	EXPECT_EQ(B, 0b10010110);		//[10010110] 01010011
	EXPECT_EQ(C, 0b01010011);		// 10010110 [01010011]

	uint8_t D = *cpu.Registers()[(int)REG::D];
	uint8_t E = *cpu.Registers()[(int)REG::E];
								
	EXPECT_EQ(D, 0b00101001);		//[00101001] 10000111
	EXPECT_EQ(E, 0b10000111);		// 00101001 [10000111]
}

//Just a test to make sure the reference is working right
//no need to test all registers
TEST(Processor, SetRegistersViaArray) {
	CPU cpu(nullptr);
	*cpu.Registers()[(int)REG::A] = 139;
	EXPECT_EQ((uint8_t)cpu.GetA(), 139);
}