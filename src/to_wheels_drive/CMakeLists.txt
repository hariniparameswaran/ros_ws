cmake_minimum_required(VERSION 3.8)
project(to_wheels_drive)


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(backward_ros REQUIRED)
find_package(rcpputils REQUIRED)


set(THIS_PACKAGE_INCLUDE_DEPENDS
  control_toolbox
  controller_interface
  generate_parameter_library
  geometry_msgs
  hardware_interface
  nav_msgs
  pluginlib
  rclcpp
  rclcpp_lifecycle
  rcpputils
  realtime_tools
  tf2
  tf2_msgs
)

foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()
add_compile_definitions(RCPPUTILS_VERSION_MAJOR=${rcpputils_VERSION_MAJOR})
add_compile_definitions(RCPPUTILS_VERSION_MINOR=${rcpputils_VERSION_MINOR})


add_library(to_wheels_drive SHARED
  src/to_wheels_drive.cpp
  src/odometry.cpp
)
target_compile_features(to_wheels_drive PUBLIC cxx_std_17)
target_include_directories(to_wheels_drive PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/to_wheels_drive>
  /opt/ros/humble/include
)
ament_target_dependencies(to_wheels_drive
  rclcpp
  rclcpp_lifecycle
  rcpputils
  controller_interface
  control_toolbox
  hardware_interface
  pluginlib
  realtime_tools
  tf2
  tf2_msgs
  geometry_msgs
  nav_msgs
)

target_link_libraries(diff_drive_controller
  PUBLIC
    to_wheels_drive_parameters
pluginlib_export_plugin_description_file(controller_interface to_wheels_drive_plugin.xml)



# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  
  set(ament_cmake_copyright_FOUND TRUE)
  
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(
  DIRECTORY include/
  DESTINATION include/to_wheels_drive
)
install(TARGETS to_wheels_drive to_wheels_drive_parameters
  EXPORT export_to_wheels_drive
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

target_include_directories(to_wheels_drive
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)



ament_target_dependencies(to_wheels_drive
  rclcpp
  rcpputils
)

ament_export_targets(export_to_wheels_drive HAS_LIBRARY_TARGET)
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_package()