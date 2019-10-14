#pragma once

#include <memory>

#include "entity.hpp"

class Hierarchy
{
public:
    Hierarchy();


    std::unique_ptr<Entity> m_RootEntity;
};

