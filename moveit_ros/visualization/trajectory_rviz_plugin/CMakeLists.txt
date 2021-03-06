set(MOVEIT_LIB_NAME moveit_trajectory_rviz_plugin)

# Header files that need Qt Moc pre-processing for use with Qt signals, etc:
set(HEADERS
  include/moveit/trajectory_rviz_plugin/trajectory_display.h
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Trajectory Display
add_library(${MOVEIT_LIB_NAME}_core SHARED
  src/trajectory_display.cpp
  ${HEADERS}
)
set_target_properties(${MOVEIT_LIB_NAME}_core PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
set_target_properties(${MOVEIT_LIB_NAME}_core PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
target_link_libraries(${MOVEIT_LIB_NAME}_core
  moveit_rviz_plugin_render_tools
  moveit_planning_scene_rviz_plugin_core
  rviz_ogre_vendor::OgreMain
)

ament_target_dependencies(${MOVEIT_LIB_NAME}_core
    rclcpp
    rviz2
    moveit_msgs
    pluginlib
    Boost
)

# Plugin Initializer
add_library(${MOVEIT_LIB_NAME} SHARED src/plugin_init.cpp)
set_target_properties(${MOVEIT_LIB_NAME} PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
set_target_properties(${MOVEIT_LIB_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
target_link_libraries(${MOVEIT_LIB_NAME} ${MOVEIT_LIB_NAME}_core)
ament_target_dependencies(${MOVEIT_LIB_NAME}
    rclcpp
    pluginlib
    Boost
)

install(DIRECTORY include/ DESTINATION include)

install(TARGETS ${MOVEIT_LIB_NAME} ${MOVEIT_LIB_NAME}_core
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

ament_export_libraries(
  ${MOVEIT_LIB_NAME}_core
  ${MOVEIT_LIB_NAME}
)