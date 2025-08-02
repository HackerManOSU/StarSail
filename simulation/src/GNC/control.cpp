#include "control.h"

// Simple PD controller for attitude stabilization

Eigen::Vector3d calculate_control_torque(const StateVector& state) {
    // --- Controller Gains ---
    // These values are chosen to provide a reasonably fast and stable response

    const double Kp = 0.1;              // Proportional gain (corrects attitude error)
    const double Kd = 0.5;              // Derivative gain (dampens rotation)

    // --- Desired State ---
    // We want to stop rotating, so the desired attitude is no rotation
    // and the desired angular velocity is zero
    Eigen::Quaterniond q_desired(1.0, 0.0, 0.0, 0.0);
    Eigen::Vector3d omega_desired(0.0, 0.0, 0.0);

    // --- Current State ---
    Eigen::Quaterniond q_current(state[9], state[6], state[7], state[8]);
    Eigen::Vector3d omega_current = state.tail<3>();

    // --- Error Calculation ---
    // Attitude error, represented by the vector part of the error quaternion
    Eigen::Quaternion q_error = q_current.inverse() * q_desired;
    Eigen::Vector3d error_vec = q_error.vec();

    // Angular velocity error
    Eigen::Vector3d omega_error = omega_current - omega_desired;

    // --- PD Control Law ---
    Eigen::Vector3d torque = -Kp * error_vec - Kd * omega_error;

    return torque;
}