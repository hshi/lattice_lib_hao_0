set(src_lib latticehao)

set(srcs
        ../inc/cluster.h
        ../inc/supercubic.h
        cluster.cpp
        supercubic.cpp
        )

add_library(${src_lib} STATIC ${srcs})

install(TARGETS ${src_lib}  DESTINATION lib)
