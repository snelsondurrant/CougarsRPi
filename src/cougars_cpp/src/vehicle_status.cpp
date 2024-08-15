

// #include <chrono>
// #include <functional>
// #include <memory>
// #include <string>

// #include "dvl_msgs/msg/dvl.hpp"
// #include "dvl_msgs/msg/dvldr.hpp"
// #include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"
// #include "geometry_msgs/msg/twist_with_covariance_stamped.hpp"
// #include "rclcpp/rclcpp.hpp"
// #include "std_msgs/msg/float64.hpp"
// #include "std_msgs/msg/string.hpp"

// #include "nav_msgs/msg/odometry.hpp"
// #include <vector>

// #include <chrono>
// #include <functional>
// #include <memory>
// #include <string>

// #include "cougars_cpp/pid.h"
// #include "dvl_msgs/msg/dvldr.hpp"
// #include "frost_interfaces/msg/desired_depth.hpp"
// #include "frost_interfaces/msg/desired_heading.hpp"
// #include "frost_interfaces/msg/desired_speed.hpp"
// #include "frost_interfaces/msg/u_command.hpp"
// #include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"
// #include "geometry_msgs/msg/twist_with_covariance_stamped.hpp"
// #include "rclcpp/rclcpp.hpp"


// #define UPDATE_TIMER_MS std::chrono::milliseconds(10)


// using namespace std::chrono_literals;
// using std::placeholders::_1;


// rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
// auto qos = rclcpp::QoS(
//     rclcpp::QoSInitialization(qos_profile.history, qos_profile.depth),
//     qos_profile);

// class VehicleStatus : public rclcpp::Node {
// public:
//   VehicleStatus() : Node("vehicle_status") {

//     x_y_subscription_ = this->create_subscription<
//         geometry_msgs::msg::PoseWithCovarianceStamped>(
//         "odometry/filtered", 10, std::bind(&VehicleStatus::x_y_callback, this, _1));

//     depth_subscription_ = this->create_subscription<
//         geometry_msgs::msg::PoseWithCovarianceStamped>(
//         "depth_data", 10, std::bind(&VehicleStatus::depth_callback, this, _1));

//     // TODO: change this to 'vehicle_status' listener
//     velocity_subscription_ = this->create_subscription<
//         geometry_msgs::msg::TwistWithCovarianceStamped>(
//         "dvl_velocity", 10,
//         std::bind(&VehicleStatus::velocity_callback, this, _1));

//     orientation_subscription_ = this->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
//         "modem_imu", qos, std::bind(&VehicleStatus::orientation_callback, this, _1));

//     // declare ros timers
//     update_timer_ = this->create_wall_timer(
//         UPDATE_TIMER_MS, std::bind(&VehicleStatus::timer_callback, this));
//   }

// private:
//   void x_y_callback(const geometry_msgs::msg::PoseWithCovarianceStamped &x_y_message ){
//     this->y_pos = x_y_message.pose.pose.position.y;
//     this->x_pos = x_y_message.pose.pose.position.x;
//   }
//   void depth_callback(
//       const geometry_msgs::msg::PoseWithCovarianceStamped &depth_msg) {
//     this->depth = depth_msg.pose.pose.position.z;
//   }
//   void velocity_callback(
//       const geometry_msgs::msg::TwistWithCovarianceStamped &velocity_msg) {
//     this->x_velocity = velocity_msg.twist.twist.linear.x;
//   }
//   void orientation_callback(const geometry_msgs::msg::PoseWithCovarianceStamped &orientation_msg) {
//     this->q_w = orientation_msg.pose.pose.orientation.w;
//     this->q_x = orientation_msg.pose.pose.orientation.x;
//     this->q_y = orientation_msg.pose.pose.orientation.y;
//     this->q_z = orientation_msg.pose.pose.orientation.z;
//   }


//   void update_callback() {
//     auto message = nav_msgs::msg::Odometry();
//     message.pose.pose.position.x = this->x_pos;
//     message.pose.pose.position.y = this->y_pos;
//     message.pose.pose.position.z = this->depth;
//     message.pose.pose.orientation.w = this->q_w;
//     message.pose.pose.orientation.y = this->q_y;
//     message.pose.pose.orientation.z = this->q_z;
//     message.pose.pose.orientation.x = this->q_x;
//     message.twist.twist.linear.x = this->x;
    

//     // publishes speed, depth, global x,y, 
//     // and orientation (quaternion)
//     // to be used by MOOS and anything else to 
//     vehicle_status_publisher_->publish(message);

//   }

//   // call back timer to update
//   rclcpp::TimerBase::SharedPtr update_timer_;
//   // depth, speed, heading
//   rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr
//       depth_subscription_;
//   rclcpp::Subscription<geometry_msgs::msg::TwistWithCovarianceStamped>::
//       SharedPtr velocity_subscription_;
//   rclcpp::Subscription<dvl_msgs::msg::DVLDR>::SharedPtr orientation_subscription_;

//   // current x,y
//   rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr x_y_subscription_;

//   rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr
//       vehicle_status_publisher_;

//   // status variables
//   float q_x = 0.0;
//   float q_y = 0.0;
//   float q_z = 0.0;
//   float q_w = 0.0;
//   float x_velocity = 0.0;
//   float depth = 0.0;
//   float x_pos = 0.0;
//   float y_pos = 0.0;
// };

// int main(int argc, char *argv[]) {
//   rclcpp::init(argc, argv);
//   rclcpp::spin(std::make_shared<VehicleStatus>());
//   rclcpp::shutdown();
//   return 0;
// }