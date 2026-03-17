#ifndef DISASM_H
#define DISASM_H

#include <format>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <vector>
#include <sstream>

namespace disasm {
    std::vector<char> load_binary(const std::string& bin_path);
    std::vector<char> disassemble(const std::vector<char>& in_bin_code);
    bool save_asm(const std::string& asm_path, const std::string& in_asm_code);

    constexpr std::size_t DEFAULT_ROW_LENGTH{ 8 };
    bool print_binary_code(const std::vector<char> bin_code, std::size_t row_length);
    bool print_binary_code(const std::vector<char> bin_code);
    bool print_binary_file(const std::string& bin_path, std::size_t row_length);
    bool print_binary_file(const std::string& bin_path);
}

#endif // DISASM_H
