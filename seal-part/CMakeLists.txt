

cmake_minimum_required(VERSION 3.13)


aux_source_directory(. DIR_LIB_SRCS)
 
add_library(seal ${DIR_LIB_SRCS})


# GMP
find_path(GMP_INCLUDE_DIR NAMES gmp.h)
find_library(GMP_LIBRARIES NAMES gmp libgmp)
find_library(GMPXX_LIBRARIES NAMES gmpxx libgmpxx)

# If not called from root CMakeLists.txt
if(NOT DEFINED SEAL_BUILD_EXAMPLES)
    set(SEAL_BUILD_EXAMPLES ON)

    # Import Microsoft SEAL
    find_package(SEAL 4.0.0 EXACT REQUIRED)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()

if(SEAL_BUILD_EXAMPLES)


    if(TARGET SEAL::seal)
        target_link_libraries(seal PRIVATE SEAL::seal gmp gmpxx)
    elseif(TARGET SEAL::seal_shared)
        target_link_libraries(seal PRIVATE SEAL::seal_shared gmp gmpxx)
    else()
        message(FATAL_ERROR "Cannot find target SEAL::seal or SEAL::seal_shared")
    endif()
endif()



