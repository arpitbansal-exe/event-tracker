include(FetchContent)
# Fetch curl
# Allow curl to build as a static lib and skip unused parts
set(BUILD_CURL_EXE OFF)
set(BUILD_SHARED_LIBS OFF)
set(HTTP_ONLY ON)
set(CURL_DISABLE_LDAP ON)
set(CURL_USE_OPENSSL OFF)
set(CURL_USE_SCHANNEL OFF)
set(CURL_USE_WINSSL OFF)
set(BUILD_CURL_EXE OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(HTTP_ONLY ON CACHE BOOL "" FORCE)
set(CURL_DISABLE_LDAP ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  curl
  GIT_REPOSITORY https://github.com/curl/curl.git
  GIT_TAG curl-8_7_1
)
FetchContent_MakeAvailable(curl)

add_library(EventTracker STATIC
    src/EventTracker.cpp
    src/EventBuilder.cpp
	src/Transporter.cpp
)

target_include_directories(EventTracker PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

# Link with curl
target_link_libraries(EventTracker PRIVATE CURL::libcurl)