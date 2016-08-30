set(test_exe latticetest)

set(test_srcs
        ../inc/cluster.h
        ../inc/supercubic.h
        cluster_test.cpp
        supercubic_test.cpp
        test_all.cpp)

add_executable(${test_exe} ${test_srcs})

target_link_libraries(${test_exe} latticehao)

install(TARGETS ${test_exe}  DESTINATION test)
