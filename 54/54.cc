#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <fstream>

#define NUMBER_OF_GAMES 1000

using namespace std;

enum CardValue { Two = 2, Three, Four, Five, Six, Seven, Eight,
                Nine, Ten, Jack, Queen, King, Ace };

enum PokerHand { HighCard, OnePair, TwoPairs, ThreeOfAKind, Straight, Flush, FullHouse,
                FourOfAKind, StraightFlush, RoyalFlush };

struct Card
{
    char suit;
    CardValue value;
};

class Hand
{
    public:
        Hand(Card, Card, Card, Card, Card);

        PokerHand GetHandValue();

        bool IsBetterHand(Hand);

    private: 
        bool AceExists();
        bool HasNOfAKind(int);
        bool HasNOfAKindAndMOfAKind(int,int);

        CardValue GetCardValueForNOfAKind(int n);
        map<int,int> CountCardValues();
        pair<CardValue,CardValue> GetCardValueForNOfAKindAndMOfAKind(int n, int m);

        bool IsBetterStraightFlush(Hand);
        bool IsBetterFourOfAKind(Hand);
        bool IsBetterFullHouse(Hand);
        bool IsBetterFlush(Hand);
        bool IsBetterStraight(Hand);
        bool IsBetterThreeOfAKind(Hand);
        bool IsBetterTwoPairs(Hand);
        bool IsBetterOnePair(Hand);
        bool IsBetterHighCard(Hand);

        bool IsRoyalFlush();
        bool IsStraightFlush();
        bool IsFourOfAKind();
        bool IsFullHouse();
        bool IsFlush();
        bool IsStraight();
        bool IsThreeOfAKind();
        bool IsTwoPairs();
        bool IsOnePair();

        vector<Card> cards;
};

CardValue ConvertToCardValue(char value)
{
    switch(value)
    {
        case '2':
            return Two;
        case '3':
            return Three;
        case '4':
            return Four;
        case '5':
            return Five;
        case '6':
            return Six;
        case '7':
            return Seven;
        case '8':
            return Eight;
        case '9':
            return Nine;
        case 'T':
            return Ten;
        case 'J':
            return Jack;
        case 'Q':
            return Queen;
        case 'K':
            return King;
        case 'A':
            return Ace;
        default:
            cout << "Error has occurred!!" << endl;
            exit(1);
    }
}

Hand GetHand(istream &fin)
{
    Card cards[5];

    for (int i=0; i<5; ++i)
    {
        char temp;
        fin >> temp;
        cards[i].value = ConvertToCardValue(temp);

        fin >> temp;
        cards[i].suit = temp;
    }

    return Hand(cards[0], cards[1], cards[2], cards[3], cards[4]);
}

vector< pair<Hand,Hand> > GetGames()
{
    vector< pair<Hand,Hand> > toReturn;
    fstream fin("poker.txt");

    for (int i=0; i<NUMBER_OF_GAMES; ++i)
    {
        Hand playerOneHand = GetHand(fin);
        Hand playerTwoHand = GetHand(fin);

        toReturn.push_back(make_pair(playerOneHand, playerTwoHand));
    }

    return toReturn;
}

bool DoesPlayerOneWin(Hand hand1, Hand hand2)
{
    return hand1.IsBetterHand(hand2);
}

int CountPlayerOneWins(const vector< pair<Hand,Hand> > &game)
{
    int count = 0;

    for (int i=0; i<game.size(); ++i)
    {
        if (DoesPlayerOneWin(game[i].first, game[i].second))
        {
            ++count;
        }
    }

    return count;
}

int PlayerOneTotalWins()
{
    vector< pair<Hand,Hand> > game = GetGames();

    return CountPlayerOneWins(game);
}

int main()
{
    cout << PlayerOneTotalWins() << endl;
}


bool CardCompare(Card card1, Card card2)
{
    return card1.value < card2.value;
}

Hand::Hand(Card card1, Card card2, Card card3, Card card4, Card card5)
{
    cards.push_back(card1);
    cards.push_back(card2);
    cards.push_back(card3);
    cards.push_back(card4);
    cards.push_back(card5);

    sort(cards.begin(), cards.end(), CardCompare);
}

