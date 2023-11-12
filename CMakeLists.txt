cmake_minimum_required (VERSION 3.8)

project ("chain-of-responsibility")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CHAIN_OF_RESPONSIBILITY_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory("./examples")

set(CATCH2_DIR ${CMAKE_CURRENT_LIST_DIR}/submodules/Catch2)
set(CATCH2_INCLUDE_DIR ${CATCH2_DIR}/include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_subdirectory(${CATCH2_DIR})
    add_subdirectory("./tests")
endif()
