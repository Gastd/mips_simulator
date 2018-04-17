#include "simulator.h"

MIPS::MIPS()
{
}

MIPS::~MIPS()
{
}

void MIPS::openFile(std::string path)
{
    std::ifstream infile;
    infile.open(path, std::ios::binary|std::ios::in);

    int8_t buffer[1];
    int8_t* memory_pointer = (int8_t *) &mem[0];
    while(infile.read((char *)&buffer, sizeof(buffer)))
    {
        memory_pointer[0] = buffer[0];
        memory_pointer++;
    }
    infile.close();
}

void MIPS::run()
{
    while(*pc <= 2000*4 or finish_sim_)  /*pc <= 2k words*/
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

void MIPS::fetch()
{
    ri = *pc;
    pc++;
}

void MIPS::decode()
{
    opcode = (ri & 0xFC00000)>>26;
    rs = (ri & 0x1F00000)>>20;
    rt = (ri & 0x1F0000)>>16;
    rd = (ri & 0xF800)>>11;
    shamt = (ri & 0x7C0)>>6;
    funct = (ri & 0x3F);
}

void MIPS::execute()
{}
