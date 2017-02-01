//
// Created by Chrome on 1/29/17.
//

#ifndef LINKER_LINKER_H
#define LINKER_LINKER_H

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>

const int MACHINE_SIZE = 200;

class Message{
public:
    Message() {}
    std::string add_success() {
        return " Success.";
    }
    std::string change_to_multiply_defined_error() {
        return " Error: This variable is multiply defined; first value used.";
    }
    std::string add_symbol_not_defined_error(std::string s) {
        return " Error: " + s + " is not defined; zero used.";
    }
    std::string add_symbol_not_used_warning(std::string s, int module_number) {
        std::ostringstream mn;
        mn << module_number;
        return " Warning: " + s + "was defined in module " + mn.str() + " but never used.";
    }
    std::string add_multiple_variables_used_error() {
        return " Error: Multiple variables used in instruction; all but first ignored.";
    }
    std::string add_def_exceeds_error() {
        return " Error: Definition exceeds module size; first word in module used.";
    }
    std::string add_symbol_exceeds_error(std::string s, int module_number) {
        std::ostringstream mn;
        mn << module_number;
        return " Error: Use of " + s + " in module " + mn.str() + " exceeds module size; use ignored.";
    }
    std::string add_relative_exceeds_error() {
        return " Error: Relative address exceeds module size; zero used.";
    }
    std::string add_absolute_exceeds_error() {
        return " Error: Absolute address exceeds machine size; zero used.";
    }
};

class ND{ // definition list
    std::string S; // S is the symbol being defined
    int R; // R is the relative address to which the symbol refers
    std::string message;
public:
    ND(std::string s, int r, std::string m = "") {
        S = s;
        R = r;
        message = m;
    }
    std::string get_S() {
        return S;
    }
    int get_R() {
        return R;
    }
    std::string get_message() {
        return message;
    }
    void change_message(std::string new_m) {
        message = new_m;
    }
    friend std::ostream &operator << (std::ostream & out, ND & nd);
    friend std::ostream &operator << (std::ostream & out, ND & nd) {
        out << nd.S << "=" << nd.R;
        return out;
    }
};

class NU{ // use list
    std::string S; // S is an external symbol used in the module
    std::vector<int> R; // R is a list of relative addresses in the module in which the symbol is used
public:
    NU(std::string s, std::vector<int> r) {
        S = s;
        R = r;
    }
    std::string get_S() {
        return S;
    }
    std::vector<int> get_R() {
        return R;
    }
    friend std::ostream &operator << (std::ostream & out, NU & nu);
    friend std::ostream &operator << (std::ostream & out, NU & nu) {
        out << nu.S;
        for (int i = 0; i < nu.R.size(); i++) {
            out << " " << nu.R[i];
        }
        return out;
    }
};

class NT { // program text
    char T; // T is a single character indicating if the address in the word is I, A, R, E
    int W; // W is a 4-digit instruction
    std::string message;
public:
     NT(char t, int w) {
         T = t;
         W = w;
         message = "";
     }
    char get_T() {
        return T;
    }
    int get_W() {
        return W;
    }
    std::string get_message() {
        return message;
    }
    void change_W(int new_w) {
        W = new_w;
    }
    void change_message(std::string new_m) {
        message = new_m;
    }
    friend std::ostream &operator << (std::ostream & out, NT & nt);
    friend std::ostream &operator << (std::ostream & out, NT & nt) {
        out << nt.T << "=" << nt.W;
        return out;
    }
};

class Module {
    int base_address;

    int definition_number;
    std::vector<ND> definition_list;

    int use_number;
    std::vector<NU> use_list;

    int program_number;
    std::vector<NT> program_list;

public:
    Module(int dn, std::vector<ND> nd, int un, std::vector<NU> nu, int pn, std::vector<NT> nt) {
        base_address = 0;
        definition_number = dn;
        definition_list = nd;
        use_number = un;
        use_list = nu;
        program_number = pn;
        program_list = nt;
    }
    int get_base_address(){
        return base_address;
    }
    int get_definition_number() {
        return definition_number;
    }
    std::vector<ND> & get_definition_list() {
        return definition_list;
    }
    int get_use_number() {
        return use_number;
    }
    std::vector<NU> & get_use_list() {
        return use_list;
    }
    int get_program_number() {
        return program_number;
    }
    std::vector<NT> & get_program_list() {
        return program_list;
    }
    void change_base_address(int new_ba) {
        base_address = new_ba;
    }
    friend std::ostream &operator << (std::ostream & out, Module & M);

private:
    friend std::ostream &operator << (std::ostream & out, Module & M) {
        out << M.definition_number;
        for (int i = 0; i < M.definition_number; i++) {
            out << " " << M.definition_list[i];
        }
        out << "\n";

        out << M.use_number;
        for (int i = 0; i < M.use_number; i++) {
            out << " " <<  M.use_list[i];
        }
        out << "\n";

        out << M.program_number;
        for (int i =0; i < M.program_number; i++) {
            out << " " <<  M.program_list[i];
        }
        out << "\n";
        return out;
    }
};

