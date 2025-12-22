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
    for (const auto& sys : _systems)
        sys(*this);
}

}  // namespace ECS
