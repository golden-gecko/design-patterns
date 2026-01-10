export module DemoBuilder;

import <iostream>;
import <string>;

export namespace DemoBuilder
{
	class Computer
	{
	public:
		void setCPU(const std::string& cpu)
		{
			mCpu = cpu;
		}

		void setRAM(const std::string& ram)
		{
			mRam = ram;
		}

		void displayInfo() const
		{
			std::cout
				<< "Computer Configuration:"
				<< "\n  CPU: " << mCpu
				<< "\n  RAM: " << mRam
				<< std::endl;
		}

	private:
		std::string mCpu;
		std::string mRam;
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
			mComputer.setCPU("Gaming CPU");
		}

		void buildRAM() override
		{
			mComputer.setRAM("16GB DDR4");
		}

		Computer getResult() override
		{
			return mComputer;
		}

	private:
		Computer mComputer;
	};

	class ServerComputerBuilder : public Builder
	{
	public:
		void buildCPU() override
		{
			mComputer.setCPU("Server CPU");
		}

		void buildRAM() override
		{
			mComputer.setRAM("64GB DDR4");
		}

		Computer getResult() override
		{
			return mComputer;
		}

	private:
		Computer mComputer;
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
