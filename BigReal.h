#ifndef BIGINT_BIGREAL_H
#define BIGINT_BIGREAL_H
#include <bits/stdc++.h>
#include "Bigint.h"
using namespace std;

class BigReal {
private:
    int decimalPointPosition;
    Bigint decimalNumber;
    bool checkValidInput(const string& input);
    void deleteZerosFromFractionPart();
    void addZerosToFractionPart(BigReal& realNumber, int times);
    void equalFractionPartLength(BigReal& firstNumber, BigReal& secondNumber);
    void zeros_after_dpp();
public:
    BigReal (double realNumber = 0.0); // Default constructor
    BigReal (string realNumber); // Initialize from string
    BigReal (const BigReal& other); // Copy constructor
    BigReal (BigReal&& anotherReal) noexcept;
    BigReal& operator= (BigReal& other); // Assignment operator
    BigReal& operator= (BigReal&& anotherReal) noexcept;
    void setNum (string realNumber);
    BigReal operator+ (BigReal& other);
    BigReal operator- (BigReal& other);
    bool operator< (BigReal anotherReal);
    bool operator> (BigReal anotherReal);
    bool operator== (BigReal anotherReal);
    friend ostream& operator << (ostream& out, BigReal num);
    bool sign();
    int size();
};


#endif //BIGINT_BIGREAL_H
