add_subdirectory(Central)
add_subdirectory(DccExParser)
add_subdirectory(DccProtocol)

if((${CMAKE_SYSTEM_NAME} STREQUAL "Linux") AND (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch64"))
    add_subdirectory(RaspberryDMA)
endif()