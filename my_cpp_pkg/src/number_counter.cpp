#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

using namespace std::placeholders;
using namespace std::chrono_literals;

class NumberCounterNode : public rclcpp::Node
{
public:
    NumberCounterNode() : Node("number_counter")
    {
        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10, 
            std::bind(&NumberCounterNode::callbackNumbers, this, _1));
        

        publisher_ = this->create_publisher<example_interfaces::msg::Int64>(
            "number_count", 10);
        RCLCPP_INFO(this->get_logger(), "Number counter has been started.");
    }

private:
    void callbackNumbers(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        newNumber_ = msg->data;
        msg->data = newNumber_ + (counter_ * 2);
        counter_++;
        publishNewNumber(msg);
    }

    void publishNewNumber(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Data: %lld", msg->data);
    }

    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    int newNumber_;
    int counter_ = 1;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
