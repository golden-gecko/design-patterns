#pragma once

#include <memory>
#include <string>

template <class Id, class BaseType, class FactoryType>
class Factory
{
public:
	void registerFactory(const Id& id, const std::shared_ptr<FactoryType>& factory)
	{
		factories.emplace(id, factory);
	}

	void unregisterFactory(const Id& id)
	{
		factories.erase(id);
	}

	std::shared_ptr<BaseType> create(const Id& id) const
	{
		if (auto factory = factories.find(id); factory != factories.end())
		{
			return factory->second->create();
		}

		return nullptr;
	}

private:
	std::map<Id, std::shared_ptr<FactoryType>> factories;
};

namespace DemoFactory
{
	class Vehicle
	{
	};

	class Car : public Vehicle
	{
	public:
		Car(int speed) : speed(speed)
		{
		}

	private:
		int speed;
	};

	class Plane : public Vehicle
	{
	};

	class VehicleFactory
	{
	public:
		virtual std::shared_ptr<Vehicle> create() const = 0;
	};

	class CarFactory : public VehicleFactory
	{
	public:
		std::shared_ptr<Vehicle> create() const override
		{
			return std::make_shared<Car>(20);
		}
	};

	class SuperCarFactory : public VehicleFactory
	{
	public:
		std::shared_ptr<Vehicle> create() const override
		{
			return std::make_shared<Car>(80);
		}
	};

	class PlaneFactory : public VehicleFactory
	{
	public:
		std::shared_ptr<Vehicle> create() const override
		{
			return std::make_shared<Plane>();
		}
	};

	class MyFactory : public Factory<std::string, Vehicle, VehicleFactory>
	{
	};

	void run()
	{
		MyFactory myFactory;

		myFactory.registerFactory("Car", std::make_shared<CarFactory>());
		myFactory.registerFactory("SuperCar", std::make_shared<SuperCarFactory>());

		myFactory.registerFactory("Plane", std::make_shared<PlaneFactory>());

		auto car1 = myFactory.create("Car");
		auto car2 = myFactory.create("Car");

		auto superCar1 = myFactory.create("SuperCar");
		auto superCar2 = myFactory.create("SuperCar");

		auto plane1 = myFactory.create("Plane");
		auto plane2 = myFactory.create("Plane");
	}
}
