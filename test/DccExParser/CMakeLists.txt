find_package(Catch2 REQUIRED)

add_executable(${TEST_DCC_EX_PARSER}
    TestDccExBasicParser.cpp
    TestDccExInfoCommands.cpp
    TestDccExLocoCommands.cpp
    TestDccExSensorsCommands.cpp
    TestDccExStatusCommands.cpp
    TestDccExTrackCommands.cpp
)

target_include_directories(${TEST_DCC_EX_PARSER}
    PRIVATE ${INCLUDE_DIRECTORIES}/DccExParser
    PRIVATE ${INCLUDE_DIRECTORIES}/Common )

target_link_libraries(${TEST_DCC_EX_PARSER} PRIVATE Catch2::Catch2WithMain)
target_link_libraries(${TEST_DCC_EX_PARSER} PRIVATE ${LIB_DCC_EX_PARSER})

target_compile_definitions(${TEST_DCC_EX_PARSER} 
    PRIVATE LIB_DCC_EX_VERSION_HI=${LIB_DCC_EX_VERSION_HI}
    PRIVATE LIB_DCC_EX_VERSION_LO=${LIB_DCC_EX_VERSION_LO}
)