/**
 * Unversidade de Brasilia
 * Instituto de Ciências Exatas
 * Departamento de Ciencia da Computaçao
 * Organização e Arquitetura de Computadores
 * 
 * Trabalho II - MIPS Simulator
 * Porfessor: Ricardo Jacobi
 * @author Gabriel F P Araujo
 */

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

    mips.run();

    return 0;
}
