/*
Three distinct points are plotted at random on a Cartesian plane, for which -1000 ≤ x, y ≤ 1000, such that a triangle is formed.

Consider the following two triangles:

A(-340,495), B(-153,-910), C(835,-947)

X(-175,41), Y(-421,-714), Z(574,-645)

It can be verified that triangle ABC contains the origin, whereas triangle XYZ does not.

Using triangles.txt (right click and 'Save Link/Target As...'), a 27K text file containing the co-ordinates of one thousand "random" triangles, find the number of triangles for which the interior contains the origin.

NOTE: The first two examples in the file represent the triangles in the example given above.
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Point
{
    int x;
    int y;
};

struct Line
{
    Point p1;
    Point p2;
};

bool Bary(Point p, Point p1, Point p2, Point p3)
{
    double a, b, c;
    int x,x1,x2,x3;
    int y,y1,y2,y3;
    x = p.x;
    y = p.y;
    x1 = p1.x;
    y1 = p1.y;
    x2 = p2.x;
    y2 = p2.y;
    x3 = p3.x;
    y3 = p3.y;

    a = ((y2 - y3)*(x - x3) + (x3-x2)*(y-y3)) / (((y2 - y3)*(x1 -x3) + (x3-x2)*(y1-y3))*1.0);
    b = ((y3 -y1)*(x-x3) + (x1-x3)*(y-y3)) / (((y2-y3)*(x1-x3) + (x3-x2)*(y1-y3)) * 1.0);
    c = 1 - a - b;

    return 0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c <=1;
}

bool DoesTriangleContainOrigin(Point a, Point b, Point c)
{
    Point origin;
    origin.x = 0;
    origin.y = 0;

    return Bary(origin, a, b, c);
}

int GetAnswer()
{
    int ax, ay, bx, by, cx, cy;
    int count = 0;

    ifstream fin("triangles.txt");

    for (int i=0; i<1000; ++i)
    {
        fin >> ax >> ay >> bx >> by >> cx >> cy;

        Point a, b, c;

        a.x = ax;
        a.y = ay;
        b.x = bx;
        b.y = by;
        c.x = cx;
        c.y = cy;

        if (DoesTriangleContainOrigin(a, b, c))
        {
            ++count;
        }
    }

    return count;
}

int main()
{
    cout << GetAnswer() << endl;

    return 0;
}

