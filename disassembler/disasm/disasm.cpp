#include <disasm.h>

namespace {
    constexpr short OP_LENGTH[256] {
    //x 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
        1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
        1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
        1, 3, 3, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 1, 2, 1,
        1, 3, 3, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 3, 3, 3, 1, 2, 1, 1, 1, 3, 3, 3, 3, 2, 1,
        1, 1, 3, 2, 3, 1, 2, 1, 1, 1, 3, 2, 3, 3, 2, 1,
        1, 1, 3, 1, 3, 1, 2, 1, 1, 1, 3, 1, 3, 3, 2, 1,
        1, 1, 3, 1, 3, 1, 2, 1, 1, 1, 3, 1, 3, 3, 2, 1,
    };
}

namespace disasm {
    std::vector<char> load_binary(const std::string& bin_path)
    {
        std::ifstream bin_file{ bin_path, std::ios::binary | std::ios::in };
        if (!bin_file.is_open()) { return {}; }
        auto bin_size{ std::filesystem::file_size(bin_path) };
        std::vector<char> out_bin_code( bin_size, {} );
        bin_file.read(out_bin_code.data(), bin_size);
        bin_file.close();
        return out_bin_code;
    }

    // TODO: implement me
    std::vector<char> disassemble(const std::vector<char>& in_bin_code)
    {
        if (in_bin_code.empty()) { return {}; }
        std::vector<char> asm_code;
        auto op = in_bin_code.begin();
        while(op != in_bin_code.end()) {
            switch(*op && 0xFF) {
                case 0x00:
                    op += OP_LENGTH[*op];
            }
        }
        
        return asm_code;
    }

    // TODO: implement me
    bool save_asm(const std::string& asm_path, const std::string& in_asm_code)
    {
        if (in_asm_code.empty() || asm_path.empty()) { return false; }

        return false;
    }

    ////////

    bool print_binary_code(const std::vector<char> bin_code, std::size_t row_length)
    {
        if (bin_code.empty()) { return false; }

        for (std::size_t i = 0; i < bin_code.size(); i++) {
            if (i != 0 && i % row_length == 0) {
                std::cout << '\n';
            }
            std::cout << std::uppercase << std::setfill('0') << std::setw(2) << std::hex
                      << (bin_code[i] & 0xFF);
            std::cout << ' ';
        }
        std::cout << std::endl;

        return true;
    }

    bool print_binary_code(const std::vector<char> bin_code)
    {
        return print_binary_code(bin_code, DEFAULT_ROW_LENGTH);
    }

    bool print_binary_file(const std::string& bin_path, std::size_t row_length)
    {
        return print_binary_code(load_binary(bin_path), row_length);
    }

    bool print_binary_file(const std::string& bin_path)
    {
        return print_binary_code(load_binary(bin_path), DEFAULT_ROW_LENGTH);
    }
}

