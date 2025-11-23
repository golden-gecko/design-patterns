#pragma once

#include <iostream>
#include <string>

namespace DemoBuilder
{
	class Computer
	{
	public:
		std::string cpu;
		std::string ram;

		void setCPU(const std::string& cpu)
		{
			this->cpu = cpu;
		}

		void setRAM(const std::string& ram)
		{
			this->ram = ram;
		}

		void displayInfo() const
		{
			std::cout
				<< "Computer Configuration:"
				<< "\n  CPU: " << cpu
				<< "\n  RAM: " << ram
				<< std::endl;
		}
	};

	class Builder
	{
	public:
		virtual void buildCPU() = 0;
		virtual void buildRAM() = 0;
		virtual Computer getResult() = 0;
	};

	class GamingComputerBuilder : public Builder
	{
	public:
		void buildCPU() override
		{
			computer.setCPU("Gaming CPU");
		}

		void buildRAM() override
		{
			computer.setRAM("16GB DDR4");
		}

		Computer getResult() override
		{
			return computer;
		}

	private:
		Computer computer;
	};

	class ServerComputerBuilder : public Builder
	{
	public:
		void buildCPU() override
		{
			computer.setCPU("Server CPU");
		}

		void buildRAM() override
		{
			computer.setRAM("64GB DDR4");
		}

		Computer getResult() override
		{
			return computer;
		}

	private:
		Computer computer;
	};

	class ComputerDirector
	{
	public:
		void construct(Builder& builder)
		{
			builder.buildCPU();
			builder.buildRAM();
		}
	};

	void run()
	{
		GamingComputerBuilder gamingBuilder;
		ServerComputerBuilder serverBuilder;

		ComputerDirector director;

		director.construct(gamingBuilder);
		director.construct(serverBuilder);

		Computer gamingComputer = gamingBuilder.getResult();
		Computer serverComputer = serverBuilder.getResult();

		gamingComputer.displayInfo();
		serverComputer.displayInfo();
	}
}
