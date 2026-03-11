#include <disasm.h>

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <some string>" << std::endl;
        return 1;
    }

    disasm::say_hello();

    disasm::test_s my_test{ disasm::create_test_s(argv[1]) };
    std::cout << "You entered: \"" << argv[1] << "\"\n";
    for (auto &c : my_test.name) {
        std::cout << c << " ";
    }

    std::cout << "\n\n";

    for (std::size_t i = 0; i < my_test.name.length(); i++) {
        std::cout << i << " " << my_test.name[i] << "\n";
    }

    std::cout << "Thank you for trying out my program!\n";

    std::cout.flush();
    return 0;
}
