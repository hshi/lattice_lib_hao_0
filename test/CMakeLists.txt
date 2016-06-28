set(test_exe latticetest)

file(GLOB test_srcs "*.cpp")

add_executable(${test_exe} ${test_srcs})

target_link_libraries(${test_exe} latticehao)

install(TARGETS ${test_exe}  DESTINATION test)
