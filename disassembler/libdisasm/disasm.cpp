#include <disasm.h>

namespace {
    constexpr short OP_BYTE_LENGTH[256] {
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

    const char* OP_STRING[]{
        "NOP",
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
        //bin_file.close(); // Destructor will handle it
        return out_bin_code;
    }

    std::string disassemble(const std::vector<char>& in_bin_code)
    {
        if (in_bin_code.empty()) { return {}; }
        std::string asm_code;
        std::size_t pc{ 0 };
        auto code{ &in_bin_code.data()[pc] };
        while(pc < in_bin_code.size()) {
            asm_code += hex16u(pc);
            asm_code += "  ";
            // TODO: implement all opcode strings
            switch(*code) {
                case 0x00:
                    asm_code += "NOP";
                    break;
                // case 0x01:
                //     break;
                // case 0x02:
                //     break;
                // case 0x03:
                //     break;
                // case 0x04:
                //     break;
                // case 0x05:
                //     break;
                // case 0x06:
                //     break;
                // case 0x07:
                //     break;
                // case 0x09:
                //     break;
                // case 0x0A:
                //     break;
                // case 0x0B:
                //     break;
                case 0x0E:
                    asm_code += "MVI    C, #$";
                    asm_code += disasm::hex8u(code[1]);
                    break;
                default:
                    asm_code += "???";
                    break;
            }
            auto op_bytes = OP_BYTE_LENGTH[static_cast<unsigned char>(*code)];
            pc += op_bytes;
            code += op_bytes;
            asm_code += "\n";
        }
        return asm_code;
    }

    // Returns false (bool) if fails
    bool save_asm(const std::string& asm_path, const std::string& in_asm_code)
    {
        if (in_asm_code.empty() || asm_path.empty()) { return false; }
		std::ofstream asm_file{ asm_path, std::ios::trunc };
        if (!asm_file) { return false; }
		asm_file << in_asm_code;
		// asm_file.close() // Destructor will handle this.
        return true;
    }

    ////////

    bool print_binary_code(const std::vector<char>& bin_code, std::size_t row_length)
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

    bool print_binary_code(const std::vector<char>& bin_code)
    {
        return disasm::print_binary_code(bin_code, DEFAULT_ROW_LENGTH);
    }

    bool print_binary_file(const std::string& bin_path, std::size_t row_length)
    {
        return disasm::print_binary_code(disasm::load_binary(bin_path), row_length);
    }

    bool print_binary_file(const std::string& bin_path)
    {
        return disasm::print_binary_code(disasm::load_binary(bin_path), DEFAULT_ROW_LENGTH);
    }



	static constexpr const char* HEX_DIGITS_LOWER{ "0123456789abcdef" };
	static constexpr const char* HEX_DIGITS_UPPER{ "0123456789ABCDEF" };
    std::string hex8u(int x)
    {
        char hex_chars[3]{ 0 };
		hex_chars[0] = HEX_DIGITS_UPPER[(x >> 4) & 0x0F];
		hex_chars[1] = HEX_DIGITS_UPPER[x & 0x0F];
        std::string hex{ hex_chars };
        return hex;
    }

    std::string hex8l(int x)
    {
        char hex_chars[3]{ 0 };
        hex_chars[0] = HEX_DIGITS_LOWER[(x >> 4) & 0x0F];
        hex_chars[1] = HEX_DIGITS_LOWER[x & 0x0F];
        std::string hex{ hex_chars };
        return hex;
    }

    std::string hex16u(int x)
    {
        char hex_chars[5]{ 0 };
        hex_chars[0] = HEX_DIGITS_UPPER[(x >> 12) & 0x0F];
        hex_chars[1] = HEX_DIGITS_UPPER[(x >> 8) & 0x0F];
        hex_chars[2] = HEX_DIGITS_UPPER[(x >> 4) & 0x0F];
        hex_chars[3] = HEX_DIGITS_UPPER[(x) & 0x0F];
        std::string hex{ hex_chars };
        return hex;
    }

    std::string hex16l(int x)
    {
        char hex_chars[5]{ 0 };
        hex_chars[0] = HEX_DIGITS_LOWER[(x >> 12) & 0x0F];
        hex_chars[1] = HEX_DIGITS_LOWER[(x >> 8) & 0x0F];
        hex_chars[2] = HEX_DIGITS_LOWER[(x >> 4) & 0x0F];
        hex_chars[3] = HEX_DIGITS_LOWER[(x) & 0x0F];
        std::string hex{ hex_chars };
        return hex;
    }
}

