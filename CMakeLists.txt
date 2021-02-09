###############################################################################
# CMake version checking and policy
cmake_minimum_required(VERSION 3.7...3.19)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

###############################################################################

###############################################################################

#VERSION SCHEME MAJOR.MINOR.PATCH
#MAJOR is breaking change
#MINOR non breaking additions to the API (backwards compatible)
#PATCH bug fixes only, no API changes at all

set(TOP_NAMESPACE "lib_src_inc")

# Define the project information
project(com_sys_lib
        VERSION 0.0.0
        DESCRIPTION "Wireless Communication Systems Library"
        LANGUAGES CXX)

# Define the package information based on the project information
set(PACKAGE ${PROJECT_NAME})
set(DESCRIPTION ${${PROJECT_NAME}_DESCRIPTION})
set(PACKAGE_NAME ${PACKAGE})
set(PACKAGE_TARNAME ${PACKAGE})
set(PACKAGE_BUGREPORT "")
set(PACKAGE_URL "https://github.com/jsochacki/${PROJECT_NAME}")
set(PACKAGE_VERSION ${${PROJECT_NAME}_VERSION})
set(PACKAGE_STRING "${PACKAGE} ${${PROJECT_NAME}_VERSION}")

# Set the version of GSL required
set(GSL_VERSION_REQUIRED 2.6)

###############################################################################

###############################################################################
# Setup Non Target Options

#TODO NOT SURE IF WE WANT OR NEED THIS
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

# Default to off (opposite of hidden is default)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

# com_sys_lib will build shared this way unless the user sets
# -DBUILD_SHARED_LIBS=OFF and then they will get a static library
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# Need this to fix RPATH so that people can run apps against your library after
# they have compiled against it (you wont have an issue if you don't do this but
# others will)
# NEEDS to be before add_library
#if(APPLE)
#  set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
#elseif(UNIX)
#  set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
#endif()
# New Version
if(NOT APPLE)
  set(CMAKE_INSTALL_RPATH "$ORIGIN")
endif()

###############################################################################

###############################################################################
# Get external libraries we are dependent on

find_package(GSL ${GSL_VERSION_REQUIRED} EXACT
             MODULE
             REQUIRED COMPONENTS ALL)

find_library(MATH_LIBRARY m)

###############################################################################

###############################################################################
# Make variables for all files and paths

# Set build paths
set(build_inc_path "${CMAKE_CURRENT_SOURCE_DIR}/inc")
set(build_src_path "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(build_tests_path "${CMAKE_CURRENT_SOURCE_DIR}/tests")

# Set install paths
set(install_library_path "lib/${PROJECT_NAME}")
set(install_include_path "include/${PROJECT_NAME}/inc")
set(install_include_file_path "include/${PROJECT_NAME}/include_file")

# Set build and Install files
set(build_header_files
      ${build_inc_path}/com_sys_lib_build_settings.h
      ${build_inc_path}/com_sys_lib.h
      ${build_inc_path}/constants.h
      ${build_inc_path}/exceptions.h
      ${build_inc_path}/link_budget.h
      ${build_inc_path}/modem.h
      ${build_inc_path}/parsers.h
      ${build_inc_path}/string_pack.h
      ${build_inc_path}/transceiver.h)

set(install_interface_header_files
      ${install_include_file_path}/DVBS2xplus-codebook.csv
      ${install_include_path}/com_sys_lib_build_settings.h
      ${install_include_path}/com_sys_lib.h
      ${install_include_path}/constants.h
      ${install_include_path}/exceptions.h
      ${install_include_path}/link_budget.h
      ${install_include_path}/modem.h
      ${install_include_path}/parsers.h
      ${install_include_path}/string_pack.h
      ${install_include_path}/transceiver.h)

set(source_files
      ${build_src_path}/constants.cpp
      ${build_src_path}/exceptions.cpp
      ${build_src_path}/link_budget.cpp
      ${build_src_path}/modem.cpp
      ${build_src_path}/parsers.cpp
      ${build_src_path}/transceiver.cpp)

###############################################################################

###############################################################################
# Generate targets
# Make GSL components globally available (If calling from a subdirectory only
# though so we don't need to do that here)
#if(GSL_FOUND)
#   set_target_properties(GSL::gsl
#                         GSL::gslcblas
#                         PROPERTIES IMPORTED_GLOBAL TRUE)
#endif()
add_library(${PROJECT_NAME})

###############################################################################

###############################################################################
# Generated Files section

# Will make com_sys_lib_export.h and define COM_SYS_LIB_EXPORT symbol
# MUST BE AFTER TARGET IS DEFINED ABOVE ( with add_library )

set(EXPORT_HEADER_NAME "${PROJECT_NAME}_build_settings.h")

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
                       BASE_NAME ${EXPORT_HEADER_NAME}
                       EXPORT_MACRO_NAME CSLDECLSPEC
                       EXPORT_FILE_NAME ${build_inc_path}/${EXPORT_HEADER_NAME})

# Need to add the generated export header to the list of headers to use when
# building
#list(APPEND build_header_files
#   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_export.h)
list(APPEND build_header_files
     ${build_inc_path}/${EXPORT_HEADER_NAME})

# Need to add the generated export header to the list of headers to use when
# installed
#list(APPEND install_interface_header_files
#   ${install_include_path}/${PROJECT_NAME}_export.h)
list(APPEND install_interface_header_files
     ${install_include_path}/${EXPORT_HEADER_NAME})

###############################################################################

###############################################################################
# Add all the source files to the library

