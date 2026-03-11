#ifndef DISASM_H
#define DISASM_H

#include <string>

namespace disasm {
    struct test_s {
        std::string name;
        int x;
        int y;
    };

    void say_hello();
    test_s create_test_s(const std::string &given_name);
}

#endif // DISASM_H
