export module DemoPrototype;

import <iostream>;

export namespace DemoPrototype
{
	class Shape
	{
	public:
		virtual Shape* clone() const = 0;
	};

	class Circle : public Shape
	{
	public:
		Circle(float radius) : mRadius(radius)
		{
		}

		Circle(const Circle& other) : mRadius(other.mRadius)
		{
		}

		Circle* clone() const override
		{
			return new Circle(*this);
		}

		float getRadius() const
		{
			return mRadius;
		}

	private:
		float mRadius;
	};

	class Square : public Shape
	{
	public:
		Square(float size) : mSize(size)
		{
		}

		Square(const Square& other) : mSize(other.mSize)
		{
		}

		Square* clone() const override
		{
			return new Square(*this);
		}

		float getSize() const
		{
			return mSize;
		}

	private:
		float mSize;
	};

	void run()
	{
		Circle* circle1 = new Circle(10.0f);
		Circle* circle2 = new Circle(20.0f);
		Circle* circle3 = circle1->clone();

		Square* square1 = new Square(100.0f);
		Square* square2 = new Square(200.0f);
		Square* square3 = square1->clone();

		std::cout << "Radius #1: " << circle1->getRadius() << std::endl;
		std::cout << "Radius #2: " << circle2->getRadius() << std::endl;
		std::cout << "Radius #3: " << circle3->getRadius() << std::endl;

		std::cout << std::endl;

		std::cout << "Square #1: " << square1->getSize() << std::endl;
		std::cout << "Square #2: " << square2->getSize() << std::endl;
		std::cout << "Square #3: " << square3->getSize() << std::endl;

		delete circle1;
		delete circle2;
		delete circle3;

		delete square1;
		delete square2;
		delete square3;
	}
}
