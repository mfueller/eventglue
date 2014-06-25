cmake_minimum_required(VERSION 2.8.3)
project(mcr_robinson_hello_world)

# only need mcr_robinson
find_package(catkin REQUIRED COMPONENTS mcr_robinson)

####### these options are for debugging....
set( CMAKE_CXX_FLAGS "-Wno-enum-compare " )
set( CMAKE_BUILD_TYPE Debug)
#######

# only needed for the python example
catkin_python_setup()

# dependencies, include dir and library definition
catkin_package(
  CATKIN_DEPENDS
    mcr_robinson
  INCLUDE_DIRS
    common/include
  LIBRARIES
    helloworld
)

include_directories(
  common/include
  ${catkin_INCLUDE_DIRS} 
 )

link_directories(
  ${catkin_LIBRARY_DIRS}
)


# build the library, requires the source files
add_library(helloworld
  common/src/HelloWorldImpl.cpp
)
target_link_libraries(helloworld
  ${catkin_LIBRARIES}
)

# install the header files (might not be required)
install(DIRECTORY common/include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  PATTERN ".svn" EXCLUDE
)
