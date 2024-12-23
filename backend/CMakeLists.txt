cmake_minimum_required(VERSION 3.10)
project(number_guessing_game)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Crow
include(FetchContent)
FetchContent_Declare(
    Crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow
    GIT_TAG v1.0+5
)
FetchContent_MakeAvailable(Crow)

# Add executable
add_executable(number_guessing_game src/main.cpp)

# Link libraries and include directories
target_link_libraries(number_guessing_game PRIVATE Crow::Crow)
target_include_directories(number_guessing_game PRIVATE ${crow_SOURCE_DIR}/include)

# If on Windows, add these definitions
if(WIN32)
    target_compile_definitions(number_guessing_game PRIVATE
        _CRT_SECURE_NO_WARNINGS
        _WIN32_WINNT=0x0601
    )
endif() 