import { useState, useEffect } from 'react';
import './App.css';

// A type for the telemetry data structure
interface TelemetryData {
  pos_x?: number;
  pos_y?: number;
  pos_z?: number;
  q_w?: number;
  q_x?: number;
  q_y?: number;
  q_z?: number;
  omega_x?: number;
  omega_y?: number;
  omega_z?: number;
}

function App() {
  const [telemetry, setTelemetry] = useState<TelemetryData>({});
  const [isConnected, setIsConnected] = useState(false);

  useEffect(() => {
    const ws = new WebSocket('ws://localhost:9001');

    ws.onopen = () => {
      console.log('Connected to telemetry server');
      setIsConnected(true);
    };

    ws.onmessage = (event) => {
      try {
        const data = JSON.parse(event.data);
        setTelemetry(data);
      } catch (error) {
        console.error('Failed to parse telemetry data:', error);
      }
    };

    ws.onclose = () => {
      console.log('Disconnected from telemetry server');
      setIsConnected(false);
    };

    ws.onerror = (error) => {
      console.error('WebSocket error:', error);
      setIsConnected(false);
    };

    // Clean up the connection when the component unmounts
    return () => {
      ws.close();
    };
  }, []); // The empty dependency array ensures this effect runs only once

  return (
    <div className="bg-gray-900 text-white min-h-screen flex flex-col items-center justify-center font-sans">
      <header className="text-center">
        <h1 className="text-5xl font-bold mb-4">StarSail Ground Station</h1>
        <p className="text-lg mb-6">
          Status: 
          <span className={`font-semibold ${isConnected ? 'text-cyan-400' : 'text-red-500'}`}>
            {isConnected ? ' Connected' : ' Disconnected'}
          </span>
        </p>
        <div className="bg-gray-800 p-4 rounded-lg shadow-lg w-96 text-left">
          <h2 className="text-2xl font-semibold mb-2">Live Telemetry</h2>
          <pre className="font-mono text-sm overflow-x-auto">
            {JSON.stringify(telemetry, null, 2)}
          </pre>
        </div>
      </header>
    </div>
  );
}

export default App;