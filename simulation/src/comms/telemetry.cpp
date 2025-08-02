#include "telemetry.h"
#include <iostream>
#include <sstream>
#include <iomanip>

TelemetryServer::TelemetryServer() {
    server.init_asio();

    server.set_open_handler([this](websocketpp::connection_hdl hdl) {
        std::lock_guard<std::mutex> lock(connection_mutex);
        connections.insert(hdl);
    });

    server.set_close_handler([this](websocketpp::connection_hdl hdl) {
        std::lock_guard<std::mutex> lock(connection_mutex);
        connections.erase(hdl);
    });

    server.set_message_handler([](websocketpp::connection_hdl, Server::message_ptr) {
        // This server is broadcast-only; ignore incoming messages
    });
}

TelemetryServer::~TelemetryServer() {
    if (running) {
        stop();
    }
}

void TelemetryServer::run() {
    running = true;
    server.listen(9001);
    server.start_accept();

    server_thread = std::thread([this]() {
        server.run();
    });
}

void TelemetryServer::stop() {
    running = false;
    server.stop_listening();
    server.stop();
    if (server_thread.joinable()) {
        server_thread.join();
    }
}

void TelemetryServer::broadcast(const StateVector& state) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(4);
    ss << R"({"pos_x":)" << state(0)
       << R"(,"pos_y":)" << state(1)
       << R"(,"pos_z":)" << state(2)
       << R"(,"vel_x":)" << state(3)
       << R"(,"vel_y":)" << state(4)
       << R"(,"vel_z":)" << state(5)
       << R"(,"q_x":)" << state(6)
       << R"(,"q_y":)" << state(7)
       << R"(,"q_z":)" << state(8)
       << R"(,"q_w":)" << state(9)
       << R"(,"omega_x":)" << state(10)
       << R"(,"omega_y":)" << state(11)
       << R"(,"omega_z":)" << state(12)
       << "}";

    std::lock_guard<std::mutex> lock(connection_mutex);
    for (const auto& hdl : connections) {
        websocketpp::lib::error_code ec;
        server.send(hdl, ss.str(), websocketpp::frame::opcode::text, ec);
    }
}