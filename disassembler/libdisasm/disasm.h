#ifndef DISASM_H
#define DISASM_H

#include <format>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <vector>
#include <sstream>
#include <locale>

namespace disasm {

    // Returns empty vector<char> on failure (empty parameter)
    std::vector<char> load_binary(const std::string& bin_path);

    // Returns empty string on failure (empty parameter)
    // Unknown op codes will be rendered as '???'
    // Alternate op codes will be rendered as '???'
    std::string disassemble(const std::vector<char>& in_bin_code);

    // TODO: make (wrapper) struct for AssemblyCode or place header data in the
    // assembly code outputted by disassemble(), because right now there are no
    // checks making sure in_asm_code is actual assembly code
    bool save_asm(const std::string& asm_path, const std::string& in_asm_code);

    static constexpr const std::size_t DEFAULT_ROW_LENGTH{ 8 };
    bool print_binary_code(const std::vector<char>& bin_code, std::size_t row_length);
    bool print_binary_code(const std::vector<char>& bin_code);
    bool print_binary_file(const std::string& bin_path, std::size_t row_length);
    bool print_binary_file(const std::string& bin_path);

    // 8-bit to *UPPERCASE* hex string
    std::string hex8u(int x);

    // 8-bit to *lowercase* hex string
    std::string hex8l(int x);

    // 16-bit to *UPPERCASE* hex string
    std::string hex16u(int x);

    // 16-bit to *lowercase* hex string
    std::string hex16l(int x);

    std::string get_op_string(const char* op);
}

#endif // DISASM_H
