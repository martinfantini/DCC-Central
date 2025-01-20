find_package(pugixml REQUIRED)
find_package(Catch2 REQUIRED)

add_executable(${TEST_CENTRAL_NAME}
    ${SRC_DIRECTORIES}/Central/XmlHelpers.cpp
    ${SRC_DIRECTORIES}/Central/Helpers.cpp
    ${SRC_DIRECTORIES}/Central/Configuration.cpp
    ${SRC_DIRECTORIES}/Central/Address.cpp
    # Tests
    TestConfiguration.cpp
    TestXmlHelpers.cpp
)

target_include_directories(${TEST_CENTRAL_NAME} PRIVATE ${INCLUDE_DIRECTORIES}/Central)

target_link_libraries(${TEST_CENTRAL_NAME} PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST_CENTRAL_NAME} PRIVATE pugixml::shared)
