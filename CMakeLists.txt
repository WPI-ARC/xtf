cmake_minimum_required(VERSION 2.8.3)
project(xtf)
## Find dependencies
find_package(catkin REQUIRED COMPONENTS roscpp rospy)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
find_package(LibXML++ REQUIRED)
## Catkin setup
catkin_python_setup()
catkin_package(INCLUDE_DIRS include CATKIN_DEPENDS roscpp rospy DEPENDS system_lib)
## Include both default Catkin headers and LibXML++ headers
include_directories(include ${catkin_INCLUDE_DIRS} ${LibXML++_INCLUDE_DIRS})
## Declare a cpp library
add_library(${PROJECT_NAME} src/xtf.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${LibXML++_LIBRARIES})
add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})
## Mark library for installation
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/xtf.hpp DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
