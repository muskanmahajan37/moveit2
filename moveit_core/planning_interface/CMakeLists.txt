set(MOVEIT_LIB_NAME moveit_planning_interface)

add_library(${MOVEIT_LIB_NAME} SHARED
  src/planning_interface.cpp
  src/planning_response.cpp
)
set_target_properties(${MOVEIT_LIB_NAME} PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
set_target_properties(${MOVEIT_LIB_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
ament_target_dependencies(${MOVEIT_LIB_NAME}
  moveit_msgs
  urdf
  urdfdom
  urdfdom_headers
)
target_link_libraries(${MOVEIT_LIB_NAME}
  moveit_robot_trajectory
  moveit_robot_state
)

install(TARGETS ${MOVEIT_LIB_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)
