#include <disasm.h>

// shell commands to build & run
// (in intel8080/ directory)
// intel8080$ cmake -B build
// intel8080$ cmake --build build
// intel8080$ ./build/disassembler/disasm_cli/disasm rom/spaceinvaders/invaders.h

namespace disasm_test {
    constexpr std::size_t MIN_ARGS{ 2 };
    bool args_do_not_exist(int argc, char* argv[])
    {
        if (argc < (MIN_ARGS + 1)) {
            printf("Usage: %s <path to binary file> <row length>\n", argv[0]);
            return true;
        }
        return false;
    }

    bool test_load_binary(int argc, char* argv[])
    {
        if (args_do_not_exist(argc, argv)) { return false; }

        const std::string bin_path{ argv[1] };
        std::vector<char> bin_code{ disasm::load_binary(bin_path) };
        if (bin_code.empty()) {
            std::cout << "Error loading binary" << std::endl;
            return false;
        }
        return true;
    }

    bool test_print_binary_code_w_row_length(int argc, char* argv[])
    {
        if (args_do_not_exist(argc, argv)) { return false; }

        const std::string bin_path{ argv[1] };
        const std::size_t row_length{ static_cast<std::size_t>(std::stoi(argv[2])) };
        return disasm::print_binary_code(disasm::load_binary(bin_path), row_length);
    }

    bool test_print_binary_code_default_row_length(int argc, char* argv[])
    {
        if (args_do_not_exist(argc, argv)) { return false; }

        const std::string bin_path{ argv[1] };
        const std::vector<char> bin_code{ disasm::load_binary(bin_path) };
        return disasm::print_binary_code(bin_code);
    }

    bool test_print_binary_file_w_row_length(int argc, char* argv[])
    {
        if (args_do_not_exist(argc, argv)) { return false; }

        const std::string bin_path{ argv[1] };
        const std::size_t row_length{ static_cast<std::size_t>(std::stoi(argv[2])) };
        return disasm::print_binary_file(bin_path, row_length);
    }

    bool test_print_binary_file_default_row_length(int argc, char* argv[])
    {
        if (args_do_not_exist(argc, argv)) { return false; }

        const std::string bin_path{ argv[1] };
        return disasm::print_binary_file(bin_path);
    }

    static int passed{ 0 };
    static int total{ 0 };
    bool test_case(const std::string& test_name, bool (*test_function)(int, char**), int argc, char* argv[])
    {
        total++;
        if (!(*test_function)(argc, argv)) {
            std::cout << "FAIL: " << test_name << std::endl;
            return false;
        }
        else {
            std::cout << "PASS: " << test_name << std::endl;
            passed++;
            return true;
        }
    }
}
