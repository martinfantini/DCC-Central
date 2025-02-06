find_package(pugixml REQUIRED)
find_package(Catch2 REQUIRED)

add_executable(${TEST_LIB_DCC_PROTOCOL}
    ${SRC_DIRECTORIES}/DccProtocol/DccCommandGenerator.cpp
    # Tests
    TestDccCommandGenerator.cpp
)

target_compile_definitions(${TEST_LIB_DCC_PROTOCOL} 
    PRIVATE LIB_DCC_PROTOCOL_VERSION_HI=${LIB_DCC_PROTOCOL_VERSION_HI}
    PRIVATE LIB_DCC_PROTOCOL_VERSION_LO=${LIB_DCC_PROTOCOL_VERSION_LO}
    PRIVATE UNIT_TEST_PRIVATE_METHODS
)

target_include_directories(${TEST_LIB_DCC_PROTOCOL} PRIVATE ${INCLUDE_DIRECTORIES}/DccProtocol)

target_link_libraries(${TEST_LIB_DCC_PROTOCOL} PRIVATE Catch2::Catch2WithMain)
