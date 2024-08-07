#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"
#include "geometry_msgs/msg/TwistWithCovarianceStamped.hpp"
#include "dvl_msgs/msg/dvl.hpp"
#include <vector>



using std::placeholders::_1;



class DVLSender : public rclcpp::Node
{
  public:
    DVLSender():Node("dvl_data_sender"){
        publisher_dvl_depth = this->create_publisher<std_msgs::msg::Float64>("dvl_dfb", 10);
        publisher_dvl_velocity = this->create_publisher<geometry_msgs::msg::TwistWithCovarianceStamped>("dvl_velocity", 10);
        subscriber_dvl_data = this->create_subscription<dvl_msgs::msg::DVL>("/dvl/data", 10, std::bind(&DVLSender::dvl_data_callback, this, _1));
        subscriber_dvl_position = this->create_subscription<dvl_msgs::msg::DVLDR>("/dvl/position", 10, std::bind(&DVLSender::dvl_pos_callback, this, _1));

    }

    void dvl_data_callback(const dvl_msgs::msg::DVL::SharedPtr msg) {


        geometry_msgs::msg::TwistWithCovarianceStamped stamped_msg;

        // filling in the upper left corner of the 6X6 covariance matrix
        std::vector<double> twistCovariance;
        int index = 0;
        double defaultValue = 0;
        for(int i = 0; i < 36;){
            if (i % 6 < 3 && i < 15){
                twistCovariance.push_back(msg.covariance[index])
                index++;
            }
            else{
                twistCovariance.push_back(defaultValue);
            }
        }

        stamped_msg.twist.covariance = twistCovariance;
        stamped_msg.twist.linear = msg.velocity;
        subscriber_dvl_data->publish(stamped_msg);


    }
    void dvl_pos_callback(const dvl_msgs::msg::DVLDR::SharedPtr msg) {


            
    }



  private:
    // publisher localizatoin pkg types
    rclcpp::Publisher<geometry_msgs::msg::TwistWithCovarianceStamped>::SharedPtr publisher_dvl_velocity;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_dvl_depth;
    
    // subscribers - listening to dvl driver
    rclcpp::Subscription<dvl_msgs::msg::DVL>::SharedPtr subscriber_dvl_data;
    rclcpp::Subscription<dvl_msgs::msg::DVLDR>::SharedPtr subscriber_dvl_position
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DVLSender>());
  rclcpp::shutdown();
  return 0;
}