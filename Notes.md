# Core Features and Tech Stack
- **Simulation Core:** C++ for orbital dynamics, altitude propagation, GNC algorithms
- **Ground Station UI:** React + WebSocket frontend
- **Middleware:** C++ WebSocket server

## Simulation Loop in C++
- Use **Eigen** for vector math, rotations, and matrix ops
- Use **Runge-Kutta** or Euler integration for orbit/attitude updates
- Implement time stepping with std::chrono or a fixed timestep

## GNC Algorithms in C++
- **Guidance:** Plan burns (e.g., delta-v for Hohmann)
- **Navigation:** Implement an Extended Kalman Filter using simulated sensor noise
- **Control:** Start with PID or quaternion feedback control

## C++ WebSocket Server
- **uWebSockets:** Fast, modern

## React Frontend
- Use **React + Three.js** to display:
  - Earth (globe or orbit ring)
  -   Spacecraft 3D model + attitude axes
  -   Live charts or numerical telemetry
-   Use socket.io-client or native WebSocket API to connect to the C++ backend

## Dev
CMake project with dependencies:
- Eigen (math)
- uWebSockets (telemetry)
- Optional: spdlog or fmt for clean logging
