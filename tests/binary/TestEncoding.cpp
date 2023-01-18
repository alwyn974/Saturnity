/*
** EPITECH PROJECT, 2023
** TestTest.cpp
** File description:
** TestTest.cpp
*/

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

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