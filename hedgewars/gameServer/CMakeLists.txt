cmake_minimum_required(VERSION 3.19)

if(POLICY CMP0177)
  cmake_policy(SET CMP0177 NEW)
endif()

project(hedgewars-server)

find_program(CABAL_EXECUTABLE cabal REQUIRED)

option(BUILD_OFFICIAL_SERVER "Build with official server features" OFF)

set(SERVER_EXECUTABLE_NAME "hedgewars-server${CMAKE_EXECUTABLE_SUFFIX}")
set(SERVER_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/${SERVER_EXECUTABLE_NAME}")
set(CABAL_DIST_DIR "${CMAKE_CURRENT_BINARY_DIR}/cabal-dist")

if(BUILD_OFFLINE)
    list(APPEND CABAL_FLAGS "--offline")
endif()

if(BUILD_OFFICIAL_SERVER)
    list(APPEND CABAL_FLAGS "--flags=officialServer")
else()
    list(APPEND CABAL_FLAGS "--flags=-officialServer")
endif()

message(STATUS "Checking Haskell dependencies with Cabal...")

execute_process(
    COMMAND ${CABAL_EXECUTABLE}
            v2-build
            exe:hedgewars-server
            --only-configure
            --dry-run
            --builddir=${CABAL_DIST_DIR}
            ${CABAL_FLAGS}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RESULT_VARIABLE CABAL_CHECK_EXIT_CODE
    OUTPUT_VARIABLE CABAL_CHECK_OUTPUT
    ERROR_VARIABLE CABAL_CHECK_ERROR
)

message(CHECK_START "Determining resulting binary path...")

execute_process(
    COMMAND ${CABAL_EXECUTABLE}
            list-bin
            exe:hedgewars-server
            --builddir=${CABAL_DIST_DIR}
            ${CABAL_FLAGS}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    OUTPUT_VARIABLE SERVER_BIN_PATH_UNPARSED
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE RESULT
)

if(NOT RESULT EQUAL 0)
    message(CHECK_FAIL "failure")
    message(FATAL_ERROR "Cabal failed to determine path to the binary for hedgewars-server")
else()
    file(TO_CMAKE_PATH "${SERVER_BIN_PATH_UNPARSED}" SERVER_BIN_PATH)
    message(CHECK_PASS ${SERVER_BIN_PATH})
endif()

if(NOT CABAL_CHECK_EXIT_CODE EQUAL 0)
    # Print the error from Cabal so the user knows which package is missing/conflict
    message(WARNING "${CABAL_CHECK_OUTPUT}")
    message(FATAL_ERROR "Cabal dependency check failed! See output above for missing packages or conflicts.\nError details:\n${CABAL_CHECK_ERROR}")
else()
    message(STATUS "Haskell dependencies are valid.")
endif()

set(CABAL_BIN_OUTPUT "${CABAL_DIST_DIR}/build/hedgewars-server${CMAKE_EXECUTABLE_SUFFIX}")

add_custom_target(hedgewars-server ALL
    COMMAND ${CABAL_EXECUTABLE} 
            v2-build
            exe:hedgewars-server
            --builddir=${CABAL_DIST_DIR}
            ${CABAL_FLAGS}

    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "Building hedgewars-server with Cabal..."
    VERBATIM
)

install(PROGRAMS "${SERVER_BIN_PATH}" DESTINATION ${target_binary_install_dir})

