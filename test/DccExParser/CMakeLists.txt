find_package(Catch2 REQUIRED)

add_executable(${TEST_DCC_EX_PARSER}
    TestDccExBasicParser.cpp
    TestDccExCommandConverter.cpp
)

target_include_directories(${TEST_DCC_EX_PARSER} PRIVATE ${INCLUDE_DIRECTORIES}/DccExParser)

target_link_libraries(${TEST_DCC_EX_PARSER} PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST_DCC_EX_PARSER} PRIVATE ${LIB_DCC_EX_PARSER})

