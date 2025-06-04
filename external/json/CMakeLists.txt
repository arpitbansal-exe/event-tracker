cmake_minimum_required(VERSION 3.15)
include(FetchContent)

message(STATUS "Configuring nlohmann/json library...")

# Disable nlohmann/json tests and other unnecessary features
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
set(JSON_MultipleHeaders OFF CACHE INTERNAL "")

# Fetch nlohmann/json library
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)
message(STATUS "Fetching nlohmann/json v3.11.3...")

# Make nlohmann/json available
FetchContent_MakeAvailable(nlohmann_json)

# Create a custom target to make nlohmann/json visible in Visual Studio
add_custom_target(nlohmann_json_headers
    COMMENT "nlohmann/json header-only library"
    SOURCES ${nlohmann_json_SOURCE_DIR}/single_include/nlohmann/json.hpp
)

# Organize the custom target into External/json folder
set_target_properties(nlohmann_json_headers PROPERTIES 
    FOLDER "External/json"
    PROJECT_LABEL "nlohmann_json (headers)"
)

message(STATUS "nlohmann/json configuration complete!")