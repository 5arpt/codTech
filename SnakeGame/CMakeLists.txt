cmake_minimum_required(VERSION 3.17)
project(nibbles)

set(CMAKE_CXX_STANDARD 20)

# Set the output folder for the .exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add your source files
add_executable(nibbles src/main.cpp src/engine.cpp headers/engine.hpp src/draw.cpp src/input.cpp src/SnakeSection.cpp headers/SnakeSection.hpp src/update.cpp src/apple.cpp headers/apple.hpp src/wall.cpp headers/wall.hpp
        assets/sounds/eat.cpp
)

# Include SFML headers
include_directories(headers C:/SFML/include)

# Link SFML libraries manually
target_link_directories(nibbles PRIVATE C:/SFML/lib)
target_link_libraries(nibbles
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-system
)

# Copy assets folder (e.g., images, fonts, sounds)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy required SFML + MinGW DLLs to the .exe folder
if(WIN32)
    file(GLOB SFML_DLLS "C:/SFML/bin/*.dll")
    file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    file(GLOB MINGW_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DLLS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
