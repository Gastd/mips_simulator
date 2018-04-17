#include "simulator.h"

// Aux function
void dump_mem(uint32_t address, uint32_t size);         // Auxiliary fucntion, print the memory chunk

// simulated mips instructions
int32_t lw(uint32_t address, int16_t kte);              // Simulated instruction lw, load word
int32_t lh(uint32_t address, int16_t kte);              // Simulated instruction lh, load halfword
uint32_t lhu(uint32_t address, int16_t kte);            // Simulated instruction lhu, load unsigned halfword
int32_t lb(uint32_t address, int16_t kte);              // Simulated instruction lb, load byte
int32_t lbu(uint32_t address, int16_t kte);             // Simulated instruction lbu, load unsigned byte
void sw(uint32_t address, int16_t kte, int32_t dado);   // Simulated instruction sw, store word
void sh(uint32_t address, int16_t kte, uint16_t dado);  // Simulated instruction sh, store halfword
void sb(uint32_t address, int16_t kte, int8_t dado);    // Simulated instruction sb, load byte


MIPS::MIPS()
{
    pc = 0x00000;

    // Initialize memory with zeros
    int i = 0;
    for (i = 0; i < MEM_SIZE; ++i)
    {
        mem[i] = 0;
    }

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
    while(pc <= 0x00000ffc or !finish_sim_)  /*pc <= 2k words*/
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
    ri = mem[pc];
    pc++;
}

void MIPS::decode()
{
    opcode = (ri & 0xFC000000)>>26;
    rs = (ri & 0x3E00000)>>21;
    rt = (ri & 0x1F0000)>>15;
    rd = (ri & 0xF800)>>11;
    shamt = (ri & 0x7C0)>>6;
    funct = (ri & 0x3F);
    kte16 = (ri & 0xFFFF);
    kte26 = (ri & 0x3FFFFFF);
}

void MIPS::execute()
{
    switch(opcode)
    {
        case EXT:
        {
            switch((int)EXT)
            {
                case ADD:
                {
                    R[rd] = R[rs] + R[rt];
                }
                case SUB:
                {
                    R[rd] = R[rs] - R[rt];
                }
                case MULT:
                {
                    R[rd] = R[rs] * R[rt];
                }
                case DIV:
                {
                    R[rd] = R[rs] / R[rt];
                }
                case AND:
                {
                    R[rd] = R[rs] & R[rt];
                }
                case OR:
                {
                    R[rd] = R[rs] | R[rt];
                }
                case XOR:
                {
                    R[rd] = R[rs] ^ R[rt];
                }
                case NOR:
                {
                    R[rd] = not(R[rs] | R[rt]);
                }
                case SLT:
                {
                    R[rd] = (R[rs] < R[rt]) ? 1 : 0;
                }
                case JR:
                {
                    pc = R[rs];
                }
                case SLL:
                {
                    R[rd] = R[rt] << shamt;
                }
                case SRL:
                {
                    R[rd] = R[rt] >> shamt;
                }
                case SRA:
                {
                    R[rd] = R[rt] >> shamt;
                }
                case SYSCALL:
                {
                    if(R[2] == 10)
                        finish_sim_ = true;
                }

                case MFHI:
                {

                }
                case MFLO:
                {

                }
            }
            break;
        }
        case LW:
        {
            R[rt] = lw(R[rs], kte16);
        }
        case LB:
        {
            R[rt] = lb(R[rs], kte16);
        }
        case LBU:
        {
            R[rt] = lbu(R[rs], kte16);
        }
        case LH:
        {
            R[rt] = lh(R[rs], kte16);
        }
        case LHU:
        {
            R[rt] = lhu(R[rs], kte16);
        }
        case LUI:
        {
            R[rt] = kte16;
        }
        case SW:
        {
            sw(R[rs], kte16, R[rt]);
        }
        case SB:
        {
            sb(R[rs], kte16, R[rt]);
        }
        case SH:
        {
            sh(R[rs], kte16, R[rt]);
        }
        case BEQ:
        {
            if(R[rs] == R[rt])
                pc += (kte16<<4);
        }
        case BNE:
        {
            if(R[rs] != R[rt])
                pc += (kte16<<4);
        }
        case BLEZ:
        {
            if(R[rs] <= 0)
                pc = kte26;
        }
        case BGTZ:
        {
            if(R[rs] >= 0)
                pc = kte26;
        }
        case ADDI:
        {
            R[rt] = R[rs] + kte16;
        }
        case SLTI:
        {
            R[rd] = (R[rs] < kte16) ? 1 : 0;
        }
        case SLTIU:
        {
            R[rd] = (R[rs] < kte16) ? 1 : 0;
        }
        case ANDI:
        {
            R[rd] = R[rs] and (kte16&0xFFFF);
        }
        case ORI:
        {
            R[rt] = R[rs] | kte16;
        }
        case XORI:
        {
            R[rt] = R[rs] ^ kte16;
        }
        case J:
        {
            pc = kte26;
        }
        case JAL:
        {
            R[31] = pc;
            pc = kte26;
        }
        case ADDUI:
        {
            R[rt] = R[rs] + kte16; // Looks like ADDI
        }

    }
}

