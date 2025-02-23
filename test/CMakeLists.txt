include(CTest)
include(Catch)

add_subdirectory(Central)
add_subdirectory(DccExParser)
add_subdirectory(DccProtocol)
add_subdirectory(Common)
add_subdirectory(RestApi)

if((${CMAKE_SYSTEM_NAME} STREQUAL "Linux") AND (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch64"))
    add_subdirectory(RaspberryDMA)
endif()
