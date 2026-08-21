#pragma once

#include <iostream>
#include <string>
#include <utility>

namespace DemoMove
{
	class Vehicle
	{
	public:
		Vehicle(const std::string& name, int speed) :
			name{ name }, speed{ speed }
		{
		}

		Vehicle(const Vehicle& other) :
			name{ other.name }, speed{ other.speed }
		{
		}

		Vehicle(Vehicle&& other) :
			name{ std::move(other.name) }, speed{ other.speed }
		{
		}

	public:
		std::string name;
		int speed{ 0 };
	};

	void run()
	{
		Vehicle v1("car", 10);
		Vehicle v2 = std::move(v1);

		std::cout << "name: _" << v1.name << "_ speed: _" << v1.speed << "_" << std::endl;
		std::cout << "name: _" << v2.name << "_ speed: _" << v2.speed << "_" << std::endl;
	}
}
