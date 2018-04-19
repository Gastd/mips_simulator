#include <iostream>
#include "simulator.h"

int main(int argc, char *argv[])
{
    std::string text_path(""), data_path("");
    if (argc != 3)
    {
        std::cout << "Please provide exactly two files (text.bin and data.bin)" << std::endl;
        return 0;
    }
    else
    {
        text_path = argv[1];
        data_path = argv[2];
    }

    MIPS mips;

    mips.fillMemory(text_path, data_path, false);

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
    // mips.dump_reg('h');

    return 0;
}
