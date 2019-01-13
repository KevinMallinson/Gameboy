#pragma once
#include <iostream>
#include "InstructionSet.h"
#include <vector>

class CPU : InstructionSet
{
public:
	CPU();
	~CPU();
private:
	//Let's define our registers... They are pointers so we can store them in a vector and have them stay consistent
	int8_t * A;
	int8_t * B;
	int8_t * C;
	int8_t * D;
	int8_t * E;
	int8_t * F; //flags
	int8_t * H;
	int8_t * L;

	int16_t PC;
	int16_t SP;

	//Getters (for register pairs)
	inline int16_t AF() { return ((*A << 8) | *F); }
	inline int16_t BC() { return ((*B << 8) | *C); }
	inline int16_t DE() { return ((*D << 8) | *E); }
	inline int16_t HL() { return ((*H << 8) | *L); }
	
	//Setters (for register pairs)
	inline void AF(int16_t val) { *A = (val & 0xFF00) >> 8;	*F = (val & 0x00FF); }
	inline void BC(int16_t val) { *B = (val & 0xFF00) >> 8;	*C = (val & 0x00FF); }
	inline void DE(int16_t val) { *D = (val & 0xFF00) >> 8;	*E = (val & 0x00FF); }
	inline void HL(int16_t val) { *H = (val & 0xFF00) >> 8;	*L = (val & 0x00FF); }

	//Our container for our registers, should support getting/setting via here, or getting/setting via the variables A, B, H, L, etc.
	std::vector<int8_t *> registers;

	// Fetch Decode Execute Cycle
	void Cycle();

	virtual int NOP() override;
	virtual int LD(int dest, int source) override;
};