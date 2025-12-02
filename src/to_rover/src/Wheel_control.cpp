#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

using namespace std::chrono_literals;

class WheelVelpub : public rclcpp::Node
{

public :

WheelVelpub() : Node("Wheel_Control")
{

pub=this->create_publisher<std_msgs::msg::Float64MultiArray>("/joint_command",10);
tim=this->create_wall_timer(std::chrono::milliseconds(100),
std::bind(&WheelVelpub::timer_callback,this));
RCLCPP_INFO(this->get_logger(),"Velocity started");
}

private:
void timer_callback()
{
std_msgs::msg::Float64MultiArray vel;
vel.data={0.5,0.5,0.5,0.5};
pub->publish(vel);
RCLCPP_INFO(this->get_logger(),"Publishing Velocity");
}

rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr pub;
rclcpp::TimerBase::SharedPtr tim;
};

int main(int argc,char* argv[])
{

rclcpp::init(argc,argv);
auto node = std::make_shared<WheelVelpub>();
rclcpp::spin(node);
rclcpp::shutdown();
return 0;

}
