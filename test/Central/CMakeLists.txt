add_executable(${TEST_EXECUTABLE_CENTRAL_NAME}
    ${SRC_DIRECTORIES}/Central/Configuration/XmlHelpers.cpp
    ${SRC_DIRECTORIES}/Central/Configuration/Configuration.cpp
    ${SRC_DIRECTORIES}/Central/Helpers/Helpers.cpp
    ${SRC_DIRECTORIES}/Central/Helpers/Address.cpp
    # Tests
    TestConfiguration.cpp
    TestXmlHelpers.cpp
)

target_compile_definitions(${TEST_EXECUTABLE_CENTRAL_NAME} 
    PRIVATE EXECUTABLE_CENTRAL_VERSION_HI=${EXECUTABLE_CENTRAL_VERSION_HI}
    PRIVATE EXECUTABLE_CENTRAL_VERSION_LO=${EXECUTABLE_CENTRAL_VERSION_LO}
)

target_include_directories(${TEST_EXECUTABLE_CENTRAL_NAME}
    PRIVATE ${INCLUDE_DIRECTORIES}/Central
    PRIVATE ${INCLUDE_DIRECTORIES}/Common
)

target_link_libraries(${TEST_EXECUTABLE_CENTRAL_NAME} 
    PRIVATE Catch2::Catch2WithMain
    PRIVATE pugixml::pugixml
)

catch_discover_tests(${TEST_EXECUTABLE_CENTRAL_NAME})

if(CODE_COVERAGE)
    include(CodeCoverage)
    setup_target_for_coverage_gcovr_html(
        NAME Coverage-${TEST_EXECUTABLE_CENTRAL_NAME}
        EXECUTABLE ${TEST_EXECUTABLE_CENTRAL_NAME})
endif()