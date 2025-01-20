cmake_minimum_required(VERSION 3.15)

project(DCC-Central)

# Ser environment variables for all modules
set(INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIRECTORIES ${CMAKE_SOURCE_DIR}/src)

set(EXECUTABLE_CENTRAL_NAME DCC-Central)
set(TEST_CENTRAL_NAME TestDCCCentral)

set(LIB_DCC_EX_PARSER libDccExParser)
set(TEST_DCC_EX_PARSER TestDccExParser)

add_subdirectory(src)
add_subdirectory(test)