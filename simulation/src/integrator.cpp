#include "integrator.h"
#include "dynamics.h"

// Integrates the state forward in time by dt
// Eventually convert this to a more accurate integrastor like Runge-Kutta (RK4)
void integrate(StateVector& state, double dt) {
    StateVector k1 = derivatives(state);
    StateVector k2 = derivatives(state + 0.5 * dt * k1);
    StateVector k3 = derivatives(state + 0.5 * dt * k2);
    StateVector k4 = derivatives(state + dt * k3);

    state += (dt /6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);

    // Normalize the quaternion to prevent drift due to numerical errors
    state.segment<4>(6).normalize();
}