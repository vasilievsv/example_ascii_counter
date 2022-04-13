set(TESTS
    error_sequence
    good_sequence)

foreach(fname ${TESTS})
    add_executable(test_${fname} test_${fname}.c)
    target_include_directories(test_${fname} PRIVATE "${SRC_DIR}")
    target_link_libraries(test_${fname} ascii_counter)
    add_test(NAME test_${fname} COMMAND $<TARGET_FILE:test_${fname}>)
endforeach()