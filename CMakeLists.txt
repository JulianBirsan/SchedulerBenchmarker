cmake_minimum_required(VERSION 3.14)
project(SchedulerBenchmarker)

include(FetchContent)
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

add_executable(scheduler_benchmarker src/main.cc)
target_link_libraries(scheduler_benchmarker PRIVATE nlohmann_json::nlohmann_json) 