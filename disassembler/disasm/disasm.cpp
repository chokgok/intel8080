#include <disasm.h>

#include <cstddef>
#include <iostream>
#include <string>

namespace {
    struct hidden_struct_s {
        std::size_t id;
        double x;
        double y;
    };
}

namespace disasm {
    void say_hello()
    {
        std::cout << "Hello!" << std::endl;
    }

    test_s create_test_s(const std::string &given_name)
    {
        int x = 0;
        int y = 0;
        return test_s{given_name, x, y};
    }
}

