#include <iostream>
#include "common.h"
#include "integrator.h"
#include "comms/telemetry.h"

/* ============================================================== */
/* ==================== Simulation Functions ==================== */
/* ============================================================== */

int main () {
    // Start web server for telemetry to ground station
    TelemetryServer server;
    server.run();

    // Initial state: [position(km), velocity(km/s)] for a low Earth orbit
    StateVector state;

    // 1. Initial Translational State (LEO)
    state.head<3>() << 7000.0, 0.0, 0.0;        // Position (km)
    state.segment<3>(3) << 0.0, 7.546, 0.0;     // Velocity (km/s)

    // 2. Initial Rotational State (Attitude and Angular Velocity)
    Eigen::Quaterniond initial_q(1, 0, 0, 0); // Identity quaternion (w, x, y, z)
    state.segment<4>(6) = initial_q.coeffs(); // Stored as [x, y, z, w]
    state.tail<3>() << 0.05, 0.0, 0.0;

    const double dt = 1.0; // Time step in seconds
    const double simulationDuration = 90 * 60.0; // Simulate one orbit

    std::cout << "Starting simulation..." << std::endl;

    for (double t = 0; t < simulationDuration; t += dt) {

        integrate(state, dt);

        // Log the state and broadcast telemetry every second
        if ((int)t % 1 == 0) {
            server.broadcast(state);
        }

        
        // Log the state every minute
        if ((int)t % 60 == 0) {
            std::cout << "Time: " << t << "s"
            << ", Pos: (" << state(0) << ", " << state(1) << ", " << state(2) << ")"
            << ", Vel: (" << state(3) << ", " << state(4) << ", " << state(5) << ")"
            << ", Quat (x,y,z,w): (" << state(6) << ", " << state(7) << ", " << state(8) << ", " << state(9) << ")"
            << ", Omega: (" << state(10) << ", " << state(11) << ", " << state(12) << ")"
            << std::endl;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Simulation finished." << std::endl;

    // Destructor will stop the server, just here for clarity and safety net
    server.stop();

    return 0;
}

