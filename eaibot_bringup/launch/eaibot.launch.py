import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, TimerAction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration

# Obtains share directory paths.
pkg_eaibot_bringup = get_package_share_directory('eaibot_bringup')
pkg_eaibot_control = get_package_share_directory('eaibot_control')
pkg_eaibot_description = get_package_share_directory('eaibot_description')

def generate_launch_description():
    # Declares launch arguments
    camera_arg = DeclareLaunchArgument(
            'include_camera',
            default_value='True',
            description='Indicates whether to include camera launch.')
    camera =  LaunchConfiguration('include_camera')
    rplidar_arg = DeclareLaunchArgument(
            'include_rplidar',
            default_value='True',
            description='Indicates whether to include rplidar launch.')
    rplidar =  LaunchConfiguration('include_rplidar')

    # Includes eaibot_description launch file
    include_eaibot_description = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_eaibot_description, 'launch', 'eaibot_description.launch.py'),
        ),
        launch_arguments={
            'rsp': 'True',
        }.items()
    )

    # Include eaibot_control launch file
    include_eaibot_control =  IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_eaibot_control, 'launch', 'eaibot_control.launch.py'),
        ),
        launch_arguments={
        }.items()
    )

    # Include rplidar launch file
    include_rplidar = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_eaibot_bringup, 'launch', 'rplidar.launch.py'),
        ),
        launch_arguments={
            "serial_port": '/dev/ttyUSB_LIDAR',
        }.items(),
                condition=IfCondition(rplidar)
    )
    # Include camera launch file
    include_camera = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_eaibot_bringup, 'launch', 'camera.launch.py'),
        ),
        launch_arguments={
        }.items(),
                condition=IfCondition(camera)
    )

    # TODO))(francocipollone): Improve concatenation of launch files.
    #
    # Waits for eaibot_description to set up robot_state_publisher.
    eaibot_control_timer = TimerAction(period=5.0, actions=[include_eaibot_control])
    # Defer sensors launch to avoid overhead while robot_state_publisher is setting up.
    rplidar_timer = TimerAction(period=3.0, actions=[include_rplidar])
    camera_timer = TimerAction(period=3.0, actions=[include_camera])

    twist_mux_params = os.path.join(pkg_eaibot_bringup,'config','twist_mux.yaml')
    twist_mux = Node(
            package="twist_mux",
            executable="twist_mux",
            parameters=[twist_mux_params],
            remappings=[('/cmd_vel_out','/diff_controller/cmd_vel_unstamped')]
        )

    return LaunchDescription([
        include_eaibot_description,
        eaibot_control_timer,
        camera_arg,
        camera_timer,
        rplidar_arg,
        rplidar_timer,
        twist_mux,
    ])