bool Hand::IsBetterHand(Hand other)
{
    PokerHand handValue1 = GetHandValue();
    PokerHand handValue2 = other.GetHandValue();

    if (handValue1 > handValue2)
    {
        return true;
    }
    else if (handValue1 < handValue2)
    {
        return false;
    }

    if (handValue1 == StraightFlush)
    {
        return IsBetterStraightFlush(other);
    }
    else if (handValue1 == FourOfAKind)
    {
        return IsBetterFourOfAKind(other);
    }
    else if (handValue1 == FullHouse)
    {
        return IsBetterFullHouse(other);
    }
    else if (handValue1 == Flush)
    {
        return IsBetterFlush(other);
    }
    else if (handValue1 == Straight)
    {
        return IsBetterStraight(other);
    }
    else if (handValue1 == ThreeOfAKind)
    {
        return IsBetterThreeOfAKind(other);
    }
    else if (handValue1 == TwoPairs)
    {
        return IsBetterTwoPairs(other);
    }
    else if (handValue1 == OnePair)
    {
        return IsBetterOnePair(other);
    }

    return IsBetterHighCard(other);
}

bool Hand::IsBetterStraightFlush(Hand other)
{
    return IsBetterHighCard(other);
}

bool Hand::IsBetterFourOfAKind(Hand other)
{
    CardValue value1 = GetCardValueForNOfAKind(4);
    CardValue value2 = other.GetCardValueForNOfAKind(4);

    return value1 > value2;
}

bool Hand::IsBetterFullHouse(Hand other)
{
    return IsBetterThreeOfAKind(other);
}

bool Hand::IsBetterFlush(Hand other)
{
    return IsBetterHighCard(other);
}

bool Hand::IsBetterStraight(Hand other)
{
    return IsBetterHighCard(other);
}

bool Hand::IsBetterThreeOfAKind(Hand other)
{
    CardValue value1 = GetCardValueForNOfAKind(3);
    CardValue value2 = other.GetCardValueForNOfAKind(3);

    return value1 > value2;
}

bool Hand::IsBetterTwoPairs(Hand other)
{
    pair<CardValue,CardValue> values1 = GetCardValueForNOfAKindAndMOfAKind(2,2);
    pair<CardValue,CardValue> values2 = other.GetCardValueForNOfAKindAndMOfAKind(2,2);

    if (max(values1.first, values1.second) > max(values2.first, values2.second))
    {
        return true;
    }
    else if (min(values1.first, values1.second) > min(values2.first, values2.second))
    {
        return true;
    }
    else if (max(values1.first, values1.second) < max(values2.first, values2.second))
    {
        return false;
    }
    else if (min(values1.first, values1.second) < min(values2.first, values2.second))
    {
        return false;
    }

    return IsBetterHighCard(other);
}

bool Hand::IsBetterOnePair(Hand other)
{
    CardValue value1 = GetCardValueForNOfAKind(2);
    CardValue value2 = other.GetCardValueForNOfAKind(2);

    if (value1 > value2)
    {
        return true;
    }
    else if (value1 < value2)
    {
        return false;
    }

    return IsBetterHighCard(other);
}

bool Hand::IsBetterHighCard(Hand other)
{
    for (int i=cards.size()-1; i>=0; --i)
    {
        if (cards[i].value > other.cards[i].value)
        {
            return true;
        }
        else if (cards[i].value < other.cards[i].value)
        {
            return false;
        }
    }

    // Should never occur, but this is a full tie.
    return false;
}

pair<CardValue,CardValue> Hand::GetCardValueForNOfAKindAndMOfAKind(int n, int m)
{
    bool foundN = false;
    bool foundM = false;
    CardValue valueN;
    CardValue valueM;
    
    map<int,int> cardValueCount = CountCardValues();

    for (map<int,int>::iterator it=cardValueCount.begin();
            it != cardValueCount.end(); ++it)
    {
        if (!foundN && it->second == n)
        {
            valueN = (CardValue)it->first;
            foundN = true;
        }
        else if (it->second == m)
        {
            valueM = (CardValue)it->first;
            foundM = true;
        }
    }

    if (!(foundN && foundM))
    {
        cout << "Error has occurred!!!!" << endl;
        exit(1);
    }

    return make_pair(valueN, valueM);
}

