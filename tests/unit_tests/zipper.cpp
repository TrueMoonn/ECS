/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** zipper.cpp
*/

#include <gtest/gtest.h>

#include "Zipper.hpp"
#include "Registry.hpp"

static ECS::Registry simple_registry_setup() {
    ECS::Registry reg;
    reg.registerComponent<int>();
    reg.registerComponent<char>();

    reg.addComponent<int>(0, 0);
    reg.addComponent<int>(1, 1);
    reg.addComponent<char>(1, '1');
    return reg;
}

static ECS::Registry hard_registry_setup() {
    ECS::Registry reg;
    reg.registerComponent<int>();
    reg.registerComponent<char>();

    reg.addComponent<int>(0, 0);
    reg.addComponent<int>(8, 8);
    reg.addComponent<int>(2, 2);
    reg.addComponent<char>(9, '9');
    reg.addComponent<char>(5, '5');

    reg.addComponent<int>(1, 1);
    reg.addComponent<char>(1, '1');

    reg.addComponent<char>(3, '3');
    reg.addComponent<int>(3, 3);

    reg.addComponent<char>(6, '6');
    reg.addComponent<int>(6, 6);
    return reg;
}

TEST(zipper, simple_zipper) {
    ECS::Registry reg = simple_registry_setup();

    auto& ints = reg.getComponents<int>();
    auto& chars = reg.getComponents<char>();
    int nbi = 0;
    for (auto &&[in, ch] : ECS::Zipper(ints, chars)) {
        EXPECT_EQ(in.value(), 1);
        EXPECT_EQ(ch.value(), '1');
        nbi += 1;
    }
    EXPECT_EQ(nbi, 1);
}

TEST(zipper, hard_zipper) {
    ECS::Registry reg = hard_registry_setup();

    auto& ints = reg.getComponents<int>();
    auto& chars = reg.getComponents<char>();
    int nbi = 0;
    for (auto &&[in, ch] : ECS::Zipper(ints, chars)) {
        nbi += 1;
    }
    EXPECT_EQ(nbi, 3);
}

TEST(zipper, simple_indexed_zipper) {
    ECS::Registry reg = simple_registry_setup();

    auto& ints = reg.getComponents<int>();
    auto& chars = reg.getComponents<char>();
    int nbi = 0;
    for (auto &&[i, in, ch] : ECS::IndexedZipper(ints, chars)) {
        EXPECT_EQ(in.value(), 1);
        EXPECT_EQ(ch.value(), '1');
        EXPECT_EQ(i, 1);
        nbi += 1;
    }
    EXPECT_EQ(nbi, 1);
}

TEST(zipper, hard_indexed_zipper) {
    ECS::Registry reg = hard_registry_setup();

    auto& ints = reg.getComponents<int>();
    auto& chars = reg.getComponents<char>();
    int nbi = 0;
    for (auto &&[i, in, ch] : ECS::IndexedZipper(ints, chars)) {
        if (i == 1) {
            EXPECT_EQ(in.value(), 1);
            EXPECT_EQ(ch.value(), '1');
        }
        if (i == 3) {
            EXPECT_EQ(in.value(), 3);
            EXPECT_EQ(ch.value(), '3');
        }
        if (i == 6) {
            EXPECT_EQ(in.value(), 6);
            EXPECT_EQ(ch.value(), '6');
        }
        nbi += 1;
    }
    EXPECT_EQ(nbi, 3);
}
