export module DemoComponent;

import <bitset>;
import <iostream>;
import <map>;
import <sstream>;
import <vector>;

export namespace DemoComponent
{
	using ComponentType = std::uint8_t;
	const ComponentType MAX_COMPONENTS = 32;
	using Signature = std::bitset<MAX_COMPONENTS>;

	class Component
	{
	};

	class Engine : public Component
	{
	public:
		void start()
		{
		}
	};

	class Renderer : public Component
	{
	public:
		void render()
		{
		}
	};

	class Transform : public Component
	{
	public:
		void move()
		{
		}
	};

	class Entity
	{
	public:
		Entity(int id, const std::string& name) : id(id), name(name)
		{
		}

		int getId() const
		{
			return id;
		}

		const std::string& getName() const
		{
			return name;
		}

		template <class T>
		void add()
		{
		}

		template <class T>
		T get()
		{
			return T();
		}

	private:
		int id;
		std::string name;
	};

	class IPool
	{
	public:
		virtual ~IPool() = default;
	};

	template <class T>
	class Pool : public IPool
	{
	public:
		std::vector<T> components;
		std::map<int, int> entityToIndex;
	};

	class Coordinator
	{
	public:
		Entity createEntity(const std::string& name)
		{
			Entity entity(entityCount, name);

			entities.insert(std::make_pair(entityCount, entity));

			entityCount += 1;

			return entity;
		}

		template <class T>
		void registerComponent()
		{
			std::string_view typeName = typeid(T).name();

			components[typeName] = std::make_shared<Pool<T>>();
			componentTypes[typeName] = componentCount;

			componentCount += 1;
		}

		template <class T>
		std::shared_ptr<Pool<T>> getPool() const
		{
			if (auto pool = components.find(std::string_view(typeid(T).name())); pool != components.end())
			{
				return std::dynamic_pointer_cast<Pool<T>>(pool->second);
			}

			return nullptr;
		}

		template <class T>
		void add(Entity& entity, T component)
		{
			auto pool = getPool<T>();

			if (pool)
			{
				pool->components.push_back(component);
			}
		}

		template <class T>
		void remove(Entity& entity)
		{
		}

		std::string toString() const
		{
			std::ostringstream str;

			str << "Entities (" << entities.size() << "):\n";

			for (const auto& i : entities)
			{
				str << "  " << i.first << ' ' << i.second.getName() << '\n';
			}

			str << "Components (" << components.size() << "):\n";

			for (const auto& i : components)
			{
				str << "  " << i.first << '\n';
			}

			str << "Component types (" << componentTypes.size() << "):\n";

			for (const auto& i : componentTypes)
			{
				str << "  " << i.first << ' ' << static_cast<int>(i.second) << '\n';
			}

			return str.str();
		}

	private:
		int entityCount = 0;
		ComponentType componentCount = 0;

		std::map<int, Entity> entities;
		std::map<std::string_view, std::shared_ptr<IPool>> components;
		std::map<std::string_view, ComponentType> componentTypes;
	};

	void run()
	{
		Coordinator coordinator;

		coordinator.registerComponent<Engine>();
		coordinator.registerComponent<Renderer>();
		coordinator.registerComponent<Transform>();

		std::cout << coordinator.toString() << std::endl;

		Entity car = coordinator.createEntity("Car");
		Entity truck = coordinator.createEntity("Truck");

		std::cout << coordinator.toString() << std::endl;

		coordinator.add(car, Engine());
		coordinator.add(car, Renderer());
		coordinator.add(car, Transform());

		coordinator.add(truck, Renderer());
		coordinator.add(truck, Transform());
		
		car.get<Engine>().start();
		car.get<Renderer>().render();
		car.get<Transform>().move();

		truck.get<Engine>().start();
		truck.get<Renderer>().render();
		truck.get<Transform>().move();
	}
}
