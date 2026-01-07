#pragma once

#include <iostream>
#include <ctime>

struct Task
{
    int id{};
    std::string description{};
    std::string status{"in-progress"};
    std::time_t createdAt{std::time(nullptr)};
    std::time_t updatedAt{std::time(nullptr)};
};