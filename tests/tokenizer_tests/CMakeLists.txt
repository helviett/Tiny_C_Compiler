include_directories(${gtest_SOURCE_DIRS}/include ${gtest_SOURCE_DIRS} )
add_subdirectory(test_src)
add_executable(run_tokenizer_tests tokenizer_test.cpp ${CMAKE_SOURCE_DIR}/includes/tokenizer.h
        ${CMAKE_SOURCE_DIR}/src/tokenizer.cpp)

target_link_libraries(run_tokenizer_tests gtest gtest_main)

