/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** sparse_array.cpp
*/

#include <gtest/gtest.h>
#include "ECS/SparseArray.hpp"

TEST(sparse_array, init) {
    ECS::SparseArray<int> arr;
    EXPECT_EQ(arr.size(), 0);
}

TEST(sparse_array, copy_init) {
    ECS::SparseArray<int> arr(1);

    arr.insert_at(0, 1);
    ECS::SparseArray<int> arr2(arr);
    EXPECT_EQ(arr[0].value(), arr2[0]);
}

TEST(sparse_array, emplace_data) {
    ECS::SparseArray<int> arr(3);

    arr.emplace_at(1, 1);
    EXPECT_EQ(arr[1].value(), 1);
    arr.emplace_at(2, 2);
    EXPECT_EQ(arr[2].value(), 2);
}

TEST(sparse_array, creation_insert_data_space) {
    ECS::SparseArray<int> arr(3);
    int data = 1;

    arr.insert_at(1, data);
    EXPECT_EQ(arr[1].value(), 1);
    arr.insert_at(2, 2);
    EXPECT_EQ(arr[2].value(), 2);
}

TEST(sparse_array, creation_insert_data_no_space) {
    ECS::SparseArray<int> arr;
    int data = 1;

    arr.insert_at(1, data);
    EXPECT_EQ(arr[1].value(), 1);
    arr.insert_at(2, 2);
    EXPECT_EQ(arr[2].value(), 2);
}

TEST(sparse_array, get_index) {
    ECS::SparseArray<int> arr(2);

    arr.insert_at(0, 2);
    EXPECT_EQ(arr.get_index(2), 0);
    EXPECT_EQ(arr.get_index(30), 2);
}


TEST(sparse_array, eraser) {
    ECS::SparseArray<int> arr;

    arr.insert_at(0, 2);
    arr.erase(0);
    EXPECT_FALSE(arr[0].has_value());
}
