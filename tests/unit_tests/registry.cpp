/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** registry.cpp
** Copyright [2025] <DeepestDungeonGroup>
*/

#include <gtest/gtest.h>

#include "ECS/Registry.hpp"

void test_system_add_one(ECS::Registry& reg) {
    auto &simple_int = reg.getComponents<int>();

    for (ECS::Entity e = 0; e < simple_int.size(); ++e) {
        if (simple_int[e].has_value())
            simple_int[e].value() += 1;
    }
}

TEST(registry, register_component) {
    ECS::Registry reg = {};
    auto result = reg.registerComponent<int>();

    EXPECT_EQ(typeid(ECS::SparseArray<int>), typeid(result));
}

TEST(registry, create_component) {
    ECS::Registry reg = {};
    auto result = reg.registerComponent<int>();

    auto &cmpts = reg.getComponents<int>();
    reg.createComponent<int>(0, 1);
    EXPECT_TRUE(cmpts[0].has_value());
    EXPECT_EQ(cmpts[0].value(), 1);
}

TEST(registry, access_component) {
    ECS::Registry reg = {};

    reg.registerComponent<int>();
    auto &cmpts = reg.getComponents<int>();
    EXPECT_EQ(typeid(ECS::SparseArray<int>), typeid(cmpts));
    reg.addComponent<int>(0, 1);
    EXPECT_TRUE(cmpts[0].has_value());
    EXPECT_EQ(cmpts[0].value(), 1);
}

TEST(registry, remove_entity) {
    ECS::Registry reg = {};

    reg.registerComponent<int>();
    auto &cmpts = reg.getComponents<int>();
    reg.addComponent<int>(0, 1);
    reg.killEntity(0);
    EXPECT_FALSE(cmpts[0].has_value());
}

TEST(registry, systems) {
    ECS::Registry reg = {};
    ECS::SparseArray<int> cmpts = {};

    reg.registerComponent<int>();
    reg.addComponent<int>(0, 1);
    reg.addSystem(test_system_add_one);
    reg.runSystems();
    cmpts = reg.getComponents<int>();
    EXPECT_EQ(cmpts[0].value(), 2);
}


