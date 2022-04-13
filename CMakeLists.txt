cmake_minimum_required(VERSION 3.5)

project(ascii_counter C)

set(CMAKE_C_STANDARD 99)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

    set(LIB_SRC
        ${SRC_DIR}/ascii_counter.c)

    add_library(ascii_counter STATIC ${LIB_SRC} ${SRC_DIR})
    target_include_directories(ascii_counter
        PRIVATE
        "$SRC_DIR"
        "${SRC_DIR}/include"
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
    set_target_properties(ascii_counter PROPERTIES OUTPUT_NAME ascii_counter)

    option(BUILD_TESTING "Build and run tests" ON)
    if (${BUILD_TESTING})
        enable_testing()
        add_subdirectory(tests)
        endif()