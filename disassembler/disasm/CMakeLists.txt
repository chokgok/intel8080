add_library(libdisasm)

target_sources(libdisasm
  PRIVATE
    disasm.cpp
  PUBLIC
    FILE_SET HEADERS
    FILES
      disasm.h
)

