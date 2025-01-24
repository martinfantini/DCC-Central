cmake_minimum_required(VERSION 3.25)

project(DCC-Central LANGUAGES CXX)

# Ser environment variables for all modules
set(INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIRECTORIES ${CMAKE_SOURCE_DIR}/src)

set(EXECUTABLE_CENTRAL_NAME DCC-Central)
set(TEST_CENTRAL_NAME TestDCCCentral)

# Information about the lib DCC Parser
set(LIB_DCC_EX_PARSER libDccExParser)
set(TEST_DCC_EX_PARSER TestDccExParser)

if(DEFINED ENV{DCC_Protocol_Version_1})
    set(DCC_PROTOCOL_VERSION_1 "$ENV{DCC_Protocol_Version_1}")
else()
    set(DCC_PROTOCOL_VERSION_1 "0")
endif()

if(DEFINED ENV{DCC_Protocol_Version_2})
    set(DCC_PROTOCOL_VERSION_2 "$ENV{DCC_Protocol_Version_2}")
else()
    set(DCC_PROTOCOL_VERSION_2 "0")
endif()

if(DEFINED ENV{DCC_Protocol_Version_3})
    set(DCC_PROTOCOL_VERSION_3 "$ENV{DCC_Protocol_Version_3}")
else()
    set(DCC_PROTOCOL_VERSION_3 "0")
endif()

if(DEFINED ENV{DCC_Protocol_Version_4})
    set(DCC_PROTOCOL_VERSION_4 "$ENV{DCC_Protocol_Version_4}")
else()
    set(DCC_PROTOCOL_VERSION_4 "1")
endif()

add_subdirectory(src)
add_subdirectory(test)
