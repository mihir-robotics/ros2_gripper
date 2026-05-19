// ROS 2 Node that sends a String message to Arduino via Serial Port

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

class gripper : public rclcpp::Node
{
public:
  gripper() : Node("gripper")
  {
    this->declare_parameter("port", "/dev/ttyUSB0");
    std::string port = this->get_parameter("port").as_string();

    fd_ = open(port.c_str(), O_RDWR | O_NOCTTY);
    struct termios tty{};
    tcgetattr(fd_, &tty);
    cfsetspeed(&tty, B9600);
    cfmakeraw(&tty);
    tcsetattr(fd_, TCSANOW, &tty);

    sub_ = create_subscription<std_msgs::msg::String>(
      "gripper/state", 10,
      [this](std_msgs::msg::String::SharedPtr msg) {
        std::string cmd = msg->data + "\n";
        write(fd_, cmd.c_str(), cmd.size());
      });
  }

  ~gripper() { close(fd_); }

private:
  int fd_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<gripper>());
  rclcpp::shutdown();
}