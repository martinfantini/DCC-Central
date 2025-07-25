add_executable(${TEST_DCC_EX_PARSER}
    TestDccExBasicParser.cpp
    TestDccExInfoCommands.cpp
    TestDccExLocoCommands.cpp
    TestDccExSensorsCommands.cpp
    TestDccExStatusCommands.cpp
    TestDccExTrackCommands.cpp
    TestDccExCommandConverter.cpp
)

target_include_directories(${TEST_DCC_EX_PARSER}
    PRIVATE ${INCLUDE_DIRECTORIES}/DccExParser
    PRIVATE ${INCLUDE_DIRECTORIES}/Common )

target_link_libraries(${TEST_DCC_EX_PARSER} 
    PRIVATE Catch2::Catch2WithMain
    PRIVATE ${LIB_DCC_EX_PARSER}
)

target_compile_definitions(${TEST_DCC_EX_PARSER} 
    PRIVATE LIB_DCC_EX_VERSION_HI=${LIB_DCC_EX_VERSION_HI}
    PRIVATE LIB_DCC_EX_VERSION_LO=${LIB_DCC_EX_VERSION_LO}
)

catch_discover_tests(${TEST_DCC_EX_PARSER})

if(CODE_COVERAGE)
    target_link_libraries(${TEST_DCC_EX_PARSER} PRIVATE gcov)
    include(CodeCoverage)
    setup_target_for_coverage_gcovr_html(
        NAME Coverage-${TEST_DCC_EX_PARSER}
        EXECUTABLE ${TEST_DCC_EX_PARSER})
endif()