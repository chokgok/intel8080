#include <disasm.h>

namespace {
    constexpr const short OP_BYTE_LENGTH[256] {
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

    constexpr const char* OP_STRING[] {
        "NOP",
        "LXI    B, #${0:02x}{1:02x}",
        "STAX   B",
        "INX    B",
        "INR    B",
        "DCR    B",
        "MVI    B, #${0:02x}",
        "RLC",
        "*NOP",
        "DAD    B",
        "LDAX   B",
        "DCX    B",
        "INR    C",
        "DCR    C",
        "MVI    C, #${0:02x}",
        "RRC",
        "*NOP",
        "LXI    D, #${0:02x}{1:02x}",
        "STAX   D",
        "INX    D",
        "INR    D",
        "DCR    D",
        "MVI    D, #${0:02x}",
        "RAL",
        "*NOP",
        "DAD    D",
        "LDAX   D",
        "DCX    D",
        "INR    E",
        "DCR    E",
        "MVI    E, #${0:02x}",
        "RAR",
        "*NOP",
        "LXI    H, #${0:02x}{1:02x}",
        "SHLD   ${0:02x}{1:02x}",
        "INX    H",
        "INR    H",
        "DCR    H",
        "MVI    H, #${0:02x}",
        "DAA",
        "*NOP",
        "DAD    H",
        "LHLD   ${0:02x}{1:02x}",
        "DCX    H",
        "INR    L",
        "DCR    L",
        "MVI    L, #${0:02x}",
        "CMA",
        "*NOP",
        "LXI    SP, #${0:02x}{1:02x}",
        "STA    ${0:02x}{1:02x}",
        "INX    SP",
        "INR    M",
        "DCR    M",
        "MVI    M, #${0:02x}",
        "STC",
        "*NOP",
        "DAD    SP",
        "LDA    ${0:02x}{1:02x}",
        "DCX    SP",
        "INR    A",
        "DCR    A",
        "MVI    A, #${0:02x}",
        "CMC",
        "MOV    B, B",
        "MOV    B, C",
        "MOV    B, D",
        "MOV    B, E",
        "MOV    B, H",
        "MOV    B, L",
        "MOV    B, M",
        "MOV    B, A",
        "MOV    C, B",
        "MOV    C, C",
        "MOV    C, D",
        "MOV    C, E",
        "MOV    C, H",
        "MOV    C, L",
        "MOV    C, M",
        "MOV    C, A",
        "MOV    D, B",
        "MOV    D, C",
        "MOV    D, D",
        "MOV    D, E",
        "MOV    D, H",
        "MOV    D, L",
        "MOV    D, M",
        "MOV    D, A",
        "MOV    E, B",
        "MOV    E, C",
        "MOV    E, D",
        "MOV    E, E",
        "MOV    E, H",
        "MOV    E, L",
        "MOV    E, M",
        "MOV    E, A",
        "MOV    H, B",
        "MOV    H, C",
        "MOV    H, D",
        "MOV    H, E",
        "MOV    H, H",
        "MOV    H, L",
        "MOV    H, M",
        "MOV    H, A",
        "MOV    L, B",
        "MOV    L, C",
        "MOV    L, D",
        "MOV    L, E",
        "MOV    L, H",
        "MOV    L, L",
        "MOV    L, M",
        "MOV    L, A",
        "MOV    M, B",
        "MOV    M, C",
        "MOV    M, D",
        "MOV    M, E",
        "MOV    M, H",
        "MOV    M, L",
        "HLT",
        "MOV    M, A",
        "MOV    A, B",
        "MOV    A, C",
        "MOV    A, D",
        "MOV    A, E",
        "MOV    A, H",
        "MOV    A, L",
        "MOV    A, M",
        "MOV    A, A",
        "ADD    B",
        "ADD    C",
        "ADD    D",
        "ADD    E",
        "ADD    H",
        "ADD    L",
        "ADD    M",
        "ADD    A",
        "ADC    B",
        "ADC    C",
        "ADC    D",
        "ADC    E",
        "ADC    H",
        "ADC    L",
        "ADC    M",
        "ADC    A",
        "SUB    B",
        "SUB    C",
        "SUB    D",
        "SUB    E",
        "SUB    H",
        "SUB    L",
        "SUB    M",
        "SUB    A",
        "SBB    B",
        "SBB    C",
        "SBB    D",
        "SBB    E",
        "SBB    H",
        "SBB    L",
        "SBB    M",
        "SBB    A",
        "ANA    B",
        "ANA    C",
        "ANA    D",
        "ANA    E",
        "ANA    H",
        "ANA    L",
        "ANA    M",
        "ANA    A",
        "XRA    B",
        "XRA    C",
        "XRA    D",
        "XRA    E",
        "XRA    H",
        "XRA    L",
        "XRA    M",
        "XRA    A",
        "ORA    B",
        "ORA    C",
        "ORA    D",
        "ORA    E",
        "ORA    H",
        "ORA    L",
        "ORA    M",
        "ORA    A",
        "CMP    B",
        "CMP    C",
        "CMP    D",
        "CMP    E",
        "CMP    H",
        "CMP    L",
        "CMP    M",
        "CMP    A",
        "RNZ",
        "POP    B",
        "JNZ    ${0:02x}{1:02x}",
        "JMP    ${0:02x}{1:02x}",
        "CNZ    ${0:02x}{1:02x}",
        "PUSH   B",
        "ADI    #${0:02x}",
        "RST    0",
        "RZ",
        "RET",
        "JZ     ${0:02x}{1:02x}",
        "*JMP   ${0:02x}{1:02x}",
        "CZ     ${0:02x}{1:02x}",
        "CALL   ${0:02x}{1:02x}",
        "ACI    #${0:02x}",
        "RST    1",
        "RNC",
        "POP    D",
        "JNC    ${0:02x}{1:02x}",
        "OUT    #${0:02x}",
        "CNC    ${0:02x}{1:02x}",
        "PUSH   D",
        "SUI    #${0:02x}",
        "RST    2",
        "RC",
        "*RET",
        "JC     ${0:02x}{1:02x}",
        "IN     #${0:02x}",
        "CC     ${0:02x}{1:02x}",
        "*CALL  ${0:02x}{1:02x}",
        "SBI    #${0:02x}",
        "RST    3",
        "RPO",
        "POP    H",
        "JPO    ${0:02x}{1:02x}",
        "XTHL",
        "CPO    ${0:02x}{1:02x}",
        "PUSH   H",
        "ANI    #${0:02x}",
        "RST    4",
        "RPE",
        "PCHL",
        "JPE    ${0:02x}{1:02x}",
        "XCHG",
        "CPE    ${0:02x}{1:02x}",
        "*CALL  ${0:02x}{1:02x}",
        "XRI    #${0:02x}",
        "RST    5",
        "RP",
        "POP    PSW",
        "JP     ${0:02x}{1:02x}",
        "DI",
        "CP     ${0:02x}{1:02x}",
        "PUSH   PSW",
        "ORI    #${0:02x}",
        "RST    6",
        "RM",
        "SPHL",
        "JM     ${0:02x}{1:02x}",
        "EI",
        "CM     ${0:02x}{1:02x}",
        "*CALL  ${0:02x}{1:02x}",
        "CPI    #${0:02x}",
        "RST    7",
    };
}

namespace disasm {
    std::vector<unsigned char> load_binary(const std::string& bin_path)
    {
        std::ifstream bin_file{ bin_path, std::ios::binary | std::ios::in };
        if (!bin_file.is_open()) { return {}; }
        auto bin_size{ std::filesystem::file_size(bin_path) };
        std::vector<unsigned char> out_bin_code( bin_size, {} );
        bin_file.read(reinterpret_cast<char*>(out_bin_code.data()), bin_size);
        //bin_file.close(); // Destructor will handle it
        return out_bin_code;
    }

