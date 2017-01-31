#include "linker.h"

int main(int argc, char const * argv[]) {
    // definition
    Message system_message;
    int module_number;
    std::vector<Module> M;
    std::vector<ND> symbol_table;

    // input
    if (argc > 2) {
        freopen(argv[1], "r", stdin);
    }
    get_input(module_number, M);

    // processing
    pass_one(module_number, M, symbol_table, system_message);
    pass_two(module_number, M, symbol_table, system_message);

    // print symbol table
    int sm_count = 0;
    std::cout << "Symbol Table\n";
    for (int i = 0; i < symbol_table.size(); i++, sm_count++) {
        std::cout << symbol_table[i] << system_message.get_messages(sm_count) << "\n";
    }
    std::cout << "\n";

    // print memory address
    int memory_address = 0;
    std::cout << "Memory Map\n";
    for (int i = 0; i < module_number; i++) {
        for (int j = 0; j < M[i].get_program_number(); j++, memory_address++, sm_count++) {
            std::ostringstream out_address;
            out_address << memory_address << ": ";
            std::cout << std::setw(4) << std::left << out_address.str() << M[i].get_program_list()[j].get_W()
                      << system_message.get_messages(sm_count) << std::endl;
        }
    }

    return 0;
}