#include <disasm.h>

int main(int argc, char* argv[])
{
    // test_case("load_binary", test_load_binary, argc, argv);
    // test_case("print_binary_code w/o default row length", test_print_binary_code_w_row_length, argc, argv);
    // test_case("print_binary_code w/ default row length", test_print_binary_code_default_row_length, argc, argv);
    // test_case("print_binary_file w/o default row length", test_print_binary_file_w_row_length, argc, argv);
    // test_case("print_binary_file w/ default row length", test_print_binary_file_default_row_length, argc, argv);
    // std::cout << "Passed: " << passed << "/" << total << std::endl;

    if (argc < 3) {
        printf("Usage: %s <binary file input> <asm file output>", argv[0]);
        return 1;
    }

    auto bin_code{ disasm::load_binary(argv[1]) };
    if (bin_code.empty()) {
        std::cout << "Failed to load binary file" << std::endl;
        return 1;
    }
    auto asm_code{ disasm::disassemble(bin_code) };
    if (asm_code.empty()) {
        std::cout << "Failed to disassemble the binary" << std::endl;
        return 1;
    }
    if (!disasm::save_asm(argv[2], asm_code)) {
        std::cout << "Failed to save disassembled binary file" << std::endl;
        return 1;
    }
    
    return 0;
}
