#pragma once

namespace DemoComponents
{
	class Engine
	{
	};

	class Renderer
	{
	};

	class Transform
	{
	};

	class Car
	{
	public:
		template <class T>
		void add()
		{
		}
	};

	void run()
	{
		Car car;

		car.add<Engine>();
		car.add<Renderer>();
		car.add<Transform>();
	}
}
