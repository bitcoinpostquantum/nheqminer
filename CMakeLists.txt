
cmake_minimum_required(VERSION 3.5)

project(nheqminer)

if (MSVC10)
    GET_FILENAME_COMPONENT(VS_DIR [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\10.0\\Setup\\VS;ProductDir] REALPATH CACHE)
elseif (MSVC90)
    GET_FILENAME_COMPONENT(VS_DIR [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\9.0\\Setup\\VS;ProductDir] REALPATH CACHE)
elseif (MSVC80)
    GET_FILENAME_COMPONENT(VS_DIR [HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0\\Setup\\VS;ProductDir] REALPATH CACHE)
endif()

if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.0)
    message(FATAL "Need gcc 5 and later")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fvisibility=hidden -fvisibility-inlines-hidden") #  -Wall

## Enable solvers here
#### older slower
option(USE_CPU_TROMP "USE CPU_TROMP" OFF)
option(USE_CUDA_TROMP "USE CUDA_TROMP" ON)
#### faster
option(USE_CPU_XENONCAT "USE CPU_XENONCAT" OFF)
option(USE_CUDA_DJEZO "USE CUDA_DJEZO" OFF)
####
option(USE_SILENTARMY "USE SILENTARMY" OFF)

message(STATUS "cpu_tromp: ${USE_CPU_TROMP}")
message(STATUS "cuda_tromp: ${USE_CUDA_TROMP}")
message(STATUS "USE_CPU_XENONCAT: ${USE_CPU_XENONCAT}")
message(STATUS "USE_CUDA_DJEZO: ${USE_CUDA_DJEZO}")
message(STATUS "USE_SILENTARMY: ${USE_SILENTARMY}")

set(WN 96 CACHE STRING "Equihash param N")
set(WK 3 CACHE STRING "Equihash param K")
add_definitions(-DWN=${WN} -DWK=${WK})
set(equihash "EQUIHASH: N = ${WN} K = ${WK}")

set(RESTBITS "" CACHE STRING "Equihash param RESTBITS")
if(${RESTBITS})
    add_definitions(-DRESTBITS=${RESTBITS})
    set(equihash "${equihash} RESTBITS:${RESTBITS}")
endif()    
message(STATUS ${equihash})


## Add solvers here
if (USE_CPU_TROMP)
    add_definitions(-DUSE_CPU_TROMP)
endif()
if (USE_CPU_XENONCAT)
    add_definitions(-DUSE_CPU_XENONCAT)
endif()
if (USE_CUDA_TROMP)
    add_definitions(-DUSE_CUDA_TROMP)
endif()
if (USE_CUDA_DJEZO)
    add_definitions(-DUSE_CUDA_DJEZO)
endif()

if (USE_SILENTARMY)
    add_definitions(-DUSE_SILENTARMY)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ocl_device_utils)
    find_package(OpenCL REQUIRED)
    #message(STATUS ${OpenCL_LIBRARIES})
    include_directories(${OpenCL_INCLUDE_DIR})
    #link_directories(${OpenCL_LIBRARY})
endif()


########
# LINUX
if(CMAKE_COMPILER_IS_GNUCXX)
#    # use native cpu features
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -fPIC")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -fPIC")

#    # optimizations
#    add_definitions(-O3)

    # use
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64 -msse2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -msse2")
    # optimizations
    add_definitions(-O2)
endif()

# Common
include_directories(${nheqminer_SOURCE_DIR}/nheqminer)

# BOOST
#find_package(Threads REQUIRED COMPONENTS)
# compile boost staticaly
set(Boost_USE_STATIC_LIBS ON)
#set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#set(BUILD_SHARED_LIBRARIES OFF)
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
find_package(Boost REQUIRED COMPONENTS system log_setup log date_time filesystem thread)

if (Boost_FOUND)
  # From the offical documentation:
  # Add include directories to the build. [...] If the SYSTEM option is given,
  # the compiler will be told the directories are meant as system include
  # directories on some platforms (signalling this setting might achieve effects
  # such as the compiler skipping warnings [...])."
  include_directories (SYSTEM ${Boost_INCLUDE_DIR})

  # From the offical documentation:
  # "Specify directories in which the linker will look for libraries. [...] Note
  # that this command is rarely necessary. Library locations returned by
  # find_package() and find_library() are absolute paths. Pass these absolute
  # library file paths directly to the target_link_libraries() command. CMake
  # will ensure the linker finds them."
  link_directories (${Boost_LIBRARY_DIRS})
else()
    message("Boost_FOUND NOT FOUND")
endif ()

include_directories(${CMAKE_CURRENT_BINARY_DIR}/../)

