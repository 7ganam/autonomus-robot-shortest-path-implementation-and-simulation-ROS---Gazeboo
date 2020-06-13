cmake_minimum_required(VERSION 2.8.3)
project(as1)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  geometry_msgs
  message_generation
  nav_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)



## To declare and build messages, services or actions from within this


## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   PP.msg
 )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   nav_msgs
   geometry_msgs 
   std_msgs
 )



## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
   DEPENDS roscpp geometry_msgs std_msgs
   CATKIN_DEPENDS # TODO
   INCLUDE_DIRS # TODO include
   LIBRARIES # TODO
   CATKIN_DEPENDS nav_msgs roscpp rospy
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)




#############
## Testing ##
#############


include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(subpub1 src/subpub1.cpp)
target_link_libraries(subpub1 ${catkin_LIBRARIES})
add_dependencies(subpub1 as1_generate_messages_cpp)


include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(laser src/laser.cpp)
target_link_libraries(laser ${catkin_LIBRARIES})
add_dependencies(laser as1_generate_messages_cpp)

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(imu src/imu.cpp)
target_link_libraries(imu ${catkin_LIBRARIES})
add_dependencies(imu as1_generate_messages_cpp)

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(kin src/kin.cpp)
target_link_libraries(kin ${catkin_LIBRARIES})
add_dependencies(kin as1_generate_messages_cpp)



#include_directories(include ${catkin_INCLUDE_DIRS})
#add_executable(goto src/goto.cpp)
#target_link_libraries(goto ${catkin_LIBRARIES})
#add_dependencies(goto as1_generate_messages_cpp)

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(ttt src/ttt.cpp)
target_link_libraries(ttt  ${catkin_LIBRARIES})
add_dependencies(ttt  as1_generate_messages_cpp)

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(assignment src/assignment.cpp)
target_link_libraries(assignment  ${catkin_LIBRARIES})
add_dependencies(assignment  as1_generate_messages_cpp)

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(gofunction src/gofunction.cpp)
target_link_libraries(gofunction ${catkin_LIBRARIES})
add_dependencies(gofunction  as1_generate_messages_cpp)

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(astar src/astar.cpp)
target_link_libraries(astar ${catkin_LIBRARIES})
add_dependencies(astar  as1_generate_messages_cpp)

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(astar_1 src/astar_1.cpp)
target_link_libraries(astar_1 ${catkin_LIBRARIES})
add_dependencies(astar_1  as1_generate_messages_cpp)

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(rrt src/rrt.cpp)
target_link_libraries(rrt ${catkin_LIBRARIES})
add_dependencies(rrt  as1_generate_messages_cpp)