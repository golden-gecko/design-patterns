cmake_minimum_required(VERSION 4.2)

project(design-patterns)

add_executable(
	design-patterns
	Builder.hpp
	Components.hpp
	Events.hpp
	Facade.hpp
	Factory.hpp
	Flyweight.hpp
	Main.cpp
	Orders.hpp
	Prototype.hpp
)

set_target_properties(design-patterns PROPERTIES
    CXX_EXTENSIONS NO
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
