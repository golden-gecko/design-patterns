export module DemoFlyweight;

import <iostream>;
import <map>;
import <memory>;
import <string>;

export namespace DemoFlyweight
{
	class VehicleType
	{
	public:
		VehicleType(const std::string& name, const std::string& color) :
			name(name), color(color)
		{
		}

		std::string name;
		std::string color;
	};

	class Vehicle
	{
	public:
		Vehicle(const std::shared_ptr<VehicleType>& vehicleType) :
			vehicleType(vehicleType)
		{
		}

		int x;
		int y;

		std::shared_ptr<VehicleType> vehicleType;
	};

	class VehicleFactory
	{
	public:
		void registerType(const std::string& type, const std::shared_ptr<VehicleType>& vehicleType)
		{
			vehicleTypes[type] = vehicleType;
		}

		std::shared_ptr<Vehicle> create(const std::string& type)
		{
			return std::make_shared<Vehicle>(vehicleTypes[type]);
		}

	private:
		std::map<std::string, std::shared_ptr<VehicleType>> vehicleTypes;
	};

	void run()
	{
		std::shared_ptr<VehicleType> red = std::make_shared<VehicleType>("Fast", "Red");
		std::shared_ptr<VehicleType> yellow = std::make_shared<VehicleType>("Slow", "Yellow");

		std::shared_ptr<VehicleFactory> vehicleFactory = std::make_shared<VehicleFactory>();

		vehicleFactory->registerType("red", red);
		vehicleFactory->registerType("yellow", yellow);

		std::shared_ptr<Vehicle> v1 = vehicleFactory->create("red");
		std::shared_ptr<Vehicle> v2 = vehicleFactory->create("red");

		std::shared_ptr<Vehicle> v3 = vehicleFactory->create("yellow");
		std::shared_ptr<Vehicle> v4 = vehicleFactory->create("yellow");

		std::cout << v1->vehicleType->name << " " << v1->vehicleType->color << std::endl;
		std::cout << v2->vehicleType->name << " " << v2->vehicleType->color << std::endl;

		std::cout << v3->vehicleType->name << " " << v3->vehicleType->color << std::endl;
		std::cout << v4->vehicleType->name << " " << v4->vehicleType->color << std::endl;
	}
}
