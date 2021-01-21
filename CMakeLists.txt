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

# Define the project information
project(com-sys-lib
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

# com-sys-lib will build shared this way unless the user sets
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
             CONFIG
             REQUIRED COMPONENTS ALL)

find_library(MATH_LIBRARY m)

###############################################################################

###############################################################################
# Add all the source files to the library

# Make GSL components globally available (If calling from a subdirectory only
# though so we don't need to do that here)
#if(GSL_FOUND)
#   set_target_properties(GSL::gsl
#                         GSL::gslcblas
#                         PROPERTIES IMPORTED_GLOBAL TRUE)
#endif()
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
# Directories relative to cmake_current_source_dir prior to 3.13 but now can
# just do relative to project
target_sources((${PROJECT_NAME}
               PUBLIC
                  ${CMAKE_CURRENT_SOURCE_DIR}inc/private_header.h
               INTERFACE
                  ${CMAKE_CURRENT_SOURCE_DIR}include/${PROJECT_NAME}.h
               PRIVATE
                  src/starting.cpp
                  src/starting.h
                  inc/secret_header.h)

# Add directories with source code (non header)
add_subdirectory(src)
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
             PROPERTY INTERFACE_${PROJECT_NAME}_MAJOR_VERSION ${sat-com-lib_VERSION_MAJOR})

###############################################################################

###############################################################################
# Setup Target Options

target_compile_features(${PROEJCT_NAME} cxx_std_14)

# Note that ON will set PIC ON as well by default as it is required anyway but
# ill set it just in case
# state that com-sys-lib need PIC when the default is shared libraries
set_target_properties(${PROJECT_NAME} PROPERTIES
                      POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

target_include_directories(${PROJECT_NAME}
                           PUBLIC
                               $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
                               $<INSTALL_INTERFACE:include>
                           INTERFACE
                               $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
                               $<INSTALL_INTERFACE:include>
                           PRIVATE
                               ${CMAKE_CURRENT_SOURCE_DIR})


# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
#TODO SUPPOSEDLY THIS MUST BE AFTER install(TARGET ..... EXPORT FILE) TO GET
#FILE TO ASSOCIATE WITH IT PROPERLY
set(gcc_like_cpp "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cpp "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(${PROEJCT_NAME} INTERFACE
  "$<${gcc_like_cpp}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused;-pedantic>>"
  "$<${msvc_cpp}:$<BUILD_INTERFACE:/W3;/WX>>"
)

###############################################################################

###############################################################################
# Generated Files section

# Will make com-sys-lib_export.h and define COM-SYS-LIB_EXPORT
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

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

set(CPACK_PACKAGE_VENDOR "lib-src-inc")
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
install(TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
           COMPONENT ${PROJECT_NAME}_Runtime
   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
           COMPONENT ${PROJECT_NAME}_Runtime
           NAMELINK_COMPONENT ${PROJECT_NAME}_Development
   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
           COMPONENT ${PROJECT_NAME}_Development
   INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
           COMPONENT ${PROJECT_NAME}_Runtime
           NAMELINK_COMPONENT ${PROJECT_NAME}_Development
   EXPORT ${PROJECT_NAME}Targets

# install the configuration targets
install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION lib/${PROJECT_NAME})

####### Generate and install config and version file
include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION lib/${PROJECT_NAME}
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}"
  COMPATIBILITY SameMajorVersion)

# install the configuration and Version files
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION lib/${PROJECT_NAME})

####### Make and install file so outside projects can import targets from this
####### current project WHEN IT IS IN THE HOST PROJECTS BUILD TREE ONLY
####### i.e. this is not for packaging as that was taken care of with
####### install(EXPORT ...) above
# generate the export targets for the build tree
# needs to be after the install(TARGETS ) command or else it will overwrite the
# file made there and break the package installation
export(EXPORT ${PROJECT_NAME}Targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
       NAMESPACE ${PROJECT_NAME}::)

# Lastly export the package
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
export(PACKAGE ${PACKAGE_NAME})

###############################################################################
