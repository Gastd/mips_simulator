// Unversidade de Brasilia
// Instituto de Ciências Exatas
// Departamento de Ciencia da Computaçao
// Organização e Arquitetura de Computadores
// Trabalho I - Memória MIPS
// Porfessor: Ricardo Jacobi
// Aluno: Gabriel F P Araujo
// Matrícula: 12/0050943
// 

#include "memory.h"

// int main(int argc, char const *argv[])
// {
//     // Initialize memory with zeros
//     int i = 0;
//     for (i = 0; i < MEM_SIZE; ++i)
//     {
//         mem[i] = 0;
//     }

//     printf("memory pointer = %p\n", mem);

//     printf("Teste - 1\n");
//     sb(0, 0, 0x04); sb(0, 1, 0x03); sb(0, 2, 0x02); sb(0, 3, 0x01);
//     sb(4, 0, 0xFF); sb(4, 1, 0xFE); sb(4, 2, 0xFD); sb(4, 3, 0xFC);
//     sh(8, 0, 0xFFF0); sh(8, 2, 0x8C);
//     sw(12, 0, 0xFF);
//     sw(16, 0, 0xFFFF);
//     sw(20, 0, 0xFFFFFFFF);
//     sw(24, 0, 0x80000000);
//     printf("Memória inicializada\n\n");

//     // Dumping first 28 words from memory/
//     printf("Teste - 2\n");
//     dump_mem(0, 28);
//     printf("\n");

//     printf("Teste - 3.a\n");
//     printf("\tImprimindo em hexa\n");
//     printf("\tlb(0,0) = %02d\t lb(0,1) = %02x\t lb(0,2) = %02x\t lb(0,3) = %02x\n", lb(0,0), lb(0,1), lb(0,2), lb(0,3));
//     printf("\tImprimindo em decimal\n");
//     printf("\tlb(0,0) = %02d\t lb(0,1) = %02d\t lb(0,2) = %02d\t lb(0,3) = %02d\n", lb(0,0), lb(0,1), lb(0,2), lb(0,3));

//     printf("Teste - 3.b\n");
//     printf("\tImprimindo em hexa\n");
//     printf("\tlb(4,0) = %02x\t lb(4,1) = %02x\t lb(4,2) = %02x\t lb(4,3) = %02x\n", (0xFF & lb(4,0)), (0xFF & lb(4,1)), (0xFF & lb(4,2)), (0xFF & lb(4,3)));
//     printf("\tImprimindo em decimal\n");
//     printf("\tlb(4,0) = %02d\t lb(4,1) = %02d\t lb(4,2) = %02d\t lb(4,3) = %02d\n", lb(4,0), lb(4,1), lb(4,2), lb(4,3));

//     printf("Teste - 3.c\n");
//     printf("\tImprimindo em hexa\n");
//     printf("\tlbu(4,0) = %02x\t lbu(4,1) = %02x\t lbu(4,2) = %02x\t lbu(4,3) = %02x\n", lbu(4,0), lbu(4,1), lbu(4,2), lbu(4,3));
//     printf("\tImprimindo em decimal\n");
//     printf("\tlbu(4,0) = %02d\t lbu(4,1) = %02d\t lbu(4,2) = %02d\t lbu(4,3) = %02d\n", lbu(4,0), lbu(4,1), lbu(4,2), lbu(4,3));

//     printf("Teste - 3.d\n");
//     printf("\tImprimindo em hexa\n");
//     printf("\tlh(8,0) = %04x\t lh(8,2) = %04x\n", (0xFFFF & lh(8,0)), (0xFFFF & lh(8,2)));
//     printf("\tImprimindo em decimal\n");
//     printf("\tlh(8,0) = %04d\t lh(8,2) = %04d\n", lh(8,0), lh(8,2));

//     printf("Teste - 3.e\n");
//     printf("\tImprimindo em hexa\n");
//     printf("\tlhu(8,0) = %04x\t lhu(8,2) = %04x\n", lhu(8,0), lhu(8,2));
//     printf("\tImprimindo em decimal\n");
//     printf("\tlhu(8,0) = %04d\t lhu(8,2) = %04d\n", lhu(8,0), lhu(8,2));

//     printf("Teste - 3.f\n");
//     printf("\tImprimindo em hexa\n");
//     printf("\tlw(12,0) = %08x\t lw(16,0) = %08x\t lw(20,0) = %08x\n", lw(12,0), lw(16,0), lw(20,0));
//     printf("\tImprimindo em decimal\n");
//     printf("\tlw(12,0) = %08d\t lw(16,0) = %08d\t lw(20,0) = %08d\n", lw(12,0), lw(16,0), lw(20,0));

    
//     printf("Teste Extra\n");
//     printf("Tentativa de escrita desalinhada (halfword)\n");
//     sh(3, 0, 0xF030); sh(3, 1, 0x2B01);
//     printf("Tentativa de escrita desalinhada (word)\n");
//     sw(21, 0, 0x12);
//     sw(23, 0, 0x13);
//     printf("Tentativa de leitura desalinhada (halfword)\n");
//     lh(1, 0); lh(3, 1);
//     printf("Tentativa de leitura desalinhada (word)\n");
//     lw(2, 0);
//     lw(6, 0);
//     dump_mem(0, 28);


//     return 0;
// }

void dump_mem(uint32_t address, uint32_t size)
{
    int32_t kte, i;
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
