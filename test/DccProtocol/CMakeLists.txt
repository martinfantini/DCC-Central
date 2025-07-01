add_executable(${TEST_LIB_DCC_PROTOCOL}
    # Tests
    TestDccCommandGenerator.cpp
    TestDccProgrammingGenerator.cpp
)

target_compile_definitions(${TEST_LIB_DCC_PROTOCOL} 
    PRIVATE LIB_DCC_PROTOCOL_VERSION_HI=${LIB_DCC_PROTOCOL_VERSION_HI}
    PRIVATE LIB_DCC_PROTOCOL_VERSION_LO=${LIB_DCC_PROTOCOL_VERSION_LO}
    PRIVATE UNIT_TEST_PRIVATE_METHODS
)

target_include_directories(${TEST_LIB_DCC_PROTOCOL} PRIVATE ${INCLUDE_DIRECTORIES}/DccProtocol)

target_link_libraries(${TEST_LIB_DCC_PROTOCOL} 
    PRIVATE Catch2::Catch2WithMain
    PRIVATE ${LIB_DCC_PROTOCOL}
)

catch_discover_tests(${TEST_LIB_DCC_PROTOCOL})

if(CODE_COVERAGE)
    include(CodeCoverage)
    setup_target_for_coverage_gcovr_html(
        NAME Coverage-${TEST_LIB_DCC_PROTOCOL}
        EXECUTABLE ${TEST_LIB_DCC_PROTOCOL})
endif()