#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <functional>

// ====== STRUCTS ======

struct IComponent
{
    IComponent() = default;
    virtual ~IComponent() = default;
};

// ====== ECS_Instance ======

struct ECS_Instance
{
    std::unordered_map<std::type_index, std::unique_ptr<IComponent>> components;

    std::unordered_map<std::string, std::function<void(ECS_Instance &)>> systems;

    // ====== COMPONENTS ======

    /// @brief Adds a component to a entity
    /// @tparam T
    /// @tparam ...Args
    /// @param ...args
    /// @return typeid
    template <typename T, typename... Args>
    std::type_index add_component(Args &&...args)
    {
        components[typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);

        return typeid(T);
    }

    /// @brief Gets a component to a entity
    /// @tparam T
    /// @return component || nullptr
    template <typename T>
    T *get_component()
    {
        auto it = components.find(typeid(T));

        if (it != components.end())
            return static_cast<T *>(it->second.get());

        return nullptr;
    }

    /// @brief Removes a component to a entity
    /// @param typeID
    void remove_component(std::type_index typeID)
    {
        components.erase(typeID);
    }

    // ====== SYSTEMS ======

    /// @brief Create a system for the entity
    /// @tparam Function
    /// @param system_name
    /// @param function
    template <typename Function>
    void create_system(std::string system_name, Function &&function)
    {
        systems.emplace(system_name, std::forward<Function>(function));
    }

    /// @brief Run a specific system
    /// @param system_name
    void run_system(std::string system_name)
    {
        auto it = systems.find(system_name);

        if (it != systems.end())
            it->second(*this);
    }

    /// @brief Run all systems
    void run_systems()
    {
        for (auto &sys : systems)
        {
            sys.second(*this);
        }
    }

    /// @brief Removes a specific system
    /// @param system_name: The value returned by create_system
    void remove_system(std::string system_name)
    {
        systems.erase(system_name);
    }
};

// ====== ecs_class ======

class ecs_class
{
public:
    static int current_id;

    static std::unordered_map<int, ECS_Instance> ecs_storage;

public:
    // ====== ENTITY ======

    /// @brief Creates a new entity
    /// @return int: The entity ID
    static int create_entity()
    {
        int id = current_id++;
        ecs_storage.emplace(id, ECS_Instance{});
        return id;
    }

    /// @brief Return all data related to the entity
    /// @param id
    /// @return ECS_Instance
    static ECS_Instance &get_entity(int id)
    {
        return ecs_storage.at(id);
    }

    /// @brief Removes a specific entity
    /// @param id
    static void remove_entity(int id)
    {
        ecs_storage.erase(id);
    }

    // ====== SYSTEMS ======

    /// @brief Run all systems on all entities
    static void run_all()
    {
        for (auto &[id, instance] : ecs_storage)
        {
            instance.run_systems();
        }
    }

    /// @brief Run all systems with a specific name
    /// @param system_name
    static void run_specific_all(const std::string &system_name = "")
    {
        for (auto &[id, instance] : ecs_storage)
        {
            if (system_name.empty())
                instance.run_systems();
            else
                instance.run_system(system_name);
        }
    }
};

int ecs_class::current_id = 0;
std::unordered_map<int, ECS_Instance> ecs_class::ecs_storage;