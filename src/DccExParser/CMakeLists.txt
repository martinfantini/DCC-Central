
add_library(${LIB_DCC_EX_PARSER}
    DccExBasicParser.cpp
    DccExCommandConverter.cpp
)

target_include_directories(${LIB_DCC_EX_PARSER} 
    PRIVATE ${INCLUDE_DIRECTORIES}/DccExParser
    PRIVATE ${INCLUDE_DIRECTORIES}
)
