#include "simulator.h"

MIPS::MIPS() : finish_sim_(false),
memory_filled_(false), pc(0x0),
ri(0x0), hi(0x0), lo(0x0),
opcode(0x0), rs(0x0), rt(0x0),
rd(0x0), shamt(0x0), funct(0x0),
kte16(0x0), kte26(0x0)
{
    // Initialize memory with zeros
    int i = 0;
    for (i = 0; i < MEM_SIZE; ++i)
        mem[i] = 0;

    for (i = 0; i < 32; ++i)
    {
        R[i] = 0;
    }
}

MIPS::~MIPS()
{
}

void MIPS::fillMemory(std::string text_path, std::string data_path)
{
    std::ifstream infile;
    // loading .text
    infile.open(text_path, std::ios::binary|std::ios::in);
    if(infile.is_open())
    {
        char *buffer = new char[4];
        int8_t *memory_pointer = (int8_t *) &mem[0];
        printf("memory_pointer = %p\n", memory_pointer);
        while (infile.read(buffer, 4))
        {
            memory_pointer[0] = buffer[0];
            memory_pointer[1] = buffer[1];
            memory_pointer[2] = buffer[2];
            memory_pointer[3] = buffer[3];
            // printf("memory_pointer = %p with %01x %01x %01x %01x\n", 
            //     memory_pointer, buffer[0], buffer[1], buffer[2], buffer[3]);
            memory_pointer+=4;
        }
        memory_filled_ = true;
        // while(infile.read((char *)&buffer, sizeof(buffer)))
        // {
        //     memory_pointer[0] = buffer[0];
        //     memory_pointer++;
        // }
        printf("mem[0] = %0x\n", mem[0]);
        infile.close();
    }
    else
    {
        std::cout << "Error opening text file" << std::endl;
    }

    // loading .data
    infile.open(data_path, std::ios::binary|std::ios::in);
    if(infile.is_open())
    {
        char *buffer = new char[4];
        int8_t *memory_pointer = (int8_t *) &mem[2048];
        printf("memory_pointer = %p\n", memory_pointer);
        while(infile.read(buffer, 4))
        {
            memory_pointer[0] = buffer[0];
            memory_pointer[1] = buffer[1];
            memory_pointer[2] = buffer[2];
            memory_pointer[3] = buffer[3];
            memory_pointer+=4;
        }
        printf("mem[2048] = %0x\n", mem[2048]);
        infile.close();
    }
    else
    {
        std::cout << "Error opening data file" << std::endl;
    }
}

void MIPS::run()
{
    if (!memory_filled_)
    {
        std::cout << "Memory not loaded" << std::endl;
        return;
    }
    while((pc <= 0x7D0) and (!finish_sim_))  /*pc <= 2k words*/
    {
        fetch();
        decode();
        execute();
    }
}

void MIPS::step()
{
    if (!memory_filled_ or pc > 0x7D0)
    {
        std::cout << "Memory not loaded" << std::endl;
        return;
    }

    fetch();
    decode();
    execute();
}

void MIPS::fetch()
{
    ri = mem[pc>>2];
    pc += 4;
}

void MIPS::decode()
{
    int16_t aux;
    opcode = (ri & 0xFC000000)>>26;
    rs = (ri & 0x3E00000)>>21;
    rt = (ri & 0x1F0000)>>16;
    rd = (ri & 0xF800)>>11;
    shamt = (ri & 0x7C0)>>6;
    funct = (ri & 0x3F);
    
    aux = (ri & 0xFFFF);
    kte16 = aux;
    kte26 = (ri & 0x3FFFFFF);
/*    printf("pc = %0x, ri = %0x, hi = %0x, \
            lo = %0x, opcode = %0x, rs = %0x, \
            rt = %0x, rd = %0x, shamt = %0x, \
            funct = %0x, kte16 = %0x, kte26 = %0x\n",
            pc, ri, hi, lo,
            opcode, rs, rt,
            rd, shamt, funct,
            kte16, kte26);*/
}

