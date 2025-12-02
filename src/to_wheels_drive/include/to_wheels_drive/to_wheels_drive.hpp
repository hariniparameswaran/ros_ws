#ifndef TO_WHEELS_DRIVE__TO_WHEELS_DRIVE_HPP_
#define TO_WHEELS_DRIVE__TO_WHEELS_DRIVE_HPP_

#include "odometry.hpp"
#include "tf2_msgs/msg/tf_message.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "rclcpp_lifecycle/state.hpp"
#include "realtime_tools/realtime_publisher.hpp"
#include "realtime_tools/realtime_thread_safe_box.hpp"

namespace to_wheels_drive
{
class towheelsdrive : public controller_interface::ControllerInterface
{

public:
  towheelsdrive();

  controller_interface::InterfaceConfiguration command_interface_configuration() const override;

  controller_interface::InterfaceConfiguration state_interface_configuration() const override;

  controller_interface::return_type update_reference_from_subscribers(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

  controller_interface::return_type update_and_write_commands(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

  controller_interface::CallbackReturn on_init() override;

  controller_interface::CallbackReturn on_configure(
    const rclcpp_lifecycle::State & previous_state) override;

  controller_interface::CallbackReturn on_activate(
    const rclcpp_lifecycle::State & previous_state) override;

  controller_interface::CallbackReturn on_deactivate(
    const rclcpp_lifecycle::State & previous_state) override;

  controller_interface::CallbackReturn on_cleanup(
    const rclcpp_lifecycle::State & previous_state) override;

  controller_interface::CallbackReturn on_error(
    const rclcpp_lifecycle::State & previous_state) override;

protected:

  struct WheelHandle
  {
    std::optional<std::reference_wrapper<const hardware_interface::LoanedStateInterface>> feedback;
    std::reference_wrapper<hardware_interface::LoanedCommandInterface> velocity;
  };

  const char * feedback_type() const;
  controller_interface::CallbackReturn configure_side(
    const std::string & side, const std::vector<std::string> & wheel_names,
    std::vector<WheelHandle> & registered_handles);

  std::vector<WheelHandle> registered_left_wheel_handles_;
  std::vector<WheelHandle> registered_right_wheel_handles_;

  std::shared_ptr<ParamListener> param_listener_;
  Params params_;

  int wheels_per_side_;

  Odometry odometry_;

  rclcpp::Duration cmd_vel_timeout_ = rclcpp::Duration::from_seconds(0.5);

  std::shared_ptr<rclcpp::Publisher<nav_msgs::msg::Odometry>> odometry_publisher_ = nullptr;
  std::shared_ptr<realtime_tools::RealtimePublisher<nav_msgs::msg::Odometry>>
    realtime_odometry_publisher_ = nullptr;
  nav_msgs::msg::Odometry odometry_message_;

  std::shared_ptr<rclcpp::Publisher<tf2_msgs::msg::TFMessage>> odometry_transform_publisher_ =
    nullptr;
  std::shared_ptr<realtime_tools::RealtimePublisher<tf2_msgs::msg::TFMessage>>
    realtime_odometry_transform_publisher_ = nullptr;
  tf2_msgs::msg::TFMessage odometry_transform_message_;

  bool subscriber_is_active_ = false;
  rclcpp::Subscription<TwistStamped>::SharedPtr velocity_subscriber_ = nullptr;

  realtime_tools::RealtimeThreadSafeBox<TwistStamped> received_velocity_msg_;
  TwistStamped command_msg_;

  bool publish_velocity_ = false;
  std::shared_ptr<rclcpp::Publisher<TwistStamped>> velocity_publisher_ = nullptr;
  std::shared_ptr<realtime_tools::RealtimePublisher<TwistStamped>>
    realtime_limited_velocity_publisher_ = nullptr;
  TwistStamped velocity_message_;

  rclcpp::Time previous_update_timestamp_{0};

  // publish rate limiter
  double publish_rate_ = 50.0;
  rclcpp::Duration publish_period_ = rclcpp::Duration::from_nanoseconds(0);
  rclcpp::Time previous_publish_timestamp_{0, 0, RCL_CLOCK_UNINITIALIZED};

  bool reset();
  void halt();

private:
  void reset_buffers();
};
}  // namespace to_wheels_drive
#endif  // TO_WHEELS_DRIVE__TO_WHEELS_DRIVE_HPP_