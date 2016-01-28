/*
The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating them in any order the result will always be prime. For example, taking 7 and 109, both 7109 and 1097 are prime. The sum of these four primes, 792, represents the lowest sum for a set of four primes with this property.

Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.
*/

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

class PrimeTester
{
    public:
        PrimeTester();
        bool IsPrime(int);
        int GetNextPrime(int);  // O(log n)
    private:
        void GetNextPrime();
        bool TestIfPrime(int);

        set<int> primes;
        int currentLargestPrime;
};

int ConcatenateNumbers(int num1, int num2)
{
    int numberOfDigits = (int)(log10(num2) + 1);

    return num1 * pow(10, numberOfDigits) + num2;
}

bool DoesConcatenateIntoPrime(int prime1, int prime2, PrimeTester &primeTester)
{
    int concatenatedPrime1 = ConcatenateNumbers(prime1, prime2);
    int concatenatedPrime2 = ConcatenateNumbers(prime2, prime1);

    return primeTester.IsPrime(concatenatedPrime1) && primeTester.IsPrime(concatenatedPrime2);
}

void AddPrimeToMap(map<int, set<int> > &primeToPrimesThatConcatenate, PrimeTester &primeTester, int primeToAdd)
{
    set<int> toAdd;

    for (map<int, set<int> >::iterator mit = primeToPrimesThatConcatenate.begin();
        mit != primeToPrimesThatConcatenate.end(); ++mit)
    {
        if (DoesConcatenateIntoPrime(mit->first, primeToAdd, primeTester))
        {
            toAdd.insert(mit->first);
        }
    }

    for (set<int>::iterator sit = toAdd.begin(); sit != toAdd.end(); ++sit)
    {
        primeToPrimesThatConcatenate[*sit].insert(primeToAdd);
    }

    primeToPrimesThatConcatenate[primeToAdd] = toAdd;
}

void GetCombinations(vector< set<int> > &toReturn, set<int> currentCombination, const set<int> &initialSet, set<int>::const_iterator currentConsideration, int numberToChoose)
{
    if (numberToChoose == 0)
    {
        toReturn.push_back(currentCombination);
        return;
    }

    if (currentConsideration == initialSet.end())
    {
        return;
    }

    set<int>::const_iterator sit = currentConsideration;

    ++sit;

    currentCombination.insert(*currentConsideration);
    GetCombinations(toReturn, currentCombination, initialSet, sit, numberToChoose - 1);
    currentCombination.erase(*currentConsideration);
    GetCombinations(toReturn, currentCombination, initialSet, sit, numberToChoose);
}

vector< set<int> > GetCombinations(const set<int> &initialSet, int numberToChoose)
{
    vector< set<int> > toReturn;
    set<int> currentCombination;

    GetCombinations(toReturn, currentCombination, initialSet, initialSet.begin(), numberToChoose);

    return toReturn;
}

