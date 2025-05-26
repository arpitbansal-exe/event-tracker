add_executable(TestApp main.cpp)

target_link_libraries(TestApp PRIVATE EventTracker)

target_include_directories(TestApp PRIVATE
    ${PROJECT_SOURCE_DIR}/EventTrackerLib/src/include
)