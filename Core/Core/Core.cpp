#include "stdafx.h"

#include <iostream>
#include <bitset>

#include "ootz/AStar2D.h"
#include "ootz/DirectX9/Shader.h"
#include "ootz/Basic/Example.h"
#include "ootz/Math/Math.h"
#include "ootz/Time.h"

namespace coroutine
{

std::future<int> async_add(int a, int b)
{
    return std::async([=]()
    {
        return a + b;
    });
}

std::future<int> async_fib(int n)
{
    if (n <= 2)
        co_return 1;

    int a = 1;
    int b = 1;

    for (int i = 0; i < n - 2; ++i)
    {
        int c = co_await async_add(a, b);
        a = b;
        b = c;
    }

    co_return b;
}

std::future<void> test_async_fib()
{
    for (int i = 1; i < 10; ++i)
    {
        int ret = co_await async_fib(i);
        std::cout << "async_fib(" << i << ") returns " << ret << '\n';
    }
}

}

struct MallocTest
{
    float x;
    float y;

    MallocTest()
        : x(0.0f)
        , y(0.0f)
    {
        std::cout << "MallocTest Constructor\n";
    }

    MallocTest(int a)
    {
        std::cout << "MallocTest one parameter Constructor\n";
    }

    ~MallocTest()
    {
        std::cout << "MallocTest Destructor\n";
    }
};

int main()
{
    using namespace ootz;

    //{
    //    Grid2D grid(8, 8);
    //    grid.SetAttribute(1, 1, Attribute::Unreachable);
    //    grid.SetAttribute(0, 1, Attribute::Unreachable);
    //    //grid.SetAttribute(1, 0, Attribute::Unreachable);

    //    StreamGrid2D streamGrid(grid);

    //    AStar2D aStar;
    //    std::vector<Vector2> path = aStar.GetPath(streamGrid, Vector2(0.0f, 0.0f), Vector2(7.0f, 7.0f));

    //    for (const auto& n : path)
    //    {
    //        std::cout << n << '\n';
    //    }
    //}

    //{
    //    using namespace Math;

    //    Plane plane(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 10.0f, 0.0f));

    //    const float distance = plane.DistanceFromPointSigned(Vector3(-100.0f, -2.0f, 100.0f));
    //    std::cout << distance;
    //}

    //coroutine::test_async_fib().wait();

    using namespace std;
    using namespace Time;

    auto operation = []() 
    {
        for (int i = 0; i < 10000000; ++i) {}
    };

    SystemElapsedTimer sysTimer(operation);
    ElapsedTimer timer(operation);

    cout << timer.GetElapsedTime() << '\n';
    cout << sysTimer.GetElapsedTime() << '\n';
    cout << sysTimer.GetStartTimeString() << '\n';
    cout << sysTimer.GetFinishTimeString() << '\n';

    return 0;
}

