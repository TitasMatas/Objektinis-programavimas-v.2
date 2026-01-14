cmake_minimum_required(VERSION 3.16)
project(StudentuPazymiuSistema LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags for different platforms
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(MSVC)
  add_compile_options(/W4)  # For MSVC, enable high warning level
else()
  add_compile_options(-Wall -Wextra -Wpedantic)  # For gcc/clang
endif()

set(SOURCES
    main.cpp
    v.pradine.cpp
    vector.cpp
)

# Create executable
add_executable(programa ${SOURCES})

# Optional: Install rule if desired
install(TARGETS programa RUNTIME DESTINATION bin)
