#ifndef MATERIAL_H
#define MATERIAL_H

#include <util/Color.h>

#include <string>

enum FillDirection {
    BOTTOM_UP = 0,
    TOP_DOWN = 1,
    SURFACE_UP = 2,
    SURfACE_DOWN = 3
};

struct Material
{
    std::string name = "none";
    FillDirection fillDirection = BOTTOM_UP;
    size_t offset = 0u;
    size_t minDepth = 1u;
    size_t maxDepth = 1u;
    Color color = Color();
    bool isBound = true;
};


#endif