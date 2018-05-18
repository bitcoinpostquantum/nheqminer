set(EXECUTABLE ocl_silentarmy)

add_library(${EXECUTABLE} STATIC 
			${CMAKE_CURRENT_SOURCE_DIR}/ocl_silentarmy.hpp
			${CMAKE_CURRENT_SOURCE_DIR}/ocl_silentarmy.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/param.h
			${CMAKE_CURRENT_SOURCE_DIR}/sa_blake.h
			${CMAKE_CURRENT_SOURCE_DIR}/sa_blake.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/_kernel.h
			)
