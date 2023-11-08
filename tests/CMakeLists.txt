
cmake_minimum_required (VERSION 3.8)

file(GLOB SOURCES "*.cpp")
set(TEST_APP tests)

set(AGENT_TESTS_ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_executable(${TEST_APP} ${SOURCES} "TestUtils.h")

target_include_directories(${TEST_APP} PRIVATE 
    ${CATCH2_INCLUDE_DIR}
    ${CHAIN_OF_RESPONSIBILITY_INCLUDE_PATH})

target_link_libraries(${TEST_APP}
    Catch2
    Catch2WithMain)
