#add_definitions(-DHIST)
#add_definitions(-DXINTREE)
#add_definitions(-DUNROLL)

#compute_20 -arch sm_35
find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})

#if(COMPUTE AND (COMPUTE GREATER 0))
#        LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_${COMPUTE},code=sm_${COMPUTE})
#else(COMPUTE AND (COMPUTE GREATER 0))
        #set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};; -gencode arch=compute_35,code=sm_35; -gencode arch=compute_35,code=sm_35; -gencode arch=compute_50,code=sm_50; -gencode arch=compute_52,code=sm_52; -gencode arch=compute_61,code=sm_61 )
#endif(COMPUTE AND (COMPUTE GREATER 0))

set(SRC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system log_setup log date_time filesystem thread)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CUDA_INCLUDE_DIRS})
include_directories(..)

cuda_add_library(cuda_tromp STATIC  ${SRC}/cuda_tromp.cpp
									${SRC}/equi_miner.cu
									)
target_link_libraries(cuda_tromp ${CUDA_LIBRARIES})

cuda_add_executable(eqcuda 	${SRC}/equi_miner.cu 
						 	${SRC}/../cpu_tromp/blake/blake2b.cpp
						 	OPTIONS -DCUDA_DEBUG)
target_link_libraries(eqcuda ${CUDA_LIBRARIES})
