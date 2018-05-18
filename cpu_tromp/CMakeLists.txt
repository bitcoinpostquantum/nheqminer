set(module cpu_tromp)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/cpu_tromp.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/cpu_tromp.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/equi.h
		${CMAKE_CURRENT_SOURCE_DIR}/equi_miner.h
	)

add_library(${module} STATIC ${SRC})

