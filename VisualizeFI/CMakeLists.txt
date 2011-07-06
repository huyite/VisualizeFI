cmake_minimum_required(VERSION 2.8)

# Look for FindTulip.cmake into the tulip source directory. This will provide macros for Qt files and some other Tulip-related variables
FIND_PACKAGE(TULIP3 REQUIRED)
# Look for FindQt4.cmake to get variables about Qt libraries location.
FIND_PACKAGE(Qt4  REQUIRED)
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${TULIP_INCLUDE_DIR} ${QT_INCLUDE_DIR}  ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})	

STRING(REGEX REPLACE ".*/" "" PLUGIN_NAME ${CMAKE_CURRENT_SOURCE_DIR})
STRING(TOLOWER ${PLUGIN_NAME} PLUGIN_NAME) 

# Declare plugin sources files (as .cpp files)
SET(LIB_SRCS
 FrequentItemSet.cpp
 Item.cpp
 ItemSet.cpp
 VisualizeFI.cpp
 ViewItemSet.cpp
 )

# Declare designer files (as .ui files)
SET(LIB_UI
)

# Declare QObject headers (as .h files)
SET(LIB_MOC
ViewItemSet.h
)

# Declare resources files (as .qrc files)
SET(LIB_RCC
)

# Run uic
TULIP_QT4_WRAP_UI(LIB_UI_SRCS ${LIB_UI})
# Run moc
TULIP_QT4_WRAP_CPP(LIB_MOC_SRCS ${LIB_MOC})
# Run rcc
QT4_ADD_RESOURCES(LIB_RCC_SRCS ${LIB_RCC})

ADD_LIBRARY(${PLUGIN_NAME}-${TULIP_PLUGIN_VERSION} SHARED ${LIB_SRCS} ${LIB_UI_SRCS} ${LIB_MOC_SRCS} ${LIB_RCC_SRCS})
TARGET_LINK_LIBRARIES(${PLUGIN_NAME}-${TULIP_PLUGIN_VERSION} ${TULIP_LIBRARY} ${TULIP_LIBRARY} ${TULIP_OGL_LIBRARY} ${TULIP_QT4_LIBRARY} ${QT_LIBRARIES})

INSTALL(TARGETS ${PLUGIN_NAME}-${TULIP_PLUGIN_VERSION} DESTINATION ${TULIP_PLUGINS_PATH})
