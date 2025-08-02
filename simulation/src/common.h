#pragma once

#include <Eigen/Dense>
#include <thread>
#include <chrono>

// Represents the state of the spacecraft:
// [pos(3), vel(3), q_x, q_y, q_z, q_w(4), omega(3)]
// Total size: 3 + 3 + 4 + 3 = 13
using StateVector = Eigen::Vector<double, 13>;