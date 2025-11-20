/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** Entity.hpp
** Copyright [2025] <DeepestDungeonGroup>
*/

#pragma once

    #include <cuchar>

namespace ECS {

/**
 * @brief Entity type for the ECS
 * 
 * This type inherited from size_t type and is used in the ECS as index for
 * the SparseArrays. This is useful to locate every components 'linked' to
 * the entity
 */
typedef size_t Entity;

}  // namespace ECS
