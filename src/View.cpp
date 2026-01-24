export module DemoView;

import <algorithm>;
import <iostream>;
import <ranges>;
import <string>;
import <vector>;

export namespace DemoView
{
	template<class T>
	void print(T&& collection)
	{
		for (const auto& element : collection)
		{
			std::cout << element << ", ";
		}

		std::cout << std::endl;
	}

	template<class T>
	void printMap(T&& collection)
	{
		for (const auto& element : collection)
		{
			std::cout << std::get<0>(element) << ":" << std::get<1>(element) << ", ";
		}

		std::cout << std::endl;
	}

	void run()
	{
		std::vector<int> n { 2, 1, 4, 3, 6, 5, 8, 7 };
		std::vector<std::string> s { "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight" };

		// Sort.
		std::ranges::sort(n);

		// Print.
		print(n);

		// Print in reverse.
		print(std::views::reverse(n));

		// Print first 3.
		print(std::views::take(n, 3));

		// Print even.
		print(std::views::filter(n, [](const auto& x) {
			return x % 2 == 0;
		}));

		// Print first 4 in reverse.
		print(std::views::take(n, 4) | std::views::reverse);

		// Print zipped.
		printMap(std::views::zip(n, s));
	}
}
