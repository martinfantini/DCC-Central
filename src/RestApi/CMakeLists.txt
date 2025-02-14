find_package(Boost COMPONENTS system json REQUIRED)

add_library(${LIB_REST_API}
    Serializers/Accessory.cpp
    Serializers/Turnout.cpp
    Serializers/Sensor.cpp
    Serializers/Loco.cpp
    Context.cpp
    Router.cpp
    Server.cpp
)

target_include_directories(${LIB_REST_API} 
    PRIVATE ${INCLUDE_DIRECTORIES}/RestApi
    PRIVATE ${INCLUDE_DIRECTORIES}
)

target_compile_definitions(${LIB_REST_API} 
    PRIVATE LIB_REST_API_VERSION_HI=${LIB_REST_API_VERSION_HI}
    PRIVATE LIB_REST_API_VERSION_HI=${LIB_REST_API_VERSION_HI}
)

# Link against library
target_link_libraries(${LIB_REST_API} PRIVATE Boost::json Boost::system)