
cmake_minimum_required(VERSION 3.1)
project(GameSolver)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

add_library(GameSolver SHARED
    ${PROJECT_SOURCE_DIR}/src/Game.cpp
    ${PROJECT_SOURCE_DIR}/src/GameSolver.cpp
)

enable_testing()

add_executable(test_game_solver
    ${PROJECT_SOURCE_DIR}/test/test.cpp
)
target_link_libraries(test_game_solver
    GameSolver
)
add_test(test_game_solver test_game_solver)
