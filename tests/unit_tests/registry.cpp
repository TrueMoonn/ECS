/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** registry.cpp
** Copyright [2025] <DeepestDungeonGroup>
*/

#include <gtest/gtest.h>

#include "ECS/Registry.hpp"
#include "ECS/DenseSA.hpp"

void test_system_add_one(ECS::Registry& reg) {
    auto &integers = reg.getComponents<int>();
    auto& spar = integers.getSpar();

    for (std::size_t page = 0; page < spar.size(); ++page) {
        for (std::size_t e = 0; e < spar[page].size(); ++e) {
            if (spar[page][e].has_value()) {
                auto& val = integers.getComponent(spar[page][e].value());
                val++;
            }
        }
    }
}

TEST(registry, register_component) {
    ECS::Registry reg = {};
    auto result = reg.registerComponent<int>();

    EXPECT_EQ(typeid(ECS::DenseSparseArray<int>), typeid(result));
}

TEST(registry, create_component) {
    ECS::Registry reg = {};
    auto& integers = reg.registerComponent<int>();

    reg.createComponent<int>(0, 1);
    EXPECT_TRUE(integers.getSpar()[0][0].has_value());
    EXPECT_EQ(integers.getSpar()[0][0].value(), 0);
    EXPECT_EQ(integers.getComponent(0), 1);
}

TEST(registry, access_component) {
    ECS::Registry reg = {};
    auto& integers = reg.registerComponent<int>();

    reg.addComponent<int>(0, 1);
    EXPECT_TRUE(integers.getSpar()[0][0].has_value());
    EXPECT_EQ(integers.getSpar()[0][0].value(), 0);
    EXPECT_EQ(integers.getComponent(0), 1);
    reg.createComponent<int>(2, 3);
    EXPECT_TRUE(integers.getSpar()[0][2].has_value());
    EXPECT_EQ(integers.getSpar()[0][2].value(), 1);
    EXPECT_EQ(integers.getComponent(1), 3);
}

TEST(registry, remove_entity) {
    ECS::Registry reg = {};
    auto& integers = reg.registerComponent<int>();

    reg.addComponent<int>(0, 1);
    reg.addComponent<int>(1, 2);
    reg.killEntity(0);
    EXPECT_FALSE(integers.getSpar()[0][0].has_value());
    EXPECT_EQ(integers.getComponent(integers.getSpar()[0][1].value()), 2);
}

TEST(registry, systems) {
    ECS::Registry reg = {};
    auto& integers = reg.registerComponent<int>();

    reg.addComponent<int>(0, 1);
    reg.addComponent<int>(1000, 1000);
    reg.addSystem(test_system_add_one);
    reg.runSystems();
    EXPECT_TRUE(integers.getSpar()[0][0].has_value());
    EXPECT_EQ(integers.getSpar()[0][0].value(), 0);
    EXPECT_EQ(integers.getComponent(0), 2);
    EXPECT_TRUE(integers.getSpar()[1][0].has_value());
    EXPECT_EQ(integers.getSpar()[1][0].value(), 1);
    EXPECT_EQ(integers.getComponent(1), 1001);
}
