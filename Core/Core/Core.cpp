#include "stdafx.h"

#include <iostream>

#include "ootz/AStar2D.hpp"

int main()
{
    using namespace ootz;

    {
        Grid2D grid(8, 8);
        grid.SetAttribute(1, 1, Attribute::Unreachable);
        grid.SetAttribute(0, 1, Attribute::Unreachable);
        grid.SetAttribute(1, 0, Attribute::Unreachable);

        StreamGrid2D streamGrid(grid);

        AStar2D aStar;
        std::vector<Vector2> path = aStar.GetPath(streamGrid, Vector2(0.0f, 0.0f), Vector2(7.0f, 7.0f));

        for (const auto& n : path)
        {
            std::cout << n << '\n';
        }
    }

    return 0;
}

