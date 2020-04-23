cmake_minimum_required (VERSION 2.8)
project(test)

enable_testing()
add_test(test1 demo 2 3)
set_tests_properties(test1 PROPERTIES PASS_REGULAR_EXPRESSION " is 5")

add_test(test2 demo 4 3)
set_tests_properties(test2 PROPERTIES PASS_REGULAR_EXPRESSION " is 7")

add_test(test3 demo 2 3)
set_tests_properties(test3 PROPERTIES PASS_REGULAR_EXPRESSION "is 7")

add_test(test4 demo 2 4)
set_tests_properties(test4 PROPERTIES PASS_REGULAR_EXPRESSION "is 6")


add_executable(demo cmaketest.c)