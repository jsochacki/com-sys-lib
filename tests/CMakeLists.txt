project(com_sys_lib_test)
# main.cpp is the main.cpp in this directory
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
                      PRIVATE
                         GSL::gsl
                         GSL::gslcblas
                         lib_src_inc::com_sys_lib)

add_test(${PROJECT_NAME} com_sys_lib)
