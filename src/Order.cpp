export module DemoOrder;

import <memory>;
import <string>;

import DemoFactory;

export namespace DemoOrder
{
	struct Vector3
	{
		int x;
		int y;
		int z;
	};

	class Order
	{
	};

	class OrderFactory
	{
	public:
		virtual std::shared_ptr<Order> create() const = 0;
	};

	class OrderCreate : public Order
	{
	public:
		int id;
	};

	class OrderCreateFactory : public OrderFactory
	{
	public:
		std::shared_ptr<Order> create() const override
		{
			return std::make_shared<OrderCreate>();
		}
	};

	class OrderMove : public Order
	{
	public:
		Vector3 position;
	};

	class OrderMoveFactory : public OrderFactory
	{
	public:
		std::shared_ptr<Order> create() const override
		{
			return std::make_shared<OrderMove>();
		}
	};

	void run()
	{
		Factory<std::string, Order, OrderFactory> myFactory;

		myFactory.registerFactory("Create", std::make_shared<OrderCreateFactory>());
		myFactory.registerFactory("Move", std::make_shared<OrderCreateFactory>());

		auto order1 = myFactory.create("Create");
		auto order2 = myFactory.create("Create");

		auto order3 = myFactory.create("Move");
		auto order4 = myFactory.create("Move");
		auto order5 = myFactory.create("Move");
	}
}
