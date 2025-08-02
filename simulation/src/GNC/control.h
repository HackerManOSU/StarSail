#pragma once

#include "../common.h"

// Calculates the control torque to stabilize the spacecraft's attitude
// Aims to drive angular velocity to zero and align with an identity quaternion
Eigen::Vector3d calculate_control_torque(const StateVector& state);