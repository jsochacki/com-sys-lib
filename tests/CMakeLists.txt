project(com-sys-lib-test)
# main.cpp is the main.cpp in this directory
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
                      PRIVATE
                         GSL::gsl
                         GSL::gslcblas
                         com-sys-lib::com-sys-lib)

add_test(${PROJECT_NAME} com-sys-lib)
