#include <iostream>

#include "Adapter.hpp"
#include "Builder.hpp"
#include "Component.hpp"
#include "Event.hpp"
#include "Facade.hpp"
#include "Factory.hpp"
#include "Flyweight.hpp"
#include "Lambda.hpp"
#include "Move.hpp"
#include "Order.hpp"
#include "Pool.hpp"
#include "Prototype.hpp"
#include "Thread.hpp"
#include "View.hpp"

int main()
{
	DemoAdapter::run();
	DemoBuilder::run();
	DemoComponent::run();
	DemoEvent::run();
	DemoFacade::run();
	DemoFlyweight::run();
	DemoFactory::run();
	DemoMove::run();
	DemoLambda::run();
	DemoOrder::run();
	DemoPool::run();
	DemoPrototype::run();
	// DemoThread::run();
	DemoView::run();

	std::cin.get();

	return 0;
}
