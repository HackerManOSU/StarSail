#pragma once

#include "common.h"

// Integrates the state forward in time by dt using Runge-Kutta 4th order method
void integrate(StateVector& state, double dt);