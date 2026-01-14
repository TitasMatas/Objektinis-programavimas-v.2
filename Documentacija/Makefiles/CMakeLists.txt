cmake_minimum_required(VERSION 3.16)
project(StudentuPazymiuSistema LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Warnings
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- Main program sources ---
set(SOURCES
    main.cpp
    v.pradine.cpp
    vector.cpp
    student.cpp
)

add_executable(programa ${SOURCES})

# --- Unit tests (optional bonus) ---
# If you have doctest.h in Tests/ and tests.cpp in Tests/
add_executable(unit_tests
    Tests/tests.cpp
    student.cpp
    vector.cpp
)
target_include_directories(unit_tests PRIVATE Tests)

# Install rule (optional)
install(TARGETS programa RUNTIME DESTINATION bin)
