/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** Registry.hpp
** Copyright [2025] <DeepestDungeonGroup>
*/

#ifndef INCLUDE_REGISTRY_HPP_
    #define INCLUDE_REGISTRY_HPP_

    #include <unordered_map>
    #include <typeindex>
    #include <functional>
    #include <any>
    #include <vector>
    #include <utility>
    #include <iostream>

    #include "SparseArray.hpp"
    #include "Entity.hpp"

namespace ECS {

class Registry {
 public:
    template <typename Component>
    SparseArray<Component>& registerComponent() {
        _component_array.insert_or_assign(
            std::type_index(typeid(Component)), SparseArray<Component>());
        _remover.push_back([](Registry& reg, const Entity& e) {
            auto &cmpts = reg.getComponents<Component>();
            if (e < cmpts.size() && cmpts[e].has_value())
                cmpts.erase(e);
        });
        return std::any_cast<SparseArray<Component>&>(
            _component_array.at(std::type_index(typeid(Component))));
    }

    template <typename Component>
    SparseArray<Component>& getComponents() {
        return std::any_cast<SparseArray<Component>&>(
            _component_array.at(std::type_index(typeid(Component))));
    }

    template <typename Component>
    SparseArray<Component> const & getComponents() const {
        return std::any_cast<SparseArray<Component>&>(
            _component_array.at(std::type_index(typeid(Component))));
    }

    void addSystem(const std::function<void(Registry&)>& f) {
        _systems.push_back(f);
    }

    void runSystems(void);

    void killEntity(const Entity& e);

    template <typename Component>
    void addComponent(const Entity& e, const Component& c) {
        try {
            std::any_cast<SparseArray<Component>&>(
                _component_array.at(
                    std::type_index(typeid(Component)))).insert_at(e, c);
        } catch (const std::bad_any_cast& e) {
            std::cout << e.what() << std::endl;
        }
    }

    template <typename Component>
    void addComponent(const Entity& e, Component&& c) {
        try {
            std::any_cast<SparseArray<Component>&>(
                _component_array.at(
                    std::type_index(typeid(Component)))).insert_at(
                        e, std::forward<Component>(c));
        } catch (const std::bad_any_cast& e) {
            std::cout << e.what() << std::endl;
        }
    }

    template <typename Component>
    void removeComponent(const Entity& e) {
        try {
            std::any_cast<SparseArray<Component>&>(
                _component_array.at(
                    std::type_index(typeid(Component)))).erase(e);
        } catch (const std::bad_any_cast& e) {
            std::cout << e.what() << std::endl;
        }
    }

 private:
    std::unordered_map<std::type_index, std::any> _component_array;
    std::vector<std::function<void(Registry&, const Entity&)>> _remover;

    std::vector<std::function<void(Registry&)>> _systems;
};

}  // namespace ECS

#endif  // INCLUDE_REGISTRY_HPP_
