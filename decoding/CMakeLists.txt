cmake_minimum_required(VERSION 3.0.0)
project(hello)


enable_testing()


file(COPY data.txt DESTINATION ${PROJECT_BINARY_DIR})
add_executable(decoding decoding.cpp)



# GMP
find_path(GMP_INCLUDE_DIR NAMES gmp.h)
find_library(GMP_LIBRARIES NAMES gmp libgmp)
find_library(GMPXX_LIBRARIES NAMES gmpxx libgmpxx)

target_link_libraries(decoding gmp gmpxx)
