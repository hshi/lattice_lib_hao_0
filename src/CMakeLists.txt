set(src_lib latticehao)

file(GLOB srcs "*.cpp")

add_library(${src_lib} STATIC ${srcs})

install(TARGETS ${src_lib}  DESTINATION lib)
