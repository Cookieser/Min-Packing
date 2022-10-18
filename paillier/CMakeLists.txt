aux_source_directory(. DIR_LIB_SRCS)
 
add_library(paillier ${DIR_LIB_SRCS})


# GMP
find_path(GMP_INCLUDE_DIR NAMES gmp.h)
find_library(GMP_LIBRARIES NAMES gmp libgmp)
find_library(GMPXX_LIBRARIES NAMES gmpxx libgmpxx)

 
target_link_libraries(paillier gmp gmpxx)
