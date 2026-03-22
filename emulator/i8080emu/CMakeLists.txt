add_executable(i8080emu)

target_sources(i8080emu
  PRIVATE
    i8080emu.cpp
)

target_link_libraries(i8080emu
  PRIVATE
    libi8080emu
)