void dump_mem(uint32_t address, uint32_t size)
{
    uint32_t kte, i;
    size /= 4;
    for(kte = 0, i = 0; i < size; i++, kte += 4)
    {
        int32_t dado = lw((address + kte), 0);
        printf("mem[%d] = %08x\n", i, dado);
    }
}

int32_t lw(uint32_t address, int16_t kte)
{
    if (address % 4)
    {
        printf("Word address não múltiplo de 4\n");
        return -0x0;
    }
    uint32_t memory_address = (address + kte) / 4;
    int32_t *point_address = &mem[memory_address];

    return point_address[kte / 4];
}

int32_t lh(uint32_t address, int16_t kte)
{
    uint32_t memory_address = (address + kte) / 4;
    if (address % 2)
    {
        printf("Halfword address não múltiplo de 2\n");
        return -0x0;
    }
    int16_t *point_address = (int16_t *) &mem[memory_address];

    return point_address[kte / 2];
}

uint32_t lhu(uint32_t address, int16_t kte)
{
    uint32_t memory_address = (address + kte) / 4;
    if (address % 2)
    {
        printf("Halfword address não múltiplo de 2\n");
        return -0x0;
    }
    uint16_t *point_address = (uint16_t *) &mem[memory_address];

    return 0x0000FFFF & point_address[kte / 2];
}

int32_t lb(uint32_t address, int16_t kte)
{
    uint32_t memory_address = (address + kte) / 4;
    int8_t *point_address = (int8_t *) &mem[memory_address];

    return point_address[kte];
}

int32_t lbu(uint32_t address, int16_t kte)
{
    uint32_t memory_address = (address + kte) / 4;
    int8_t *point_address = (int8_t *) &mem[memory_address];

    return 0x000000FF & point_address[kte];
}

void sw(uint32_t address, int16_t kte, int32_t dado)
{
    uint32_t memory_address = (address + kte) / 4;
    if (address % 4)
    {
        printf("Word address não múltiplo de 4\n");
        return;
    }
    int32_t *point_address = &mem[memory_address];

    point_address[kte / 4] = dado;
}

void sh(uint32_t address, int16_t kte, uint16_t dado)
{
    uint32_t memory_address = (address + kte) / 4;
    if (address % 2)
    {
        printf("Halfword address não múltiplo de 2\n");
        return;
    }
    int16_t *point_address = (int16_t *) &mem[memory_address];

    point_address[kte / 2] = dado;
}

void sb(uint32_t address, int16_t kte, int8_t dado)
{
    uint32_t memory_address = (address + kte) / 4;
    int8_t *point_address = (int8_t *) &mem[memory_address];

    point_address[kte] = dado;
}
