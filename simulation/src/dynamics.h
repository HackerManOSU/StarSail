#pragma once

#include "common.h"

// Calculates the derivatives (accelerations) based on physics
StateVector derivatives(const StateVector& state);