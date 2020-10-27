cmake_minimum_required(VERSION 3.10)

project(rpg_game_test)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})

add_executable(google_test_output JsonParser_test.cpp ${PARENT_DIR}/creature.cpp ${PARENT_DIR}/JsonParser.cpp )
target_compile_features(google_test_output PRIVATE cxx_std_17)
target_link_libraries(google_test_output ${GTEST_LIBRARIES} pthread)