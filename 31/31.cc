/*
In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
It is possible to make £2 in the following way:

1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins?
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> GetCoins()
{
    vector<int> toReturn;

    toReturn.push_back(1);
    toReturn.push_back(2);
    toReturn.push_back(5);
    toReturn.push_back(10);
    toReturn.push_back(20);
    toReturn.push_back(50);
    toReturn.push_back(100);
    toReturn.push_back(200);

    return toReturn;
}

int GetWaysToMakeValue(int value)
{
    vector<int> coins = GetCoins();
    vector<int> waysForCoinsToMakeValue(value + 1, 0);

    waysForCoinsToMakeValue[0] = 1;

    for (int i=0; i<coins.size(); ++i)
    {
        int coin = coins[i];

        for (int total=0; total<waysForCoinsToMakeValue.size(); ++total)
        {
            if (total - coin >= 0)
            {
                waysForCoinsToMakeValue[total] += waysForCoinsToMakeValue[total-coin];
            }
        }
    }

    return waysForCoinsToMakeValue[200];
}

int main()
{
    cout << GetWaysToMakeValue(200) << endl;

    return 0;
}

