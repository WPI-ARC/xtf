cmake_minimum_required(VERSION 2.8.3)
project(xtf)
## Find dependencies
find_package(catkin REQUIRED COMPONENTS arc_utilities roscpp rospy)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
find_package(LibXML++ REQUIRED)
## Catkin setup
catkin_python_setup()
catkin_package(INCLUDE_DIRS include LIBRARIES ${PROJECT_NAME} CATKIN_DEPENDS arc_utilities roscpp rospy DEPENDS system_lib LibXML++)
## Include both default Catkin headers and LibXML++ headers
include_directories(include ${catkin_INCLUDE_DIRS} ${LibXML++_INCLUDE_DIRS})
## Enable debug symbols
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g")
## Declare a cpp library
add_library(${PROJECT_NAME} include/${PROJECT_NAME}/xtf.hpp src/${PROJECT_NAME}/xtf.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${LibXML++_LIBRARIES})
add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})
## Mark library for installation
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  PATTERN ".svn" EXCLUDE
)
