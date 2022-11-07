CMAKE_MINIMUM_REQUIRED(VERSION 3.20 FATAL_ERROR)

PROJECT(SourceCodeAnalyser
        VERSION 2.0
        HOMEPAGE_URL https://github.com/AarnoldGad/LooseProjects.git
        LANGUAGES C CXX
        )

MESSAGE(STATUS "Configuring ${PROJECT_NAME} v${PROJECT_VERSION} ...")

SET(CMAKE_CONFIGURATION_TYPES Debug Release)

FIND_PACKAGE(Threads REQUIRED)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

SET(CMAKE_DEBUG_POSTFIX -d)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Executable

ADD_EXECUTABLE(scanalyzer)

SET_TARGET_PROPERTIES(scanalyzer PROPERTIES
                      OUTPUT_NAME scanalyzer
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON
                      CXX_EXTENSIONS OFF
                      FOLDER "scanalyzer"
                      )

SET(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
SET(HPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/scan")
SET(CPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

TARGET_COMPILE_DEFINITIONS(scanalyzer PRIVATE
                           $<$<CONFIG:Debug>:_DEBUG>
                           $<$<CONFIG:Release>:NDEBUG>
                           )

TARGET_INCLUDE_DIRECTORIES(scanalyzer PUBLIC
                           ${INCLUDE_DIR}
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_BINARY_DIR}"
                           )

TARGET_INCLUDE_DIRECTORIES(scanalyzer SYSTEM PRIVATE
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/include>
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/include>
                           )

                           
TARGET_SOURCES(scanalyzer PRIVATE
               ${HPP_DIR}/arguments.hpp

               ${CPP_DIR}/main.cpp
               ${CPP_DIR}/arguments.cpp
               )

TARGET_LINK_DIRECTORIES(scanalyzer PRIVATE
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/lib>
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/lib>
                        )

TARGET_LINK_DIRECTORIES(scanalyzer PRIVATE
                        Threads::Threads
                        ${CMAKE_DL_LIBS}
                        )
