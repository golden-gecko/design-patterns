export module DemoEvents;

import <functional>;
import <iostream>;
import <map>;
import <string_view>;

export namespace DemoEvents
{
	class Event
	{
	public:
		virtual std::string_view GetType() const = 0;

		virtual ~Event()
		{
		}
	};

	class EventStart : public Event
	{
	public:
		static constexpr std::string_view  Type = "EventStart";

		std::string_view GetType() const override
		{
			return Type;
		}
	};

	class EventStop : public Event
	{
	public:
		static constexpr std::string_view  Type = "EventStop";

		std::string_view GetType() const override
		{
			return Type;
		}
	};

	class Dispatcher
	{
	public:
		void subscribe(const std::string_view& type, std::function<void(const Event&)> handler)
		{
			observers[type].push_back(handler);
		}

		void post(const Event& event) const
		{
			if (auto observersForEventType = observers.find(event.GetType()); observersForEventType != observers.end())
			{
				for (auto& observer : observersForEventType->second)
				{
					observer(event);
				}
			}
		}

	private:
		std::map<std::string_view, std::vector<std::function<void(const Event&)>>> observers;
	};

	void onStart(const Event& event)
	{
		std::cout << "onStart" << std::endl;
	}

	void onStartWithDelay(const Event& event, int delay)
	{
		std::cout << "onStartWithDelay(" << delay << ")" << std::endl;
	}

	void onStop(const Event& event)
	{
		std::cout << "onStop" << std::endl;
	}

	void run()
	{
		Dispatcher dispatcher;

		dispatcher.subscribe(EventStart::Type, onStart);
		dispatcher.subscribe(EventStart::Type, std::bind(onStartWithDelay, std::placeholders::_1, 100));

		dispatcher.subscribe(EventStop::Type, onStop);

		dispatcher.post(EventStart());
		dispatcher.post(EventStop());

		dispatcher.post(EventStart());
		dispatcher.post(EventStop());
	}
}
