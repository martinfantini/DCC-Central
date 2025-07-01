add_executable(${TEST_LIB_CENTRAL_COMMON}
    # Tests
    TestAccessory.cpp
    TestLoco.cpp
    TestSensor.cpp
    TestTurnout.cpp
)

target_include_directories(${TEST_LIB_CENTRAL_COMMON}
    PRIVATE ${INCLUDE_DIRECTORIES}/Common
)

target_link_libraries(${TEST_LIB_CENTRAL_COMMON} PRIVATE Catch2::Catch2WithMain Boost::multi_index)

catch_discover_tests(${TEST_LIB_CENTRAL_COMMON})

if(CODE_COVERAGE)
    include(CodeCoverage)
    setup_target_for_coverage_gcovr_html(
        NAME Coverage-${TEST_LIB_CENTRAL_COMMON}
        EXECUTABLE ${TEST_LIB_CENTRAL_COMMON})
endif()