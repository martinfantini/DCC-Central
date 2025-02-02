cmake_minimum_required(VERSION 3.25)

project(DCC-Central LANGUAGES CXX VERSION 1.0.0.0)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/version.cmake)

# Ser environment variables for all modules
set(INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIRECTORIES ${CMAKE_SOURCE_DIR}/src)

# Information about the Central Binary
set(EXECUTABLE_CENTRAL_NAME DCC-Central)
set(EXECUTABLE_CENTRAL_NAME DCC-Central)
generate_version(EXECUTABLE_CENTRAL_VERSION EXECUTABLE_CENTRAL_VERSION "0.0" "0.1")
message("The " ${EXECUTABLE_CENTRAL_NAME} " version is " ${EXECUTABLE_CENTRAL_VERSION_HI} "." ${EXECUTABLE_CENTRAL_VERSION_LO})
set(TEST_EXECUTABLE_CENTRAL_NAME TestDCCCentral)

# Information about the lib DCC-Ex Parser
set(LIB_DCC_EX_PARSER libDccExParser)
generate_version(LIB_DCC_EX_VERSION LIB_DCC_EX_VERSION 0.0 0.1)
message("The library " ${LIB_DCC_EX_PARSER} " version is " ${LIB_DCC_EX_VERSION_HI} "." ${LIB_DCC_EX_VERSION_LO})
set(TEST_DCC_EX_PARSER TestDccExParser)

# Information about the lib DCC
set(LIB_DCC_PROTOCOL libDccProtocol)
generate_version(LIB_DCC_PROTOCOL_VERSION LIB_DCC_PROTOCOL_VERSION 0.0 0.1)
message("The library " ${LIB_DCC_PROTOCOL} " version is " ${LIB_DCC_PROTOCOL_VERSION_HI} "." ${LIB_DCC_PROTOCOL_VERSION_LO})
set(TEST_LIB_DCC_PROTOCOL TestLibDccProtocol)

add_subdirectory(src)
add_subdirectory(test)
