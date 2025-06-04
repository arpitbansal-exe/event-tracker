cmake_minimum_required(VERSION 3.15)
message(STATUS "CMake version: ${CMAKE_VERSION}")

project(EventTracker LANGUAGES CXX)
message(STATUS "Configuring project: ${PROJECT_NAME}")

# Set C++ standard to C++17 and make it required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD} (required)")

# Enable folders in Visual Studio for better project organization
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
message(STATUS "Visual Studio folder organization enabled")

# Display build configuration info
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

# Add subdirectories - each contains its own CMakeLists.txt
message(STATUS "Adding subdirectories...")

add_subdirectory(external/curl)
message(STATUS "  - Added external/curl (HTTP client library)")

add_subdirectory(external/json)
message(STATUS "  - Added external/json (nlohmann JSON library)")

add_subdirectory(EventTrackerLib)
message(STATUS "  - Added EventTrackerLib (main library)")

add_subdirectory(TestApp)
message(STATUS "  - Added TestApp (test application)")

message(STATUS "EventTracker project configuration complete!")