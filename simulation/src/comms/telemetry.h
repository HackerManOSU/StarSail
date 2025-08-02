#pragma once

#define ASIO_STANDALONE

#include <asio.hpp>
#include <string>
#include <thread>
#include <set>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "../common.h"

class TelemetryServer {
public:
    TelemetryServer();
    ~TelemetryServer();
    void run();
    void stop();
    void broadcast(const StateVector& state);

private:
    using Server = websocketpp::server<websocketpp::config::asio>;

    Server server;
    std::thread server_thread;
    std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> connections;
    std::mutex connection_mutex;
    bool running = false;
};