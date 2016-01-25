/*
By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

   3
  7 4
 2 4 6
8 5 9 3

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom of the triangle below:

                            75
                          95  64
                        17  47  82
                      18  35  87  10
                    20  04  82  47  65
                  19  01  23  75  03  34
                88  02  77  73  07  63  67
              99  65  04  28  06  16  70  92
            41  41  26  56  83  40  80  70  33
          41  48  72  33  47  32  37  16  94  29
        53  71  44  65  25  43  91  52  97  51  14
      70  11  33  28  77  73  17  78  39  68  17  57
    91  71  52  38  17  14  91  43  58  50  27  29  48
  63  66  04  68  89  53  67  30  73  16  69  87  40  31
04  62  98  27  23  09  70  98  73  93  38  53  60  04  23
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;

vector< vector<int> > FillTriangle()
{
    vector< vector<int> > triangle;
    stringstream ss;
    
    string triangleText = 
    "\
                                75\
                              95  64\
                            17  47  82\
                          18  35  87  10\
                        20  04  82  47  65\
                      19  01  23  75  03  34\
                    88  02  77  73  07  63  67\
                  99  65  04  28  06  16  70  92\
                41  41  26  56  83  40  80  70  33\
              41  48  72  33  47  32  37  16  94  29\
            53  71  44  65  25  43  91  52  97  51  14\
          70  11  33  28  77  73  17  78  39  68  17  57\
        91  71  52  38  17  14  91  43  58  50  27  29  48\
      63  66  04  68  89  53  67  30  73  16  69  87  40  31\
    04  62  98  27  23  09  70  98  73  93  38  53  60  04  23\
    ";

    ss << triangleText;

    int temp;

    for (int row=0; row<15; ++row)
    {
        triangle.push_back(vector<int>());

        for (int col=0; col<row+1; ++col)
        {
            ss >> temp;
            triangle[row].push_back(temp);
        }
    }

    return triangle;
}

int GetValueByTraversingTriangle(vector< vector<int> > triangle)
{
    int sum;
    int col = 0;

    sum = triangle[0][0];

    for (int row=1; row<triangle.size(); ++row)
    {
        col += rand() % 2;
        sum += triangle[row][col];
    }

    return sum;
}

int GetTheBestPathYouCan(int numberOfTrials)
{
    int max = 0;
    vector< vector<int> > triangle = FillTriangle();
    srand(time(NULL));

    for (int i=0; i<numberOfTrials; ++i)
    {
        int value = GetValueByTraversingTriangle(triangle);

        if (value > max)
        {
            max = value;
        }
    }

    return max;
}

int main()
{
    cout << GetTheBestPathYouCan(32768) << endl;
    return 0;
}

