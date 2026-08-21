#pragma once

#include <iostream>
#include <string>
#include <syncstream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstdlib>

namespace DemoThread
{
	std::vector<int> numbers;
	std::mutex numbersMutex;

	void producer(const std::string& name)
	{
		while (true)
		{
			{
				// std::osyncstream(std::cout) << name << ": trying to lock" << std::endl;

				std::lock_guard<std::mutex> lock(numbersMutex);

				// std::osyncstream(std::cout) << name << ": locked" << std::endl;

				numbers.push_back(1 + std::rand() % 100);

				std::osyncstream(std::cout) << name << ": size: " << numbers.size() << std::endl;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1000 + std::rand() % 1000));
		}
	}

	void consumer(const std::string& name)
	{
		while (true)
		{
			{
				// std::osyncstream(std::cout) << name << ": trying to lock" << std::endl;

				std::lock_guard<std::mutex> lock(numbersMutex);

				// std::osyncstream(std::cout) << name << ": locked" << std::endl;

				if (numbers.size() > 0)
				{
					numbers.pop_back();
				}

				std::osyncstream(std::cout) << name << ": size: " << numbers.size() << std::endl;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(500 + std::rand() % 500));
		}
	}

	void run()
	{
		std::thread p1(producer, "add       1");
		std::thread c1(consumer, "substract 1");
		std::thread c2(consumer, "substract 2");
		std::thread c3(consumer, "substract 3");
		std::thread c4(consumer, "substract 4");

		p1.join();
		c1.join();
		c2.join();
		c3.join();
		c4.join();
	}
}