set(SOURCE_FILES
    # sources
    nheqminer/amount.cpp
    nheqminer/api.cpp
    nheqminer/arith_uint256.cpp
    nheqminer/crypto/sha256.cpp
    nheqminer/json/json_spirit_reader.cpp
    nheqminer/json/json_spirit_value.cpp
    nheqminer/json/json_spirit_writer.cpp
    nheqminer/libstratum/ZcashStratum.cpp
    nheqminer/main.cpp
    nheqminer/primitives/block.cpp
    nheqminer/speed.cpp
    nheqminer/uint256.cpp
    nheqminer/utilstrencodings.cpp
    # headers
    nheqminer/amount.h
    nheqminer/api.hpp
    nheqminer/arith_uint256.h
    nheqminer/crypto/sha256.h
    nheqminer/hash.h
    nheqminer/json/json_spirit.h
    nheqminer/json/json_spirit_error_position.h
    nheqminer/json/json_spirit_reader.h
    nheqminer/json/json_spirit_reader_template.h
    nheqminer/json/json_spirit_stream_reader.h
    nheqminer/json/json_spirit_utils.h
    nheqminer/json/json_spirit_value.h
    nheqminer/json/json_spirit_writer.h
    nheqminer/json/json_spirit_writer_template.h
    nheqminer/libstratum/StratumClient.cpp
    nheqminer/libstratum/StratumClient.h
    nheqminer/libstratum/ZcashStratum.cpp
    nheqminer/libstratum/ZcashStratum.h
    nheqminer/primitives/block.h
    nheqminer/primitives/transaction.h
    nheqminer/script/script.h
    nheqminer/serialize.h
    nheqminer/speed.hpp
    nheqminer/streams.h
    nheqminer/support/allocators/zeroafterfree.h
    nheqminer/tinyformat.h
    nheqminer/uint252.h
    nheqminer/uint256.h
    nheqminer/utilstrencodings.h
    nheqminer/version.h
    nheqminer/zcash/JoinSplit.hpp
    nheqminer/zcash/NoteEncryption.hpp
    nheqminer/zcash/Proof.hpp
    nheqminer/zcash/Zcash.h
    nheqminer/SolverStub.h # just a stub

    nheqminer/AvailableSolvers.h
    nheqminer/ISolver.h
    nheqminer/Solver.h
    nheqminer/MinerFactory.h
    nheqminer/MinerFactory.cpp

    # make same path on windows
    #blake shared
    # src
    blake2/blake2bx.cpp
    # headers
    blake2/blake2.h
    blake2/blake2b-load-sse2.h
    blake2/blake2b-load-sse41.h
    blake2/blake2b-round.h
    blake2/blake2-config.h
    blake2/blake2-impl.h
    blake2/blake2-round.h
    )

set(LIBS ${LIBS} ${Boost_LIBRARIES})

if (USE_CPU_TROMP)
    add_subdirectory(cpu_tromp)
endif()
if (USE_CPU_XENONCAT)
    add_subdirectory(cpu_xenoncat)
endif()
if (USE_CUDA_TROMP)
    add_subdirectory(cuda_tromp)
endif()
if (USE_CUDA_DJEZO)
    add_subdirectory(cuda_djezo)
endif()
if (USE_SILENTARMY)
    add_subdirectory(ocl_device_utils)
    add_subdirectory(ocl_silentarmy)
    set(LIBS ${LIBS} ocl_device_utils ocl_silentarmy ${OpenCL_LIBRARIES})    
endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${LIBS})

# link libs
if (USE_CPU_TROMP)
    target_link_libraries(${PROJECT_NAME} cpu_tromp)
endif()
if (USE_CPU_XENONCAT)
    add_library(xenoncat_avx1 SHARED IMPORTED GLOBAL)
    if (APPLE)
        set_target_properties(xenoncat_avx1 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/cpu_xenoncat/asm_mac/equihash_avx1.o)
    else()
        set_target_properties(xenoncat_avx1 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/cpu_xenoncat/asm_linux/equihash_avx1.o)
    endif(APPLE)
    add_library(xenoncat_avx2 SHARED IMPORTED GLOBAL)
    if (APPLE)
        set_target_properties(xenoncat_avx2 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/cpu_xenoncat/asm_mac/equihash_avx2.o)
    else()
        set_target_properties(xenoncat_avx2 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/cpu_xenoncat/asm_linux/equihash_avx2.o)
    endif(APPLE)
    target_link_libraries(${PROJECT_NAME} cpu_xenoncat xenoncat_avx1 xenoncat_avx2)
endif()
if (USE_CUDA_TROMP)
    target_link_libraries(${PROJECT_NAME} cuda_tromp)
endif()
if (USE_CUDA_DJEZO)
    target_link_libraries(${PROJECT_NAME} cuda_djezo)
endif()

target_link_libraries(${PROJECT_NAME} ${LIBS})




