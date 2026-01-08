/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** Registry.cpp
*/

#include "ECS/Registry.hpp"

namespace ECS {

void Registry::killEntity(Entity e) {
    for (auto& rm : _remover)
        rm(*this, e);
}

void Registry::runSystems(void) {
    for (const auto& [name, sys] : _systems)
        sys(*this);
}

void addSystem(const std::string& name,
    const std::function<void(Registry&)>& f) {
    _systems.emplace_back(name, f);
}

int getSystem(const std::string& name) {
    for (int i = 0; i < _systems; ++i)
        if (!name.compare(_systems[i].second))
            return i;
    return -1;
}

void removeSystem(const std::string& name) {
    auto idx = getSystem(name);
    if (idx < 0)
        return;
    std::erease(_systems, _systems[idx]);
}

}  // namespace ECS
