set(EXECUTABLE cpu_xenoncat)

#cpu_xenoncat/
file(GLOB SRC_LIST
    xenoncat.cpp )
file(GLOB HEADERS
    cpu_xenoncat.hpp
    )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CUDA_INCLUDE_DIRS})
include_directories(..)
ADD_LIBRARY(${EXECUTABLE} STATIC ${SRC_LIST} ${HEADERS})
TARGET_LINK_LIBRARIES(${EXECUTABLE} )


# for Linux, BSD, Solaris, Minix
if(UNIX AND NOT APPLE)
    add_custom_command(TARGET ${EXECUTABLE} PRE_BUILD
                    COMMAND chmod +x fasm
		            COMMAND ./fasm -m 512000 ../asm_linux/equihash_avx1.asm equihash_avx1.o
                    COMMAND ./fasm -m 512000 ../asm_linux/equihash_avx2.asm equihash_avx2.o
                    COMMENT "-- Compile ASM files"
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/asm_linux 
                    )

elseif(APPLE)
    add_custom_command(TARGET ${EXECUTABLE} PRE_BUILD
                    COMMAND chmod +x fasm
                    COMMAND ./fasm -m 1280000 ../asm_linux/equihash_avx1.asm equihash_avx1.elf.o
                    COMMAND ./fasm -m 1280000 ../asm_linux/equihash_avx2.asm equihash_avx2.elf.o
                    COMMAND chmod +x objconv
                    COMMAND ./objconv -fmacho64 -nu equihash_avx1.elf.o equihash_avx1.o
                    COMMAND ./objconv -fmacho64 -nu equihash_avx2.elf.o equihash_avx2.o
                    COMMENT "-- Compile ASM files"
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/asm_mac
                    )    
endif()


install( TARGETS ${EXECUTABLE} RUNTIME DESTINATION bin ARCHIVE DESTINATION lib LIBRARY DESTINATION lib )
install( FILES ${HEADERS} DESTINATION include/${EXECUTABLE} )
