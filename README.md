# Intel 8080 Emulator + Disassembler

To build:

1. `cd` into this repository on your computer.
    Example: `cd ~/intel8080`
2. `cmake -B build` to setup `build/` directory.
3. `cmake --build build` to actually build the thing.
4. (optional) `cmake --build build --config [Debug|Release|RelWithDebInfo]` for
   different build types.

(TODO: HOWTO install the executables?)

To use `disasm` (disassembler) CLI:
1. `disasm` is located in
   `build/disassembler/disasm_cli/[Debug|Release|RelWithDebInfo]`
2. TODO: fill the rest of this out

