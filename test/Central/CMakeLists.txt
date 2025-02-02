find_package(pugixml REQUIRED)
find_package(Catch2 REQUIRED)

add_executable(${TEST_EXECUTABLE_CENTRAL_NAME}
    ${SRC_DIRECTORIES}/Central/XmlHelpers.cpp
    ${SRC_DIRECTORIES}/Central/Helpers.cpp
    ${SRC_DIRECTORIES}/Central/Configuration.cpp
    ${SRC_DIRECTORIES}/Central/Address.cpp
    # Tests
    TestConfiguration.cpp
    TestXmlHelpers.cpp
)

target_compile_definitions(${TEST_EXECUTABLE_CENTRAL_NAME} 
    PRIVATE EXECUTABLE_CENTRAL_VERSION_HI=${EXECUTABLE_CENTRAL_VERSION_HI}
    PRIVATE EXECUTABLE_CENTRAL_VERSION_LO=${EXECUTABLE_CENTRAL_VERSION_LO}
)

target_include_directories(${TEST_EXECUTABLE_CENTRAL_NAME} PRIVATE ${INCLUDE_DIRECTORIES}/Central)

target_link_libraries(${TEST_EXECUTABLE_CENTRAL_NAME} PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST_EXECUTABLE_CENTRAL_NAME} PRIVATE pugixml::shared)
