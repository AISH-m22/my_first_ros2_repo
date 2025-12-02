#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <cmath>

class CircleNode : public rclcpp::Node
{
    public:
        CircleNode() : Node("circle_node")
            {
                publisher_= this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);

                velocity = 1.0;
                angular_velocity = 1.0;

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