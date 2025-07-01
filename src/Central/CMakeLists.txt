find_package(Boost COMPONENTS program_options filesystem system REQUIRED)

add_executable(${EXECUTABLE_CENTRAL_NAME} 
    main.cpp
    Configuration/XmlHelpers.cpp
    Configuration/Configuration.cpp
    Helpers/Address.cpp
    Helpers/CommandOptions.cpp
    Helpers/Helpers.cpp
    Helpers/Logger.cpp
    Manager/AccessoryManager.cpp
    Manager/DccTrackManager.cpp
    Manager/InfoManager.cpp
    Manager/SensorsManager.cpp
    Manager/TrackManager.cpp
    Manager/TurnoutManager.cpp
    RestApi/RestService.cpp
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
target_link_libraries(${EXECUTABLE_CENTRAL_NAME}
    PRIVATE Boost::program_options Boost::filesystem Boost::system
    PRIVATE pugixml::pugixml
    PRIVATE glog::glog
    PRIVATE ${LIB_REST_API}
    PRIVATE ${LIB_DCC_PROTOCOL}
    PRIVATE ${LIB_DCC_EX_PARSER}
)
