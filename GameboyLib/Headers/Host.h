#pragma once
#include "CPU.h"
#include "MMU.h"
#include "GPU.h"


/**
 * The host class integrates the vital components together.
*/
class Host
{
public:
	Host();
	~Host();

private:
	CPU * cpu;
	GPU * gpu;
	MMU * mmu;
};