CardValue Hand::GetCardValueForNOfAKind(int n)
{
    map<int,int> cardValueCount = CountCardValues();

    for (map<int,int>::iterator it=cardValueCount.begin();
            it != cardValueCount.end(); ++it)
    {
        if (it->second == n)
        {
            return (CardValue)(it->first);
        }
    }

    cout << "Error occurred!!!" << endl;
    exit(1);
}


PokerHand Hand::GetHandValue()
{
    if (IsRoyalFlush())
    {
        return RoyalFlush;
    }
    else if (IsStraightFlush())
    {
        return StraightFlush;
    }
    else if (IsFourOfAKind())
    {
        return FourOfAKind;
    }
    else if (IsFullHouse())
    {
        return FullHouse;
    }
    else if (IsFlush())
    {
        return Flush;
    }
    else if (IsStraight())
    {
        return Straight;
    }
    else if (IsThreeOfAKind())
    {
        return ThreeOfAKind;
    }
    else if (IsTwoPairs())
    {
        return TwoPairs;
    }
    else if (IsOnePair())
    {
        return OnePair;
    }
    else
    {
        return HighCard;
    }
}

map<int,int> Hand::CountCardValues()
{
    map<int,int> cardValueCount;

    for (int i=0; i<cards.size(); ++i)
    {
        if (cardValueCount.count(cards[i].value) == 0)
        {
            cardValueCount[cards[i].value] = 1;
        }
        else
        {
            ++cardValueCount[cards[i].value];
        }
    }

    return cardValueCount;
}

bool Hand::HasNOfAKind(int n)
{
    map<int,int> cardValueCount = CountCardValues();

    for (map<int,int>::iterator it=cardValueCount.begin();
            it != cardValueCount.end(); ++it)
    {
        if (it->second >= n)
        {
            return true;
        }
    }

    return false;
}

bool Hand::HasNOfAKindAndMOfAKind(int n, int m)
{
    map<int,int> cardValueCount = CountCardValues();

    bool foundN = false;
    bool foundM = false;

    for (map<int,int>::iterator it=cardValueCount.begin();
            it != cardValueCount.end(); ++it)
    {
        if (!foundN && it->second == n)
        {
            foundN = true;
        }
        else if (it->second == m)
        {
            foundM = true;
        }
    }

    return foundN && foundM;
}

bool Hand::AceExists()
{
    for (int i=0; i<cards.size(); ++i)
    {
        if (cards[i].value == Ace)
        {
            return true;
        }
    }

    return false;
}

bool Hand::IsRoyalFlush()
{
    return (IsStraightFlush() && AceExists());
}

bool Hand::IsStraightFlush()
{
    return (IsStraight() && IsFlush());
}

bool Hand::IsFourOfAKind()
{
    return HasNOfAKind(4);
}

bool Hand::IsFullHouse()
{
    return HasNOfAKindAndMOfAKind(3, 2);
}

bool Hand::IsFlush()
{
    for (int i=0; i<cards.size(); ++i)
    {
        if (cards[0].suit != cards[i].suit)
        {
            return false;
        }
    }

    return true;
}

bool Hand::IsStraight()
{
    sort(cards.begin(), cards.end(), CardCompare);

    for (int i=0; i<cards.size() - 1; ++i)
    {
        if (cards[i+1].value - cards[i].value != 1)
        {
            return false;
        }
    }

    return true;
}

bool Hand::IsThreeOfAKind()
{
    return HasNOfAKind(3);
}

bool Hand::IsTwoPairs()
{
    return HasNOfAKindAndMOfAKind(2, 2);
}

bool Hand::IsOnePair()
{
    return HasNOfAKind(2);
}

