#include <stdint.h>
#include <stdio.h>

#define MEM_SIZE 4096   // Simulated memory's size

// Memory
int32_t mem[MEM_SIZE];  // Memory array

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
