cmake_minimum_required(VERSION 3.10)

# Project name and settings
project(uart_flash_programmer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set cross compilation target
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall")

# Set release and debug profile
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG -flto")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/asio)

# Source files
set(SOURCES
    ${PROJECT_NAME}.cpp
)
file(GLOB_RECURSE SOURCE_FILES source/*.cpp)
list(APPEND SOURCES ${SOURCE_FILES})

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add compilation flag
## For GCC/Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -w)
    target_compile_options(${PROJECT_NAME} PRIVATE -D_GLIBCXX_USE_NANOSLEEP -pthread)
    # Link libraries 
    target_link_libraries(${PROJECT_NAME} PUBLIC pthread)
## For MSVC
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /w)
    target_compile_options(${PROJECT_NAME} PRIVATE /D_GLIBCXX_USE_NANOSLEEP)
    target_compile_options(${PROJECT_NAME} PRIVATE /_CRT_SECURE_NO_DEPRECATE)
endif()

