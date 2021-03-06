#include "linker.h"

void process() {
    // definition
    int module_number;
    std::vector<Module> M;
    std::vector<ST> symbol_table;
    std::vector<std::string> usage_message;
    Message system_message;

    // input
    get_input(module_number, M);

    // processing
    pass_one(module_number, M, symbol_table, system_message);
    pass_two(module_number, M, symbol_table, usage_message, system_message);

    // print symbol table
    std::cout << "Symbol Table\n";
    for (int i = 0; i < symbol_table.size(); i++) {
        std::cout << symbol_table[i] << symbol_table[i].get_message() << "\n";
    }
    std::cout << "\n";

    // print memory address
    int memory_address = 0;
    std::cout << "Memory Map\n";
    for (int i = 0; i < module_number; i++) {
        for (int j = 0; j < M[i].get_program_number(); j++, memory_address++) {
            std::ostringstream out_address;
            out_address << memory_address << ": ";
            std::cout << std::setw(4) << std::left << out_address.str() << M[i].get_program_list()[j].get_W()
                      << M[i].get_program_list()[j].get_message() << std::endl;
        }
    }

    // print usage message
    std::cout << std::endl;
    for (int i = 0; i < usage_message.size(); i++) {
        std::cout << usage_message[i] << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char const * argv[]) {
    // input
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            std::cin.clear();
            std::cin.sync();
            freopen(argv[i], "r", stdin);
            process();
        }
    }
    else {
        std::cin.clear();
        std::cin.sync();
        process();
    }

    return 0;
}