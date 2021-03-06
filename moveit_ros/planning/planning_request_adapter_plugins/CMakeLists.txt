set(MOVEIT_LIB_NAME moveit_default_planning_request_adapter_plugins)

set(SOURCE_FILES
  src/empty.cpp
  src/fix_start_state_bounds.cpp
  src/fix_start_state_collision.cpp
  src/fix_start_state_path_constraints.cpp
  src/fix_workspace_bounds.cpp
  src/add_time_parameterization.cpp
  src/add_iterative_spline_parameterization.cpp
  src/add_time_optimal_parameterization.cpp
  src/resolve_constraint_frames.cpp
)

add_library(${MOVEIT_LIB_NAME} SHARED ${SOURCE_FILES})

set_target_properties(${MOVEIT_LIB_NAME} PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
set_target_properties(${MOVEIT_LIB_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
ament_target_dependencies(${MOVEIT_LIB_NAME}
    Boost
    rclcpp
    pluginlib
    moveit_core
)

add_executable(moveit_list_request_adapter_plugins src/list.cpp)
ament_target_dependencies(moveit_list_request_adapter_plugins
  Boost
  rclcpp
  pluginlib
  ament_index_cpp
)

install(TARGETS ${MOVEIT_LIB_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

install(TARGETS moveit_list_request_adapter_plugins
  DESTINATION lib/${PROJECT_NAME})
