find_package(Catch2 REQUIRED)

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

target_link_libraries(${TEST_LIB_CENTRAL_COMMON} PRIVATE Catch2::Catch2WithMain)

