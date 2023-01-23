/*
** EPITECH PROJECT, 2023
** TestTest.cpp
** File description:
** TestTest.cpp
*/

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

#include <boost/array.hpp>

TEST(Encoding, TestEncodingInteger)
{
    const auto expected = 1;
    const auto actual = 1;
    ASSERT_EQ(expected, actual);
}

TEST(spdlog, TestSpdlog)
{
    spdlog::info("Welcome to Saturnity!");
}

TEST(Boost, array)
{
    boost::array<int, 4> array = {1, 2, 3, 4};
    ASSERT_EQ(array[0], 1);
    ASSERT_EQ(array[1], 2);
    ASSERT_EQ(array[2], 3);
    ASSERT_EQ(array[3], 4);
}