    std::string disassemble(const std::vector<unsigned char>& in_bin_code)
    {
        if (in_bin_code.empty()) { return {}; }
        std::string asm_code;
        std::size_t pc{ 0 };
        auto code{ &in_bin_code.data()[pc] };
        while(pc < in_bin_code.size()) {
            asm_code += std::format("{:04x}  ", pc);
            // asm_code += hex16u(pc);
            // asm_code += "  ";
            // TODO: implement all opcode strings
            asm_code += get_op_string(code);
            auto op_bytes = OP_BYTE_LENGTH[*code];
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

    bool print_binary_code(const std::vector<unsigned char>& bin_code, std::size_t row_length)
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

    bool print_binary_code(const std::vector<unsigned char>& bin_code)
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

    std::string get_op_string(const unsigned char* op)
    {
        // TODO: should I add file_size parameter and check if there's actual
        // room in the array for byte_little and byte_big?
        int byte_little;
        int byte_big;
        short length = OP_BYTE_LENGTH[*op];

        bool has_one_byte = length >= 2;
        bool has_two_bytes = length == 3;
        bool has_no_bytes = !(has_one_byte || has_two_bytes);
        if (has_one_byte) {
            byte_little = op[1];
            if (has_two_bytes) {
                byte_big = op[2];
            }
        }

        std::string result;
        const char* op_string{ OP_STRING[*op] };
        //std::cout << op_string;
        if (has_no_bytes) {
            result = OP_STRING[*op];
            return result;
        } else if (has_two_bytes) {
            result = std::vformat(op_string, std::make_format_args(byte_big, byte_little));
        } else if (has_one_byte) {
            result = std::vformat(op_string, std::make_format_args(byte_little));
        }
        return result;

        // auto distance = (op + file_size) - op;
        // if (distance > 2) {
        //     param_little_end = op[1];
        //     param_big_end = op[2];
        // } else if (distance > 1) {
        //     param_little_end = op[1];
        //     param_little_end = -1; //???
        // }
    }
}