bool IsCombinationValid(const set<int> &combination, map<int, set<int> > &primeToPrimesThatConcatenate)
{
    for (set<int>::const_iterator sit = combination.begin(); sit != combination.end(); ++sit)
    {
        for (set<int>::const_iterator sit2 = combination.begin(); sit2 != combination.end(); ++sit2)
        {
            if (*sit != *sit2)
            {
                if (primeToPrimesThatConcatenate[*sit].count(*sit2) == 0)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool DoesValidCombinationExist(map<int, set<int> > &primeToPrimesThatConcatenate, set<int> currentCombination, const set<int> &initialSet, set<int>::const_iterator currentConsideration, int numberToChoose)
{
    if (numberToChoose == 0)
    {
        return true;
    }

    if (currentConsideration == initialSet.end())
    {
        return false;
    }

    set<int>::const_iterator sit = currentConsideration;

    ++sit;

    currentCombination.insert(*currentConsideration);


    if (IsCombinationValid(currentCombination, primeToPrimesThatConcatenate))
    {
        bool foundValidCombination = DoesValidCombinationExist(primeToPrimesThatConcatenate, currentCombination, initialSet, sit, numberToChoose - 1);

        if (foundValidCombination)
        {
            return true;
        }
    }

    currentCombination.erase(*currentConsideration);

    return DoesValidCombinationExist(primeToPrimesThatConcatenate, currentCombination, initialSet, sit, numberToChoose);
}

bool FoundValidCombination(map<int, set<int> > &primeToPrimesThatConcatenate, set<int> &toCheck, int numberOfPrimes)
{
    return DoesValidCombinationExist(primeToPrimesThatConcatenate, set<int>(), toCheck, toCheck.begin(), numberOfPrimes);
}

bool IsSolutionFound(map<int, set<int> > &primeToPrimesThatConcatenate, int currentPrime, int numberOfPrimes)
{
    set<int> toCheck = primeToPrimesThatConcatenate[currentPrime];

    if (toCheck.size() < numberOfPrimes - 1)
    {
        return false;
    }

    return FoundValidCombination(primeToPrimesThatConcatenate, toCheck, numberOfPrimes - 1);
}

int GetSum(const set<int> &numbers)
{
    int sum = 0;

    for (set<int>::const_iterator sit = numbers.begin(); sit != numbers.end(); ++sit)
    {
        cout << *sit << ' ';
        sum += *sit;
    }
    cout << endl;

    return sum;
}

int GetSolution(map<int, set<int> > &primeToPrimesThatConcatenate, int currentPrime, int numberOfPrimes)
{
    int min = numeric_limits<int>::max();
    set<int> toCheck = primeToPrimesThatConcatenate[currentPrime];
    vector< set<int> > combinations = GetCombinations(toCheck, numberOfPrimes - 1);

    for (int i=0; i<combinations.size(); ++i)
    {
        if (IsCombinationValid(combinations[i], primeToPrimesThatConcatenate))
        {
            combinations[i].insert(currentPrime);

            int sum = GetSum(combinations[i]);

            if (sum < min)
            {
                min = sum;
            }
        }
    }

    return min;
}

int GetLowestSum(int numberOfPrimes)
{
    if (numberOfPrimes < 2)
    {
        return 0;
    }

    PrimeTester primeTester;
    map<int, set<int> > primeToPrimesThatConcatenate;

    int currentPrime = 2;

    for (;; currentPrime = primeTester.GetNextPrime(currentPrime))
    {
        AddPrimeToMap(primeToPrimesThatConcatenate, primeTester, currentPrime);

        if (IsSolutionFound(primeToPrimesThatConcatenate, currentPrime, numberOfPrimes))
        {
            break;
        }
    }

    return GetSolution(primeToPrimesThatConcatenate, currentPrime, numberOfPrimes);
}

int main()
{
    cout << GetLowestSum(5) << endl;

    return 0;
}


PrimeTester::PrimeTester()
{
    primes.insert(2);
    primes.insert(3);
    
    currentLargestPrime = 3;
}

bool PrimeTester::IsPrime(int candidate)
{
    while (currentLargestPrime < sqrt(candidate))
    {
        GetNextPrime();
    }

    return TestIfPrime(candidate);
}

int PrimeTester::GetNextPrime(int previousPrime)
{
    while (currentLargestPrime <= previousPrime)
    {
        GetNextPrime();
    }

    set<int>::iterator sit = primes.find(previousPrime);

    if (sit == primes.end())
    {
        cout << previousPrime << " is not a prime!!!" << endl;
        exit(1);
    }

    return *(++sit);
}

bool PrimeTester::TestIfPrime(int candidate)
{
    for (set<int>::iterator sit = primes.begin(); *sit <= sqrt(candidate); ++sit)
    {
        if (candidate % *sit == 0)
        {
            return false;
        }
    }

    return true;
}

void PrimeTester::GetNextPrime()
{
    int candidate = currentLargestPrime + 2;

    while (!TestIfPrime(candidate))
    {
        candidate += 2;
    }

    currentLargestPrime = candidate;
    primes.insert(candidate);
}

