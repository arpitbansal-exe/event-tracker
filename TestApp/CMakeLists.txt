
# Create BasicApp executable
message(STATUS "  - Create BasicApp executabe")
add_executable(BasicApp BasicApp/main.cpp)
target_link_libraries(BasicApp PRIVATE EventTracker)
target_include_directories(BasicApp PRIVATE 
    ${PROJECT_SOURCE_DIR}/EventTrackerLib/src/include
)

# Create LoadApp executable  
message(STATUS "  - Create LoadApp executable  ")
add_executable(LoadApp LoadApp/main.cpp)
target_link_libraries(LoadApp PRIVATE EventTracker)
target_include_directories(LoadApp PRIVATE 
    ${PROJECT_SOURCE_DIR}/EventTrackerLib/src/include
)

# Group both executables under "TestApp" folder in Visual Studio
set_target_properties(BasicApp LoadApp PROPERTIES
    FOLDER "TestApp"
)