find_package(pugixml REQUIRED)
find_package(Boost COMPONENTS program_options filesystem system REQUIRED)
find_package(glog REQUIRED)

add_executable(${EXECUTABLE_CENTRAL_NAME} 
    main.cpp
    CommandOptions.cpp
    XmlHelpers.cpp
    Logger.cpp
    Address.cpp
    Configuration.cpp
    Helpers.cpp
    CentralManager.cpp
)

target_include_directories(${EXECUTABLE_CENTRAL_NAME} 
    PRIVATE ${INCLUDE_DIRECTORIES}
    PRIVATE ${INCLUDE_DIRECTORIES}/Central
)

target_compile_definitions(${EXECUTABLE_CENTRAL_NAME} 
    PRIVATE EXECUTABLE_CENTRAL_VERSION_HI=${EXECUTABLE_CENTRAL_VERSION_HI}
    PRIVATE EXECUTABLE_CENTRAL_VERSION_LO=${EXECUTABLE_CENTRAL_VERSION_LO}
)

# Link against library
target_link_libraries(${EXECUTABLE_CENTRAL_NAME} PRIVATE Boost::program_options Boost::filesystem Boost::system)
target_link_libraries(${EXECUTABLE_CENTRAL_NAME} PRIVATE pugixml::shared)
target_link_libraries(${EXECUTABLE_CENTRAL_NAME} PRIVATE glog::glog)