# Need this so internal code (local code in other directories)
# has the same namespace that code that imports or
# installs this library has (as set in the install( EXPORT ... NAMESPACE )
# and the export( EXPORT ... NAMESPACE ) commands below
# You want this as well as the alias is immutable and cannot have its properties
# changed this way and will let you know if you accidentally try to
add_library(${TOP_NAMESPACE}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
# Directories relative to cmake_current_source_dir prior to 3.13 but now can
# just do relative to project
target_sources(${PROJECT_NAME}
               PUBLIC
                  "$<BUILD_INTERFACE:${build_header_files}>"
                  "$<INSTALL_INTERFACE:${install_interface_header_files}>"
               PRIVATE
                  ${build_header_files}
                  ${source_files})

# Add directories with source code (non header)
if(BUILD_TESTING)
   add_subdirectory(tests)
endif()

###############################################################################

###############################################################################
# Link up the libraries

if(GSL_FOUND)
   message(DEBUG "The following GSL Libraries were found ${GSL_LIBRARIES}")
   target_link_libraries(${PROJECT_NAME}
                         PUBLIC
                           GSL::gsl GSL::gslcblas)
endif()

if(MATH_LIBRARY)
   target_link_libraries(${PROJECT_NAME} PUBLIC ${MATH_LIBRARY})
endif()

###############################################################################

###############################################################################
# Set Target version options

# SOVERSION is for runtime loader lib generates i.e. lib.so.major
# VERSION is for humans and packages i.e. lib.so.major.minor.patch
# Name link is automatically made and is for the build time linker i.e. lib.so
set_target_properties(${PROJECT_NAME} PROPERTIES
                        VERSION ${${PROJECT_NAME}_VERSION}
                        SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR})
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY
             COMPATIBLE_INTERFACE_STRING ${PROJECT_NAME}_MAJOR_VERSION)
set_property(TARGET ${PROJECT_NAME}
             PROPERTY INTERFACE_${PROJECT_NAME}_MAJOR_VERSION ${com_sys_lib_VERSION_MAJOR})

###############################################################################

###############################################################################
# Setup Target Options

# Note that ON will set PIC ON as well by default as it is required anyway but
# ill set it just in case
# state that com_sys_lib need PIC when the default is shared libraries
set_target_properties(${PROJECT_NAME} PROPERTIES
                      POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

target_include_directories(${PROJECT_NAME}
                           PUBLIC
                               "$<BUILD_INTERFACE:${build_inc_path}>"
                               "$<INSTALL_INTERFACE:${install_include_path}>"
                           PRIVATE
                               ${build_inc_path})

# Lets you use the same system header calls you would if the library was
# installed vs local in lib directory 
# But i currently cant get it to play nice when using from another project
# locally so punt for now
if(NOT LOCAL_LIBRARY_BUILD)
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
target_include_directories(${PROJECT_NAME}
                           PRIVATE
                           "${PARENT_DIR}")
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(${PROJECT_NAME} PRIVATE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused;-pedantic>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:/W3>>")

###############################################################################

###############################################################################
# Test section
# enable testing
include(CTest)

# does the application run
add_test(NAME Runs COMMAND ${PROJECT_NAME} 25)

# does the usage message work?
add_test(NAME Usage COMMAND ${PROJECT_NAME})
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

# define a function to simplify adding tests
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction(do_test)

# do a bunch of result based tests
do_test(${PROJECT_NAME} 4 "4 is 2")
do_test(${PROJECT_NAME} 9 "9 is 3")
do_test(${PROJECT_NAME} 5 "5 is 2.236")
do_test(${PROJECT_NAME} 7 "7 is 2.645")
do_test(${PROJECT_NAME} 25 "25 is 5")
do_test(${PROJECT_NAME} -25 "-25 is [-nan|nan|0]")
do_test(${PROJECT_NAME} 0.0001 "0.0001 is 0.01")

###############################################################################

###############################################################################
# Packaging section

include(InstallRequiredSystemLibraries)
include(CPack)

set(CPACK_PACKAGE_VENDOR "lib_src_inc")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${${PROJECT_NAME}_DESCRIPTION})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENCE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES
/.git
/dist
/.*build.*
/\\\\.DS_Store
)
###############################################################################

###############################################################################
# Installation section

####### Install targets first
# RUNTIME is for windows dlls
# LIBRARY is for shared libs in linux
# ARCHIVE is for static libraries
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
           COMPONENT ${PROJECT_NAME}_Runtime
   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
           COMPONENT ${PROJECT_NAME}_Runtime
           NAMELINK_COMPONENT ${PROJECT_NAME}_Development
   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
           COMPONENT ${PROJECT_NAME}_Development
   INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

# install the configuration targets
install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${TOP_NAMESPACE}::
  DESTINATION ${install_library_path})

####### Generate and install config and version file
include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${install_library_path})

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}"
  COMPATIBILITY SameMajorVersion)

# Install the configuration and Version files
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION ${install_library_path})

# Install the header files
install(FILES ${build_header_files} DESTINATION ${install_include_path})

####### Make and install file so outside projects can import targets from this
####### current project WHEN IT IS IN THE HOST PROJECTS BUILD TREE ONLY
####### i.e. this is not for packaging as that was taken care of with
####### install(EXPORT ...) above
# generate the export targets for the build tree
# needs to be after the install(TARGETS ) command or else it will overwrite the
# file made there and break the package installation
export(EXPORT ${PROJECT_NAME}Targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
       NAMESPACE ${TOP_NAMESPACE}::)

# Lastly export the package
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
export(PACKAGE ${PACKAGE_NAME})
#set(CMAKE_PREFIX_PATH CACHE FILEPATH ${install_library_path})

###############################################################################
