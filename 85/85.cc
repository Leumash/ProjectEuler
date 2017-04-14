#include <iostream>
#include <cmath>

using namespace std;

// Number of rectangles for a given w, h = w(w + 1) * h(h + 1) / 4

int countRectangles(int width, int height) {
    return width * (width + 1) * height * (height + 1) / 4;
}

double findHeight(int w, int target) {
    double c = -target * 4.0 / (w * (w + 1.0));
    return (-1 + sqrt(1 - 4 * c)) / 2;
}

int getAreaOfGridWithNumberOfSubRectanglesNearestTo(int target) {
    int maxWidth = 0;
    int maxHeight = 0;
    int closest = 276447231;    // Max int

    for (int width=1; ; ++width) {
        double height = findHeight(width, target);
        int above = countRectangles(width, ceil(height));
        int below = countRectangles(width, floor(height));

        if (above - target < closest) {
            maxWidth = width;
            maxHeight = ceil(height);
            closest = above - target;
        }
        if (target - below < closest) {
            maxWidth = width;
            maxHeight = floor(height);
            closest = target - below;
        }
        if (width > height) {
            break;
        }
    }

    return maxWidth * maxHeight;
}

int main() {
    cout << getAreaOfGridWithNumberOfSubRectanglesNearestTo(2000000) << endl;
}

