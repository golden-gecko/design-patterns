export module DemoLambda;

import <algorithm>;
import <iostream>;
import <string>;
import <vector>;

export namespace DemoLambda
{
	class MyLambda
	{
	public:
		int operator()(int a, int b) const
		{
			return a + b;
		}
	};

	void custom()
	{
		MyLambda myLambda;

		std::cout << myLambda(1, 1) << std::endl;
		std::cout << myLambda(2, 3) << std::endl;
	}

	void sort()
	{
		auto print = [](const auto& collection)
		{
			for (const auto& element : collection)
			{
				std::cout << element << ", ";
			}

			std::cout << std::endl;
		};

		auto byLength = [](const auto& a, const auto& b)
		{
			return a.size() < b.size();
		};

		std::vector<std::string> words = { "city", "apple", "dog", "cat", "computer" };

		// Print.
		print(words);

		// Sort alphabetically.
		std::sort(words.begin(), words.end());

		print(words);

		// Sort by length.
		std::sort(words.begin(), words.end(), byLength);

		print(words);
	}

	void run()
	{
		custom();
		sort();
	}
}
