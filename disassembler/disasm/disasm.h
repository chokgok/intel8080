#ifndef DISASM_H
#define DISASM_H

#include <fstream>

namespace disasm {
    const char* load_binary(const char* path);
    const char* disassemble(const char* code);
    void build_asm();
}

#endif // DISASM_H
