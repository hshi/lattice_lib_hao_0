set(lattice_srcs supercubic.cpp cluster.cpp)

add_library(latticehao STATIC ${lattice_srcs})

install(TARGETS latticehao DESTINATION lib)
