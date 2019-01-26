#pragma once
#include <iostream>

class InstructionSet
{
public:
	virtual int NOP();													//No Operation
	virtual int LD(uint8_t * dest, uint8_t * source);					//Load source register value in to dest register
	virtual ~InstructionSet() { };
};