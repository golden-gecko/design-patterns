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
	public:
		Component(const std::string& name) : name(name)
		{
		}

		const std::string& getName() const
		{
			return name;
		}

	private:
		std::string name;
	};

	class Engine : public Component
	{
	public:
		Engine(const std::string& name) : Component(name)
		{
		}

		void start()
		{
		}
	};

	class Renderer : public Component
	{
	public:
		Renderer(const std::string& name) : Component(name)
		{
		}

		void render()
		{
		}
	};

	class Transform : public Component
	{
	public:
		Transform(const std::string& name) : Component(name)
		{
		}

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

	private:
		int id;
		std::string name;
	};

	class IPool
	{
	public:
		virtual ~IPool() = default;
		virtual std::string toString() const = 0;
	};

	template <class T>
	class Pool : public IPool
	{
	public:
		std::shared_ptr<T> get(int entity) const
		{
			auto item = entityToComponent.find(entity);

			if (item == entityToComponent.end())
			{
				return nullptr;
			}

			return components[item->second];
		}

		std::string toString() const override
		{
			std::stringstream str;

			for (const auto& component : components)
			{
				if (component)
				{
					str << "    " << component->getName() << '\n';
				}
			}

			str << '\n';

			for (const auto& ids : entityToComponent)
			{
				str << "    Entity " << ids.first << " : Component " << ids.second << '\n';
			}

			return str.str();
		}

	public:
		std::vector<std::shared_ptr<T>> components;
		std::map<int, int> entityToComponent;
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
		void add(Entity& entity, std::shared_ptr<T> component)
		{
			auto pool = getPool<T>();

			if (pool)
			{
				pool->entityToComponent.insert(std::make_pair(entity.getId(), static_cast<int>(pool->components.size())));
				pool->components.push_back(component);
			}
		}

		template <class T>
		std::shared_ptr<T> get(Entity& entity)
		{
			if (auto item = entities.find(entity.getId()); item == entities.end())
			{
				return nullptr;
			}

			auto pool = getPool<T>();

			if (pool == nullptr)
			{
				return nullptr;
			}

			return pool->get(entity.getId());
		}

		template <class T>
		void remove(Entity& entity)
		{
			if (auto item = entities.find(entity.getId()); item == entities.end())
			{
				return;
			}

			auto pool = getPool<T>();

			if (pool == nullptr)
			{
				return;
			}

			if (auto component = pool->entityToComponent.find(entity.getId()); component != pool->entityToComponent.end())
			{
				pool->components[component->second].reset();
				pool->entityToComponent.erase(component->first);
			}
		}

		std::string toString() const
		{
			std::ostringstream str;

			str << "Entities (" << entities.size() << "):\n";

			for (const auto& i : entities)
			{
				str << "  " << i.first << ' ' << i.second.getName() << '\n';
			}

			str << "\nComponents (" << components.size() << "):\n";

			for (const auto& i : components)
			{
				str << "  " << i.first << ' ' << '\n';
				str << i.second->toString() << '\n';
			}

			str << "\nComponent types (" << componentTypes.size() << "):\n";

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

		Entity car = coordinator.createEntity("Car");
		Entity plane = coordinator.createEntity("Plane");
		Entity truck = coordinator.createEntity("Truck");

		coordinator.add(car, std::make_shared<Engine>("Engine for car"));
		coordinator.add(car, std::make_shared<Renderer>("Renderer for car"));
		coordinator.add(car, std::make_shared<Transform>("Transform for car"));

		coordinator.add(plane, std::make_shared<Engine>("Engine for plane"));
		coordinator.add(plane, std::make_shared<Renderer>("Renderer for plane"));
		coordinator.add(plane, std::make_shared<Transform>("Transform for plane"));

		coordinator.add(truck, std::make_shared<Engine>("Engine for truck"));
		coordinator.add(truck, std::make_shared<Renderer>("Renderer for truck"));
		coordinator.add(truck, std::make_shared<Transform>("Transform for truck"));

		auto c1 = coordinator.get<Engine>(car);
		auto c2 = coordinator.get<Renderer>(car);
		auto c3 = coordinator.get<Transform>(car);

		auto c4 = coordinator.get<Engine>(truck);
		auto c5 = coordinator.get<Renderer>(truck);
		auto c6 = coordinator.get<Transform>(truck);

		std::cout << "--------------------------------------------------" << std::endl;
		std::cout << "--- After add ------------------------------------" << std::endl;
		std::cout << "--------------------------------------------------" << std::endl;
		std::cout << coordinator.toString() << std::endl;

		coordinator.remove<Engine>(car);
		coordinator.remove<Renderer>(plane);
		coordinator.remove<Transform>(truck);

		std::cout << "--------------------------------------------------" << std::endl;
		std::cout << "--- After remove ---------------------------------" << std::endl;
		std::cout << "--------------------------------------------------" << std::endl;
		std::cout << coordinator.toString() << std::endl;
	}
}