void MIPS::execute()
{
    switch(opcode)
    {
        case EXT:
        {
            switch(funct)
            {
                case ADD:
                {
                    R[rd] = R[rs] + R[rt];
                    printf("R[%d] = R[%d] + R[%d]\n", rd, rs, rt);
                    break;
                }
                case ADDU:
                {
                    R[rd] = R[rs] + R[rt];
                    printf("R[%d] = R[%d] + R[%d]\n", rd, rs, rt);
                    break;
                }
                case SUB:
                {
                    R[rd] = R[rs] - R[rt];
                    printf("R[%d] = R[%d] - R[%d]\n", rd, rs, rt);
                    break;
                }
                case MULT:
                {
                    R[rd] = R[rs] * R[rt];
                    printf("R[%d] = R[%d] * R[%d]\n", rd, rs, rt);
                    break;
                }
                case DIV:
                {
                    R[rd] = R[rs] / R[rt];
                    printf("R[%d] = R[%d] / R[%d]\n", rd, rs, rt);
                    break;
                }
                case AND:
                {
                    R[rd] = R[rs] & R[rt];
                    printf("R[%d] = R[%d] & R[%d]\n", rd, rs, rt);
                    break;
                }
                case OR:
                {
                    R[rd] = R[rs] | R[rt];
                    printf("R[%d] = R[%d] | R[%d]\n", rd, rs, rt);
                    break;
                }
                case XOR:
                {
                    R[rd] = R[rs] ^ R[rt];
                    printf("R[%d] = R[%d] ^ R[%d]\n", rd, rs, rt);
                    break;
                }
                case NOR:
                {
                    R[rd] = not(R[rs] | R[rt]);
                    printf("R[%d] = not(R[%d] | R[%d])\n", rd, rs, rt);
                    break;
                }
                case SLT:
                {
                    R[rd] = (R[rs] < R[rt]) ? 1 : 0;
                    printf("R[%d] = (R[%d] < R[%d]) ? 1 : 0\n", rd, rs, rt);
                    break;
                }
                case JR:
                {
                    pc = R[rs];
                    printf("pc = R[%d]\n", rs);
                    break;
                }
                case SLL:
                {
                    R[rd] = R[rt] << shamt;
                    printf("R[%d] = R[%d] << %d\n", rd, rs, shamt);
                    break;
                }
                case SRL:
                {
                    R[rd] = R[rt] >> shamt;
                    printf("R[%d] = R[%d] >> %d\n", rd, rs, shamt);
                    break;
                }
                case SRA:
                {
                    R[rd] = R[rt] >> shamt;
                    printf("R[%d] = R[%d] >> %d\n", rd, rs, shamt);
                    break;
                }
                case SYSCALL:
                {
                    if(R[2] == 10)
                    {
                        printf("SYSCALL EXIT\n");
                        finish_sim_ = true;
                    }
                    if(R[2] == 1)
                    {
                        // printf("SYSCALL PRINT INT\n");
                        printf("%d", (int32_t)R[4]);
                    }
                    if(R[2] == 4)
                    {
                        // printf("SYSCALL PRINT STRING\n");
                        // byte address => /4
                        int8_t offset = R[4] % 4;
                        int8_t *ptr = (int8_t*)&mem[R[4]>>2];
                        printf("%s", (char*)&ptr[offset]);
                    }
                    break;
                }

                case MFHI:
                {
                    break;
                }
                case MFLO:
                {
                    break;
                }
            }
            break;
        }
        case LW:
        {
            R[rt] = lw(R[rs], kte16);
            printf("memory_address = %d\n", R[rs]+kte16);
            printf("R[%d] = lw(R[%d], %d)\n", rt, rs, kte16);
            break;
        }
        case LB:
        {
            R[rt] = lb(R[rs], kte16);
            printf("memory_address = %d\n", R[rs]+kte16);
            printf("R[%d] = lb(R[%d], %d)\n", rt, rs, kte16);
            break;
        }
        case LBU:
        {
            R[rt] = lbu(R[rs], kte16);
            printf("memory_address = %d\n", R[rs]+kte16);
            printf("R[%d] = lbu(R[%d], %d)\n", rt, rs, kte16);
            break;
        }
        case LH:
        {
            R[rt] = lh(R[rs], kte16);
            printf("memory_address = %d\n", R[rs]+kte16);
            printf("R[%d] = lh(R[%d], %d)\n", rt, rs, kte16);
            break;
        }
        case LHU:
        {
            R[rt] = lhu(R[rs], kte16);
            printf("memory_address = %d\n", R[rs]+kte16);
            printf("R[%d] = lhu(R[%d], %d)\n", rt, rs, kte16);
            break;
        }
        case LUI:
        {
            R[rt] = kte16;
            printf("memory_address = %d\n", R[rs]+kte16);
            printf("R[%d] = %d\n", rt, kte16);
            break;
        }
        case SW:
        {
            sw(R[rs], kte16, R[rt]);
            printf("memory_address = %d\n", R[rs]+kte16);
            printf("sw(R[%d], %d, R[%d])\n", rs, kte16, rt);
            break;
        }
        case SB:
        {
            sb(R[rs], kte16, R[rt]);
            printf("memory_address = %d\n", R[rs]+kte16);
            printf("sb(R[%d], %d, R[%d])\n", rs, kte16, rt);
            break;
        }
        case SH:
        {
            sh(R[rs], kte16, R[rt]);
            printf("memory_address = %d\n", R[rs]+kte16);
            printf("sh(R[%d], %d, R[%d])\n", rs, kte16, rt);
            break;
        }
        case BEQ:
        {
            if(R[rs] == R[rt])
                pc += (kte16<<2);
            printf("if(R[%d] == R[%d]) pc += (%d<<2);\n", rs, rt, kte16);
            break;
        }
        case BNE:
        {
            if(R[rs] != R[rt])
                pc += (kte16<<2);
            printf("if(R[%d] != R[%d]) pc += (%d<<2);\n", rs, rt, kte16);
            break;
        }
        case BLEZ:
        {
            if(R[rs] <= 0)
                pc += (kte16<<2);
            printf("if(R[%d] <= 0) pc += (%d<<2);\n", rs, kte16);
            break;
        }
        case BGTZ:
        {
            if(R[rs] >= 0)
                pc += (kte16<<2);
            printf("if(R[%d] >= 0) pc += (%d<<2);\n", rs, kte16);
            break;
        }
        case ADDI:
        {
            R[rt] = R[rs] + kte16;
            printf("R[%d] = (R[%d] + %d)\n", rt, rs, kte16);
            break;
        }
        case SLTI:
        {
            R[rd] = (R[rs] < kte16) ? 1 : 0;
            printf("R[%d] = (R[%d] < %d) ? 1 : 0\n", rd, rs, kte16);
            break;
        }
        case SLTIU:
        {
            R[rd] = (R[rs] < kte16) ? 1 : 0;
            printf("R[%d] = (R[%d] < %d) ? 1 : 0\n", rd, rs, kte16);
            break;
        }
        case ANDI:
        {
            R[rd] = R[rs] & (kte16&0xFFFF);
            printf("R[%d] = R[%d] & %d\n", rt, rs, (kte16&0xFFFF));
            break;
        }
        case ORI:
        {
            R[rt] = R[rs] | kte16;
            printf("R[%d] = R[%d] | %d\n", rt, rs, kte16);
            break;
        }
        case XORI:
        {
            R[rt] = R[rs] ^ kte16;
            printf("R[%d] = R[%d] ^ %d\n", rt, rs, kte16);
            break;
        }
        case J:
        {
            // word adress => *4
            pc = kte26<<2;
            printf("J %d\n", kte26<<2);
            break;
        }
        case JAL:
        {
            R[31] = pc;
            // word adress => *4
            pc = kte26<<2;
            printf("JAL %d\n", kte26<<2);
            break;
        }
        case ADDUI:
        {
            R[rt] = R[rs] + kte16; // Looks like ADDI
            printf("R[%d] = R[%d] + %d\n", rt, rs, kte16);
            break;
        }

    }
}

