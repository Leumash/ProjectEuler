/*
The points P (x1, y1) and Q (x2, y2) are plotted at integer co-ordinates and are joined to the origin, O(0,0), to form ΔOPQ.


There are exactly fourteen triangles containing a right angle that can be formed when each co-ordinate lies between 0 and 2 inclusive; that is,
0 ≤ x1, y1, x2, y2 ≤ 2.


Given that 0 ≤ x1, y1, x2, y2 ≤ 50, how many right triangles can be formed?
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point
{
    int x;
    int y;
    Point(int xx, int yy) : x(xx), y(yy) {}
    operator == (const Point &other)
    {
        return x == other.x && y == other.y;
    }
};

bool DoesFormRightTriangle(Point &A, Point &B, Point &C)
{
    if (A == B || B == C || A == C)
    {
        return false;
    }

    vector<int> distances(3);

    distances[0] = (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
    distances[1] = (A.x - C.x) * (A.x - C.x) + (A.y - C.y) * (A.y - C.y);
    distances[2] = (B.x - C.x) * (B.x - C.x) + (B.y - C.y) * (B.y - C.y);

    sort(distances.begin(), distances.end());

    return distances[0] + distances[1] == distances[2];
}

int GCD(int a, int b)
{
    return b == 0 ? a : GCD(b, a%b);
}

int GetNumberOfRightTriangles(int limit)
{
    int count = 0;

    count += limit * limit * 3;

    for (int x=1; x<=limit; ++x)
    {
        for (int y=1; y<=limit; ++y)
        {
            int gcd = GCD(x, y);

            count += min(y * gcd / x, (limit - x) * gcd / y) * 2;
        }
    }

    return count;
}

int main()
{
    cout << GetNumberOfRightTriangles(50) << endl;

    return 0;
}

