cmake_minimum_required(VERSION 3.10)
project(ECS)

########## SETUP ##########
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(ECS_SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set(ECS_HDR_DIR "${PROJECT_SOURCE_DIR}/include/")

########## OPTIONS ##########
option(ENABLE_ECS_TESTS "Build tests along with the library" OFF)
option(ENABLE_ECS_COVERAGE "Enable coverage reporting" OFF)

########## TESTING ##########
if(ENABLE_ECS_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    endif()
endif()

if (ENABLE_ECS_TESTS)
  enable_testing()
  add_subdirectory(tests/unit_tests)
endif ()

########## ECS ##########
add_library( ${PROJECT_NAME} STATIC
    ${ECS_SRC_DIR}Registry.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${ECS_HDR_DIR}
)
