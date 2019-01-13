#pragma once

class InstructionSet
{
public:
	virtual int NOP() = 0;											//No Operation
	virtual int LD(int dest, int source) = 0;						//Load source register value in to dest register
	

	//Make sure we clean up
	virtual ~InstructionSet() { };
};