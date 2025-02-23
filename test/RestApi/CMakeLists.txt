find_package(Boost COMPONENTS system json REQUIRED)

add_executable(${TEST_LIB_REST_API}
    Serializers/TestAccessory.cpp
    Serializers/TestLoco.cpp
    Serializers/TestSensor.cpp
    Serializers/TestTurnout.cpp
)

target_include_directories(${TEST_LIB_REST_API} 
    PRIVATE ${INCLUDE_DIRECTORIES}/RestApi
    PRIVATE ${INCLUDE_DIRECTORIES}
)

target_link_libraries(${TEST_LIB_REST_API}
    PRIVATE Catch2::Catch2WithMain
    PRIVATE ${LIB_REST_API}
)


catch_discover_tests(${TEST_LIB_REST_API})

if(CODE_COVERAGE)
    include(CodeCoverage)
    setup_target_for_coverage_gcovr_html(
        NAME Coverage-${TEST_LIB_REST_API}
        EXECUTABLE ${TEST_LIB_REST_API})
endif()
