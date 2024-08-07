import launch
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription([
        launch.actions.ExecuteProcess(
            cmd=['ros2', 'bag', 'record', '-s', 'mcap', '-a'],
            output='screen'
        ),
        launch_ros.actions.Node(
            package='cougars_py',
            executable='manual_control'
        ),
        launch_ros.actions.Node(
            package='cougars_py',
            executable='leak_sub'
        ),
        launch_ros.actions.Node(
            package='cougars_py',
            executable='battery_sub'
        ),
        launch_ros.actions.Node(
            package='cougars_cpp',
            executable='demo_control'
        ),
        # launch_ros.actions.Node(
        #     package='seatrac',
        #     executable='modem'
        # ),
        launch.actions.DeclareLaunchArgument('ip_address', default_value='192.168.194.95'),
        launch_ros.actions.Node(
            package='dvl_a50', 
            executable='dvl_a50_sensor', 
            parameters=[{'dvl_ip_address': launch.substitutions.LaunchConfiguration('ip_address')}],
        ),
    ])