void MIPS::dump_mem(uint32_t address, uint32_t size)
{
    uint32_t kte, i;
    size /= 4;
    for(kte = 0, i = 0; i < size; i++, kte += 4)
    {
        int32_t dado = lw((address + kte), 0);
        printf("mem[%d] = %08x\n", i, dado);
    }
}

int32_t MIPS::lw(uint32_t address, int16_t kte)
{
    if ((address + kte) % 4)
    {
        printf("Word address não múltiplo de 4\n");
        return -0x0;
    }
    uint32_t memory_address = (address + kte) / 4;
    int32_t *point_address = &mem[memory_address];

    return point_address[0];
}

int32_t MIPS::lh(uint32_t address, int16_t kte)
{
    uint32_t memory_address = (address + kte) / 4;
    if ((address + kte) % 2)
    {
        printf("Halfword address não múltiplo de 2\n");
        return -0x0;
    }
    int16_t *point_address = (int16_t *) &mem[memory_address];

    return point_address[kte / 2];
}

uint32_t MIPS::lhu(uint32_t address, int16_t kte)
{
    uint32_t memory_address = (address + kte) / 4;
    if ((address + kte) % 2)
    {
        printf("Halfword address não múltiplo de 2\n");
        return -0x0;
    }
    uint16_t *point_address = (uint16_t *) &mem[memory_address];

    return 0x0000FFFF & point_address[kte / 2];
}

int32_t MIPS::lb(uint32_t address, int16_t kte)
{
    uint32_t memory_address = (address + kte) / 4;
    int8_t *point_address = (int8_t *) &mem[memory_address];

    return point_address[kte];
}

int32_t MIPS::lbu(uint32_t address, int16_t kte)
{
    uint32_t memory_address = (address + kte) / 4;
    int8_t *point_address = (int8_t *) &mem[memory_address];

    return 0x000000FF & point_address[kte];
}

void MIPS::sw(uint32_t address, int16_t kte, int32_t dado)
{
    uint32_t memory_address = (address + kte) / 4;
    if ((address + kte) % 4)
    {
        printf("Word address não múltiplo de 4\n");
        return;
    }
    int32_t *point_address = &mem[memory_address];

    point_address[0] = dado;
}

void MIPS::sh(uint32_t address, int16_t kte, uint16_t dado)
{
    uint32_t memory_address = (address + kte) / 4;
    if ((address + kte) % 2)
    {
        printf("Halfword address não múltiplo de 2\n");
        return;
    }
    int16_t *point_address = (int16_t *) &mem[memory_address];

    point_address[kte / 2] = dado;
}

void MIPS::sb(uint32_t address, int16_t kte, int8_t dado)
{
    uint32_t memory_address = (address + kte) / 4;
    int8_t *point_address = (int8_t *) &mem[memory_address];

    point_address[kte] = dado;
}
