cmake_minimum_required(VERSION 3.25)

project(DCC-Central LANGUAGES CXX VERSION 1.0.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(Version)

option(BUILD_TESTING "To generate the unit tests" OFF)

# Ser environment variables for all modules
set(INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIRECTORIES ${CMAKE_SOURCE_DIR}/src)

list(APPEND CMAKE_MESSAGE_CONTEXT "Main")

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

# Information about the lib RestApi
set(LIB_REST_API libRestApi)
generate_version(LIB_REST_API_VERSION LIB_REST_API_VERSION 0.0 0.1)
message("The library " ${LIB_REST_API} " version is " ${LIB_REST_API_VERSION_HI} "." ${LIB_REST_API_VERSION_LO})
set(TEST_LIB_REST_API TestLibRestApi)

# Information about Test common data
set(TEST_LIB_CENTRAL_COMMON TestCentralCommon)

# Information about the lib raspberry
set(LIB_RASPBEERY_DMA libRaspberryDMA)
generate_version(LIB_RASPBEERY_DMA_VERSION LIB_RASPBEERY_DMA_VERSION 0.0 0.1)
message("The library " ${LIB_RASPBEERY_DMA} " version is " ${LIB_RASPBEERY_DMA_VERSION_HI} "." ${LIB_RASPBEERY_DMA_VERSION_LO})

message("System Processor: ${CMAKE_SYSTEM_PROCESSOR}")
message("Os Name: ${CMAKE_SYSTEM_NAME}")
message("System Version: ${CMAKE_SYSTEM_VERSION}")

add_subdirectory(externals/pugixml)
add_subdirectory(externals/glog)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(externals/Catch2)
    add_subdirectory(test)

    if(CODE_COVERAGE)
        include(CodeCoverage)
        append_coverage_compiler_flags()

        # we need to turn off optimization for non-skewed coverage reports
        set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    endif()
endif()

add_subdirectory(src)

