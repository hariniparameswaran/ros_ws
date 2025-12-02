
#include "to_wheels_drive/to_wheels_drive.hpp"
#include "hardware_interface/types/hardware_interface_type_values.hpp"

namespace  to_wheels_drive
{
towheelsdrive::towheelsdrive() : controller_interface::ControllerInterface{}

void to_wheels_drive::initialize_implementation_parameter_listener()
{
  to_param_listener_ =
    std::make_shared<to_wheels_drive::ParamListener>(get_node());
}

  controller_interface::CallbackReturn Ackerman::configure_odometry()
  {
  ackermann_params_ = ackermann_param_listener_->get_params();

  if (ackermann_params_.steering_track_width <= std::numeric_limits<double>::epsilon())
  {
    ackermann_params_.steering_track_width = ackermann_params_.traction_track_width;
  }

  const double traction_wheels_radius = ackermann_params_.traction_wheels_radius;
  const double traction_track_width = ackermann_params_.traction_track_width;
  const double steering_track_width = ackermann_params_.steering_track_width;
  const double wheelbase = ackermann_params_.wheelbase;

} // namespace  to_wheels_drive
