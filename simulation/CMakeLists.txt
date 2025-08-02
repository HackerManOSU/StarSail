cmake_minimum_required(VERSION 3.10)
project(StarSailSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Threads REQUIRED)

# Fetch libraries
include(FetchContent)
FetchContent_Declare(
    Eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(Eigen)

FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-28-0
)
FetchContent_MakeAvailable(asio)

FetchContent_Declare(
  websocketpp
  GIT_REPOSITORY https://github.com/zaphoyd/websocketpp.git
  GIT_TAG master
)
FetchContent_MakeAvailable(websocketpp)

add_executable(starsail_sim 
    src/main.cpp
    src/dynamics.cpp
    src/integrator.cpp
    src/GNC/control.cpp
    src/comms/telemetry.cpp
)

target_include_directories(starsail_sim PRIVATE 
    ${eigen_SOURCE_DIR}
    ${asio_SOURCE_DIR}/asio/include
    ${websocketpp_SOURCE_DIR}
)

target_link_libraries(starsail_sim PRIVATE 
    Eigen3::Eigen 
    Threads::Threads
)