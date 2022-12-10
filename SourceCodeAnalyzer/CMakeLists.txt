CMAKE_MINIMUM_REQUIRED(VERSION 3.20 FATAL_ERROR)

PROJECT(SourceCodeAnalyser
        VERSION 2.0
        HOMEPAGE_URL https://github.com/AarnoldGad/LooseProjects.git
        LANGUAGES C CXX
        )

SET(CMAKE_CONFIGURATION_TYPES Debug Release)

SET(SourceCodeAnalyzer_VERSION_MAJOR 2)
SET(SourceCodeAnalyzer_VERSION_MINOR 0)

STRING(TIMESTAMP SourceCodeAnalyzer_BUILD_DAY "%d")
STRING(TIMESTAMP SourceCodeAnalyzer_BUILD_MONTH "%m")
STRING(TIMESTAMP SourceCodeAnalyzer_BUILD_YEAR "%Y")
STRING(TIMESTAMP SourceCodeAnalyzer_BUILD_DATE "%d %b %Y")

MESSAGE(STATUS "Configuring ${PROJECT_NAME} version ${PROJECT_VERSION} on ${SourceCodeAnalyzer_BUILD_DATE}...")

FIND_PACKAGE(Threads REQUIRED)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

SET(CMAKE_DEBUG_POSTFIX -d)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

CONFIGURE_FILE(config.hpp.in scaconfig.hpp @ONLY NEWLINE_STYLE LF)

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
               ${HPP_DIR}/ProgramArguments/ArgumentDescriptor.hpp
               ${HPP_DIR}/ProgramArguments/ArgumentDescriptor.inl
               ${HPP_DIR}/ProgramArguments/ArgumentDictionary.hpp
               ${HPP_DIR}/ProgramArguments/ArgumentDictionary.inl
               ${HPP_DIR}/ProgramArguments/ArgumentParser.hpp
               ${HPP_DIR}/ProgramArguments/ArgumentParser.inl
               ${HPP_DIR}/ProgramArguments/ProgramArguments.hpp
               ${HPP_DIR}/ProgramArguments/ProgramArguments.inl

               ${CPP_DIR}/ProgramArguments/ArgumentDescriptor.cpp
               ${CPP_DIR}/ProgramArguments/ArgumentDictionary.cpp
               ${CPP_DIR}/ProgramArguments/ArgumentParser.cpp
               ${CPP_DIR}/ProgramArguments/ProgramArguments.cpp

               ${CPP_DIR}/main.cpp
               )

TARGET_LINK_DIRECTORIES(scanalyzer PRIVATE
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/lib>
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/lib>
                        )

TARGET_LINK_DIRECTORIES(scanalyzer PRIVATE
                        Threads::Threads
                        ${CMAKE_DL_LIBS}
                        )
