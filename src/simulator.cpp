#include "simulator.h"

MIPS::MIPS()
{
}

MIPS::~MIPS()
{
}

void MIPS::run()
{
    while(pc <= 2e3*4 or finish_sim_)  /*pc <= 2k words*/
    {
        fetch();
        decode();
        execute();
    }
}

void MIPS::step()
{
    fetch();
    decode();
    execute();
}
