set(lattice_test_srcs supercubic_test.cpp test_all.cpp)

add_executable(latticetest ${lattice_test_srcs})

target_link_libraries(latticetest latticehao)

install(TARGETS latticetest  DESTINATION test)
