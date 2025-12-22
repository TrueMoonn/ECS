/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** zipper.cpp
*/

#include <gtest/gtest.h>

#include "ECS/Zipper.hpp"
#include "ECS/SparseArray.hpp"

#define SIMPLE_SETUP ECS::SparseArray<int> ints;\
    ECS::SparseArray<char> chars;\
    chars.emplace_at(1, '1');\
    ints.emplace_at(1, 1);\
    ints.emplace_at(0, 0);

#define HARD_SETUP ECS::SparseArray<int> ints;\
    ECS::SparseArray<char> chars;\
    ints.emplace_at(0, 0);\
    ints.emplace_at(8, 8);\
    ints.emplace_at(2, 2);\
    chars.emplace_at(9, '9');\
    chars.emplace_at(5, '5');\
    ints.emplace_at(1, 1);\
    chars.emplace_at(1, '1');\
    chars.emplace_at(3, '3');\
    ints.emplace_at(3, 3);\
    chars.emplace_at(6, '6');\
    ints.emplace_at(6, 6);

TEST(zipper, simple_zipper) {
    SIMPLE_SETUP
    int nbi = 0;
    for (auto &&[in, ch] : ECS::Zipper(ints, chars)) {
        EXPECT_EQ(in, 1);
        EXPECT_EQ(ch, '1');
        nbi += 1;
    }
    EXPECT_EQ(nbi, 1);
}

TEST(zipper, hard_zipper) {
    HARD_SETUP
    int nbi = 0;
    for (auto &&[in, ch] : ECS::Zipper(ints, chars)) {
        nbi += 1;
    }
    EXPECT_EQ(nbi, 3);
}

TEST(zipper, simple_indexed_zipper) {
    SIMPLE_SETUP
    int nbi = 0;
    for (auto &&[i, in, ch] : ECS::IndexedZipper(ints, chars)) {
        EXPECT_EQ(in, 1);
        EXPECT_EQ(ch, '1');
        EXPECT_EQ(i, 1);
        nbi += 1;
    }
    EXPECT_EQ(nbi, 1);
}

TEST(zipper, hard_indexed_zipper) {
    HARD_SETUP
    int nbi = 0;
    for (auto &&[i, in, ch] : ECS::IndexedZipper(ints, chars)) {
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

TEST(zipper, update_indexed_zipper) {
    SIMPLE_SETUP
    int index_found = 0;
    for (auto &&[i, in, ch] : ECS::IndexedZipper(ints, chars)) {
        in += 1;
        ch += 1;
        index_found = i;
    }
    EXPECT_EQ(ints[index_found], index_found + 1);
    EXPECT_EQ(chars[index_found], index_found + '0' + 1);
}
