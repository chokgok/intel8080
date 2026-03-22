add_library(i8080)

target_sources(i8080
  PRIVATE
    i8080.cpp
  PUBLIC
    FILE_SET HEADERS
    FILES
      i8080.h
)

