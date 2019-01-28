#include "..\Headers\Host.h"

Host::Host()
{
	gpu = new GPU();
	mmu = new MMU(gpu);
	cpu = new CPU(mmu);
}

Host::~Host()
{
	delete gpu;
	delete mmu;
	delete cpu;
}
