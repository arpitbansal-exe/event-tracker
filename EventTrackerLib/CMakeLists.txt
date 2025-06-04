project(EventTrackerLib)
message(STATUS "Configuring EventTrackerLib...")
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")

add_library(EventTracker STATIC ${SOURCES})
target_include_directories(EventTracker PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)
message(STATUS "Linked CURL::libcurl,nlohmann_json  privately to EventTracker")
target_link_libraries(EventTracker PRIVATE 
    CURL::libcurl
    nlohmann_json::nlohmann_json
)

# Define DEBUG macro for debug builds
target_compile_definitions(EventTracker PRIVATE 
    $<$<CONFIG:Debug>:DEBUG>
)
# Let folder structure match actual layout
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src FILES ${SOURCES})
message(STATUS "Configuring EventTrackerLib DONE!!!")