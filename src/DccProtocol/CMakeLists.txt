add_library(${LIB_DCC_PROTOCOL} STATIC
    DccCommandGenerator.cpp
    DccProgrammingCommandGenerator.cpp
)

target_include_directories(${LIB_DCC_PROTOCOL} 
    PRIVATE ${INCLUDE_DIRECTORIES}/DccProtocol
)

target_compile_definitions(${LIB_DCC_PROTOCOL} 
    PRIVATE LIB_DCC_PROTOCOL_VERSION_HI=${LIB_DCC_PROTOCOL_VERSION_HI}
    PRIVATE LIB_DCC_PROTOCOL_VERSION_LO=${LIB_DCC_PROTOCOL_VERSION_LO}
)
