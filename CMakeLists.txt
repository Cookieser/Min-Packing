cmake_minimum_required(VERSION 3.0.0)
project(Coding)


enable_testing()

add_subdirectory(coding) #add sub directory
add_subdirectory(paillier) #add sub directory
file(COPY data.txt DESTINATION ${PROJECT_BINARY_DIR})
file(COPY m1.txt DESTINATION ${PROJECT_BINARY_DIR})
add_executable(main main.cpp)




# GMP
find_path(GMP_INCLUDE_DIR NAMES gmp.h)
find_library(GMP_LIBRARIES NAMES gmp libgmp)
find_library(GMPXX_LIBRARIES NAMES gmpxx libgmpxx)

 

target_link_libraries(main gmp gmpxx coding paillier)








 

