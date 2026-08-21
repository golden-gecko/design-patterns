#pragma once

#include <iostream>
#include <vector>

namespace DemoPool
{
	class Particle
	{
	public:
		void init(std::size_t newId)
		{
			id = newId;
		}

		std::size_t getId() const
		{
			return id;
		}

	private:
		std::size_t id = 0;
	};

	template<class T>
	class Pool
	{
	public:
		Pool(std::size_t size)
		{
			objects.resize(size);
		}

		Particle* create()
		{
			if (last_object < size())
			{
				objects[last_object].init(last_object);

				last_object += 1;

				return &(objects[last_object - 1]);
			}

			return nullptr;
		}

		void destroy(std::size_t id)
		{
			if (id < size())
			{
				objects[id] = objects[last_object - 1];

				last_object -= 1;
			}
		}

		void print()
		{
			for (std::size_t i = 0; i < last_object; i++)
			{
				std::cout << objects[i].getId() << std::endl;
			}
		}

		std::size_t size() const
		{
			return objects.size();
		}

	private:
		std::vector<T> objects;

		std::size_t last_object = 0;
	};

	void run()
	{
		Pool<Particle> pool(10);

		std::cout << "=== Create ===" << std::endl;

		pool.create();
		pool.create();
		pool.create();
		pool.print();

		std::cout << "=== Destroy ===" << std::endl;

		pool.destroy(1);
		pool.print();
	}
}
