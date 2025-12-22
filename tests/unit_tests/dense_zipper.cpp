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

TEST(dense_zipper, simple_indexed_dense_zipper) {
    SIMPLE_SETUP
    int nbi = 0;
    for (auto &&[i, in, ch] : ECS::IndexedDenseZipper(ints, chars)) {
        EXPECT_EQ(in, 1);
        EXPECT_EQ(ch, '1');
        EXPECT_EQ(i, 1);
        nbi += 1;
    }
    EXPECT_EQ(nbi, 1);
}

TEST(dense_zipper, hard_indexed_dense_zipper) {
    HARD_SETUP
    int nbi = 0;
    for (auto &&[i, in, ch] : ECS::IndexedDenseZipper(ints, chars)) {
        if (i == 1) {
            EXPECT_EQ(in, 1);
            EXPECT_EQ(ch, '1');
        }
        if (i == 3) {
            EXPECT_EQ(in, 3);
            EXPECT_EQ(ch, '3');
        }
        if (i == 6) {
            EXPECT_EQ(in, 6);
            EXPECT_EQ(ch, '6');
        }
        nbi += 1;
    }
    EXPECT_EQ(nbi, 3);
}

TEST(dense_zipper, update_indexed_dense_zipper) {
    // SIMPLE_SETUP
    // int index_found = 0;
    // for (auto &&[i, in, ch] : ECS::IndexedDenseZipper(ints, chars)) {
    //     in += 1;
    //     ch += 1;
    //     index_found = i;
    // }
    // EXPECT_EQ(ints[index_found], index_found + 1);
    // EXPECT_EQ(chars[index_found], index_found + '0' + 1);
}
