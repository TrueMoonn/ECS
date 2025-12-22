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
        _remover.push_back([](Registry& reg, Entity e) {
            reg.getComponents<Component>().removeComponent(e);
        });
        return GET_DENSE_REF(_components);
    }

    template <typename Component>
    DenseSparseArray<Component>& getComponents() {
        return GET_DENSE_REF(_components);
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
        GET_DENSE_REF(_components).createComponent(
            e, std::forward<Args>(args)...);
    }

    template <typename Component>
    void addComponent(Entity e, const Component& c) {
        GET_DENSE_REF(_components).addComponent(e, c);
}

    template <typename Component>
    void addComponent(Entity e, Component&& c) {
        GET_DENSE_REF(_components).addComponent(
            e, std::forward<Component>(c));
    }

    template <typename Component>
    void removeComponent(Entity e) {
        GET_DENSE_REF(_components).removeComponent(e);
    }

 private:
    std::unordered_map<std::type_index, std::any> _components;
    std::vector<std::function<void(Registry&, const Entity&)>> _remover;

    std::vector<std::function<void(Registry&)>> _systems;
};

}  // namespace ECS
