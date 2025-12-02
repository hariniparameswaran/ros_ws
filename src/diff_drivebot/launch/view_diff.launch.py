from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration, Command
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from ament_index_python.packages import get_package_share_directory
from launch.actions import TimerAction
import os

def generate_launch_description():

    use_sim_time = LaunchConfiguration('use_sim_time', default=True)

    # Path to your URDF.xacro file
    pkg_path = get_package_share_directory('diff_drivebot')
    urdf_file = os.path.join(pkg_path, 'urdf', 'diff_drive.urdf.xacro')
    control_yaml=os.path.join(get_package_share_directory('diff_drivebot'),'config',
    'diff_control.yaml')      
    
    # Create robot_description from xacro
    robot_description = ParameterValue(Command(['xacro ', urdf_file]), value_type=str)

    # Publish robot_description to ROS 2
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': robot_description}]
    )

     # Launch Gazebo Fortress (Ignition)
    gz_sim_process = TimerAction(period= 3.0,
        actions=[ExecuteProcess(
        cmd=['ign', 'gazebo', '-v', '4', 'empty.sdf'],
        output='screen')
        ]
    )

    # Spawn the robot in Gazebo Fortress using ros_gz_sim
    spawn_entity = ExecuteProcess(
        cmd=['ros2', 'run', 'ros_gz_sim', 'create',
             '-topic', 'robot_description',
             '-name', 'Diff_Drivebot',
             '-z', '0.5'],
        output='screen'
    )
    
    
    
    joint_state = Node(
        package='controller_manager',
        executable='spawner',
        arguments=['joint_state_broadcaster'],
        output='screen'
        
    )
    
    diff_drive = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["diff_drive_controller","--param-file",control_yaml],
        output="screen",
    )

     
    
    bridge = Node(
    package='ros_ign_bridge',
    executable='parameter_bridge',
    arguments=['/clock@rosgraph_msgs/msg/Clock[ignition.msgs.Clock'],
    output='screen'
    )
    
    


    return LaunchDescription([
        
        robot_state_publisher_node,
        gz_sim_process,
        spawn_entity,
        joint_state,
        diff_drive,
        bridge
    ])
