#pragma once

#include <memory>
#include <string>
#include "Factory.hpp"

namespace DemoOrder
{
	class Order
	{
	public:
		virtual ~Order() = default;
	};

	class OrderFactory
	{
	public:
		virtual std::shared_ptr<Order> create() const = 0;
	};

	class OrderCreate : public Order
	{
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

		std::shared_ptr<Order> order1 = myFactory.create("Create");
		std::shared_ptr<Order> order2 = myFactory.create("Create");

		std::shared_ptr<Order> order3 = myFactory.create("Move");
		std::shared_ptr<Order> order4 = myFactory.create("Move");
		std::shared_ptr<Order> order5 = myFactory.create("Move");
	}
}