void get_input(int & module_number, std::vector<Module> & M) {
    std::cin >> module_number;  // number of modules
    for (int i = 0; i < module_number; i++) {
        // definition list
        std::vector<ND> def_list;
        int def_number;
        std::cin >> def_number;
        for (int j = 0; j < def_number; j++) {
            std::string def_symbol;
            std::cin >> def_symbol;

            int relative_address;
            std::cin >> relative_address;

            ND nd(def_symbol, relative_address);
            def_list.push_back(nd);
        }
        // use list
        std::vector<NU> use_list;
        int use_number;
        std::cin >> use_number;
        for (int j = 0; j < use_number; j++) {
            std::string use_symbol;
            std::cin >> use_symbol;

            std::vector<int> use_address;
            int tmp_use_address;
            std::cin >> tmp_use_address;
            while (tmp_use_address != -1) {
                use_address.push_back(tmp_use_address);
                std::cin >> tmp_use_address;
            }
            use_address.push_back(-1);

            NU nu(use_symbol, use_address);
            use_list.push_back(nu);
        }
        // program text
        std::vector<NT> program_text;
        int prog_number;
        std::cin >> prog_number;
        for (int j = 0; j < prog_number; j++) {
            char type;
            std::cin >> type;

            int word;
            std::cin >> word;

            NT nt(type, word);
            program_text.push_back(nt);
        }
        Module m(def_number, def_list, use_number, use_list, prog_number, program_text);
        M.push_back(m);
    }
}

int check_symbol_existence(std::vector<ND> symbol_table, std::string symbol) {
    for (int i = 0; i < symbol_table.size(); i++) {
        if (symbol == symbol_table[i].get_S()) {
            return i;
        }
    }
    return -1;

}

void pass_one(int module_number, std::vector<Module> & M, std::vector<ND> & symbol_table, Message sys_m) {
    int cur_address = 0;
    for (int i = 0; i < module_number; i++) {
        M[i].change_base_address(cur_address);
        cur_address = cur_address + M[i].get_program_number();
        for (int j = 0; j < M[i].get_definition_number(); j++) {
            std::string symbol = M[i].get_definition_list()[j].get_S();
            int check = check_symbol_existence(symbol_table, symbol);
            if (check > -1) {
                symbol_table[check].change_message(sys_m.change_to_multiply_defined_error());
                continue;
            }
            std::string message;
            int relative_add = M[i].get_definition_list()[j].get_R();
            int absolute_add = M[i].get_definition_list()[j].get_R() + M[i].get_base_address();
            if (relative_add >= M[i].get_program_number()) {
                message = sys_m.add_def_exceeds_error();
                absolute_add = 0;
            }
            else message = sys_m.add_success();
            ND tmp_nd(symbol, absolute_add, message);
            symbol_table.push_back(tmp_nd);
        }
    }
}

void pass_two(int module_number, std::vector<Module> & M, std::vector<ND> symbol_table, Message sys_m) {
    for (int i = 0; i < module_number; i++) {
        // process type 'E'
        for (int j = 0; j < M[i].get_use_number(); j++) {
            std::string symbol = M[i].get_use_list()[j].get_S();
            int def_address = -1;
            for (int k = 0; k < symbol_table.size(); k++) {
                if (symbol == symbol_table[k].get_S()) {
                    def_address = symbol_table[k].get_R();
                    break;
                }
            }
            if (def_address > M[i].get_program_number()) {
                M[i].get_program_list()[j]
            }
            if (def_address != -1) {
                for (int k = 0; k < M[i].get_use_list()[j].get_R().size(); k++) {
                    int symbol_use_index = M[i].get_use_list()[j].get_R()[k];
                    if (symbol_use_index != -1 and M[i].get_program_list()[symbol_use_index].get_T() == 'E') {
                        int w = M[i].get_program_list()[symbol_use_index].get_W();
                        w = w / 1000 * 1000 + def_address;
                        M[i].get_program_list()[symbol_use_index].change_W(w);
                    }
                }
            }
        }

        for (int j = 0; j < M[i].get_program_number(); j++) {
            char t = M[i].get_program_list()[j].get_T();
            if (t == 'I') {
                M[i].get_program_list()[j].change_message(sys_m.add_success());
            }
            else if (t == 'A') {
                int w = M[i].get_program_list()[j].get_W();
                if (w % 1000 >= MACHINE_SIZE) {
                    M[i].get_program_list()[j].change_message(sys_m.add_absolute_exceeds_error());
                    M[i].get_program_list()[j].change_W(w / 1000 * 1000);
                }
                else M[i].get_program_list()[j].change_message(sys_m.add_success());
            }
            else if (t == 'R') {
                int w = M[i].get_program_list()[j].get_W();
                if (w % 1000 >= M[i].get_program_number()) {
                    M[i].get_program_list()[j].change_message(sys_m.add_relative_exceeds_error());
                    M[i].get_program_list()[j].change_W(w / 1000 * 1000);
                }
                else {
                    M[i].get_program_list()[j].change_message(sys_m.add_success());
                    w = w + M[i].get_base_address();
                    M[i].get_program_list()[j].change_W(w);
                }
            }
            else {
                continue;
            }
        }
    }
}

#endif //LINKER_LINKER_H
