#pragma once

#include <iostream>

namespace DemoPrototype
{
	class Shape
	{
	public:
		virtual Shape* clone() const = 0;
	};

	class Circle : public Shape
	{
	public:
		float radius;

		Circle(float radius) : radius(radius)
		{
		}

		Circle(const Circle& other) : radius(other.radius)
		{
		}

		Circle* clone() const override
		{
			return new Circle(*this);
		}
	};

	class Square : public Shape
	{
	public:
		float size;

		Square(float size) : size(size)
		{
		}

		Square(const Square& other) : size(other.size)
		{
		}

		Square* clone() const override
		{
			return new Square(*this);
		}
	};

	void run()
	{
		auto circle1 = new Circle(10.0f);
		auto circle2 = new Circle(20.0f);
		auto circle3 = circle1->clone();

		auto square1 = new Square(100.0f);
		auto square2 = new Square(200.0f);
		auto square3 = square1->clone();

		std::cout << "Radius #1: " << circle1->radius << std::endl;
		std::cout << "Radius #2: " << circle2->radius << std::endl;
		std::cout << "Radius #3: " << circle3->radius << std::endl;

		std::cout << std::endl;

		std::cout << "Square #1: " << square1->size << std::endl;
		std::cout << "Square #2: " << square2->size << std::endl;
		std::cout << "Square #3: " << square3->size << std::endl;

		delete circle1;
		delete circle2;
		delete circle3;

		delete square1;
		delete square2;
		delete square3;
	}
}
