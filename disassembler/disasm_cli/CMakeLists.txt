add_executable(disasm_cli)

target_sources(disasm_cli
  PRIVATE
    disasm_cli.cpp
    disasm_test.cpp
)

target_link_libraries(disasm_cli
  PRIVATE
    libdisasm
)

