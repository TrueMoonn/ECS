project(ECS_unit_tests)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} 
    sparse_array.cpp
    registry.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    ECS
    GTest::gtest_main
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${ECS_HDR_DIR}
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
