/*
Three circles of equal radius are placed inside a larger circle such that each pair of circles is tangent to one another and the inner circles do not overlap. There are four uncovered "gaps" which are to be filled iteratively with more tangent circles.

At each iteration, a maximally sized circle is placed in each gap, which creates more gaps for the next iteration. After 3 iterations (pictured), there are 108 gaps and the fraction of the area which is not covered by circles is 0.06790342, rounded to eight decimal places.

What fraction of the area is not covered by circles after 10 iterations?
Give your answer rounded to eight decimal places using the format x.xxxxxxxx .
*/

/*

What type of problem is this?

Circle Packing

*/

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

#define PI 3.141592653589793238462643383279502884197169399375105820974

using namespace std;

struct Circle
{
    double radius;
    bool isBig;
    Circle() {}
    Circle(double r, bool is) : radius(r), isBig(is) {}
};

double Area(double radius)
{
    return PI * radius * radius;
}

double GetRadiusOfOuterSoddyCircle(double A, double B, double C)
{
    return abs(A * B * C / (A * B + B * C + C * A - 2 * sqrt(A * B * C * (A + B + C))));
}

double GetRadiusOfInnerSoddyCircle(double A, double B, double C)
{
    return abs(A * B * C / (A * B + B * C + C * A + 2 * sqrt(A * B * C * (A + B + C))));
}

double GetRadiusOfCircleTangentToTwoCirclesAndInsideAnotherTangentCircle(double A, double B, double C)
{
    return abs(A * B * C / (A * C + B * C - A * B + 2 * sqrt(A * B * C * (C - A - B))));
}

vector<vector<Circle>> LoadInitialInnerCirclesToProcess(double initialRadius)
{
    Circle normalCircle;

    normalCircle.radius = initialRadius;
    normalCircle.isBig = false;

    vector<vector<Circle>> toReturn;

    vector<Circle> toInsert;

    toInsert.push_back(normalCircle);
    toInsert.push_back(normalCircle);
    toInsert.push_back(normalCircle);

    toReturn.push_back(toInsert);

    return toReturn;
}

vector<vector<Circle>> LoadInitialOuterCirclesToProcess(double initialRadius, double radiusOfBigCircle)
{
    Circle bigCircle;
    Circle normalCircle;

    bigCircle.radius = radiusOfBigCircle;
    bigCircle.isBig = true;

    normalCircle.radius = initialRadius;
    normalCircle.isBig = false;

    vector<vector<Circle>> toReturn;

    vector<Circle> toInsert;

    toInsert.push_back(normalCircle);
    toInsert.push_back(normalCircle);
    toInsert.push_back(bigCircle);

    // Two normal circles + Large circles
    toReturn.push_back(toInsert);

    return toReturn;
}

double CalculateUncoveredRatio(const vector<Circle> &innerCircles, double radiusOfBigCircle)
{
    double totalInnerArea = 0;

    for (const Circle &innerCircle : innerCircles)
    {
        totalInnerArea += Area(innerCircle.radius);
    }

    return (Area(radiusOfBigCircle) - totalInnerArea) / Area(radiusOfBigCircle);
}

vector<vector<Circle>> MakeSetsToAdd(const vector<Circle> &setOfCircles, const Circle &newCircle)
{
    vector<vector<Circle>> toReturn;

    vector<Circle> one;
    vector<Circle> two;
    vector<Circle> three;

    one.push_back(newCircle);
    one.push_back(setOfCircles[0]);
    one.push_back(setOfCircles[1]);

    two.push_back(newCircle);
    two.push_back(setOfCircles[0]);
    two.push_back(setOfCircles[2]);

    three.push_back(newCircle);
    three.push_back(setOfCircles[1]);
    three.push_back(setOfCircles[2]);

    toReturn.push_back(one);
    toReturn.push_back(two);
    toReturn.push_back(three);

    return toReturn;
}

vector<Circle> GetCirclesToAdd(vector<vector<Circle>> &toProcess, int iterations)
{
    vector<Circle> toReturn;

    for (int i=0; i<iterations; ++i)
    {
        vector<vector<Circle>> nextIterationToProcess;

        for (const vector<Circle> &setOfCircles : toProcess)
        {
            Circle newCircle;

            if (setOfCircles[2].isBig)
            {
                newCircle.radius = GetRadiusOfCircleTangentToTwoCirclesAndInsideAnotherTangentCircle(setOfCircles[0].radius, setOfCircles[1].radius, setOfCircles[2].radius);
            }
            else
            {
                newCircle.radius = GetRadiusOfInnerSoddyCircle(setOfCircles[0].radius, setOfCircles[1].radius, setOfCircles[2].radius);
            }

            newCircle.isBig = false;

            // New circle created, so add to area
            toReturn.push_back(newCircle);

            // Create 3 new tasks for iteration
            vector<vector<Circle>> toAdd = MakeSetsToAdd(setOfCircles, newCircle);

            nextIterationToProcess.insert(nextIterationToProcess.end(), toAdd.begin(), toAdd.end());
        }

        toProcess = nextIterationToProcess;
    }

    return toReturn;
}

double GetFractionOfAreaNotCovered(int iterations)
{
    const int initialRadius = 1;
    // Assume the big three circles have a radius of one
    // Calculate the radius of the BIG circle
    double radiusOfBigCircle = GetRadiusOfOuterSoddyCircle(initialRadius, initialRadius, initialRadius);

    vector<Circle> innerCircles(3, Circle(1, false));

    vector<vector<Circle>> innerCircleToProcess = LoadInitialInnerCirclesToProcess(initialRadius);
    vector<vector<Circle>> outerCirclesToProcess = LoadInitialOuterCirclesToProcess(initialRadius, radiusOfBigCircle);

    vector<Circle> circlesToAdd = GetCirclesToAdd(innerCircleToProcess, iterations);

    innerCircles.insert(innerCircles.end(), circlesToAdd.begin(), circlesToAdd.end());

    circlesToAdd = GetCirclesToAdd(outerCirclesToProcess, iterations);

    innerCircles.insert(innerCircles.end(), circlesToAdd.begin(), circlesToAdd.end());
    innerCircles.insert(innerCircles.end(), circlesToAdd.begin(), circlesToAdd.end());
    innerCircles.insert(innerCircles.end(), circlesToAdd.begin(), circlesToAdd.end());

    return CalculateUncoveredRatio(innerCircles, radiusOfBigCircle);
}

int main()
{
    cout << fixed << setprecision(8) << GetFractionOfAreaNotCovered(10) << endl;

    return 0;
}

