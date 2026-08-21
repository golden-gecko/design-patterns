cmake_minimum_required(VERSION 4.2)

project(design-patterns)

# Sources
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Target
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS NO
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
)
