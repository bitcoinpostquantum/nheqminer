set(EXECUTABLE cuda_djezo)

option(ENABLE_CUDA "Enable the cuda build" ON)

# depending on gcc version
# ;-std=c++11 => Ubuntu 14.04 check gcc versions
#set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-std=c++11)

file(GLOB SRC_LIST
    cuda_djezo.cpp
    equi_miner.cu )
file(GLOB HEADERS
    cuda_djezo.hpp
    eqcuda.hpp
    )


set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-D_FORCE_INLINES;--disable-warnings;--ptxas-options=-v;-Xptxas=-dlcm=ca;-Xptxas=-dscm=cs; -O3)


find_package(CUDA REQUIRED)

if(COMPUTE AND (COMPUTE GREATER 0))
        LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_${COMPUTE},code=sm_${COMPUTE})
else(COMPUTE AND (COMPUTE GREATER 0))
        set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-gencode arch=compute_30,code=sm_30;-gencode arch=compute_35,code=sm_35;-gencode arch=compute_50,code=sm_50; -gencode arch=compute_52,code=sm_52; -gencode arch=compute_60,code=sm_60 )
endif(COMPUTE AND (COMPUTE GREATER 0))

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CUDA_INCLUDE_DIRS})
include_directories(..)
CUDA_ADD_LIBRARY(${EXECUTABLE} STATIC ${SRC_LIST} ${HEADERS})

link_directories("/usr/local/cuda/lib")

if(APPLE)
	target_link_libraries(${EXECUTABLE}  ${CUDA_LIBRARIES} /usr/local/cuda/lib/libcudart_static.a /usr/local/cuda/lib/libcuda.dylib)
else()
	target_link_libraries(${EXECUTABLE}  ${CUDA_LIBRARIES} cuda)
endif()	




install( TARGETS ${EXECUTABLE} RUNTIME DESTINATION bin ARCHIVE DESTINATION lib LIBRARY DESTINATION lib )
install( FILES ${HEADERS} DESTINATION include/${EXECUTABLE} )
