Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

add_subdirectory(Central)
add_subdirectory(DccExParser)
add_subdirectory(DccProtocol)
add_subdirectory(Common)

if((${CMAKE_SYSTEM_NAME} STREQUAL "Linux") AND (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch64"))
    add_subdirectory(RaspberryDMA)
endif()
