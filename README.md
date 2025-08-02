# StarSail
A simulation of a spacecraft's trajectory, orbital mechanics, and attitude control with algorithms for guidance, navigation, and control (GNC)

# Steps to Run The Simulation
### 1. Build and Run the C++ Simulation

Navigate to the simulation build directory and compile the project:

```sh
cd simulation/build
cmake ..
make
```

Once compiled, run the simulation executable:

```sh
./starsail_sim
```

### 2. Run the Ground Station UI

The ground station is a React application. Navigate to the `ground-station` directory, install dependencies, and start the development server:

```sh
cd ground-station
npm install
npm run dev
```

### 3. View the Ground Station

Open your web browser and navigate to the local address provided by Vite (usually `http://localhost:5173`). The ground station UI will connect to the running simulation to visualize telemetry and send commands.