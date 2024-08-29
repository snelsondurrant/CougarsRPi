import launch
import launch_ros.actions
import launch_ros.descriptions

from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory

import os
import datetime

def generate_launch_description():

    folder = "sensors_bag_" + str(datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S"))

    # Get the directory of the launch files
    package_dir = os.path.join(
        get_package_share_directory('cougars_py'), 'launch')


    return launch.LaunchDescription([
        
        # Start the data recording
        launch.actions.ExecuteProcess(
            cmd=['ros2', 'bag', 'record', '-o', '/home/frostlab/ros2_ws/bag/' + folder, '-s', 'mcap', '-a'],
            output='screen',
        ),
        # Include additional launch files
        launch.actions.IncludeLaunchDescription(
            PythonLaunchDescriptionSource(os.path.join(package_dir, 'sensors_launch.py'))
        ),
    ])