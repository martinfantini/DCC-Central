
add_library(${LIB_DCC_EX_PARSER}
    DccExBasicParser.cpp
    DccExCommandConverter.cpp
    Helpers.cpp
    InfoInterface.cpp
)

target_include_directories(${LIB_DCC_EX_PARSER} 
    PRIVATE ${INCLUDE_DIRECTORIES}/DccExParser
    PRIVATE ${INCLUDE_DIRECTORIES}/Common
)

target_compile_definitions(${LIB_DCC_EX_PARSER} 
    PRIVATE LIB_DCC_EX_VERSION_HI=${LIB_DCC_EX_VERSION_HI}
    PRIVATE LIB_DCC_EX_VERSION_LO=${LIB_DCC_EX_VERSION_LO}
)