/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** zipper.cpp
*/

#include <gtest/gtest.h>

#include "ECS/DenseZipper.hpp"
#include "ECS/DenseSA.hpp"

#define SIMPLE_SETUP ECS::DenseSparseArray<int> ints;\
    ECS::DenseSparseArray<char> chars;\
    chars.createComponent(1, '1');\
    ints.createComponent(1, 1);\
    ints.createComponent(0, 0);

#define HARD_SETUP ECS::DenseSparseArray<int> ints;\
ECS::DenseSparseArray<char> chars;\
    ints.createComponent(0, 0);\
    ints.createComponent(8, 8);\
    ints.createComponent(2, 2);\
    chars.createComponent(9, '9');\
    chars.createComponent(5, '5');\
    ints.createComponent(1, 1);\
    chars.createComponent(1, '1');\
    chars.createComponent(3, '3');\
    ints.createComponent(3, 3);\
    chars.createComponent(6, '6');\
    ints.createComponent(6, 6);

TEST(dense_zipper, simple_dense_zipper) {
    SIMPLE_SETUP
    int nbi = 0;
    for (auto &&[in, ch] : ECS::DenseZipper(ints, chars)) {
        EXPECT_EQ(in, 1);
        EXPECT_EQ(ch, '1');
        nbi += 1;
    }
    EXPECT_EQ(nbi, 1);
}

TEST(dense_zipper, hard_dense_zipper) {
    HARD_SETUP
    int nbi = 0;
    for (auto &&[in, ch] : ECS::DenseZipper(ints, chars)) {
        nbi += 1;
    }
    EXPECT_EQ(nbi, 3);
}
