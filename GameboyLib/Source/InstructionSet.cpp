#include "../Headers/InstructionSet.h"

/**
	Perform No-Operation.
	@return the number of cycles
*/
int InstructionSet::NOP()
{
	return 4;
}

/**
	Load register B in to register A
	@param dest the destination register
	@param src the source register
	@return the number of cycles
*/
int InstructionSet::LD(uint8_t * dest, uint8_t * source)
{
	//Set the value of dest to the value of source
	*dest = *source;

	return 4;
}