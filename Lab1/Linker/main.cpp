#include "linker.h"

int main(int argc, char const * argv[]) {
    // definition
    std::string input;
    int module_number;
    std::vector<Module> M;
    std::vector<ND> symbol_table;

    // input
    if (argc > 1) {
        std::ofstream my_file;
        std::string filename = argv[0];
        my_file.open(filename);
        my_file.close();
        return 0;
    }
    else {
        get_input(module_number, M);
    }

    // processing
    pass_one(module_number, M, symbol_table);
    pass_two(module_number, M, symbol_table);

    // print symbol table
    std::cout << "Symbol Table\n";
    for (int i = 0; i < symbol_table.size(); i++) {
        std::cout << symbol_table[i] << "\n";
    }
    std::cout << "\n";

    // print memory address
    int memory_address = 0;
    std::cout << "Memory Map\n";
    for (int i = 0; i < module_number; i++) {
        for (int j = 0; j < M[i].get_program_number(); j++, memory_address++) {
            std::ostringstream out_address;
            out_address << memory_address << ": ";
            std::cout << std::setw(4) << std::left << out_address.str() << M[i].get_program_list()[j].get_W() << std::endl;
        }
    }

    return 0;
}