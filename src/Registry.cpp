/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** Registry.cpp
** Copyright [2025] <DeepestDungeonGroup>
*/

#include "ECS/Registry.hpp"

namespace ECS {

void Registry::killEntity(const Entity& e) {
    for (auto& rm : _remover)
        rm(*this, e);
}

void Registry::runSystems(void) {
    for (const auto& sys : _systems)
        sys(*this);
}

}  // namespace ECS

