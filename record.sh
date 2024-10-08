#!/bin/bash

##########################################################
# RECORDS A ROS2 BAG FILE
# - Run this after running the 'bash start.sh' script
##########################################################

cleanup() {

    bash ~/ros2_ws/moos_tools/mission_kill.sh

    exit 0
}
trap cleanup SIGINT

echo ""
echo "Enter a descriptive folder name for the rosbag: "
read FOLDER
echo ""

cd ~/ros2_ws
source install/setup.bash

# TODO: Add scripting wizardry here
bash ~/ros2_ws/dvl_tools/reset_dr.sh
bash ~/ros2_ws/init_factor_graph.sh

# Start the MOOS-IvP mission
bash ~/ros2_ws/moos_tools/mission_start_processes.sh
bash ~/ros2_ws/moos_tools/mission_deploy.sh

FOLDER=$FOLDER-$(date +"%Y-%m-%d-%H-%M-%S")
ros2 bag record -o /home/frostlab/ros2_ws/bag/$FOLDER -s mcap -a
