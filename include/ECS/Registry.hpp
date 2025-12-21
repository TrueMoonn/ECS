/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** Registry.hpp
** Copyright [2025] <DeepestDungeonGroup>
*/

#pragma once

    #include <unordered_map>
    #include <typeindex>
    #include <functional>
    #include <any>
    #include <vector>
    #include <utility>
    #include <iostream>

    #include "ECS/DenseSA.hpp"
    #include "ECS/Entity.hpp"

    #define GET_DENSE_REF(m) std::any_cast<DenseSparseArray<Component>&>(\
        m.at(std::type_index(typeid(Component))))

namespace ECS {

class Registry {
 public:
    template <typename Component>
    DenseSparseArray<Component>& registerComponent() {
        _components.insert_or_assign(
            std::type_index(typeid(Component)), DenseSparseArray<Component>());
        // _remover.push_back([](Registry& reg, Entity e) {
        //     auto &cmpts = reg.getComponents<Component>();
        //     if (e < cmpts.size() && cmpts[e].has_value())
        //         cmpts.erase(e);
        // });
        return GET_DENSE_REF(_components);
    }

    template <typename Component>
    DenseSparseArray<Component>& getComponents() {
        return GET_DENSE_REF(_components);
    }

    template <typename Component>
    std::vector<SparseArray<std::size_t>>& getSparComponents() {
        return GET_DENSE_REF(_components).getSparComponents();
    }

    template <typename Component>
    const std::vector<SparseArray<std::size_t>>& getSparComponents() const {
        return GET_DENSE_REF(_components).getSparComponents();
    }

    template <typename Component>
    Component& getComponent(std::size_t index) {
        return GET_DENSE_REF(_components).getComponent(index);
    }

    template <typename Component>
    const Component& getComponent(std::size_t index) const {
        return GET_DENSE_REF(_components).getComponent(index);
    }

    template <typename Component>
    DenseSparseArray<Component> const & getComponents() const {
        return GET_DENSE_REF(_components);
    }

    void addSystem(const std::function<void(Registry&)>& f) {
        _systems.push_back(f);
    }

    void runSystems(void);

    void killEntity(Entity e);

    template <typename Component, typename... Args>
    void createComponent(Entity e, Args&&... args) {
        try {
            GET_DENSE_REF(_components).createComponent(
                e, std::forward<Args>(args)...);
        } catch (const std::bad_any_cast& e) {
            std::cout << e.what() << std::endl;
        }
    }

    template <typename Component>
    void addComponent(Entity e, const Component& c) {
        try {
            GET_DENSE_REF(_components).addComponent(e, c);
        } catch (const std::bad_any_cast& e) {
            std::cout << e.what() << std::endl;
        }
    }

    template <typename Component>
    void addComponent(Entity e, Component&& c) {
        try {
            GET_DENSE_REF(_components).addComponent(
                e, std::forward<Component>(c));
        } catch (const std::bad_any_cast& e) {
            std::cout << e.what() << std::endl;
        }
    }

    template <typename Component>
    void removeComponent(Entity e) {
        try {
            GET_DENSE_REF(_components).removeComponent(e);
        } catch (const std::bad_any_cast& e) {
            std::cout << e.what() << std::endl;
        }
    }

 private:
    std::unordered_map<std::type_index, std::any> _components;
    std::vector<std::function<void(Registry&, const Entity&)>> _remover;

    std::vector<std::function<void(Registry&)>> _systems;
};

}  // namespace ECS
