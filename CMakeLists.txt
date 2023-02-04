# Copyright (c) 2023 Michał Gibas

cmake_minimum_required(VERSION 3.15)
project(tspviz)

### project settings ###

# the C++ standard (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# app executable file name
set(APP_TARGET_NAME tspviz)

# tests executable file name
set(TEST_TARGET_NAME tspviz_test)

# warning level
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

######

### app source files ###
set(APP_SOURCES_PATH src/app/)

set(APP_SOURCES
    main.cpp
    gfx/window.cpp
    app.cpp
)

list(TRANSFORM APP_SOURCES PREPEND ${APP_SOURCES_PATH})

### logging ###
if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

### graphics ###
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

### app build ###
add_executable(
    ${APP_TARGET_NAME} ${APP_SOURCES}
)
target_link_libraries(
    ${APP_TARGET_NAME} PRIVATE spdlog::spdlog ${SDL2_LIBRARIES}
)

### test source files ###
set(TEST_SOURCES_PATH src/tests/)

set(TEST_SOURCES
    main_test.cpp
)

list(TRANSFORM TEST_SOURCES PREPEND ${TEST_SOURCES_PATH})

### tests ###
# fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  ${TEST_TARGET_NAME}
  ${TEST_SOURCES}
)
target_link_libraries(
  ${TEST_TARGET_NAME}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TEST_TARGET_NAME})