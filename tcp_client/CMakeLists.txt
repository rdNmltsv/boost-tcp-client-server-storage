cmake_minimum_required(VERSION 3.24)

project(tcp_client
		VERSION 0.1
		DESCRIPTION "Client for TCP server based on boost.asio"
		LANGUAGES CXX
)

if(NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file (GLOB SOURCES source/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# START Boost
include(FetchContent)

message("Downloading boost. Please, wait a while!")
FetchContent_Declare(
	boost
	URL https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.zip
	URL_HASH SHA256=e34756f63abe8ac34b35352743f17d061fcc825969a2dd8458264edb38781782
	FIND_PACKAGE_ARGS NAMES Boost
)

message("Boost downloaded. Populating...")
FetchContent_MakeAvailable(boost)
message("Boost succesfully populated.")
FetchContent_GetProperties(boost SOURCE_DIR BOOST_DIR)
target_include_directories(${PROJECT_NAME} PUBLIC ${BOOST_DIR})
# END Boost

# START nlohmann_json
FetchContent_Declare(
    json 
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)

FetchContent_MakeAvailable(json)
message("Nlohmann_json populated.")

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
# END nlohmann_json

target_link_libraries(${PROJECT_NAME}
    PRIVATE
		ws2_32
        wsock32
)
