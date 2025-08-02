#include "dynamics.h"
#include "GNC/control.h"

/* ============================================================== */
/* ========================= Constants ========================== */
/* ============================================================== */

// Earth's gravitations parameter
const double MU_EARTH = 398600.4418; // (km^3/s^2)

// Spacecraft's moment of inertia tensor (assuming a simple diagonal tensor)
// Represents resistance to rotational motion. Units: kg*m^2
// For simulation purposes, we can use scaled values.
const Eigen::Matrix3d INERTIA_TENSOR = (Eigen::Vector3d(100.0, 100.0, 100.0)).asDiagonal();
const Eigen::Matrix3d INERTIA_TENSOR_INV = INERTIA_TENSOR.inverse();

// Calculates the derivatives (accelerations) based on physics
StateVector derivatives(const StateVector& state) {
    StateVector dot;

    // 1. Translational Dynamics (Position and Velocity)
    Eigen::Vector3d position = state.head<3>();
    Eigen::Vector3d velocity = state.segment<3>(3);
    double r = position.norm();
    // Two-body gravitational acceleration
    Eigen::Vector3d acceleration = -MU_EARTH * position / (r * r * r);  // F = -GM * r / r^3

    dot.head<3>() = velocity;           // d(pos)/dt = vel
    dot.segment<3>(3) = acceleration;   // d(vel)/dt = acc

    // 2. Rotational Dynamics (Attitude and Angular Velocity)
    // Eigen stores quaternion coeffs as [x, y, z, w] but the constructor is (w, x, y, z)
    Eigen::Quaterniond q(state[9], state[6], state[7], state[8]); // Construct w,x,y,z from state's x,y,z,w
    Eigen::Vector3d omega = state.tail<3>();

    Eigen::Quaterniond omega_quat(0.0, omega.x(), omega.y(), omega.z());
    Eigen::Quaterniond q_dot = q * omega_quat;
    q_dot.coeffs() *= 0.5;

    dot.segment<4>(6) = q_dot.coeffs(); // d(q)/dt

    // Calculate control torque
    Eigen::Vector3d control_torque = calculate_control_torque(state);

    // Euler's equation of motion: I * omega_dot + omega x (I * omega) = torque
    // omega_dot = I_inv * (torque - omega x (I * omega))
    Eigen::Vector3d omega_dot = INERTIA_TENSOR_INV * (control_torque - omega.cross(INERTIA_TENSOR * omega));
    dot.tail<3>() = omega_dot;

    return dot;
}