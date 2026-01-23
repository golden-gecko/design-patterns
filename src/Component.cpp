export module DemoComponent;

import <bitset>;
import <iostream>;
import <map>;
import <sstream>;
import <vector>;

export namespace DemoComponent
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
