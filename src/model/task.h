#pragma once

#include <iostream>
#include <ctime>

enum taskStatus
{
    TODO,
    IN_PROGRESS,
    DONE,
};

struct Task
{
    std::string id{};
    std::string description{};
    std::string status{};
    std::time_t createdAt{};
    std::time_t updatedAt{};
};