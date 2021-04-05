cmake_minimum_required(VERSION 3.10)
project(tictactoe)

# File vars
set(SOURCE_FILES Engine.cpp Minimax.cpp TicTacToe.cpp HumanPlayer.cpp EnginePlayer.cpp TicTacToeMove.cpp TicTacToeState.cpp)
set(HEADER_FILES Engine.hpp Game.hpp GameState.hpp Move.hpp Minimax.hpp Player.hpp HumanPlayer.hpp EnginePlayer.hpp TicTacToe.hpp TicTacToeState.hpp TicTacToeMove.hpp)
add_library(Engine ${SOURCE_FILES} ${HEADER_FILES})

# Executables
add_executable(tictactoe main.cpp)
add_executable(minimax_worker minimax_worker.cpp)

# Set to CXX17
set_property(TARGET tictactoe PROPERTY CXX_STANDARD 17)
set_property(TARGET minimax_worker PROPERTY CXX_STANDARD 17)

# Enable compiler-specific options
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(tictactoe PRIVATE /W4 /permissive-)
    target_compile_options(minimax_worker PRIVATE /W4 /permissive-)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(tictactoe PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(minimax_worker PRIVATE -Wall -Wextra -pedantic)
endif()

# Auto-format
find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    message("FORMATTED")
    unset(SOURCE_FILES_PATHS)
    foreach(SOURCE_FILE ${HEADER_FILES} ${SOURCE_FILES} main.cpp)
        get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
        set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
    endforeach()

    add_custom_target(
            ClangFormat
            COMMAND ${CLANG_FORMAT}
            -i
            -style=file
            ${SOURCE_FILES_PATHS})

    add_dependencies(tictactoe ClangFormat)
    add_dependencies(tictactoe minimax_worker)
    add_dependencies(minimax_worker ClangFormat)

else()
    message("NO FORMAT")
endif()

target_link_libraries(minimax_worker Minimax)
target_link_libraries(tictactoe Minimax)

# https://docs.microsoft.com/en-us/cpp/build/manage-libraries-with-vcpkg?view=msvc-160&tabs=windows
# Need to figure out how to do this outside of vcpkg
find_package(Boost REQUIRED mpi serialization)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(tictactoe ${Boost_LIBRARIES})
target_link_libraries(minimax_worker ${Boost_LIBRARIES})

find_package(MPI REQUIRED)
include_directories(${MPI_CXX_INCLUDE_PATH})
target_link_libraries(tictactoe ${MPI_CXX_LIBRARIES})
target_link_libraries(minimax_worker ${MPI_CXX_LIBRARIES})
