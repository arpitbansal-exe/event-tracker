cmake_minimum_required(VERSION 3.15)
include(FetchContent)
message(STATUS "Configuring Dependency- Curl ...")
# Curl options
set(BUILD_CURL_EXE OFF)
set(BUILD_SHARED_LIBS OFF)
set(HTTP_ONLY ON)
set(CURL_DISABLE_LDAP ON)
set(CURL_USE_OPENSSL OFF)
set(CURL_USE_SCHANNEL ON)
set(CURL_USE_WINSSL OFF)

set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(BUILD_CURL_EXE OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(HTTP_ONLY ON CACHE BOOL "" FORCE)
set(CURL_DISABLE_LDAP ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  curl
  GIT_REPOSITORY https://github.com/curl/curl.git
  GIT_TAG curl-8_7_1
)

FetchContent_MakeAvailable(curl)

# Organize curl projects into a folder in Visual Studio
set_target_properties(libcurl_static PROPERTIES FOLDER "External/curl")
set_target_properties(libcurl_object PROPERTIES FOLDER "External/curl")

# Hide curl utility targets if they exist
if(TARGET curl_uninstall)
    set_target_properties(curl_uninstall PROPERTIES FOLDER "External/curl")
endif()

if(TARGET man)
    set_target_properties(man PROPERTIES FOLDER "External/curl")
endif()

if(TARGET opts-man)
    set_target_properties(opts-man PROPERTIES FOLDER "External/curl")
endif()

# Set folder for any other curl-related targets that might be created
get_property(all_targets DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
foreach(target ${all_targets})
    if(TARGET ${target})
        get_target_property(target_type ${target} TYPE)
        if(NOT target_type STREQUAL "INTERFACE_LIBRARY")
            set_target_properties(${target} PROPERTIES FOLDER "External/curl")
        endif()
    endif()
endforeach()