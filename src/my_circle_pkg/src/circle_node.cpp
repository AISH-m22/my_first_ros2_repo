#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <cmath>

class CircleNode : public rclcpp::Node
{
    public:
        CircleNode() : Node("circle_node")
            {
                publisher_= this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);

                subscriber_ = this->create_subscription<geometry_msgs::msg::Twist>(
                "turtle1/cmd_vel", 10,
                [this](const geometry_msgs::msg::Twist::SharedPtr msg) {
                RCLCPP_INFO(this->get_logger(), 
                "Subscriber received: linear=%.2f, angular=%.2f", 
                msg->linear.x, msg->angular.z);
                 });

                // ROS2 parameters for dynamic input
                this->declare_parameter<double>("velocity", 5.5);
                this->declare_parameter<double>("angular_velocity", 2.0);

                this->get_parameter("velocity", velocity);
                this->get_parameter("angular_velocity", angular_velocity);

                double radius = velocity / angular_velocity;
                double circumference = 2 * M_PI * radius;

                RCLCPP_INFO(this->get_logger(),"Cirlce radius: %.2f", radius);
                RCLCPP_INFO(this->get_logger(), "Circumference: %.2f", circumference);

                timer_= this->create_wall_timer(
                    std::chrono::milliseconds(100),
                    std::bind(&CircleNode::publish_cmd, this));
            }
        private:
            void publish_cmd()
            {
                geometry_msgs::msg::Twist msg;
                msg.linear.x = velocity;
                msg.angular.z = angular_velocity;
                publisher_->publish(msg);
            }

        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
        rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscriber_;
        rclcpp::TimerBase::SharedPtr timer_;
        double velocity, angular_velocity;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CircleNode>());
    rclcpp::shutdown();
    return 0;
}