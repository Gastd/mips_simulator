#include <iostream>
#include "simulator.h"

int main(int argc, char const *argv[])
{
    MIPS mips;

    mips.fillMemory("../text.bin","../data.bin");

    // mips.step();
    // mips.step();
    // mips.step();
    // mips.step();
    // mips.step();
    // mips.step();
    // mips.step();
    // mips.step();
    // mips.step();
    // mips.step();
    // mips.step();
    // mips.step();
    // mips.step();
    // mips.step();

    mips.run();
    mips.dump_mem(0, 40);

    return 0;
}
