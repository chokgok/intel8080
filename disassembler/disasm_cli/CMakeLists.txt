add_executable(disasm)

target_sources(disasm
  PRIVATE
    disasm_cli.cpp
)

target_link_libraries(disasm
  PRIVATE
    libdisasm
)

